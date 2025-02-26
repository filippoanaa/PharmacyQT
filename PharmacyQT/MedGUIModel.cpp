#include "MedGUIModel.h"
#include"PrescriptionCRUD.h"
#include"PrescriptionReadOnlyGUI.h"
#include "PrescriptionGUI.h"
#include<string.h>
#include<set>
void MedGUIModel::initGUI()
{
	QHBoxLayout* mainLy = new QHBoxLayout;
	mainLy->addWidget(tblV);
	setLayout(mainLy);


	//arg medicamente
	auto formLy = new QFormLayout;
	formLy->addRow("Name", txtName);
	formLy->addRow("Producer", txtProducer);
	formLy->addRow("Price", txtPrice);
	formLy->addRow("Substance", txtSubstance);

	//butoane
	auto lyBtns = new QHBoxLayout;
	lyBtns->addWidget(btnAdd);
	lyBtns->addWidget(btnDelete);
	lyBtns->addWidget(btnModify);
	lyBtns->addWidget(btnUndo);
	lyBtns->addWidget(btnExit);


	//sortare
	auto layoutSort = new QVBoxLayout;
	groupBox->setLayout(layoutSort);
	layoutSort->addWidget(btnSortByName);
	layoutSort->addWidget(btnSortByproducer);
	layoutSort->addWidget(btnSortByPriceSubst);

	//filtrare
	auto layoutFilter = new QFormLayout;
	groupBoxFilter->setLayout(layoutFilter);
	layoutFilter->addRow(btnFilterByPrice, filterPrice);
	layoutFilter->addRow(btnFilterBySubst, filterSubstance);
	filterPrice->setPlaceholderText("Price");
	filterSubstance->setPlaceholderText("Substance");
	layoutFilter->addRow(btnReload);	

	auto lyBtnsPrescription = new QHBoxLayout;
	lyBtnsPrescription->addWidget(btnCrud);
	lyBtnsPrescription->addWidget(btnReadOnly);
	lyBtnsPrescription->addWidget(btnAddR);
	lyBtnsPrescription->addWidget(btnEmptyR);
	lyBtnsPrescription->addWidget(btnAddRandomR);


	auto layoutInput = new QVBoxLayout;
	layoutInput->addLayout(formLy);
	layoutInput->addLayout(lyBtns);
	layoutInput->addWidget(groupBox);
	layoutInput->addWidget(groupBoxFilter);
	layoutInput->addWidget(btnPrescription);
	layoutInput->addLayout(lyBtnsPrescription);
	mainLy->addLayout(layoutInput);

	btnsTypes->setLayout(layoutTypes);
	mainLy->addWidget(btnsTypes);
	mainLy->addLayout(layoutTypes);

	this->resize(1100, 500); 

}


void MedGUIModel::loadData(const vector<Med>& meds)
{
	tableModel->setMeds(meds);

	//typeButtons();
}

void MedGUIModel::loadPrescriptionData(const vector<Med> meds)
{
	prescriptionList->clear();

	for (const auto& elem : meds) {
		auto item = new QListWidgetItem(QString::fromStdString(
			elem.getName() + " " + elem.getProducer() + " " + std::to_string(elem.getPrice()) + " " + elem.getSubstance()));
		prescriptionList->addItem(item);
	}
}


void MedGUIModel::initConnect()
{
	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		QList<QWidget*> openWindows = QApplication::topLevelWidgets();
		for (QWidget* window : openWindows) {
			if (window != this) {
				window->close();
			}
		}
		this->close();	
		});


	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		auto name = txtName->text().toStdString();
		auto producer = txtProducer->text().toStdString();
		auto price = txtPrice->text().toDouble();
		auto substance = txtSubstance->text().toStdString();

		if (name == "" || producer == "" || price == 0 || substance == "") {
			QMessageBox::warning(nullptr, "Invalid data", "All fields are required!Please enter a name, producer, price and substance.");
			return;
		}

		try {
			srv.addMed(name, producer, price, substance);
			QMessageBox::information(nullptr, "Confirmation", "Med added successfully");
			loadData(srv.getAll());
			clearFields();
		}
		catch (ValidationException&) {
			QMessageBox::warning(nullptr, "Invalid data", "Invalid Med!");
			clearFields();
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
			clearFields();
		}
		});


	QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
		auto name = txtName->text();
		auto producer = txtProducer->text();

		if (name == "" || producer == "") {
			QMessageBox::warning(nullptr, "Invalid data", "Select a med from the list first");
			return;
		}

		try {
			srv.deleteMed(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData());
			QMessageBox::information(nullptr, "Confirmation", "Med deleted");
			loadData(srv.getAll());
			clearFields();
		}
		catch (ValidationException& validationException) {
			QMessageBox::warning(nullptr, "Invalid data", QString::fromStdString(validationException.getMessage()));
			clearFields();
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
			clearFields();
		}
		});

	QObject::connect(btnModify, &QPushButton::clicked, [&]() {
		auto name = txtName->text();
		auto producer = txtProducer->text();
		auto newPrice = txtPrice->text();
		auto newSubstance = txtSubstance->text();

		if (name == "" || producer == "" || newPrice == "" || newSubstance == "") {
			QMessageBox::warning(nullptr, "Invalid data", "Select the med you want to modify from the list.");
			return;
		}	

		try {
			srv.modifyMed(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData(), newPrice.toDouble(), newSubstance.toLocal8Bit().constData());
			QMessageBox::information(nullptr, "Confirmation", "Med modified");
			loadData(srv.getAll());
			clearFields();
		}
		catch (ValidationException& validationException) {
			QMessageBox::warning(nullptr, "Invalid data", QString::fromStdString(validationException.getMessage()));
			clearFields();
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
			clearFields();
		}
		});


	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			loadData(srv.getAll());
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
		}
		});


	QObject::connect(btnSortByName, &QPushButton::clicked, [&]() {
		try {
			auto allMeds = srv.sortMedsByName();
			if (allMeds.size() == 0)
				QMessageBox::information(nullptr, "Invalid data", "You need to add some meds first!");
			loadData(allMeds);
		}
		catch (const RepoException& e) {
			QMessageBox::critical(nullptr, "Error", e.what());
		}
		catch (const std::exception& e) {
			QMessageBox::critical(nullptr, "Error", e.what());
		}
		});


	QObject::connect(btnSortByproducer, &QPushButton::clicked, [&]() {
		auto allMeds = srv.sortMedsByProducer();
		if (allMeds.size() == 0)
			QMessageBox::information(nullptr, "Invalid data", "You need to add some meds first!");
		loadData(allMeds);
		});


	QObject::connect(btnSortByPriceSubst, &QPushButton::clicked, [&]() {
		auto allMeds = srv.sortMedsBySubstanceAndPrice();
		if (allMeds.size() == 0)
			QMessageBox::information(nullptr, "Invalid data", "You need to add some meds first!");
		loadData(allMeds);
		});


	QObject::connect(btnFilterByPrice, &QPushButton::clicked, [&]() {
		int price = filterPrice->text().toInt();
		auto filtered = srv.filterByPrice(price);
		loadData(filtered);
		clearFields();
		});


	QObject::connect(btnFilterBySubst, &QPushButton::clicked, [&]() {
		string subst = filterSubstance->text().toStdString();
		auto filtered = srv.filterBySubstance(subst);
		loadData(filtered);
		clearFields();
		});

	QObject::connect(btnReload, &QPushButton::clicked, [&]() {
		loadData(srv.getAll());
		});	


	QObject::connect(btnPrescription, &QPushButton::clicked, [&]() {
		PrescriptionGUI* prescription = new PrescriptionGUI{ srv, srv.getPrescription() };
		prescription->show();
		});


	QObject::connect(btnAddR, &QPushButton::clicked, [&]() {
		try {
			string name = txtName->text().toStdString();
			string producer = txtProducer->text().toStdString();
			if (name == "" || producer == "") {
				QMessageBox::warning(this, "Warning", "Select a med from the list first");
				return;
			}

			srv.addToPrescription(name, producer);
			QMessageBox::information(this, "Info", QString::fromStdString("Med added to the prescription"));
			clearFields();
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
		}
		});


	QObject::connect(btnEmptyR, &QPushButton::clicked, [&]() {
		try {
			srv.emptyPrescription();
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
		}
		});


	QObject::connect(btnAddRandomR, &QPushButton::clicked, [&]() {
		try {
			srv.addRandomMedsToPrescription(3);
		}
		catch (RepoException& repoException) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(repoException.getError()));
		}
		});


	QObject::connect(btnCrud, &QPushButton::clicked, [&] {
		auto windowPrescription = new PrescriptionCRUD(srv.getPrescription(), srv);
		windowPrescription->show();
		});


	QObject::connect(btnReadOnly, &QPushButton::clicked, [&]() {
		auto windowShapes = new PrescriptionReadOnlyGUI(srv.getPrescription());
		windowShapes->show();
		});


	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
			txtName->setText("");
			txtProducer->setText("");
			txtPrice->setText("");
			txtSubstance->setText("");
			return;
		}
		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();

		auto cel0Index = tblV->model()->index(selRow, 0);
		auto cel0Value = tblV->model()->data(cel0Index, Qt::DisplayRole).toString();
		txtName->setText(cel0Value);

		auto cel1Index = tblV->model()->index(selRow, 1);
		auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
		txtProducer->setText(cel1Value);

		auto cel2Index = tblV->model()->index(selRow, 2);
		auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
		txtPrice->setText(cel2Value);

		auto cel3Index = tblV->model()->index(selRow, 3);
		auto cel3Value = tblV->model()->data(cel3Index, Qt::DisplayRole).toString();
		txtSubstance->setText(cel3Value);

		});

}

void MedGUIModel::typeButtons()
{
	QLayoutItem* aux;
	while ((aux = layoutTypes->takeAt(0)) != nullptr) {
		if (QWidget* widget = aux->widget()) {
			delete widget;
		}
		delete aux;
	}

	vector<Med> allMeds = srv.getAll();
	std::set<string>uniqueSubstances;
	for (const auto& med : allMeds) {
		uniqueSubstances.insert(med.getSubstance());
	}
	map<string, int> raport = srv.raportSubstance();
	for (const auto& pair : raport) {
		QPushButton* btnSubst = new QPushButton(QString::fromStdString(pair.first));
		btnsTypes->layout()->addWidget(btnSubst);
		QObject::connect(btnSubst, &QPushButton::clicked, [=]() {
			QMessageBox::information(nullptr, "Info", QString("Numarul de produse pentru %1 este: %2").arg(QString::fromStdString(pair.first)).arg(pair.second));			});

	}

}

void MedGUIModel::clearFields()
{
	txtName->clear();
	txtProducer->clear();
	txtPrice->clear();
	txtSubstance->clear();
	filterPrice->clear();
	filterSubstance->clear();
}
