#ifndef COVIDSTATISTICS_H_INCLUDED
#define COVIDSTATISTICS_H_INCLUDED
#include"../CovidInfo/CovidInfo.cpp"
#include"../Sorting/Sorting.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

/*Classe que lida com todos os processamento necessários
  na estrutura de dados que armazena as informações de infecção 
  sobre o covid
*/
class CovidStatistics
{

  private:
    vector<CovidInfo> covidInfoList;

  public:
    //Função de processamento do csv
    CovidStatistics();
    ~CovidStatistics();
    void setCovidInfoList(vector<CovidInfo> covidList);
    vector<CovidInfo> getCovidInfoList();
    void push(CovidInfo* line);
    void dailyCasesTotalizers(vector<CovidInfo> covidInfoList);
};

#endif