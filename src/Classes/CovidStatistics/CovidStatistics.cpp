#include "./CovidStatistics.h"
#include "../CovidInfo/CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

CovidStatistics::CovidStatistics(vector<string> processedCsv)
{
  string date = "", state = "", city = "";
  int code = 0.0;
  int cases = 0, deaths = 0, j = 0;
  for (int i = 6; i < processedCsv.size(); i++)
  {
    if (j == 0)
      date = processedCsv.at(i);
    else if (j == 1)
      state = processedCsv.at(i);
    else if (j == 2)
    {
      city = processedCsv.at(i);
    }

    else if (j == 3)
    {
      code = stoi(processedCsv.at(i));
    }

    else if (j == 4)
    {
      cases = stoi(processedCsv.at(i));
    }

    else if (j == 5)
      deaths = stoi(processedCsv[i]);

    if (j == 6)
    {
      CovidInfo *auxCovidInfo = new CovidInfo(date, state, city, code, cases, deaths);
      this->covidInfoList.push_back(*auxCovidInfo);
      j = 0;
    }
    j++;
  }
}

CovidStatistics::~CovidStatistics()
{
}

void CovidStatistics::printDates()
{
  for (int i = 0; i < this->covidInfoList.size(); i++)
  {
    if(i > 1111615 && i < 1111715 )
    cout << "Cidade : " << covidInfoList.at(i).city << " Casos : " <<  covidInfoList.at(i).cases << endl;
  }
}