#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "./Classes/CovidInfo/CovidInfo.h"
#include "./Classes/FileHandler/FileHandler.cpp"
#include "./Classes/CovidStatistics/CovidStatistics.h"
#include "./Classes/Sorting/Sorting.cpp"
#include "./Classes/Testing/Testing.h"
#include "./Classes/Testing/Testing.cpp"
#include <locale>
#include <ctime>

using namespace std;

int main(int argc, char **argv)
{
  setlocale(LC_CTYPE, "");
  Testing test;
  //test.execute(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");
  //test.StatisticalAnalysis(5);
  test.estatisticaDePobre(5);
  return 0;
}
