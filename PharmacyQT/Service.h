#pragma once
#include "MedRepo.h"
#include "Validator.h"
#include "Prescription.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

using std::string;
using std::vector;
using std::map;
using std::unique_ptr;

class MedsStore {
private:
	RepoInterface& repo;
	MedValidator& validator;
	Prescription currentPrescription;
	vector<unique_ptr<UndoAction>> undoActions;

public:
	/*
	 * Constructor
	 */
	explicit MedsStore(MedRepo& mr, MedValidator& val) : repo{ mr }, validator{ val } {};

	/*
	 * Constructor de copiere sters pentru clasa MedsStore.
	 * Se interzice copierea obiectelor de tip MedsStore.
	 */
	MedsStore(const MedsStore& ot) = delete;

	/*
	 * Returneaza referinta la vectorul cu toate medicamentele.
	 * return type - vector<Med>&
	 */
	const vector<Med>& getAll();

	/*
	 * Adauga un medicament.
	 * name - const string&, numele medicamentului.
	 * producer - const string&, producatorul medicamentului.
	 * price - double, pretul medicamentului.
	 * substance - const string&, substanta medicamentului.
	 */
	void addMed(const string& name, const string& producer, double price, const string& substance);

	/*
	 * Sterge un medicament dupa nume si producator.
	 * name - const string&, numele medicamentului.
	 * producer - const string&, producatorul medicamentului.
	 */
	void deleteMed(const string& name, const string& producer);

	/*
	 * Modifica pretul si substanta medicamentului.
	 * name -const string&, numele medicamentului.
	 * producer - const string&,producatorul medicamentului.
	 * newPrice - double, noul pret al medicamentului.
	 * newSubstance - const string&, noua substanta a medicamentului.
	 */
	void modifyMed(const string& name, const string& producer, double newPrice, const string& newSubstance);

	/*
	 * Gaseste un medicament dupa nume si producator.
	 * name - const string&, numele medicamentului.
	 * producer - const string&, producatorul medicamentului.
	 * return type - Med&
	 */
	const Med& findMed(const string& name, const string& producer);

	/*
	 * Sorteaza medicamentele dupa nume.
	 * return type - vector<Med>
	 */
	vector<Med> sortMedsByName();

	/*
	 * Sorteaza medicamentele dupa producator.
	 * return type - vector<Med>
	 */
	vector<Med> sortMedsByProducer();

	/*
	 * Sorteaza medicamentele dupa substanta si pret.
	 * return type - vector<Med>
	 */
	vector<Med> sortMedsBySubstanceAndPrice();

	/*
	 * Filtreaza medicamentele care au pretul mai mic sau egal cu price.
	 * price -double,  pretul maxim al medicamentelor.
	 * return type - vector<Med>
	 */
	vector<Med> filterByPrice(double price);

	/*
	 * Filtreaza medicamentele care au substanta egala cu substance.
	 * substance - substanta medicamentelor.
	 * return type - vector<Med>
	 */
	vector<Med> filterBySubstance(const string& substance);

	/*
	 * Adauga un medicament in reteta.
	 * name - const string&, numele medicamentului.
	 * producer - const string&, producatorul medicamentului.
	 */
	void addToPrescription(const string& name, const string& producer);

	/*
	 * Adauga un numar de medicamente in reteta.
	 * howMany - numarul de medicamente de adaugat.
	 * return type - int
	 */
	int addRandomMedsToPrescription(int howMany);

	/*
	 * Goleste reteta.
	 */
	void emptyPrescription();

	/*
	 * Returneaza toate medicamentele din reteta.
	 * return type - vector<Med>&
	 */
	const vector<Med>& getAllPrescription();

	/*
	 * Returneaza un dictionar cu substantele si numarul de medicamente care contin fiecare substanta.
	 * return type - map<string, int>
	 */
	map<string, int> raportSubstance();

	/*
	 * Efectueaza actiunea de undo.
	 */
	void undo();

	/*
	 * Exporta medicamentele din reteta in format CSV.
	 * fileName - numele fisierului CSV.
	 */
	void exportPrescriptionToCSV(const string& fileName) const;

	/*
	 * Returneaza reteta curenta.
	 * return type - Prescription&
	 */
	Prescription& getPrescription();
};
