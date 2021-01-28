#include "./Testing.h"
#include "../FileHandler/FileHandler.h"
#include "../Sorting/Sorting.h"
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

void Testing::selectRandomCases()
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
  cout << "Digite [2] para QuickSort;" << endl;
  cout << "Digite [3] para ShellSort;" << endl;

  cout << "-------------------------------------------------------------------------------" << endl;

  cin >> algoritmoSelecionado;

  while (algoritmoSelecionado != 1 && algoritmoSelecionado != 2 && algoritmoSelecionado != 3)
  {
    cout << "Digite um numero valido!" << endl;
    cin >> algoritmoSelecionado;
  }

  return algoritmoSelecionado;
}

void Testing::preProcessing(string filename, clock_t &processingTime)
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
  clock_t tempo_inicio = clock();
  //Abre o arquivo de texto , desmembra o mesmo , e salva em um vector de CovidInfo
  vector<CovidInfo> processedFile = FileReader->csvHandler(filename != "" ? filename : "brazil_covid19_cities.csv");
  cout << "Arquivo Desmenbrado com Sucesso" << endl;
  //Ordenação do vetor por (Estado,Cidade) e data.
  sorting.mergeSort(processedFile, 0, processedFile.size());
  //Geração do novo arquivo csv com os dados processados
  statistics.dailyCasesTotalizers(processedFile);
  cout << "Arquivo pre-processado com sucesso!" << endl;
  clock_t tempo_termino = clock();
  processingTime = (tempo_termino - tempo_inicio) / ((float)CLOCKS_PER_SEC);
  
}

void Testing::execute(string filename)
{
  clock_t tempo_processamento = clock();

  preProcessing(filename , tempo_processamento);
  cout << "Tempo total de execução do processamento: " << tempo_processamento << " segundos" << endl;
  /*this->selectRandomCases();
  int outType = this->SelecionarSaida();
  int selectedOrdering = this->SelecionarAlgoritmo();*/
}

void Testing::statisticalAnalysis(int M)
{
  int N[5] = {10000, 50000, 100000, 500000, 1000000};

  float timeMerge[5] = {0, 0, 0, 0, 0};
  float timeQuick[5] = {0, 0, 0, 0, 0};
  float timeShell[5] = {0, 0, 0, 0, 0};

  int comparisonsMerge[5] = {0, 0, 0, 0, 0};
  int comparisonsQuick[5] = {0, 0, 0, 0, 0};
  int comparisonsShell[5] = {0, 0, 0, 0, 0};

  int swapMerge[5] = {0, 0, 0, 0, 0};
  int swapQuick[5] = {0, 0, 0, 0, 0};
  int swapShell[5] = {0, 0, 0, 0, 0};

  float timeAvgMerge[5] = {0, 0, 0, 0, 0};
  float timeAvgQuick[5] = {0, 0, 0, 0, 0};
  float timeAvgShell[5] = {0, 0, 0, 0, 0};

  int comparisonsAvgMerge[5] = {0, 0, 0, 0, 0};
  int comparisonsAvgQuick[5] = {0, 0, 0, 0, 0};
  int comparisonsAvgShell[5] = {0, 0, 0, 0, 0};

  int swapAvgMerge[5] = {0, 0, 0, 0, 0};
  int swapAvgQuick[5] = {0, 0, 0, 0, 0};
  int swapAvgShell[5] = {0, 0, 0, 0, 0};

  Sorting *Sort = new Sorting();
  FileHandler *File = new FileHandler();
  clock_t timeStart = 0, timeEnd;
  int *comparisons = 0;
  int *swaps = 0;
  cout << "ola";
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < M; j++)
    {
      vector<CovidInfo> notSorted = File->getNCovidInfos(N[i]);
      vector<CovidInfo> toSort = notSorted;
      
      timeStart = 0;
      timeEnd = 0;
      /*
      timeStart;
      mergeSort(vetor randomico, size);
      timeEnd;
      swapMerge[i] = swapMerge[j] + Pegar numero de swaps;
      comparisonsMerge[i] = swapMerge[i] + Pegar numero de comparisons;
      timeMerge[i] = timeMerge[i] + Pegar o time;
      */

      timeStart = clock();
      //Sort->shellSortCases(toSort, N[i], comparisons, swaps);
      timeEnd = clock();
      float time = (timeEnd - timeStart) / (float)CLOCKS_PER_SEC;
      swapShell[i] = swapShell[i] + 77;
      comparisonsShell[i] = swapShell[i] + 55;
      //timeShell[i] = timeShell[i] + time;
      
      /*
      timeStart = 0;
      timeStart;
      quickSort(vetor randomico, size);
      timeEnd;
      swapQuick[i] = swapQuick[i] + Pegar numero de swaps;
      comparisonsQuick[j] = swapQuick[i] + Pegar numero de comparisons;
      timeQuick[i] = timeQuick[i] + Pegar o time;*/
    }
  }
  
  for (int j = 0; j < 5; j++)
  {
    //timeAvgMerge[j] = timeMerge[j] / 5;
    //timeAvgQuick[j] = timeQuick[j] / 5;
    timeAvgShell[j] = timeShell[j] / 5;

    //comparisonsAvgMerge[j] = comparisonsMerge[j] / 5;
    //comparisonsAvgQuick[j] = comparisonsQuick[j] / 5;
    comparisonsAvgShell[j] = comparisonsShell[j] / 5;

    //swapAvgMerge[j] = swapMerge[j] / 5;
    //swapAvgQuick[j] = swapQuick[j] / 5;
    swapAvgShell[j] = swapShell[j] / 5;

    cout << timeAvgShell[j] << " " << comparisonsAvgShell[j] << " " << swapAvgShell[j] << endl;
  }
  
  //CriarArquivoSaida(Resultados); 
}
