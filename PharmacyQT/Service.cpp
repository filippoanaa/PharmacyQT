#include "Service.h"
#include<functional>
#include<cstring>
#include<fstream>
using std::make_unique;


const vector<Med>& MedsStore::getAll()
{
	return repo.getAll();
}

void MedsStore::addMed(const string& name, const string& producer, double price, const string& substance) {
	Med m{ name, producer, price, substance };
	validator.valideaza(m);
	repo.store(m);
	undoActions.push_back(make_unique<UndoAdd>(repo, m));

}

const Med& MedsStore::findMed(const string& name, const string& producer) {
	return repo.find(name, producer);
}


void MedsStore::deleteMed(const string& name, const string& producer) {
	Med m = repo.find(name, producer);
	repo.del(m);
	undoActions.push_back(make_unique<UndoDelete>(repo, m));
}

void MedsStore::modifyMed(const string& name, const string& producer, double newPrice, const string& newSubstance) {
	Med m = repo.find(name, producer);
	repo.del(m);

	Med new_m = Med{ name, producer, newPrice, newSubstance };
	validator.valideaza(new_m);
	repo.store(new_m);
	undoActions.push_back(make_unique<UndoUpdate>(repo, m, new_m));
}

vector<Med> MedsStore::filterByPrice(double price) {
	const vector<Med>& allMeds = repo.getAll();
	vector<Med> filteredMeds;
	std::copy_if(allMeds.begin(), allMeds.end(), back_inserter(filteredMeds), [=](const Med& m) {
		return m.getPrice() <= price;
		});
	return filteredMeds;
}

vector<Med> MedsStore::filterBySubstance(const string& substance) {
	const vector<Med>& allMeds = repo.getAll();
	vector<Med> filteredMeds;
	std::copy_if(allMeds.begin(), allMeds.end(), back_inserter(filteredMeds), [substance](const Med& m) {
		return m.getSubstance() == substance;	
		});
	return filteredMeds;
}

vector<Med> MedsStore::sortMedsByName() {
	vector<Med> sortedCopy{ repo.getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpName);
	return sortedCopy;
}


vector<Med> MedsStore::sortMedsByProducer() {
	vector<Med> sortedCopy{ repo.getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpProducer);
	return sortedCopy;
}

vector<Med> MedsStore::sortMedsBySubstanceAndPrice() {
	vector<Med> sortedCopy{ repo.getAll() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpPriceSubstance);
	return sortedCopy;
}

void MedsStore::addToPrescription(const string& name, const string& producer) {
	const auto& med = repo.find(name, producer);
	currentPrescription.addMedToPrescription(med);
}

void MedsStore::emptyPrescription() {
	currentPrescription.emptyPrescription();
}

const vector<Med>& MedsStore::getAllPrescription() {
	return currentPrescription.getAllPrescription();
}

int MedsStore::addRandomMedsToPrescription(int howMany) {
	currentPrescription.addRandomMeds(this->getAll(), howMany);
	return currentPrescription.getAllPrescription().size();
}

map<string, int> MedsStore::raportSubstance() {
	vector<Med> allMeds = this->getAll();
	map<string, int> map;

	for (const auto& m : allMeds) {
		string substance = m.getSubstance();
		map[substance]++;
	}
	return map;

}

void MedsStore::undo() {
	if (undoActions.empty()) {
		throw RepoException("Undo is no longer possible!");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void MedsStore::exportPrescriptionToCSV(const string& fileName) const {
	std::ofstream out(fileName);
	const auto& all = currentPrescription.getAllPrescription();

	if (!out.is_open()) {
		throw RepoException("Unable to open the file:" + fileName);
	}

	for (const auto& med : all) {
		out << med.getName() << "," << med.getProducer() << "," << med.getPrice() << "," << med.getSubstance() << "\n";
	}
	out.close();
}

Prescription& MedsStore::getPrescription()
{
	return currentPrescription;
}




