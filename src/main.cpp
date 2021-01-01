#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include "./Classes/FileHandler/FileHandler.cpp"

using namespace std;

int main(int argc, char** argv)
{  
  FileHandler *FileReader = new FileHandler();
  FileReader->csvHandler("brazil_covid19_cities.csv");
  return 0;
}