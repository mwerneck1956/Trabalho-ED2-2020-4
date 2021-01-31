
#ifndef COVIDINFO_H_INCLUDED
#define COVIDINFO_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/*Classe para armazenar cada registro(linha) do CSV*/
class CovidInfo
{
private:
public:
  string date;
  string state;
  string city;
  float code;
  int cases;
  int deaths;
  int totalCases;
  //Função de processamento do csv
  CovidInfo();
  CovidInfo(string date, string state, string city, int code, int cases, int deaths);
  CovidInfo(string date, string state, string city, int code, int cases, int totalCases, int deaths);

  ~CovidInfo();
};

#endif