#pragma once
#include<string>
#include <utility>
#include<vector>
#include "Med.h"

using std::string;
using std::vector;

class ValidationException {
	vector<string> errorMsg;
public:
	explicit ValidationException(vector<string> errorMessages) : errorMsg{ std::move(errorMessages) } {};

	string getMessage() {
		string fullMsg;
		for (const string& e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};
class MedValidator {
public:
	void valideaza(const Med& m) {
		vector<string> errors;
		if (m.getName().empty())
			errors.emplace_back("Name must have at least 1 character!");
		if (m.getProducer().empty())
			errors.emplace_back("Producer must have at least 1 character!");
		if (m.getPrice() < 0)
			errors.emplace_back("Price can't be a negative number!");
		if (m.getSubstance().empty())
			errors.emplace_back("Substance must have at least 1 character!");

		if (!errors.empty())
			throw ValidationException(errors);
	}
};

