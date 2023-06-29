#include "mainwindow.h"
#include "brightness.h"
#include "./ui_mainwindow.h"

#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->brightnessSlider->setValue(Brightness::brightnessHandler().getBrightness());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    Brightness::brightnessHandler().setBrightness(value);
    ui->brightnessLabel->setText(QStringLiteral("Brightness - %1%").arg(value));
}


void MainWindow::on_restartButton_released()
{
    execl("/sbin/shutdown", "shutdown", "-r", "now", (char *)0);
}


void MainWindow::on_shutDownButton_released()
{
    execl("/sbin/shutdown", "shutdown", "-P", "now", (char *)0);
}

