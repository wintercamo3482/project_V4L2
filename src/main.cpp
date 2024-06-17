#include "widget.h" // widget.h 불러오기

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);   // QApplication 인스턴스 생성
    Widget w;                       // 작성한 Widget 생성
    w.show();                       // 해당 위젯 show
    return app.exec();              // 이벤트 루프 실행
}