/*
Meno a priezvisko:

POKYNY:
(1)  Subor premenujte na Priezvisko_Meno_ID_du06.cpp (pouzite vase udaje bez diakritiky).
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
#include <cstring>
#include <cassert>

using namespace std;

//-------------------------------------------------------------------------------------------------
// ULOHA (0.1 boda)
//-------------------------------------------------------------------------------------------------
/*
	Do deklaracie funkcie doplnte implicitne hodnoty parametrov.
	Pre parameter 'a' nech je implicitna hodnota 10,
	pre parameter 'b' nech je implicitna hodnota 20.
*/
int sucet(int a = 10, int b = 20) {
	return a + b;
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.9 boda)
//-------------------------------------------------------------------------------------------------
/*
	Trieda 'String' reprezentuje textovy retazec. Doplnte jej implementaciu podla zadania nizsie.

	Trieda implementuje textovy retazec, polom prvkov typu 'char', zakoncenym hodnotou '\0' (ako v jazyku C).
	Adresa tohoto pola je ulozena v atribute 'data'.
	Atribut 'data' musi byt sukromny (v casti 'private').
	Ak do implementacie triedy budete pridavat dalsie atributy, tak atribut 'data' musi zostat ako prvy atribut
	(pridanie dalsich atributov nie je nutne).

	Vytvorte verejne (v casti public) konstruktory, destruktory a metody (kazda poduloha je za 0.1 boda):

	a)  Vytvorte konstruktor bez parametrov.
		Tento konstruktor vytvori objekt reprezentujuci prazdny textovy retazec.

	b)  Vytvorte konstruktor s parametrom typu 'const char *'.
		Tento konstruktor vytvori objekt reprezentujuci textovy retazec, ktory je kopiou vstupneho parametra.

	c)  Vytvorte kopirovaci konstruktor. Tento konstruktor vytvori hlboku kopiu.

	d)  Vytvorte metodu 'size_t getLength() const', ktora vrati pocet znakov v textovom retazci (bez '\0').

	e)  Vytvorte metodu 'char getChar(const size_t index) const'.
		Vstupny parameter je indexom znaku v textovom retazci (prvy znak je na pozicii s indexom nula).
		Metoda vratich znak, ktory sa nachadza na mieste urcenom indexom.
		Ak je 'index' mimo rozsahu, alebo textovy retazec neobsahuje ziadne znaky, tak metoda vrati '\0'.

	f)  Vytvorte metodu 'const char * toCString() const'.
		Metoda vrati smernik na C-ckovsku reprezentaciu textoveho retazca.
		Implementacia je jednoducha, metoda vrati adresu v atribute 'data' (kopiu adresy).
		Poznamka: Kedze (konstantny) typ navratvej hodnoty zabranuje zmene obsahu textoveho retazca, nevytvarajte kopiu textu.

	g)  Vytvorte metodu 'void set(const char *text)',
		ktora nastavi novu hodnotu textoveho retazca podla vstupneho parametra.
		Nezabudnite dealokovat nepotrebnu pamat.

	h)  Vytvorte metodu 'void append(const char *text)', ktora prida na koniec 'text', ktory je vstupnym parametrom.
		Nezabudnite dealokovat nepotrebnu pamat.

	i)  Vytvorte destruktor, ktory v pripade potreby dealokuje pamat.

	Pre alokaciu a dealokaciu poli pouzivajte new[] a delete[].

	Funkcia 'basicTestString' je urcena na test spravnej deklaracie konstruktorov, metod a destruktora.
	Postupne v nej odkomentuj jednotlive riadky. Tieto musia byt po dokonceni vypracovania kompilovatelne.
	Funkcia testuje spravnost funkcnosti len ciastocne. Vytvorte dalsie testy pre overenenie funkcnosti.
*/

class String { // Prve tri riadky deklaracie triedy musia zostat nezmenene
private:
	char *data; // obsah textoveho retazca (ak pridate dalsie atributy, tak tento musi zostat prvym atributom)
public:
	String() {
		data = new char[1];
		data[0] = '\0';
	}

	String(const char* text) {
		if (text) {
			data = new char[std::strlen(text) + 1];
			std::strcpy(data, text);
		}
		else {
			data = new char[1];
			data[0] = '\0';
		}
	}

	String(const String &original) {
		data = new char[original.getLength() + 1];
		std::strcpy(data, original.data);
	}

	size_t getLength() const {
		return std::strlen(data);
	}

	char getChar(const size_t index) const {
		if (index < getLength()) {
			return data[index];
		}
		else {
			return '\0';
		}
	}

	const char * toCString() const {
		return data;
	}

	void set(const char *text) {
		if (text) {
			delete[] data;
			data = new char[std::strlen(text) + 1];
			std::strcpy(data, text);
		}
	}

	void append(const char *text) {
		if (text) {
			char *newData = new char[getLength() + std::strlen(text) + 1];
			std::strcpy(newData, data);
			std::strcat(newData, text);
			delete[] data;
			data = newData;
		}
	}

	~String() {
		delete[] data;
	}
};

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

void basicTestString() {
	// a)
	String str1;

	//b)
	String str2("hello world");

	// c)
	String str3(str2);

	// d)
	size_t length1 = str1.getLength();
	assert(length1 == 0);
	size_t length2 = str2.getLength();
	assert(length2 == 11);

	// e)
	char letter1 = str1.getChar(0);
	assert(letter1 == '\0');
	char letter2 = str2.getChar(0);
	assert(letter2 == 'h');
	char letter3 = str2.getChar(1000);
	assert(letter3 == '\0');

	// f)
	const char *cstr1 = str1.toCString();
	assert(cstr1[0] == '\0');
	const char *cstr2 = str2.toCString();
	assert(std::strcmp(cstr2, "hello world") == 0);

	// g)
	str2.set("HELLO WORLD AGAIN");
	assert(std::strcmp(str2.toCString(), "HELLO WORLD AGAIN") == 0);

	// h)
	str2.append("dalsi text");
	assert(std::strcmp(str2.toCString(), "HELLO WORLD AGAINdalsi text") == 0);

	assert(std::strcmp(str3.toCString(), "hello world") == 0);
}

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {

	// tu mozete doplnit testovaci kod

	basicTestString();

	return 0;
}