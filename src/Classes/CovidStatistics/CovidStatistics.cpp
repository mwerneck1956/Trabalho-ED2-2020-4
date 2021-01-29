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
  vector<CovidInfo> t;
  //cout << "before clear" << sizeof(std::vector<CovidInfo>) + (sizeof(CovidInfo) * covidInfoList.size());
  //Utilizando o swap o vector desaloca os elementos anteriores da memória.
  covidInfoList.swap(t);
  //cout << "after clear" << sizeof(std::vector<CovidInfo>) + (sizeof(CovidInfo) * covidInfoList.size());

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

void CovidStatistics::dailyCasesTotalizers(vector<CovidInfo> covidInfoList){
    std::ofstream outfile("brazil_covid19_cities_processado.csv");
    int lastDayCases = 0 , dailyTotalCases = 0;
    outfile << "date," << "state," <<  "city," << "code," << "dailyCases," << "totalCases," << "deaths," << endl;
    for (int i = 0 ; i < covidInfoList.size() ; i++){
        string baseCity = covidInfoList.at(i).city;
        dailyTotalCases = 0;
        while(i < covidInfoList.size()){
          lastDayCases = i >= 1 ? covidInfoList.at(i - 1).cases : 0;
          dailyTotalCases = covidInfoList.at(i).cases;
          outfile << covidInfoList.at(i).date  << ",";
          outfile << covidInfoList.at(i).state << ",";
          outfile << covidInfoList.at(i).city << ",";
          outfile << covidInfoList.at(i).code << ",";
          outfile <<  dailyTotalCases - lastDayCases << ",";
          outfile << dailyTotalCases  <<",";
          outfile << covidInfoList.at(i).deaths << ",";
          outfile << "\n";
          i++;
        }
    
        lastDayCases = 0;
    }
    covidInfoList.clear();
    covidInfoList.shrink_to_fit();
  
}