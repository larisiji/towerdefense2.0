#include "choosescene.h"
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include "scene1.h"
#include<QPoint>
choosescene::choosescene(QWidget *parent) : QMainWindow(parent)
{
//配置选择关卡场景
    this->setFixedSize(1080,810);
    this->setWindowIcon(QIcon(":/back/icon.jpg"));
    this->setWindowTitle("Play with Doraemon");
    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu=bar->addMenu("start");
    QAction * quitAction=startMenu->addAction("quit");

    //点击实现退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    mypushbutton * startBtn1=new mypushbutton( ":/back/1.png");
    startBtn1->setParent(this);
   startBtn1->move((int)(this->width()*0.445),(int)(this->height()*0.2));
   mypushbutton * startBtn2=new mypushbutton( ":/back/2.png");
   startBtn2->setParent(this);
  startBtn2->move((int)(this->width()*0.445),(int)(this->height()*0.4));
  mypushbutton * startBtn3=new mypushbutton( ":/back/3.png");
  startBtn3->setParent(this);
 startBtn3->move((int)(this->width()*0.445),(int)(this->height()*0.6));
 //选择关卡
 scene1 *choice1=new scene1;
 //自身隐藏

connect(startBtn1,&mypushbutton::clicked,[=](){
    startBtn1->zoom1();
    startBtn1->zoom2();
    QTimer::singleShot(500,this,[=](){
        this->hide();
        choice1->show();
});
});

}

void choosescene:: paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pic;
    pic.load(":/back/background3.0.jpg");
    painter.drawPixmap(0,0,1080,810,pic);
}
