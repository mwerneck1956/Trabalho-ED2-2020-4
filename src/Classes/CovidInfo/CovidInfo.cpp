#include "./CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


CovidInfo::CovidInfo(string date,string state,string city , int code , int cases , int deaths)
{

  this->date = date;
  this->cases = cases;
  this->city = city;
  this->code = code;
  this->cases = cases;
  this->deaths = deaths;
}


void CovidInfo::printInfo()
{
  cout << "Data" << date << endl;
  cout << "Casos" << cases << endl;
  cout << "Cidade" << city << endl;
  cout << "Code" << code << endl;
}

