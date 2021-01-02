
#ifndef COVIDINFO_H_INCLUDED
#define COVIDINFO_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class CovidInfo
{
private:
public:
  string date;
  string state;
  string city;
  int code;
  int cases;
  int deaths;
  //Função de processamento do csv
  CovidInfo(string date, string state, string city, int code, int cases, int deaths);
  void printInfo();
};

#endif