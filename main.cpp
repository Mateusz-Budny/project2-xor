#include<iostream>
//#include<string>
using namespace std;
int LiczbaElementow = 0;
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

    elem* przedostatni2 = (elem*)malloc(sizeof(elem));
    przedostatni2 = XOR(przedostatni->xored_wskazniki, ostatni);
    if (przedostatni == Lista->aktualny)
        return ostatni;
    else if (przedostatni == NULL)
        return NULL;
    else
        return szukajNastepnikaAktualnej(przedostatni2, przedostatni, Lista);
    //return NULL;

}
elem* szukajPoprzednikaAktualnej(elem* pierwszy, elem* nastepny, List* Lista) {
    elem* nastepny2 = (elem*)malloc(sizeof(elem));
    nastepny2 = XOR(nastepny->xored_wskazniki, pierwszy);
    if (nastepny == Lista->aktualny)
        return pierwszy;
    else if (nastepny == NULL)
        return NULL;
    else
        return szukajPoprzednikaAktualnej(nastepny, nastepny2, Lista);
    //return NULL;
}
bool czyPusta(List* List) {
    if (List->poczatek == NULL || List->koniec == NULL)
        return true;
    else
        return false;

}
void generujListe(List* Lista, int wartosc) {
    elem* nowy = (elem*)malloc(sizeof(elem));
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
        elem* nowy = (elem*)malloc(sizeof(elem));
        nowy->value = wartosc;
        Lista->poczatek = nowy;
        Lista->koniec->xored_wskazniki = XOR(Lista->poczatek, 0);
        Lista->poczatek->xored_wskazniki = XOR(0, Lista->koniec);
        Lista->aktualny = Lista->koniec;
    }
    //normalna sytuacja przynajmniej 2 elementy
    else {
        elem* nowy = (elem*)malloc(sizeof(elem));
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
        elem* nowy = (elem*)malloc(sizeof(elem));
        nowy->value = wartosc;
        Lista->koniec = nowy;
        Lista->poczatek->xored_wskazniki = XOR(0, Lista->koniec);
        Lista->koniec->xored_wskazniki = XOR(Lista->poczatek, 0);
        Lista->aktualny = Lista->poczatek;
    }
    //normalna sytuacja przynajmniej 2 elementy
    else {
        elem* nowy = (elem*)malloc(sizeof(elem));
        nowy->value = wartosc;
        nowy->xored_wskazniki = XOR(Lista->koniec, 0);
        Lista->koniec->xored_wskazniki = XOR(nowy, XOR(Lista->koniec->xored_wskazniki, 0));
        Lista->koniec = nowy;
        //Lista->koniec->xored_wskazniki=XOR()

    }
}

void dodajPrzedAktualny(List* Lista, int wartosc) {
    //pusta lista
    if (czyPusta(Lista) == true) {
        generujListe(Lista, wartosc);
    }
    //jest 1 element
    else if (Lista->poczatek == Lista->koniec) {
        elem* nowy = (elem*)malloc(sizeof(elem));
        nowy->value = wartosc;
        Lista->poczatek = nowy;
        Lista->koniec->xored_wskazniki = XOR(Lista->poczatek, 0);
        Lista->poczatek->xored_wskazniki = XOR(0, Lista->koniec);
        Lista->aktualny = Lista->koniec;
    }
    //normalna sytuacja przynajmniej 2 elementy
    else {
        elem* nowyElement = (elem*)malloc(sizeof(elem));
        nowyElement->value = wartosc;
        elem* Poprzednik = szukajPoprzednikaAktualnej(0, Lista->poczatek, Lista);//(elem*)malloc(sizeof(elem));
        nowyElement->xored_wskazniki = XOR(Poprzednik, Lista->aktualny);
        Poprzednik->xored_wskazniki = XOR(XOR(Poprzednik->xored_wskazniki, Lista->aktualny), nowyElement);
        Lista->aktualny->xored_wskazniki = XOR(nowyElement, XOR(Lista->aktualny->xored_wskazniki, Poprzednik));
    }
}

void zwrocAktual(List* Lista) {
    if (czyPusta(Lista) == false) {
        if (Lista->aktualny != NULL)
            cout << Lista->aktualny->value << endl;
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
            Lista->aktualny = szukajNastepnikaAktualnej(Lista->koniec, 0, Lista);
            zwrocAktual(Lista);
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
        elem* drugi;// = (elem*)malloc(sizeof(elem));
        elem* trzeci;// = (elem*)malloc(sizeof(elem));
        drugi = XOR(Lista->poczatek->xored_wskazniki, 0);
        trzeci = XOR(Lista->poczatek, drugi->xored_wskazniki);
        free(Lista->poczatek);
        Lista->poczatek = drugi;
        Lista->poczatek->xored_wskazniki = XOR(0, trzeci);
        //cout << "element drugi ma wartosc " << drugi->value << endl;
        //cout << "element trzeci ma wartosc " << trzeci->value << endl;
        //Lista->poczatek->xored_wskazniki = XOR(0, XOR(Lista->poczatek, XOR(Lista->poczatek->xored_wskazniki, 0)->xored_wskazniki));
        //Lista->poczatek = XOR(Lista->poczatek->xored_wskazniki, 0);
    }
}

void usunOstatni(List* Lista) {
    if (Lista->poczatek == Lista->koniec) {
        Lista->poczatek = NULL;
        Lista->koniec = NULL;
        Lista->aktualny = NULL;
    }
    else {
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
    //Lista->aktualny=Lista->aktualny;
    if (Lista->poczatek == Lista->koniec) {
        Lista->poczatek = NULL;
        Lista->koniec = NULL;
        Lista->aktualny = NULL;
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
        if (Poprzedni != NULL) {
            free(Lista->aktualny);
            Lista->aktualny = Poprzedni;
        }
        else {
            free(Lista->aktualny);
            Lista->aktualny = Lista->koniec;
        }
    }
}
void usunZWartosciaA(List* Lista, int wartosc) {
    wartosc = wartosc;
}
void drukujNormalnie(elem* poprzedni, elem* aktualny) {
    cout << aktualny->value << "  ";
    elem* nowy = (elem*)malloc(sizeof(elem));
    nowy = XOR(poprzedni, aktualny->xored_wskazniki);
    if (nowy != NULL) {
        drukujNormalnie(aktualny, nowy);
    }
}

//void drukujNormalnie(List* Lista) {druk(0, Lista->poczatek);}

void drukujOdTylu(elem* nastepny, elem* aktualny) {
    cout << aktualny->value << "  ";
    elem* nowy = (elem*)malloc(sizeof(elem));
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
    /*dodajNakoniec(&Lista, 5);
    dodajNakoniec(&Lista, 6);
    dodajNakoniec(&Lista, 7);
    dodajNakoniec(&Lista, 8);
    dodajNakoniec(&Lista, 9);
    dodajNakoniec(&Lista, 10);
    drukujNormalnie(0,Lista.poczatek);*/
    //WAZNE - dostep do poprzedniego elementu
    //elem* nowy = (elem*)malloc(sizeof(elem));
    //nowy= XOR(Lista.koniec->xored_wskazniki, 0);
    //----Lista.koniec->xored_wskazniki=XOR()
    while (cin >> komenda) {

        //cout << komenda;
        //if (komenda == "ADD_BEG") {
        if (!strcmp(komenda, "ADD_BEG")) {
            cin >> znak;
            //cout << "z przodu: " << znak << endl;
            dodajNaPoczatek(&Lista, znak);
        }
        //else if (komenda == "ADD_END"){
        else if (!strcmp(komenda, "ADD_END")) {
            cin >> znak;
            //cout << "z tylu: "<<znak << endl;
            dodajNakoniec(&Lista, znak);

        }
        //else if (komenda == "ADD_ACT") {
        else if (!strcmp(komenda, "ADD_ACT")) {
            cin >> znak;
            //cout << endl << "DODALEM PRZED ACT!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            //cout << "z tylu: "<<znak << endl;
            dodajPrzedAktualny(&Lista, znak);

        }
        //else if (komenda == "ACTUAL") {
        else if (!strcmp(komenda, "ACTUAL")) {
            //cout << "3:ACTUAL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            zwrocAktual(&Lista);
            //elem* pop = (elem*)malloc(sizeof(elem));
            //pop = szukajNastepnikaAktualnej(Lista.koniec,0, &Lista);
            //cout << endl << endl << pop->value << endl << endl;
            //elem* nast = (elem*)malloc(sizeof(elem));
            //nast = szukajPoprzednikaAktualnej(0, Lista.poczatek, &Lista);
            //cout << endl << endl << nast->value << endl << endl;
            //dodajPrzedAktualny(&Lista, znak);

        }
        //else if (komenda == "NEXT") {
        else if (!strcmp(komenda, "NEXT")) {
            //cout << endl << "!!!!!!!!!!!!!!!!4:NEXT" << endl;
            zwrocNast(&Lista);
        }
        //else if (komenda == "PREV") {
        else if (!strcmp(komenda, "PREV")) {
            //cout << "5:PREV" << endl;
            zwrocPoprz(&Lista);
        }
        //else if (komenda == "DEL_BEG") {
        else if (!strcmp(komenda, "DEL_BEG")) {
            //cout << endl << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!6:DEL_BEG" << endl;
            usunPierwszy(&Lista);
        }
        //else if (komenda == "DEL_END") {
        else if (!strcmp(komenda, "DEL_END")) {
            //cout << "!!!!!!!!!!!!!!!!7:DEL_END" << endl;
            usunOstatni(&Lista);
        }
        //else if (komenda == "DEL_ACT") {
        else if (!strcmp(komenda, "DEL_ACT")) {
            //cout << "8:DEL_ACT" << endl;
            usunAktual(&Lista);
        }
        //else if (komenda == "DEL_VAL") {
        else if (!strcmp(komenda, "DEL_VAL")) {
            cin >> znak;
            //cout << "8:DEL_ACT" << endl;
            usunZWartosciaA(&Lista, znak);
        }
        //else if (komenda == "PRINT_FORWARD") {
        else if (!strcmp(komenda, "PRINT_FORWARD")) {
            //cout << "9:PRINT_FORWARD" << endl;
            if (Lista.poczatek != NULL)
                drukujNormalnie(0, Lista.poczatek);
            cout << endl;
        }
        //else if (komenda == "PRINT_BACKWARD") {
        else if (!strcmp(komenda, "PRINT_BACKWARD")) {
            //cout << "10:PRINT_BACKWARD" << endl;
            if (Lista.koniec != NULL)
                drukujOdTylu(0, Lista.koniec);
            cout << endl;
        }
    }

    return 0;
}
/*
ADD_END 1
PRINT_FORWARD
ADD_BEG 11
PRINT_FORWARD
ADD_END 12
PRINT_FORWARD
ADD_BEG 13
PRINT_FORWARD
ADD_END 14
PRINT_FORWARD
ADD_BEG 8
PRINT_FORWARD
DEL_BEG
PRINT_FORWARD
ADD_BEG 9
PRINT_FORWARD
ADD_END 9
PRINT_FORWARD
ACTUAL
ADD_BEG 10
PRINT_FORWARD
DEL_BEG
PRINT_FORWARD
ADD_BEG 36
ADD_ACT 76
PRINT_FORWARD
ACTUAL
ADD_END 18
PRINT_FORWARD
NEXT
ADD_BEG 17
PRINT_FORWARD
ADD_END 19
ADD_ACT 77
PRINT_FORWARD
ADD_BEG 97
PRINT_FORWARD
ACTUAL
ADD_END 14
PRINT_FORWARD
ADD_BEG 37
PRINT_FORWARD
ADD_END 3
ADD_END 33
ADD_END 47
ADD_END 9
PRINT_FORWARD
*/