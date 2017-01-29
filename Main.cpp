#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <conio.h>
#include "Car.h"
#include "Person.h"
#include "Admin.h"
#include "Worker.h"
#include <fstream>
#include "functions.h"
#include <iomanip>

using namespace std;

const string admin_password = "salon2017";
const int max_car_amount = 30;
const int max_workers_amount = 5;
int admin_counter = 0;
int workers_counter = 0;
int car_counter = 0;
int budget;

int main() {
	fstream plik_budget;
	plik_budget.open("budget.txt", ios::in);
	if (plik_budget.good()) {
		plik_budget >> budget;
		plik_budget.close();
	}
	else {
		cout << "Program wymaga pliku budget.txt aby poprawnie dzialac!" << endl;
		return 0;
	}
	low_budget(budget);
	srand(time(NULL));
	string password;
	char choose;
	bool end = false;
	welcome_menu();
	 Car ** car_tab = new Car * [max_car_amount];
	 for (int i = 0; i < max_car_amount; i++) {
		 car_tab[i] = NULL;
	 }
	 Worker ** worker_tab = new Worker *[max_workers_amount];
	 for (int i = 0; i < max_workers_amount; ++i) {
		 worker_tab[i] = NULL;
	 }
	 Admin *administrator;

	while (end != true) {
		system("CLS");
		menu();
		choose = _getch();
		switch (choose)
		{
		case '1': {
			cout << "Podaj haslo: ";
			cin >> password;
			if (password == admin_password) {
				bool administration = option_1(admin_counter, administrator);
				if (administration) {
					admin_menu(administrator, car_tab, car_counter, max_car_amount, budget, workers_counter,max_workers_amount, worker_tab);
				}
			}
			else {
				cout << "Podano bledne haslo! BLAD!" << endl;
				_getch();
			}
			break;
		}
		case '2': {
			show_cars();
			break;
		}
		case '3': {
			save_cars_to_file(car_tab, max_car_amount);
			break;
		}
		case '4': {
			int number;
			system("cls");
			cout << "Podaj numer licznika (0-29): ";
			cin >> number;
			try {
				read_car_with_number(car_tab, number);
			}
			catch (string exception) {
				cout << "Wyjatek: " << exception << endl;
				_getch();
			}
			break;
		}
		case '5': {
			save_workers_to_file(worker_tab, workers_counter);
			break;
		}
		case '6': {
			read_workers(worker_tab, workers_counter);
			break;
		}
		case '7': {
			system("cls");
			cout << "Twoj budzet wynosi: " << budget << endl;
			_getch();
			break;
		}
		case '8': {
			read_cars(car_tab, car_counter,max_car_amount);
			break;
		}
		case '9':
		{
			end = true;
			break;
		}
		default:
			system("cls");
			cout << "Podano zla wartosc! " << endl;
			_getch();
			break;
		}
	}
	 for (int i = 0; i < max_car_amount; ++i) {
		 if (car_tab[i] != NULL) {
			 delete car_tab[i];
		 }
	} 
	 for (int i = 0; i < max_workers_amount; ++i) {
		 if (worker_tab[i] != NULL) {
			 delete worker_tab[i];
		 }
	 }
	system("cls");
	cout << "Dziekujemy za spedzony czas w naszym salonie!" << endl;
	_getch();
	delete[] car_tab; 
	delete[] worker_tab;
}