#include "Person.h"
#include <iostream>
#include <string>

using namespace std;

 Person::Person(string name, string surname, string month, string email, string street, string city, int day, int year, string PESEL) {
	this -> name = name;
	this -> surname = surname;
	this -> month = month;
	this -> email = email;
	this ->street = street;
	this -> city = city;
	this -> day = day;
	this -> year = year;
	this -> PESEL = PESEL;
} 

 Person::~Person() {
	 cout << "Usunieto osobe!" << endl;
 } 