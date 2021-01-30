
#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include "../../Classes/FileHandler/FileHandler.h"
#include "../../Classes/CovidInfo/CovidInfo.h"
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
  vector<CovidInfo> selectRandomCases();
  void execute(string filename);
  void executeSorting(int choice, vector<CovidInfo> *covidInfoSet);
  int selectFirstPhase();
  void writeOutFile(vector<CovidInfo> &data, int out);
  void PreProcessing(string filename, clock_t &processingTime);
  void SelectRandomCases();
  void Execute(string filename);
  void StatisticalAnalysis(int M);
  void estatisticaDePobre(int M);
};

#endif