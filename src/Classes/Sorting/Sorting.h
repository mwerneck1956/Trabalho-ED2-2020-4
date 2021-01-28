#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Sorting 
{
    private:
    
    public:
        Sorting();
        void merge(vector<CovidInfo> &covidInfoList, int p, int q, int r);
        void mergeSort(vector<CovidInfo> &covidInfoList, int p, int r);
        void imprimirInformacoes(vector<CovidInfo> covidInfoList, int tam, float tempoExecucao);
        void shellSortStateCityDate(vector<CovidInfo> &convidInfoList, int n);
        void shellSortCases(vector<CovidInfo> &convidInfoList, int n);
        void imprimir(vector<CovidInfo> covidInfoList, int tam);
        void mergeCases(vector<CovidInfo> &covidInfoList, int p, int q, int r);
        void mergeSortCases(vector<CovidInfo> &covidInfoList, int p, int r);
        

};

#endif

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