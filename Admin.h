#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "Car.h"
#include "Worker.h"

using std::string;

class Admin {
private:
	string name, surname;
public:
	friend class Worker;
	friend class Car;
	void buy_car(Car ** car_tab, int &car_counter, int max_car_amount, int &budget);
	void sell_car(Car ** car_tab, int number, int &budget, int max_car_amount, int &car_counter);
	void add_worker(int &max_wokers_amount, int & workers_counter, Worker ** worker_tab);
	Admin(string name, string surname);
	 virtual ~Admin();
};

