#include "MedRepo.h"
#include "Service.h"
#include <cassert>
#include<string>
#include <sstream>
#include<fstream>
#include "Tests.h"
using namespace std;

void Tests::testAddR() {

	MedRepo repoTest;
	//repoTest.store(Med("med1", "prod1", 10, "subst1"));
	//repoTest.store(Med("med2", "prod2", 20, "subst3"));
	//assert(repoTest.getAll().size() == 2);

	//Med m1 = repoTest.find("med1", "prod1");
	//assert(m1.getSubstance() == "subst1");
	//assert(repoTest.exist(m1) == true);
	//try {
	//	repoTest.store(Med("med1", "prod1", 10, "subst1"));
	//	assert(false);
	//}
	//catch (RepoException& re) {
	//	assert(true);
	//	assert(re.getError() == "Med with name: med1 and producer: prod1 already exists!");
	//}
}

void Tests::testDeleteR() {
	MedRepo repoTest;
	repoTest.store(Med("med1", "prod1", 10, "subst1"));
	repoTest.store(Med("med2", "prod2", 20, "subst3"));
	assert(repoTest.getAll().size() == 2);
	repoTest.del(Med("med1", "prod1", 10, "subst1"));
	assert(repoTest.getAll().size() == 1);
	assert(repoTest.exist(Med("med1", "prod1", 10, "subst1")) == false);
	try {
		repoTest.del(Med("med1", "prod1", 10, "subst1"));
		assert(false);

	}
	catch (RepoException& re) {
		assert(true);
	}
}



void Tests::testAddS() {
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest{ repoTest, val };
	try {
		srvTest.addMed("abc", "abc", -1, "abc");
		assert(Med("abc", "abc", -1, "abc").getPrice() < 0);
		assert(false);
	}
	catch (ValidationException& v) {
		assert(true);
		assert(v.getMessage() == "Price can't be a negative number!\n");
	}

}

void Tests::testDeleteS() {
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	srvTest.addMed("med1", "prod1", 100, "subst1");
	assert(srvTest.getAll().size() == 1);
	srvTest.deleteMed("med1", "prod1");
	assert(srvTest.getAll().empty());
}

void Tests::testModifyS() {
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	srvTest.addMed("med1", "prod1", 100, "subst1");
	assert(srvTest.getAll().size() == 1);
	srvTest.modifyMed("med1", "prod1", 300, "subst3");
	assert(srvTest.getAll()[0].getPrice() == 300);

}
void Tests::testFindS() {
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	srvTest.addMed("med1", "prod1", 100, "subst1");
	Med m = srvTest.findMed("med1", "prod1");
	assert(m.getSubstance() == "subst1");
	assert(m.getPrice() == 100);

}

void Tests::testFilterS() {
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	repoTest.store(Med("a", "b", 10, "sub"));
	repoTest.store(Med("g", "h", 10, "sub"));
	repoTest.store(Med("c", "e", 200, "sub2"));
	repoTest.store(Med("d", "e", 20, "sub2"));

	//filter by price
	auto rez = srvTest.filterByPrice(150);
	assert(rez.size() == 3);

	auto rez2 = srvTest.filterBySubstance("sub");
	assert(rez2.size() == 2);


}

void Tests::testSortS() {
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	repoTest.store(Med("a", "b", 10, "c"));
	repoTest.store(Med("g", "h", 10, "i"));
	repoTest.store(Med("c", "e", 200, "i"));
	repoTest.store(Med("d", "e", 20, "z"));


	//sortare dupa nume
	auto rez = srvTest.sortMedsByName();
	assert(rez[0].getName() == "a");
	assert(rez[rez.size() - 1].getName() == "g");

	//sortare dupa producator
	auto rez2 = srvTest.sortMedsByProducer();
	assert(rez2[0].getProducer() == "b");
	assert(rez2[rez.size() - 1].getProducer() == "h");

	//sortare dupa substanta si pret
	auto rez3 = srvTest.sortMedsBySubstanceAndPrice();
	assert(rez3[0].getPrice() == 10);
	assert(rez3[1].getSubstance() == rez[1].getSubstance());
	assert(rez3[1].getPrice() == 10);
}

void Tests::testSettersGetters() {
	Med m1{ "med2", "prod2", 10, "subst2" };
	m1.setName("med1");
	m1.setPrice(100);
	m1.setSubstance("subst1");
	m1.setProducer("prod1");
	assert(m1.getName() == "med1");
	assert(m1.getProducer() == "prod1");
	assert(m1.getPrice() == 100);
	assert(m1.getSubstance() == "subst1");

}
void Tests::testCmp() {
	Med m2{ "med2", "prod2", 10, "subst2" };
	Med m1{ "aaa", "aaa", 1, "aaa" };
	Med m3{ "aaa","bbb", 100, "aaa" };

	//cmp name
	assert(cmpName(m1, m2) == true);

	//cmp producer
	assert(cmpProducer(m1, m2) == true);

	//cmp substance
	assert(cmpPriceSubstance(m1, m2) == true);
	assert(cmpPriceSubstance(m1, m3) == 0);
	// cout<<cmpPriceSubstance(m1, m3);
}


void Tests::testValidator() {
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	srvTest.addMed("med1", "prod1", 100, "subst1");

	assert(srvTest.getAll().size() == 1);

	Med m1{ "abc","abc", -1,"abc" };
	try {
		val.valideaza(m1);
	}
	catch (ValidationException& v) {
		assert(true);
		assert(v.getMessage() == "Price can't be a negative number!\n");
	}

	Med m2{ "","abc",100, "abc" };
	try {
		val.valideaza(m2);
	}
	catch (ValidationException& v) {
		assert(true);
		assert(v.getMessage() == "Name must have at least 1 character!\n");
	}

	Med m3{ "abc","",100, "abc" };
	try {
		val.valideaza(m3);
	}
	catch (ValidationException& v) {
		assert(true);
		assert(v.getMessage() == "Producer must have at least 1 character!\n");
	}
	Med m4{ "abc","abc",100, "" };
	try {
		val.valideaza(m4);
	}
	catch (ValidationException& v) {
		assert(true);
		assert(v.getMessage() == "Substance must have at least 1 character!\n");
	}

}

void Tests::testAddPrescription() {
	Prescription prescriptionTest;
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	srvTest.addMed("a", "b", 10, "c");
	srvTest.addMed("g", "h", 10, "i");
	assert(srvTest.getAll().size() == 2);
	try {
		srvTest.addToPrescription("a", "b");
		srvTest.addToPrescription("g", "h");
		assert(true);
	}
	catch (RepoException& re) {
		assert(false);
	}

	try {
		srvTest.addToPrescription("x", "y");
		assert(false);
	}
	catch (RepoException& re) {
		assert(true);
	}

}

void Tests::testEmptyPrescription() {
	Prescription prescriptionTest;
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	srvTest.addMed("a", "b", 10, "c");
	srvTest.addMed("g", "h", 10, "i");
	srvTest.addToPrescription("a", "b");
	assert(srvTest.getAllPrescription().size() == 1);
	srvTest.emptyPrescription();
	assert(srvTest.getAllPrescription().empty());

}

void Tests::testAddRandomToPrescription() {
	Prescription prescriptionTest;
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	srvTest.addMed("a", "b", 10, "c");
	srvTest.addMed("x", "y", 10, "c");
	srvTest.addMed("g", "h", 10, "i");
	assert(srvTest.addRandomMedsToPrescription(5) == 3);
}

void Tests::testRaport() {
	MedRepo repoTest;
	MedValidator val;
	MedsStore srvTest(repoTest, val);
	srvTest.addMed("a", "b", 10, "c");
	srvTest.addMed("x", "y", 10, "c");
	srvTest.addMed("g", "h", 10, "i");
	assert(srvTest.raportSubstance()["c"] == 2);
	assert(srvTest.raportSubstance()["i"] == 1);
}

void Tests::testFileRepo() {
	std::ofstream out("D:\\Semestrul 2\\OOP\\LAB8-9(bun)\\testMeds.txt", std::ios::trunc);
	out.close();
	MedRepoFile repo{ "D:\\Semestrul 2\\OOP\\LAB8-9(bun)\\testMeds.txt" };
	repo.store(Med{ "aa", "aa", 11, "aa" });
	assert(repo.getAll().size() == 1);
	auto m = repo.find("aa", "aa");
	assert(m.getPrice() == 11);
	repo.del(m);
	assert(repo.getAll().empty());
	try {
		repo.del(m);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

}
void Tests::testUndo() {
	MedRepo repo;
	MedValidator val;
	MedsStore srv{ repo,val };
	try {
		srv.undo();
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	//undo adauga
	srv.addMed("aa", "aa", 11, "aa");
	assert(repo.getAll().size() == 1);
	srv.undo();
	assert(repo.getAll().size() == 0);

	//undo stergere
	srv.addMed("bb", "bb", 11, "bb");
	assert(repo.getAll().size() == 1);
	srv.deleteMed("bb", "bb");
	assert(repo.getAll().size() == 0);
	srv.undo();
	assert(repo.getAll().size() == 1);

	//undo modifica
	srv.addMed("cc", "cc", 11, "aa");
	srv.modifyMed("cc", "cc", 100, "bb");
	Med m = srv.findMed("cc", "cc");
	assert(m.getPrice() == 100);
	assert(m.getSubstance() == "bb");
	srv.undo();
	Med old_m = srv.findMed("cc", "cc");
	assert(old_m.getPrice() == 11);
	assert(old_m.getSubstance() == "aa");


}

void Tests::testExport() {
	MedRepo repo;
	MedValidator val;
	Prescription prescription;
	MedsStore srv{ repo,val };
	srv.addMed("aa", "aa", 11, "aa");
	srv.addMed("bb", "bb", 12, "bb");
	srv.addRandomMedsToPrescription(2);
	srv.exportPrescriptionToCSV("D:\\Semestrul 2\\OOP\\LAB8-9(bun)\\test.csv");
	std::ifstream in("D:\\Semestrul 2\\OOP\\LAB8-9(bun)\\test.csv");
	assert(in.is_open());
	int cnt = 0;
	while (!in.eof()) {
		string line;
		in >> line;
		cnt++;
	}
	in.close();
	assert(cnt == 3);
	try {
		srv.exportPrescriptionToCSV("D:\\Semestrul 2\\x\\a\\b.csv");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}


void Tests::testAll()
{
	//repo tests
	testAddR();
	testDeleteR();
	testFileRepo();


	//srv tests
	testAddS();
	testDeleteS();
	testModifyS();
	testFindS();
	testSortS();
	testFilterS();
	testUndo();
	testExport();


	////domain tests
	testSettersGetters();
	testValidator();
	testCmp();

	////prescription tests
	testAddPrescription();
	testEmptyPrescription();
	testAddRandomToPrescription();
	testRaport();
}
