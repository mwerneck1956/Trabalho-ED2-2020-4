#include <iostream>
//#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include "./Classes/CovidInfo/CovidInfo.h"
#include "./Classes/FileHandler/FileHandler.cpp"
#include "./Classes/CovidStatistics/CovidStatistics.h"
#include "./Classes/Sorting/Sorting.cpp"
#include <locale>
#include <ctime>

using namespace std;

int SelecionarSaida()
{
  int saidaSelecionada;

  cout << "----------------------------------------------------" << endl;
  cout << "Selecione a saida dos resultados de teste: " << endl;
  cout << "----------------------------------------------------" << endl;

  cout << "Digite 10 para escrever a saida em um arquivo txt;" << endl;
  cout << "Digite 100 para escrever a saida no console;" << endl;

  cout << "----------------------------------------------------" << endl;

  cin >> saidaSelecionada;

  while (saidaSelecionada != 10 && saidaSelecionada != 100)
  {

    cout << "Digite um numero valido!" << endl;
    cin >> saidaSelecionada;
  }

  return saidaSelecionada;
}

int SelecionarAlgoritmo()
{
  int algoritmoSelecionado;

  cout << "------------------------------------" << endl;
  cout << "Selecione o algoritmo de ordenacao: " << endl;
  cout << "------------------------------------" << endl;

  cout << "Digite 1 para MergeSort;" << endl;
  cout << "Digite 2 para QuickSort;" << endl;
  cout << "Digite 3 para ShellSort;" << endl;

  cout << "------------------------------------" << endl;

  cin >> algoritmoSelecionado;

  while (algoritmoSelecionado != 1 && algoritmoSelecionado != 2 && algoritmoSelecionado != 3)
  {

    cout << "Digite um numero valido!" << endl;
    cin >> algoritmoSelecionado;
  }

  return algoritmoSelecionado;
}

int main(int argc, char **argv)
{
  float tempoExecucao;
  clock_t tempo_inicio = 0, tempo_termino;

  int algoritmoSelecionado = -1;
  int saidaSelecionada = -1;

  setlocale(LC_ALL, "");

  FileHandler *FileReader = new FileHandler();

  vector<CovidInfo> CovidInfoList = FileReader->csvHandler(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");
 
  CovidStatistics *statistic = new CovidStatistics();

  Sorting *Sort = new Sorting();

  /*Sort->mergeSort(CovidInfoList,0,CovidInfoList.size() - 1);
  Sort->imprimirInformacoes(CovidInfoList,100);
  
  statistic->setCovidInfoList(CovidInfoList);


  statistic->dailyCasesTotalizers();*/

  algoritmoSelecionado = SelecionarAlgoritmo();

  saidaSelecionada = SelecionarSaida();

  if (algoritmoSelecionado == 1)
  {
    cout << "Algoritmo MergeSort selecionado" << endl;

    tempo_inicio = clock();
    Sort->mergeSort(CovidInfoList, 0, 12);
    tempo_termino = clock();
    tempoExecucao = ((tempo_termino - tempo_inicio) / (float)CLOCKS_PER_SEC);

    Sort->imprimirInformacoes(CovidInfoList, 12, tempoExecucao);

  }

  if (algoritmoSelecionado == 2)
  {
    cout << "Algoritmo QuickSort selecionado" << endl;

    tempo_inicio = clock();
    Sort->quickSort(CovidInfoList, 0, 12, 'c'); //'c' para ordenar por casos, 's' para State-City-Date
    tempo_termino = clock();
    tempoExecucao = ((tempo_termino - tempo_inicio) / (float)CLOCKS_PER_SEC);
    Sort->imprimirInformacoes(CovidInfoList, 12, tempoExecucao);
  }

  if (algoritmoSelecionado == 3)
  {
    cout << "Algoritmo ShellSort selecionado" << endl;

    //Sort->shellSort(CovidInfoList, 0, 12);
    //Sort->imprimirInformacoes(CovidInfoList, 12);
  }

 // delete statistic;

  return 0;
}
