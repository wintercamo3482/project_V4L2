#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("카메라 어플리케이션");

    QPixmap pix("/home/ubuntu2004/dev_ws/project_V4L2/res/Lenna.png");

    int w = ui->label_display->width ();
    int h = ui->label_display->height ();
    ui->label_display->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    ui->btn_fileOpen->setText("파일 열기");
    ui->btn_startCam->setText("웹캠 시작");
    ui->btn_stopCam->setText("웹캠 종료");

    connect(ui->btn_fileOpen, &QPushButton::clicked, this, &Widget::btn_fileOpen_clicked);
    connect(ui->btn_startCam, &QPushButton::clicked, this, &Widget::btn_startCam_clicked);
    connect(ui->btn_stopCam, &QPushButton::clicked, this, &Widget::btn_stopCam_clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::btn_fileOpen_clicked()
{
    qDebug("open clicked");
    // Qstring file_path = QFileDialog::getOpenFileName(this, )
}

void Widget::btn_startCam_clicked()
{
    qDebug("start clicked");
}

void Widget::btn_stopCam_clicked()
{
    qDebug("stop clicked");
}