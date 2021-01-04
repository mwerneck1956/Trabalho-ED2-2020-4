#include "./FileHandler.h"
#include "../CovidStatistics/CovidStatistics.cpp"
#include "../CovidInfo/CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void FileHandler::printFile(vector<string> file)
{
  int j = 0;
  for (int i = 0; i < file.size(); i++)
  {
    cout << file.at(i) << ",";
    j++;
    if (j == 6)
    {
      cout << endl;
      j = 0;
    }
  }
}

void FileHandler::csvHandler(string filename)
{

  string date, state, name, code, cases, deaths;
  CovidStatistics *CovidFile = new CovidStatistics();
  ifstream arq(filename);

  int line = 0;
  if (arq.is_open())
  {
    //Vai ate o final do arquivo separando cada elemento do csv por , 
    while (!arq.eof())
    {

      getline(arq, date, ',');
      getline(arq, state, ',');
      getline(arq, name, ',');
      getline(arq, code, ',');
      getline(arq, cases, ',');
      getline(arq, deaths);

      if (line >= 1)
      {
        //Criado objeto covid info e feito as transformações para int necessarias
        CovidInfo *line = new CovidInfo(date, state, name, stoi(code), stoi(cases), stoi(deaths));
        CovidFile->push(line);
        line = NULL;
      }
      line ++;
    }
    cout << "Arquivo processado com sucesso" << endl;
    CovidFile->printDates();
  }

  else
  {
    cout << "Nao foi possivel abrir o arquivo" << endl;
  }
}