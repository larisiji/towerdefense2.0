#include "mypushbutton.h"
#include<QPropertyAnimation>
mypushbutton::mypushbutton(QString normalImg,QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pic;
    pic.load(normalImg);
    //设置固定大小
    this->setFixedSize(pic.width()*0.3,pic.height()*0.3);
    //设置不规则图片形式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pic);
   this->setIconSize(QSize(pic.width()*0.3,pic.height()*0.3));
}
void mypushbutton::zoom1(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
   animation->setDuration(200);
   //start
   animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation->setEndValue((QRect(this->x(),this->y()+20,this->width(),this->height())));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}
void mypushbutton::zoom2(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
   animation->setDuration(200);
   //start
   animation->setStartValue(QRect(this->x(),this->y()+20,this->width(),this->height()));

    animation->setEndValue((QRect(this->x(),this->y(),this->width(),this->height())));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}
