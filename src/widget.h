#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
// #include <QLabel>
// #include <QPixmap>

namespace Ui
{
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui; // 윈도우상에 배치한 위젯에 접근하기 위한 오브젝트

public slots:
    void btn_fileOpen_clicked();
    void btn_startCam_clicked();
    void btn_stopCam_clicked();
};

#endif