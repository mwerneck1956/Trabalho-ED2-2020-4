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
    int k = 0;

    while (i < q && j < r){
        
        cout << "no i " << covidInfoList.at(i).city << endl;
        cout << "no j " << covidInfoList.at(j).city << endl;
        cout << "Comparando "  << covidInfoList.at(i).city.compare(covidInfoList.at(j).city) << endl;


        if (covidInfoList.at(i).city.compare(covidInfoList.at(j).city) == 1)
        {
            int teste = covidInfoList.at(i).city.compare(covidInfoList.at(j).city);
            cout << teste << endl;
           
            auxCovidInfoList.push_back(covidInfoList.at(i));
            i++;
        }
        else
        {
            auxCovidInfoList.push_back(covidInfoList.at(j));
            j++;
        }
        k++;
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

    cout << "---------------------------------------";
    cout << endl;
    for (int i = 0; i < r; i++)
        cout << covidInfoList.at(i).city + "," + covidInfoList.at(i).state << endl;
}

/*void Sorting::imprimir(vector<CovidInfo> covidInfoList, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        cout << covidInfoList.at(i).state << endl;
    }
}*/

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
