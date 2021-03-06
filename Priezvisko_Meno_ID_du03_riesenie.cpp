/*
Meno a priezvisko:

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_du03.cpp (pouzite vase udaje bez diakritiky).
(2)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(3)  Cela implementacia musi byt v tomto jednom subore.
(4)  Odovzdajte len tento (spravne premenovany) zdrojovy subor.
(5)  Program musi byt kompilovatelny.
(6)  Globalne a staticke premenne su zakazane.
(7)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
	 (nemente nazvy, navratove hodnoty ani typ a pocet parametrov v zadanych funkciach).
	 Nemente implementacie hotovych pomocnych funkcii, ani implementacie zadanych datovych typov.
(8)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo struktury.
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo struktur).
	 Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
	int data; // hodnota uzla
	Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
	Node* first; // smernik na prvy uzol zoznamu
};

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada pole 'data' od najvacsieho po najmensi prvok.
	Pouzite algoritmus insertion sort.
	Usporiadanie je od najvacsieho po najmensi prvok (opacne ako na tutorialy)!

	PARAMETRE:
		[in, out] data - pole, ktore funkcia usporiada
		[in] length - pocet prvkov pola

	VSTUPNE PODMIENKY:
		'length' moze mat lubovolnu hodnotu
		'data' ukazuje na platne pole

	PRIKLADY:
		{1,3,2} -> {3, 2, 1}
		{} -> {}
*/

void insertionSort(int *data, const size_t length) {
	for (size_t i = 1; i < length; ++i) {
		int current = data[i];
		size_t j = i;
		while (j > 0 && data[j - 1] < current) {
			data[j] = data[j - 1];
			--j;
		}
		data[j] = current;
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada textove retazce v poli 'data' od najvacsieho po najmensi prvok (lexikograficky).
	Pouzite algoritmus insertion sort.
	Usporiadanie je od najvacsieho po najmensi prvok!

	 PARAMETRE:
		[in, out] data - pole, ktore funkcia usporiada.
				Pole obsahuje smerniky na textove retazce.
				Kazdy textovy retazec je ukonceny '\0'.
				Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

	VSTUPNE PODMIENKY:
		'data' obsahuje minimalne jeden smernik.
		Posledny smernik ma hodnotu 'nullptr'.

	PRIKLADY:
		{"Juraj", "Peter", "Andrej", nullptr} -> {"Peter", "Juraj", "Andrej", nullptr}
		{nullptr} -> {nullptr}

	POZNAMKY:
		Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
		const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

		Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
	if (data[0] == nullptr) {
		return;
	}
	for (size_t i = 1; data[i] != nullptr; ++i) {
		const char *current = data[i];
		size_t j = i;
		while (j > 0 && strcmp(data[j - 1], current) < 0) {
			data[j] = data[j - 1];
			--j;
		}
		data[j] = current;
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada zretazeny zoznam 'list' od najvacsieho po najmensi prvok.
	Pouzite algoritmus insertion sort.
	Usporiadanie je od najvacsieho po najmensi prvok!

	PARAMETRE:
		[in, out] list - zretazeny zoznam, ktory funkcia usporiada

	VSTUPNE PODMIENKY:
		'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
		'list' nie je 'nullptr'

	PRIKLADY:
		vstup: 2->1->3, vystup: 3->2->1
		vstup: prazdny zoznam, vystup: prazdny zoznam
*/
void insertionSort(List * list) {
	if (list->first != nullptr) { // ak zoznam obsahuje aspon jeden uzol
		// vytvorime dva zoznamy (s usporiadanymi prvkami ('sortedFirst'), neusporiadanymi prvkami ('waitingFirst'))

		// neusporiadany zoznam obsahuje vsetky uzly povodneho zoznamu okrem prveho uzla (na zaciatku sme overili ze zoznam obsahuje aspon jeden uzol)
		Node* waitingFirst = list->first->next; // druhy uzol povodneho zoznamu, alebo 'nullptr' ak povodny zoznam obsahuje jediny uzol

		// usporiadany zoznam na zaciatku obsahuje len prvy uzol povodneho zoznamu (na zaciatku sme overili ze existuje)
		Node* sortedFirst = list->first; // prvy uzol povodneho zoznamu bude na zaciatku jediny uzol usporiadaneho zoznamu
		sortedFirst->next = nullptr; // usporiadany zoznam bude mat na zaciatku prave jeden uzol

		// pokial neusporiadany zoznam obsahuje uzly
		while (waitingFirst != nullptr) {
			Node* current = waitingFirst; // prvy uzol z neusporiadaneho zoznamu (ktory zaradime do usporiadaneho zoznamu)
			waitingFirst = waitingFirst->next;

			// zaradenie prveho uzla z neusporiadaneho zoznamu do usporiadaneho zoznamu
			if (current->data > sortedFirst->data) { // ak treba uzol zaradit na zaciatok usporiadaneho zoznamu
				current->next = sortedFirst;
				sortedFirst = current;
			}
			else {                                // inak uzol treba zaradit nie na zaciatok usporiadaneho zoznamu
				Node* tmp = sortedFirst;
				while (tmp->next != nullptr && tmp->next->data > current->data) {
					tmp = tmp->next;
				}
				current->next = tmp->next;
				tmp->next = current;
			}
		}

		// usporiadany zoznam 'sortedFirst' je vyslednym usporiadanym zoznamom
		list->first = sortedFirst;
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Vykona algoritmus merge (cast algoritmu merge sort).
	Kombinuje dve susedne usporiadane casti v poli 'input' do jednej usporiadanej casti v poli 'output'
	Usporiadanie je od najvacsieho po najmensi prvok!

	PARAMETRE:
		[out] 'output' - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
		[in] 'input'   - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
						 musia byt pri volani funkcie usporiadane od najvacsieho po najmensi prvok
		[in] 'low'     - index 1. prvku lavej usporiadanej casti pola 'input'
		[in] 'middle'  - index 1. prvku pravej usporiadanej casti pola 'input'
		[in] 'high'    - index za poslednym prvkom pravej usporiadanej casti pola 'input'

	VYSTUPNE PODMIENKY:
		output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1]
		obsah 'input' sa nemeni
		prvky s indexami mensimi ako 'low' sa nemenia (v obidvoch poliach)
		prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (v obidvoch poliach)

	PRIKLAD:
		low: 4
		middle: 8
		hight: 12
		input:  {10, 20, 30, 40, 7, 5, 2, 0, 8, 4, 2, 1, 10, 20, 30, 40}
		output: {10, 20, 30, 40, 8, 7, 5, 4, 2, 2, 1, 0, 10, 20, 30, 40}
*/

void merge(int* output, const int* input, const size_t low, const size_t middle, const size_t high)
{
	size_t first = low;
	size_t second = middle;
	size_t out = low;

	while (first < middle && second < high) {
		if (input[first] >= input[second]) { // stabilne triedenie
			output[out] = input[first];
			++first;
		}
		else {
			output[out] = input[second];
			++second;
		}
		++out;
	}
	while (first < middle) {
		output[out] = input[first];
		++first;
		++out;
	}
	while (second < high) {
		output[out] = input[second];
		++second;
		++out;
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada prvky v poli 'data' od najvacsieho po najmensi.
	Pouzite algoritmus merge sort.
	Usporiadanie je od najvacsieho po najmensi prvok!

	PARAMETRE:
		[in, out] data - pole, ktore funkcia usporiada
		[int]   length - pocet prvkov pola

	VSTUPNE PODMIENKY:
		'data' ukazuje na platne pole

	PRIKLADY:
		{1,3,2} -> {3, 2, 1}
		{} -> {}

	POZNAMKA:
		Pri implementacii top-down bude vhodne vytvorit a zavolat rekurzivnu funkciu.
*/
void mergeSort(int* arrayA, int* arrayB, const size_t low, const size_t high)
{
	if (low + 1 >= high) {
		return;
	}

	const size_t middle = (high + low) / 2;

	mergeSort(arrayB, arrayA, low, middle);
	mergeSort(arrayB, arrayA, middle, high);

	merge(arrayA, arrayB, low, middle, high);
}
void mergeSort(int *data, const size_t length) {
	int* tmpArray = new int[length]; // pomocne pole
	std::memcpy(tmpArray, data, length * sizeof(int));
	mergeSort(data, tmpArray, 0, length);
	delete[] tmpArray;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {

	// tu mozete doplnit testovaci kod

	return 0;
}