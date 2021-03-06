/*
Meno a priezvisko:

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_du04.cpp (pouzite vase udaje bez diakritiky).
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

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Hmotnost produktu a obalu. Hmotnost zabaleneho produktu je suctom obidvoch poloziek
struct Weight {
	int product; // hmotnost produktu
	int packing; // hmotnost balenia
};

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada pole 'data'.
	Pouzije algoritmus bubble sort.
	Poradie usporiadania je od najvacsieho prvku po najmensi.

	PARAMETRE:
		[in, out] data - pole, ktore funkcia usporiada
		[in] length - pocet prvkov pola

	VSTUPNA PODMIENKA:
		ak 'length' > 0, tak 'data' ukazuje na platne pole

	PRIKLADY:
		{1,3,2} -> {3, 2, 1}
		{} -> {}
*/
void swap(int*a, int*b) {
	int c = *a;
	*a = *b;
	*b = c;
}

void bubbleSort(int *data, const size_t length) {
	for (size_t i = 1; i < length; ++i) {
		for (size_t j = 0; j < length - i; ++j) {
			if (data[j] < data[j + 1]) {
				swap(&data[j], &data[j + 1]);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada pole 'data' podla celkovej hmotnosti zabaleneho tovaru, t.j. podla suctu poloziek (product a packing).
	Pouzije algoritmus bubble sort.
	Poradie usporiadania je od najvacsieho prvku po najmensi.

	Podmienka porovnania struktur:
	Pri porovnavani prvkov funkcia scita hodnoty product a packing oboch porovnavanych struktur.
	Struktury s vacsim suctom poloziek budu po usporiadani pred strukturami s mensim suctom poloziek.

	Vzajomne usporiadanie struktur s rovnakym suctom poloziek:
	Pri bodovom hodnoteni nezalezi na vzajomnom usporiadani struktur s rovnakym suctom poloziek (aj ked hodnoty poloziek mozu byt rozne).
	Lepsie je vsak implementovat stabilne triedenie (struktury s rovnakym suctom poloziek nemenia vzajomne usporiadanie).

	PARAMETRE:
		[in, out] data - pole, ktore funkcia usporiada
		[in] length - pocet prvkov pola

	VSTUPNA PODMIENKA:
		ak 'length' > 0, tak 'data' ukazuje na platne pole

	PRIKLADY:
		{{10, 1}, {20, 2}, {5,2}} -> {{20, 2}, {10, 1},{5,2}} pretoze 20+2=22, 10+1=11, 5+2=7 a 22 > 11 > 7
		{} -> {}

	POZNAMKA:
		Priklady jednoducheho vytvorenia pola v testovacom kode:
		Weight baliky[] = {{10, 1}, {20, 2}, {5,2}};
		Weight baliky[] = {{.product = 10, .packing = 1}, {.product = 20, .packing = 2}, {.product = 5, .packing = 2}};
*/
void swap(Weight*a, Weight*b) {
	Weight c = *a;
	*a = *b;
	*b = c;
}

void bubbleSort(Weight *data, const size_t length) {
	for (size_t i = 1; i < length; ++i) {
		for (size_t j = 0; j < length - i; ++j) {
			const int weight0 = data[j].product + data[j].packing;
			const int weight1 = data[j + 1].product + data[j + 1].packing;
			if (weight0 < weight1) {
				swap(&data[j], &data[j + 1]);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Vyberie pivota a vrati jeho index.
	Pivota vyberie ako median prvkov:
	  - data[low]
	  - data[(high+low)/2]
	  - data[high-1]

	PARAMETRE:
		[in] 'data' - pole, v ktoreho casti s indexami low ... high-1, funkcia vybera pivot
		[in] 'low'  - index prveho prvku casti pola, v ktorej funkcia hlada pivot
		[in] 'high' - index za poslednym prvkom casti pola, v ktorej funkcia hlada pivot

	RETURN:
		index pivota

	VSTUPNE PODMIENKY:
		'data' ukazuje na platne pole
		'low' < 'high'

	PRIKLADY:
		data: {10, 20, 2000, 30, 1000, 40, 5000, 50, 60, 70}, low: 2, high: 7 -> return 2
		data: {10, 20, 1000, 30, 2000, 40, 5000, 50, 60, 70}, low: 2, high: 7 -> return 4
		data: {10, 20, 5000, 30, 1000, 40, 2000, 50, 60, 70}, low: 2, high: 7 -> return 6

		data: {10, 20, 1000, 30, 40, 2000, 50, 5000, 60, 70}, low: 2, high: 8 -> return 5

		data: {10, 20, 1000, 2000, 30, 40, 50},               low: 2, high: 4 -> return 3
		data: {10, 20, 2000, 1000, 30, 40, 50},               low: 2, high: 4 -> return 3

		data: {10, 20, 1000, 30, 40},                         low: 2, high: 3 -> return 2
*/
size_t getPivotIndex(const int *data, const size_t low, const size_t high)
{
	const size_t middle = (high + low) / 2;

	const int l = data[low];
	const int m = data[middle];
	const int h = data[high - 1];

	if ((l <= m && l >= h) || (l >= m && l <= h)) {
		return low;
	}
	else if ((m <= l && m >= h) || (m >= l && m <= h)) {
		return middle;
	}
	else {
		return high - 1;
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Vykona partition (cast algoritmu quick sort) a vrati novy index pivota.
	Pouzije styl algoritmu Lomuto.
	Poradie usporiadania:
		Najprv (vlavo) budu prvky vacsie alebo rovne ako pivot,
		potom pivot,
		potom (vpravo) prvky mensie ako pivot.

	PARAMETRE:
		[in, out] 'data' - pole, v ktoreho casti 'low' ... 'high'-1 bude vykonane partition
		[in] 'pivot' - index pivota (pred partition)
		[in] 'low'   - index prveho prvku casti pola, v ktorej bude vykonany partition
		[in] 'high'  - index za poslednym prvkom casti pola, v ktorej bude vykonany partition

	RETURN:
		Index pivota po vykonani partition.

	VSTUPNE PODMIENKY:
		'low' <= 'pivot' < 'high'
		(index pivota moze byt lubobolny v rozsahu 'low'...'high'-1, napriklad v pripade nahodneho vyberu)
		'data' ukazuje na platne pole

	PRIKLADY:
		1. priklad:
			vstup:  data: {10, 20, 30, 40, 50, 60, 70, 80, 90}, pivot: 5, low: 2, high: 7
			vystup: data: {10, 20, 70, 60, 50, 30, 40, 80, 90}, return 3

		2. priklad:
			vstup:  data: {10, 20, 30, 40, 50, 60, 70, 50, 80, 90}, pivot: 4, low: 2, high: 8
			vystup: data: {10, 20, 50, 60, 70, 50, 30, 40, 80, 90}, return 5
*/
size_t partition(int *data, const size_t pivot, const size_t low, const size_t high)
{
	swap(&data[pivot], &data[high - 1]);

	size_t put = low;
	size_t compare = low;
	while (compare < high) { // v cykle sa vykona aj vymena pivota
		if (data[compare] >= data[high - 1]) { // prvky s hodnotou rovnakou ako pivot budu vlavo
			swap(&data[put], &data[compare]);
			++put;
		}
		++compare;
	}

	return put - 1;
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada cast pola 'data' (s indexami 'low' ... 'high'-1)
	Pouzije algoritmus quick sort, styl Lomuto.
	Poradie usporiadania je od najvacsieho prvku po najmensi.

	PARAMETRE:
		[in] 'data' - pole, ktoreho cast funkcia usporiada
		[in] 'low'  - index prveho prvkou casti pola, ktoru funkcia usporiada
		[in] 'high' - index za posledny prvok casti pola, ktoru funkcia usporiada

	VSTUPNA PODMIENKA:
		ak 'low' < 'high', tak 'data' ukazuje na platne pole

	PRIKLAD:
		data: {1, 2, 3, 4, 5, 6, 7, 8, 9}, low: 2, high: 7 -> data: {1, 2, 7, 6, 5, 4, 3, 8, 9}
*/
void quickSort(int *data, const size_t low, const size_t high)
{
	if (low + 1 >= high) {
		return;
	}

	size_t pivot = getPivotIndex(data, low, high);

	pivot = partition(data, pivot, low, high);

	quickSort(data, low, pivot);
	quickSort(data, pivot + 1, high);
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {

	// tu mozete doplnit testovaci kod

	return 0;
}