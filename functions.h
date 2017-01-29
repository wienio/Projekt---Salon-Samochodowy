#pragma once
#include "Admin.h"

void menu();
bool option_1(int &admin_counter, Admin *&adm);
void admin_menu(Admin *administrator, Car ** car_tab, int &car_counter, int max_car_amount, int &budget, int & workers_counter, int max_workers_amount, Worker ** worker_tab);
void show_cars();
void welcome_menu();
void low_budget(int &budget);
void save_workers_to_file(Worker ** worker_tab, int workers_counter);
void save_cars_to_file(Car ** car_tab, int max_car_amount);
void read_workers(Worker ** worker_tab, int & workers_counter);
void read_cars(Car ** car_tab, int &car_counter);
void read_car_with_number(Car **car_tab, int number);