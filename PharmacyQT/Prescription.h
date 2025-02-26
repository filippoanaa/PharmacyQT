#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Observer.h"
#include "Med.h"

using std::vector;

class Prescription : public Observable {
private:
    vector<Med> prescription;

public:
    /*
     * Constructor implicit pentru clasa Prescription.
     */
    Prescription() = default;

    /*
     * Adauga un medicament in reteta.
     * m - referinta constanta la medicamentul de adaugat.
     */
    void addMedToPrescription(const Med& m);

    /*
     * Goleste reteta.
     */
    void emptyPrescription();

    /*
     * Adauga un numar de medicamente random in reteta.
     * originalPrescription - vector de medicamente din care se aleg aleatoriu.
     * howMany - numarul de medicamente de adaugat in reteta.
     */
    void addRandomMeds(vector<Med> originalPrescription, int howMany);

    /*
     * Returneaza toate medicamentele din reteta.
     * return type - vector<Med>&
     */
    const vector<Med>& getAllPrescription() const;

};
