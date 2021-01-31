#include "./CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//Para Armazenamento a ser processado
CovidInfo::CovidInfo()
{
}

//Para o arquivo não processado
CovidInfo::CovidInfo(string date, string state, string city, int code, int cases, int deaths)
{

  this->date = date;
  this->state = state;
  this->city = city;
  this->code = code;
  this->cases = cases;
  this->deaths = deaths;
}

//Para Armazenamento do arquivo processado
CovidInfo::CovidInfo(string date, string state, string city, int code, int cases, int totalCases, int deaths)
{

  this->date = date;
  this->state = state;
  this->city = city;
  this->code = code;
  this->cases = cases;
  this->totalCases = totalCases;
  this->deaths = deaths;
}

CovidInfo::~CovidInfo()
{
}

