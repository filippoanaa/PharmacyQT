#include "PrescriptionGUI.h"

void PrescriptionGUI::initGUI() {
	prescription.addObserver(this);
	QFormLayout* lyPrescription = new QFormLayout;
	setLayout(lyPrescription);

	lyPrescription->addRow("Name: ", nameMedPrescription);
	lyPrescription->addRow("Producer: ", producerMedPrescription);

	lyPrescription->addWidget(btnAddPrescription);

	lyPrescription->addRow(lblRandom, randomNo);
	lyPrescription->addWidget(btnAddRandomToPrescription);
	lyPrescription->addWidget(btnEmptyPrescription);
	lyPrescription->addRow(lblExport, editExport);
	lyPrescription->addWidget(btnExportPrescription);
	lyPrescription->addWidget(prescriptionList);

}

void PrescriptionGUI::loadPrescriptionData(const vector<Med> meds)
{
	prescriptionList->clear();
	for (const auto& elem : meds) {
		auto item = new QListWidgetItem(QString::fromStdString(
			elem.getName() + " " + elem.getProducer() + " " + std::to_string(elem.getPrice()) + " " + elem.getSubstance()));
		prescriptionList->addItem(item);
	}
}

void PrescriptionGUI::connect() {
	QObject::connect(btnAddPrescription, &QPushButton::clicked, [&]() {
		try {

			string name = nameMedPrescription->text().toStdString();
			string producer = producerMedPrescription->text().toStdString();

			if (name == "" || producer == "") {
				QMessageBox::warning(this, "Warning", "Enter a name and a producer");
				return;
			}
			srv.addToPrescription(name, producer);
			QMessageBox::information(this, "Info", "Med added to the prescription");
			loadPrescriptionData(srv.getAllPrescription());
			clearFields();
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
			clearFields();
		}
		});


	QObject::connect(btnAddRandomToPrescription, &QPushButton::clicked, [&]() {
		try {
			if (randomNo->text().isEmpty()) {
				QMessageBox::warning(this, "Warning", "Enter a number");
				return;
			}

			int nr = randomNo->text().toInt();
			srv.addRandomMedsToPrescription(nr);
			loadPrescriptionData(srv.getAllPrescription());
			QMessageBox::information(this, "Info", "Random meds added to the prescription");
			clearFields();
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
			clearFields();
		}
		});

	QObject::connect(btnEmptyPrescription, &QPushButton::clicked, [&]() {
		try {
			srv.emptyPrescription();
			loadPrescriptionData(srv.getAllPrescription());
			QMessageBox::information(this, "Info", "Prescription emptied");
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
		}
		});

	QObject::connect(btnExportPrescription, &QPushButton::clicked, [&]() {
		try {
			string file = editExport->text().toStdString();
			srv.exportPrescriptionToCSV(file);

			prescriptionList->clear();
			srv.emptyPrescription();

			QMessageBox::information(this, "Info", "Export done. Check the file " + QString::fromStdString(file) + ".txt");
			loadPrescriptionData(srv.getAllPrescription());
			
			clearFields();	
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
			clearFields();
		}
		});


}

void PrescriptionGUI::clearFields()
{
	nameMedPrescription->clear();
	producerMedPrescription->clear();
	randomNo->clear();
	editExport->clear();
}
