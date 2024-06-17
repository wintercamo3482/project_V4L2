#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("카메라 어플리케이션");

    int w = ui->label_display->width ();
    int h = ui->label_display->height ();
    
    file.setFileName("/home/ubuntu2004/dev_ws/project_V4L2/res/pattern.yuv");

    if (file.open(QIODevice::ReadOnly)) // 파일 읽기에 성공하면?
    {
        timer = new QTimer(this);   // QTimer 인스턴스 생성
        connect(timer, &QTimer::timeout, this, &Widget::updateFrame);   // 이를 인라인 함수에 연결
        timer->start(33); // 대충 30 fps에 맞춰서 해당 함수 실행하게끔
    }

    ui->btn_fileOpen->setText("파일 열기");
    ui->btn_startCam->setText("웹캠 시작");
    ui->btn_stopCam->setText("웹캠 종료");

    connect(ui->btn_fileOpen, &QPushButton::clicked, this, &Widget::btn_fileOpen_clicked);
    connect(ui->btn_startCam, &QPushButton::clicked, this, &Widget::btn_startCam_clicked);
    connect(ui->btn_stopCam, &QPushButton::clicked, this, &Widget::btn_stopCam_clicked);
};

Widget::~Widget()
{
    file.close();
    delete ui;
}

void Widget::btn_fileOpen_clicked()
{
    qDebug("open clicked");
}

void Widget::btn_startCam_clicked()
{
    qDebug("start clicked");
}

void Widget::btn_stopCam_clicked()
{
    qDebug("stop clicked");
}

void Widget::updateFrame()
{
    frameData = file.read(frameSize);   // 파일에서 frameSize만큼 데이터를 읽어 frameData 바이트 배열에 저장

    if (frameData.size() == frameSize)  // 파일에서 읽은 데이터의 크기와 예상한 프레임 크기의 일치 여부 판단
    {
        QImage image = decoder.convert2RGB(frameData, width, height);   // YUYV 데이터를 RGB QImage로 변환
        ui->label_display->setPixmap(QPixmap::fromImage(image));
        ui->label_display->setScaledContents(true);
    }
}