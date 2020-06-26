#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
using namespace std;

LARGE_INTEGER freq, starting, ending;
double mikrosekundy;
fstream plik;
bool wersja_deweloperska;

inline double stoptimer(){
			    QueryPerformanceCounter(&ending);
                mikrosekundy = ((ending.QuadPart - starting.QuadPart)*1000000.0) / freq.QuadPart;
                cout << endl << "Czas trwania: " << setprecision(9) << mikrosekundy << endl;
                if(!wersja_deweloperska)getche();
                return mikrosekundy;
                }

//dodaj (dla tablic i list: poczatek, koniec, wybrane miejsce) - add(for arrays & lists: beginning, end, chosen position)
//usun (dla tablic i list: poczatek, koniec, wybrane miejsce)  - remove(for arrays & lists: beginning, end, chosen position)
//wyszukaj - find
//wyswietl  - display

struct tablica{
	signed int *tab;
	int rozmiar;
	tablica(){
		plik.open("dane.txt");
		if (!plik.is_open()) {cout << "Nie udalo sie otworzyc pliku!" << endl; _Exit(0);}
		plik >> rozmiar;
		int *p = new(nothrow) int[rozmiar];
		if (!p){
			cout << "Nie mozna bylo przydzielic pamieci!" << endl;
		} else {
			for (int i=0; i<rozmiar; i++){
			plik >> p[i];
			}
			tab=p;
		}
		plik.close();
	}
	tablica(int mini, int maxi, int ilosc){
		int *p = new(nothrow) int[ilosc];
		if (!p){
            cout << "Nie mozna bylo przydzielic pamieci!" << endl;
		} else {
		    rozmiar = ilosc;
            for (int i=0; i<rozmiar; i++){
			p[i] = rand() % (maxi - mini + 1) + mini;
            }
            tab=p;
		}
	}
	double dodaj_pierwszy_element(signed int element){
	    QueryPerformanceCounter(&starting);
        int *temp = new(nothrow) int[rozmiar+1];
			if (!temp){
                cout << "Nie mozna bylo przydzielic pamieci!" << endl;
			} else {
			    rozmiar++;
			    temp[0]=element;
                for (int i=1; i<rozmiar; i++){
                    temp[i]=tab[i-1];
                }
                delete[] tab;
                tab=temp;
			}
			return stoptimer();
	}
	double dodaj_ostatni_element(signed int element){
	    QueryPerformanceCounter(&starting);
	    int *temp = new(nothrow) int[rozmiar+1];
			if (!temp){
                cout << "Nie mozna bylo przydzielic pamieci!" << endl;
			} else {
                for (int i=0; i<rozmiar; i++){
                    temp[i]=tab[i];
                }
                temp[rozmiar]=element;
                delete[] tab;
                tab=temp;
                rozmiar++;
			}
			return stoptimer();
	}
	double dodaj_na_wybrana_pozycje(int pozycja, signed int element){
	    QueryPerformanceCounter(&starting);
	    if(pozycja<=rozmiar && pozycja >=0){
			int *temp = new(nothrow) int[rozmiar+1];
			if (!temp){
                cout << "Nie mozna bylo przydzielic pamieci!" << endl;
			} else {
                for (int i=0; i<pozycja; i++){
                    temp[i]=tab[i];
                }
                temp[pozycja]=element;
                for (int i=pozycja; i<rozmiar; i++){
                    temp[i+1]=tab[i];
                }
                delete[] tab;
                tab=temp;
                rozmiar++;
			}
		} else {
			cout << "Zla pozycja!" << endl;
		}
		return stoptimer();
	}
	double usun_pierwszy_element(){
            if(rozmiar==0) return 0;
            QueryPerformanceCounter(&starting);
            int *temp = new(nothrow) int[rozmiar-1];
			if (!temp){
                cout << "Nie mozna bylo przydzielic pamieci!" << endl;
			} else {
                for (int i=1; i<rozmiar; i++){
                    temp[i-1]=tab[i];
                }
                delete[] tab;
                tab=temp;
                rozmiar--;
			}
			return stoptimer();
	}
	double usun_ostatni_element(){
	    if(rozmiar==0) return 0;
	    QueryPerformanceCounter(&starting);
	    int *temp = new(nothrow) int[rozmiar-1];
			if (!temp){
                cout << "Nie mozna bylo przydzielic pamieci!" << endl;
			} else {
			    rozmiar--;
                for (int i=0; i<rozmiar; i++){
                    temp[i]=tab[i];
                }
                delete[] tab;
                tab=temp;
			}
			return stoptimer();
	}
	double usun_z_wybranej_pozycji(int pozycja){
	    QueryPerformanceCounter(&starting);
		if(pozycja<rozmiar && pozycja >=0){
			int *temp = new(nothrow) int[rozmiar-1];
			if (!temp){
                cout << "Nie mozna bylo przydzielic pamieci!" << endl;
			} else {
                for (int i=0; i<pozycja; i++){
                    temp[i]=tab[i];
                }
                for (int i=pozycja+1; i<rozmiar; i++){
                    temp[i-1]=tab[i];
                }
                delete[] tab;
                tab=temp;
                rozmiar--;
			}
		} else {
			cout << "Pozycja poza zakresem tablicy" << endl;
		}
		return stoptimer();
	}
	double wyszukaj(signed int szukane){
	    bool b = false;
	    double pierwsze;
		cout << "Szukany element jest na tych pozycjach (liczac od 0): ";
		QueryPerformanceCounter(&starting);
		for (int i=0; i<rozmiar; i++){
			if(tab[i]==szukane){
                if (b==false){
                    b=true;
                    pierwsze=stoptimer();
                } else {
                    stoptimer();
                }
				cout << "Pozycja: " << i << endl;
			}
		}
		if (b==true){
            cout << "Pierwszy taki element znaleziono po " << pierwsze << " mikrosekundach." << endl;
            return pierwsze;
		} else {
            cout << "Nie znaleziono takiego elementu." << endl;
            return 0;
		}
	}
	void wyswietl(){
	    cout << endl;
		for (int i=0; i<rozmiar; i++){
			cout << tab[i] << ", ";
		}
		cout << endl;
		getch();
	}
	void menu(){
	    signed int chwila;
	    int moment;
	    plik.open("wyniki.txt", ios::in | ios::out | ios::app);
	    do{
        system("CLS");
        cout << "Co chcesz zrobic z ta struktura danych?" << endl;
        cout << "A - dodaj pierwszy element" << endl;
        cout << "B - dodaj element na wybranej pozycji" << endl;
        cout << "C - dodaj ostatni element" << endl;
        cout << "X - usun pierwszy element" << endl;
        cout << "Y - usun element na wybranej pozycji" << endl;
        cout << "Z - usun ostatni element" << endl;
        cout << "W - wyszukaj element" << endl;
        cout << "P - pokaz zawartosc" << endl;
        switch (getche()){
        case 97:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+dodaj_pierwszy_element(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << dodaj_pierwszy_element(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---tablica, dodaj pierwszy, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 98:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            cout << "Podaj pozycje: ";
            cin >> moment;
            if(moment<0 || moment>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+dodaj_na_wybrana_pozycje(moment, chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << dodaj_na_wybrana_pozycje(moment, chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---tablica, dodaj wybrany, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 99:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+dodaj_ostatni_element(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << dodaj_ostatni_element(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---tablica, dodaj ostatni, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 120:
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+usun_pierwszy_element();
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << usun_pierwszy_element();
            plik << endl;
            plik << "---Koniec Pomiaru---tablica, usun pierwszy, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 121:
            cout << "Podaj pozycje: ";
            cin >> moment;
            if(moment<0 || moment>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+usun_z_wybranej_pozycji(moment);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << usun_z_wybranej_pozycji(moment);
            plik << endl;
            plik << "---Koniec Pomiaru---tablica, usun wybrany, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 122:
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+usun_ostatni_element();
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << usun_ostatni_element();
            plik << endl;
            plik << "---Koniec Pomiaru---tablica, usun ostatni, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 119:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+wyszukaj(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << wyszukaj(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---tablica, wyszukaj, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 112:
            wyswietl();
            break;
        case 27:
            plik.close();
            return;
        }
    }while(1);
	}
};
struct lista_dwukierunkowa_dane{
    signed int dane;
    lista_dwukierunkowa_dane *poprzedni;
    lista_dwukierunkowa_dane *nastepny;
};
struct lista_dwukierunkowa{
    lista_dwukierunkowa_dane *head;
    lista_dwukierunkowa_dane *tail;
    lista_dwukierunkowa_dane *temp1, *temp2;
    int rozmiar;
    lista_dwukierunkowa(){
		plik.open("dane.txt");
		if (!plik.is_open()) {cout << "Nie udalo sie otworzyc pliku!" << endl; _Exit(0);}
		plik >> rozmiar;
		if (rozmiar>0){
            head = new lista_dwukierunkowa_dane;
            plik >> head->dane;
            head->poprzedni = NULL;
            temp1 = head;
            if (rozmiar > 1){
                for(int i=1; i<rozmiar; i++){
                    temp2 = new lista_dwukierunkowa_dane;
                    temp1->nastepny=temp2;
                    temp2->poprzedni=temp1;
                    plik >> temp2->dane;
                    temp1=temp2;
                }
            }
            tail=temp1;
            tail->nastepny=NULL;
		}
		plik.close();
    }
    lista_dwukierunkowa(int mini, int maxi, int ilosc){
		rozmiar = ilosc;
		if (rozmiar>0){
            head = new lista_dwukierunkowa_dane;
            head->dane = rand() % (maxi - mini + 1) + mini;
            head->poprzedni = NULL;
            temp1 = head;
            if (rozmiar > 1){
                for(int i=1; i<rozmiar; i++){
                    temp2 = new lista_dwukierunkowa_dane;
                    temp1->nastepny=temp2;
                    temp2->poprzedni=temp1;
                    temp2->dane = rand() % (maxi - mini + 1) + mini;
                    temp1=temp2;
                }
            }
            tail=temp1;
            tail->nastepny=NULL;
		}
    }
    double dodaj_pierwszy_element(signed int element){
        QueryPerformanceCounter(&starting);
        temp1 = head;
        head = new lista_dwukierunkowa_dane;
        head->dane = element;
        head->nastepny = temp1;
        if(rozmiar==0) {tail = head; head->poprzedni=NULL;} else temp1->poprzedni=head;
        rozmiar++;
        return stoptimer();
	}
	double dodaj_ostatni_element(signed int element){
	    QueryPerformanceCounter(&starting);
	    temp1 = tail;
        tail = new lista_dwukierunkowa_dane;
        tail->dane = element;
        tail->poprzedni = temp1;
        if(rozmiar==0) {head = tail; tail->nastepny=NULL;} else temp1->nastepny=tail;
        rozmiar++;
        return stoptimer();
	}
	double dodaj_na_wybrana_pozycje(int pozycja, signed int element){
	    QueryPerformanceCounter(&starting);
		if(pozycja<=rozmiar && pozycja >=0){
			if (pozycja!=0 && pozycja!=rozmiar){
                temp1 = head;
                for (int i=1; i<pozycja; i++){
                    temp1=temp1->nastepny;
                }
                temp2=temp1->nastepny;
                temp1->nastepny->poprzedni=new lista_dwukierunkowa_dane;
                temp1->nastepny=temp1->nastepny->poprzedni;
                temp1->nastepny->poprzedni=temp1;
                temp1->nastepny->dane=element;
                temp1->nastepny->nastepny=temp2;
			} else {
			    if (pozycja==0){
                    temp1 = head;
                    head = new lista_dwukierunkowa_dane;
                    head->dane = element;
                    head->nastepny = temp1;
                    if(rozmiar==0) {tail = head; head->poprzedni=NULL;} else temp1->poprzedni=head;
			    } else {
                    temp1 = tail;
                    tail = new lista_dwukierunkowa_dane;
                    tail->dane = element;
                    tail->poprzedni = temp1;
                    if(rozmiar==0) {head = tail; tail->nastepny=NULL;} else temp1->nastepny=tail;
			    }
			}
			rozmiar++;
		} else {
			cout << "Nie ma takiej pozycji w liscie ani nie przylega ona z prawej strony do juz istniejacych pozycji." << endl;
		}
		return stoptimer();
	}
	double usun_pierwszy_element(){
	    if (rozmiar==0) {cout << "Nic tu nie ma!"; return 0;}
        QueryPerformanceCounter(&starting);
	    temp1 = head;
        head = head->nastepny;
        delete temp1;
        rozmiar--;
		return stoptimer();
	}
	double usun_ostatni_element(){
	    if (rozmiar==0) {cout << "Nic tu nie ma!"; return 0;}
	    QueryPerformanceCounter(&starting);
	    temp1 = tail;
        tail = tail->poprzedni;
        delete temp1;
        rozmiar--;
		return stoptimer();
	}
	double usun_z_wybranej_pozycji(int pozycja){
	    QueryPerformanceCounter(&starting);
		if(pozycja<rozmiar && pozycja >=0){
			if (pozycja!=0 && pozycja!=rozmiar-1){
                temp1 = head;
                for (int i=1; i<pozycja; i++){
                    temp1=temp1->nastepny;
                }
                temp2 = temp1->nastepny;
                temp1->nastepny=temp1->nastepny->nastepny;
                temp1->nastepny->poprzedni=temp1;
                delete temp2;
			} else {
			    if (pozycja==0){
                    temp1 = head;
                    head = head->nastepny;
                    delete temp1;
			    } else {
			        temp1 = tail;
                    tail = tail->nastepny;
                    delete temp1;
			    }
			}
			rozmiar--;
		} else {
			cout << "Nie ma takiej pozycji w liscie." << endl;
		}
		return stoptimer();
	}
	double wyszukaj(signed int szukane){
	    bool b = false;
	    double pierwsze;
		cout << "Szukany element jest na tych pozycjach (liczac od 0): ";
	    QueryPerformanceCounter(&starting);
	    temp1 = head;
	    for(int i=0; i<rozmiar; i++){
            if(temp1->dane==szukane){
                if (b==false){
                    b=true;
                    pierwsze=stoptimer();
                } else {
                    stoptimer();
                }
				cout << "Pozycja: " << i << endl;
            }
            temp1=temp1->nastepny;
	    }
	    if (b==true){
            cout << "Pierwszy taki element znaleziono po " << pierwsze << " mikrosekundach." << endl;
            return pierwsze;
		} else {
            cout << "Nie znaleziono takiego elementu." << endl;
            return 0;
		}
	}
	void wyswietl(){
	    cout << endl;
	    temp1 = head;
	    for (int i=0; i<rozmiar; i++){
            cout << temp1->dane << ", ";
            temp1=temp1->nastepny;
	    }
	    cout << endl;
	    getch();
	}
    void menu(){
	    signed int chwila;
	    int moment;
	    plik.open("wyniki.txt", ios::in | ios::out | ios::app);
	    do{
        system("CLS");
        cout << "Co chcesz zrobic z ta struktura danych?" << endl;
        cout << "A - dodaj pierwszy element" << endl;
        cout << "B - dodaj element na wybranej pozycji" << endl;
        cout << "C - dodaj ostatni element" << endl;
        cout << "X - usun pierwszy element" << endl;
        cout << "Y - usun element na wybranej pozycji" << endl;
        cout << "Z - usun ostatni element" << endl;
        cout << "W - wyszukaj element" << endl;
        cout << "P - pokaz zawartosc" << endl;
        switch (getche()){
        case 97:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+dodaj_pierwszy_element(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << dodaj_pierwszy_element(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---lista, dodaj pierwszy, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 98:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            cout << "Podaj pozycje: ";
            cin >> moment;
            if(moment<0 || moment>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+dodaj_na_wybrana_pozycje(moment, chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << dodaj_na_wybrana_pozycje(moment, chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---lista, dodaj wybrany, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 99:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+dodaj_ostatni_element(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << dodaj_ostatni_element(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---lista, dodaj ostatni, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 120:
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+usun_pierwszy_element();
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << usun_pierwszy_element();
            plik << endl;
            plik << "---Koniec Pomiaru---lista, usun pierwszy, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 121:
            cout << "Podaj pozycje: ";
            cin >> moment;
            if(moment<0 || moment>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+usun_z_wybranej_pozycji(moment);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << usun_z_wybranej_pozycji(moment);
            plik << endl;
            plik << "---Koniec Pomiaru---lista, usun wybrany, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 122:
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+usun_ostatni_element();
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << usun_ostatni_element();
            plik << endl;
            plik << "---Koniec Pomiaru---lista, usun ostatni, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 119:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+wyszukaj(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << wyszukaj(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---lista, wyszukaj, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 112:
            wyswietl();
            break;
        case 27:
            plik.close();
            return;
        }
    }while(1);
	}
};
struct kopiec_binarny_typu_maksimum{
    signed int *tab;
    signed int temp1, temp2;
    int rozmiar;
    kopiec_binarny_typu_maksimum(){
		plik.open("dane.txt");
		if (!plik.is_open()) {cout << "Nie udalo sie otworzyc pliku!" << endl; _Exit(0);}
		plik >> rozmiar;
		int *p = new(nothrow) int[rozmiar];
		if (!p){
			cout << "Nie mozna bylo przydzielic pamieci!" << endl;
		} else {
			for (int i=0; i<rozmiar; i++){
                plik >> p[i];
                temp2=i;
                while (temp2>0){
                    if(p[(temp2-1)/2]<p[temp2]){
                        temp1=p[temp2];
                        p[temp2]=p[(temp2-1)/2];
                        p[(temp2-1)/2]=temp1;
                    }
                    temp2=(temp2-1)/2;
                }
			}
			tab=p;
		}
		plik.close();
	}
    kopiec_binarny_typu_maksimum(int mini, int maxi, int ilosc){
		int *p = new(nothrow) int[ilosc];
		if (!p){
            cout << "Nie mozna bylo przydzielic pamieci!" << endl;
		} else {
		    rozmiar = ilosc;
            for (int i=0; i<rozmiar; i++){
			p[i] = rand() % (maxi - mini + 1) + mini;
			temp2=i;
                while (temp2>0){
                    if(p[(temp2-1)/2]<p[temp2]){
                        temp1=p[temp2];
                        p[temp2]=p[(temp2-1)/2];
                        p[(temp2-1)/2]=temp1;
                    }
                    temp2=(temp2-1)/2;
                }
            }
            tab=p;
		}
    }
    double dodaj (signed int element){
        QueryPerformanceCounter(&starting);
	    int *p = new(nothrow) int[rozmiar+1];
			if (!p){
                cout << "Nie mozna bylo przydzielic pamieci!" << endl;
			} else {
                for (int i=0; i<rozmiar; i++){
                    p[i]=tab[i];
                }
                p[rozmiar]=element;
                temp2=rozmiar;
                while (temp2>0){
                    if(p[(temp2-1)/2]<p[temp2]){
                        temp1=p[temp2];
                        p[temp2]=p[(temp2-1)/2];
                        p[(temp2-1)/2]=temp1;
                    }
                    temp2=(temp2-1)/2;
                }
                delete[] tab;
                tab=p;
                rozmiar++;
			}
			return stoptimer();
    }
    double usun (signed int pozycja){
        if(pozycja>rozmiar){cout << "Zla pozycja!"; return 0;}
        QueryPerformanceCounter(&starting); //zamiana z ostatnim lisciem
        temp1=tab[rozmiar-1];
        tab[rozmiar-1]=tab[pozycja];
        tab[pozycja]=temp1;
        temp1=pozycja;
	    int *temp = new(nothrow) int[rozmiar-1]; //usuwanie ostatniego liscia
			if (!temp){
                cout << "Nie mozna bylo przydzielic pamieci!" << endl;
			} else {
			    rozmiar--;
                for (int i=0; i<rozmiar; i++){
                    temp[i]=tab[i];
                }
                delete[] tab;
                tab=temp;
                while(2*temp1+1<rozmiar){ //sortowanie
                    if(2*temp1+2<rozmiar){
                        if(tab[temp1]<tab[2*temp1+1] || tab[temp1]<tab[2*temp1+2]){
                            if (tab[2*temp1+1]<tab[2*temp1+2]){
                                temp2=tab[2*temp1+2];
                                tab[2*temp1+2]=tab[temp1];
                                tab[temp1]=temp2;
                                temp1=2*temp1+2;
                            } else {
                                temp2=tab[2*temp1+1];
                                tab[2*temp1+1]=tab[temp1];
                                tab[temp1]=temp2;
                                temp1=2*temp1+1;
                            }
                        } else break;
                    } else if(tab[temp1]<tab[2*temp1+1]) {
                        temp2=tab[2*temp1+1];
                        tab[2*temp1+1]=tab[temp1];
                        tab[temp1]=temp2;
                        temp1=2*temp1+1;
                    } else break;
                }
			}
        return stoptimer();
    }
    double wyszukaj(signed int szukane){
        bool b = false;
	    double pierwsze;
		cout << "Szukany element jest na tych pozycjach (liczac od 0): ";
		QueryPerformanceCounter(&starting);
		szukanie(szukane, 0, b, pierwsze);
		if (b==true){
            cout << "Pierwszy taki element znaleziono po " << pierwsze << " mikrosekundach." << endl;
            return pierwsze;
		} else {
            cout << "Nie znaleziono takiego elementu." << endl;
            return 0;
		}
    }
    double szukanie(signed int szukane, int i, bool &b, double &pierwsze){
        if(szukane<=tab[i]){
            if(szukane==tab[i]){
                if(b==false){
                    b=true;
                    pierwsze=stoptimer();
                } else {
                    stoptimer();
                }
                cout << "Pozycja: " << i << endl;
            }
            if(2*i+1<rozmiar){
                szukanie(szukane, 2*i+1, b, pierwsze);
            }
            if(2*i+2<rozmiar){
                szukanie(szukane, 2*i+2, b, pierwsze);
            }
        }
        return pierwsze;
    }
    void wyswietl(){
        int glebokosc=0, i=0, j=1, k;
        cout << "Legenda: liczba(pozycja)->pozycja_rodzica" << endl;
        while(j<=rozmiar){
            cout << "Glebokosc " << glebokosc << ": ";
            for(k=0; k<j && i<rozmiar; k++, i++){
                cout << tab[i]<< "(" << i << ")->" << (i-1)/2 << ", ";
            }
            cout << endl;
            j=j*2;
            glebokosc++;
        }
    getch();
    }
    void menu(){
	    signed int chwila;
	    int moment;
	    plik.open("wyniki.txt", ios::in | ios::out | ios::app);
	    do{
        system("CLS");
        cout << "Co chcesz zrobic z ta struktura danych?" << endl;
        cout << "D - dodaj element" << endl;
        cout << "U - usun element z wybranej pozycji" << endl;
        cout << "W - wyszukaj element" << endl;
        cout << "P - pokaz zawartosc" << endl;
        switch (getche()){
        case 100:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+dodaj(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << dodaj(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---kopiec, dodaj, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 117:
            cout << "Podaj pozycje: ";
            cin >> moment;
            if(moment<0 || moment>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+usun(moment);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << usun(moment);
            plik << endl;
            plik << "---Koniec Pomiaru---kopiec, usun, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 119:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+wyszukaj(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << wyszukaj(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru--- kopiec, wyszukaj, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 112:
            wyswietl();
            break;
        case 27:
            plik.close();
            return;
        }
    }while(1);
	}
};
struct drzewo_czerwonoczarne_dane{
    signed int dane;
    drzewo_czerwonoczarne_dane *lewy;
    drzewo_czerwonoczarne_dane *prawy;
    drzewo_czerwonoczarne_dane *rodzic;
    bool kolor; //true - czerwony; false - czarny
};
struct drzewo_czerwonoczarne{
    int rozmiar;
    drzewo_czerwonoczarne_dane *korzen;
    drzewo_czerwonoczarne_dane *temp1, *temp2, *temp3;
    drzewo_czerwonoczarne_dane *temp4;
    bool korzenny;

    void pokazanie(drzewo_czerwonoczarne_dane *p, int &i){
    if(p==NULL){--i; return;}
    cout << p->dane;
    p->kolor?cout<<"-RED-":cout<<"-BLACK-";
    cout << i;
    if(p->rodzic!=NULL)cout << " R: " << p->rodzic->dane;
    if(p->lewy!=NULL)cout << " L: " << p->lewy->dane;
    if(p->prawy!=NULL)cout << " P: " << p->prawy->dane;
    cout << "| ";
    pokazanie(p->lewy, ++i);
    pokazanie(p->prawy, ++i);
    --i;
    }

    void wyswietl(){
    temp1=korzen;
    int i=0;
    cout << "Legenda: wierzcholek-kolor-wysokosc, korzen ma wysokosc 0" << endl;
    cout << "Dwa kolejne wierzcholki z kolejnej wysokosci sa potomkami jednego z poprzedniej," << endl;
    cout << "Liczac po kolei od pierwszego wymienionego elementu wysokosci" << endl;
    cout << "R - rodzic, P - prawy potomek, L - lewy potomek" << endl;
    pokazanie(temp1, i);
    getche();
    }

    void rotacjaR(drzewo_czerwonoczarne_dane *wierzcholek){
        int i=0;
        if(wierzcholek->rodzic!=NULL){
            if (wierzcholek->rodzic->lewy==wierzcholek){
                wierzcholek->rodzic->lewy=wierzcholek->lewy;
            } else if (wierzcholek->rodzic->prawy==wierzcholek){
                wierzcholek->rodzic->prawy=wierzcholek->lewy;
        }
        } else korzenny=true;
        wierzcholek->lewy->rodzic=wierzcholek->rodzic;
        wierzcholek->rodzic=wierzcholek->lewy;
        wierzcholek->lewy=wierzcholek->lewy->prawy;
        wierzcholek->rodzic->prawy=wierzcholek;
        if(korzenny){korzen=wierzcholek->rodzic;}
        if(wierzcholek->lewy!=NULL) wierzcholek->lewy->rodzic=wierzcholek;
        korzenny=false;
    }
    void rotacjaL(drzewo_czerwonoczarne_dane *wierzcholek){
        int i=0;
        if(wierzcholek->rodzic!=NULL){
            if (wierzcholek->rodzic->lewy==wierzcholek){
                wierzcholek->rodzic->lewy=wierzcholek->prawy;
            } else if (wierzcholek->rodzic->prawy==wierzcholek){
                wierzcholek->rodzic->prawy=wierzcholek->prawy;
        }
        } else korzenny=true;
        wierzcholek->prawy->rodzic=wierzcholek->rodzic;
        wierzcholek->rodzic=wierzcholek->prawy;
        wierzcholek->prawy=wierzcholek->prawy->lewy;
        wierzcholek->rodzic->lewy=wierzcholek;
        if(korzenny){korzen=wierzcholek->rodzic;}
        if(wierzcholek->prawy!=NULL) wierzcholek->prawy->rodzic=wierzcholek;
        korzenny=false;
    }
    drzewo_czerwonoczarne(){
        korzenny=false;
        plik.open("dane.txt");
        if (!plik.is_open()) {cout << "Nie udalo sie otworzyc pliku!" << endl; _Exit(0);}
		plik >> rozmiar;
		if (rozmiar>0){
            korzen = new drzewo_czerwonoczarne_dane;
            plik >> korzen->dane;
            korzen->rodzic=NULL;
            korzen->lewy=NULL;
            korzen->prawy=NULL;
            korzen->kolor=false;
            temp1=korzen;
            for(int i=1; i<rozmiar; i++){
                temp3=new drzewo_czerwonoczarne_dane;
                plik >> temp3->dane;
                temp3->kolor=true;
                temp1=korzen;
                while(temp1!=NULL){
                    temp2=temp1;
                    if(temp3->dane <= temp1->dane){
                        temp1=temp1->lewy;
                    } else {
                        temp1=temp1->prawy;
                    }
                }
                temp3->rodzic=temp2;
                temp3->lewy=NULL;
                temp3->prawy=NULL;
                if(temp3->dane <= temp2->dane){
                    temp2->lewy = temp3;
                } else {
                    temp2->prawy = temp3;
                }
                while(temp3->rodzic!=NULL && temp3->rodzic->rodzic!=NULL){
                    if(temp3->rodzic->kolor==false) break;
                    if(temp3->rodzic->rodzic->prawy!=NULL
                       && temp3->rodzic->rodzic->lewy!=NULL
                       && (temp3->rodzic->rodzic->prawy!=temp3->rodzic && temp3->rodzic->rodzic->lewy->kolor==true
                       || temp3->rodzic->rodzic->lewy!=temp3->rodzic && temp3->rodzic->rodzic->prawy->kolor==true)){
                        temp3->rodzic->rodzic->lewy->kolor=false;
                        temp3->rodzic->rodzic->prawy->kolor=false;
                        temp3=temp3->rodzic->rodzic;
                        if(temp3!=korzen) temp3->kolor=true;
                        continue;
                    }
                    if(temp3->rodzic->prawy==temp3
                       && temp3->rodzic->rodzic->lewy==temp3->rodzic
                       && (temp3->rodzic->rodzic->prawy==NULL
                       || (temp3->rodzic->rodzic->prawy!=NULL
                       && temp3->rodzic->rodzic->prawy->kolor==false))){
                        rotacjaL(temp3->rodzic);
                        temp3=temp3->lewy;
                    } else if(temp3->rodzic->lewy==temp3
                              && temp3->rodzic->rodzic->prawy==temp3->rodzic
                              && (temp3->rodzic->rodzic->lewy==NULL
                              || (temp3->rodzic->rodzic->lewy!=NULL
                              && temp3->rodzic->rodzic->lewy->kolor==false))){
                        rotacjaR(temp3->rodzic);
                        temp3=temp3->prawy;
                    }
                    if(temp3->rodzic!=NULL){
                        if(temp3->rodzic->lewy==temp3
                           && temp3->rodzic->rodzic->lewy==temp3->rodzic
                           && (temp3->rodzic->rodzic->prawy==NULL
                           || (temp3->rodzic->rodzic->prawy!=NULL
                           && temp3->rodzic->rodzic->prawy->kolor==false))){
                        rotacjaR(temp3->rodzic->rodzic);
                        temp3->rodzic->kolor=!temp3->rodzic->kolor;
                        temp3->rodzic->prawy->kolor=!temp3->rodzic->prawy->kolor;
                        break;
                    } else if(temp3->rodzic->prawy==temp3
                              && temp3->rodzic->rodzic->prawy==temp3->rodzic
                              && (temp3->rodzic->rodzic->lewy==NULL
                              || (temp3->rodzic->rodzic->lewy!=NULL
                              && temp3->rodzic->rodzic->lewy->kolor==false))){
                        rotacjaL(temp3->rodzic->rodzic);
                        temp3->rodzic->kolor=!temp3->rodzic->kolor;
                        temp3->rodzic->lewy->kolor=!temp3->rodzic->lewy->kolor;
                        break;
                    }
                    }
                }
            }
		}
		plik.close();
    }
    drzewo_czerwonoczarne(int mini, int maxi, int ilosc){
        korzenny=false;
		rozmiar=ilosc;
		if (rozmiar>0){
            korzen = new drzewo_czerwonoczarne_dane;
            korzen->dane=rand() % (maxi - mini + 1) + mini;
            korzen->rodzic=NULL;
            korzen->lewy=NULL;
            korzen->prawy=NULL;
            korzen->kolor=false;
            temp1=korzen;
            for(int i=1; i<rozmiar; i++){
                temp3=new drzewo_czerwonoczarne_dane;
                temp3->dane=rand() % (maxi - mini + 1) + mini;
                temp3->kolor=true;
                temp1=korzen;
                while(temp1!=NULL){
                    temp2=temp1;
                    if(temp3->dane <= temp1->dane){
                        temp1=temp1->lewy;
                    } else {
                        temp1=temp1->prawy;
                    }
                }
                temp3->rodzic=temp2;
                temp3->lewy=NULL;
                temp3->prawy=NULL;
                if(temp3->dane <= temp2->dane){
                    temp2->lewy = temp3;
                } else {
                    temp2->prawy = temp3;
                }
                while(temp3->rodzic!=NULL && temp3->rodzic->rodzic!=NULL){
                    if(temp3->rodzic->kolor==false) break;
                    if(temp3->rodzic->rodzic->prawy!=NULL
                       && temp3->rodzic->rodzic->lewy!=NULL
                       && (temp3->rodzic->rodzic->prawy!=temp3->rodzic && temp3->rodzic->rodzic->lewy->kolor==true
                       || temp3->rodzic->rodzic->lewy!=temp3->rodzic && temp3->rodzic->rodzic->prawy->kolor==true)){
                        temp3->rodzic->rodzic->lewy->kolor=false;
                        temp3->rodzic->rodzic->prawy->kolor=false;
                        temp3=temp3->rodzic->rodzic;
                        if(temp3!=korzen) temp3->kolor=true;
                        continue;
                    }
                    if(temp3->rodzic->prawy==temp3
                       && temp3->rodzic->rodzic->lewy==temp3->rodzic
                       && (temp3->rodzic->rodzic->prawy==NULL
                       || (temp3->rodzic->rodzic->prawy!=NULL
                       && temp3->rodzic->rodzic->prawy->kolor==false))){
                        rotacjaL(temp3->rodzic);
                        temp3=temp3->lewy;
                    } else if(temp3->rodzic->lewy==temp3
                              && temp3->rodzic->rodzic->prawy==temp3->rodzic
                              && (temp3->rodzic->rodzic->lewy==NULL
                              || (temp3->rodzic->rodzic->lewy!=NULL
                              && temp3->rodzic->rodzic->lewy->kolor==false))){
                        rotacjaR(temp3->rodzic);
                        temp3=temp3->prawy;
                    }
                    if(temp3->rodzic!=NULL){
                        if(temp3->rodzic->lewy==temp3
                           && temp3->rodzic->rodzic->lewy==temp3->rodzic
                           && (temp3->rodzic->rodzic->prawy==NULL
                           || (temp3->rodzic->rodzic->prawy!=NULL
                           && temp3->rodzic->rodzic->prawy->kolor==false))){
                        rotacjaR(temp3->rodzic->rodzic);
                        temp3->rodzic->kolor=!temp3->rodzic->kolor;
                        temp3->rodzic->prawy->kolor=!temp3->rodzic->prawy->kolor;
                        break;
                    } else if(temp3->rodzic->prawy==temp3
                              && temp3->rodzic->rodzic->prawy==temp3->rodzic
                              && (temp3->rodzic->rodzic->lewy==NULL
                              || (temp3->rodzic->rodzic->lewy!=NULL
                              && temp3->rodzic->rodzic->lewy->kolor==false))){
                        rotacjaL(temp3->rodzic->rodzic);
                        temp3->rodzic->kolor=!temp3->rodzic->kolor;
                        temp3->rodzic->lewy->kolor=!temp3->rodzic->lewy->kolor;
                        break;
                    }
                    }
                }
            }
		}
    }
    double dodaj(signed int element){
        QueryPerformanceCounter(&starting);
        rozmiar++;
        if (rozmiar==1){
            korzen = new drzewo_czerwonoczarne_dane;
            korzen->dane=element;
            korzen->rodzic=NULL;
            korzen->lewy=NULL;
            korzen->prawy=NULL;
            korzen->kolor=false;
        } else {
                temp3=new drzewo_czerwonoczarne_dane;
                temp3->dane=element;
                temp3->kolor=true;
                temp1=korzen;
                while(temp1!=NULL){
                    temp2=temp1;
                    if(temp3->dane <= temp1->dane){
                        temp1=temp1->lewy;
                    } else {
                        temp1=temp1->prawy;
                    }
                }
                temp3->rodzic=temp2;
                temp3->lewy=NULL;
                temp3->prawy=NULL;
                if(temp3->dane <= temp2->dane){
                    temp2->lewy = temp3;
                } else {
                    temp2->prawy = temp3;
                }
                while(temp3->rodzic!=NULL && temp3->rodzic->rodzic!=NULL){
                    if(temp3->rodzic->kolor==false) break;
                    if(temp3->rodzic->rodzic->prawy!=NULL
                       && temp3->rodzic->rodzic->lewy!=NULL
                       && (temp3->rodzic->rodzic->prawy!=temp3->rodzic && temp3->rodzic->rodzic->lewy->kolor==true
                       || temp3->rodzic->rodzic->lewy!=temp3->rodzic && temp3->rodzic->rodzic->prawy->kolor==true)){
                        temp3->rodzic->rodzic->lewy->kolor=false;
                        temp3->rodzic->rodzic->prawy->kolor=false;
                        temp3=temp3->rodzic->rodzic;
                        if(temp3!=korzen) temp3->kolor=true;
                        continue;
                    }
                    if(temp3->rodzic->prawy==temp3
                       && temp3->rodzic->rodzic->lewy==temp3->rodzic
                       && (temp3->rodzic->rodzic->prawy==NULL
                       || (temp3->rodzic->rodzic->prawy!=NULL
                       && temp3->rodzic->rodzic->prawy->kolor==false))){
                        rotacjaL(temp3->rodzic);
                        temp3=temp3->lewy;
                    } else if(temp3->rodzic->lewy==temp3
                              && temp3->rodzic->rodzic->prawy==temp3->rodzic
                              && (temp3->rodzic->rodzic->lewy==NULL
                              || (temp3->rodzic->rodzic->lewy!=NULL
                              && temp3->rodzic->rodzic->lewy->kolor==false))){
                        rotacjaR(temp3->rodzic);
                        temp3=temp3->prawy;
                    }
                    if(temp3->rodzic!=NULL){
                        if(temp3->rodzic->lewy==temp3
                           && temp3->rodzic->rodzic->lewy==temp3->rodzic
                           && (temp3->rodzic->rodzic->prawy==NULL
                           || (temp3->rodzic->rodzic->prawy!=NULL
                           && temp3->rodzic->rodzic->prawy->kolor==false))){
                        rotacjaR(temp3->rodzic->rodzic);
                        temp3->rodzic->kolor=!temp3->rodzic->kolor;
                        temp3->rodzic->prawy->kolor=!temp3->rodzic->prawy->kolor;
                        break;
                    } else if(temp3->rodzic->prawy==temp3
                              && temp3->rodzic->rodzic->prawy==temp3->rodzic
                              && (temp3->rodzic->rodzic->lewy==NULL
                              || (temp3->rodzic->rodzic->lewy!=NULL
                              && temp3->rodzic->rodzic->lewy->kolor==false))){
                        rotacjaL(temp3->rodzic->rodzic);
                        temp3->rodzic->kolor=!temp3->rodzic->kolor;
                        temp3->rodzic->lewy->kolor=!temp3->rodzic->lewy->kolor;
                        break;
                    }
                    }
                }
        }
        return stoptimer();
    }
    drzewo_czerwonoczarne_dane* szukanieDoUsuniecia(signed int szukane, drzewo_czerwonoczarne_dane *wierzcholek){
            if(szukane==wierzcholek->dane){
                return wierzcholek;
            } else{
                if(wierzcholek->lewy!=NULL && szukane<=wierzcholek->dane){
                    return szukanieDoUsuniecia(szukane, wierzcholek->lewy);
                } else
                if(wierzcholek->prawy!=NULL && szukane>wierzcholek->dane){
                    return szukanieDoUsuniecia(szukane, wierzcholek->prawy);
                }
                return NULL;
            }
    }
    double usun(signed int element){
        bool kolor_dodatkowy=true, kolor_chwilowy; //potrzebne przy usuwaniu
        cout << "Zostanie usuniete pierwsze wystapienie tej liczby, liczac od korzenia." << endl;
        if(rozmiar==0) return 0;
        temp3=szukanieDoUsuniecia(element, korzen);
        if(temp3==NULL){cout << "Nie ma takiego elementu"; Sleep(2000); return 0;}
        QueryPerformanceCounter(&starting);
        rozmiar--;
        temp4=NULL;
        if(temp3->lewy==NULL && temp3->prawy==NULL){
            if(temp3!=korzen){
            if(temp3->rodzic->lewy==temp3){
                temp3->rodzic->lewy=NULL;
            } else {
                temp3->rodzic->prawy=NULL;
            }
            } else korzen=NULL;
            delete temp3;
            return stoptimer();
        }
        if(temp3->lewy==NULL){
            if(temp3!=korzen){
            if(temp3->kolor==false){
                if(temp3->prawy->kolor==true && temp3->rodzic->kolor==true){
                    temp3->prawy->kolor=false;
                }
            }
            if(temp3->rodzic->lewy==temp3){
                temp3->rodzic->lewy=temp3->prawy;
            } else {
                temp3->rodzic->prawy=temp3->prawy;
            }
            } else {korzen=temp3->prawy; korzen->kolor=false;}
            temp3->prawy->rodzic=temp3->rodzic;
            delete temp3;
        } else {
        if(temp3->prawy==NULL){
            if(temp3!=korzen){
            if(temp3->kolor==false){
                if(temp3->lewy->kolor==true && temp3->rodzic->kolor==true){
                    temp3->lewy->kolor=false;
                }
            }
            if(temp3->rodzic->lewy==temp3){
                temp3->rodzic->lewy=temp3->lewy;
            } else {
                temp3->rodzic->prawy=temp3->lewy;
            }
            } else {korzen=temp3->lewy; korzen->kolor=false;}
            temp3->lewy->rodzic=temp3->rodzic;
            delete temp3;
        } else {
        if(temp3->prawy->lewy==NULL){
            if(temp3->prawy->kolor==false){
                kolor_dodatkowy=false;
                temp1=temp3->prawy->prawy;
                if(temp1==NULL) temp4=temp3->prawy;
            }
            temp3->prawy->kolor=temp3->kolor;
            if(temp3!=korzen){
               if(temp3->rodzic->lewy==temp3){
                    temp3->rodzic->lewy=temp3->prawy;
                } else {
                    temp3->rodzic->prawy=temp3->prawy;
                }
            } else korzen=temp3->prawy;
            temp3->prawy->rodzic=temp3->rodzic;
            temp3->lewy->rodzic=temp3->prawy;
            temp3->prawy->lewy=temp3->lewy;
            delete temp3;
        } else {
            temp2=temp3->prawy;
            while(temp2->lewy!=NULL){
                temp2=temp2->lewy;
            }
            if (temp2->kolor==false){
                kolor_dodatkowy=false;
                temp1=temp2->prawy;
                if(temp1==NULL)temp4=temp2;
            }
            if(temp2->prawy!=NULL) temp2->prawy->kolor=temp2->kolor;
            temp2->kolor=temp3->kolor;
            if(temp2->rodzic->lewy==temp2){
                temp2->rodzic->lewy=temp2->prawy;
            } else {
                temp2->rodzic->prawy=temp2->prawy;
            }
            if(temp2->prawy!=NULL) temp2->prawy->rodzic=temp2->rodzic;
            if(temp3!=korzen){
                if(temp3->rodzic->lewy==temp3){
                    temp3->rodzic->lewy=temp2;
                } else {
                    temp3->rodzic->prawy=temp2;
                }
            } else korzen=temp2;
            temp2->rodzic=temp3->rodzic;
            temp3->lewy->rodzic=temp2;
            temp2->lewy=temp3->lewy;
            temp3->prawy->rodzic=temp2;
            temp2->prawy=temp3->prawy;
            delete temp3;
        }
        }
        }
        while(kolor_dodatkowy==false  && korzen!=temp1 && temp4==NULL){
            if(temp1->rodzic->lewy==temp1 && temp1->rodzic->prawy!=NULL && temp1->rodzic->prawy->kolor==true){
                rotacjaL(temp1->rodzic);
                kolor_chwilowy=temp1->rodzic->kolor;
                temp1->rodzic->kolor=temp1->rodzic->rodzic->kolor;
                temp1->rodzic->rodzic->kolor=kolor_chwilowy;
            } else
            if(temp1->rodzic->prawy==temp1 && temp1->rodzic->lewy!=NULL && temp1->rodzic->lewy->kolor==true){
                rotacjaR(temp1->rodzic);
                kolor_chwilowy=temp1->rodzic->kolor;
                temp1->rodzic->kolor=temp1->rodzic->rodzic->kolor;
                temp1->rodzic->rodzic->kolor=kolor_chwilowy;
            }
        if(temp1->rodzic->lewy==temp1 && temp1->rodzic->prawy!=NULL && temp1->rodzic->prawy->kolor==false
           && (temp1->rodzic->prawy->prawy==NULL || (temp1->rodzic->prawy->prawy!=NULL && temp1->rodzic->prawy->prawy->kolor==false))
           && (temp1->rodzic->prawy->lewy==NULL || (temp1->rodzic->prawy->lewy!=NULL && temp1->rodzic->prawy->lewy->kolor==false))){
            temp1->rodzic->prawy->kolor=true;
            temp1=temp1->rodzic;
            continue;
        } else
        if(temp1->rodzic->prawy==temp1 && temp1->rodzic->lewy!=NULL && temp1->rodzic->lewy->kolor==false
           && (temp1->rodzic->lewy->prawy==NULL || (temp1->rodzic->lewy->prawy!=NULL && temp1->rodzic->lewy->prawy->kolor==false))
           && (temp1->rodzic->lewy->lewy==NULL || (temp1->rodzic->lewy->lewy!=NULL && temp1->rodzic->lewy->lewy->kolor==false))){
           temp1->rodzic->lewy->kolor=true;
           temp1=temp1->rodzic;
           continue;
        }
        if(temp1->rodzic->lewy==temp1 && temp1->rodzic->prawy!=NULL && temp1->rodzic->prawy->kolor==false
           && (temp1->rodzic->prawy->prawy==NULL || (temp1->rodzic->prawy->prawy!=NULL && temp1->rodzic->prawy->prawy->kolor==false))
           && (temp1->rodzic->prawy->lewy!=NULL && temp1->rodzic->prawy->lewy->kolor==true)){
            kolor_chwilowy=temp1->rodzic->prawy->kolor;
            temp1->rodzic->prawy->kolor=temp1->rodzic->prawy->lewy->kolor;
            temp1->rodzic->prawy->lewy->kolor=kolor_chwilowy;
            rotacjaR(temp1->rodzic->prawy);
        } else
        if(temp1->rodzic->prawy==temp1 && temp1->rodzic->lewy!=NULL && temp1->rodzic->lewy->kolor==false
           && (temp1->rodzic->lewy->prawy!=NULL && temp1->rodzic->lewy->prawy->kolor==true)
           && (temp1->rodzic->lewy->lewy==NULL || (temp1->rodzic->lewy->lewy!=NULL && temp1->rodzic->lewy->lewy->kolor==false))){
           kolor_chwilowy=temp1->rodzic->lewy->kolor;
           temp1->rodzic->lewy->kolor=temp1->rodzic->lewy->prawy->kolor;
           temp1->rodzic->lewy->prawy->kolor=kolor_chwilowy;
           rotacjaL(temp1->rodzic->lewy);
        }
        if(temp1->rodzic->lewy==temp1 && temp1->rodzic->prawy!=NULL && temp1->rodzic->prawy->kolor==false
           && (temp1->rodzic->prawy->prawy!=NULL && temp1->rodzic->prawy->prawy->kolor==true)){
            temp1->rodzic->prawy->kolor=temp1->rodzic->kolor;
            temp1->rodzic->kolor=false;
            kolor_dodatkowy=true;
            temp1->rodzic->prawy->prawy->kolor=false;
            rotacjaL(temp1->rodzic);
        } else
        if(temp1->rodzic->prawy==temp1 && temp1->rodzic->lewy!=NULL && temp1->rodzic->lewy->kolor==false
           && (temp1->rodzic->lewy->lewy!=NULL && temp1->rodzic->lewy->lewy->kolor==true)){
            temp1->rodzic->lewy->kolor=temp1->rodzic->kolor;
            temp1->rodzic->kolor=false;
            kolor_dodatkowy=true;
            temp1->rodzic->lewy->lewy->kolor=false;
            rotacjaR(temp1->rodzic);
        }
        }
        return stoptimer();
    }
    double wyszukaj(signed int szukane){
        bool b = false;
	    double pierwsze;
		cout << "Szukany element znaleziono tyle razy: ";
		QueryPerformanceCounter(&starting);
		if(korzen!=NULL) szukanie(szukane, korzen, b, pierwsze);
		if (b==true){
            cout << "Pierwszy taki element znaleziono po " << pierwsze << " mikrosekundach." << endl;
            return pierwsze;
		} else {
            cout << "Nie znaleziono takiego elementu." << endl;
            return 0;
		}
    }
    double szukanie(signed int szukane, drzewo_czerwonoczarne_dane *wierzcholek, bool &b, double &pierwsze){
            if(szukane==wierzcholek->dane){
                if(b==false){
                    b=true;
                    pierwsze=stoptimer();
                } else {
                    stoptimer();
                }
                cout << "ZNALEZIONO" << endl;
            }
            if(wierzcholek->lewy!=NULL && szukane<=wierzcholek->dane){
                szukanie(szukane, wierzcholek->lewy, b, pierwsze);
            } else
            if(wierzcholek->prawy!=NULL && szukane>wierzcholek->dane){
                szukanie(szukane, wierzcholek->prawy, b, pierwsze);
            }
        return pierwsze;
    }
    void menu(){
	    signed int chwila;
	    int moment;
	    plik.open("wyniki.txt", ios::in | ios::out | ios::app);
	    do{
        system("CLS");
        cout << "Co chcesz zrobic z ta struktura danych?" << endl;
        cout << "D - dodaj element" << endl;
        cout << "U - usun element wybrana liczbe" << endl;
        cout << "W - wyszukaj element" << endl;
        cout << "P - pokaz zawartosc" << endl;
        switch (getche()){
        case 100:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+dodaj(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << dodaj(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru---drzewo, dodaj, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 117:
            cout << "Podaj liczbe, wierzcholek ja zawierajacy zostanie usuniety: ";
            cin >> moment;
            if(moment<0 || moment>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+usun(moment);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << usun(moment);
            plik << endl;
            plik << "---Koniec Pomiaru---drzewo, usun, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 119:
            cout << "Podaj liczbe: ";
            cin >> chwila;
            if(chwila<-1000000 || chwila>1000000){
                cout << "Poza zakresem! Nie pozwole na to!" << endl;
                _Exit(0);
            }
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+wyszukaj(chwila);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << wyszukaj(chwila);
            plik << endl;
            plik << "---Koniec Pomiaru--- drzewo, wyszukaj, rozmiar: " << rozmiar;
            plik << endl;
            break;
        case 112:
            wyswietl();
            break;
        case 27:
            plik.close();
            return;
        }
    }while(1);
	}
};
tablica *a;
lista_dwukierunkowa *b;
kopiec_binarny_typu_maksimum *c;
drzewo_czerwonoczarne *d;
void menu0();
void menu1();
void menu2a();
void menu2b();
void menu0(){
    do{
        system("CLS");
        cout << "Witaj! Program podaje czas trwania operacji w MIKROSEKUNDACH. " << endl
        << "Wersja deweloperska oblicza sredni czas, wykonujac 100 razy zadana operacje," << endl
        << "a wynik zapisuje do pliku wyniki.txt" << endl << "Jaka wersje programu chcesz wlaczyc?" << endl;
        cout << "N - Normalna" << endl;
        cout << "D - Deweloperska" << endl;
        switch (getche()){
        case 110:
            wersja_deweloperska=false;
            menu1();
            break;
        case 100:
            wersja_deweloperska=true;
            menu1();
            break;
        case 27:
            return;
        }
    }while(1);
}
void menu1(){
    do{
        system("CLS");
        cout << "Jak chcesz wczytac dane?" << endl;
        cout << "P - z Pliku dane.txt" << endl;
        cout << "L - Losowac dane" << endl;
        switch (getche()){
        case 112: menu2a();
            break;
        case 108: menu2b();
            break;
        case 27:
            return;
        }
    }while(1);
}
void menu2a(){
    do{
        system("CLS");
        cout << "Jaka strukture danych chcesz zbudowac?" << endl;
        cout << "T - Tablice" << endl;
        cout << "L - Liste dwukierunkowa" << endl;
        cout << "K - Kopiec binarny typu maksimum" << endl;
        cout << "D - drzewo czerwono-czarne" << endl;
        switch (getche()){
        case 116: a = new tablica(); a->menu(); delete a;
            break;
        case 108: b = new lista_dwukierunkowa(); b->menu(); for(int h=0; h<b->rozmiar; h++) b->usun_pierwszy_element();
            break;
        case 107: c = new kopiec_binarny_typu_maksimum(); c->menu(); delete c;
            break;
        case 100: d = new drzewo_czerwonoczarne(); d->menu(); delete d;
            break;
        case 27:
            return;
        }
    }while(1);
}
void menu2b(){
    signed int mini, maxi;
    int ilosc;
    do{
        system("CLS");
        cout << "Podaj ilosc liczb: ";
        cin >> ilosc;
        if(ilosc>1000000 || ilosc<0){
            cout << "Poza zakresem! Nie pozwole na to!" << endl;
            _Exit(0);
        }
        cout << "Podaj najmniejsza liczbe: ";
        cin >> mini;
        if(mini<-1000000 || mini>1000000){
            cout << "Poza zakresem! Nie pozwole na to!" << endl;
            _Exit(0);
        }
        cout << "Podaj najwieksza liczbe: ";
        cin >> maxi;
        if(maxi<-1000000 || maxi>1000000 || maxi<mini){
            cout << "Poza zakresem! Nie pozwole na to!" << endl;
            _Exit(0);
        }
        cout << "Jaka strukture danych chcesz zbudowac?" << endl;
        cout << "T - Tablice" << endl;
        cout << "L - Liste dwukierunkowa" << endl;
        cout << "K - Kopiec binarny typu maksimum" << endl;
        cout << "D - drzewo czerwono-czarne" << endl;
        switch (getche()){
        case 116: a = new tablica(mini, maxi, ilosc); a->menu(); delete a;
            break;
        case 108: b = new lista_dwukierunkowa(mini, maxi, ilosc); b->menu(); delete b;
            break;
        case 107: c = new kopiec_binarny_typu_maksimum(mini, maxi, ilosc); c->menu(); delete c;
            break;
        case 100: d = new drzewo_czerwonoczarne(mini, maxi, ilosc); d->menu(); delete d;
            break;
        case 27:
            return;
        }
    }while(1);
}
int main(){
    QueryPerformanceFrequency(&freq);
    menu0();
	return 0;
}
