#ifndef funkcje_programu_hpp
#define funkcje_programu_hpp

#include <iostream>
#include "graf.hpp"
#include "graf2.hpp"
#include <fstream>
#include <string>

/*
                             bool sprawdz(....)

funkcja sprawdzajaca czy wygenerowana krawedz juz istnieje
argumetny:
int pocz  --> nr wierzcholka startowego
int kon   --> nr wierzcholka koncowego
int *tab1 --> tablica wierzcholkow poczatkowych
int *tab2 --> tablica wierzcholkow koncowych
*/
bool sprawdz(int pocz, int kon, int ile_elem, int *tab1, int *tab2 );


/*
                            funckja menu()
zwraca menu tekstowe
*/
void menu();


/*
                            bool load_graph(...)
funckja odpowiedzialna za wczytywanie danych do grafów z pliku
graf *graf_new   --> wskaznik na graf reperezentowany za pomoca macierzy sasiedztwa
graf_lista *grafnew --> wskaznik na graf reperezentowany za pomoca lisy sasiedztwa
*/
bool load_graph(graf *graf_new , graf_lista *grafnew);



/*
                            void save_to_file(...)
funckja odpowiedzialna za zapisywanie danych do pliku (kosztu i sciezki dojscia)
graf *graf_new   --> wskaznik na graf reperezentowany za pomoca macierzy sasiedztwa
graf_lista *grafnew --> wskaznik na graf reperezentowany za pomoca lisy sasiedztwa
*/
void save_to_file(graf *graff1, graf_lista *graf2);



/*
                           void generuj_plik()
funkcja generujaca plik tekstowy, ktory zwiera graf o wlasciwosciach ustalonych podczas dzialania funkcji
*/
void generuj_plik();



void generu_pliki(int amount);

#endif // funkcje_programu_hpp
