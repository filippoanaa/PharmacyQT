#include <algorithm>
#include "MedRepo.h"
#include "vector"
#include<fstream>
#include <sstream>
#include <iostream>

using std::ofstream;
using std::ifstream;
using std::getline;
using std::stod;
using std::stringstream;

Med& MedRepo::find(const string& name, const string& producer) {
	auto f = std::find_if(this->allMeds.begin(), this->allMeds.end(), [=](const Med& m) {
		return m.getName() == name && m.getProducer() == producer;
		});

	if (f != this->allMeds.end())
		return *f;
	else
		throw RepoException("Med with name: " + name + " and producer: " + producer + " doesn't exist!");
}


bool MedRepo::exist(const Med& m) {
	try {
		find(m.getName(), m.getProducer());
		return true;
	}
	catch (RepoException& re) {
		return false;
	}

}

void MedRepo::store(const Med& m) {
	if (exist(m)) {
		throw RepoException("Med with name: " + m.getName() + " and producer: " + m.getProducer() + " already exists!");
	}
	this->allMeds.push_back(m);
}

vector<Med>& MedRepo::getAll() {
	return this->allMeds;
}

void MedRepo::del(const Med& m) {
	if (!exist(m)) {
		throw RepoException("Med with name: " + m.getName() + " and producer: " + m.getProducer() + " does not exist!");
	}

	auto it = std::find_if(allMeds.begin(), allMeds.end(), [&](const Med& med) {
		return med.getName() == m.getName() && med.getProducer() == m.getProducer();
		});

	if (it!= allMeds.end()) {
		allMeds.erase(it);
	}

	
}


void MedRepoFile::loadFromFile() {

	ifstream medFile(this->fileName);
	if (!medFile.is_open()) {
		throw RepoException("Cannot read from file " + fileName);
	}

	string line;
	while (getline(medFile, line)) {
		if (!line.empty()) {
			string name, producer, substance;
			double price;
			stringstream linestream(
				line);
			string currentItem;
			int itemNumber = 0;
			while (getline(linestream, currentItem, ',')) {
				currentItem.erase(remove_if(currentItem.begin(), currentItem.end(), ::isspace), currentItem.end());

				if (itemNumber == 0) name = currentItem;
				if (itemNumber == 1) producer = currentItem;
				if (itemNumber == 2) price = stod(currentItem);
				if (itemNumber == 3) substance = currentItem;
				itemNumber++;
			}
			Med m{ name, producer, price, substance };
			MedRepo::store(m);	
			
		}
	}
	medFile.close();
}

void MedRepoFile::saveToFile() {
	try {
		ofstream medOutput(this->fileName);
		if (!medOutput.is_open()) {
			throw RepoException("Cannot write to file: " + fileName);
		}
		for (auto& med : getAll()) {
			medOutput << med.getName() << "," << med.getProducer() << "," << med.getPrice() << "," << med.getSubstance() << "\n";
		}
		medOutput.close();
	}
	catch (RepoException& e) {
		cout << e.getError();
	}

}

void MedRepoFile::store(const Med& m) {
	MedRepo::store(m);
	saveToFile();
}

void MedRepoFile::del(const Med& m) {
	MedRepo::del(m);
	saveToFile();
}

