
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
  int SelectOut();
  int SelectSortMethod();
  vector<CovidInfo> selectRandomCases();
  void Execute(string filename);
  void ExecuteSorting(int choice, vector<CovidInfo> *covidInfoSet);
  int SelectPhase();
  void WriteOutFile(vector<CovidInfo> &data, int out);
  void PreProcessing(string filename, clock_t &processingTime);
  void SelectRandomCases();
  void StatisticalAnalysis(int M);
  void PrintStatistic(int M, int N[], float time[], int swaps[], int comparisons[], int algorithm, ofstream &statisticsResults);
};


#endif