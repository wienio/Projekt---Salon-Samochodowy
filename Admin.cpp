#include "Admin.h"
#include "Worker.h"
#include "Car.h"
#include <conio.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;


Admin::Admin(string name, string surname) {
	this->name = name;
	this->surname = surname;
}

Admin::~Admin()
{
	cout << "Usunieto konto administratora!" << endl;
}

void Admin::add_worker(int &max_workers_amount, int &workers_amount, Worker ** worker_tab) {
	srand(time(NULL));
	if (workers_amount < max_workers_amount) {
		string imie, nazwisko, miesiac_urodzenia, mail, ulica, miasto, id, nr_pesel;
		int dzien, rok;
		char choose;
		cout << "Podaj imie pracownika: ";
		cin >> imie;
		cout << "Podaj nazwisko pracownika: ";
		cin >> nazwisko;
		cout << "Podaj maila pracownika: ";
		cin >> mail;
		cout << "Podaj miasto w ktorym pracownik mieszka: ";
		cin >> miasto;
		cout << "Podaj ulice na ktorej pracownik mieszka: ";
		cin >> ulica;
		cout << "Podaj dzien, miesiac (slownie) oraz rok w ktorym sie pracownik urodzil: ";
		cin >> dzien >> miesiac_urodzenia >> rok;
		cout << "Podaj numer PESEL pracownika: ";
		bool is_pesel_correct = false;
		while (is_pesel_correct==false) {
			cin >> nr_pesel;
			if (nr_pesel.length() != 11) {
				cout << "Podany PESEL jest za krotki, PESEL zawiera 11 znakow z przedzialu 0-9!" << endl;
			}
			else {
				is_pesel_correct = true;
				for (int i = 0; i < nr_pesel.length(); ++i) {
					if (nr_pesel[i] < 48 || nr_pesel[i] > 57) {
						is_pesel_correct = false;
						system("cls");
						cout << "Prosze podac PESEL jeszcze raz, poniewaz zawiera nieodpowiednie znaki!" << endl;
						break;
					}
				}
			}
		}
		cout << "Czy chcesz wygenerowac ID (6 liczb) dla pracownika automatycznie? [T/N] ";
		choose = _getch();

		while (choose != 't' && choose != 'T' && choose != 'N' && choose != 'n') {
			system("cls");
			cout << "Podano bledna litere, prosze wpisac T / N !";
			choose = _getch();
		}

		if (choose == 't' || choose == 'T') {
			id = "000000";
			for (int i = 0; i < 6; ++i) {
				id[i] += rand() % 10;
			}
		}
		else {
			bool if_correct = true;
			bool exit = false;
			while (exit == false) {
				cin >> id;
				for (int i = 0; i < id.length(); ++i) {
					if (id[i] < 48 && id[i] > 57) {
						if_correct = false;
						break;
					}
				}

				while (id.length() != 6 || if_correct == false) {
					cout << "Podane id jest zlej dlugosci lub zawiera w sobie nieodpowiednie znaki, prosze wpisac 6 liczb!" << endl;
					id.clear();
					cin >> id;
					for (int i = 0; i < id.length(); ++i) {
						if (id[i] < 48 && id[i] > 57) {
							if_correct = false;
							break;
						}
						else {
							if_correct = true;
						}
					}
				}

				if (id.length() == 6 && if_correct == true) {
					exit = true;
				}
			}
		}
		
		worker_tab[workers_amount] = new Worker(imie,nazwisko,miesiac_urodzenia,mail,ulica,miasto,dzien,rok,nr_pesel,id);
		workers_amount++;
	}
	else {
		cout << "W salonie pracuje juz 5 pracownikow i to jest maksimum!" << endl;
		_getch();
	}
}

void Admin::buy_car(Car ** car_tab, int &car_counter, int max_car_amount, int &budget) {
	srand(time(NULL));
	if (car_counter > 29) {
		system("cls");
		cout << "Salon samochodowy jest juz pelny i nie mozna juz wiecej kupic!" << endl;
		_getch();
	}
	else {
		int i = 0;
		while (car_tab[i] != NULL) {
			++i;
		}
		string brand, model, body, engine_type, gearbox, body_color;
		int production_year, price, power, weight;
		double engine_capacity;
		cout << "Podaj marke samochodu: ";
		cin >> brand;
		cout << "Podaj model: ";
		cin >> model;
		cout << "Podaj typ nadzwozia: ";
		cin >> body;
		cout << "Podaj typ silnika: ";
		cin >> engine_type;
		cout << "Podaj pojemnosc silnika: ";
		cin >> engine_capacity;
		cout << "Podaj moc silnika w KM: ";
		cin >> power;
		cout << "Podaj typ skrzyni (manualna / automatyczna): ";
		cin >> gearbox;
		cout << "Podaj kolor nadwozia: ";
		cin >> body_color;
		cout << "Podaj mase samochodu: ";
		cin >> weight;
		cout << "Podaj rok produkcji: ";
		cin >> production_year;
		cout << "Podaj cene samochodu: ";
		cin >> price;
		if (price > budget) {
			cout << "Niestety nie stac nas na ten samochod" << endl;
		}
		else {
			budget -= price;
			fstream plik_budget;
			plik_budget.open("budget.txt", ios::out);
			if (plik_budget.good()) {
				plik_budget << budget;
				plik_budget.close();
			}
			car_tab[i] = new Car(brand, model, body, engine_type, gearbox, body_color, production_year, price, power, engine_capacity, weight);
			car_tab[i]->add_margin();
			car_counter++;
			cout << "Zaleca sie zapisanie aut do pliku po wyjsciu z panelu administracyjnego!" << endl;
		}
	}
	_getch();
}

void Admin::sell_car(Car ** car_tab, int number, int &budget, int max_car_amount, int &car_counter) {
	if (car_tab[number] == NULL || number > 29) {
		cout << "Blad, pod tym numerem nie znajduje sie zaden samochod! " << endl;
	}
	else {
		budget += car_tab[number]->get_price();
		fstream plik_budget;
		plik_budget.open("budget.txt", ios::out);
		if (plik_budget.good()) {
			plik_budget << budget;
			plik_budget.close();
		}
		car_tab[number]->delete_car();
		car_tab[number] = NULL;
		car_counter--;
		save_cars_to_file(car_tab, max_car_amount);
		cout << "Udalo sie sprzedac samochod!" << endl;
	}
	_getch();
}