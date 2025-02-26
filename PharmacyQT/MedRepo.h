#pragma once
#include <vector>
#include <string>
#include <ostream>
#include "Med.h"
#include <exception>

using std::vector;
using std::exception;

class RepoException : public exception {
private:
	string errorMsg;

public:
	/*
	 * Constructor pentru clasa RepoException.
	 */
	RepoException(string errorMsg) : errorMsg{ std::move(errorMsg) } {};

	/*
	 * Returneaza mesajul de eroare.
	 * return type - string
	 */
	string getError() {
		return this->errorMsg;
	}
};

class RepoInterface {
public:
	/*
	 * Constructor implicit pentru clasa RepoInterface.
	 */
	RepoInterface() = default;

	/*
	 * Constructor de copiere sters pentru clasa RepoInterface.
	 * Se interzice copierea obiectelor de tip RepoInterface.
	 */
	RepoInterface(const RepoInterface& ot) = delete;

	/*
	 * Adauga un medicament
	 * Este o functie virtuala pura care trebuie implementata de clasele derivate.
	 * m - const Med&, referinta la medicamentul de adaugat.
	 */
	virtual void store(const Med& m) = 0;

	/*
	 * Returneaza referinta la vectorul cu toate medicamentele.
	 * return type - vector<Med>&
	 */
	virtual vector<Med>& getAll() = 0;

	/*
	 * Gaseste un medicament dupa nume si producator si returneaza o referinta la acesta.
	 * Arunca o exceptie daca medicamentul nu este gasit.
	 * name - const string&, numele medicamentului.
	 * producer - const string&, producatorul medicamentului.
	 * return type - Med&
	 */
	virtual Med& find(const string& name, const string& producer) = 0;

	/*
	 * Verifica daca un medicament exista.
	 * m - const Med&, referinta la medicamentul de verificat.
	 * return type - bool
	 */
	virtual bool exist(const Med& m) = 0;

	/*
	 * Sterge un medicament.
	 * Este o functie virtuala pura care trebuie implementata de clasele derivate.
	 * m - const Med&, referinta la medicamentul de sters.
	 */
	virtual void del(const Med& m) = 0;
};

class MedRepo : public RepoInterface {
private:
	vector<Med> allMeds;

public:
	/*
	 * Constructor implicit pentru clasa MedRepo.
	 */
	MedRepo() = default;

	/*
	 * Constructor de copiere sters pentru clasa MedRepo.
	 * Se interzice copierea obiectelor de tip MedRepo.
	 */
	MedRepo(const MedRepo& ot) = delete;

	/*
	 * Adauga un medicament la lista de medicamente.
	 * Arunca o exceptie daca medicamentul deja exista.
	 * m - const Med&, referinta la medicamentul de adaugat.
	 */
	void store(const Med& m) override;

	/*
	 * Returneaza referinta la vectorul cu toate medicamentele.
	 * return type - vector<Med>&
	 */
	vector<Med>& getAll() override;

	/*
	 * Gaseste un medicament dupa nume si producator si returneaza o referinta la acesta.
	 * Arunca o exceptie daca medicamentul nu este gasit.
	 * name - const string&, numele medicamentului.
	 * producer - const string&, producatorul medicamentului.
	 * return type - Med&
	 */
	Med& find(const string& name, const string& producer) override;

	/*
	 * Verifica daca un medicament exista in depozit.
	 * m - const Med&, referinta la medicamentul de verificat.
	 * return type - bool, true daca medicamentul exista, false altfel.
	 */
	bool exist(const Med& m) override;

	/*
	 * Sterge un medicament
	 * Arunca exceptie daca medicamentul nu este gasit
	 * m - const Med&, referinta la medicamentul de sters.
	 */
	void del(const Med& m) override;
};

class MedRepoFile : public MedRepo {
private:
	string fileName;

	/*
	 * Incarca datele din fisierul specificat in `fileName`.
	 * Arunca o exceptie daca fisierul nu poate fi citit.
	 */
	void loadFromFile();

	/*
	 * Salveaza datele curente din depozit in fisierul specificat in `fileName`.
	 * Arunca o exceptie daca fisierul nu poate fi scris.
	 */
	void saveToFile();

public:
	/*
	 * Constructor pentru clasa MedRepoFile.
	 * fName - string, numele fisierului din care se incarca si in care se salveaza datele.
	 */
	MedRepoFile(string fName) : fileName{ fName } {
		loadFromFile();
	};

	/*
	 * Adauga un medicament si salveaza datele in fisier.
	 * m - const Med&, referinta la medicamentul de adaugat.
	 */
	void store(const Med& m) override;

	/*
	 * Sterge un medicament
	 * Arunca exceptie daca medicamentul nu este gasit
	 * m - const Med&, referinta la medicamentul de sters.
	 */
	void del(const Med& m);
};
