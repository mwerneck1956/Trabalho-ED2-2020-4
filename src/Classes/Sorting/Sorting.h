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
        void shellSortCases(vector<CovidInfo> &convidInfoList, int n, int &comparisons, int &swaps);
        void imprimir(vector<CovidInfo> covidInfoList, int tam);
        void mergeCases(vector<CovidInfo> &covidInfoList, int p, int q, int r, int &comparisons, int &swaps);
        void mergeSortCases(vector<CovidInfo> &covidInfoList, int p, int r, int &comparisons, int &swaps);
        

};

#endif
