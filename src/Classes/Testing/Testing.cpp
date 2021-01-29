#include "./Testing.h"
#include "../FileHandler/FileHandler.h"
#include "../CovidInfo/CovidInfo.h"
#include "../CovidStatistics/CovidStatistics.h"
#include "../Sorting/Sorting.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <vector>

using namespace std;

Testing::Testing()
{
}

int Testing::SelecionarSaida()
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

void Testing::SelectRandomCases()
{
  int n;

  //@todo mudar para casos fixos 10.000,50.000,100.000,500.000,1.000.000
  cout << "-------------------------------------------------------------------------------" << endl;
  cout << "Selecione o número de instâncias para teste" << endl;
  cout << "Obs: (deve ser um número entre 1 e 1000000)" << endl;
  cout << "-------------------------------------------------------------------------------" << endl;
  cin >> n;
  while (n <= 1 || n >= 100000)
  {
    cout << "Opção invalida" << endl;
    cin >> n;
  }
  FileHandler fileHandler;
  vector<CovidInfo> covidArray = fileHandler.getNCovidInfos(n);

  int i = 0;
  for (CovidInfo a : covidArray)
  {
    i++;
    if (i > 20)
      break;
    cout << a.city << endl;
    cout << a.cases << endl;
  }
}

int Testing::SelecionarAlgoritmo()
{
  int algoritmoSelecionado;

  cout << "-------------------------------------------------------------------------------" << endl;
  cout << "Selecione o algoritmo de ordenacao: " << endl;
  cout << "-------------------------------------------------------------------------------" << endl;

  cout << "Digite [1] para MergeSort;" << endl;
  cout << "Digite [2] para ShellSort;" << endl;
  cout << "Digite [3] para QuickSort;" << endl;

  cout << "-------------------------------------------------------------------------------" << endl;

  cin >> algoritmoSelecionado;

  while (algoritmoSelecionado != 1 && algoritmoSelecionado != 2 && algoritmoSelecionado != 3)
  {
    cout << "Digite um numero valido!" << endl;
    cin >> algoritmoSelecionado;
  }

  return algoritmoSelecionado;
}

void Testing::PreProcessing(string filename, clock_t &processingTime)
{
  Sorting sorting;
  FileHandler *FileReader = new FileHandler();
  CovidStatistics statistics;
  int option;

  cout << "-------------------------------------------------------------------------------------" << endl;
  cout << "Processamento dos Dados: " << endl;
  cout << "O Arquivo processado sera salvo no arquivo :  brazil_covid19_cities_processado.csv" << endl;
  cout << "------------------------------------------------------------------------------------" << endl;

  cout << "Digite [1] para comecar o processamento do arquivo csv" << endl;

  cin >> option;
  while (option != 1)
  {
    cout << "Digite uma opcao valida!" << endl;
    cin >> option;
  }
  clock_t startTime = clock();
  //Abre o arquivo de texto , desmembra o mesmo , e salva em um vector de CovidInfo
  vector<CovidInfo> processedFile = FileReader->csvHandler(filename != "" ? filename : "brazil_covid19_cities.csv");
  cout << "Arquivo Desmenbrado com Sucesso" << endl;
  //Ordenação do vetor por (Estado,Cidade) e data.
  sorting.mergeSort(processedFile, 0, processedFile.size());
  //Geração do novo arquivo csv com os dados processados
  statistics.dailyCasesTotalizers(processedFile);
  cout << "Arquivo pre-processado com sucesso!" << endl;
  clock_t finalTime = clock();
  processingTime = (finalTime - startTime) / ((float)CLOCKS_PER_SEC);
}

void Testing::Execute(string filename)
{
  clock_t processingTime = clock();

  PreProcessing(filename, processingTime);
  cout << "Tempo total de execução do processamento: " << processingTime << " segundos" << endl;
  /*this->selectRandomCases();
  int outType = this->SelecionarSaida();
  int selectedOrdering = this->SelecionarAlgoritmo();*/
}

void Testing::algumNomeBom(int algoritmoSelecionado)
{
  Sorting *sort = new Sorting();
  clock_t startTime = 0, finalTime;

  startTime = clock();
  algoritmoSelecionado == 1 ? sort->mergeSortCases(toSort, 0, N[i] - 1, sortComparisons[i], sortSwaps[i]) : algoritmoSelecionado == 2 ? sort->shellSortCases(toSort, N[i] - 1, sortComparisons[i], sortSwaps[i])
                                                                                                                                      : sort->quickSortCases(toSort, N[i] - 1, sortComparisons[i], sortSwaps[i]);
  finalTime = clock();
  float totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
  sortSwaps[i] += mergeSwaps[i];
  sortComparisons[i] += mergeComparisons[i];
  sortTime[i] += totalTime;
}

void Testing::StatisticalAnalysis(int M)
{
  ofstream saida;

  clock_t startTime = 0, finalTime;

  int N[5] = {10000, 50000, 100000, 500000, 1000000};

  float sortTime[5] = {0, 0, 0, 0, 0};

  int sortComparisons[5] = {0, 0, 0, 0, 0};

  int sortSwaps[5] = {0, 0, 0, 0, 0};

  float timeAvgSort[5] = {0, 0, 0, 0, 0};

  int comparisonsAvgSort[5] = {0, 0, 0, 0, 0};

  int swapsAvgSort[5] = {0, 0, 0, 0, 0};

  Sorting *Sort = new Sorting();
  FileHandler *File = new FileHandler();

  int algoritmoSelecionado = SelecionarAlgoritmo();

  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < M; j++)
    {
      vector<CovidInfo> toSort = File->getNCovidInfos(N[i]);

      startTime = clock();
      algoritmoSelecionado == 1 ? Sort->mergeSortCases(toSort, 0, N[i] - 1, sortComparisons[i], sortSwaps[i]) : 
      algoritmoSelecionado == 2 ? Sort->shellSortCases(toSort, N[i] - 1, sortComparisons[i], sortSwaps[i]) :
      Sort->quickSortCases(toSort, N[i] - 1, sortComparisons[i], sortSwaps[i]);
      finalTime = clock();
      float totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
      
      sortSwaps[i] += sortSwaps[i];
      sortComparisons[i] += sortComparisons[i];
      sortTime[i] += totalTime;

      vector<CovidInfo>().swap(toSort);
      /*notSorted.clear();
      notSorted.shrink_to_fit();
      toSort.clear();
      toSort.shrink_to_fit();*/
    }
  }

  cout << "-------------------------------------------------------------------------------" << endl;

  int saidaSelecionada = SelecionarSaida();

  if (saidaSelecionada == 10)
  {
    saida.open("saida.txt", ios::app);
  }

  if (algoritmoSelecionado == 1)
  {
    for (int j = 0; j < 5; j++)
    {
      timeAvgMerge[j] = mergeTime[j] / 5;
      comparisonsAvgMerge[j] = mergeComparisons[j] / 5;
      swapsAvgMerge[j] = mergeSwaps[j] / 5;

      if (saidaSelecionada == 10)
      {

        saida << "Os resultados do algoritmo MergeSort para um vetor randomico de tamanho " << N[j] << " foram: " << endl;
        saida << "Media de tempo dos " << M << " conjuntos: " << timeAvgMerge[j] << endl;
        saida << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgMerge[j] << endl;
        saida << "Media de trocas dos " << M << " conjuntos: " << swapsAvgMerge[j] << endl;

        saida << "-------------------------------------------------------------------------------" << endl;
      }

      else
      {
        cout << "Os resultados do algoritmo MergeSort para um vetor randomico de tamanho " << N[j] << " foram: " << endl;
        cout << "Media de tempo dos " << M << " conjuntos: " << timeAvgMerge[j] << endl;
        cout << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgMerge[j] << endl;
        cout << "Media de trocas dos " << M << " conjuntos: " << swapsAvgMerge[j] << endl;

        cout << "-------------------------------------------------------------------------------" << endl;
      }
    }
  }

  /*if (algoritmoSelecionado == 2)
  {

    for (int j = 0; j < 5; j++)
    {

      for (int j = 0; j < 5; j++)
      {
        timeAvgShell[j] = shellTime[j] / 5;
        comparisonsAvgShell[j] = comparisonsShell[j] / 5;
        swapsAvgShell[j] = swapsShell[j] / 5;

        if (saidaSelecionada == 10)
        {

          saida << "Os resultados do algoritmo Shellsort para um vetor randomico de tamanho " << N[j] << " foram: " << endl;
          saida << "Media de tempo dos " << M << " conjuntos: " << timeAvgShell[j] << endl;
          saida << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgShell[j] << endl;
          saida << "Media de trocas dos " << M << " conjuntos: " << swapsAvgShell[j] << endl;

          saida << "-------------------------------------------------------------------------------" << endl;
        }

        else
        {
          cout << "Os resultados do algoritmo Shellsort para um vetor randomico de tamanho " << N[j] << " foram: " << endl;
          cout << "Media de tempo dos " << M << " conjuntos: " << timeAvgShell[j] << endl;
          cout << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgShell[j] << endl;
          cout << "Media de trocas dos " << M << " conjuntos: " << swapsAvgShell[j] << endl;

          cout << "-------------------------------------------------------------------------------" << endl;
        }
      }
    }
  }*/

  /*if (algoritmoSelecionado == 3)
  {

    for (int j = 0; j < 5; j++)
    {
      timeAvgQuick[j] = quickTime[j] / 5;
      comparisonsAvgQuick[j] = comparisonsQuick[j] / 5;
      swapsAvgQuick[j] = swapsQuick[j] / 5;

      if (saidaSelecionada == 10)
      {
        saida << "Os resultados do algoritmo QuickSort para um vetor randomico de tamanho " << N[j] << " foram: " << endl;
        saida << "Media de tempo dos " << M << "conjuntos: " << timeAvgQuick[j] << endl;
        saida << "Media de comparacoes dos " << M << "conjuntos: " << comparisonsAvgQuick[j] << endl;
        saida << "Media de trocas dos " << M << "conjuntos: " << swapsAvgQuick[j] << endl;

        cout << "-------------------------------------------------------------------------------" << endl;
      }

      else
      {
        cout << "Os resultados do algoritmo QuickSort para um vetor randomico de tamanho " << N[j] << " foram: " << endl;
        cout << "Media de tempo dos " << M << "conjuntos: " << timeAvgQuick[j] << endl;
        cout << "Media de comparacoes dos " << M << "conjuntos: " << comparisonsAvgQuick[j] << endl;
        cout << "Media de trocas dos " << M << "conjuntos: " << swapsAvgQuick[j] << endl;

        cout << "-------------------------------------------------------------------------------" << endl;
      }
    }
  }*/
  cout << "-------------------------------------------------------------------------------" << endl;

  saida.close();
}