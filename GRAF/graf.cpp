#include "graf.hpp"
#define INTMAXX  40000000

graf::graf()
{
    size_G=0;
    row_G=0;
    denisty_G=0.0;
    matrix_G=NULL;
    d=NULL;
    p=NULL;
    QS=NULL;
    stos=NULL;
    negative_value=false;
    algorithm_used=false;
}


void graf::reserve_memory(int  k, int j)
{
    size_G=k;
    row_G=j;
    double licznik=2*k, mianownik=j*(j-1);
    denisty_G=licznik/mianownik*100;

    stos=new int[row_G];
    d=new long long [row_G];
    p=new int [row_G];
    QS=new bool [row_G];

    matrix_G= new int* [row_G];

    for(int i=0; i<row_G; i++)
     matrix_G[i]= new int [row_G];


    for(int i=0; i<row_G; i++)
        for(int j=0; j<row_G; j++)
            matrix_G[i][j]= 0;
}


void graf::add_data(int weight_edge, int first_V, int final_V)
{

    matrix_G[first_V][final_V]=weight_edge;

    if(weight_edge < 0) negative_value=true;   // sprawdza czy waga ujemna
}


void graf::show_matrix()
{
    for(int i=0; i<row_G; i++)
    std::cout << i << " ";

    std::cout << std::endl;


    for(int i=0; i<row_G; i++)
    {
        std::cout << std::endl;
        for(int j=0; j<row_G; j++)
        {
            std::cout << matrix_G[i][j] << " ";
        }
    }

    std::cout << std::endl;
    std::cout << "gęstosc: " << denisty_G << "   liczba wierzcholkow: " << row_G << "   liczba krawedzi: " << size_G <<std::endl;

}


graf::~graf()
{

    delete [] d;
    delete [] p;
    delete [] QS;
    delete [] stos;

    for(int i=0; i<row_G; i++)
        delete [] matrix_G[i];


    delete [] matrix_G;
}


void graf::alg_Dijkstry()
{

    if(!negative_value)
    {
        algorithm_used=true;         // zaznaczenie ze algorytm jest wykorzystany

                // zaznaczenie ze algorytm Dijkstry
        int i,u,j, sptr=0;
        std::cout << "wpisz nr wieszcholka startowego: ";
        std::cin >> start;
        std::cout << std::endl;
        if(start<0 || start >= row_G)
        {
            std::cout << "wybrales wieszcholek spoza zakresu mozliwosci! " << std::endl;
            return;
        }
        clock_t time_req;
        time_req = clock();

        for(int i=0; i<row_G; i++)          // uzupelnie danych w poszcegolnych tablicach dynamicznych
        {
            d[i]=INTMAXX;
            p[i]=-1;
            QS[i]=false;
        }

        d[start]=0;                        // ustawienie kosztu dla wierzcholka startowego na 0


        for(i=0; i<row_G; i++)              // przegladanie sasiadow
        {

            for(j=0; QS[j]; j++);
            for(u=j++; j<row_G; j++)
                if(!QS[j] && (d[j] < d[u]))
                    u=j;


            QS [ u ] = true;

            for(int k=0; k<row_G; k++)
            {
                if(!QS[k] && (d[k]> d[u]+matrix_G[u][k]) && (matrix_G[u][k]!=0))
                {
                    d[k]=d[u]+matrix_G[u][k];
                    p[k]=u;
                }
            }
        }
        time_req = clock() - time_req;

        for( i = 0; i < row_G; i++ )                //wypisanie sciezki i kosztu
        {
            std::cout << i << ": ";

            for( j = i; j > -1; j = p [ j ] ) stos [ sptr++ ] = j;

            while( sptr ) std::cout << stos [ --sptr ] << " ";

            std::cout << "$" << d [ i ] << std::endl;
        }
        std::cout << "Using pow function, it took " << (float)time_req/CLOCKS_PER_SEC << " seconds" << std::endl ;
        time_D=(float)time_req/CLOCKS_PER_SEC;

    }

    else std::cout << "graf zawiera krawedzie o wagach ujemnych!!! algorytm ten nie moze zostac wykonany!!!!" << std::endl;


}



long long graf::return_total_cost(int i){
    return d[i];

}


int graf::return_queue(int i){
    int  sptr=0;



    for(int j=i; j!=-1; j=p[j])
                stos[sptr++]=j;


    return sptr-1;


}


int graf::return_row(){
return row_G;

}


void graf::free_memory(){
  delete [] d;
  delete [] p;
  delete [] QS;
  delete [] stos;
  negative_value=false;
  algorithm_used=false;
  for(int i=0; i<row_G; i++)
    delete [] matrix_G[i];


  delete [] matrix_G;
}


bool graf::BL(){
    int i, x,k;
    bool test;

    d[start]=0;

    for(i=1; i< row_G; i++)
    {
        test=true;
        for(x=0; x<row_G; x++)
            for(k=0; k<row_G;k++)
                if((d[k]>(d[x]+matrix_G[x][k])) && matrix_G[x][k]!=0)
                {
                    d[k]=d[x]+matrix_G[x][k];
                    p[k]=x;
                    test=false;
                }
        if( test ) return true;
    }

    for(x=0; x<row_G; x++)
        for(i=0; i<row_G; i++)
            if(d[i]>d[x]+matrix_G[x][i] && matrix_G[x][i]!=0)
                return false;


    return true;
}


void graf::BellmanFord(){
    algorithm_used=true;
    std::cout << "BF" << std::endl;
    clock_t time_req;

    int sptr;
    for(int i=0; i<row_G; i++)
    {
        d[i]=INTMAXX;
        p[i]=-1;
    }

    std::cout << "wpisz nr wieszcholka startowego: ";
    std::cin >> start;
    std::cout << std::endl;
    if(start<0 || start >= row_G)
    {
         std::cout << "wybrales wieszcholek spoza zakresu mozliwosci! " << std::endl;
         return;
    }
    time_req = clock();


    if(BL())
    {
        sptr=0;
        time_req = clock() - time_req;

        for(int i=0; i<row_G; i++)
        {
            std::cout << i << ": ";
            for(int x=i; x!=-1; x=p[ x ])
                stos[sptr++]=x;

            while(sptr)
                std::cout << stos[--sptr] << " ";

            std::cout << "$" << d [i] << std::endl;
        }
        std::cout << "Using pow function, it took " << (double)time_req/CLOCKS_PER_SEC << " seconds" << std::endl;
        time_B=(double)time_req/CLOCKS_PER_SEC;
    }

    else std::cout << "Negative Cycle found!" << std::endl;



}


double graf::return_time_D()
{
    return time_D;
}


double graf::return_time_B()
{
    return time_B;
}

