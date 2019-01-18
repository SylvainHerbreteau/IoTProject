#ifndef DATACHART_H
#define DATACHART_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <vector>
#include "json.hpp"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

using json = nlohmann::json;

class datachart
{
public:
    datachart();
    ~datachart();
    int nb_msg;
    double min_temp, max_temp, min_hum, max_hum, min_pres, max_pres;

    QLineSeries *series_temp;
    QLineSeries *series_hum;
    QLineSeries *series_pres;

    QChart *chart_temp;
    QChart *chart_hum;
    QChart *chart_pres;

    QList<QString> list_msg;
    QList<json> list_msg_json;
};

#endif // DATACHART_H
