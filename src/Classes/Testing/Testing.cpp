#include "./Testing.h"
#include "../FileHandler/FileHandler.h"
#include "../CovidInfo/CovidInfo.h"
#include "../CovidStatistics/CovidStatistics.h"
#include "../Sorting/Sorting.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <vector>

using namespace std;

Testing::Testing()
{
}

//Função para escolha da saida no console ou em arquivo txt
int Testing::SelectOut()
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

/*Função de obtenção dos n registros aleatórios, retorna um vector<CovidInfo> contendos os 
  n registros obtidos
*/
vector<CovidInfo> Testing::selectRandomCases()
{
  int n;
  cout << "-------------------------------------------------------------------------------" << endl;
  cout << "Selecione o numero de instâncias para teste" << endl;
  cout << "Obs: (deve ser um numero entre 1 e 1400000)" << endl;
  cout << "-------------------------------------------------------------------------------" << endl;
  cin >> n;
  while (n <= 1 || n > 1400000)
  {
    cout << "Opção invalida" << endl;
    cin >> n;
  }
  FileHandler fileHandler;
  vector<CovidInfo> covidArray = fileHandler.getNCovidInfos(n);

  return covidArray;
}
/*Função para o usuário selecionar o metodo de ordenação*/
int Testing::SelectSortMethod()
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

//Faz o pre processamento do csv base , e retorna o tamanho do vetor processado gerado
void Testing::PreProcessing(string filename, clock_t &processingTime)
{
  Sorting sorting;
  FileHandler *FileReader = new FileHandler();
  CovidStatistics statistics;
  clock_t tempo_inicio = clock();

  //Abre o arquivo de texto , desmembra o mesmo , e salva em um vector de CovidInfo
  vector<CovidInfo> processedFile = FileReader->csvHandler(filename != "" ? filename : "brazil_covid19_cities.csv");


  //Ordenação do vetor por (Estado,Cidade) e data.
  sorting.shellSortStateCityDate(processedFile, processedFile.size());

  //Geração do novo arquivo csv com os dados processados
  statistics.dailyCasesTotalizers(processedFile);


  clock_t tempo_termino = clock();
  processingTime = (tempo_termino - tempo_inicio) / ((float)CLOCKS_PER_SEC);

  cout << "Arquivo pre-processado com sucesso em " << processingTime << " segundos!" << endl;

  //Para desalocar o vector da memória
  processedFile = vector<CovidInfo>();
}
/*Função para executar o algoritmo de ordeanação escolhido pelo usuário
  e também informar n de trocas ,comparacoes , e tempo total.
*/
void Testing::ExecuteSorting(int choice, vector<CovidInfo> *covidInfoSet)
{
  Sorting sorting;
  int comparisons = 0, swaps = 0;
  clock_t startTime, finalTime;
  startTime = clock();
  switch (choice)
  {
  case 1:
    sorting.mergeSortCases(*covidInfoSet, 0, covidInfoSet->size(), comparisons, swaps);
    break;
  case 2:
    sorting.shellSortCases(*covidInfoSet, covidInfoSet->size(), comparisons, swaps);
    break;
  case 3:
    sorting.quicksortCases(*covidInfoSet, 0, covidInfoSet->size(), comparisons, swaps);
    break;
  default:
    break;
  }
  finalTime = clock();
  cout << "----------------------------------------------------" << endl;
  cout << "Ordenação Finalizada" << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "Tempo de Processamento : " << (finalTime - startTime) / ((float)CLOCKS_PER_SEC) << " segundos" << endl;
  cout << "Número de Comparações : " << comparisons << endl;
  cout << "Número de Trocas : " << swaps << endl;
  cout << "----------------------------------------------------" << endl;
}

//Função para selecionar a função desejada do sistema preProcessamento/Estatisticas/Testes
int Testing::SelectPhase()
{
  int option;

  cout << "-------------------------------------------------------------------------------------------" << endl;
  cout << "Processamento dos Dados" << endl
       << endl;
  cout << "O Arquivo processado sera salvo no arquivo :  brazil_covid19_cities_processado.csv" << endl;
  cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;

  cout << "Digite [1] para comecar o processamento do arquivo csv" << endl;
  cout << "Digite [2] ir para o modulo de testes(Somente se ja tiver o arquivo pre-processado salvo)" << endl;
  cout << "Digite [3] para ir para o modulo de estatisticas(Somente se ja tiver o arquivo pre-processado salvo)" << endl;
  cout << "Digite [0] para sair do programa" << endl;
  cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;

  cin >> option;
  while (option < 1 && option > 3)
  {
    cout << "Digite uma opcao valida!" << endl;
    cin >> option;
  }

  return option;
}
//Função para escrever os resultados obtidos no modulo de testes pelo algoritmo de ordenação
void Testing::WriteOutFile(vector<CovidInfo> &data, int out)
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

//Função principal que executa o ciclo de funcionamento do programa
void Testing::Execute(string filename)
{
  //Para utilizar os algoritmos de ordenação
  clock_t processing_time = clock();

  int phase = SelectPhase();
  while (phase != 0)
  {
    if (phase == 1)
      this->PreProcessing(filename, processing_time);

    //Modulo de Escolha do algoritmo para ordernar os dados e seleção dos registros aleatórios
    else if (phase == 2)
    {
      //Seleção dos registros aleatórios
      vector<CovidInfo> processedCovidInfo = this->selectRandomCases();

      //Execução do algoritmo de ordenação sobre os registros aleatórios
      this->ExecuteSorting(SelectSortMethod(), &processedCovidInfo);

      //Escolha e escrita dependendo da saída escolhida pelo usuáriso (console ou txt)
      int saida = this->SelectOut();
      this->WriteOutFile(processedCovidInfo, saida);
    }
    //Modulo para geração das estatisticas
    else
    {
      int m;
      cout << "Digite o valor de M para o calculo das estatisticas" << endl;
      cin >> m;
      while (m < 5)
      {
        cout << "Valor de M invalido digite novamente!" << endl;
        cin >> m;
      }
      this->StatisticalAnalysis(m);
    }
    phase = SelectPhase();
  }
}

//Função que irá printar os resultados das estatisticas da analise
void Testing::PrintStatistic(int M, int N[], float time[], int swaps[], int comparisons[], int algorithm, ofstream &statisticsResults)
{
  //As variaveis que irão armazenar as médias são inicializadas com 0
  float timeAvg[5] = {0, 0, 0, 0, 0};
  float swapsAvg[5] = {0, 0, 0, 0, 0};
  float comparisonsAvg[5] = {0, 0, 0, 0, 0};

  //É feito uma string de vetor select para demonstrar qual algoritmo foi calculado
  string select[3] = {"MergeSort", "ShellSort", "QuickSort"};

  //Um loop é iniciado para os 5 valores diferentes de N[i], 10000, 50000, 100000, 500000, 1000000
  for (int j = 0; j < 5; j++)
  {
    //São calculados as estatisticas médias de cada N[i] diferente para cada algoritmo
    timeAvg[j] = time[j] / M;
    comparisonsAvg[j] = comparisons[j] / M;
    swapsAvg[j] = swaps[j] / M;

    //As informações são imprimidas em um arquivo .txt
    statisticsResults << "Os resultados do algoritmo " << select[algorithm] << " para um vetor randomico de tamanho " << N[j] << " foram " << endl;
    statisticsResults << "Media de tempo dos " << M << " conjuntos: " << timeAvg[j] << endl;
    statisticsResults << "Media de comparacoes dos " << M << " conjuntos: " << comparisonsAvg[j] << endl;
    statisticsResults << "Media de trocas dos " << M << " conjuntos: " << swapsAvg[j] << endl
                      << endl;
  }
  statisticsResults << "-------------------------------------------------------------------------------" << endl;
}

//Algoritmo que ira realizar a analise estatistica
void Testing::StatisticalAnalysis(int M)
{
  //são inicializados as variáveis para o tempo
  clock_t startTime = 0, finalTime;

  //é inicializado o vetor N que têm os tamanhos especificados no trabalho para os testes
  int N[5] = {10000, 50000, 100000, 500000, 1000000};

  //vetores que armazenarão os tempos para cada N diferente para cada algoritmo diferente
  float mergeTime[5] = {0, 0, 0, 0, 0};
  float quickTime[5] = {0, 0, 0, 0, 0};
  float shellTime[5] = {0, 0, 0, 0, 0};

  //vetores que armazenarão o número de comparações e trocas de cada iteração para os três diferentes algotimos
  int comparisons[5] = {0, 0, 0, 0, 0};
  int swaps[5] = {0, 0, 0, 0, 0};

  //contadores que irão armazenar o somátorio do número de comparações para os M conjuntos diferentes de cada algoritmo
  int counterComparisonsQuick[5] = {0, 0, 0, 0, 0};
  int counterComparisonsShell[5] = {0, 0, 0, 0, 0};
  int counterComparisonsMerge[5] = {0, 0, 0, 0, 0};

  //contadores que irão armazenar o somátorio do número de trocas para os M conjuntos diferentes de cada algoritmo
  int counterSwapsShell[5] = {0, 0, 0, 0, 0};
  int counterSwapsMerge[5] = {0, 0, 0, 0, 0};
  int counterSwapsQuick[5] = {0, 0, 0, 0, 0};

  Sorting *Sort = new Sorting();
  FileHandler *File = new FileHandler();

  //loop para os 5 diferentes valores possíveis de N
  for (int i = 0; i < 5; i++)
  {
    cout << "------------------------------------" << endl;
    cout << "Iteracoes de " << N[i] << endl;
    //loop para os M conjuntos de vetores diferentes
    for (int j = 0; j < M; j++)
    {
      //É criado um vetor notSorted com registros aleatórios com tamanho N
      vector<CovidInfo> notSorted = File->getNCovidInfos(N[i]);
      //É criado também um vetor toSort que irá receber notSorted para manter desorganizado
      vector<CovidInfo> toSort = notSorted;

      //é zerado as comparações e swaps para permitir que esses vetores funcionem para os três algoritmos
      comparisons[i] = 0;
      swaps[i] = 0;
      startTime = clock();
      Sort->mergeSortCases(toSort, 0, N[i] - 1, comparisons[i], swaps[i]);
      finalTime = clock();
      float totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
      counterSwapsMerge[i] += swaps[i];
      counterComparisonsMerge[i] += comparisons[i];
      mergeTime[i] += totalTime;
      //são feitos todos e incrementos após chamar a função de ordenação e então limpa o vetor toSort
      toSort.clear();
      toSort.shrink_to_fit();

      //é feito a mesma coisa dos dois comentários anteriores para os dois algoritmos seguintes
      toSort = notSorted;
      comparisons[i] = 0;
      swaps[i] = 0;
      startTime = clock();
      Sort->shellSortCases(toSort, N[i] - 1, comparisons[i], swaps[i]);
      finalTime = clock();
      totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
      counterSwapsShell[i] += swaps[i];
      counterComparisonsShell[i] += comparisons[i];
      shellTime[i] += totalTime;
      toSort.clear();
      toSort.shrink_to_fit();

      toSort = notSorted;
      comparisons[i] = 0;
      swaps[i] = 0;
      startTime = clock();
      Sort->quicksortCases(toSort, 0, N[i] - 1, comparisons[i], swaps[i]);
      finalTime = clock();
      totalTime = (finalTime - startTime) / (float)CLOCKS_PER_SEC;
      counterSwapsQuick[i] += swaps[i];
      counterComparisonsQuick[i] += comparisons[i];
      quickTime[i] += totalTime;
      toSort.clear();
      toSort.shrink_to_fit();

      //o vetor notSorted é limpado
      notSorted.clear();
      notSorted.shrink_to_fit();

      cout << j + 1 << "º "
           << "M "
           << "de " << N[i] << " feito..." << endl;
    }
    cout << "------------------------------------" << endl;
  }
  //ofstream para o arquivo de saída em .txt e os prints que sairão em satisticsResults.txt
  ofstream statisticsResults("statisticsResults.txt");
  PrintStatistic(M, N, mergeTime, counterSwapsMerge, counterComparisonsMerge, 0, statisticsResults);
  PrintStatistic(M, N, shellTime, counterSwapsShell, counterComparisonsShell, 1, statisticsResults);
  PrintStatistic(M, N, quickTime, counterSwapsQuick, counterComparisonsQuick, 2, statisticsResults);
  cout << "Arquivo de Texto statisticsResults.txt Gerado com sucesso!" << endl;
}