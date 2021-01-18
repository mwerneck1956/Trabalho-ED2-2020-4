#include "./Sorting.h"
#include "../CovidStatistics/CovidStatistics.h"
#include "../CovidInfo/CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

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

        /*cout << "no i " << covidInfoList.at(i).city << endl;
        cout << "no j " << covidInfoList.at(j).city << endl;
        cout << "Comparando "  << covidInfoList.at(i).city.compare(covidInfoList.at(j).city) << endl;*/

        if ((covidInfoList.at(i).state.compare(covidInfoList.at(j).state) == -1))
        {
            auxCovidInfoList.push_back(covidInfoList.at(i));
            i++;
            
        }
        else if((covidInfoList.at(i).state.compare(covidInfoList.at(j).state) == 0))
        {
            if((covidInfoList.at(i).city.compare(covidInfoList.at(j).city) == -1))
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

    while (i < q)
    {
        auxCovidInfoList.push_back(covidInfoList.at(i));
        k++;
        i++;
    }

    while (j < r)
    {
        auxCovidInfoList.push_back((covidInfoList.at(j)));
        k++;
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

void Sorting::imprimir(vector<CovidInfo> covidInfoList, int r)
{
    int totalCasos = 0;

    cout << endl;

     for (int i = 0; i < r; i++)
    {
        cout << covidInfoList.at(i).date << "," << covidInfoList.at(i).state << "," << covidInfoList.at(i).city << "," << 
        covidInfoList.at(i).code << "," << covidInfoList.at(i).cases << "," << covidInfoList.at(i).deaths << endl;
        
        totalCasos += covidInfoList.at(i).cases;

    }

    cout << endl;

    cout << " O numero total de casos diarios eh de: " << totalCasos << endl;

}

void Sorting::quickSort(vector<CovidInfo> &covidInfoList, int b, int e)
{
    int p;

    if (e == -1)
        e = covidInfoList.size() - 1;
    
    if (b < 3)
        p = particao(covidInfoList, b, e);
        quickSort(covidInfoList, b, p-1);
        quickSort(covidInfoList, p+1, e);
}

int Sorting::particao(vector<CovidInfo> &covidInfoList, int b, int e)
{
    CovidInfo pivo = covidInfoList.back();
    int i = b;

    for (int j = 0; j < covidInfoList.size(); j++)
    {
        if (covidInfoList[j].date <= pivo.date)
        {
            CovidInfo aux = covidInfoList[i];
            covidInfoList[i] = covidInfoList[j];
            covidInfoList[j] = aux;
            i++;
        }
        else if(covidInfoList[j].date == pivo.date)
        {
            if(covidInfoList[j].state <= pivo.state)
            {
                CovidInfo aux = covidInfoList[i];
                covidInfoList[i] = covidInfoList[j];
                covidInfoList[j] = aux;
                i++;
            }
            else if(covidInfoList[j].state == pivo.state and covidInfoList[j].city <= pivo.city)
            {
                CovidInfo aux = covidInfoList[i];
                covidInfoList[i] = covidInfoList[j];
                covidInfoList[j] = aux;
                i++;
            }
        }
    }
    CovidInfo aux2 = covidInfoList[i];
    covidInfoList[i] = covidInfoList[e];
    covidInfoList[e] = aux2;

    return i;
}

//Teste feito na main()

/*
int main()
{
    int tam = 8;
    int vet[tam] = {39, 5, 12, 1, 34, 64, 7, 76};

    mergeSort(vet, 0, tam);

    cout<<"Vetor ordenado: "<<endl;
    for(int i = 0; i < tam; i++)
    {
        cout<<" "<<vet[i];
    }

    cout<<endl;

    return 0;
}*/
