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
int numCopias = 0;

clock_t tempo_inicio = 0, tempo_termino;

Sorting::Sorting()
{
    cout << "Objeto sorting montado" << endl;
}

void Sorting::merge(vector<CovidInfo> &covidInfoList, int p, int q, int r)
{
    
    vector<CovidInfo> auxCovidInfoList;
    int i = p;
    int j = q;
    int k = q;

    while (i < q && j < r)
    {
        numComparacoes++;

            if ((covidInfoList.at(i).state.compare(covidInfoList.at(j).state) == -1))
            {
                auxCovidInfoList.push_back(covidInfoList.at(i));
                i++;
                numCopias++;
            }
            else if ((covidInfoList.at(i).state.compare(covidInfoList.at(j).state) == 0))
            {
                if ((covidInfoList.at(i).city.compare(covidInfoList.at(j).city) == -1))
                {
                    auxCovidInfoList.push_back(covidInfoList.at(i));
                    i++;
                    numCopias++;
                }
                else if((covidInfoList.at(i).city.compare(covidInfoList.at(j).city) == 0))
                {
                    if((covidInfoList.at(i).date.compare(covidInfoList.at(j).date) == -1))
                    {
                        auxCovidInfoList.push_back(covidInfoList.at(i));
                        i++;
                        numCopias++;
                    }
                    else
                    {
                        auxCovidInfoList.push_back(covidInfoList.at(j));
                        j++;
                        numCopias++;
                    }
                }
                else
                {
                    auxCovidInfoList.push_back(covidInfoList.at(j));
                    j++;
                    numCopias++;
                }
                
            }
            else
            {
                auxCovidInfoList.push_back(covidInfoList.at(j));
                j++;
                numCopias++;
            }
    }

    while (i < q)
    {
        auxCovidInfoList.push_back(covidInfoList.at(i));
        i++;
        numCopias++;
    }

    while (j < r)
    {
        auxCovidInfoList.push_back((covidInfoList.at(j)));
        j++;
        numCopias++;
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

void Sorting::quickSort(vector<CovidInfo> &covidInfoList, int p, int q, char t)
{
    int r;

    int cIt = 1;
    int dIt = 1;
    int b = 0;

    if(p < q)
    {
        if (t == 'c')
        {
            r = particaoCases(covidInfoList, p, q);
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

int Sorting::particaoCases(vector<CovidInfo> &covidInfoList, int p, int q)
{
    int x = covidInfoList[p].cases;
    int i = p;
    int j;

    for(j = p+1; j < q; j++)
    {
        if(covidInfoList[j].cases <= x)
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

void Sorting::imprimirInformacoes(vector<CovidInfo> covidInfoList, int tam, float tempoExecucao)
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
}
