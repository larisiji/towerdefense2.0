#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QAction>
#include<QObject>
#include<QPainter>
#include"mypushbutton.h"
#include<QPoint>
#include<QWidget>
#include"choosescene.h"
#include<QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置主场景
    //设置固定大小

        setFixedSize(1080,810);


        //设置图标
       setWindowIcon(QIcon(":/back/icon.jpg"));
        //设置标题
       setWindowTitle("Play with Doraemon");
       //退出按钮实现
       connect(ui->actionquit,&QAction::triggered,[=](){
           this->close();
       });//开始按钮
       mypushbutton * startBtn=new mypushbutton( ":/back/final.png");
       startBtn->setParent(this);
      startBtn->move((int)(this->width()*0.5-startBtn->width()*0.5),(int)(this->height()*0.35));

      //选择关卡
      choice=new choosescene;
      //自身隐藏
     connect(startBtn,&mypushbutton::clicked,[=](){
         startBtn->zoom1();
         startBtn->zoom2();
         QTimer::singleShot(500,this,[=](){
             this->hide();
          choice->show();
    });
         });


}
void MainWindow::paintEvent(QPaintEvent*){
        QPainter painter(this);
        QPixmap pic;
        pic.load(":/back/15.jpg");
        painter.drawPixmap(0,0,1080,810,pic);

}
MainWindow::~MainWindow()
{
    delete ui;
}

