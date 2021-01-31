#include "./FileHandler.h"
#include "../CovidStatistics/CovidStatistics.cpp"
#include "../CovidInfo/CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <functional>

using namespace std;

//Função para obter n registros aleatório do CSV processado
vector<CovidInfo> FileHandler::getNCovidInfos(int n)
{
  string date, state, city, code, dailyCases, totalCases, deaths, line;
  //Abre o csv pré-processado
  ifstream arq("brazil_covid19_cities_processado.csv");
  int linesProcessed = 0;
  vector<CovidInfo> file;
  if (arq.is_open())
  {
    //Vai ate o final do arquivo separando cada elemento do csv por ,
    while (!arq.eof() && linesProcessed < n)
    {
      getline(arq, date, ',');
      getline(arq, state, ',');
      getline(arq, city, ',');
      getline(arq, code, ',');
      getline(arq, dailyCases, ',');
      getline(arq, totalCases, ',');
      getline(arq, deaths, ',');
      //Pula a primeira linha do arquivo , pois é o header informativo o que cada coluna significa
      if (linesProcessed >= 1)
      {
        //Criado objeto covid info e feito as transformações para int necessarias
        CovidInfo *line = new CovidInfo(date, state, city, stoi(code), stoi(dailyCases), stoi(totalCases), stoi(deaths));
        file.push_back(*line);
      }
      linesProcessed++;
    }
  }
  arq.close();
  /*Apos ter salvo os dados do csv processado na memória utilizando o Vector 
    passo para a etapa de geração de número aleatorios
  */
  //Funções/Variaveis para gerar os números aleatórios
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution(0, file.size() - 1);
  vector<CovidInfo> sortedInfos;
  int drawn = 0;

  //Vetor auxiliar para eu controlar quais indices ja foram gerados
  vector<bool> usedIndexs;
  for (int i = 0; i < file.size(); i++)
    usedIndexs.push_back(false);

  for (int i = 0; i < n - 1; i++)
  {
    //Garanto que o indice que gerei ainda não foi utilizado , para não ocorrerem duplicatas.
    while (usedIndexs[drawn])
      drawn = distribution(generator);

    sortedInfos.push_back(file.at(drawn));
    //Adiciono o número sorteado no meu vetor de indices já sorteados
    usedIndexs[drawn] = true;
  }

  //Código para desalocar memória do vector https://www.techiedelight.com/delete-vector-free-memory-cpp/
  file.clear();
  file.shrink_to_fit();

  return sortedInfos;
}

/*Função para armazenar os registros do csv brazil_covid19_cities.csv em um Array da classe CovidInfo*/
vector<CovidInfo> FileHandler::csvHandler(string filename)
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

      //Pula a primeira linha do arquivo , pois é o header informativo o que cada coluna significa
      if (line >= 1)
      {
        //Criado objeto covid info e feito as transformações para int necessarias
        CovidInfo *line = new CovidInfo(date, state, name, stoi(code), stoi(cases), stoi(deaths));
        CovidFile->push(line);
        line = NULL;
      }
      line++;
    }
    return CovidFile->getCovidInfoList();
    cout << "Arquivo processado com sucesso" << endl;
  }
  else
  {

    cout << "Nao foi possivel abrir o arquivo" << endl;
  }
  vector<CovidInfo> teste;
  return teste;
}