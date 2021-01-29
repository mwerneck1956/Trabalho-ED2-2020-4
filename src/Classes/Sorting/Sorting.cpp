#include "./Sorting.h"
#include "../CovidStatistics/CovidStatistics.h"
#include "../CovidInfo/CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

int numComparacoes = 0;

Sorting::Sorting()
{
}

void Sorting::merge(vector<CovidInfo> &covidInfoList, int p, int q, int r)
{

    vector<CovidInfo> auxCovidInfoList;
    int i = p;
    int j = q;

    while (i < q && j < r)
    {
        

        if ((covidInfoList.at(i).state.compare(covidInfoList.at(j).state) == -1))
        {
            auxCovidInfoList.push_back(covidInfoList.at(i));
            i++;
            
        }
        else if ((covidInfoList.at(i).state.compare(covidInfoList.at(j).state) == 0))
        {
            if ((covidInfoList.at(i).city.compare(covidInfoList.at(j).city) == -1))
            {
                auxCovidInfoList.push_back(covidInfoList.at(i));
                i++;
                
            }
            else if ((covidInfoList.at(i).city.compare(covidInfoList.at(j).city) == 0))
            {
                if ((covidInfoList.at(i).date.compare(covidInfoList.at(j).date) == -1))
                {
                    auxCovidInfoList.push_back(covidInfoList.at(i));
                    i++;
                    
                }
                else
                {
                    auxCovidInfoList.push_back(covidInfoList.at(j));
                    j++;
                    
                }
            }
            else
            {
                auxCovidInfoList.push_back(covidInfoList.at(j));
                j++;
                
            }
        }
        else
        {
            auxCovidInfoList.push_back(covidInfoList.at(j));
            j++;
            
        }
    }

    while (i < q)
    {
        auxCovidInfoList.push_back(covidInfoList.at(i));
        i++;
        
    }

    while (j < r)
    {
        auxCovidInfoList.push_back((covidInfoList.at(j)));
        j++;
        
    }

    for (i = p; i < r; i++)
    {
        covidInfoList.at(i) = auxCovidInfoList.at(i - p);
    }
}

void Sorting::shellSortStateCityDate(vector<CovidInfo> &covidInfoList, int n){
   int i = (n - 1)/ 2;
   int chave, k;
   CovidInfo aux = covidInfoList.at(i);

   while(i != 0)
   {
      do
      {
         chave = 1;
         for(k = 0; k< n - i; ++k){
            if(covidInfoList.at(k).state == covidInfoList.at(k + i).state)
            {
               if(covidInfoList.at(k).city == covidInfoList.at(k+i).city)
               {
                   if(covidInfoList.at(k).date > covidInfoList.at(k+i).date)
                   {
                      aux = covidInfoList.at(k);
                      covidInfoList.at(k) = covidInfoList.at(k + i);
                      covidInfoList.at(k + i) = aux;
                      chave = 0; 
                   }
                   
               }
               else if(covidInfoList.at(k).city > covidInfoList.at(k+i).city)
               {
                      aux = covidInfoList.at(k);
                      covidInfoList.at(k) = covidInfoList.at(k + i);
                      covidInfoList.at(k + i) = aux;
                      chave = 0;      
               }
            }
            else if(covidInfoList.at(k).state > covidInfoList.at(k+i).state){
                    aux = covidInfoList.at(k);
                    covidInfoList.at(k) = covidInfoList.at(k+i);
                    covidInfoList.at(k+i) = aux;
                    chave = 0;
            }
         }
      }while(chave == 0);
      i = i / 2;
   }
}

///Funcao recursiva
void Sorting::mergeSort(vector<CovidInfo> &covidInfoList, int p, int r)
{

    if (p < r - 1)
    {
        int q = (p + r) / 2;
        
        mergeSort(covidInfoList, p, q); ///chama de p a q
        mergeSort(covidInfoList, q, r); ///chama de q a r
        merge(covidInfoList, p, q, r);
    }
}

void Sorting::shellSortCases(vector<CovidInfo> &covidInfoList, int n, int &comparisons, int &swaps)
{
    int h = 1;
    int i, j;

    while (h < n)
    {
        h = h * 3 + 1; //calcula o h inicial
    }

    while (h > 1)
    {
        h /= 3; //atualiza valor de h

        for (i = h; i < n; i++)
        {
            CovidInfo aux = covidInfoList.at(i);
            j = i;  
            // efetua comparações entre elementos com distância h:
            comparisons++;
            while (j >= h && aux.totalCases < covidInfoList.at(j - h).totalCases)
            {
                covidInfoList.at(j) = covidInfoList.at(j-h);
                j -= h; // atualiza valor de j
                swaps++;
                if( j != 0)
                {
                    comparisons++;
                }
            }
            covidInfoList.at(j) = aux;     
        }
    }
}   
void Sorting::quickSort(vector<CovidInfo> &covidInfoList, int p, int q, char t) //t ='c' para ordenar por casos, 's' para State-City-Date
{
    int r;

    int cIt = 1;
    int dIt = 1;
    int b = 0;

    if(p < q)
    {
        if (t == 'c')
        {
            r = particaoCases_r(covidInfoList, p, q);
            quickSort(covidInfoList, p, r);  
            quickSort(covidInfoList, r+1, q);
        }
        else if(t == 's')
        {
            r = particaoStates(covidInfoList, p, q);
            quickSort(covidInfoList, p, r);  
            quickSort(covidInfoList, r+1, q);

            quickSortCities(covidInfoList, p, q);

            quickSortDates(covidInfoList, p, q);
        }
    }
}

void Sorting::quickSortCities(vector<CovidInfo> &covidInfoList, int p, int q)
{
    int r;
    int cIt = 1;
    int b = 0;

    if(p < q)
    {
        while(cIt <= q)
        {
            if(covidInfoList.at(cIt-1).state.compare(covidInfoList.at(cIt).state) != 0)
            {
                r = particaoCities(covidInfoList, b, cIt-1);
                quickSortCities(covidInfoList, b, r);  
                quickSortCities(covidInfoList, r+1, cIt-1);
                b = cIt;
            }
            cIt++;
        }
    }
}

void Sorting::mergeCases(vector<CovidInfo> &covidInfoList, int p, int q, int r, int &comparisons, int &swaps)
{

    vector<CovidInfo> auxCovidInfoList;
    int i = p;
    int j = q;

    while (i < q && j < r)
    {
        comparisons++;

            if (covidInfoList.at(i).totalCases < covidInfoList.at(j).totalCases)
            {
                auxCovidInfoList.push_back(covidInfoList.at(i));
                i++;
                swaps++;
            }
            else
            {
                auxCovidInfoList.push_back(covidInfoList.at(j));
                j++;
                swaps++;
            }
    }

    while (i < q)
    {
        auxCovidInfoList.push_back(covidInfoList.at(i));
        i++;
        swaps++;
    }

    while (j < r)
    {
        auxCovidInfoList.push_back((covidInfoList.at(j)));
        j++;
        swaps++;
    }

    for (i = p; i < r; i++)
    {
        covidInfoList.at(i) = auxCovidInfoList.at(i - p);
    }
}

///Funcao recursiva
void Sorting::mergeSortCases(vector<CovidInfo> &covidInfoList, int p, int r, int &comparisons, int &swaps)
{
    if (p < r - 1)
    {
        int q = (p + r) / 2;
        mergeSortCases(covidInfoList, p, q, comparisons, swaps); ///chama de p a q
        mergeSortCases(covidInfoList, q, r, comparisons, swaps); ///chama de q a r
        mergeCases(covidInfoList, p, q, r, comparisons, swaps);
    }
}
void Sorting::quickSortDates(vector<CovidInfo> &covidInfoList, int p, int q)
{
    int r;
    int dIt = 1;
    int b = 0;

    if(p < q)
    {
        while(dIt <= q)
        {
            if(covidInfoList.at(dIt-1).city.compare(covidInfoList.at(dIt).city) != 0)
            {
                r = particaoDates(covidInfoList, b, dIt-1);
                quickSortDates(covidInfoList, b, r);  
                quickSortDates(covidInfoList, r+1, dIt-1);
                b = dIt;
            }
            dIt++;
        }
    }
}

int Sorting::particaoCases_r(vector<CovidInfo> &covidInfoList, int p, int q)
{
    srand (time(NULL));
    int r = rand()%((q - p) + 1) + p;
    
    swap(covidInfoList[r], covidInfoList[q]);

    return particaoCases(covidInfoList, p, q);
}

int Sorting::particaoCases(vector<CovidInfo> &covidInfoList, int p, int q)
{
    int x = covidInfoList[p].totalCases;
    int i = p;
    int j;

    for(j = p+1; j < q; j++)
    {
        if(covidInfoList[j].totalCases <= x)
        {
            i++;
            swap(covidInfoList[i], covidInfoList[j]);
        }
    }

    swap(covidInfoList[i], covidInfoList[p]);
    return i;
}

int Sorting::particaoStates(vector<CovidInfo> &covidInfoList, int p, int q)
{
    string x = covidInfoList[p].state;
    int i = p;
    int j;

    for(j = p+1; j < q; j++)
    {
        if(covidInfoList.at(j).state.compare(x) == -1 or covidInfoList.at(j).state.compare(x) == 0)
        {
            i++;
            swap(covidInfoList[i], covidInfoList[j]);
        }
         
    }

    swap(covidInfoList[i], covidInfoList[p]);
    return i;
}

int Sorting::particaoCities(vector<CovidInfo> &covidInfoList, int p, int q)
{
    string x = covidInfoList[p].city;
    int i = p;
    int j;

    for(j = p+1; j < q; j++)
    {
        if(covidInfoList.at(j).city.compare(x) == -1 or covidInfoList.at(j).city.compare(x) == 0)
        {
            i++;
            swap(covidInfoList[i], covidInfoList[j]);
        }
    }

    swap(covidInfoList[i], covidInfoList[p]);
    return i;
}

int Sorting::particaoDates(vector<CovidInfo> &covidInfoList, int p, int q)
{
    string x = covidInfoList[p].date;
    int i = p;
    int j;

    for(j = p+1; j < q; j++)
    {
        if(covidInfoList.at(j).date.compare(x) == -1 or covidInfoList.at(j).date.compare(x) == 0)
        {
            i++;
            swap(covidInfoList[i], covidInfoList[j]);
        }
    }

    swap(covidInfoList[i], covidInfoList[p]);
    return i;
}
/*
void Sorting::imprimirInformacoes(vector<CovidInfo> covidInfoList, int tam, float tempoExecucao)
} */
/*void Sorting::imprimirInformacoes(vector<CovidInfo> covidInfoList, int tam, float tempoExecucao)
{
    int totalCasos = 0;

    cout << endl;

    for (int i = 0; i < tam; i++)
    {
        cout << covidInfoList.at(i).date << "," << covidInfoList.at(i).state << "," << covidInfoList.at(i).city << "," << covidInfoList.at(i).code << "," << covidInfoList.at(i).cases << "," << covidInfoList.at(i).deaths << endl;

        totalCasos += covidInfoList.at(i).cases;
    }

    cout << "O numero total de casos diarios eh: " << totalCasos << endl;

    cout << "O numero de comparacoes foi: " << numComparacoes << endl;

    cout << "O numero de copias foi: " << numCopias << endl;

    cout << "Tempo total de execução: " << tempoExecucao << " segundos" << endl;

    numComparacoes = 0;
    numCopias = 0;

    cout << endl;
}*/
