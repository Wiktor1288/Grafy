#include "graf2.hpp"
#include<iomanip>
#define INTMAXX  40000000

graf_lista::graf_lista(){
    negative_value=false;
    element=NULL;
    lista_grafu=NULL;
    d=NULL;
    p=NULL;
    stos=NULL;
    r=NULL;
    start=0;
    row_G=0;
    size_G=0;
    QS=NULL;
    algorithm_used=false;
}


graf_lista::~graf_lista(){

    delete [] stos;
    delete [] p;
    delete [] d;
    delete [] QS;

    for(int i=0; i<row_G; i++)
    {
        element=lista_grafu[i];
        while(element)
        {
            r = element;
            element = element->next;
            delete r;
        }
    }

    delete [] lista_grafu;

}


void graf_lista::reserve_memory(int  edges, int vertices){


    size_G=edges;
    row_G=vertices;

    QS=new bool[row_G];
    stos=new int[row_G];
    d=new long long [row_G];
    p=new int [row_G];
    lista_grafu= new elem_listy* [row_G];

    for(int i=0; i<row_G; i++)
    {
        lista_grafu[i]=NULL;
    }
}


void graf_lista::add_element(int firs_V, int final_V, int weight_edge){

    element=new elem_listy;
    element->wiesz=final_V;
    element->weight=weight_edge;
    element->next=lista_grafu[firs_V];
    lista_grafu[firs_V]=element;

    if(weight_edge<0) negative_value=true;
}


void graf_lista::show_G(){

    for(int i=0; i<row_G; i++){

        std::cout << " lista[ " << i << " ] = ";
        r=lista_grafu[i];
        while( r )
        {
        std::cout << r->wiesz << " ";
        r = r->next;
        }
        std::cout << std::endl;
    }
}


void graf_lista::free_memory(){

    delete [] stos;
    delete [] p;
    delete [] d;
    delete [] QS;
    algorithm_used=false;
    negative_value=false;
    for(int i=0; i<row_G; i++)
    {
        element=lista_grafu[i];
        while(element)
        {
            r = element;
            element = element->next;
            delete r;
        }
    }

    delete [] lista_grafu;

}


void  graf_lista::alg_Dijkstry(){

    if(negative_value!=true){
    int i,j,u,sptr=0;
    algorithm_used=true;
    clock_t time_req;

    for(i=0; i<row_G; i++)
    {
        d[i]=INTMAXX;
        p[i]=-1;
        QS[i]=false;
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
    d[start]=0;

    for(i=0; i<row_G; i++)
    {
        for(j=0; QS[ j ]; j++);
        for(u=j++; j<row_G; j++)
            if(!QS[j] && (d[j]<d[u])) u=j;

        QS[u]=true;

        for(element=lista_grafu[u]; element; element=element->next)
            if(!QS[element->wiesz] && (d[element->wiesz]>d[u]+element->weight))
            {
                d[element->wiesz]=d[u]+element->weight;
                p[element->wiesz]=u;
            }
    }


    time_req = clock() - time_req;

    for(i= 0; i<row_G; i++)
    {
        std::cout << i << ": ";
        for(j=i; j>-1; j=p[j]) stos[sptr++]=j;
        while(sptr) std::cout << stos[--sptr] << " ";
            std::cout << "$" << d[i] << std::endl;
    }
    std::cout << "Using pow function, it took " << (double)time_req/CLOCKS_PER_SEC << " seconds" << std::endl ;
    time_D=(double)time_req/CLOCKS_PER_SEC;
    }

    else std::cout << "ujemna waga krawedzi!!! nie mozna wykorzystac tego algorytmu." << std::endl;
}


bool graf_lista::BF(){


    int i, x;
    bool test;
    elem_listy * pomoc;
    algorithm_used=true;

    d[start]=0;
    for(i=1; i<row_G; i++)
    {
        test=true;
        for(x=0; x<row_G; x++)
            for(pomoc=lista_grafu[x]; pomoc; pomoc=pomoc->next)
                if(d[pomoc->wiesz]>d[x]+pomoc->weight)
                {
                    test=false;
                    d[pomoc->wiesz]=d[x]+pomoc->weight;
                    p[pomoc->wiesz] = x;
                }
        if(test) return true;

    }

    for(x=0; x<row_G; x++)
        for(pomoc=lista_grafu[x]; pomoc; pomoc=pomoc->next)
            if(d[pomoc->wiesz]>d[x]+pomoc->weight) return false;

    return true;

}

void graf_lista::BellmanFord(){

    int sptr,i,x;
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
     for(i=0; i<row_G; i++)
    {
        d[i]=INTMAXX;
        p[i]=-1;
    }
    if(BF())
    {
        sptr=0;
        time_req = clock() - time_req;

        for(i=0; i<row_G; i++)
        {
            std::cout << i << ": ";
            for(x=i; x!=-1; x=p[x])
                stos[sptr++]=x;

            while(sptr)
                std::cout << stos[--sptr] << " ";

            std::cout << "$" << d[i] << std::endl;
        }
        std::cout << "Using pow function, it took " << (double)time_req/CLOCKS_PER_SEC << " seconds" << std::endl ;
        time_B=(double)time_req/CLOCKS_PER_SEC;

    }
    else std::cout << "Negative Cycle found!" << std::endl;

}


long long graf_lista::return_total_cost(int i){
    return d[i];

}


int graf_lista::return_row(){
return row_G;

}


int graf_lista::return_queue(int i){
    int  sptr=0;


    for(int j=i; j!=-1; j=p[j])
                stos[sptr++]=j;


    return sptr-1;


}


double graf_lista::return_time_D()
{
    return time_D;
}


double graf_lista::return_time_B()
{
    return time_B;
}


