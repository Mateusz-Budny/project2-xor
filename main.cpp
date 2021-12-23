#include<iostream>
using namespace std;

struct elem {
	elem* xored_wskazniki;
	int value;
};

struct List {
	elem* poczatek;
	elem* koniec;
	elem* aktualny;
};

elem* XOR(elem* e1, elem* e2) {
	return (elem*)((unsigned int)(e1) ^ (unsigned int)(e2));
}

elem* szukajNastepnikaAktualnej(elem* przedostatni, elem* ostatni, List* Lista) {
	elem* przedostatni2;
	przedostatni2 = XOR(przedostatni->xored_wskazniki, ostatni);
	if (przedostatni == Lista->aktualny)
		return ostatni;
	else
		return szukajNastepnikaAktualnej(przedostatni2, przedostatni, Lista);
}

elem* szukajPoprzednikaAktualnej(elem* pierwszy, elem* nastepny, List* Lista) {
	elem* nastepny2;
	nastepny2 = XOR(nastepny->xored_wskazniki, pierwszy);
	if (nastepny == Lista->aktualny)
		return pierwszy;
	else
		return szukajPoprzednikaAktualnej(nastepny, nastepny2, Lista);
}

bool czyPusta(List* List) {
	if (List->poczatek == NULL || List->koniec == NULL)
		return true;
	else
		return false;
}

void generujListe(List* Lista, int wartosc) {
	elem* nowy = new elem;
	nowy->value = wartosc;
	nowy->xored_wskazniki = 0;
	Lista->poczatek = nowy;
	Lista->koniec = nowy;
	Lista->aktualny = nowy;
}

void dodajNaPoczatek(List* Lista, int wartosc) {
	//pusta lista
	if (czyPusta(Lista) == true) {
		generujListe(Lista, wartosc);
	}
	//jest 1 element
	else if (Lista->poczatek == Lista->koniec) {
		elem* nowy = new elem;
		nowy->value = wartosc;
		Lista->poczatek = nowy;
		Lista->koniec->xored_wskazniki = XOR(Lista->poczatek, 0);
		Lista->poczatek->xored_wskazniki = XOR(0, Lista->koniec);
		Lista->aktualny = Lista->koniec;
	}
	//normalna sytuacja przynajmniej 2 elementy
	else {
		elem* nowy = new elem;
		nowy->value = wartosc;
		nowy->xored_wskazniki = XOR(Lista->poczatek, 0);
		Lista->poczatek->xored_wskazniki = XOR(XOR(0, Lista->poczatek->xored_wskazniki), nowy);
		Lista->poczatek = nowy;
	}
}

void dodajNakoniec(List* Lista, int wartosc) {
	//pusta lista
	if (czyPusta(Lista) == true) {
		generujListe(Lista, wartosc);
	}
	//jest 1 element
	else if (Lista->poczatek == Lista->koniec) {
		elem* nowy = new elem;
		nowy->value = wartosc;
		Lista->koniec = nowy;
		Lista->poczatek->xored_wskazniki = XOR(0, Lista->koniec);
		Lista->koniec->xored_wskazniki = XOR(Lista->poczatek, 0);
		Lista->aktualny = Lista->poczatek;
	}
	//normalna sytuacja przynajmniej 2 elementy
	else {
		elem* nowy = new elem;
		nowy->value = wartosc;
		nowy->xored_wskazniki = XOR(Lista->koniec, 0);
		Lista->koniec->xored_wskazniki = XOR(nowy, XOR(Lista->koniec->xored_wskazniki, 0));
		Lista->koniec = nowy;
	}
}

void dodajPrzedAktualny(List* Lista, int wartosc) {
	//pusta lista
	if (czyPusta(Lista) == true) {
		generujListe(Lista, wartosc);
	}
	//jest 1 element
	else if (Lista->poczatek == Lista->koniec) {
		elem* nowy = new elem;
		nowy->value = wartosc;
		Lista->poczatek = nowy;
		Lista->koniec->xored_wskazniki = XOR(Lista->poczatek, 0);
		Lista->poczatek->xored_wskazniki = XOR(0, Lista->koniec);
		Lista->aktualny = Lista->koniec;
	}
	//sa 2 elementy
	else if (Lista->poczatek == XOR(Lista->koniec->xored_wskazniki, 0)) {
		elem* nowy = new elem;
		nowy->value = wartosc;
		if (Lista->aktualny == Lista->koniec) {
			nowy->xored_wskazniki = XOR(Lista->poczatek, Lista->koniec);
			Lista->poczatek->xored_wskazniki = XOR(0, nowy);
			Lista->koniec->xored_wskazniki = XOR(nowy, 0);
			Lista->aktualny = Lista->koniec;
		}
		else if (Lista->aktualny == Lista->poczatek) {
			nowy->xored_wskazniki = XOR(Lista->poczatek, 0);
			Lista->poczatek->xored_wskazniki = XOR(XOR(0, Lista->poczatek->xored_wskazniki), nowy);
			Lista->poczatek = nowy;
			Lista->aktualny = XOR(Lista->poczatek->xored_wskazniki, 0);
		}
	}
	//normalna sytuacja przynajmniej 3 elementy
	else {
		if (Lista->aktualny == Lista->poczatek) {
			dodajNaPoczatek(Lista, wartosc);
		}
		else {
			elem* nowyElement = new elem;
			nowyElement->value = wartosc;
			elem* Poprzednik = szukajPoprzednikaAktualnej(0, Lista->poczatek, Lista);
			nowyElement->xored_wskazniki = XOR(Poprzednik, Lista->aktualny);
			Poprzednik->xored_wskazniki = XOR(XOR(Poprzednik->xored_wskazniki, Lista->aktualny), nowyElement);
			Lista->aktualny->xored_wskazniki = XOR(nowyElement, XOR(Lista->aktualny->xored_wskazniki, Poprzednik));
		}
	}
}

void zwrocAktual(List* Lista) {
	if (czyPusta(Lista) == false) {
		if (Lista->aktualny != NULL)
			cout << Lista->aktualny->value << endl;
		else
			cout << "NULL" << endl;
	}
	else
		cout << "NULL" << endl;
}

void zwrocNast(List* Lista) {
	if (czyPusta != NULL) {
		if (Lista->aktualny == Lista->koniec) {
			Lista->aktualny = Lista->poczatek;
			zwrocAktual(Lista);
		}
		else {
			if (Lista->koniec != NULL) {
				Lista->aktualny = szukajNastepnikaAktualnej(Lista->koniec, 0, Lista);
				zwrocAktual(Lista);
			}
		}
	}
	else
		cout << "NULL" << endl;
}

void zwrocPoprz(List* Lista) {
	if (czyPusta != NULL) {
		if (Lista->aktualny == Lista->poczatek) {
			Lista->aktualny = Lista->koniec;
			zwrocAktual(Lista);
		}
		else {
			Lista->aktualny = szukajPoprzednikaAktualnej(0, Lista->poczatek, Lista);
			zwrocAktual(Lista);
		}
	}
	else
		cout << "NULL" << endl;
}

void usunPierwszy(List* Lista) {
	if (Lista->poczatek == Lista->koniec) {
		Lista->poczatek = NULL;
		Lista->koniec = NULL;
		Lista->aktualny = NULL;
	}
	else {
		if (Lista->aktualny == Lista->poczatek) {
			Lista->aktualny = Lista->koniec;
		}
		elem* drugi;
		elem* trzeci;
		drugi = XOR(Lista->poczatek->xored_wskazniki, 0);
		trzeci = XOR(Lista->poczatek, drugi->xored_wskazniki);
		free(Lista->poczatek);
		Lista->poczatek = drugi;
		Lista->poczatek->xored_wskazniki = XOR(0, trzeci);
	}
}

void usunOstatni(List* Lista) {
	if (Lista->poczatek == Lista->koniec) {
		Lista->poczatek = NULL;
		Lista->koniec = NULL;
		Lista->aktualny = NULL;
	}
	else {
		if (Lista->aktualny == Lista->koniec) {
			Lista->aktualny = XOR(Lista->koniec->xored_wskazniki, 0);
		}
		elem* przedostatni;
		elem* przedprzedostatni;
		przedostatni = XOR(Lista->koniec->xored_wskazniki, 0);
		przedprzedostatni = XOR(Lista->koniec, przedostatni->xored_wskazniki);
		free(Lista->koniec);
		Lista->koniec = przedostatni;
		Lista->koniec->xored_wskazniki = XOR(0, przedprzedostatni);
	}
}

void usunAktual(List* Lista) {
	if (Lista->poczatek == Lista->koniec) {
		Lista->poczatek = NULL;
		Lista->koniec = NULL;
		Lista->aktualny = NULL;
	}
	else if (Lista->aktualny == Lista->poczatek) {
		Lista->aktualny = Lista->koniec;
		usunPierwszy(Lista);
	}
	else if (Lista->aktualny == Lista->koniec) {
		Lista->aktualny = XOR(Lista->koniec->xored_wskazniki, 0);
		usunOstatni(Lista);
	}
	else {
		elem* Poprzedni;
		elem* Nastepny;
		elem* PoprzednikPoprzednika;
		elem* NastepnikNastepnika;
		Poprzedni = szukajPoprzednikaAktualnej(0, Lista->poczatek, Lista);
		Nastepny = szukajNastepnikaAktualnej(Lista->koniec, 0, Lista);
		PoprzednikPoprzednika = XOR(Poprzedni->xored_wskazniki, Lista->aktualny);
		NastepnikNastepnika = XOR(Nastepny->xored_wskazniki, Lista->aktualny);
		Poprzedni->xored_wskazniki = XOR(PoprzednikPoprzednika, Nastepny);
		Nastepny->xored_wskazniki = XOR(Poprzedni, NastepnikNastepnika);
		free(Lista->aktualny);
		Lista->aktualny = Poprzedni;
	}
}

void usunZWartosciaA(List* Lista, elem* poprzedni, elem* biezaczy, int wartosc) {
	if (czyPusta(Lista) == false) {
		if (biezaczy->value == wartosc) {
			if (biezaczy == Lista->poczatek) {
				usunPierwszy(Lista);
				usunZWartosciaA(Lista, 0, Lista->poczatek, wartosc);
			}
			else if (biezaczy == Lista->koniec) {
				usunOstatni(Lista);
			}
			else {
				poprzedni->xored_wskazniki = XOR(XOR(poprzedni->xored_wskazniki, biezaczy), XOR(biezaczy->xored_wskazniki, poprzedni));
				XOR(biezaczy->xored_wskazniki, poprzedni)->xored_wskazniki = XOR(XOR(XOR(biezaczy->xored_wskazniki, poprzedni)->xored_wskazniki, biezaczy), poprzedni);
				if (biezaczy == Lista->aktualny)
					Lista->aktualny = poprzedni;

				usunZWartosciaA(Lista, poprzedni, XOR(biezaczy->xored_wskazniki, poprzedni), wartosc);
			}
		}
		else {
			if (biezaczy != Lista->koniec) {
				usunZWartosciaA(Lista, biezaczy, XOR(biezaczy->xored_wskazniki, poprzedni), wartosc);
			}
		}
	}
}

void drukujNormalnie(elem* poprzedni, elem* aktualny) {
	cout << aktualny->value << "  ";
	elem* nowy;
	nowy = XOR(poprzedni, aktualny->xored_wskazniki);
	if (nowy != NULL) {
		drukujNormalnie(aktualny, nowy);
	}
}

void drukujOdTylu(elem* nastepny, elem* aktualny) {
	cout << aktualny->value << "  ";
	elem* nowy;
	nowy = XOR(nastepny, aktualny->xored_wskazniki);
	if (nowy != NULL) {
		drukujOdTylu(aktualny, nowy);
	}
}

int main() {
	List Lista;
	Lista.aktualny = NULL;
	Lista.koniec = NULL;
	Lista.poczatek = NULL;
	char komenda[20];
	int znak;
	while (cin >> komenda) {

		if (!strcmp(komenda, "ADD_BEG")) {
			cin >> znak;
			dodajNaPoczatek(&Lista, znak);
		}
		else if (!strcmp(komenda, "ADD_END")) {
			cin >> znak;
			dodajNakoniec(&Lista, znak);
		}
		else if (!strcmp(komenda, "ADD_ACT")) {
			cin >> znak;
			dodajPrzedAktualny(&Lista, znak);
		}
		else if (!strcmp(komenda, "ACTUAL")) {
			zwrocAktual(&Lista);
		}
		else if (!strcmp(komenda, "NEXT")) {
			zwrocNast(&Lista);
		}
		else if (!strcmp(komenda, "PREV")) {
			zwrocPoprz(&Lista);
		}
		else if (!strcmp(komenda, "DEL_BEG")) {
			usunPierwszy(&Lista);
		}
		else if (!strcmp(komenda, "DEL_END")) {
			usunOstatni(&Lista);
		}
		else if (!strcmp(komenda, "DEL_ACT")) {
			usunAktual(&Lista);
		}
		else if (!strcmp(komenda, "DEL_VAL")) {
			cin >> znak;
			usunZWartosciaA(&Lista, 0, Lista.poczatek, znak);
		}
		else if (!strcmp(komenda, "PRINT_FORWARD")) {
			if (czyPusta(&Lista) == true)
				cout << "NULL" << endl;
			else {
				if (Lista.poczatek != NULL)
					drukujNormalnie(0, Lista.poczatek);
				cout << endl;
			}
		}
		else if (!strcmp(komenda, "PRINT_BACKWARD")) {
			if (czyPusta(&Lista) == true)
				cout << "NULL" << endl;
			else {
				if (Lista.koniec != NULL)
					drukujOdTylu(0, Lista.koniec);
				cout << endl;
			}
		}
	}
	return 0;
}
