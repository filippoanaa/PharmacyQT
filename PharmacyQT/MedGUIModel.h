#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/qtabwidget.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qslider.h>
#include <qdebug.h>
#include <QtWidgets/qmessagebox.h>
#include <vector>
#include <string>
#include <QtWidgets/QTableWidget.>
#include<QStringList>
#include<QtWidgets/QGroupBox>
#include"TableModel.h"
#include "Service.h"

class MedGUIModel : public QWidget {

protected:
	MedsStore& srv;
	QListWidget* lst = new QListWidget;
	TableModel* tableModel;
	QListView* lstV = new QListView;
	QTableView* tblV = new QTableView;

	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnAdd = new QPushButton{ "&Add" };
	QPushButton* btnDelete = new QPushButton{ "&Delete" };
	QPushButton* btnModify = new QPushButton{ "&Modify" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };

	QLineEdit* txtName = new QLineEdit;
	QLineEdit* txtProducer = new QLineEdit;
	QLineEdit* txtPrice = new QLineEdit;
	QLineEdit* txtSubstance = new QLineEdit;

	QGroupBox* groupBox = new QGroupBox(QString::fromStdString("Sort options"));
	QPushButton* btnSortByName = new QPushButton(QString::fromStdString("By name"));
	QPushButton* btnSortByproducer = new QPushButton(QString::fromStdString("By producer"));
	QPushButton* btnSortByPriceSubst = new QPushButton(QString::fromStdString("By price+substance"));

	QGroupBox* groupBoxFilter = new QGroupBox(QString::fromStdString("Filter options"));
	QPushButton* btnFilterByPrice = new QPushButton(QString::fromStdString("By price"));
	QPushButton* btnFilterBySubst = new QPushButton(QString::fromStdString("By substance"));
	QPushButton* btnReload = new QPushButton(QString::fromStdString("Reload meds"));
	QLineEdit* filterPrice = new QLineEdit;
	QLineEdit* filterSubstance = new QLineEdit;

	//prescription
	QListWidget* prescriptionList = new QListWidget;
	QPushButton* btnPrescription = new QPushButton("Show prescription menu");


	QPushButton* btnCrud = new QPushButton{ "PrescriptionCRUDGUI" };
	QPushButton* btnReadOnly = new QPushButton{ "PrescriptionReadOnlyGUI" };
	QPushButton* btnAddR = new QPushButton{ "Add med to prescription" };
	QPushButton* btnEmptyR = new QPushButton{ "Empty prescription" };
	QPushButton* btnAddRandomR = new QPushButton{ "Add 3 random meds" };

	QPushButton* btnReloadData = new QPushButton("Reload data");
	QWidget* btnsTypes = new QWidget;
	QVBoxLayout* layoutTypes = new QVBoxLayout;

	void initGUI();
	void loadData(const vector<Med>& meds);
	void loadPrescriptionData(const vector<Med> meds);
	void initConnect();
	void typeButtons();
	void clearFields();

public:
	MedGUIModel(MedsStore& srv) :srv{ srv } {
		this->setWindowTitle("Meds Management");

		//initializez interfata grafica
		initGUI();

		tableModel = new TableModel{ srv.getAll() };
		tblV->setModel(tableModel);

		//conectare butoane
		initConnect();

		//typeButtons();

	}

};

