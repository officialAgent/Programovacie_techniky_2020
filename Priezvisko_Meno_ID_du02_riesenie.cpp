/*
Meno a priezvisko:

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_du02.cpp (pouzite vase udaje bez diakritiky).
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

// Reprezentacia uzla zretazeneho zoznamu
struct Node {
	int data; // hodnota uzla
	Node* next; // adresa nasledujuceho uzla zoznamu
};

// Reprezentacia zretazeneho zoznamu
struct List {
	Node* first; // adresa prveho uzla zoznamu
};

// Uspesnost vykonania funkcie
enum class Result {
	SUCCESS, // funkcia vykonana uspesne
	FAILURE  // chyba pri vykonavani funkcie
};


//-------------------------------------------------------------------------------------------------
// ULOHA c.1 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia prida novy uzol s hodnotou 'val' na zaciatok zoznamu 'list'.

	PARAMETRE:
		[in] list - vstupny zretazeny zoznam
		[in] val - hodnota uzla pridaneho na zaciatok zoznamu

	PRIKLADY:
		list={} a val=0 ... zoznam po vykonani funkcie ... {0}
		list={-3} a val=1 ... zoznam po vykonani funkcie ... {1,-3}
		list={6,6,6,8} a val=10 ... zoznam po vykonani funkcie ... {10,6,6,6,8}
*/

// pomocna funkcia na vytvorenie noveho uzla
Node* createNode(const int val) {
	Node* newNode = new Node;
	newNode->data = val;
	newNode->next = nullptr;
	return newNode;
}

void prependNode(List* list, const int val) {
	Node* newNode = createNode(val);
	newNode->next = list->first;
	list->first = newNode;
}

//-------------------------------------------------------------------------------------------------
// ULOHA c.2 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia prida novy uzol s hodnotou 'val' na koniec zoznamu 'list'.

	PARAMETRE:
		[in] list - vstupny zretazeny zoznam
		[in] val - hodnota uzla pridaneho na koniec zoznamu

	PRIKLADY:
		list={} a val=7 ... zoznam po vykonani funkcie ... {7}
		list={0} a val=1 ... zoznam po vykonani funkcie ... {0,1}
		list={1,2,3,4,5} a val=6 ... zoznam po vykonani funkcie ... {1,2,3,4,5,6}
*/

void appendNode(List* list, const int val) {
	Node* newNode = createNode(val);
	if (!list->first) {
		list->first = newNode;
	}
	else {
		Node* tmp = list->first;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = newNode;
	}
}

//-------------------------------------------------------------------------------------------------
// ULOHA c.3 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia vytvori novy zretazeny zoznam a vyplni ho vsetkymi cislami (v zachovanom poradi),
	ktore sa nachadzaju vo vstupnom poli 'data', ktore ma dlzku 'n'.

	PARAMETRE:
		[in] data - vstupne pole cisiel
		[in] n - dlzka vstupneho pola

	RETURN:
		Vytvoreny zretazeny zoznam obsahujuci vsetky hodnoty zo vstupneho pola 'data' (v zachovanom poradi).
		V pripade prazdneho pola (dlzka 0), funkcia vrati prazdny zoznam (prazdny zoznam je taky, kde smernik 'first'
		ukazuje na 'nullptr'). V pripade neplatnej dlzky (ak je parameter 'n' zaporny), funkcia vrati 'nullptr'.

	PRIKLADY:
		data={1} a n=1 ... vrati zoznam ... {1}
		data={7,6,41,2} a n=4 ... vrati zoznam ... {7,6,41,2}
		data={3,2,1} a n=0 ... vrati zoznam ... {}
		data={6,3,9,10} a n=-7 ... vrati ... 'nullptr'
*/

List* createListFromArray(const int* data, const int n) {
	if (n < 0)
		return nullptr;
	List* list = new List;
	list->first = nullptr;
	for (int i = n - 1; i >= 0; i--) {
		prependNode(list, data[i]);
	}
	return list;
}

//-------------------------------------------------------------------------------------------------
// ULOHA c.4 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia vytvori novy symetricky zretazeny zoznam (vid priklady) podla parametra 'val'. Symetricky zoznam ma
	tvar 0,1,2,...val...2,1,0.

	PARAMETRE:
		[in] val - hodnota uzla podla, ktoreho sa vytvori novy symetricky zretazeny zoznam (uzol v strede zoznamu).

	RETURN:
		Vytvoreny zretazeny zoznam obsahujuci prvky v takom poradi, aby bol symetricky. V pripade 'val'<0, funkcia vrati
		'nullptr'.

	PRIKLADY:
		val=-31 ... vrati ... nullptr
		val=0 ... vrati zoznam ... {0}
		val=1 ... vrati zoznam ... {0,1,0}
		val=2 ... vrati zoznam ... {0,1,2,1,0}
		val=3 ... vrati zoznam ... {0,1,2,3,2,1,0}
		val=4 ... vrati zoznam ... {0,1,2,3,4,3,2,1,0}
		val=6 ... vrati zoznam ... {0,1,2,3,4,5,6,5,4,3,2,1,0}
*/

List* createSymmetricList(const int val) {
	if (val < 0)
		return nullptr;
	List* list = new List;
	list->first = nullptr;
	for (int i = 0; i <= val; i++) {
		prependNode(list, i);
	}
	for (int i = val; i > 0; i--) {
		prependNode(list, i - 1);
	}
	return list;
}


//-------------------------------------------------------------------------------------------------
// ULOHA c.5 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia odstrani (aj spravne uvolni pamat) zo vstupneho zoznamu 'list' prvy uzol.

	PARAMETRE:
		[in,out] list - vstupny zretazeny zoznam

	RETURN:
		Result::SUCCESS, ak bol prvy uzol vymazany
		Result::FAILURE, ak nebol prvy uzol vymazany (vstupny zoznam bol prazdny)

	PRIKLADY:
		list={} ... funkcia vrati Result::FAILURE
		list={5} ... zoznam po vykonani funkcie ... {} a vrati Result::SUCCESS
		list={10,10,10} ... zoznam po vykonani funkcie ... {10,10} a vrati Result::SUCCESS
		list={3,2,1} ... zoznam po vykonani funkcie ... {2,1} a vrati Result::SUCCESS
*/

Result removeFirstNode(List* list) {
	if (list->first) {
		Node* tmp = list->first->next;
		delete list->first;
		list->first = tmp;
		return Result::SUCCESS;
	}
	return Result::FAILURE;
}

//-------------------------------------------------------------------------------------------------
// ULOHA c.6 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia najde prvy uzol zretazeneho zoznamu 'list', ktory obsahuje hodnotu 'val'.

	PARAMETRE:
		[in] list - vstupny zretazeny zoznam
		[in] val - hodnota uzla, ktory sa hlada

	RETURN:
		Funkcia vrati prvy uzol, ktory obsahuje hodnotu 'val'. Ak sa taky uzol v zozname nenachadza alebo je vstupny
		zoznam prazdny, vtedy funkcia vrati 'nullptr'.

	PRIKLADY:
		list={}, val=10 ... funkcia vrati 'nullptr'
		list={2}, val=3 ... funkcia vrati 'nullptr'
		list={1,2,3,4,5,6}, val=-1 ... funkcia vrati 'nullptr'
		list={1}, val=1 ... funkcia vrati uzol s hodnotou 1
		list={5,9,18}, val=9 ... funkcia vrati uzol s hodnotou 9
*/

Node* findNodeInList(List* list, const int val) {
	Node* tmp = list->first;
	while (tmp) {
		if (tmp->data == val) {
			break;
		}
		tmp = tmp->next;
	}
	return tmp;
}

//-------------------------------------------------------------------------------------------------
// ULOHA c.7 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia zisti, ci su dva vstupne zoznamy 'list1' a 'list2' rovnake (t.j. rovnako dlhe a obsahujuce
	rovnake hodnoty uzlov v rovnakom poradi).

	PARAMETRE:
		[in] list1 - prvy zretazeny zoznam
		[in] list2 - druhy zretazeny zoznam

	RETURN:
		'true' - ak su vstupne zoznamy rovnake
		'false' - ak vstupne zoznamy nie su rovnake

	PRIKLADY:
		list1={1}
		list2={}
		Funkcia vrati 'false'.

		list1={}
		list2={5,3}
		Funkcia vrati 'false'.

		list1={}
		list2={}
		Funkcia vrati 'true'.

		list1={1}
		list2={1}
		Funkcia vrati 'true'.

		list1={4,-9,2}
		list2={4,-9,2}
		Funkcia vrati 'true'.

		list1={3,2,1}
		list2={1,2,3}
		Funkcia vrati 'false'.

		list1={2}
		list2={7,4,5}
		Funkcia vrati 'false'.
*/

bool areListsEqual(List* list1, List* list2) {
	Node* tmp1 = list1->first;
	Node* tmp2 = list2->first;
	while (tmp1 && tmp2) {
		if (tmp1->data != tmp2->data) {
			return false;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	if (tmp1 || tmp2) {
		return false;
	}
	return true;
}


//-------------------------------------------------------------------------------------------------
// ULOHA c.8 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia vytvori novy zretazeny zoznam prekopirovanim vsetkych hodnot uzlov vstupneho zoznamu 'list' v obratenom
	poradi.

	PARAMETRE:
		[in] list - vstupny zretazeny zoznam

	RETURN:
		Zretazeny oznam, ktory vznikne prekopirovanim hodnot uzlov vstupneho zoznamu 'list' v obratenom poradi.

	PRIKLADY:
		list={} ... funkcia vrati ... {} t.j. prazdny zoznam
		list={1} ... funkcia vrati ... {1}
		list={5,6} ... funkcia vrati ... {6,5}
		list={8,14,2,3} ... funkcia vrati ... {3,2,14,8}
*/

List* copyListReverse(List* list) {
	List* new_list = new List;
	new_list->first = nullptr;
	Node* tmp = list->first;
	while (tmp) {
		prependNode(new_list, tmp->data);
		tmp = tmp->next;
	}
	return new_list;
}

//-------------------------------------------------------------------------------------------------
// ULOHA c.9 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia vyhlada predchodcu zadaneho uzla 'node' vo vstupnom zretazenom zozname 'list'. Uzol 'node' je vzdy
	existujucim uzlom vstupneho zoznamu 'list'.

	PARAMETRE:
		[in] list - vstupny zretazeny zoznam
		[in] node - uzol zretazeneho zoznamu 'list', ktoreho predchodcu hladame

	RETURN:
		Uzol, ktory je predchodcom uzla 'node' v zozname 'list'. V pripade hladania predchodcu prveho uzla zoznamu,
		funkcia vrati 'nullptr'.

	PRIKLADY:
		list={4}
		node=4
		Funkcia vrati 'nullptr'.

		list={1,2,3,4,5}
		node=1
		Funkcia vrati 'nullptr'.

		list={-2,-3,56,4,41}
		node=-3
		Funkcia vrati uzol s hodnotou -2.

		list={10,54,69,82,6}
		node=6
		Funkcia vrati uzol s hodnotou 82.
*/

Node* findPreviousNode(List* list, Node* node) {
	Node* prev = nullptr;
	Node* tmp = list->first;
	while (tmp) {
		if (tmp == node) {
			return prev;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
// ULOHA c.10 (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Funkcia zduplikuje vsetky uzly vstupneho zoznamu 'list', ktore obsahuju kladnu hodnotu.

	PARAMETRE:
		[in,out] list - vstupny zretazeny zoznam

	PRIKLADY:
		list={} ... po vykonani funkcie ... {}
		list={3} ... po vykonani funkcie ... {3,3}
		list={-1,1} ... po vykonani funkcie ... {-1,1,1}
		list={-8,-9,-13} ... po vykonani funkcie ... {-8,-9,-13}
		list={1,0,-2,3,-4} ... po vykonani funkcie ... {1,1,0,-2,3,3,-4}
*/

void duplicatePositiveNodes(List* list) {
	Node* tmp = list->first;
	Node* newNode = nullptr;
	while (tmp) {
		if (tmp->data > 0) {
			newNode = createNode(tmp->data);
			newNode->next = tmp->next;
			tmp->next = newNode;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main(int argc, char** argv) {

	// tu mozete doplnit vas vlastny testovaci kod
	return 0;
}