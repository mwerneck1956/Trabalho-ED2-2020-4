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

  cout << "Digite [1] para escrever a saida em um arquivo txt;" << endl;
  cout << "Digite [2] para escrever a saida no console;" << endl;

  cout << "----------------------------------------------------" << endl;

  cin >> saidaSelecionada;

  while (saidaSelecionada != 1 && saidaSelecionada != 2)
  {

    cout << "Digite um numero valido!" << endl;
    cin >> saidaSelecionada;
  }

  return saidaSelecionada;
}

vector<CovidInfo> Testing::selectRandomCases()
{
  int n;
  //@todo mudar para casos fixos 10.000,50.000,100.000,500.000,1.000.000
  cout << "-------------------------------------------------------------------------------" << endl;
  cout << "Selecione o numero de instâncias para teste" << endl;
  cout << "Obs: (deve ser um numero entre 1 e 1000000)" << endl;
  cout << "-------------------------------------------------------------------------------" << endl;
  cin >> n;
  while (n <= 1 || n >= 1000000)
  {
    cout << "Opção invalida" << endl;
    cin >> n;
  }
  FileHandler fileHandler;
  vector<CovidInfo> covidArray = fileHandler.getNCovidInfos(n);

  return covidArray;
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
  clock_t tempo_inicio = clock();
  //Abre o arquivo de texto , desmembra o mesmo , e salva em um vector de CovidInfo
  vector<CovidInfo> processedFile = FileReader->csvHandler(filename != "" ? filename : "brazil_covid19_cities.csv");
  cout << "Arquivo Desmembrado com Sucesso" << endl;
  //Ordenação do vetor por (Estado,Cidade) e data.
  sorting.shellSortStateCityDate(processedFile, processedFile.size());
  //Geração do novo arquivo csv com os dados processados
  statistics.dailyCasesTotalizers(processedFile);
  cout << "Arquivo pre-processado com sucesso!" << endl;
  clock_t tempo_termino = clock();
  processingTime = (tempo_termino - tempo_inicio) / ((float)CLOCKS_PER_SEC);
  //Para desalocar o vector da memória
  processedFile = vector<CovidInfo>();
}

void Testing::executeSorting(int choice, vector<CovidInfo> *covidInfoSet)
{
  Sorting sorting;
  int comparacoes = 0, trocas = 0;
  switch (choice)
  {
  case 1:
    sorting.mergeSortCases(*covidInfoSet, 0, covidInfoSet->size(), comparacoes, trocas);
    break;
  case 2:
    sorting.shellSortCases(*covidInfoSet, covidInfoSet->size(), comparacoes, trocas);
    break;
  case 3:
    sorting.quicksortXD(*covidInfoSet, 0, covidInfoSet->size(), comparacoes, trocas);
    break;
  default:
    break;
  }
}

int Testing::selectFirstPhase()
{
  int option;

  cout << "-------------------------------------------------------------------------------------" << endl;
  cout << "Processamento dos Dados: " << endl;
  cout << "O Arquivo processado sera salvo no arquivo :  brazil_covid19_cities_processado.csv" << endl;
  cout << "------------------------------------------------------------------------------------" << endl;

  cout << "Digite [1] para comecar o processamento do arquivo csv" << endl;
  cout << "Digite [2] para pular o pre-processamento(Somente se ja tiver o arquivo pre-processado salvo)" << endl;
  cin >> option;
  while (option != 1 && option != 2)
  {
    cout << "Digite uma opcao valida!" << endl;
    cin >> option;
  }

  return option;
}

void Testing::writeOutFile(vector<CovidInfo> &data, int out)
{
  if (out == 1)
  {
    ofstream arq("saidaTestes.txt");
    for (int i = 0; i < 100; i++)
    {
      arq << data.at(i).date << endl;
      arq << data.at(i).state << "-" << data.at(i).city << endl;
      arq << "Novos Casos : " << data.at(i).cases << endl;
      arq << "Casos Totais : " << data.at(i).totalCases << endl;
      arq << "Mortes : " << data.at(i).totalCases << endl;
    }
    cout << "Arquivo saidaTestes.txt Gerado Com Sucesso!!" << endl;
  }
  else if (out == 2)
  {
    cout << "Dados Apos a Ordenação" << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < 10; i++)
    {
      cout << data.at(i).date << endl;
      cout << data.at(i).state << "-" << data.at(i).city << endl;
      cout << "Novos Casos : " << data.at(i).cases << endl;
      cout << "Casos Totais : " << data.at(i).totalCases << endl;
      cout << "Mortes : " << data.at(i).totalCases << endl;
    }
  }
}

void Testing::execute(string filename)
{
  FileHandler *FileReader = new FileHandler();
  Sorting sorting;
  CovidStatistics statistics;
  clock_t tempo_processamento = clock();
  int firstPhase = selectFirstPhase();
  if (firstPhase == 1)
    this->PreProcessing(filename, tempo_processamento);
  vector<CovidInfo> processedCovidInfo = this->selectRandomCases();
  this->executeSorting(SelecionarAlgoritmo(), &processedCovidInfo);
  int saida = this->SelecionarSaida();
  writeOutFile(processedCovidInfo, saida);
}
void Testing::StatisticalAnalysis(int M)
{
  ofstream exit;
  float timeAvgSort[5] = {0, 0, 0, 0, 0};
  int comparisonsAvgSort[5] = {0, 0, 0, 0, 0};
  int swapsAvgSort[5] = {0, 0, 0, 0, 0};
  clock_t startTime = 0, finalTime;

  int N[5] = {10000, 50000, 100000, 500000, 1000000};

  float sortTime[5] = {0, 0, 0, 0, 0};

  int sortComparisons[5] = {0, 0, 0, 0, 0};
  int sortSwaps[5] = {0, 0, 0, 0, 0};

  Sorting *Sort = new Sorting();
  FileHandler *File = new FileHandler();

  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < M; j++)
    {
      vector<CovidInfo> toSort = File->getNCovidInfos(N[i]);

      startTime = clock();
      Sort->shellSortCases(toSort, N[i] - 1, sortComparisons[i], sortSwaps[i]);
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

  /*for(int i = 0; i < 5; i++)
    Exit(M, N[i], algoritmoSelecionado, saidaSelecionada, sortTime[i], sortComparisons[i], sortSwaps[i]);*/

  string nomeAlgoritmo;

  /*if (saidaSelecionada == 10)
    exit.open("saida.txt", ios::app);

    algoritmoSelecionado == 1 ? nomeAlgoritmo = "MergeSort" : algoritmoSelecionado == 2 ? nomeAlgoritmo = "ShellSort" : nomeAlgoritmo = "QuickSort";

  for (int i = 0; i < 5; i++)
  {
    timeAvgSort[i] = sortTime[i] / 5;
    comparisonsAvgSort[i] = sortComparisons[i] / 5;
    swapsAvgSort[i] = sortSwaps[i] / 5;

    if (saidaSelecionada == 10)
    {

      exit << "Os resultados do algoritmo " << nomeAlgoritmo << " para um vetor randomico de tamanho " << N[i] << " foram: " << endl;
      exit << "Media de tempo dos " << M << " conjuntos: " << timeAvgSort[i] << endl;
      exit << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgSort[i] << endl;
      exit << "Media de trocas dos " << M << " conjuntos: " << swapsAvgSort[i] << endl;

      exit << "-------------------------------------------------------------------------------" << endl;
    }

    else
    {*/
  for (int i = 0; i < 5; i++)
  {
    timeAvgSort[i] = sortTime[i] / 5;
    comparisonsAvgSort[i] = sortComparisons[i] / 5;
    swapsAvgSort[i] = sortSwaps[i] / 5;
    cout << "Tempo: " << i << sortTime[i] << endl;
    cout << "Comparacoes: " << i << sortComparisons[i] << endl;
    cout << "Trocas: " << i << sortSwaps[i] << endl;
    cout << "Os resultados do algoritmo " << nomeAlgoritmo << " para um vetor randomico de tamanho " << N[i] << " foram: " << endl;
    cout << "Media de tempo dos " << M << " conjuntos: " << timeAvgSort[i] << endl;
    cout << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgSort[i] << endl;
    cout << "Media de trocas dos " << M << " conjuntos: " << swapsAvgSort[i] << endl;

    cout << "-------------------------------------------------------------------------------" << endl;
  }
  //}
  //}

  exit.close();

  cout << "-------------------------------------------------------------------------------" << endl;
}

void Testing::estatisticaDePobre(int M)
{
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

  int contadorSwapsShell[5] = {0, 0, 0, 0, 0};
  int contadorComparacoesShell[5] = {0, 0, 0, 0, 0};

  int contadorSwapsMerge[5] = {0, 0, 0, 0, 0};
  int contadorComparacoesMerge[5] = {0, 0, 0, 0, 0};

  int contadorSwapsQuick[5] = {0, 0, 0, 0, 0};
  int contadorComparacoesQuick[5] = {0, 0, 0, 0, 0};

  Sorting *Sort = new Sorting();
  FileHandler *File = new FileHandler();

  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < M; j++)
    {
      vector<CovidInfo> notSorted = File->getNCovidInfos(N[i]);
      vector<CovidInfo> toSort = notSorted;

      mergeComparisons[i] = 0;
      mergeSwaps[i] = 0;
      startTime = clock();
      Sort->mergeSortCases(toSort, 0, N[i] - 1, mergeComparisons[i], mergeSwaps[i]);
      finalTime = clock();
      float totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
      contadorSwapsMerge[i] += mergeSwaps[i];
      contadorComparacoesMerge[i] += mergeComparisons[i];
      mergeTime[i] += totalTime;
      vector<CovidInfo>().swap(toSort);

      toSort = notSorted;
      comparisonsShell[i] = 0;
      swapsShell[i] = 0;
      startTime = clock();
      Sort->shellSortCases(toSort, N[i] - 1, comparisonsShell[i], swapsShell[i]);
      finalTime = clock();
      totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
      contadorSwapsShell[i] += swapsShell[i];
      contadorComparacoesShell[i] += comparisonsShell[i];
      shellTime[i] += totalTime;
      vector<CovidInfo>().swap(toSort);

      toSort = notSorted;
      comparisonsQuick[i]=0;
      swapsQuick[i]=0;
      startTime = clock();
      Sort->quicksortXD(toSort, 0, N[i] - 1, comparisonsQuick[i], swapsQuick[i]);
      finalTime = clock();
      totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
      contadorSwapsQuick[i] += swapsQuick[i];
      contadorComparacoesQuick[j] += comparisonsQuick[i];
      quickTime[i] += totalTime;
    }
  }

  for (int j = 0; j < 5; j++)
  {
    timeAvgShell[j] = shellTime[j] / M;
    comparisonsAvgShell[j] = contadorComparacoesShell[j] / M;
    swapsAvgShell[j] = contadorSwapsShell[j] / M;
    cout << "Os resultados do algoritmo Shellsort para um vetor randomico de tamanho " << N[j] << " foram " << endl;
    cout << "Media de tempo dos " << M << " conjuntos: " << timeAvgShell[j] << endl;
    cout << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgShell[j] << endl;
    cout << "Media de trocas dos " << M << " conjuntos: " << swapsAvgShell[j] << endl
         << endl;
  }
  cout << "-------------------------------------------------------------------------------" << endl;

  for (int j = 0; j < 5; j++)
  {
    timeAvgMerge[j] = mergeTime[j] / M;
    comparisonsAvgMerge[j] = contadorComparacoesMerge[j] / M;
    swapsAvgMerge[j] = contadorComparacoesMerge[j] / M;

    cout << "Os resultados do algoritmo MergeSort para um vetor randomico de tamanho " << N[j] << " foram " << endl;
    cout << "Media de tempo dos " << M << " conjuntos: " << timeAvgMerge[j] << endl;
    cout << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgMerge[j] << endl;
    cout << "Media de trocas dos " << M << " conjuntos: " << swapsAvgMerge[j] << endl
         << endl;
  }

  cout << "-------------------------------------------------------------------------------" << endl;

  for (int j = 0; j < 5; j++)
  {
    timeAvgQuick[j] = quickTime[j] / M;
    comparisonsAvgQuick[j] = contadorComparacoesQuick[j] / M;
    swapsAvgQuick[j] = contadorSwapsQuick[j] / M;
    cout << "Os resultados do algoritmo QuickSort para um vetor randomico de tamanho " << N[j] << " foram " << endl;
    cout << "Media de tempo dos " << M << " conjuntos: " << timeAvgQuick[j] << endl;
    cout << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvgQuick[j] << endl;
    cout << "Media de trocas dos " << M << " conjuntos: " << swapsAvgQuick[j] << endl
         << endl;
  }
  //cout << "-------------------------------------------------------------------------------" << endl;
  //CriarArquivoSaida(Resultados);
}
