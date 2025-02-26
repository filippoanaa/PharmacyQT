#pragma once
#include<string>
#include<iostream>
using std::string;
using std::cout;
using std::endl;


class Med {
private:
	string name;
	string producer;
	double price;
	string substance;
public:
	Med() = delete;

	/* Constructor */
	Med(string n, string prod, double pr, string sub) : name{ std::move(n) }, producer{ std::move(prod) }, price{ pr }, substance{ std::move(sub) } {};

	Med(const Med& ot) : name{ ot.name }, producer{ ot.producer }, price{ ot.price }, substance{ ot.substance } {
		// cout << "Med copy construtor called. " << endl;
	}

	Med& operator=(const Med& ot) {
		this->name = ot.name;
		this->producer = ot.producer;
		this->price = ot.price;
		this->substance = ot.substance;
		return *this;
	}

	~Med() = default;

	/* Getter pentru pret
	* return type - double, pretul medicamentului
	*/
	double getPrice() const;

	/* Getter pentru producator
	* return type - string, producatorul medicamentului
	*/
	string getProducer() const;

	/* Getter pentru cantitatea de substanta activa
	* return type - string, substanta activa din medicament
	*/
	string getSubstance() const;

	/* Getter pentru denumire
	* return type - string, numele medicamentului
	*/
	string getName() const;

	/*
	* setter pentru nume
	* newName - const string&, noul nume
	*/
	void setName(const string& newName);

	/* Setter pentru pret
	* newPrice - int, noul pret
	*/
	void setPrice(double newPrice);

	void setProducer(const string& newProducer);

	/* Setter pentru cantitatea de substanta activa
	* newSubstance - const string&, noua substanta
	*/
	void setSubstance(const string& newSubstance);
};

bool cmpName(const Med& m1, const Med& m2);

bool cmpProducer(const Med& m1, const Med& m2);

bool cmpPriceSubstance(const Med& m1, const Med& m2);
