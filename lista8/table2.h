#pragma once
#include <iostream>
#include "table.h"

using namespace std;

class Table2 {

private:

	string name;			//nazwa tablicy
	string password;		//hasło (min. 5 znaków, 1 mała litera, 1 wielka litera, 1 znak specjalny, 1 cyfra)
	int tableLength;		//długość tablicy
	int* table;				//wskaźnik na tablicę

	void fillWithFives();				//wypełnia tablicę cyfrą 5

public:

	Table2();				//konstruktor bezparametrowy z domyślnymi wartościami
	Table2(string name, int tableLength, string password);  //konstruktor z parametrami
	Table2(const Table2 &otherTable);			//konstruktor kopiujący

	~Table2();				//destruktor

	string getName();					//zwraca nazwę tablicy
	void setName(string newName);		//zmienia nazwę tablicy
	void setPassword(string newPassword);	//metoda ustawia nowe hasło (wymagania jak przy polu password)
	void changePassword(string newPassword); //metoda zmienia hasło na nowe (wymagania jak wyżej + nowe musi się różnić na dwóch pozycjach od poprzedniego)
	int getSize();						//zwraca długość tablicy
	bool setNewSize(int newSize);		//zmienia długość tablicy
	int* getTable();					//zwraca tablicę
	void setTable(int* newTable);		//ustawia nową tablicę
	Table2* cloneTable();				//klonująca obiekt (Zbędna. Powiela funkcjonalność konstruktora kopiującego)
	void setSize(int newSize);			//zmienia parametr tableLength
	void setValueAt(int position, int newValue); //ustawia nową wartość na zadanej pozycji

	Table2& operator = (const Table2 &otherTable); //operator =
	Table2 operator + (const Table2 &otherTable);	//operator + zwracający konkatenację dwóch tablic
	Table2 operator << (int position);	//operator << przesuwający tablicę o zadaną liczbę pozycji w lewo
	Table2 operator >> (int position);	//operator >> przesuwający tablicę o zadaną liczbę pozycji w prawo

	void showTable();					//wyœwietla nazwę, długość i zawartość tablicy
	bool checkPassword(string password); //sprawdza czy hasło jest poprawne
	bool checkNewPassword(string oldPassword, string newPassword); //sprawdza czy hasło różni się od poprzedniego o dwa znaki


};