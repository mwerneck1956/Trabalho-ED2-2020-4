  
#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

class FileHandler
{
private:
  vector<CovidInfo> processedCovidCsv;
public:
  //Função de processamento do csv
  vector<CovidInfo> csvHandler(string filename);
  vector<CovidInfo> getNCovidInfos(int n);
  void  printLine(string line);
  void  printFile(vector<string> file);
  

  
};

#endif