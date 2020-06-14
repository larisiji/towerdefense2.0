#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"choosescene.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//重写绘图事件画图
    void paintEvent(QPaintEvent*);
    choosescene *choice=NULL;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
