#include "./FileHandler.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


void FileHandler::printFile(vector<string> file){
  int j = 0;
  for(int i = 0 ; i < file.size() ; i++){
    cout << file.at(i) << ",";
    j++;
    if(j == 6){
       cout << endl;
        j = 0;
      }
    }
}



void FileHandler::csvHandler(string filename)
{

  string line, lineItem;
  vector<string> processedCsv;
  ifstream arq(filename);
  int count = 0;
  if (arq.is_open())
  {
    while (!arq.eof())
    {
      getline(arq, line);
      for (int i = 0; i < line.size(); i++)
      {
          lineItem = "";
          while (line[i] != ',' &&  i < line.size() - 1)
          {
            lineItem.push_back(line[i]);
            i++;
          }
          processedCsv.push_back(lineItem);
      }
      count++;
    }
    cout << "Arquivo processado com sucesso" << endl;
    //printFile(processedCsv);
  
  }
  else
  {
    cout << "Nao foi possivel abrir o arquivo" << endl;
  }
}