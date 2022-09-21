#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 添加折线图
    ui->graphicsView->setChart(createLineChart());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chart;
    delete pWavelengthData;
    delete pData;
}

QChart *MainWindow::createLineChart()
{
    // 创建QChart对象
    chart = new QChart();

    // 创建折线图系列对象
    series = new QLineSeries(chart);

    // 设置通用属性
    setChartAttribute(chart, "近红外光谱仪");
    // 返回QChart对象
    return chart;
}

void MainWindow::setChartAttribute(QChart *chart, QString title)
{
    //主题
    chart->setTheme(QChart::ChartThemeLight);
    //设置动画
    chart->setAnimationOptions(QChart::AllAnimations);
    //隐藏图例
    chart->setBackgroundVisible(true);
    // 创建默认坐标轴
    chart->createDefaultAxes();
    //设置图表坐标轴的范围，可以不设置，自动调节的
    //chart->axisX()->setRange(3000, 12000);
    //chart->axisY()->setRange(0, 1);
    // 设置标题
    chart->setTitle(title);
    //隐藏图例
    chart->legend()->hide();
    // 设置data，在设置标题时使用
    chart->setData(Qt::UserRole, title);
}


void MainWindow::setSeries(){

    series->clear();
    //写入数据
    for(int  i = 0;i<fileSize;++i)
    {
        series->append( pWavelengthData[i],pData[i]);
    }
    // 将series添加到QChart对象中
    chart->addSeries(series);
}


void MainWindow::getTxtData(std::vector<std::vector<double>>& res,std::string fileRoute){

    std::ifstream infile;

    //将文件流对象与文件连接起来
    infile.open(fileRoute);
    //若失败,则输出错误消息,并终止程序运行
    assert(infile.is_open());
    std::vector<double> spe;
    std::string s;
    while (getline(infile, s)) {
        std::istringstream is(s); //将读出的一行转成数据流进行操作
        double d;
        while (!is.eof()) {
            is >> d;
            spe.push_back(d);
        }
        res.push_back(spe);
        spe.clear();
        s.clear();
    }
    infile.close();             //关闭文件输入流

}

void MainWindow::on_clear_clicked()
{
    QVector<QPointF> points;
    series->replace(points);
    chart->createDefaultAxes();
}

void MainWindow::connect_NIR()
{
    //Get data
    devNum = 0;
    if(enumerateDevices(&devNum)<0)
    {
        ui->statusbar->showMessage("Enumerate NIR device error,exit!!!",2000);
    }else
    {
        ui->statusbar->showMessage(&"NIR device number " [ devNum],2000);

        //open device
        if(openSpectrometer(devNum-1)<0){
            ui->statusbar->showMessage(&"Failed to open NIR device" [ devNum],2000);
        }
        ui->statusbar->showMessage(&"Open NIR device success" [ devNum],2000);

    }
}

 void MainWindow::scan_NIR()
 {

     fileSize = 0;
     time=0;
     getFormattedSpectrumLengths(&fileSize);
     pWavelengthData = new double(fileSize);
     pData = new unsigned int(fileSize);
     getFormattedSpectrum(pWavelengthData,pData);
     time = getEstimatedScanTime();
     if(fileSize == 0)
         ui->statusbar->showMessage("Failed to get data",2000);
     setSeries();
     setChartAttribute(chart, "近红外光谱仪");

 }

void MainWindow::on_start_clicked()
{
    connect_NIR();
}


void MainWindow::on_sacn_clicked()
{
    if(devNum == 0)
        ui->statusbar->showMessage(&"Please open NIR device" [ devNum],2000);
    else
        scan_NIR();
    ui->lcdNumber->display(time);

}

//扫描模式不同
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int tmp = ui->comboBox->currentIndex();
    if(tmp==0)
        setChartAttribute(chart, "近红外光谱仪");
    if(tmp==1)
        setChartAttribute(chart, "近红外光谱仪");
    if(tmp==2)
        setChartAttribute(chart, "近红外光谱仪");
}


void MainWindow::OnExportBtnClicked()
{
    //1.选择导出的csv文件保存路径
    QString csvFile = QFileDialog::getExistingDirectory(this);
    if(csvFile.isEmpty())
       return;

    //2.文件名采用系统时间戳生成唯一的文件
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    csvFile += tr("/%1.csv").arg(current_date);

    //3.用QFile打开.csv文件 如果不存在则会自动新建一个新的文件
    QFile file(csvFile);
    if ( file.exists())
    {
        //如果文件存在执行的操作，此处为空，因为文件不可能存在
    }
    file.open( QIODevice::ReadWrite | QIODevice::Text );
    statusBar()->showMessage(tr("Saving data"));
    QTextStream out(&file);

    //4.获取数据
    for(int i = 0;i<fileSize;++i){
        out<<pWavelengthData[i]<<pData[i];
    }

    //其他数据可按照这种方式进行添加即可

    //5.写完数据需要关闭文件
    file.close();
}


void MainWindow::on_pushButton_clicked()
{
    OnExportBtnClicked();
}

bool MainWindow::predict(svm_problem *prob_inline)
{
   ui->statusbar->showMessage("predict marche" );
   //svm_model model2=svm_load_model("MyModel.txt");
   //return svm_predict(&model2,&prob_inline);
   return false;
}


void MainWindow::train(std::string path)
{
    fp = fopen("MyModel.txt","r");
    if(fp) //need to change!!!
    {
        ui->statusbar->showMessage("model has been generated" );
    }else
    {
        ui->statusbar->showMessage("train success" );

        int count=0,count_y=0;

        //Create svm_problem struct for Data
        problem.l = InfraredNum;
        problem.y = new double[problem.l];

        svm_node *x_space = new svm_node[(FeatureNum+1)*problem.l];
        problem.x = new svm_node *[problem.l];

        //读取文件中的数据
        std::ifstream ifs;							//创建流对象
        ifs.open(path,std::ios::in);	//打开文件
        //ifs.open(path);	//打开文件
        if (!ifs.is_open())						//判断文件是否打开
        {
            ui->statusbar->showMessage("Failed open file!!!");
            return;
        }
        std::vector<std::string> item;		//用于存放文件中的一行数据
        std::string temp;				//临时存储文件中的一行数据
        getline(ifs, temp);
        getline(ifs, temp);//前两行不需要存放在数据中

        while(getline(ifs, temp))  //利用 getline（）读取文件中的每一行，并放入到 item 中
        {
            item.push_back(temp);
        }
        ui->statusbar->showMessage(&"item size:" [item.size()]);
        //遍历文件中的每一行数据
        int count_x=0;
        for (auto it = item.begin(); it != item.end(); it++)
        {
            int before = count;
            std::string str;
            //其作用是把字符串分解为单词(在此处就是把一行数据分为单个数据)
            std::istringstream istr(*it);
            //将字符串流 istr 中的字符读入到 str 字符串中，读取方式是以逗号为分隔符
            getline(istr, str, ',');
            str = str.substr(0,2);
            if(!str.compare("HH"))
                problem.y[count_y++] = 1;
            else if(!str.compare("ZH"))
                problem.y[count_y++] = 2;
            else if(!str.compare("YC"))
                problem.y[count_y++] = 3;
            else if(!str.compare("DL"))
                problem.y[count_y++] = 4;
//            cout << str << "\t";            // str 对应第一列数据
//            cout << problem->y[count_y-1] << "\t";

            for(int i=0;i<FeatureNum;i++)
            {
                getline(istr, str, ',');
                x_space[count].index = i;
                x_space[count].value = atof(str.c_str());
                //cout << x_space[count].value << " ";            // str 对应第二列数据
                count++;
            }
            x_space[count].index = -1;
            problem.x[count_x++] = &x_space[before];
            count++;
            //cout << endl;
        }

    }

    //parameter initialized
    param.svm_type = C_SVC;
    param.kernel_type = RBF;
    param.degree = 3;
    param.gamma = 0.0001;
    param.coef0 = 0;
    param.nu = 0.5;
    param.cache_size = 100;
    param.C = 10;
    param.eps = 1e-5;
    param.shrinking = 1;
    param.probability = 0;
    param.nr_weight = 0;
    param.weight_label = NULL;
    param.weight = NULL;

    ui->statusbar->showMessage("svm train start");
    svm_model *model = svm_train(&problem,&param);
    ui->statusbar->showMessage("svm train start +1 ");
    svm_save_model("MyModel.txt",model);
    ui->statusbar->showMessage("svm train end");

}
