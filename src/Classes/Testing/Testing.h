
#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include "../../Classes/FileHandler/FileHandler.h"
#include "../../Classes/CovidInfo/Covidinfo.h"
#include "../../Classes/Sorting/Sorting.h"
#include "../../Classes/CovidStatistics/CovidStatistics.h"

using namespace std;

class Testing
{
private:

public: 
  Testing();
  int SelecionarSaida();
  int SelecionarAlgoritmo();
  vector<CovidInfo> preProcessing(string filename , clock_t &processingTime);
  void selectRandomCases();
  void execute(string filename);

  
};

#endif