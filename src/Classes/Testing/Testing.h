
#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
/*#include "../../Classes/FileHandler/FileHandler.h"
#include "../../Classes/CovidInfo/Covidinfo.h"
#include "../../Classes/Sorting/Sorting.h"
#include "../../Classes/CovidStatistics/CovidStatistics.h"*/

class Testing
{
private:

public: 
  Testing();
  int SelecionarSaida();
  int SelecionarAlgoritmo();
  void PreProcessing(string filename , clock_t &processingTime);
  void SelectRandomCases();
  void Execute(string filename);
  void StatisticalAnalysis(int M);
  
  
};

#endif