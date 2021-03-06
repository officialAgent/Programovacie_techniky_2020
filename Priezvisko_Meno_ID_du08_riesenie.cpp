/*
Meno a priezvisko:

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_du08.cpp (pouzite vase udaje bez diakritiky).
(2)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(3)  Cela implementacia musi byt v tomto jednom subore.
(4)  Odovzdajte len tento (spravne premenovany) zdrojovy subor.
(5)  Program musi byt kompilovatelny.
(6)  Globalne a staticke premenne su zakazane.
(7)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
	 (nemente nazvy, navratove hodnoty ani typ a pocet parametrov v zadanych funkciach).
	 Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
	 (ak nie je v zadani ulohy uvedene inak).
(8)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo struktury.
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo struktur).
	 Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Vrati priemernu hodnotu prvkov vstupneho inicializacneho zoznamu.
	Ak inicializacny zoznam neobsahuje ziadne prvky, tak vyhodi vynimku typu 'std::invalid_argument',
	ktorej metoda 'what' vrati textovy retazec: "inicializacny zoznam je prazdny".

	V Implementacii pouzite 'std::accumulate'.

	PARAMETER:
		[in] data - zoznam prvkov

	NAVRATOVA HODNOTA:
		Priemerna hodnota prvkov vstupneho inicializacneho zoznamu

	VYNIMKA:
		Ak je inicializacny zoznam prazdny,
		tak vyhodi vynimku typu 'std::invalid_argument',
		ktorej metoda 'what' vrati vysvetlujuci popis: "inicializacny zoznam je prazdny" (dodrzte presne tento textovy retazec!)
*/

double average(const initializer_list<int> & data) {
	if (data.size() == 0) {
		throw invalid_argument("inicializacny zoznam je prazdny");
	}
	else {
		double sum = std::accumulate(data.begin(), data.end(), 0.0);
		return sum / double(data.size());
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Vrati iterator na 1. prvok zoznamu 'data' obsahujuci hodnotu 'value'
	Pozor na pripad, ked 'data' obsahuje viac prvkov s hodnotou 'value'.

	V implementacii pouzite 'std::find'.

	PARAMETRE:
		[in] data - zoznam, v ktorom funkcia hlada 1. vyskyt hodnoty 'value'
		[in] value - hodnota hladaneho prvku

	NAVRATOVA HODNOTA:
		Ak 'data' obsahuje prvok s hodnotou 'value', tak vrati konstantny iterator na 1. takyto prvok.
		Inak vrati iterator za posledny prvok 'data' (iterator 'data.cend()')
*/

list<int>::const_iterator findValue(const list<int> & data, int value) noexcept {
	return find(data.cbegin(), data.cend(), value);
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Vrati iterator na 1. prvok, ktoreho hodnota je v rozsahu <200, 400> (vratane 200 a 400).

	V implementacii pouzite funkciu 'std::find_if'.
	Pri jej volani pouzite ako jeden z argumentov funkciu 'isInRange200to400'.

	PARAMETER:
		[in] data - zoznam, v ktorom sa hlada 1. vyskyt hodnoty v rozsahu <200, 400>

	NAVRATOVA HODNOTA:
		Ak 'data' obsahuje prvok/prvky v rozsahu <200,400>, tak vrati iterator na 1. takyto prvok.
		Inak vrati iterator za posledny prvok (iterator 'data.cend()').
*/

bool isInRange200to400(const int element) noexcept {
	return element >= 200 && element <= 400;
}

list<int>::const_iterator findInRange200to400(const list<int> & data) noexcept {
	return find_if(data.cbegin(), data.cend(), &isInRange200to400);
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	V zozname 'data' nahradi vsetky hodnoty v rozsahu <200, 400> (vratane 200 a 400), hodnotou 5.

	V implementacii pouzite funkciu 'std::replace_if'.
	Pri jej volani pouzite ako jeden z argumentov funkciu 'isInRange200to400' (definovanu v zadani predchadzajuceho prikladu).

	PARAMETER:
		[in] data - zoznam, v ktorom funkcia nahradi vsetky hodnoty v rozsahu <200, 400> hodnotou 5
*/

void replace200to400by5(list<int> & data) noexcept {
	replace_if(data.begin(), data.end(), isInRange200to400, 5);
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Zvysi hodnotu kazdeho prvku vstupneho zoznamu o 1 (ku kazdej hodnote pripocita 1).

	V implementacii pouzite funkciu 'std::transform'.
	Pri jej volani pouzite ako jeden z argumentov funkciu 'increment'.

	PARAMETER:
		[in, out] data - zoznam, v ktorom funkcia zvysi hodnotu kazdeho prvku o 1
*/

int increment(int element) noexcept {
	return element + 1;
}

void incrementAll(list<int> & data) noexcept {
	transform(data.cbegin(), data.cend(), data.begin(), increment);
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//----------------------------------------------------------------------------------------------
/*
	Vstupny zoznam obsahuje celkovy pocet bodov z predmetu, pre kazdeho studenta.
	Ak je pocet bodov teste pod hranicou na lepsiu znamku (do lepsej znamky chyba 1 bod),
	tak funkcia zvysi pocet bodov o 1.
	Ak do lepsej znamky chyba viac bodov, tak funkcia nezmeni pocet bodov.

	V implementacii pouzite funkciu 'std::transform'.
	Pri jej volani pouzite ako jeden z argumentov  funkciu 'incrementPointsIfItHelps'.

	PARAMETER:
		[in, out] points - celkovy pocet bodov z predmetu, pre kazdeho studenta
						   (niektore mozu byt po vykonani funkcie inkrementovane)

	PRIKLAD:
		vstup:  { 100, 90, 91, 92, 93, 53, 54, 55, 56, 57, 91, 92 }
		vystup: { 100, 90, 92, 92, 93, 53, 54, 56, 56, 57, 92, 92 }
*/

int incrementPointsIfItHelps(int points) noexcept {
	switch (points) {
	case 91:
		return 92;
	case 82:
		return 83;
	case 73:
		return 74;
	case 64:
		return 65;
	case 55:
		return 56;
	default:
		return points;
	}
}

void helpAfterExam1(list<int> & points) noexcept {
	transform(points.begin(), points.end(), points.begin(), incrementPointsIfItHelps);
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//----------------------------------------------------------------------------------------------
/*
	Implementujte rovnaku funkcionalitu ako v predchadzajucom priklade,
	ale namiesto 'std::transform' pouzite "range-based for" cyklus, v ktorom budete volat 'incrementPointsIfItHelps'.
*/

void helpAfterExam2(list<int> & points) noexcept {
	for (int & point : points) {
		point = incrementPointsIfItHelps(point);
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Vrati novy zoznam, v ktorom hodnota kazdeho prvku je dana suctom prvkov 'data1' a 'data2' s rovnakym indexom.

	V implementacii puzite 'std::transform'.
	Pri jej volani pouzite ako jeden z argumentov 'std::plus<int>()'.

	PARAMETRE:
		[in] data1 - obsahuje scitance
		[in] data2 - obsahuje scitance

	NAVRATOVA HODNOTA:
		Zoznam, v ktorom hodnota kazdeho prvku je suctom prvkov v 'data1' a 'data2' s rovnakym indexom.

	VSTUPNA PODMIENKA:
		'data1' a 'data2' maju rovnaky pocet prvkov

	VYSTUPNA PODMENKA:
		Nech 'output' je vystupny zoznam.
		Pocet prvkov 'output' je rovnaky ako pocet prvkov 'data1' a 'data2'.
		Pre kazde i take, ze i >= 0 && i < data1.size() plati: output[i] = data1[i] + data2[i].
*/

list<int> add(const list<int> & data1, const list<int> & data2) noexcept {
	list<int> output(data1.size());
	transform(data1.begin(), data1.end(), data2.begin(), output.begin(), plus<int>());
	return output;
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada prvky vektora od najvacsieho po najmensi.

	V implementacii pouzite 'std::sort' alebo 'std::stable_sort' s parametrom 'std::greater<int>()',

	PARAMETER:
		[in, out] data - vektor, ktory funkcia usporiada
*/

void sort1(vector<int> & data) noexcept {
	// riesenie s pouzitim 'std::sort'
	sort(data.begin(), data.end(), greater<int>());

	// riesenie s pouzitim 'std::stable_sort'
	stable_sort(data.begin(), data.end(), greater<int>());
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Usporiada prvky vektora od najvacsieho po najmensi.

	V implementacii pouzite 'std::sort' alebo 'std::stable_sort' s reverznymi iteratormi.

	PARAMETER:
		[in, out] data - vektor, ktory funkcia usporiada
*/

void sort2(vector<int> & data) noexcept {
	// riesenie s pouzitim 'std::sort'
	sort(data.rbegin(), data.rend());

	// riesenie s pouzitim 'std::stable_sort'
	stable_sort(data.rbegin(), data.rend());
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {

	// tu mozete doplnit testovaci kod

	return 0;
}