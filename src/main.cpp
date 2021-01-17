#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include "./Classes/CovidInfo/CovidInfo.h"
#include "./Classes/FileHandler/FileHandler.cpp"
#include "./Classes/CovidStatistics/CovidStatistics.h"
#include "./Classes/Sorting/Sorting.cpp"
#include <locale>

using namespace std;



int main(int argc, char** argv)
{  
  setlocale(LC_ALL,"");
  
  Sorting *Sort = new Sorting();
  FileHandler *FileReader = new FileHandler();


  vector<CovidInfo> CovidInfoList = FileReader->csvHandler(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");
  CovidStatistics *statistic = new CovidStatistics();
  statistic->setCovidInfoList(CovidInfoList);
  vector<CovidInfo> sorted =  FileReader->getNCovidInfos(1000000);
  cout << "indo pro merge sort";
  Sort->mergeSort(sorted,0,sorted.size());
  Sort->imprimirInformacoes(sorted,10);
  
}
