#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QMovie>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Datashow();
    void chgthishometypetxt();
    void resetpigmov();
    void on_reset_clicked();
    void on_loadgame_clicked();
    void setAllbutadisappear();
    void on_Qbtngameexit_clicked();
    //void on_MoveButa(QLabel*,int tp);
    void setAllbutaOn();
    void showthishomepig(int);
    void on_Qbtngamestart_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_Qbtnscience_clicked();

    void on_pushButton_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_Qbtnpighome_clicked();

    void on_QBtnPigDown_clicked();

    void on_QbtnPigup_clicked();

    void on_QBtnPigQuickUp_clicked();

    void on_QBtnPigQuickDown_clicked();

    void on_QBtnUnlockPigHome_clicked();

    void on_QBtnCBigpig_clicked();

    void on_QBtnCColouredPig_clicked();

    void on_QBtnCBlackPig_clicked();

    void on_QBtnPigCNULL_clicked();

    void on_Qbtnshop_clicked();

    void on_pushButton_23_clicked();

    void on_Qspin1_valueChanged(int arg1);

    void on_Qspin2_valueChanged(int arg1);



    void on_Qspin3_valueChanged(int arg1);

    void on_QBtnShopAplly_clicked();

    void on_Qbtnoption_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_Qbtndata_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_28_clicked();

    void on_QBtnNexitMonth_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_24_clicked();

    void on_Qbtnloadthegame_clicked();


    void on_pushButton_2_clicked();

    void on_Qbtndeveloper_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    int canexit;
    QMovie *bigpig;
    QMovie *nullmovie;
    QMovie *blackpig;
    QMovie *colouredpig;
};

#endif // MAINWINDOW_H
