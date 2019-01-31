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

    //Used to parse the received message
    void parseMessage(QString msg);

    //Used to display the Json on the textEdit widget
    void displayJson(int cMsg);
    ~ChartWindow();

public slots :
    /* Called when a message is received*/
    void messageReceivedSlot(const QByteArray &message, const QMqttTopicName &topic);


private slots :
    void selectedCombo();

private:
    Ui::ChartWindow *ui;
    QChartView * chartview;
    datachart *data;
    QList<QChartView *> charts;
    int currentMsg;
};

#endif // CHARTWINDOW_H
