#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
        

        void quickSort(vector<CovidInfo> &covidInfoList, int p, int q, char t = 'c'); //'c' para ordenar por casos, 's' para State-City-Date
        void quickSortCities(vector<CovidInfo> &covidInfoList, int p, int q);
        void quickSortDates(vector<CovidInfo> &covidInfoList, int p, int q);
        int particaoCases(vector<CovidInfo> &covidInfoList, int p, int q);
        int particaoCases_r(vector<CovidInfo> &covidInfoList, int p, int q);
        int particaoStates(vector<CovidInfo> &covidInfoList, int p, int q);
        int particaoCities(vector<CovidInfo> &covidInfoList, int p, int q);
        int particaoDates(vector<CovidInfo> &covidInfoList, int p, int q);
};

#endif
