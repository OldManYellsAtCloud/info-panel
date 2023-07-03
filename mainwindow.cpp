#include "mainwindow.h"
#include "brightness.h"
#include "./ui_mainwindow.h"
#include "config.h"

#include <unistd.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int baseBrightness = config::getConfig().getIntConfig("brightness");
    if (baseBrightness < 0 || baseBrightness > 100) {
        baseBrightness = Brightness::brightnessHandler().getBrightness();
        config::getConfig().setIntConfig("brightness", baseBrightness);
    }
    ui->brightnessSlider->setValue(baseBrightness);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    Brightness::brightnessHandler().setBrightness(value);
    config::getConfig().setIntConfig("brightness", value);
    ui->brightnessLabel->setText(QStringLiteral("Brightness - %1%").arg(value));
}


void MainWindow::on_restartButton_released()
{
    QMessageBox::StandardButton response = QMessageBox::question(this, "Reboot", "Reboot?", QMessageBox::Yes|QMessageBox::No);
    if (response == QMessageBox::Yes) {
        execl("/sbin/shutdown", "shutdown", "-r", "now", (char *)0);
    }
}


void MainWindow::on_shutDownButton_released()
{
    QMessageBox::StandardButton response = QMessageBox::question(this, "Shut down", "Shut down?", QMessageBox::Yes|QMessageBox::No);
    if (response == QMessageBox::Yes) {
        execl("/sbin/shutdown", "shutdown", "-P", "now", (char *)0);
    }
}

