#include "chart.h"
#include <QPainter>
#include <QRgb>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileDialog>


Chart::Chart(QWidget *parent):
    QWidget(parent)
{
    this->setAutoFillBackground(true);

}

