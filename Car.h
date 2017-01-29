#pragma once

#include <iostream>
#include <string>

using std::string;
class Car
{
private:
	string brand, model, body, engine_type, gearbox, body_color;
	int production_year, price, power, weight;
	double engine_capacity;
public:
	friend std::ostream & operator << (std::ostream & os, Car *& car_tab);
	friend void read_cars(Car ** car_tab, int &car_counter, int max_car_amount);
	friend void save_cars_to_file(Car ** car_tab, int max_car_amount);
	int get_price();
	void add_margin();
	void delete_car();
	Car(string brand, string model, string body, string engine_type, string gearbox, string body_color, int production_year, int price, int power, double engine_capacity, int weight);
	static void get_information(Car ** car_tab, int number);
	virtual ~Car();
};