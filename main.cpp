#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!createConnection()) // 初始化数据库
        return 1;
    MainWindow w;
    w.show();
    QDesktopWidget *desktop = QApplication::desktop();                                // 设置窗口出现在屏幕正中间
    w.move((desktop->width() - w.width()) / 2, (desktop->height() - w.height()) / 2); // 设置窗口出现在屏幕正中间
    return app.exec();
}
