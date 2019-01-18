#include "datachart.h"

datachart::datachart()
{
    nb_msg = 0;
    min_temp = 0;
    max_temp = 0;

    min_hum = 0;
    max_hum = 0;

    min_pres = 0;
    max_pres = 0;

    chart_temp = new QChart();
    chart_hum = new QChart();
    chart_pres = new QChart();

    chart_temp->setTitle("Temperature Chart");
    chart_hum->setTitle("Humidity Chart");
    chart_pres->setTitle("Pressure Chart");

    chart_temp->setTheme(QChart::ChartThemeDark);
    chart_hum->setTheme(QChart::ChartThemeDark);
    chart_pres->setTheme(QChart::ChartThemeDark);

    series_temp = new QLineSeries(chart_temp);
    series_hum = new QLineSeries(chart_hum);
    series_pres = new QLineSeries(chart_pres);

    chart_temp->createDefaultAxes();
    chart_hum->createDefaultAxes();
    chart_pres->createDefaultAxes();


    series_temp->setName("Temperature");
    series_hum->setName("Humidity");
    series_pres->setName("Pressure");

}

datachart::~datachart(){
    delete chart_temp;
    delete chart_hum;
    delete chart_pres;

    delete series_temp;
    delete series_hum;
    delete series_pres;
}
