#include "Med.h"
#include <string>
#include <iostream>
#include<qdebug.h>
using std::string;
using std::cout;
using std::endl;
using std::ostream;

string Med::getName() const {
	return this->name;
}

double Med::getPrice() const {
	return this->price;
}
string Med::getProducer() const {
	return this->producer;
}

string Med::getSubstance() const {
	return this->substance;
}

void Med::setName(const string& newName) {
	this->name = newName;
}

void Med::setPrice(double newPrice) {
	this->price = newPrice;
}

void Med::setProducer(const string& newProducer) {
	this->producer = newProducer;
}

void Med::setSubstance(const string& newSubstance) {
	this->substance = newSubstance;
}

bool cmpName(const Med& m1, const  Med& m2) {
	return m1.getName() < m2.getName();

}

bool cmpProducer(const Med& m1, const Med& m2) {
	return m1.getProducer() < m2.getProducer();
}
bool cmpPriceSubstance(const Med& m1, const Med& m2) {
	if (m1.getSubstance() == m2.getSubstance())
		return m1.getPrice() < m1.getPrice();
	return m1.getSubstance() < m2.getSubstance();
}



