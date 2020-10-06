#ifndef graf2_hpp
#define graf2_hpp
#include <iostream>
#include <ctime>
/*
plik zawierający klase grafu reprezentowanego za pomoca listy sasiedztwa
*/


/*
Struktura reprezentująca krwaedz, zawiera adres nastepnego wierzcholka, nr startowego wierzcholka
oraz wage krawiedzi. Struktura uzywana jest  w kalsie, aby zrealizowac liste sasiedztwa
*/
struct elem_listy{
  elem_listy * next;
  int wiesz;
  int weight;
};



class graf_lista{
elem_listy *r;                              // element pomocniczy
elem_listy *element;                        // element
elem_listy **lista_grafu;                   // realizacja listy sasiedztwa
long long *d;                               // tablica kosztu dojscia
int *p;                                     // tablica poprzednika
int size_G;                                 // ilosc krawedzi
int row_G;                                  // ilosc wierzcholkow
bool BF();                                  // metoda poboczna alg Bellmana Forda
bool *QS;                                   // zbior wieszcholkow S i Q  (do alg. Dijkstry)
bool negative_value;                        // zmienna sprawdzajaca czy jest waga ujemna
double time_D;
double time_B;

public:
bool algorithm_used;                                    // sprawdza czy alg zostal juz jakis wykrozystany. Zmiena zabespiecza zapisywaniu do pliku pustych danych/ lub segmenta
int start;                                              // wierzcholek startowy
int *stos;                                              // tablica przechowujaca sciezke
graf_lista();                                           // konstruktor
~graf_lista();                                          // dekonstruktor
void add_element(int firs_V, int final_V, int weight_edge);            // dodawanie elementu
void reserve_memory(int  edges, int vertices);          // zajecie pamieci i uzupelnienie niektorych zmiennych
void show_G();                                          // wyswietla graf
void free_memory();                                     // zwalnia pamiec
void alg_Dijkstry();                                    // algorytm szukanai MIN sciezki do wierzcholka alg. Dijkstry
long long return_total_cost(int i);                     // zwraca koszt sciezki
void BellmanFord();                                     // alg Bellmana Forda
int return_row();                                       // zwraca ilosc wierzcholkow
int return_queue(int i);                                // zwraca sciezke
double return_time_D();
double return_time_B();

};
#endif // graf2_hpp
