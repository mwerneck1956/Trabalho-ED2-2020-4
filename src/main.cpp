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



int main(int argc, char** argv)
{  
  setlocale(LC_ALL,"");
  
  //Sorting *Sort = new Sorting();
  FileHandler *FileReader = new FileHandler();
  //O arquivo de texto passado pelo usuário fica no argv[1]
  //FileReader->csvHandler(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");

  vector<CovidInfo> CovidInfoList = FileReader->csvHandler(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");

  CovidStatistics *naoSei = new CovidStatistics();
  Sorting *mergeSorte = new Sorting();
  Sorting *shellSorte = new Sorting();
  //mergeSorte->mergeSort(CovidInfoList, 0, 8);
  shellSorte->shellSort(CovidInfoList);
  shellSorte->imprimir(CovidInfoList, 8);
  //naoSei->setCovidInfoList(CovidInfoList);
  //naoSei->printDates();
  
  
  //string a = "Brasiléia" , b = "Bujari";
  //0 Se são iguais
  //1 se o atual for maior que comparado
  //-1 se o atual for menor do que o comparado
  //cout << a.compare(b);
  
  
 
 

  return 0;
}
