#include "Prescription.h"
#include <random>
using std::shuffle;
using std::default_random_engine;
using std::random_device;

void Prescription::addMedToPrescription(const Med& m) {
	prescription.push_back(m);
	notify();
}

void Prescription::emptyPrescription() {
	prescription.clear();
	notify();
}

const vector<Med>& Prescription::getAllPrescription() const {
	return prescription;
}

void Prescription::addRandomMeds(vector<Med> originalPrescription, int howMany) {
	shuffle(originalPrescription.begin(), originalPrescription.end(), default_random_engine(random_device{}()));

	int targetSize = prescription.size() + howMany;
	while (prescription.size() < targetSize && !originalPrescription.empty()) {
		prescription.push_back(originalPrescription.back());
		originalPrescription.pop_back();
	}
	notify();
}


