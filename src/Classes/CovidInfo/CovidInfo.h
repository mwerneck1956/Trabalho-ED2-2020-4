
#ifndef COVIDINFO_H_INCLUDED
#define COVIDINFO_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class CovidInfo
{
private:
public:
  string date;
  string state;
  string city;
  float code;
  int cases;
  int deaths;
  int totalCases;
  //Função de processamento do csv
  CovidInfo();
  CovidInfo(string date, string state, string city, int code, int cases, int deaths);
  CovidInfo(string date, string state, string city, int code, int cases, int totalCases, int deaths);

  ~CovidInfo();
  void printInfo();

  friend bool operator<(const CovidInfo &c1, const CovidInfo &c2)
  {
    if (c1.state == c2.state and c1.city == c2.city)
    {
      return c1.date < c2.date;
    }
    else if (c1.state == c2.state)
    {
      return c1.city < c2.city;
    }

    return c1.state < c2.state;
  }

  friend bool operator<=(const CovidInfo &c1, const CovidInfo &c2)
  {
    if (c1.state == c2.state and c1.city == c2.city)
    {
      return c1.date <= c2.date;
    }
    else if (c1.state == c2.state)
    {
      return c1.city <= c2.city;
    }

    return c1.state <= c2.state;
  }
};

#endif