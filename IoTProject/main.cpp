#include "mainwindow.h"
#include "chartwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignLeft,
                    w.size(),
                    a.desktop()->availableGeometry()
                ));
    //ChartWindow d;
    w.show();
    //d.show();

    return a.exec();
}
