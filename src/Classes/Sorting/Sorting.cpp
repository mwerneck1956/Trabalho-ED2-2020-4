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

//Função de intercalação, p = inicio do vetor, q = meio do vetor , r = final do vetor*/
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

void Sorting::shellSortStateCityDate(vector<CovidInfo> &covidInfoList, int n)
{
    int i = (n - 1) / 2;
    int chave, k;
    CovidInfo aux = covidInfoList.at(i);

    while (i != 0)
    {
        do
        {
            chave = 1;
            for (k = 0; k < n - i; ++k)
            {
                if (covidInfoList.at(k).state == covidInfoList.at(k + i).state)
                {
                    if (covidInfoList.at(k).city == covidInfoList.at(k + i).city)
                    {
                        if (covidInfoList.at(k).date > covidInfoList.at(k + i).date)
                        {
                            aux = covidInfoList.at(k);
                            covidInfoList.at(k) = covidInfoList.at(k + i);
                            covidInfoList.at(k + i) = aux;
                            chave = 0;
                        }
                    }
                    else if (covidInfoList.at(k).city > covidInfoList.at(k + i).city)
                    {
                        aux = covidInfoList.at(k);
                        covidInfoList.at(k) = covidInfoList.at(k + i);
                        covidInfoList.at(k + i) = aux;
                        chave = 0;
                    }
                }
                else if (covidInfoList.at(k).state > covidInfoList.at(k + i).state)
                {
                    aux = covidInfoList.at(k);
                    covidInfoList.at(k) = covidInfoList.at(k + i);
                    covidInfoList.at(k + i) = aux;
                    chave = 0;
                }
            }
        } while (chave == 0);
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
                covidInfoList.at(j) = covidInfoList.at(j - h);
                j -= h; // atualiza valor de j
                swaps++;
                comparisons++;
            }
            covidInfoList.at(j) = aux;
        }
    }
}

void Sorting::quicksortXD(vector<CovidInfo> &covidInfoList, int began, int end, int &comparisons, int &swaps)
{
    int i, j;
    CovidInfo aux;
    CovidInfo pivo;
    i = began;
    j = end - 1;
    pivo = covidInfoList[(began + end) / 2];
    while (i <= j)
    {
        comparisons++;
        while (covidInfoList[i].totalCases < pivo.totalCases && i < end)
        {
            comparisons++;
            i++;
        }
        comparisons++;
        while (covidInfoList[j].totalCases > pivo.totalCases && j > began)
        {
            comparisons++;
            j--;
        }
        if (i <= j)
        {
            swaps++;
            aux = covidInfoList[i];
            covidInfoList[i] = covidInfoList[j];
            covidInfoList[j] = aux;
            i++;
            j--;
        }
    }
    if (j > began)
        quicksortXD(covidInfoList, began, j + 1, comparisons, swaps);
    if (i < end)
        quicksortXD(covidInfoList, i, end, comparisons, swaps);
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
