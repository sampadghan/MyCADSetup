#include "MyCAD.h"
#include <QtWidgets/QApplication>
//#include "OdaCommon.h"
//#include "MyService.h"

int main(int argc, char *argv[])
{
    //Initialize the service
    //OdRxObjectImpl<MyService> svcs;
    //Passing the service pointer to the odInitialize
    //odInitialize(&svcs);0
    QApplication a(argc, argv);
    MyCAD w;
    w.show();
    //odUninitialize();
    return a.exec();
    // Termination  of the service
}
