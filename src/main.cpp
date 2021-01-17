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
  
  //Sorting *Sort = new Sorting();
  FileHandler *FileReader = new FileHandler();


  vector<CovidInfo> CovidInfoList = FileReader->csvHandler(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");
  cout << "Acabou o processamento" << endl;
  CovidStatistics *statistic = new CovidStatistics();
  statistic->setCovidInfoList(CovidInfoList);
  //for(int i = 0 ; i < 50 ; i++)
  //cout << "Cidade : " << CovidInfoList.at(i).city << " Casos : " << CovidInfoList.at(i).cases << endl;
  statistic->dailyCasesTotalizers();
  //statistic->~CovidStatistics();

  
  
  
 
 

  return 0;
}
