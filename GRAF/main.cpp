/*
####################################################################################################################################
# PROGRA IMPLEMENTACJI GRAFU ORAZ SZUKANIA NAJKROTSZEJ SCIEZKI POMIEDZY WIESZCHOLKAMI                                              #
#   AUTOR: WIKTOR SPRINGER                                                                                                         #
#   DATA:  04.2020                                                                                                                 #
#   PLIKI SKLADOWE:  main.cpp, graf.hpp, graf.cpp, graf2.hpp, graf2.cpp, funkcje_programu.hpp, funkcje programu.cpp                #
#                                                                                                                                  #
#                                                                                                                                  #
####################################################################################################################################
*/



#include <iostream>
#include "graf.hpp"
#include "graf2.hpp"
#include <fstream>
#include "funkcje_programu.hpp"


/*
        funkcja glowna prgramu main()
zawiera implementacje niezbednych zmiennych oraz petle oblugujaca uzytkownika

*/

int main()
{
 bool powtarzaj=true;
 bool pamiec=false;
 int opcja, ilosc_plikow;
 int licznik1=0,licznik2=0;
 double sum_M_B=0.0, average_time, sum_M_D=0.0, sum_L_B=0.0, sum_L_D=0.0;
 graf graf_1;
 graf_lista graf_2;


 while(powtarzaj){

  menu();
  std::cout<<"wybierz opcje: ";
  std::cin >> opcja;
  std::cout << std::endl;
  switch(opcja){

   case 1:
   if(pamiec==false)
   pamiec=load_graph(&graf_1, &graf_2);

   else std::cout << "Najpierw nalezy zwolnic pamiec!" << std::endl;
   break;

   case 2:
   if(pamiec==true)
   save_to_file(&graf_1, &graf_2);

   else std::cout << "Brak danych do zapisu" << std::endl;
   break;

   case 3:
   generuj_plik();
   break;

   case 4:
   if(pamiec==true){
    graf_1.free_memory();
    graf_2.free_memory();
    pamiec=false;
   }

   else  std::cout << "Pamiec jest wolna" << std::endl;
   break;

   case 5:
   if(pamiec==true){
   std::cout << "macierz sasiedstwa: " << std:: endl;
   graf_1.show_matrix();
   std::cout << "lista sasiedstwa: " << std:: endl;
   graf_2.show_G();
   }
   else std::cout <<"Graf jest pusty! najpierw wczytaj dane!" << std::endl;
   break;


   case 6:
   if(pamiec==true){
   std::cout << "macierz sasiedstwa: " << std:: endl;
   graf_1.alg_Dijkstry();
   sum_M_D+=graf_1.return_time_D();
   std::cout << "lista sasiedstwa: " << std:: endl;
   graf_2.alg_Dijkstry();
   sum_L_D+=graf_2.return_time_D();
   licznik1++;
   }
   else std::cout <<"Graf jest pusty! najpierw wczytaj dane!" << std::endl;
   break;

   case 7:
   if(pamiec==true){
   std::cout << "macierz sasiedstwa: " << std:: endl;
   graf_1.BellmanFord();
   sum_M_B+=graf_1.return_time_B();
   std::cout << "lista sasiedstwa: " << std:: endl;
   graf_2.BellmanFord();
   sum_L_B+=graf_2.return_time_B();
   licznik2++;
   }
   else std::cout <<"Graf jest pusty! najpierw wczytaj dane!" << std::endl;
   break;

   case 8:
   average_time=sum_L_B/licznik2;
   std::cout << "sredni czas Bellmana dla listy: " <<average_time << std::endl;
   average_time=sum_M_B/licznik2;
   std::cout << "sredni czas Bellmana dla macierzy: " <<average_time << std::endl;
   average_time=sum_L_D/licznik1;
   std::cout << "sredni czas Dijkstry dla listy: " <<average_time << std::endl;
   average_time=sum_M_D/licznik1;
   std::cout << "sredni czas Dijkstry dla macierzy: " <<average_time << std::endl;
   std::cout <<" ilosc wywołania Bellmana: " <<licznik2 << "    ilosc wywolan Dijkstry: " << licznik1 << std::endl;

   break;

   case 9:
   std::cout <<" wprowadz ilosc plikow: ";
   std::cin >> ilosc_plikow;
   std::cout << std::endl;
   generu_pliki(ilosc_plikow);
   break;

   case 10:
   powtarzaj=false;
   break;

   default:
   std::cout <<"bledna opcja!"<< std::endl;
  }

 }






    return 0;
}
