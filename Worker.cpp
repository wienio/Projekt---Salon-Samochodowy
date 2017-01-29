#include "Worker.h"
#include "Person.h"
#include <string>
#include <iostream>
#include <conio.h>
using namespace std;

Worker::Worker(string name, string surname, string month, string email, string street, string city, int day, int year, string PESEL, string ID)
	:Person(name,surname,month,email,street,city,day,year,PESEL)
{
	this->ID = ID;
}

Worker::~Worker()
{
}

void Worker::get_information(Worker **worker_tab, int number) {
	if (number > 4 || worker_tab[number] == NULL) {
		cout << "Podano bledna wartosc! " << endl;
		_getch();
	}
	else {
		cout << worker_tab[number]->name << " " << worker_tab[number]->surname << " " << worker_tab[number]->email << " " << worker_tab[number]->PESEL << " " << worker_tab[number]->city << " " 
			<< worker_tab[number]->street
			<< " " << worker_tab[number]->day << " " << worker_tab[number]->month << " " << worker_tab[number]->year << " ID: " << worker_tab[number]->ID << endl;
	}
}

void Worker::delete_person() {
	this->day = NULL;
	this->year = NULL;
	delete this;
}