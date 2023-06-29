#include "mainwindow.h"
#include "dbustest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();
    dbustest dt("org.gspine.gesture", "/org/gspine/gesture", &w);
    w.hide();
    return a.exec();
}
