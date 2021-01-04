#include "./Sorting.h"
#include "../CovidStatistics/CovidStatistics.h"
//#include "../CovidStatistics/CovidStatistics.cpp"
#include "../CovidInfo/CovidInfo.h"
//#include "../CovidInfo/CovidInfo.cpp"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Sorting::Sorting()
{
    cout << "Objeto sorting montado" << endl;
}

void Sorting::merge(vector<CovidInfo> covidInfoList, int p, int q, int r)
{
    cout << "aqui" << endl;
    vector<CovidInfo> auxCovidInfoList;
    int i = p;
    int j = q;
    int k = 0;

    while(i < q && j < r)
    {
        if ((covidInfoList.at(i).state < covidInfoList.at(j).state) && (covidInfoList.at(i).city < covidInfoList.at(j).city))
        {
            auxCovidInfoList.at(k).state = covidInfoList.at(i).state;
            auxCovidInfoList.at(k).city = covidInfoList.at(i).city;
            i++;
        }
        else
        {
            auxCovidInfoList.at(k).state = covidInfoList.at(j).state;
            auxCovidInfoList.at(k).city = covidInfoList.at(j).city;
            j++;
        }
        k++;
    }

    while(i < q)
    {
        auxCovidInfoList.at(k).state = covidInfoList.at(i).state;
        auxCovidInfoList.at(k).city = covidInfoList.at(i).city;
        i++;
        k++;
    }

    while(j < r)
    {
        auxCovidInfoList.at(k).state = covidInfoList.at(j).state;
        auxCovidInfoList.at(k).city = covidInfoList.at(j).city;
        j++;
        k++;
    }

    for(i = p; i < r; i++)
    {
        covidInfoList.at(i).state = auxCovidInfoList.at(i - p).state;
        covidInfoList.at(i).city = auxCovidInfoList.at(i - p).city;
    }
}

///Funcao recursiva
void Sorting::mergeSort(vector<CovidInfo> covidInfoList, int p, int r)
{
    if(p < r - 1)
    {
        int q = (p + r) / 2;
        mergeSort(covidInfoList, p, q); ///chama de p a q
        mergeSort(covidInfoList, q, r);  ///chama de q a r
        merge(covidInfoList, p, q, r);
    }

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

