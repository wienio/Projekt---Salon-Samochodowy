#include "Car.h"
#include <conio.h>
using namespace std;

Car::~Car()
{
}

Car::Car(string brand, string model, string body, string engine_type, string gearbox, string body_color, int production_year, int price, int power, double engine_capacity, int weight) {
	this->brand = brand;
	this->model = model;
	this->body = body;
	this->engine_type = engine_type;
	this->gearbox = gearbox;
	this->body_color = body_color;
	this->production_year = production_year;
	this->price = price;
	this->power = power;
	this->engine_capacity = engine_capacity;
	this->weight = weight;
	cout << "Gratulacje, dodano nowe auto do salonu!" << endl;
}

void Car::get_information(Car ** car_tab, int number) {
	system("cls");
	if (car_tab[number] != NULL) {
		cout << car_tab[number]->brand << " " << car_tab[number]->model << " " << car_tab[number]->body << " " << car_tab[number]->engine_type << " " << car_tab[number]->power << " " << car_tab[number]->power << " " << car_tab[number]->gearbox << " " << car_tab[number]->body_color << " " <<
			 " " << car_tab[number]->weight << car_tab[number]->production_year << endl;
	}
	else {
		cout << "Podano zla wartosc!" << endl;
	}
	_getch();
}

int Car::get_price() {
	return this->price;
}

void Car::add_margin() {
	this->price = this->price + this->price*((rand() % 17) + 4) / 100;
}

void Car::delete_car() {
	this->production_year = NULL;
	this->price = NULL;
	this->power = NULL;
	this->weight = NULL;
	this->engine_capacity = NULL;
	delete this;
}