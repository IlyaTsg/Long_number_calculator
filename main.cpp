#include <QApplication>
#include "MainWindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window(0);
    window.show();
    return app.exec();
}
