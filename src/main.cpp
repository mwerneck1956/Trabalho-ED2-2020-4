#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "./Classes/CovidInfo/CovidInfo.h"
#include "./Classes/FileHandler/FileHandler.cpp"
#include "./Classes/CovidStatistics/CovidStatistics.h"
#include "./Classes/Sorting/Sorting.cpp"
#include "./Classes/Testing/Testing.h"
#include "./Classes/Testing/Testing.cpp"
#include <locale>
#include <ctime>

using namespace std;

int main(int argc, char **argv)
{
  setlocale(LC_CTYPE, "");
  Testing test;
  int option;
  cout << endl
       << "Trabalho Estrutura de Dados 2 2021/1" << endl;
  cout << "-----------------------------------------------------------" << endl;
  cout << "Digite [1] para começar a rodar o programa" << endl;
  cout << "-----------------------------------------------------------" << endl;
  cin >> option;
  while (option != 1)
  {
    cout << "Opção invalida" << endl;
    cin >> option;
  }
  //Execução do modulo de testes/preProcessamento/Estatistica
  test.Execute(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");
 
  

  return 0;
}
