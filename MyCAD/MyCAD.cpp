#include "MyCAD.h"
#include "OdaCommon.h"
#include "MyService.h"
#include "DbBaseHostAppServices.h"
#include "OdError.h"
#include "DbCircle.h"
#include "DbLine.h"
#include "DbBlockTable.h"
#include "DbBlockTableRecord.h"
#include <QMessageBox>

MyCAD::MyCAD(QWidget* parent)
	: QMainWindow(parent)
{
	OdRxObjectImpl<MyService> svcs;
	if (&svcs == NULL)
	{
		exit(1);
	}
	odInitialize(&svcs);
	try
	{
		OdDbDatabasePtr pDb;
		pDb = svcs.readFile("Drawing.dwg");
	}
	catch (OdError_FileException)
	{
		QMessageBox msgBox;
		msgBox.setText("OdError_FileException");
		msgBox.exec();
	}
	catch (OdError)
	{
		QMessageBox msgBox;
		msgBox.setText("OdError has occurred.");
		msgBox.exec();
	}
	ui.setupUi(this);
	//odUninitialize();
}

MyCAD::~MyCAD()
{
	odUninitialize();
}