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
    cout << "Objeto sorting montado" << endl;
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
            while (j>=h && aux.cases < covidInfoList.at(j - h).cases)
            {
                covidInfoList.at(j) = covidInfoList.at(j-h);
                j -= h; // atualiza valor de j
                swaps++;
                if(j!=0)
                {
                    comparisons++;
                }
            }
            covidInfoList.at(j) = aux;     
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

            if (covidInfoList.at(i).cases < covidInfoList.at(j).cases)
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
