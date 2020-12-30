#include "./FileHandler.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void FileHandler::csvHandler(string filename, int tamBloco)
{

  string line, lineItem;
  vector<string> processedCsv;
  ifstream arq("brazil_covid19_cities.csv");
  int count = 0;
  if (arq.is_open())
  {
    while (!arq.eof())
    {
      if(count == 10) break;
      getline(arq, line);
      for (int i = 0; i < line.size(); i++)
      {
          lineItem = "";
          while (line[i] != ',' && i < line.size())
          {
            lineItem.push_back(line[i]);
            i++;
          }
        
          processedCsv.push_back(lineItem);
      }
      count++;
    }
      cout << "csv size" << processedCsv.at(1) << endl;
      for(int i = 0 ; i < processedCsv.size() ; i++){
        cout << processedCsv.at(i) << "," << endl;
      }
      
  }
  else
  {
    cout << "Nao foi possivel abrir o arquivo" << endl;
  }
}