#include "choosescene.h"
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include "scene1.h"
#include<QPoint>
#include"collision.h"
#include"scene1.h"
#include<QTimer>
#include"scene2.h"
#include<QSound>
choosescene::choosescene(QWidget *parent) : QMainWindow(parent)
{
//配置选择关卡场景
    QSound*startsound=new QSound ("qrc:/back/click.wav");
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

 //选择关卡
 scene1 *choice1=new scene1;
 scene2*choice2=new scene2;
 //自身隐藏
 //监听
 connect(choice1,&scene1::scene1Back,this,[=](){
     choice1->hide();
     this->show();
 });
 connect(choice2,&scene2::scene2Back,this,[=](){
     choice2->hide();
     this->show();
 });
connect(startBtn1,&mypushbutton::clicked,[=](){
    startsound->play();
    startBtn1->zoom1();
    startBtn1->zoom2();
    QTimer::singleShot(500,this,[=](){
        this->hide();
        choice1->show();
        choice1->start();
});

});
connect(startBtn2,&mypushbutton::clicked,[=](){
      startsound->play();
    startBtn2->zoom1();
    startBtn2->zoom2();
    QTimer::singleShot(500,this,[=](){
        this->hide();
        choice2->show();
        choice2->start();

});

});
//返回按钮
     mypushbutton*backBtn=new mypushbutton(":/back/backbtn2.png");
     backBtn->setParent(this);
     backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
     //点击返回
     connect(backBtn,&mypushbutton::clicked,[=](){
        backBtn->zoom1();
         backBtn->zoom2();
         QTimer::singleShot(500,this,[=](){
             emit this->choosesceneBack();
             //延时返回

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
