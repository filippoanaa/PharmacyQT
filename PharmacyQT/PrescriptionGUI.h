#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qtoolbutton.h>
#include <QtWidgets/qspinbox.h>
#include <vector>
#include <string>
#include "Observer.h"
#include "Prescription.h"
#include "Service.h"

using namespace std;

class PrescriptionGUI : public QWidget, public Observer
{
private:
	MedsStore& srv;
	Prescription& prescription;

	void update() override
	{
		loadPrescriptionData(prescription.getAllPrescription());
	}

	QListWidget* prescriptionList = new QListWidget;
	QPushButton* btnAddPrescription = new QPushButton("Add med to the prescription");
	QLineEdit* nameMedPrescription = new QLineEdit;
	QLineEdit* producerMedPrescription = new QLineEdit;
	QPushButton* btnAddRandomToPrescription = new QPushButton("Add random meds");
	QLineEdit* randomNo = new QLineEdit;
	QPushButton* btnEmptyPrescription = new QPushButton("Empty prescription");
	QLineEdit* editExport = new QLineEdit;
	QPushButton* btnExportPrescription = new QPushButton("Export meds");
	QLabel* lblRandom = new QLabel{ "Number of random meds:" };
	QLabel* lblExport = new QLabel{ "File name:" };


	// initializeaza interfata grafica
	void initGUI();

	// incarca reteta in lista
	void loadPrescriptionData(const vector<Med> meds);

	// stabileste conexiunea dintre semnal si butoane
	void connect();

	void clearFields();


public:
	PrescriptionGUI(MedsStore& s, Prescription& prescription) :srv{ s }, prescription{ prescription }
	{
		this->setWindowTitle("Prescription Management");
		initGUI();
		loadPrescriptionData(prescription.getAllPrescription());
		connect();
	}
};