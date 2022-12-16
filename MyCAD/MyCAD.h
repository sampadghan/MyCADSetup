#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyCAD.h"

class MyCAD : public QMainWindow
{
    Q_OBJECT

public:
    MyCAD(QWidget *parent = nullptr);
    ~MyCAD();

private:
    Ui::MyCADClass ui;
};
