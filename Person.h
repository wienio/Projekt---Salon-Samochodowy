#pragma once
#include <iostream>
#include <string>

using std::string;

class Person {
protected:
	string name, surname, month, email, street, city, PESEL;
	int day, year;
public:
	virtual void delete_person() = 0;
	Person (string name, string surname, string month, string email, string street, string city, int day, int year, string PESEL);
	 virtual ~Person();
};