#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client("eu.thethings.network:1883",
            "sync_subcribe_cpp",
            "es_sensor_network/devices/es_rasp_sn/up",
            "es_sensor_network",
            "ttn-account-v2.NC7lBuZ1_ztXF1cSXrJnswIX4kDSCBJjQTWF_xIjce4")
{
    ui->setupUi(this);
    client.connect();

}

MainWindow::~MainWindow()
{
    delete ui;
    client.disconnect();
}
