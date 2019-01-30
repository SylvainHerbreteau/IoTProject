#include "chartwindow.h"
#include "ui_chartwindow.h"
#include <iostream>
#include <string>
#include <QMessageBox>
#include <QBrush>

ChartWindow::ChartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);
    data = new datachart();

    /* Used to display the charts in a retty way */
    ui->gridLayoutChart->setOriginCorner(Qt::BottomRightCorner);

    chartview = new QChartView(data->chart_temp);
    ui->gridLayoutChart->addWidget(chartview);
    charts << chartview;

    chartview = new QChartView(data->chart_hum);
    ui->gridLayoutChart->addWidget(chartview, 1, 1);
    charts << chartview;

    chartview = new QChartView(data->chart_pres);
    ui->gridLayoutChart->addWidget(chartview, 0, 1);
    charts << chartview;


    /*Setting background color*/
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChartWindow::selectedCombo);

    currentMsg = 0;

}

void ChartWindow::parseMessage(QString msg){
    data->list_msg.append(msg);
    data->nb_msg++;
    json j = json::parse(msg.toStdString());

    data->list_msg_json.append(j);

    double pres = j["payload_fields"]["barometric_pressure_3"].get<double>();
    double hum  = j["payload_fields"]["relative_humidity_2"].get<double>();
    double temp = j["payload_fields"]["temperature_1"].get<double>();

    if(temp < data->min_temp)
        data->min_temp = temp;
    if(temp > data->max_temp)
        data->max_temp = temp;
    if(hum < data->min_hum)
        data->min_hum = hum;
    if(hum > data->max_hum)
        data->max_hum = hum;
    if(pres < data->min_pres)
        data->min_pres = pres;
    if(pres > data->max_pres)
        data->max_pres = pres;


    data->series_temp->append(data->nb_msg, temp);
    data->series_hum->append(data->nb_msg, hum);
    data->series_pres->append(data->nb_msg, pres);

    data->chart_temp->addSeries(data->series_temp);
    data->chart_hum->addSeries(data->series_hum);
    data->chart_pres->addSeries(data->series_pres);

    data->chart_temp->createDefaultAxes();
    data->chart_hum->createDefaultAxes();
    data->chart_pres->createDefaultAxes();

    data->chart_temp->axisX()->setRange(0, data->nb_msg);
    data->chart_hum->axisX()->setRange(0, data->nb_msg);
    data->chart_pres->axisX()->setRange(0, data->nb_msg);

    data->chart_temp->axisY()->setRange(25, data->max_temp +1);
    data->chart_hum->axisY()->setRange(25, data->max_hum +1);
    data->chart_pres->axisY()->setRange(1000, data->max_pres +1);

    ui->lcdNumber_temp->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
    ui->lcdNumber_humidity->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
    ui->lcdNumber_pression->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

}

void ChartWindow::messageReceivedSlot(const QByteArray &message, const QMqttTopicName &topic){

    QString msgstr = QString::fromStdString(message.toStdString());
    parseMessage(msgstr);
    ui->comboBox->addItem("Message n°" + QString::number(data->nb_msg) + " " + topic.name());
    ui->comboBox->setItemData(ui->comboBox->count() - 1, QBrush(Qt::blue), Qt::TextColorRole);
}

void ChartWindow::displayJson(int cmsg){
    if(data->list_msg_json.size() > 0){
        std::string str = data->list_msg_json.at(cmsg).dump(4);
        ui->plainTextEdit->insertPlainText(QString::fromStdString(str));
    }

}

void ChartWindow::selectedCombo(){

    ui->plainTextEdit->clear();
    currentMsg = ui->comboBox->currentIndex();
    displayJson(currentMsg);
    ui->comboBox->setItemData(currentMsg, QBrush(Qt::black), Qt::TextColorRole);

    ui->lineEdit->clear();
    ui->lineEdit->insert("Message n° : " + QString::number(currentMsg +1));
    ui->lcdNumber_temp->display(data->series_temp->at(currentMsg).y());
    ui->lcdNumber_humidity->display(data->series_hum->at(currentMsg).y());
    ui->lcdNumber_pression->display(data->series_pres->at(currentMsg).y());

}

ChartWindow::~ChartWindow()
{
    delete chartview;
    delete data;
    delete ui;
}
