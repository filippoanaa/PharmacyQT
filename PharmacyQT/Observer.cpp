#pragma once
#include<algorithm>
#include<vector>
using std::vector;
class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> observers;
public:
	void notify() {
		for (auto o : observers) {
			o->update();
		}
	}
	void addObserver(Observer* o) {
		observers.push_back(o);
	}
	void removeObserver(Observer* o) {
		observers.erase(std::remove(observers.begin(), observers.end(), o));
		// remove: se parcurge observers si se muta toate instantele pointerului o la sf vectorului, 
		//si returneaza un iterator(new end) nou catre noua pozitie de sfarsir a intervalului de elemente valide
		//elimina elementele incepand de la new end pana la finalul vectorului observers
	}
};