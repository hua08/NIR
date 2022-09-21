#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <fstream>
#include <sstream>
#include <QtCharts/QLineSeries>
#include <QDateTime>
#include <QFileDialog>
#include <QTextStream>
#include "easynirwrapper.h"
#include "svm.h"

//! 使用QChart需要使用对应的命名空间
//! 使用方法有如下两种（更改宏定义判断条件即可更换调用方法）
#if false
QT_CHARTS_USE_NAMESPACE     // 定义好的宏定义使用命名空间
#else
using namespace QtCharts;   // 常规使用命名空间的方法
#endif

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief createLineChart 创建折线图指针
     * @return 返回折线图QChart指针
     */
    QChart *createLineChart();

    void setChartAttribute(QChart *chart, QString title);

    void setChartValue(QVector<double> &x,QVector<double> &y);

    void setSeries();

    void getTxtData(std::vector<std::vector<double>>& res,std::string fileRoute);

    void connect_NIR();

    void scan_NIR();


    void OnExportBtnClicked();


private slots:
    void on_clear_clicked();

    void on_start_clicked();

    void on_sacn_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QChart *chart;
    QLineSeries *series;

    int devNum;
    int fileSize;
    double *pWavelengthData;
    unsigned int *pData;
    int time;


    FILE *fp;
    std::string path="D:\\7.code\\NIR\\NIR\\InfraredData\\Infrared_data.csv";

    int InfraredNum = 251;
    int FeatureNum = 1102;
    std::vector<int> target;
    svm_problem problem;
    svm_parameter param;
    svm_problem prob_inline;



    void train(std::string path);
    bool predict(svm_problem *prob_inline);
};
#endif // MAINWINDOW_H
