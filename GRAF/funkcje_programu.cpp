#include "funkcje_programu.hpp"



bool sprawdz(int pocz, int kon, int ile_elem, int *tab1, int *tab2 )
{
    for (int i = 0; i < ile_elem; i++)
    {
        if ((tab1[i]==pocz && tab2[i] == kon) || (tab1[i]== kon && tab2[i] == pocz)) return true;
    }
    return false;
}



void menu()
{
    std::cout << "################## MENU ##################" <<std::endl;
    std::cout << "1--> wczytaj plik" <<std::endl;
    std::cout << "2--> zapis do pliku" <<std::endl;
    std::cout << "3--> generuj graf" <<std::endl;
    std::cout << "4--> zwolnij pamiec" <<std::endl;
    std::cout << "5--> budowa grafu" <<std::endl;
    std::cout << "6--> algorytm Dijkstry" <<std::endl;
    std::cout << "7--> algorytm Bellmana-Forda" <<std::endl;
    std::cout << "8--> wyświetl średni czas" <<std::endl;
    std::cout << "9--> generuj okreslona ilosc plikow" <<std::endl;

    std::cout << "10--> KONIEC DZIALANIA PROGRAMU" <<std::endl;
}


bool load_graph(graf *graf_new , graf_lista *grafnew)
{
    int ilosc_krawedzi;
	int ilosc_wierz;
	int wierz_start;
	int wierz_first;
	int wierz_final;
	int waga;
    std::ifstream plik;
    std::string nazwa_pliku;

    std::cout<<"podaj nazwe pliku: ";
    std::cin>> nazwa_pliku;
    std::cout << std::endl;
    plik.open(nazwa_pliku.c_str());

    if(plik.good())
    {

        plik >> ilosc_krawedzi;
        plik >> ilosc_wierz;
        plik >> wierz_start;
        graf_new->reserve_memory(ilosc_krawedzi,ilosc_wierz);
        grafnew->reserve_memory(ilosc_krawedzi,ilosc_wierz);

        while( !plik.eof() )
        {
            plik >> wierz_first;
            plik >> wierz_final;
            plik >> waga;
            if( plik.eof() ) break;

            grafnew->add_element(wierz_first, wierz_final, waga);
            graf_new->add_data(waga, wierz_first, wierz_final);
        }

        plik.close();
        return true;
    }

    else
    {
        std::cout<<"zla nazwa pliku!"<<std::endl;
        return false;
    }


}

void save_to_file(graf *graff1, graf_lista *graf2)
{

    std::ofstream plik;
    std::string nazwa_pliku;
    int licz, opcja;
    std::cout<<"podaj nazwe pliku: ";
    std::cin>> nazwa_pliku;
    std::cout << std::endl;
    std::cout <<"############ WYBOR GRAFU DO ZASPISU ############" << std::endl;
    std::cout <<"1--> macierz sasiedztwa                        #" << std::endl;
    std::cout <<"2--> lista sasiedztwa                          #" << std::endl;
    std::cout <<"################################################" << std::endl;
    std::cout <<"OPCJA: ";
    std::cin >> opcja;
    std::cout << std::endl;
    switch(opcja){

    case 1:
    plik.open(nazwa_pliku.c_str(),std::ios::out);

    if(plik.good() && graff1->algorithm_used==true)
    {
        plik << "wieszcholek startowy: " << graff1->start <<std::endl;

        for(int i=0; i<graff1->return_row(); i++)
        {
            licz=graff1->return_queue(i);
            plik << i << ":" << " ";
            for(int k=licz; k>-1; k--)
            plik<<graff1->stos[k] << " ";
            plik<<" KOSZT: " << graff1->return_total_cost(i);
            plik<< std::endl;
        }

        plik.close();
    }
    else std::cout<<"zla nazwa pliku, lub nie zostal uzyty zaden algorytm!"<<std::endl;
    break;


    case 2:
    plik.open(nazwa_pliku.c_str(),std::ios::out);

    if(plik.good() && graf2->algorithm_used==true)
    {
        plik << "wieszcholek startowy: " << graf2->start <<std::endl;
        for(int i=0; i<graf2->return_row(); i++)
        {
            licz=graf2->return_queue(i);
            plik << i << ":" << " ";
            for(int k=licz; k>-1; k--)
            plik<<graf2->stos[k] << " ";
            plik<<" KOSZT: " << graf2->return_total_cost(i);
            plik<< std::endl;
        }

    plik.close();
    }

    else std::cout<<"zla nazwa pliku, lub nie zostal uzyty zaden algorytm!"<<std::endl;
    break;

    default:
    std::cout << "BLEDNY WYBOR" << std::endl;

    }



}

void generuj_plik(){

    int ilosc_wierz, ilosc_krawedzi, k;
    double gestosc;


    std::ofstream plik;
    std::cout << "ilosc wieszcholkow: ";
    std::cin >> ilosc_wierz;
    std::cout << std::endl << "gestosc (50%->0.5): ";
    std::cin >> gestosc;
    std::cout << std::endl;

    ilosc_krawedzi=(gestosc*ilosc_wierz*(ilosc_wierz-1))/2;
    std::cout << ilosc_krawedzi <<std::endl;
    k=ilosc_krawedzi;
    int *tab1, *tab2;
    tab1=new int [k];
    tab2=new int [k];

     if (gestosc == 1.0 && ilosc_wierz>100)
    {
        int nr_kraw = 0;
            for (int i = 0; i < ilosc_wierz; i++)
            {
                for (int j = 0; j < ilosc_wierz; j++)
                {
                    if (i<j)
                    {
                        tab1[nr_kraw] = i;
                        tab2[nr_kraw] = j;
                        nr_kraw++;
                    }
                }
            }
    }

    else
    {

        for(int i=0; i<ilosc_krawedzi; i++)
        {
            int pier=rand()%ilosc_wierz;
            int osta=rand()%ilosc_wierz;

            if(pier!=osta)
            {
                if(!sprawdz(pier,osta,i,tab1,tab2))
                {
                    tab1[i]=pier;
                    tab2[i]=osta;
                }

                else i--;

            }

            else i--;
        }
    }





    std::string nazwa_pliku;
    std::cout<<"podaj nazwe pliku: ";
    std::cin>> nazwa_pliku;
    std::cout << std::endl;
    plik.open(nazwa_pliku.c_str());


    if(plik.good()){

        plik << ilosc_krawedzi << " " << ilosc_wierz << " " << 0 << std::endl;

        for(int i=0; i<ilosc_krawedzi; i++)
        {
            plik << tab1[i] << " " << tab2[i] << " " << rand()%40 +10 << std::endl;
        }
    }
    plik.close();
    delete [] tab1;
    delete [] tab2;
}




void generu_pliki(int amount)
{

    int ilosc_wierz, ilosc_krawedzi, k;
    double gestosc;

    std::string ss;
    std::string napis=".txt";
    std::ofstream plik;
    std::cout << "ilosc wierzcholkow: ";
    std::cin >> ilosc_wierz;
    std::cout << std::endl << "gestosc (50%->0.5): ";
    std::cin >> gestosc;
    std::cout << std::endl;

    ilosc_krawedzi=(gestosc*ilosc_wierz*(ilosc_wierz-1))/2;
    std::cout << ilosc_krawedzi <<std::endl;
    k=ilosc_krawedzi;
    int *tab1, *tab2;
    tab1=new int [k];
    tab2=new int [k];


    if(ilosc_wierz>150)
    {
           for(int j=0; j<ilosc_krawedzi; j++)
        {
            int pier=rand()%ilosc_wierz;
            int osta=rand()%ilosc_wierz;

            if(pier!=osta)
            {
                if(!sprawdz(pier,osta,j,tab1,tab2))
                {
                    tab1[j]=pier;
                    tab2[j]=osta;
                }

                else j--;

            }

            else j--;
        }
    }

    


    for(int i=1; i<=amount; i++)
    {
        if(ilosc_wierz<=150){
        for(int j=0; j<ilosc_krawedzi; j++)
        {
            int pier=rand()%ilosc_wierz;
            int osta=rand()%ilosc_wierz;

            if(pier!=osta)
            {
                if(!sprawdz(pier,osta,j,tab1,tab2))
                {
                    tab1[j]=pier;
                    tab2[j]=osta;
                }

                else j--;

            }

            else j--;
        }
        }
    
        ss=std::to_string(i);
        plik.open(ss+napis.c_str());
        if(plik.good()){

            plik << ilosc_krawedzi << " " << ilosc_wierz << " " << 0 << std::endl;

            for(int w=0; w<ilosc_krawedzi; w++)
            {
                plik << tab1[w] << " " << tab2[w] << " " << rand()%50 +5 << std::endl;
            }
        }
        plik.close();


    }

    delete [] tab1;
    delete [] tab2;
}

