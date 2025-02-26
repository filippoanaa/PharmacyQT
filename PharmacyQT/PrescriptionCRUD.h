#pragma once
#include<QtWidgets/QWidget>
#include<QtWidgets/QHBoxLayout>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QListWidget>
#include "Observer.h"
#include <Prescription.h>

class PrescriptionCRUD :public QWidget, public Observer {
private:
	Prescription& prescription;
	MedsStore& srv;

	QListWidget* lst = new QListWidget;
	QPushButton* btnEmpty = new QPushButton("Empty prescription");
	QPushButton* btnRandom = new QPushButton("Generate 3 meds");

	void loadList(const std::vector<Med>& meds) {
		lst->clear();
		for (auto& m : meds) {
			auto item = new QListWidgetItem(QString::fromStdString(m.getName() + " " + m.getProducer() + " " + std::to_string(m.getPrice()) + m.getSubstance() + " "));
			lst->addItem(item);
		}
	}
	void initGUI() {
		QVBoxLayout* ly = new QVBoxLayout;
		setLayout(ly);
		ly->addWidget(lst);
		ly->addWidget(btnEmpty);
		ly->addWidget(btnRandom);

	}
	void connect() {
		prescription.addObserver(this);
		setWindowTitle("PrescriptionCRUD");

		QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
			prescription.emptyPrescription();
			loadList(prescription.getAllPrescription());
			});

		QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
			srv.addRandomMedsToPrescription(3);
			loadList(prescription.getAllPrescription());
			});

	}
public:
	PrescriptionCRUD(Prescription& prescription, MedsStore& srv) :prescription{ prescription }, srv{ srv } {
		initGUI();
		connect();
		loadList(prescription.getAllPrescription());
	}

	void update() override {
		loadList(prescription.getAllPrescription());
	}

	~PrescriptionCRUD() {
		prescription.removeObserver(this);
	}

};