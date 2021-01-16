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
  /*
  cout << "antes do destrutor" << sizeof(this->covidInfoList) << endl;
  int i =0;
  for(CovidInfo p : this->covidInfoList){
     delete &this->covidInfoList.at(i);
     i++;
  }
  cout << "depois do destrutor" << sizeof(this->covidInfoList) << endl;
  */
  
}

void CovidStatistics::setCovidInfoList(vector<CovidInfo> covidList){
  this->covidInfoList = covidList;
}


vector<CovidInfo> CovidStatistics::getCovidInfoList()
{
  return this->covidInfoList;
}

void CovidStatistics::push(CovidInfo* line){
  this->covidInfoList.push_back(*line);
}

void CovidStatistics::printDates()
{
  cout << "Cidades com mais de 100k casos " << endl;
  for (int i = 0; i < 8 ; i++)
  { 
      cout << "Cidade : " << covidInfoList.at(i).city << " Estado : " << covidInfoList.at(i).state << endl;
  }
}

void CovidStatistics::getDailyCasesTotalizers(){
    int index = 0;
    for (int i = 0 ; i < this->covidInfoList.size() ; i++){
        string baseDate = covidInfoList.at(i).date;
        int diaryCases = 0;
        while(covidInfoList.at(i).date == baseDate){
          diaryCases += covidInfoList.at(i).cases;
          i++;
        }
        cout << "Total do dia " << baseDate << " : " << diaryCases << endl;;
    }
  
}