#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>
#include <QtCore/QDateTime>
#include <QtWidgets/QMessageBox>
#include <QMetaEnum>
#include <QTextCursor>
#include "chartwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonConnect_clicked();
    void on_buttonSubscribe_clicked();
    void updateLogStateChange();
    void connectedSlot();
    void disconnectedSlot();
    void usernameChangedSlot();
    void passwordChangedSlot();
    void updateLogErrorChanged();
    void disconnectionSlot();
    void messageReceivedSlot(const QByteArray &message, const QMqttTopicName &topic);

private:
    Ui::MainWindow *ui;
    QMqttClient *client;
    ChartWindow *w;
    QString msg;
};

#endif // MAINWINDOW_H
