#pragma once
#include <vector>
#include <string>
#include "Service.h"

using std::vector;
using std::string;

class Console {
private:
    MedsStore& srv;
public:
    Console(MedsStore& srv) : srv{ srv } {}
    Console(const Console& ot) = delete;

    void printMenu();
    void printPrescriptionMenu();
    void uiAdd();
    void uiDelete();
    void uiModify();
    void uiFilter();
    void uiSort();
    void uiPlayList();
    void uiAddToPlaylist();
    void uiAddRandomMedsToPlaylist();
    void uiEmptyPlaylist();
    void printMeds(const vector<Med>& allMeds);
    void uiRaport();
    void uiExport();
    void run();
};