#include "PharmacyQT.h"
#include <QtWidgets/QApplication>
#include <iostream>

#include "Console.h"
#include "Tests.h"
#include"MedGUIModel.h"

int main(int argc, char* argv[])
{
	Tests t;
	t.testAll();

	MedRepoFile repo{ "meds.txt" };
	MedValidator val;
	MedsStore srv{ repo, val };
	Console ui{ srv };

	QApplication a(argc, argv);
	MedGUIModel gui{ srv };
	gui.show();

	return a.exec();
}