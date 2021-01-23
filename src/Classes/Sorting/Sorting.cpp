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

    tempo_termino = clock();

}

///Funcao recursiva
void Sorting::mergeSort(vector<CovidInfo> &covidInfoList, int p, int r)
{
    tempo_inicio = clock();

    if (p < r - 1)
    {
        int q = (p + r) / 2;
        mergeSort(covidInfoList, p, q); ///chama de p a q
        mergeSort(covidInfoList, q, r); ///chama de q a r
        merge(covidInfoList, p, q, r);
    }
}

void Sorting::imprimirInformacoes(vector<CovidInfo> covidInfoList, int r)
{
    int totalCasos = 0;

    cout << endl;

    for (int i = 0; i < r; i++)
    {
        cout << covidInfoList.at(i).date << "," << covidInfoList.at(i).state << "," << covidInfoList.at(i).city << "," << covidInfoList.at(i).code << "," << covidInfoList.at(i).cases << "," << covidInfoList.at(i).deaths << endl;

        totalCasos += covidInfoList.at(i).cases;
    }

    cout << "O numero total de casos diarios eh: " << totalCasos << endl;

    cout << "O numero de comparacoes foi: " << numComparacoes << endl;

    cout << "O numero de copias foi: " << numCopias << endl;

    cout << "Tempo total de execução: " << ((tempo_termino - tempo_inicio) / (float)CLOCKS_PER_SEC) << " segundos" << endl;

    
    numComparacoes = 0;
    numCopias = 0;

    cout << endl;
}
