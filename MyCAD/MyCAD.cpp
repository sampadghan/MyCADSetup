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
	OdDbDatabasePtr pDb = svcs.createDatabase(false);
	try
	{
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
	OdDbDatabasePtr pDb1;
	try
	{
		//creating a empty database
		pDb1 = svcs.createDatabase(true);
	}
	catch (OdError& error)
	{
		QMessageBox msgBox;
		msgBox.setText("Empty database not created");
		msgBox.exec();
	}
	//Open the Block Table
	OdDbBlockTablePtr pTable = pDb->getBlockTableId().safeOpenObject(OdDb::kForWrite);
	OdDbObjectId blockTableID = pDb->getBlockTableId();

	//Open the Block Table
	OdDbBlockTablePtr mypTable = pDb1->getBlockTableId().safeOpenObject(OdDb::kForWrite);
	OdDbObjectId myblockTableID = pDb1->getBlockTableId();

	//Open the Model Space block
	OdDbBlockTableRecordPtr pModelSpace = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

	//Open the Model Space block
	OdDbBlockTableRecordPtr mypModelSpace = pDb1->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

	OdDbLinePtr pLine = OdDbLine::createObject();
	//OdDbObjectId objId = pModelSpace->appendOdDbEntity(pLine);
	OdDbObjectId myobjId = mypModelSpace->appendOdDbEntity(pLine);
	pLine->setStartPoint(OdGePoint3d(2, 0, 0));
	pLine->setEndPoint(OdGePoint3d(4, 2, 0));
	pLine->setColorIndex(12);

	OdDbCirclePtr pCircle = OdDbCircle::createObject();
	mypModelSpace->appendOdDbEntity(pCircle);
	OdGePoint3d center = OdGePoint3d(2.0, 0, 0);
	pCircle->setCenter(center);
	pCircle->setRadius(2.0);

	//Saving the created database as a file
	pDb->writeFile("Drawing.dwg", OdDb::kDwg, OdDb::vAC24);
	pDb1->writeFile("MyDrawing.dwg", OdDb::kDwg, OdDb::vAC24);
	//Delete the Database instance
	pDb.release();
	pDb1.release();
	ui.setupUi(this);
	odUninitialize();
}

MyCAD::~MyCAD()
{
	//odUninitialize();
}