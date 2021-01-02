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
  //O arquivo de texto passado pelo usuário fica no argv[1]
  FileReader->csvHandler(argv[1] != NULL ? argv[1] : "brazil_covid19_cities.csv");

  return 0;
}
