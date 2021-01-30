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
    void imprimirInrmacoes(vector<CovidInfo> covidInfoList, int tam, float tempoExecucao);
    //ShellSort multicriterio
    void shellSortStateCityDate(vector<CovidInfo> &convidInfoList, int n);
    //ShellSort ordenando pelo numero de casos totais
    void shellSortCases(vector<CovidInfo> &convidInfoList, int n, int &comparisons, int &swaps);
    //MergeSort ordenando pelo numero de casos totais
    void mergeCases(vector<CovidInfo> &covidInfoList, int p, int q, int r, int &comparisons, int &swaps);
    //MergeSort multicriterio
    void mergeSortCases(vector<CovidInfo> &covidInfoList, int p, int r, int &comparisons, int &swaps);
    void quicksortXD(vector<CovidInfo> &covidInfoList, int began, int end, int &comparisons, int &swaps);
  
};

#endif
