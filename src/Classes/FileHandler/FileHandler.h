
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
public:
  //Função de processamento do csv
  vector<CovidInfo> csvHandler(string filename);
  //Função para obter n registros aleatórios do arquivo processado
  vector<CovidInfo> getNCovidInfos(int n);
};

#endif