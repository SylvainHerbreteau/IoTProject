#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QDialog>
#include <QMqttClient>
#include "datachart.h"
#include "ui_chartwindow.h"

namespace Ui {
class ChartWindow;
}

class ChartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = nullptr);

    void parseMessage(QString msg);
    ~ChartWindow();

public slots :
    void messageReceivedSlot(const QByteArray &message, const QMqttTopicName &topic); //update LCD + add Combo box
    void displayJson(int cMsg);

private slots :
    void selectedCombo();

private:
    Ui::ChartWindow *ui;
    datachart *data;
    QList<QChartView *> charts;
    int currentMsg;
};

#endif // CHARTWINDOW_H
