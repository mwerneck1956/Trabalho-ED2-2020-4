
#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>

class Testing
{
private:

public: 
  Testing();
  int SelecionarSaida();
  int SelecionarAlgoritmo();
  void PreProcessing(string filename , clock_t &processingTime);
  void SelectRandomCases();
  void Execute(string filename);
  void StatisticalAnalysis(int M);
  void algumNomeBom(int algoritmoSelecionado);
  void arquivoSaida();
  
  
};

#endif