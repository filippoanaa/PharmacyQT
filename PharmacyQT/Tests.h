#pragma once
class Tests {
private:
	//repo tests
	void testAddR();
	void testDeleteR();
	void testFileRepo();


	//srv tests
	void testAddS();
	void testDeleteS();
	void testModifyS();
	void testFindS();
	void testSortS();
	void testFilterS();
	void testUndo();
	void testExport();


	//domain tests
	void testSettersGetters();
	void testValidator();
	void testCmp();

	//prescription tests
	void testAddPrescription();
	void testEmptyPrescription();
	void testAddRandomToPrescription();
	void testRaport();

public:
	void testAll();
};
