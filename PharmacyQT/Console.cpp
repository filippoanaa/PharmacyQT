#include "Console.h"
#include <iostream>
#include <map>

using namespace std;

void Console::printMenu() {
    cout << "Options:" << endl;
    cout << "0.Exit\n1.Add med\n2.Show meds\n3.Delete med\n4.Modify med\n5.Filter meds\n6.Sort meds\n7.Prescription menu\n8.Undo\n";
}

void Console::printPrescriptionMenu() {
    cout << "\nRECIPE MENU" << endl;
    cout << "Options: " << endl;
    cout << "1.Add med to prescription\n2.Add random meds to prescription\n3.Clear prescription\n4.Show current prescription\n5.Export\n6.Back to menu\n";
}

void Console::uiAdd() {
    string name, producer, substance;
    double price = 0.0;
    cout << "Name: ";
    getline(cin >> ws, name);
    cout << "Producer: ";
    getline(cin >> ws, producer);
    cout << "Price: ";
    cin >> price;
    cout << "Substance: ";
    getline(cin >> ws, substance);
    try {
        srv.addMed(name, producer, price, substance);
        cout << "Med added!\n";
    }
    catch (RepoException& re) {
        cout << re.getError() << "\n";
    }
    catch (ValidationException& v) {
        cout << "Med is not valid!\n";
        cout << v.getMessage();
    }
}

void Console::uiDelete() {
    string name, producer;
    cout << "Give the name of the med you want to delete\n";
    getline(cin >> ws, name);
    cout << "Give the producer of the med you want to delete\n";
    getline(cin >> ws, producer);
    try {
        srv.deleteMed(name, producer);
        cout << "Med deleted!\n";
    }
    catch (RepoException& re) {
        cout << re.getError() << "\n";
    }
}

void Console::uiModify() {
    string name, producer, newSubstance;
    double newPrice = 0;
    cout << "Give the name of the med you want to modify\n";
    getline(cin >> ws, name);
    cout << "Give the producer of the med you want to modify\n";
    getline(cin >> ws, producer);
    cout << "Set a new price: ";
    cin >> newPrice;
    cout << "Set a new substance: ";
    getline(cin >> ws, newSubstance);
    try {
        srv.modifyMed(name, producer, newPrice, newSubstance);
        cout << "Med modified!\n";
    }
    catch (RepoException& re) {
        cout << re.getError() << "\n";
    }
}

void Console::uiFilter() {
    int crit = 0;
    double price = 0;
    string substance;
    cout << "1- filter by price, 2- filter by substance: ";
    cin >> crit;
    if (crit == 1) {
        cout << "Give the price: ";
        cin >> price;
        printMeds(srv.filterByPrice(price));
    }
    else if (crit == 2) {
        cout << "Give the substance: ";
        cin >> substance;
        printMeds(srv.filterBySubstance(substance));
    }
    else {
        cout << "Invalid criteria!\n";
    }
}

void Console::uiSort() {
    int crit = 0;
    cout << "1-Sort by name\n2-Sort by producer\n3.Sort by substance and price\n";
    cin >> crit;
    if (crit == 1) {
        printMeds(srv.sortMedsByName());
    }
    else if (crit == 2) {
        printMeds(srv.sortMedsByProducer());
    }
    else if (crit == 3) {
        printMeds(srv.sortMedsBySubstanceAndPrice());
    }
    else {
        cout << "Invalid criteria!\n";
    }
}

void Console::printMeds(const vector<Med>& allMeds) {
    if (allMeds.empty()) {
        cout << "No meds found.\n";
    }
    else {
        for (const auto& m : allMeds) {
            cout << "Name: " << m.getName() << " Producer: " << m.getProducer()
                << " Price: " << m.getPrice() << " Substance: " << m.getSubstance() << endl;
        }
    }
}

void Console::uiAddToPlaylist() {
    string name, producer;
    cout << "Name: ";
    getline(cin >> ws, name);
    cout << "Producer: ";
    getline(cin >> ws, producer);
    try {
        srv.addToPrescription(name, producer);
        cout << "Med added to prescription!" << endl;
        cout << "Number of meds: " << srv.getAllPrescription().size() << "\n";
    }
    catch (RepoException& re) {
        cout << re.getError();
    }
    catch (ValidationException& ve) {
        cout << "Invalid med!" << endl;
        cout << ve.getMessage();
    }
}

void Console::uiAddRandomMedsToPlaylist() {
    int howMany;
    cout << "How many random meds do you want to add to the prescription?\n";
    cin >> howMany;
    try {
        int howManyAdded = srv.addRandomMedsToPrescription(howMany);
        cout << howManyAdded << " meds have been added!\n";
        cout << "Number of meds: " << srv.getAllPrescription().size() << "\n";
    }
    catch (RepoException& re) {
        cout << re.getError();
    }
}

void Console::uiEmptyPlaylist() {
    srv.emptyPrescription();
    cout << "The meds from the prescription have been deleted!" << endl;
    cout << "Number of meds: " << srv.getAllPrescription().size() << "\n";
}

void Console::uiRaport() {
    map<string, int> maps = srv.raportSubstance();
    for (const auto& m : maps) {
        cout << "Substance: " << m.first << " Number of meds: " << m.second << endl;
    }
}

void Console::uiExport() {
    string fileName;
    cout << "Give the file name where you want to export the prescription: ";
    cin >> fileName;
    string reff = "D:\\Semestrul 2\\OOP\\LAB7-9\\";
    try {
        srv.exportPrescriptionToCSV(reff.append(fileName));
        cout << "Export done!\n";
        cout << "Number of meds: " << srv.getAllPrescription().size() << "\n";
    }
    catch (RepoException& re) {
        cout << re.getError();
    }
}

void Console::uiPlayList() {
    int cmd;
    int running = 1;
    while (running) {
        printPrescriptionMenu();
        cout << "Options: ";
        cin >> cmd;
        switch (cmd) {
        case 1:
            uiAddToPlaylist();
            break;
        case 2:
            uiAddRandomMedsToPlaylist();
            break;
        case 3:
            uiEmptyPlaylist();
            break;
        case 4:
            printMeds(srv.getAllPrescription());
            break;
        case 5:
            uiExport();
            break;
        case 6:
            running = 0;
            break;
        default:
            break;
        }
    }
}

void Console::run() {
    int running = 1;
    int cmd = 0;
    while (running) {
        printMenu();
        cout << "Your option: ";
        cin >> cmd;
        switch (cmd) {
        case 0:
            running = 0;
            break;
        case 1:
            uiAdd();
            break;
        case 2:
            printMeds(srv.getAll());
            break;
        case 3:
            uiDelete();
            break;
        case 4:
            uiModify();
            break;
        case 5:
            uiFilter();
            break;
        case 6:
            uiSort();
            break;
        case 7:
            uiPlayList();
            break;
        case 8:
            try {
                srv.undo();
                cout << "Undo done!\n";
            }
            catch (RepoException& e) {
                cout << e.getError() << endl;
            }
            break;
        case 9:
            uiExport();
            break;
        default:
            break;
        }
    }
}