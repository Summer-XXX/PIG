#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QMenu>
#include<QImage>
#include<QAction>
#include<QActionEvent>
#include<QMovie>
#include<QWidget>
#include<QTime>
#include<QTimer>
#include<QDebug>
#include<QVector>
#include<QLayout>
#include<QFrame>
#include<QFile>
#include<QDesktopServices>
struct pig{
    double w;
    int boughtyear,boughtday,type;
};
    QVector <pig> pigs[100];
    int currentpighome,currentmonth,maxlockpighome,gold;
    int buffprice=100,buffspeed=100,maxpigcansell=1000;
    int pighomestoretype[105];
    int sciencemap[2][15];
    int scx,scy;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //为存档案件添加的
    QMenu* load_menu=new QMenu;
    QAction* loadlateset = new QAction("读取存档");
    QAction* resetdata = new QAction("重置存档");
    load_menu->addAction(loadlateset);
    load_menu->addAction(resetdata);
    ui->Qbtnloadgame->setMenu(load_menu);
    QObject::connect(loadlateset, SIGNAL(triggered(bool)), this, SLOT(on_loadgame_clicked()));
    QObject::connect(resetdata, SIGNAL(triggered(bool)), this, SLOT(on_reset_clicked()));
    //canexit=1;


    setAllbutadisappear();
    nullmovie=new QMovie;
    bigpig=new QMovie;
    bigpig->setFileName(":/new/buta/Resource/bigpigr.gif");
    blackpig=new QMovie;
    blackpig->setFileName(":/new/buta/Resource/blackpigr.gif");
    colouredpig=new QMovie;
    colouredpig->setFileName(":/new/buta/Resource/colouredpigr.gif");
    //猪移动的计时器
   /* QTimer *QButaMover=new QTimer(this);
    //QButaMover = new QTimer(this);   //新建定时器
        if(QButaMover==NULL)
         {
        qDebug()<<"fail timer!";
        }
        else{
        connect(QButaMover,SIGNAL(timeout()),this,SLOT(on_MoveButa()));//关联定时器计满信号和相应的槽函数
       //每隔1ms执行xytimerUpDate()函数
       qDebug()<<"This";
       QButaMover->setInterval(1000);
       QButaMover->start();
       qsrand(time(NULL));
    }
    */
    sciencemap[0][0]=1;sciencemap[1][0]=1;
    qsrand(time(NULL));
    ui->QBtnUnlockPigHome->setVisible(false);
    ui->QGoldWidget->hide();
    ui->QBirthPigMenuFrame->hide();
    ui->QTopUpMenuList->hide();
    ui->QFocus->hide();
    ui->Qshopframe->hide();
    ui->QoptionFrame->hide();
    ui->QFdata->hide();
    ui->QFsell->hide();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_Qbtngameexit_clicked()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, "豚の夢","您确定要退出游戏吗？",QMessageBox::Yes| QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            //canexit=0;
            QApplication* app;
            //QCoreApplication::exit();
            app->closeAllWindows();
        }
}

void MainWindow::on_reset_clicked()
{
    QMessageBox::StandardButton reply;
         reply = QMessageBox::critical(this, "豚の夢","重置存档讲使您失去之前的存档，确定继续吗？",QMessageBox::Yes| QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            QFile file("save.txt");
            if ( file.exists())
            {
                file.remove();
            }
        }
}

void MainWindow::on_loadgame_clicked()
{
    on_Qbtnloadthegame_clicked();
}

void MainWindow::setAllbutadisappear()
{
    ui->Buta1->setVisible(false);
    ui->Buta2->setVisible(false);
    ui->Buta3->setVisible(false);
    ui->Buta4->setVisible(false);
    ui->Buta5->setVisible(false);
    ui->Buta6->setVisible(false);
    ui->Buta7->setVisible(false);
    ui->Buta8->setVisible(false);
    ui->Buta9->setVisible(false);
    ui->Buta10->setVisible(false);
}
void MainWindow::   setAllbutaOn()
{
    ui->Buta1->setVisible(true);
    ui->Buta2->setVisible(true);
    ui->Buta3->setVisible(true);
    ui->Buta4->setVisible(true);
    ui->Buta5->setVisible(true);
    ui->Buta6->setVisible(true);
    ui->Buta7->setVisible(true);
    ui->Buta8->setVisible(true);
    ui->Buta9->setVisible(true);
    ui->Buta10->setVisible(true);
}
void MainWindow::on_Qbtngamestart_clicked()
{
    //创建某些文档
    QFile file("record.txt");
    if ( file.exists())
    {
        file.remove();
    }
    file.open( QIODevice::WriteOnly );
    file.close();


    ui->Qbtngamestart->setVisible(false);
    ui->Qbtngameexit->setVisible(false);
    ui->Qbtnloadgame->setVisible(false);
    ui->Qbtndeveloper->setVisible(false);
    currentmonth=1;
    currentpighome=1;
    maxlockpighome=1;
    pighomestoretype[1]=1;
    gold=1000;
    pig buta1={50.0,1,1,1};      //struct pig{    double w;int boughtyear,boughtday,type;};
    pigs[0].push_back(buta1);
    pigs[0].push_back(buta1);    //两个0
    showthishomepig(0);
    on_Qbtnpighome_clicked();
    setAllbutaOn();
    //on_MoveButa();
}
/*
void playtheMovie(QLabel *now,QMovie *bigpig,QMovie *bigpigr)
{
    //qDebug()<<"DID";
    int tx=now->geometry().x();
    if (tx<=10)
        tx=20;
    if (tx>=400)
        tx=390;
    int ty=now->geometry().y();
    if (ty<=100)
        ty=110;
    if (tx>=350)
        tx=340;
    //qDebug("%s:%d,%d",now->text(),tx,ty);
    int x=qrand()%11;
    x-=5;
    if (x>0)
        now->setMovie(bigpigr),bigpigr->start();
    else
        now->setMovie(bigpig),bigpig->start();
    now->move(tx+x,ty+x);
    //QEventLoop loop;
    //QTimer::singleShot(1000, &loop, SLOT(quit()));
    //loop.exec();
}
*/

void MainWindow::showthishomepig(int v)
{
    //QMovie *bigpig = new QMovie(":/new/buta/Resource/bigpigr.gif");
    //QMovie *blackpig = new QMovie(":/new/buta/Resource/blackpigr.gif");
    //QMovie *colouredpig = new QMovie(":/new/buta/Resource/colouredpigr.gif");
    int l=pigs[v].size();   //猪的数量
    qDebug()<<"WHY"<<l;
    if (l==1)
    {
        if (pigs[v][0].type==1)
           ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
           ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
           ui->Buta1->setMovie(blackpig),blackpig->start();
    }
    if (l==2)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
    }
    if (l==3)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
        if (pigs[v][2].type==1)
            ui->Buta3->setMovie(bigpig),bigpig->start();
        if (pigs[v][2].type==2)
            ui->Buta3->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][2].type==3)
            ui->Buta3->setMovie(blackpig),blackpig->start();
    }
    if (l==4)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
        if (pigs[v][2].type==1)
            ui->Buta3->setMovie(bigpig),bigpig->start();
        if (pigs[v][2].type==2)
            ui->Buta3->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][2].type==3)
            ui->Buta3->setMovie(blackpig),blackpig->start();
        if (pigs[v][3].type==1)
            ui->Buta4->setMovie(bigpig),bigpig->start();
        if (pigs[v][3].type==2)
            ui->Buta4->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][3].type==3)
            ui->Buta4->setMovie(blackpig),blackpig->start();
    }
    if (l==5)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
        if (pigs[v][2].type==1)
            ui->Buta3->setMovie(bigpig),bigpig->start();
        if (pigs[v][2].type==2)
            ui->Buta3->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][2].type==3)
            ui->Buta3->setMovie(blackpig),blackpig->start();
        if (pigs[v][3].type==1)
            ui->Buta4->setMovie(bigpig),bigpig->start();
        if (pigs[v][3].type==2)
            ui->Buta4->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][3].type==3)
            ui->Buta4->setMovie(blackpig),blackpig->start();
        if (pigs[v][4].type==1)
            ui->Buta5->setMovie(bigpig),bigpig->start();
        if (pigs[v][4].type==2)
            ui->Buta5->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][4].type==3)
            ui->Buta5->setMovie(blackpig),blackpig->start();
    }
    if (l==6)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
        if (pigs[v][2].type==1)
            ui->Buta3->setMovie(bigpig),bigpig->start();
        if (pigs[v][2].type==2)
            ui->Buta3->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][2].type==3)
            ui->Buta3->setMovie(blackpig),blackpig->start();
        if (pigs[v][3].type==1)
            ui->Buta4->setMovie(bigpig),bigpig->start();
        if (pigs[v][3].type==2)
            ui->Buta4->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][3].type==3)
            ui->Buta4->setMovie(blackpig),blackpig->start();
        if (pigs[v][4].type==1)
            ui->Buta5->setMovie(bigpig),bigpig->start();
        if (pigs[v][4].type==2)
            ui->Buta5->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][4].type==3)
            ui->Buta5->setMovie(blackpig),blackpig->start();
        if (pigs[v][5].type==1)
            ui->Buta6->setMovie(bigpig),bigpig->start();
        if (pigs[v][5].type==2)
            ui->Buta6->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][5].type==3)
            ui->Buta6->setMovie(blackpig),blackpig->start();
    }
    if (l==7)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
        if (pigs[v][2].type==1)
            ui->Buta3->setMovie(bigpig),bigpig->start();
        if (pigs[v][2].type==2)
            ui->Buta3->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][2].type==3)
            ui->Buta3->setMovie(blackpig),blackpig->start();
        if (pigs[v][3].type==1)
            ui->Buta4->setMovie(bigpig),bigpig->start();
        if (pigs[v][3].type==2)
            ui->Buta4->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][3].type==3)
            ui->Buta4->setMovie(blackpig),blackpig->start();
        if (pigs[v][4].type==1)
            ui->Buta5->setMovie(bigpig),bigpig->start();
        if (pigs[v][4].type==2)
            ui->Buta5->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][4].type==3)
            ui->Buta5->setMovie(blackpig),blackpig->start();
        if (pigs[v][5].type==1)
            ui->Buta6->setMovie(bigpig),bigpig->start();
        if (pigs[v][5].type==2)
            ui->Buta6->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][5].type==3)
            ui->Buta6->setMovie(blackpig),blackpig->start();
        if (pigs[v][6].type==1)
            ui->Buta7->setMovie(bigpig),bigpig->start();
        if (pigs[v][6].type==2)
            ui->Buta7->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][6].type==3)
            ui->Buta7->setMovie(blackpig),blackpig->start();
    }
    if (l==8)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
        if (pigs[v][2].type==1)
            ui->Buta3->setMovie(bigpig),bigpig->start();
        if (pigs[v][2].type==2)
            ui->Buta3->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][2].type==3)
            ui->Buta3->setMovie(blackpig),blackpig->start();
        if (pigs[v][3].type==1)
            ui->Buta4->setMovie(bigpig),bigpig->start();
        if (pigs[v][3].type==2)
            ui->Buta4->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][3].type==3)
            ui->Buta4->setMovie(blackpig),blackpig->start();
        if (pigs[v][4].type==1)
            ui->Buta5->setMovie(bigpig),bigpig->start();
        if (pigs[v][4].type==2)
            ui->Buta5->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][4].type==3)
            ui->Buta5->setMovie(blackpig),blackpig->start();
        if (pigs[v][5].type==1)
            ui->Buta6->setMovie(bigpig),bigpig->start();
        if (pigs[v][5].type==2)
            ui->Buta6->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][5].type==3)
            ui->Buta6->setMovie(blackpig),blackpig->start();
        if (pigs[v][6].type==1)
            ui->Buta7->setMovie(bigpig),bigpig->start();
        if (pigs[v][6].type==2)
            ui->Buta7->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][6].type==3)
            ui->Buta7->setMovie(blackpig),blackpig->start();
        if (pigs[v][7].type==1)
            ui->Buta8->setMovie(bigpig),bigpig->start();
        if (pigs[v][7].type==2)
            ui->Buta8->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][7].type==3)
            ui->Buta8->setMovie(blackpig),blackpig->start();
    }
    if (l==9)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
        if (pigs[v][2].type==1)
            ui->Buta3->setMovie(bigpig),bigpig->start();
        if (pigs[v][2].type==2)
            ui->Buta3->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][2].type==3)
            ui->Buta3->setMovie(blackpig),blackpig->start();
        if (pigs[v][3].type==1)
            ui->Buta4->setMovie(bigpig),bigpig->start();
        if (pigs[v][3].type==2)
            ui->Buta4->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][3].type==3)
            ui->Buta4->setMovie(blackpig),blackpig->start();
        if (pigs[v][4].type==1)
            ui->Buta5->setMovie(bigpig),bigpig->start();
        if (pigs[v][4].type==2)
            ui->Buta5->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][4].type==3)
            ui->Buta5->setMovie(blackpig),blackpig->start();
        if (pigs[v][5].type==1)
            ui->Buta6->setMovie(bigpig),bigpig->start();
        if (pigs[v][5].type==2)
            ui->Buta6->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][5].type==3)
            ui->Buta6->setMovie(blackpig),blackpig->start();
        if (pigs[v][6].type==1)
            ui->Buta7->setMovie(bigpig),bigpig->start();
        if (pigs[v][6].type==2)
            ui->Buta7->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][6].type==3)
            ui->Buta7->setMovie(blackpig),blackpig->start();
        if (pigs[v][7].type==1)
            ui->Buta8->setMovie(bigpig),bigpig->start();
        if (pigs[v][7].type==2)
            ui->Buta8->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][7].type==3)
            ui->Buta8->setMovie(blackpig),blackpig->start();
        if (pigs[v][8].type==1)
            ui->Buta9->setMovie(bigpig),bigpig->start();
        if (pigs[v][8].type==2)
            ui->Buta9->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][8].type==3)
            ui->Buta9->setMovie(blackpig),blackpig->start();
    }
    if (l==10)
    {
        if (pigs[v][0].type==1)
            ui->Buta1->setMovie(bigpig),bigpig->start();
        if (pigs[v][0].type==2)
            ui->Buta1->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][0].type==3)
            ui->Buta1->setMovie(blackpig),blackpig->start();
        if (pigs[v][1].type==1)
            ui->Buta2->setMovie(bigpig),bigpig->start();
        if (pigs[v][1].type==2)
            ui->Buta2->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][1].type==3)
            ui->Buta2->setMovie(blackpig),blackpig->start();
        if (pigs[v][2].type==1)
            ui->Buta3->setMovie(bigpig),bigpig->start();
        if (pigs[v][2].type==2)
            ui->Buta3->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][2].type==3)
            ui->Buta3->setMovie(blackpig),blackpig->start();
        if (pigs[v][3].type==1)
            ui->Buta4->setMovie(bigpig),bigpig->start();
        if (pigs[v][3].type==2)
            ui->Buta4->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][3].type==3)
            ui->Buta4->setMovie(blackpig),blackpig->start();
        if (pigs[v][4].type==1)
            ui->Buta5->setMovie(bigpig),bigpig->start();
        if (pigs[v][4].type==2)
            ui->Buta5->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][4].type==3)
            ui->Buta5->setMovie(blackpig),blackpig->start();
        if (pigs[v][5].type==1)
            ui->Buta6->setMovie(bigpig),bigpig->start();
        if (pigs[v][5].type==2)
            ui->Buta6->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][5].type==3)
            ui->Buta6->setMovie(blackpig),blackpig->start();
        if (pigs[v][6].type==1)
            ui->Buta7->setMovie(bigpig),bigpig->start();
        if (pigs[v][6].type==2)
            ui->Buta7->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][6].type==3)
            ui->Buta7->setMovie(blackpig),blackpig->start();
        if (pigs[v][7].type==1)
            ui->Buta8->setMovie(bigpig),bigpig->start();
        if (pigs[v][7].type==2)
            ui->Buta8->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][7].type==3)
            ui->Buta8->setMovie(blackpig),blackpig->start();
        if (pigs[v][8].type==1)
            ui->Buta9->setMovie(bigpig),bigpig->start();
        if (pigs[v][8].type==2)
            ui->Buta9->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][8].type==3)
            ui->Buta9->setMovie(blackpig),blackpig->start();
        if (pigs[v][9].type==1)
            ui->Buta10->setMovie(bigpig),bigpig->start();
        if (pigs[v][9].type==2)
            ui->Buta10->setMovie(colouredpig),colouredpig->start();
        if (pigs[v][9].type==3)
            ui->Buta10->setMovie(blackpig),blackpig->start();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    scx=0;
    scy=1;
    ui->QFocusName->setText("进攻月球");
    ui->QFocusEffect->setText("我们的猪们的数量将要进攻月球<br/>增加猪的成长速度50%");
    ui->QFoucusCost->setText("1000");
}

void MainWindow::on_pushButton_4_clicked()
{
    scx=1;
    scy=1;
    ui->QFocusName->setText("精英计划");
    ui->QFocusEffect->setText("我们的猪，不应该是普通的肉猪<br/>他们更多时候应该是一件美丽的艺术品<br/>增加猪的销售金额20%");
    ui->QFoucusCost->setText("1000");
}

void MainWindow::on_pushButton_6_clicked()
{
    scx=1;
    scy=2;
    ui->QFocusName->setText("优质牧草");
    ui->QFocusEffect->setText("不是所有的猪都叫特伦猪<br/>优质的牧草，优质的肉感<br/>增加猪的销售金额20%增加需求量100%");
    ui->QFoucusCost->setText("2000");
}

void MainWindow::on_pushButton_9_clicked()
{
    scx=1;
    scy=3;
    ui->QFocusName->setText("锻炼计划");
    ui->QFocusEffect->setText("强健的体魄不仅<br/>能使女性着迷，还能<br/>使得肉感更加浓郁<br/>增加猪的销售金额20%");
    ui->QFoucusCost->setText("3000");
}

void MainWindow::on_pushButton_11_clicked()
{
    scx=1;
    scy=4;
    ui->QFocusName->setText("医疗覆盖");
    ui->QFocusEffect->setText("损失一头优质的猪<br/>是绝对不能接受的<br/>整个猪场医疗设备<br/>完全覆盖<br/>增加猪的销售金额20%");
    ui->QFoucusCost->setText("4000");
}

void MainWindow::on_pushButton_7_clicked()
{
    scx=1;
    scy=5;
    ui->QFocusName->setText("优生优育");
    ui->QFocusEffect->setText("我们的猪打一诞生下来<br/>就有着成功的基因<br/>增加猪的销售金额20%");
    ui->QFoucusCost->setText("5000");
}

void MainWindow::on_pushButton_10_clicked()
{
    scx=1;
    scy=6;
    ui->QFocusName->setText("交配自由");
    ui->QFocusEffect->setText("窈窕淑女，君子好逑<br/>猪也有自己喜欢的对象<br/>野蛮的迫使他们交配毫无人道<br/>勇敢的去爱吧，繁衍更棒的基因<br/>增加猪的销售金额40%");
    ui->QFoucusCost->setText("6000");
}

void MainWindow::on_pushButton_8_clicked()
{
    scx=1;
    scy=7;
    ui->QFocusName->setText("猪权宣言");
    ui->QFocusEffect->setText("我们理应赋予猪们更多的权利<br/>它们的宿命真的是被吃掉吗<br/>或许在他们被吃掉之前<br/>他们也有权利去实现猪生目标<br/>增加猪的销售金额40%");
    ui->QFoucusCost->setText("7000");
}

void MainWindow::on_pushButton_12_clicked()
{
    scx=1;
    scy=8;
    ui->QFocusName->setText("猪群解放");
    ui->QFocusEffect->setText("美丽的华丽的艺术品们<br/>在消逝之前<br/>为诗和远方努力的拼搏吧<br/>记住，你们不是肉猪！<br/>增加猪的销售金额40%");
    ui->QFoucusCost->setText("8000");
}

void MainWindow::on_pushButton_13_clicked()
{
    scx=1;
    scy=9;
    ui->QFocusName->setText("猪球崛起");
    ui->QFocusEffect->setText("欢声笑语遍布了这颗星球<br/>宿命什么的随它去吧<br/>心中的梦想和价值<br/>才是真正的真理<br/>红尘如梦，如此即可<br/>增加猪的销售金额40%");
    ui->QFoucusCost->setText("9000");
}

void MainWindow::on_pushButton_14_clicked()
{
    scx=1;
    scy=10;
    ui->QFocusName->setText("天猪合一");
    ui->QFocusEffect->setText("道可道非常道名可名非常名<br/>我们曾经来过亦或者走过<br/>沧海桑田，改不了的是<br/>苍穹之蓝，洪荒之妙<br/>回归大道，归根复命<br/>世界的真理，就是如此<br/>增加猪的销售金额50%");
    ui->QFoucusCost->setText("10000");
}

void MainWindow::on_Qbtnscience_clicked()   // 焦点开关
{
    if (ui->QFocus->isVisible())
        ui->QFocus->hide();
    else
          ui->QFocus->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->QFocus->hide();
}

void MainWindow::on_pushButton_16_clicked()
{
    scx=0;
    scy=2;

    ui->QFocusName->setText("饲料操作");
    ui->QFocusEffect->setText("特定的饲料能使我们的猪们成长更快<br/>增加猪的成长速度50%");
    ui->QFoucusCost->setText("2000");
}

void MainWindow::on_pushButton_5_clicked()
{
    scx=0;
    scy=3;
    ui->QFocusName->setText("提倡繁殖");
    ui->QFocusEffect->setText("通过繁殖我们甚至能够无需购置新猪<br/>增加猪的成长速度50%");
    ui->QFoucusCost->setText("3000");
}

void MainWindow::on_pushButton_15_clicked()
{
    scx=0;
    scy=4;
    ui->QFocusName->setText("饲料操作");
    ui->QFocusEffect->setText("一套成功的流水线规划了猪的一生<br/>这套计划合乎科学，带来更多收益<br/>增加猪的成长速度50%");
    ui->QFoucusCost->setText("4000");
}

void MainWindow::on_pushButton_17_clicked()
{
    scx=0;
    scy=5;
    ui->QFocusName->setText("肉猪计划");
    ui->QFocusEffect->setText("我们决定我们的猪将会是肉猪<br/>我们需要把我们的猪供应到全世界<br/>增加猪的成长速度50%<br/>增加需求量100%");
    ui->QFoucusCost->setText("5000");
}

void MainWindow::on_pushButton_18_clicked()
{
    scx=0;
    scy=6;
    ui->QFocusName->setText("扩大需求");
    ui->QFocusEffect->setText("和世界强大的餐饮企业合作<br/>把我们的猪们全部卖给他们！<br/>形成一条巨大的产业链！<br/>增加需求量200%");
    ui->QFoucusCost->setText("6000");
}

void MainWindow::on_pushButton_19_clicked()
{
    scx=0;
    scy=7;
    ui->QFocusName->setText("基因工程");
    ui->QFocusEffect->setText("通过安全合理的修改基因<br/>让我们的肉猪们变得更加像肉猪<br/>增加猪的成长速度100%");
    ui->QFoucusCost->setText("7000");
}

void MainWindow::on_pushButton_20_clicked()
{
    scx=0;
    scy=8;
    ui->QFocusName->setText("科技革命");
    ui->QFocusEffect->setText("科技使社会进步<br/>也使我们的养猪模式变得更加科学<br/>一场真正的革新将要来临！<br/>增加猪的成长速度50%<br/>增加猪的销售金额10%");
    ui->QFoucusCost->setText("8000");
}

void MainWindow::on_pushButton_21_clicked()
{
    scx=0;
    scy=9;
    ui->QFocusName->setText("完全自动");
    ui->QFocusEffect->setText("流水线生产的集大成产物<br/>毫无人工干涉<br/>在机械声中度完作为一只被吃东西的一生<br/>增加猪的成长速度200%");
    ui->QFoucusCost->setText("9000");
}

void MainWindow::on_pushButton_22_clicked()
{
    scx=0;
    scy=10;
    ui->QFocusName->setText("宰割流水");
    ui->QFocusEffect->setText("这里是什么？养猪场？<br/>不不，这里是它们的坟墓，它们的胚胎<br/>金钱的漩涡，智慧的结晶<br/>增加猪的成长速度300%<br/>增加需求量400%");
    ui->QFoucusCost->setText("10000");
}
void MainWindow::chgthishometypetxt()
{
    //qDebug("%d %d",currentpighome,pighomestoretype[currentpighome]);
    if (pighomestoretype[currentpighome]==2)
        ui->QCurrentPigHometp->setText("黑猪");
    if (pighomestoretype[currentpighome]==1)
        ui->QCurrentPigHometp->setText("混合型");
    if (pighomestoretype[currentpighome]==0)
        ui->QCurrentPigHometp->setText("未设定");
}


void MainWindow::on_Qbtnpighome_clicked()  //点击猪圈
{

    ui->QGoldWidget->show();
    ui->QBirthPigMenuFrame->show();
    ui->QTopUpMenuList->show();
    QString temp,temp2;
    temp=QString::number(gold,10);
    ui->QGold->setText(temp);
    temp=QString::number(currentmonth,10);
    ui->QCurrentTime->setText(temp);
    ui->QTmaxtrade->setText(QString::number(maxpigcansell,10));
    int sum=0;
    for (int i=0;i<maxlockpighome;i++)
    {
        sum+=pigs[i].size();
    }
    temp=QString::number(sum,10);
    int inttemp=maxlockpighome*10;
    temp2=QString::number(inttemp,10);
    temp=temp+"/"+temp2;
    ui->QMon->setText(temp);
    chgthishometypetxt();
}
void MainWindow::resetpigmov() //正确显示猪圈
{
    chgthishometypetxt();
    ui->QBtnUnlockPigHome->setVisible(false);
    bigpig->stop();
    blackpig->stop();
    colouredpig->stop();
    ui->Buta1->setMovie(nullmovie);
    ui->Buta2->setMovie(nullmovie);
    ui->Buta3->setMovie(nullmovie);
    ui->Buta4->setMovie(nullmovie);
    ui->Buta5->setMovie(nullmovie);
    ui->Buta6->setMovie(nullmovie);
    ui->Buta7->setMovie(nullmovie);
    ui->Buta8->setMovie(nullmovie);
    ui->Buta9->setMovie(nullmovie);
    ui->Buta10->setMovie(nullmovie);
    showthishomepig(currentpighome-1);
    QString temp,temp2="/100";
    temp=QString::number(currentpighome,10);
    temp+=temp2;
    ui->Qcurrentpighome->setText(temp);
    if (currentpighome>maxlockpighome)
        ui->QBtnUnlockPigHome->setVisible(true);
}

void MainWindow::on_QBtnPigDown_clicked()
{
    currentpighome++;
    if (currentpighome==101)currentpighome=1;
    resetpigmov();
    on_Datashow();
}

void MainWindow::on_QbtnPigup_clicked()
{
    currentpighome--;
    if (currentpighome==0)currentpighome=100;
    resetpigmov();
    on_Datashow();
}

void MainWindow::on_QBtnPigQuickUp_clicked()
{
    currentpighome-=10;
    if (currentpighome<=0)currentpighome=100;
    resetpigmov();
    on_Datashow();
}

void MainWindow::on_QBtnPigQuickDown_clicked()
{
    currentpighome+=10;
    if (currentpighome>=101)currentpighome=1;
    resetpigmov();
    on_Datashow();
}

void MainWindow::on_QBtnUnlockPigHome_clicked()
{
    if (gold<1000)
        QMessageBox::about(NULL, "豚の夢", "您没有足够金币");
    else if (currentpighome>maxlockpighome+1)
        QMessageBox::about(NULL, "豚の夢", "请按照顺序解锁");
    else
    {
        gold-=1000;
        maxlockpighome++;
        resetpigmov();
        QString temp,temp2;
        temp=QString::number(gold,10);
        ui->QGold->setText(temp);
        temp=QString::number(currentmonth,10);
        ui->QCurrentTime->setText(temp);
        int sum=0;
        for (int i=0;i<currentpighome;i++)
        {
            sum+=pigs[i].size();
        }
        temp=QString::number(sum,10);
        int inttemp=currentpighome*10;
        temp2=QString::number(inttemp,10);
        temp=temp+"/"+temp2;
        ui->QMon->setText(temp);
    }
}

void MainWindow::on_QBtnCBigpig_clicked()
{
    pighomestoretype[currentpighome]=1;
    chgthishometypetxt();
}

void MainWindow::on_QBtnCColouredPig_clicked()
{
    pighomestoretype[currentpighome]=2;
    chgthishometypetxt();
}

void MainWindow::on_QBtnCBlackPig_clicked()
{
    bool flag=true;
    for (int i=0;i<pigs[currentpighome-1].size();i++)
        if (pigs[currentpighome-1][i].type!=3)
       {
            flag=false;break;
        }
    if (flag)pighomestoretype[currentpighome]=2;
    else QMessageBox::about(NULL, "豚の夢", "该猪圈中有其他猪，您无法设置");
    chgthishometypetxt();
}

void MainWindow::on_QBtnPigCNULL_clicked()
{
    bool flag=true;
    for (int i=0;i<pigs[currentpighome-1].size();i++)
        if (pigs[currentpighome-1][i].type==3)
       {
            flag=false;break;
        }
    if (flag)pighomestoretype[currentpighome]=1;
    else QMessageBox::about(NULL, "豚の夢", "该猪圈中有黑猪，您无法设置");
    chgthishometypetxt();
}

void MainWindow::on_Qbtnshop_clicked()
{
    if (ui->Qshopframe->isVisible())
    {
        ui->Qspin1->setValue(0);
        ui->Qspin2->setValue(0);
        ui->Qspin3->setValue(0);
        ui->QTallcost->setText("总花费");
        ui->Qshopframe->hide();
    }
    else
          ui->Qshopframe->show();
}

void MainWindow::on_pushButton_23_clicked()
{
    ui->Qspin1->setValue(0);
    ui->Qspin2->setValue(0);
    ui->Qspin3->setValue(0);
    ui->QTallcost->setText("总花费");
    ui->Qshopframe->hide();
}


void MainWindow::on_Qspin1_valueChanged(int arg1)
{
    int a=ui->Qspin2->value()*210;
    int b=ui->Qspin3->value()*450;
    int sum=arg1*180+a+b;
    QString temp=QString::number(sum,10);
    temp="总花费："+temp;
    ui->QTallcost->setText(temp);
}

void MainWindow::on_Qspin2_valueChanged(int arg1)
{
    int a=ui->Qspin1->value()*180;
    int b=ui->Qspin3->value()*450;
    int sum=arg1*210+a+b;
    QString temp=QString::number(sum,10);
    temp="总花费："+temp;
    ui->QTallcost->setText(temp);
}


void MainWindow::on_Qspin3_valueChanged(int arg1)
{
    int a=ui->Qspin1->value()*180;
    int b=ui->Qspin2->value()*210;
    int sum=arg1*450+a+b;
    QString temp=QString::number(sum,10);
    temp="总花费："+temp;
    ui->QTallcost->setText(temp);
}

void MainWindow::on_QBtnShopAplly_clicked()
{
    int cost=ui->Qspin1->value()*180+ui->Qspin2->value()*210+ui->Qspin3->value()*450;
    if (cost>gold)
    {
         QMessageBox::about(NULL, "豚の夢", "金币不足");
         return;
    }
    //bool can=true;
    int a=ui->Qspin1->value(),b=ui->Qspin2->value(),c=ui->Qspin3->value(),x=0,y=0;
    for (int i=1;i<=maxlockpighome;i++)
    {
        switch (pighomestoretype[i]){
        case 0:break;
        case 1:x+=10-pigs[i-1].size();break;
        case 2:y+=10-pigs[i-1].size();break;
        }
    }
    if (a+b>x||c>y)
    {
         QMessageBox::about(NULL, "豚の夢", "猪圈无法放下这些猪");
         return;
    }
    //下面开始往猪圈里面装猪
    QFile data("record.txt");
    if (data.open(QFile::WriteOnly | QIODevice::Append|QIODevice::Text)) {
        QTextStream out(&data);
        out <<"In "<< currentmonth<<" month,you have bought "<<a<<" big white pigs "<<b<<" little coloured pigs "<<c<<" blackpigs\n";
    }
    data.close();
    for (int i=0;i<maxlockpighome;i++)
    {
        pig ww;
        ww.boughtday=currentmonth;
        ww.boughtyear=currentmonth;
        if (pighomestoretype[i+1]==1&&(a>=1||b>=1))
        {
            int l=10-pigs[i].size();
            while (l--)
            {
                int q=qrand()%21;  //0-20
                q+=30;  //20-50
                double d=q*1.0;
                ww.w=d;
                if (a>=1)
                {
                    ww.type=1;
                    pigs[i].push_back(ww);
                    a--;continue;
                }
                if (b>=1)
                {
                    ww.type=2;
                    pigs[i].push_back(ww);
                    b--;continue;
                }
            }
        }
        if (pighomestoretype[i+1]==2&&(c>=1))
        {
            int l=10-pigs[i].size();
            while (l--)
            {
                int q=qrand()%21;
                q+=30;
                double d=q*1.0;
                ww.w=d;
                if (c>=1)
                {
                    ww.type=3;
                    pigs[i].push_back(ww);
                    c--;continue;
                }
            }
        }
        if (a<=0&&b<=0&&c<=0)break;
    }
    qDebug()<<"DealSuccessflly";
    gold-=cost;
    on_Qbtnpighome_clicked();
    resetpigmov();
}


void MainWindow::on_Qbtnoption_clicked()
{
    if (ui->QoptionFrame->isVisible())
    {
        ui->QoptionFrame->hide();
    }
    else
          ui->QoptionFrame->show();
}

void MainWindow::on_pushButton_26_clicked()
{
    on_Qbtngameexit_clicked();
}

void MainWindow::on_pushButton_27_clicked()
{
    QString a=ui->Qcontroler->text();
    QString key1="greedisgood";
    if (a==key1)
    {
        gold+=2000;
    }
}
void MainWindow::on_Datashow()
{
    ui->QD1B->setText("");ui->QD1T->setText("");ui->QD1W->setText("");ui->QD2B->setText("");ui->QD2T->setText("");ui->QD2W->setText("");
    ui->QD3B->setText("");ui->QD3T->setText("");ui->QD3W->setText("");ui->QD4B->setText("");ui->QD4T->setText("");ui->QD4W->setText("");
    ui->QD5B->setText("");ui->QD5T->setText("");ui->QD5W->setText("");ui->QD6B->setText("");ui->QD6T->setText("");ui->QD6W->setText("");
    ui->QD7B->setText("");ui->QD7T->setText("");ui->QD7W->setText("");ui->QD8B->setText("");ui->QD8T->setText("");ui->QD8W->setText("");
    ui->QD9B->setText("");ui->QD9T->setText("");ui->QD9W->setText("");ui->QD10B->setText("");ui->QD10T->setText("");ui->QD10W->setText("");
    int l=pigs[currentpighome-1].size();
    QString temp;
    if (l>=1)
    {
        temp=QString::number(pigs[currentpighome-1][0].boughtday, 10);ui->QD1B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][0].w, 10,2);ui->QD1W->setText(temp);
        if (pigs[currentpighome-1][0].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][0].type==2)temp="小花猪";
        if (pigs[currentpighome-1][0].type==3)temp="黑猪";
        ui->QD1T->setText(temp);
    }
    if (l>=2)
    {
        temp=QString::number(pigs[currentpighome-1][1].boughtday, 10);ui->QD2B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][1].w, 10,2);ui->QD2W->setText(temp);
        if (pigs[currentpighome-1][1].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][1].type==2)temp="小花猪";
        if (pigs[currentpighome-1][1].type==3)temp="黑猪";
        ui->QD2T->setText(temp);
    }
    if (l>=3)
    {
        temp=QString::number(pigs[currentpighome-1][2].boughtday, 10);ui->QD3B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][2].w, 10,2);ui->QD3W->setText(temp);
        if (pigs[currentpighome-1][2].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][2].type==2)temp="小花猪";
        if (pigs[currentpighome-1][2].type==3)temp="黑猪";
        ui->QD3T->setText(temp);
    }
    if (l>=4)
    {
        temp=QString::number(pigs[currentpighome-1][3].boughtday, 10);ui->QD4B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][3].w, 10,2);ui->QD4W->setText(temp);
        if (pigs[currentpighome-1][3].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][3].type==2)temp="小花猪";
        if (pigs[currentpighome-1][3].type==3)temp="黑猪";
        ui->QD4T->setText(temp);
    }
    if (l>=5)
    {
        temp=QString::number(pigs[currentpighome-1][4].boughtday, 10);ui->QD5B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][4].w, 10,2);ui->QD5W->setText(temp);
        if (pigs[currentpighome-1][4].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][4].type==2)temp="小花猪";
        if (pigs[currentpighome-1][4].type==3)temp="黑猪";
        ui->QD5T->setText(temp);
    }
    if (l>=6)
    {
        temp=QString::number(pigs[currentpighome-1][0].boughtday, 10);ui->QD6B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][0].w, 10,2);ui->QD6W->setText(temp);
        if (pigs[currentpighome-1][5].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][5].type==2)temp="小花猪";
        if (pigs[currentpighome-1][5].type==3)temp="黑猪";
        ui->QD6T->setText(temp);
    }
    if (l>=7)
    {
        temp=QString::number(pigs[currentpighome-1][6].boughtday, 10);ui->QD7B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][6].w, 10,2);ui->QD7W->setText(temp);
        if (pigs[currentpighome-1][6].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][6].type==2)temp="小花猪";
        if (pigs[currentpighome-1][6].type==3)temp="黑猪";
        ui->QD7T->setText(temp);
    }
    if (l>=8)
    {
        temp=QString::number(pigs[currentpighome-1][7].boughtday, 10);ui->QD8B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][7].w, 10,2);ui->QD8W->setText(temp);
        if (pigs[currentpighome-1][7].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][7].type==2)temp="小花猪";
        if (pigs[currentpighome-1][7].type==3)temp="黑猪";
        ui->QD8T->setText(temp);
    }
    if (l>=9)
    {
        temp=QString::number(pigs[currentpighome-1][8].boughtday, 10);ui->QD9B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][8].w, 10,2);ui->QD9W->setText(temp);
        if (pigs[currentpighome-1][8].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][8].type==2)temp="小花猪";
        if (pigs[currentpighome-1][8].type==3)temp="黑猪";
        ui->QD9T->setText(temp);
    }
    if (l>=10)
    {
        temp=QString::number(pigs[currentpighome-1][9].boughtday, 10);ui->QD10B->setText(temp);
        temp=QString::number(pigs[currentpighome-1][9].w, 10,2);ui->QD10W->setText(temp);
        if (pigs[currentpighome-1][9].type==1)temp="大花白猪";
        if (pigs[currentpighome-1][9].type==2)temp="小花猪";
        if (pigs[currentpighome-1][9].type==3)temp="黑猪";
        ui->QD10T->setText(temp);
    }
}

void MainWindow::on_Qbtndata_clicked()
{
    if (ui->QFdata->isVisible())
    {

        ui->QFdata->hide();
    }
    else
    {
        //qDebug()<<pigs[0][0].boughtday;
          ui->QFdata->show();
          on_Datashow();
    }
}

void MainWindow::on_pushButton_29_clicked()
{
    QString strPath = "record.txt";
    QDesktopServices bs;
    bs.openUrl(QUrl(strPath));
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->QFdata->hide();
}

void MainWindow::on_QBtnNexitMonth_clicked()
{
    currentmonth++;
    ui->QCurrentTime->setText(QString::number(currentmonth,10));
    for (int i=0;i<maxlockpighome;i++)
    {
        for (int j=0;j<pigs[i].size();j++)
        {
            int x=qrand()%13;   //x处于0-12
            x*=30;
            qDebug()<<"buffspeed"<<buffspeed<<endl;
            double t=1.0*buffspeed*x/1000;
            pigs[i][j].w+=t;
            //if (pigs[i][j].w>=150.0f)
            //pigs[i][j].w=150.0f;
        }
    }
    if ((currentmonth-1)%3==0)
    {
        ui->QFsell->show();
        int a=0,b=0,c=0;
        double w1=0.0f,w2=0.0f,w3=0.0f;
        for (int i=0;i<maxlockpighome;i++)
        {
           for (QVector<pig>::iterator it=pigs[i].begin();it!=pigs[i].end();)
           {
               if (currentmonth-it->boughtday>=12||it->w>=150.0f)
               {
                   if (it->type==1)
                   {
                       a++;
                       w1+=it->w;
                       it=pigs[i].erase(it);
                   }
                   if (it->type==2)
                   {
                       b++;
                       w2+=it->w;
                       it=pigs[i].erase(it);
                   }
                   if (it->type==3)
                   {
                       c++;
                       w3+=it->w;
                       it=pigs[i].erase(it);
                   }
               }
               else it++;
           }
        }
        ui->QTtp1a->setText(QString::number(a,10));
        ui->QTtp2a->setText(QString::number(b,10));
        ui->QTtp3a->setText(QString::number(c,10));
        ui->QTtp1w->setText(QString::number(w1,10,2));
        ui->QTtp2w->setText(QString::number(w2,10,2));
        ui->QTtp3w->setText(QString::number(w3,10,2));
        double p1=6*buffprice/100,p2=7*buffprice/100,p3=15*buffprice/100;
        ui->QTtp1p->setText(QString::number(p1,10,1));
        ui->QTtp2p->setText(QString::number(p2,10,1));
        ui->QTtp3p->setText(QString::number(p3,10,1));
        int c1=w1*p1,c2=w2*p2,c3=w3*p3;
        ui->QTtp1m->setText(QString::number(c1,10));
        ui->QTtp2m->setText(QString::number(c2,10));
        ui->QTtp3m->setText(QString::number(c3,10));
        int ssum=c1+c2+c3;
        ui->QTsellsum->setText(QString::number(ssum,10));
        /*if (w1+w2+w3>maxpigcansell)
        {
            ssum*=0.9;
        }*/
        QFile data("record.txt");
        if (data.open(QFile::WriteOnly | QIODevice::Append|QIODevice::Text)) {
            QTextStream out(&data);
            out <<"In "<< currentmonth<<" month,you sold "<<a<<" big white pigs "<<b<<" little coloured pigs "<<c<<" blackpigs and get "<<ssum<<" gold\n";
        }
        data.close();
        gold+=ssum;
        ui->QBtnNexitMonth->setEnabled(false);
        on_Qbtnpighome_clicked();
    }
    on_Datashow();
}

void MainWindow::on_pushButton_30_clicked()
{

   resetpigmov();
    ui->QBtnNexitMonth->setEnabled(true);
    ui->QFsell->hide();
}

void MainWindow::on_pushButton_24_clicked()
{
    QFile file("save.txt");
    if ( file.exists())
    {
        file.remove();
    }
    file.open( QIODevice::WriteOnly );
    file.close();
    if (file.open(QFile::WriteOnly | QIODevice::Append|QIODevice::Text)) {//存档系统
        QTextStream out(&file);
        out<<gold<<endl;
        out<<currentmonth<<endl;
        out<<maxlockpighome<<endl;
        out<<buffprice<<endl;
        out<<buffspeed<<endl;
        out<<maxpigcansell<<endl;
        for (int i=1;i<=100;i++)
            out<<pighomestoretype[i]<<endl;
        for (int i=0;i<=1;i++)
            for (int j=0;j<=11;j++)
                out<<sciencemap[i][j]<<endl;
        for (int i=0;i<maxlockpighome;i++)
        {
            out<<pigs[i].size()<<endl;
            int l=pigs[i].size();
            for (int j=0;j<l;j++)
                out<<pigs[i][j].boughtday<<endl<<pigs[i][j].boughtyear<<endl<<pigs[i][j].type<<endl<<pigs[i][j].w<<endl;
        }
    }
    file.close();
    QMessageBox::about(NULL, "豚の夢", "Save Completed.");
}

void MainWindow::on_Qbtnloadthegame_clicked()
{
    for (int i=0;i<maxlockpighome;i++)pigs[i].clear();
    QFile file("save.txt");
    QTextStream txtInput(&file);
    QString lineStr;
    int count=0,round=0,d=1,k=0,fs=0;
    pig temp;
    bool ok;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Open failed." << endl;
        return ;
    }
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        if (count==0)gold=lineStr.toInt();
        if (count==1)currentmonth=lineStr.toInt();
        if (count==2)maxlockpighome=lineStr.toInt();
        if (count==3)buffprice=lineStr.toInt();
        if (count==4)buffspeed=lineStr.toInt();
        if (count==5)maxpigcansell=lineStr.toInt();
        if (count>=6&&count<=105)
            pighomestoretype[d++]=lineStr.toInt();
        if (count>=106&&count<=127)
        {
            if (fs<=11)
                sciencemap[0][fs++]=lineStr.toInt();
            else
                sciencemap[1][(fs++)%12]=lineStr.toInt();
        }
        if (count>=128)
        {
            if (round==0)d=lineStr.toInt();//读入这个猪圈有几头猪
            if (round==1)temp.boughtday=lineStr.toInt();
            if (round==2)temp.boughtyear=lineStr.toInt();
            if (round==3)temp.type=lineStr.toInt();
            if (round==4){temp.w=lineStr.toDouble(&ok);
            pigs[k].push_back(temp);
            d--;round=0;
            if (d==0)
                k++,round=-1;
            }
            round++;
        }
        count++;
    }
    file.close();
    //qDebug("读取结束，持有金币%d,最大猪圈%d,第一猪圈的猪数%d",gold,maxlockpighome,pigs[0].size());
    ui->QoptionFrame->setVisible(false);
    ui->QFocus->setVisible(false);
    ui->QFdata->setVisible(false);
    ui->Qbtngamestart->setVisible(false);
    ui->Qbtngameexit->setVisible(false);
    ui->Qbtnloadgame->setVisible(false);
    ui->Qbtndeveloper->setVisible(false);
    currentpighome=1;
    showthishomepig(0);
    on_Qbtnpighome_clicked();
    setAllbutaOn();
}


void MainWindow::on_pushButton_2_clicked()
{
    int cost=scy*1000;
    if (sciencemap[scx][scy]==1)
    {
        QMessageBox::about(NULL, "豚の夢", "焦点已设置");
        return;
    }
    if (sciencemap[1-scx][1]==1)
    {
        QMessageBox::about(NULL, "豚の夢", "您已经点了不同的焦点线");
        return;
    }
    if (sciencemap[scx][scy-1]==0)
    {
        QMessageBox::about(NULL, "豚の夢", "前置焦点未设置");
        return;
    }
    if (gold<cost)
    {
        QMessageBox::about(NULL, "豚の夢", "金币不足");
        return;
    }
    gold-=cost;
    ui->QGold->setText(QString::number(gold,10));
    if (scx==0&&(scy==1||scy==2||scy==3||scy==4||scy==5||scy==8))
        buffspeed+=50;
    if (scx==0&&scy==8)
        buffprice+=10;
    if (scx==0&&scy==6)
        maxpigcansell*=3;
    if (scx==0&&scy==6)
        maxpigcansell*=2;
    if (scx==0&&scy==7)
        buffspeed+=100;
    if (scx==0&&scy==9)
        buffspeed+=200;
    if (scx==0&&scy==10)
        buffspeed+=300,maxpigcansell*=4;
    if (scx==1&&(scy==1||scy==3||scy==4||scy==5))
        buffprice+=20;
    if (scx==1&&scx==2)
        buffprice+=10,maxpigcansell*=2;
    if (scx==1&&(scy==6||scy==7||scy==8||scy==9))
        buffprice+=40;
    if (scx==1&&scy==10)
        buffprice+=50;
    sciencemap[scx][scy]=1;
    QMessageBox::about(NULL, "豚の夢", "焦点设置成功！");
    ui->QTmaxtrade->setText(QString::number(maxpigcansell,10));
}

void MainWindow::on_Qbtndeveloper_clicked()
{
    QMessageBox::about(NULL, "豚の夢", "作者:夏天，一切资源皆原创。游戏方法：点击下个月进入下个月，并增加猪的体重。每三个月系统会自动计算并出售一次。每个猪舍有一个模式，请选择养那种猪，买猪时猪会自动分配。设置焦点会得到BUFF加成。资料按键可以查询销售购买记录以及每头猪的体重。设置按键可以存档读档。括号内的为热键");
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    qDebug()<<index;
}
