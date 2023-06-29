#include "mainwindow.h"
#include "dbusListener.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();
    dbusListener dt("org.gspine.gesture", "/org/gspine/gesture", &w);
    w.hide();
    return a.exec();
}
