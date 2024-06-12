#include <iostream>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <cstring>
#include <sys/mman.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace std;

int main()
{
    // 1. 디바이스 열기
    int fd = open("/dev/video0", O_RDWR);

    if (fd == -1)
    {
        cerr << "Opening video device" << endl;
        return -1;
    }

    // 캡쳐 기능 등 지원 여부
    v4l2_capability cap;

    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
    {
        cerr << "Querying Capabilities" << endl;
        return -1;
    }

    // 포맷 설정
    v4l2_format fmt;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 640;
    fmt.fmt.pix.height = 480;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    fmt.fmt.pix.field = V4L2_FIELD_NONE;

    if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
    {
        cerr << "Setting Pixel Format" << endl;
        return -1;
    }

    // 요청 버퍼 설정
    v4l2_requestbuffers req;
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1)
    {
        cerr << "Requesting Buffer" << endl;
        return -1;
    }

    // 쿼리 버퍼
    v4l2_buffer buf;
    memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;

    if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1)
    {
        cerr << "Querying Buffer" << endl;
        return -1;
    }

    void* buffer_start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
    
    if (buffer_start == MAP_FAILED)
    {
        cerr << "mmap" << endl;
        return -1;
    }

    // 큐 버퍼
    if (ioctl(fd, VIDIOC_QBUF, &buf) == -1)
    {
        cerr << "Query Buffer" << endl;
        return -1;
    }


    // 스트림 시작
    int type = buf.type;

    if (ioctl(fd, VIDIOC_STREAMON, &type) == -1)
    {
        cerr << "Start Capture" << endl;
        return -1;
    }

    cv::namedWindow("v4l2 webcam", cv::WINDOW_AUTOSIZE);

    while (1)
    {
        // 디큐 버퍼
        if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1)
        {
            cerr << "Retrieving Frame" << endl;
            return -1;
        }

        cv::Mat img = cv::imdecode(cv::Mat(1, buf.bytesused, CV_8UC1, buffer_start), cv::IMREAD_COLOR);
        if (img.empty()) {
            cerr << "Could not decode frame" << endl;
            continue;
        }

        imshow("v4l2 webcam", img);

        if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)
        {
            cerr << "Query Buffer" << endl;
            return -1;
        }

        if (cv::waitKey(1) >= 0)
        {
            // 스트림 종료
            if (ioctl(fd, VIDIOC_STREAMOFF, &type) < 0)
            {
                cerr << "Stop stream" << endl;
                return -1;
            }
            break;
        }
    }

    close(fd);
    return 0;
}