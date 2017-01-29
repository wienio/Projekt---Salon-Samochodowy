#include "functions.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "Car.h"
#include "Admin.h"
#include <iomanip>
using namespace std;

void menu() {
	cout << "Wybierz odpowiednia opcje: " << endl <<
		"1 - Logowanie na konto administratora (nalezy znac haslo!)" << endl <<
		"2 - Wyswietlenie listy dostepnych samochodow z pliku" << endl <<
		"3 - Zapis samochodow do pliku" << endl <<
		"4 - Odczyt konkretnego samochodu z programu (nalezy podac numer auta (0-29))" << endl <<
		"5 - Zapis pracownikow do pliku" << endl <<
		"6 - Odczyt pracownikow z pliku" << endl << 
		"7 - Zobacz swoj budzet" << endl <<
		"8 - Odczyt samochodow z pliku do programu" << endl << 
		"9 - Wyjscie z salonu samochodowego" << endl;
}

void low_budget(int &budget) {
	if (budget < 7000) {
		system("cls");
		cout << "Twoj budzet jest bardzo niski, czy chcesz zresetwoac go do wartosci domyslnej [T/N]? (30000) ";
		char if_reset;
		if_reset =_getch();
		while (if_reset != 'T' && if_reset != 't' && if_reset != 'n' && if_reset != 'N') {
			system("cls");
			cout << "Podaj t/n!" << endl;
			if_reset =_getch();
		}
		if (if_reset == 't' || if_reset == 'T') {
			budget = 30000;
		}
	}
	cout << endl;
}

bool option_1(int &admin_counter, Admin *&adm) {
	char admin_choose;
	system("cls");
	cout << "Uzyskano dostep!" << endl <<
		"Co chcesz dalej zrobic? " << endl <<
		"1 - odczytanie danych o adminie z pliku" << endl <<
		"2 - utworzenie nowego konta administratora (max 1 konto admina!)" << endl;
	admin_choose = _getch();

	while (admin_choose != '1' && admin_choose != '2') {
		cout << "Podano bledna wartosc, prosze wybrac 1 lub 2!" << endl;
		cin >> admin_choose;
	}
	if (admin_choose == '1') {
		if (admin_counter == 0) {
			string name, surname;
			fstream admin_plik;
			admin_plik.open("admin.txt", ios::in);
			if (admin_plik.good()) {
				admin_plik >> name;
				admin_plik >> surname;
				admin_plik.close();
				adm = new Admin(name, surname);
				admin_counter++;
				cout << "Poprawnie odczytano dane do programu!" << endl;
				_getch();
			}
			else {
				cout << "Blad, byc moze plik nie istnieje! " << endl;
				_getch();
			}
		}
		else {
			cout << "Istnieje juz administrator tego salonu!" << endl;
			_getch();
		}

	}
	else {
		if (admin_counter == 0)
		{
			string name, surname;
			cout << "Podaj swoje imie i nazwisko: ";
			cin >> name >> surname;
			if (name[0] >= 97 && name[0] <= 122) {
				name[0] -= 32;
			}
			if (surname[0] >= 97 && surname[0] <= 122) {
				surname[0] -= 32;
			}
			admin_counter++;
			adm= new Admin(name, surname);
			cout << "Czy chcesz zapisac te dane do pliku? [T/N] ";
			fflush(stdin);
			admin_choose = _getch();

			while (admin_choose != 't' && admin_choose != 'T' && admin_choose != 'n' && admin_choose != 'N') {
				system("cls");
				cout << "Podano bledny znak!" << endl;
				fflush(stdin);
				admin_choose = _getch();
			}

			if (admin_choose == 't' || admin_choose == 'T') {
				fstream admin_plik;
				admin_plik.open("admin.txt", ios::out);
				if (admin_plik.good()) {
					admin_plik << name << " " << surname;
					admin_plik.close();
					cout << endl << "Dane zapisane poprawnie do pliku" << endl;
					_getch();
				}
				else {
					cout << "Nieoczekiwany blad!" << endl;
					_getch();
				}
			}
		}
		else {
			cout << "Istnieje juz administrator tego salonu!" << endl;
			_getch();
		}
	}
	system("cls");
	cout << "Czy chcesz wejsc w panel administracyjny? [T/N] " << endl;
	fflush(stdin);
	cin.ignore();
	admin_choose = _getch();
	while (admin_choose != 't' && admin_choose != 'T' && admin_choose != 'n' && admin_choose != 'N') {
		system("cls");
		cout << "Podaj wlasciwa wartosc [T/N] " << endl;
		cin.ignore();
		fflush(stdin);
		admin_choose = _getch();
	}
	if (admin_choose == 't' || admin_choose == 'T') {
		return true;
	}
	else {
		return false;
	}
}

void show_cars() {
	fstream cars;
	system("cls");
	cars.open("cars.txt", ios::in);
	if (cars.good()) {
		while (!cars.eof()) {
			string dane;
			getline(cars, dane);
			cout << dane << endl;
		}
		cars.close();
		cout << endl;
	}
	else {
		cout << "Blad, plik z autami nie istnieje!" << endl;
	}
	_getch();
}

void admin_menu(Admin *administrator, Car ** car_tab, int &car_counter,int max_car_amount, int &budget, int & workers_counter, int max_workers_amount, Worker ** worker_tab) {
	char exit = false;
	while (exit != true) {
		system("cls");
		cout << "Wybierz opcje co chcesz zrobic: " << endl <<
			"1 - Kup samochod " << endl <<
			"2 - Sprzedaj samochod (podaj numer auta, ktory chcesz sprzedac) " << endl <<
			"3 - Zatrudnij pracownika " << endl <<
			"4 - Wyjdz" << endl;
		char choose;
		choose = _getch();
		while (choose != '1' && choose != '2' && choose != '3' && choose != '4') {
			system("cls");
			cout << "Podano bledna wartosc, prosze podac prawidlowa (1-4)! " << endl;
			choose = _getch();
		}
		switch (choose) {
		case '1': {
			administrator->buy_car(car_tab, car_counter, max_car_amount, budget);
			break;
		}
		case '2': {
			int number;
			cout << "Podaj numer samochodu: ";
			cin >> number;
			administrator->sell_car(car_tab, number, budget, max_car_amount, car_counter);
			break;
		}
		case '3': {
			administrator->add_worker(max_workers_amount,workers_counter,worker_tab);
			break;
		}
		case '4': {
			exit = true;
			break;
		} 
		default: {
			system("cls");
			break;
		}
		} 
	}
}

void welcome_menu() {
	cout << "Witamy w wirtualnym salonie samochodowym!" << endl <<
		"(Haslo administratora to: salon2017)" << endl << endl <<
		"Twoj limit samochodow w salonie wynosi 30" << endl <<
		"Marza przy kupnie samochodu generowana jest autoamtycznie" << endl <<
		"(4%-20% wartosci kupionego samochodu)" << endl << endl << 
		"Do poprawnego wyswietlania funkcji programu nalezy " << endl <<
		"zwiekszyc rozmiar szerokosci bufora terminala do 140!" << endl << endl << 
		"Wcisnij dowolny klawisz aby kontynuowac!" << endl;
	_getch();
	return;
}

void save_workers_to_file(Worker ** worker_tab, int workers_counter) {
	fstream worker_file;
	system("cls");
	worker_file.open("workers.txt", ios::out);
	if (worker_file.good()) {
		worker_file << setw(15) << left << "Imie" << setw(15) << left << "Nazwisko" << setw(12) << left << "Miasto" << setw(15)
			<< left << "Ulica" << setw(20) << left << "Email" << setw(7) << left << "Dzien" << setw(12) << left
			<< "Miesiac" << setw(5) << left << "Rok" << setw(14) << left << "PESEL" << setw(6) << left << "ID" << endl;
		for (int i = 0; i < workers_counter; ++i) {
			if (worker_tab[i] != NULL) {
				worker_file << setw(15) << left << worker_tab[i]->name << setw(15) << left << worker_tab[i]->surname << setw(12) << left << worker_tab[i]->city << setw(15)
					<< left << worker_tab[i]->street << setw(20) << left << worker_tab[i]->email << setw(7) << left << worker_tab[i]->day << setw(12) << left
					<< worker_tab[i]->month << setw(5) << left << worker_tab[i]->year << setw(14) << left << worker_tab[i]->PESEL << setw(6) << left << worker_tab[i]->ID << endl;
			}
		}
		worker_file.close();
		cout << "Dane zapisane poprawnie!" << endl;
	}
	else {
		cout << "Nieoczekiwany blad!" << endl;
	}
	_getch();
}

void save_cars_to_file(Car ** car_tab, int max_car_amount) {
	fstream plik_car;
	system("cls");
	plik_car.open("cars.txt", ios::out);
	if (plik_car.good()) {
		plik_car << setw(12) << left << "Marka" << setw(10) << left << "Model" << setw(16) << left << "Typ nadwozia" << setw(17) << left << "Typ silnika" << setw(22) << left << "Pojemnosc silnika"
			<< setw(12) << left << "Moc (KM)" << setw(14) << left << "Typ skrzyni" << setw(16) << left << "Rok produkcji" << setw(8) << left << "Masa" << setw(10) << left << "Cena" << endl;
		for (int i = 0; i < max_car_amount; ++i) {
			if (car_tab[i] != NULL) {
				plik_car << setw(12) << left << car_tab[i]->brand << setw(10) << left << car_tab[i]->model << setw(16) << left << car_tab[i]->body << setw(17) << left << car_tab[i]->engine_type
					<< setw(22) << left << car_tab[i]->engine_capacity << setw(12) << left << car_tab[i]->power << setw(14) << left << car_tab[i]->gearbox << setw(16) << left
					<< car_tab[i]->production_year << setw(8) << left << car_tab[i]->weight << setw(10) << left << car_tab[i]->price << endl;
			}
		}
		plik_car.close();
		cout << "Dane zapisane poprawnie! " << endl;
	}
	else {
		cout << "Nieoczekiwany blad!" << endl;
	}
	_getch();
}

ostream & operator << (ostream & os, Car *& car_tab) {
	os << setw(12) << left << car_tab->brand << setw(10) << left << car_tab->model << setw(16) << left << car_tab->body << setw(17) << left << car_tab->engine_type
		<< setw(22) << left << car_tab->engine_capacity << setw(12) << left << car_tab->power << setw(14) << left << car_tab->gearbox << setw(16) << left
		<< car_tab->production_year << setw(8) << left << car_tab->weight << setw(10) << left << car_tab->price;
	return os;
}

void read_workers(Worker ** worker_tab, int & workers_counter) {
	for (int i = 0; i < workers_counter; ++i) {
		if (worker_tab[i] != NULL) {
			worker_tab[i]->delete_person();
			worker_tab[i] = NULL;
		}
	}
	fstream worker_file;
	int counter = 0;
	worker_file.open("workers.txt", ios::in);
	if (worker_file.good()) {
		string temporary;
		getline(worker_file, temporary);
		while (!worker_file.eof()) {
			string name, surname, month, email, street, city, ID, PESEL;
			int day, year;
			worker_file >> name >> surname >> city >> street >> email >> day >> month >> year >> PESEL >> ID;
			worker_tab[counter] = new Worker(name, surname, month, email, street, city, day, year, PESEL, ID);
			counter++;
			if (counter == 5) {
				break;
			}
		}
		worker_file.close();
		workers_counter = counter;
		cout << "Poprawnie odczytano dane z pliku!" << endl;
	}
	else {
		cout << "Brak pliku z pracownikami!" << endl;
	}
	_getch();
}

void read_cars(Car ** car_tab, int &car_counter, int max_car_amount) {
	for (int i = 0; i < max_car_amount; ++i) {
		if (car_tab[i] != NULL) {
			delete car_tab[i];
		}
	}
	fstream car_file;
	int counter = 0;
	car_file.open("cars.txt", ios::in);
	if (car_file.good()) {
		string temporary;
		getline(car_file, temporary);
		while (!car_file.eof()) {
			string brand, model, body, engine_type, gearbox, body_color;
			int production_year, price, power, weight;
			double engine_capacity;
			car_file >> brand >> model >> body >> engine_type >> engine_capacity >> power >> gearbox >> production_year >> weight >> price;
			car_tab[counter] = new Car(brand, model, body, engine_type, gearbox, body_color, production_year, price, power, engine_capacity, weight);
			++counter;
			if (counter == 30) {
				break;
			}
		}
		car_file.close();
		car_counter = counter;
		cout << "Poprawnie odczytano dane z pliku!" << endl;
	}
	else {
		cout << "Brak pliku!" << endl;
	}
	_getch;
}

void read_car_with_number(Car **car_tab, int number) {
	if (car_tab[number] != NULL && number < 30 && number > -1) {
		cout << setw(12) << left << "Marka" << setw(10) << left << "Model" << setw(16) << left << "Typ nadwozia" << setw(17) << left << "Typ silnika" << setw(22) << left << "Pojemnosc silnika"
			<< setw(12) << left << "Moc (KM)" << setw(14) << left << "Typ skrzyni" << setw(16) << left << "Rok produkcji" << setw(8) << left << "Masa" << setw(10) << left << "Cena" << endl;
		cout << car_tab[number] << endl;
	}
	else {
		string exception = "wykroczono poza zakres tablicy lub tablica pusta!";
		throw exception;
	}
	_getch();
}