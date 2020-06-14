#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QString>
#include <QPushButton>
#include<Qpoint>
class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
   // explicit mypushbutton(QWidget *parent = nullptr);
mypushbutton(QString normalImg,QString pressImg="");
//成员属性 保存用户传入图片
QString normalImgPath;
QString pressImgPath;
signals:
//bounce
void zoom1();
void zoom2();
};

#endif // MYPUSHBUTTON_H
