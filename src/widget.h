#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTimer>
#include <QByteArray>

#include "YUVDecoder.h"

namespace Ui    // 이게 표준. 안 바꾸는 게 맞음.
{
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT                                    // Signal Slot을 사용하기 위해 명시

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui; // Designer에서 생성된 UI파일 코드에 연결하기 위한 포인터
    QFile file;
    QByteArray frameData;   // 파일로부터 읽은 데이터를 임시 저장하는 바이트 배열. 여기선 Video의 FrameData 저장 용도로 사용
    QTimer *timer;
    YUVDecoder decoder;
    int width = 1280;
    int height = 720;
    int frameSize = width * height * 2; // 각 비디오 프레임의 총 바이트 수를 저장. YUYV인 걸 고려하여 크기 지정.

public slots:
    void btn_fileOpen_clicked();
    void btn_startCam_clicked();
    void btn_stopCam_clicked();

private slots:
    void updateFrame(); // 새 프레임 데이터를 처리하고, 결과를 QTimer 객체의 timeout() 신호와 연결. 일정 시간마다 timeout() 신호가 발생하고, updateFrame 슬롯을 자동으로 호출하여 프레임을 주기적으로 업데이트
};

#endif