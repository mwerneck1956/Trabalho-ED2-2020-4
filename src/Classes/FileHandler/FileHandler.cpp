#include "../Headers/FileHandler.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void FileHandler::csvHandler(string filename, int tamBloco)
{

  string linha, linhaProcessada;
  ifstream arq("./projeto.csv");
  int count = 0, countChar = 0, cou = 0,countItem=0;
  if (arq.is_open())
  {
    cout << "File Opened" << endl;
    while (!arq.eof())
    {
      if (cou == 10)
      break;
      getline(arq, linha);
      int z = 0;
      for (int i = 0; i < linha.size(); i++)
      {
        if (linha[i] == '"')
        {
          i++;
          while (linha[i] != '"')
          {
            linhaProcessada.push_back(linha[i]);
            z++;
            i++;
            if (linha[i] == '[')
            {
              i++;
              while (linha[i] != ']')
              {
                linhaProcessada.push_back(linha[i]);
                z++;
                i++;
              }
            }
          }
          linhaProcessada.push_back('\n');
          i++;
          z++;
        }
      }
      linha[z] = '\n';
      cout << "Terminou a linha : " << cou << endl;
      cout << linhaProcessada << endl;
      cout++;
    }
  }
  else
  {
    cout << "Nao foi possivel abrir o arquivo" << endl;
  }
}