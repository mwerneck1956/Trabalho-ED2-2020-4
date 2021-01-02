#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include "./Classes/FileHandler/FileHandler.cpp"
#include "./Classes/Sorting/Sorting.cpp"

using namespace std;

int main(int argc, char** argv)
{  

  Sorting *Sort = new Sorting();
  FileHandler *FileReader = new FileHandler();
  FileReader->csvHandler("brazil_covid19_cities.csv");

  return 0;
}
/* Teste do Merge Sort */

/*  Sorting *Sort = new Sorting();
  int tam = 8;
  int vet[tam] = {39, 5, 12, 1, 34, 64, 7, 76};
   Sort->mergeSort(vet,0,tam);
  for(int i = 0 ; i < 8 ; i++)
  cout << vet[i] << ",";

  cout << endl;
*/