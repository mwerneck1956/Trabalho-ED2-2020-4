#include "./Sorting.h"
#include "../CovidStatistics/CovidStatistics.h"
#include "../CovidInfo/CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

Sorting::Sorting()
{
}

//Função que utilizará o método de ordenação shellSort para o pré-processamento
void Sorting::shellSortStateCityDate(vector<CovidInfo> &covidInfoList, int n)
{
    //é calculado o valor do gap
    int i = n / 2;
    //são criadas as váriaveis que irão regular as repetições
    int chave, k;
    //aux irá inicializar com o vetor de covidInfoList de indice i
    CovidInfo aux = covidInfoList.at(i);

    //será feito enquanto o gap for um numero inteiro, tal qual o último caso será com i=1.
    while (i != 0)
    {
        do
        {
            chave = 1;
            for (k = 0; k < n - i; ++k)
            {
                //Os if's e elses irão verificar os componentes ordenando por (em ordem de prioridade), cidade, estado e data.
                if (covidInfoList.at(k).state == covidInfoList.at(k + i).state)
                {
                    if (covidInfoList.at(k).city == covidInfoList.at(k + i).city)
                    {
                        if (covidInfoList.at(k).date > covidInfoList.at(k + i).date)
                        {
                            //Serão feitas as trocas e a chave receberá 0
                            aux = covidInfoList.at(k);
                            covidInfoList.at(k) = covidInfoList.at(k + i);
                            covidInfoList.at(k + i) = aux;
                            chave = 0;
                        }
                    }
                    else if (covidInfoList.at(k).city > covidInfoList.at(k + i).city)
                    {
                        //Serão feitas as trocas e a chave receberá 0
                        aux = covidInfoList.at(k);
                        covidInfoList.at(k) = covidInfoList.at(k + i);
                        covidInfoList.at(k + i) = aux;
                        chave = 0;
                    }
                }
                else if (covidInfoList.at(k).state > covidInfoList.at(k + i).state)
                {
                    //Serão feitas as trocas e a chave receberá 0
                    aux = covidInfoList.at(k);
                    covidInfoList.at(k) = covidInfoList.at(k + i);
                    covidInfoList.at(k + i) = aux;
                    chave = 0;
                }
            }
        } while (chave == 0);
        //é atualizado o valor do gap i
        i = i / 2;
    }
}

//Função que utilizará o shellSort para ordenar e analisar os dados, utilizando como chave de ordenação os casos
void Sorting::shellSortCases(vector<CovidInfo> &covidInfoList, int n, int &comparisons, int &swaps)
{
    int h = 1;
    int i, j;

    while (h < n)
    {
        //O h inicial é calculado
        h = h * 3 + 1;
    }

    while (h > 1)
    {
        //O valor de h é atualizado
        h /= 3;

        for (i = h; i < n; i++)
        {
            CovidInfo aux = covidInfoList.at(i);
            j = i;
            // São efetuadas comparações entre elementos com distanciamento h
            comparisons++;
            while (j >= h && aux.totalCases < covidInfoList.at(j - h).totalCases)
            {
                //covidInfolist[j] irá receber o valor de covidInfoList[j-h]. Troca
                //Exemplo: {1,3,2}, covidInfoList[j] = 2 irá receber o valor de covidInfolist[j-h]=3, ficando assim {1,3,3}.
                covidInfoList.at(j) = covidInfoList.at(j - h);

                //O valor de j é atualizado
                j -= h;
                swaps++;
                comparisons++; //voltará para o loop e irá comparar novamente
            }
            //covidInfoList[j] irá receber o vetor auxiliar. No caso do exemplo {1,3,3}, tal que aux=2, teremos {1,2,3}. Troca
            covidInfoList.at(j) = aux;
            swaps++;
        }
    }
}

//Função que utilizará o quickSort para ordenar e analisar os dados, utilizando como chave de ordenação os casos
void Sorting::quicksortCases(vector<CovidInfo> &covidInfoList, int began, int end, int &comparisons, int &swaps)
{
    int i, j;
    CovidInfo aux;
    CovidInfo pivot;
    i = began;
    j = end - 1;
    //é feito um pivô
    pivot = covidInfoList[(began + end) / 2];
    while (i <= j)
    {
        comparisons++;
        while (covidInfoList[i].totalCases < pivot.totalCases && i < end)
        {
            comparisons++;
            i++;
        }
        comparisons++;
        while (covidInfoList[j].totalCases > pivot.totalCases && j > began)
        {
            comparisons++;
            j--;
        }
        if (i <= j)
        {
            //são realizadas as trocas
            swaps++;
            aux = covidInfoList[i];
            covidInfoList[i] = covidInfoList[j];
            covidInfoList[j] = aux;
            i++;
            j--;
        }
    }
    if (j > began)
        //é chamada a função novamente de forma recursiva
        quicksortCases(covidInfoList, began, j + 1, comparisons, swaps);
    if (i < end)
        //é chamada a função novamente de forma recursiva
        quicksortCases(covidInfoList, i, end, comparisons, swaps);
}

//Função que utilizará o mergeSort para ordenar e analisar os dados, utilizando como chave de ordenação os casos
void Sorting::mergeCases(vector<CovidInfo> &covidInfoList, int p, int q, int r, int &comparisons, int &swaps)
{
    //vector<CovidInfo> vetor que armazena os dados; p  = inicio do vetor; q = metade do vetor; r = ultima posição do vetor
    // comparisons = variavel que armazena o numero de comparações; swaps = variavel que armazena o numero de trocas;
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
