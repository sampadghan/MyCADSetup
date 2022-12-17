#include "MyCAD.h"
#include "OdaCommon.h"
#include "MyService.h"
#include "DbBaseHostAppServices.h"
#include "OdError.h"
#include "DbCircle.h"
#include "DbLine.h"
#include "DbBlockTable.h"
#include "DbBlockTableRecord.h"
#include "DbDatabase.h"
#include <QMessageBox>

MyCAD::MyCAD(QWidget* parent)
	: QMainWindow(parent)
{
	//Service template variable
	OdRxObjectImpl<MyService> svcs;
	if (&svcs == NULL)
	{
		exit(1);
	}
	//Initialize the Drawing explorer
	odInitialize(&svcs);
	//
	svcs.setRecomputeDimBlocksRequired(false);
	//To create an empty database
	OdDbDatabasePtr pDb = svcs.createDatabase(false);
	try
	{
		//populate it by reading an input file:
		pDb = svcs.readFile("Drawing.dwg");
	}
	catch (OdError_FileException)
	{
		QMessageBox msgBox;
		msgBox.setText("OdError_FileException");
		msgBox.exec();
	}
	catch (OdError& error)
	{
		QMessageBox msgBox;
		OdString myerror = error.description();
		msgBox.setText("OdError has occurred.");
		msgBox.exec();
	}
	OdDbDatabasePtr mypDb;
	try
	{
		//creating a empty database
		mypDb = svcs.createDatabase(true);
	}
	catch (OdError& error)
	{
		QMessageBox msgBox;
		msgBox.setText("Empty database not created");
		msgBox.exec();
	}
	//Open the Block Table
	OdDbBlockTablePtr pTable = mypDb->getBlockTableId().safeOpenObject(OdDb::kForWrite);
	OdDbObjectId blockTableID = mypDb->getBlockTableId();
	
	//Open the Model Space block
	OdDbBlockTableRecordPtr pModelSpace = mypDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

	//draw a circle on the model
	OdDbCirclePtr pCircle = OdDbCircle::createObject();
	pModelSpace->appendOdDbEntity(pCircle);
	OdGePoint3d center = OdGePoint3d(0.0, 0, 0);
	pCircle->setCenter(center);
	pCircle->setRadius(10.0);
	
	//draw the line on the model
	OdDbLinePtr pLine = OdDbLine::createObject();
	pModelSpace->appendOdDbEntity(pLine);
	pLine->setStartPoint(OdGePoint3d(0, 0, 0));
	pLine->setEndPoint(OdGePoint3d(50, 2, 0));

	//saving the file
	mypDb->writeFile("Drawing3.dwg", OdDb::kDwg, OdDb::vAC24);

	//release the pointer(otherwise it will give error)
	pDb.release();
	mypDb.release();
	//setup the ui
	ui.setupUi(this);
	//UnInitialize the service
	odUninitialize();
}

MyCAD::~MyCAD()
{
	//odUninitialize();
}