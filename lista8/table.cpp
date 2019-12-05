#include "pch.h"
#include "table.h"

#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

/*-----------------------------
Konstruktory i desktruktor
-----------------------------*/

Table::Table() {
	this->name = "default_name";
	this->tableLength = 10;
	this->password = "P@ssw0rd";

	cout << "bezp: " << this->name << endl;

	this->table = new int[this->tableLength];
	fillWithFives();
}

Table::Table(string name, int tableLength, string password) {
	if (name == "" || tableLength < 1 || tableLength > 1000) {
		cout << BAD_PARAMS << endl;
		return;
	}
	else if (!checkPassword(password)) {
		cout << BAD_PASS_SET << endl;
	}
	this->name = name;
	this->tableLength = tableLength;
	this->password = password;

	cout << "parametr: " << this->name << endl;

	this->table = new int[this->tableLength];
	fillWithFives();
}

Table::Table(const Table &otherTable) {
	if (&otherTable == nullptr) {
		cout << BAD_PARAMS << endl;
		return;
	}
	this->name = otherTable.name + "_copy";
	this->password = otherTable.password;
	this->tableLength = otherTable.tableLength;
	this->table = new int[this->tableLength];

	for (int i = 0; i < this->tableLength; i++) {
		this->table[i] = otherTable.table[i];
	}

	cout << "kopiuj: " << this->name << endl;
}

Table::~Table() {
	delete[] this->table;

	cout << "usuwam: " << this->name << endl;
}

/*-----------------------------
Metody
-----------------------------*/

string Table::getName() {
	return this->name;
}

void Table::setName(string newName) {
	if (newName == "") {
		return;
	}
	this->name = newName;
}

void Table::setPassword(string newPassword) {
	if (checkPassword(newPassword)) {
		this->password = newPassword;
		cout << PASS_SETTED << endl;
	}
	else {
		cout << BAD_PASS_SET << endl;
	}
}

void Table::changePassword(string newPassword) {
	if (checkPassword(newPassword) && checkNewPassword(this->password, newPassword)) {
		this->password = newPassword;
		cout << PASS_SETTED << endl;
	}
	else {
		cout << BAD_PASS_SET << endl;
	}
}

int Table::getSize() {
	return this->tableLength;
}

bool Table::setNewSize(int newSize) {
	if (newSize < 1 || newSize > 1000) {
		cout << BAD_PARAMS << endl;
		return false;
	}
	else if (newSize < this->tableLength) {
		string answer;

		do {
			cout << WARNING_TAB_LENGTH;
			cin >> answer;
		} while (answer != "tak" && answer != "nie");

		if (answer == "nie") {
			return false;
		}

	}

	int* new_table = new int[newSize];

	for (int i = 0; i < newSize; i++) {
		if (i >= this->tableLength) {
			new_table[i] = 0;
		}
		else {
			new_table[i] = this->table[i];
		}
	}

	delete[] this->table;
	this->table = new_table;
	this->tableLength = newSize;

	return true;
}

int* Table::getTable() {
	return this->table;
}

void Table::setTable(int* newTable) {
	if (newTable == nullptr) {
		cout << BAD_PARAMS << endl;
		return;
	}
	delete[] this->table;
	this->table = newTable;
}

Table* Table::cloneTable() {
	return new Table(*this);
}

void Table::setSize(int newSize) {
	if (newSize < 1 || newSize > 1000) {
		cout << BAD_PARAMS << endl;
		return;
	}
	this->tableLength = newSize;
}

void Table::setValueAt(int position, int newValue) {
	if (position < 0 || position >= this->tableLength) {
		cout << BAD_PARAMS << endl;
		return;
	}
	this->table[position] = newValue;
}

Table Table::operator + (Table &newValue) {
	int newLength = this->tableLength + newValue.tableLength;
	Table newTable("default", newLength, "P@ssw0rd");
	copy(this->table, this->table + this->tableLength, newTable.table);
	copy(newValue.table, newValue.table + newValue.tableLength, newTable.table + this->tableLength);

	return newTable;
}

Table Table::operator << (int position) {
	if (position < 0 || position > this->tableLength) {
		cout << BAD_PARAMS << endl;
		return *this;
	}

	Table newTable("default", this->tableLength, "P@ssw0rd");
	for (int i = position; i < this->tableLength; i++) {
		newTable.table[i - position] = this->table[i];
	}
	for (int i = newTable.tableLength - position; i < newTable.tableLength; i++) {
		newTable.table[i] = 0;
	}
	return newTable;
}

Table Table::operator >> (int position) {
	if (position < 0 || position > this->tableLength) {
		cout << BAD_PARAMS << endl;
		return *this;
	}
	Table newTable("default", this->tableLength, "P@ssw0rd");
	for (int i = 0; i < position; i++) {
		newTable.table[i] = 0;
	}
	for (int i = position; i < this->tableLength; i++) {
		newTable.table[i] = this->table[i - position];
	}
	return newTable;
}

void Table::showTable() {
	cout << endl << "name: " << this->name << endl;
	cout << "length: " << this->tableLength << endl;
	for (int i = 0; i < this->tableLength; i++) {
		cout << this->table[i] << " ";
	}
	cout << endl;
}

bool Table::checkPassword(string password) {
	int score = 0; //jeśli hasło jest poprawene score == 5
	bool isNumber = false;
	bool isUpper = false;
	bool isLower = false;
	bool isSpecial = false;

	if (password.length() >= 5) {
		score++;
	}

	for (int i = 0; i < password.length(); i++) {
		if (isdigit(password[i])) {
			isNumber = true;
		}
		else if (islower(password[i])) {
			isLower = true;
		}
		else if (isupper(password[i])) {
			isUpper = true;
		}
		else {
			isSpecial = true;
		}
	}

	if (isNumber) {
		score++;
	}
	if (isUpper) {
		score++;
	}
	if (isLower) {
		score++;
	}
	if (isSpecial) {
		score++;
	}

	if (score == 5) {
		return true;
	}
	return false;
}

bool Table::checkNewPassword(string oldPassword, string newPassword) {
	bool isValid = false;
	int differenceCount = 0;
	int oldPassLength = oldPassword.length();
	int newPassLength = newPassword.length();
	int absSubstract = abs(oldPassLength - newPassLength);

	if (absSubstract >= 2) {
		isValid = true;
	}
	else if (absSubstract == 1) {
		if (newPassword.find(oldPassword) == string::npos) {
			isValid = true;
		}
	}
	else {
		for (int i = 0; i < oldPassLength; i++) {
			if (oldPassword[i] != newPassword[i]) {
				differenceCount++;
			}
		}
		if (differenceCount >= 2) {
			isValid = true;
		}
	}

	return isValid;
}

void Table::fillWithFives() {
	for (int i = 0; i < this->tableLength; i++) {
		table[i] = 5;
	}
}