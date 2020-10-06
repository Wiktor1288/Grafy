#ifndef graf_hpp
#define graf_hpp
#include <iostream>
#include <ctime>

class graf{

long long size_G;       // ilosc krawedzi
int row_G;              // ilosc wierzcholkow
int **matrix_G;         // macierz sasiedstwa
long long * d;          // tablica kosztu
int * p;                // tablica poprzednika
bool *QS;               // zbior wierzcholkow S i Q
double denisty_G;       // gestosc grafu
bool negative_value;    // zmiena informujaca czy sa krawedzie o wadze ujemnej
bool BL();              // metoda pomocnicza do alg bellmana ford, sprawdza czy istnieje ujemne przejscie
double time_D;
double time_B;

public:
bool algorithm_used;                                        // zmiena informujaca czy jakis z algorytmow zostal juz uzyty
int start;                                                  // wieszcholek startowy w szukaniu najkrotszej sciezki
int *stos;                                                  // tablica zawierajaca sciezke dojscia do poszczegolnych wierzcholkow
graf();                                                     // konstruktor bezparametryczny klasy
void reserve_memory(int  k, int j);                         // metoda odpowiedzalna za zarezerwowania pamieci
void show_matrix();                                         // metoda wyswietlajaca macierz sasiedztwa
void add_data(int weight_edge, int first_V, int final_V);   // metoda odpowiedzalna za wczytanie danych (budowa grafu)
~graf();                                                    // dekonstruktor
void alg_Dijkstry();                                        // metoda algorytmy szukania MIN sciezki za pomoca alg Dijkstry
long long  return_total_cost(int i);                        // metoda zwracajaca koszt calkowity sciezki
int return_queue(int i);                                    // metoda zwracjaca sciezke dojsca do wierzcholka
int return_row();                                           // metoda zwracajac ilosc wierzcholkow grafu
void BellmanFord();                                         // metoda algorytmy szukania MIN sciezki za pomoca alg Bellmana Forda
void free_memory();                                         // metoda zwalniajaca pamiec (pozwala na ponowne uzupelnienie danych)
double return_time_D();
double return_time_B();

};
#endif
