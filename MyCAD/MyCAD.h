#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyCAD.h"
#include "OdaCommon.h"
#include "MyService.h"

class MyCAD : public QMainWindow
{
    Q_OBJECT

public:
    MyCAD(QWidget *parent = nullptr);
    ~MyCAD();

    //Service template variable
    OdRxObjectImpl<MyService> svcs;
    
    //check ODA Service initialized or not
    bool initialize();

private:
    Ui::MyCADClass ui;
};
