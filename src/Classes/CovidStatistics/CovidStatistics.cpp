#include "./CovidStatistics.h"
#include "../CovidInfo/CovidInfo.h"
#include <iostream>
#include <vector>
#include <locale.h>
#include <fstream>

using namespace std;



CovidStatistics::CovidStatistics()
{

}

CovidStatistics::~CovidStatistics()
{
}

void CovidStatistics::push(CovidInfo* line){
  this->covidInfoList.push_back(*line);
}

void CovidStatistics::printDates()
{
  cout << "Cidades com mais de 100k casos " << endl;
  for (int i = 0; i < covidInfoList.size(); i++)
  { 
      if(covidInfoList.at(i).cases > 100000)
      cout << "Cidade : " << covidInfoList.at(i).city << " Casos : " << covidInfoList.at(i).cases << endl;
  }
}