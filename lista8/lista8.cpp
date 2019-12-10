// lista8.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "table.h"
#include "table2.h"

#include <iostream>
#include <ctime>

using namespace std;

int main() {
	double czas;
	clock_t start, koniec;

	Table myTabs[8000];

	Table2 myTabs2[8000];


	start = clock();
	for (int i = 1; i < 8000; i++) {
		myTabs[i] + move(myTabs[i-1]);
	}
	
	koniec = clock();
	czas = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania przenoszenie: " << czas << endl;

	start = clock();
	for (int i = 1; i < 8000; i++) {
		myTabs2[i] + myTabs2[i-1];
	}

	koniec = clock();
	czas = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania kopiowanie: " << czas << endl;
	Table tab3, tab4, tab5;
	tab5 = tab3 + move(tab4);
	//tab.showTable();

	//Table tab2(tab);

	//tab2.showTable();

	//Table tab3(move(tab));
	//Table tab3;
	//tab3 = move(tab);

	//tab3.showTable();
	//tab.showTable();
	//delete myTabs2;
	//delete myTabs2ToCopy;
	//delete myTabs;
	//delete myTabsToCopy;
	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
