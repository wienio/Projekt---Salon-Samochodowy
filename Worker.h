#pragma once
#include "Person.h"
#include <string>

using std::string;

class Worker
	: public Person
{
private:
	string ID;
public:
	friend void read_workers(Worker ** worker_tab, int &worker_counter);
	friend void save_workers_to_file(Worker **worker_tab, int workers_counter);
	Worker(string name, string surname, string month, string email, string street, string city, int day, int year, string PESEL, string ID);
	virtual ~Worker();
	void get_information(Worker ** worker_tab, int number);
	void delete_person(); // because sometimes get bugged for integers, doubles etc for strings it works
};

