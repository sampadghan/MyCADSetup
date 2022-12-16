#include "MyCAD.h"
#include "OdaCommon.h"
#include "MyService.h"
#include "OdError.h"

MyCAD::MyCAD(QWidget *parent)
    : QMainWindow(parent)
{
    OdRxObjectImpl<MyService> svcs;
	odInitialize(&svcs);
    ui.setupUi(this);
}

MyCAD::~MyCAD()
{
    odUninitialize();
}
