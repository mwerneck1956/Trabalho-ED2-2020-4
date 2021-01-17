#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include "./Classes/CovidInfo/CovidInfo.h"
#include "./Classes/FileHandler/FileHandler.cpp"
#include "./Classes/CovidStatistics/CovidStatistics.h"
#include "./Classes/Sorting/Sorting.cpp"
#include <locale>

using namespace std;

int selecionarAlgoritmo()
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

  while(algoritmoSelecionado != 1 && algoritmoSelecionado != 2 && algoritmoSelecionado != 3)
  {  
    
    cout << "Digite um numero valido!" << endl;
    cin >> algoritmoSelecionado;

  }

  return algoritmoSelecionado;

}

int main(int argc, char** argv)
{  

  int algoritmoSelecionado = -1;

  setlocale(LC_ALL,"");
  
  //Sorting *Sort = new Sorting();
  FileHandler *FileReader = new FileHandler();


  vector<CovidInfo> CovidInfoList = FileReader->csvHandler(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");
  cout << "Acabou o processamento" << endl;
  CovidStatistics *statistic = new CovidStatistics();
  statistic->setCovidInfoList(CovidInfoList);
  //for(int i = 0 ; i < 50 ; i++)
  //cout << "Cidade : " << CovidInfoList.at(i).city << " Casos : " << CovidInfoList.at(i).cases << endl;
  statistic->dailyCasesTotalizers();

  Sorting *Sort = new Sorting();

  algoritmoSelecionado = selecionarAlgoritmo();

  if(algoritmoSelecionado == 1)
  {
    cout << "Algoritmo MergeSort selecionado" << endl;

    Sort->mergeSort(CovidInfoList, 0, 12);
    Sort->imprimirInformacoes(CovidInfoList, 12);
  }

  if(algoritmoSelecionado == 2)
  {
    cout << "Algoritmo QuickSort selecionado" << endl;

    //Sort->quickSort(CovidInfoList, 0, 12);
    //Sort->imprimirInformacoes(CovidInfoList, 12);
  }

  if(algoritmoSelecionado == 3)
  {
    cout << "Algoritmo ShellSort selecionado" << endl;

    //Sort->shellSort(CovidInfoList, 0, 12);
    //Sort->imprimirInformacoes(CovidInfoList, 12);
  }





  delete statistic;

  return 0;
}
