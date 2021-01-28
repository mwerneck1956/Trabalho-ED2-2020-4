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

void Testing::StatisticalAnalysis(int M)
{
  ofstream saida;

  clock_t startTime = 0, finalTime;

  int N[5] = {10000, 50000, 100000, 500000, 1000000};

  float mergeTime[5] = {0, 0, 0, 0, 0};
  float quickTime[5] = {0, 0, 0, 0, 0};
  float shellTime[5] = {0, 0, 0, 0, 0};

  int mergeComparisons[5] = {0, 0, 0, 0, 0};
  int comparisonsQuick[5] = {0, 0, 0, 0, 0};
  int comparisonsShell[5] = {0, 0, 0, 0, 0};

  int mergeSwaps[5] = {0, 0, 0, 0, 0};
  int swapsQuick[5] = {0, 0, 0, 0, 0};
  int swapsShell[5] = {0, 0, 0, 0, 0};

  float timeAvgMerge[5] = {0, 0, 0, 0, 0};
  float timeAvgQuick[5] = {0, 0, 0, 0, 0};
  float timeAvgShell[5] = {0, 0, 0, 0, 0};

  int comparisonsAvgMerge[5] = {0, 0, 0, 0, 0};
  int comparisonsAvgQuick[5] = {0, 0, 0, 0, 0};
  int comparisonsAvgShell[5] = {0, 0, 0, 0, 0};

  int swapsAvgMerge[5] = {0, 0, 0, 0, 0};
  int swapsAvgQuick[5] = {0, 0, 0, 0, 0};
  int swapsAvgShell[5] = {0, 0, 0, 0, 0};

  Sorting *Sort = new Sorting();
  FileHandler *File = new FileHandler();

  int algoritmoSelecionado = SelecionarAlgoritmo();

  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < M; j++)
    {
      vector<CovidInfo> notSorted = File->getNCovidInfos(N[i]);
      vector<CovidInfo> toSort = notSorted;

      if (algoritmoSelecionado == 1)
      {

        startTime = clock();
        Sort->mergeSortCases(toSort, 0, N[i] - 1, mergeComparisons[i], mergeSwaps[i]);
        finalTime = clock();
        float totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
        mergeSwaps[i] += mergeSwaps[i];
        mergeComparisons[i] += mergeComparisons[i];
        mergeTime[i] += totalTime;
      }

      if (algoritmoSelecionado == 2)
      {

        startTime = clock();
        Sort->shellSortCases(toSort, N[i] - 1, comparisonsShell[i], swapsShell[i]);
        finalTime = clock();
        float totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
        swapsShell[i] += swapsShell[i];
        comparisonsShell[i] += comparisonsShell[i];
        shellTime[i] += totalTime;
      }

      //Tem q arrumar a chamada do QuickSort

      /*if (algoritmoSelecionado == 3) 
      {

        startTime = clock();
        Sort->quickSortCases(toSort, N[i] - 1, comparisonsQuick[i], swapsQuick[i]);
        finalTime = clock();
        float totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
        swapsQuick[i] += swapsQuick[i];
        comparisonsQuick[j] += comparisonsQuick[i];
        quickTime[i] += totalTime;
      }*/
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

        cout << "-------------------------------------------------------------------------------" << endl;
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

  cout << "-------------------------------------------------------------------------------" << endl;

  if (algoritmoSelecionado == 2)
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

          cout << "-------------------------------------------------------------------------------" << endl;
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
  }

  cout << "-------------------------------------------------------------------------------" << endl;

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