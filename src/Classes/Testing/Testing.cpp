#include "./Testing.h"

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

  while (algoritmoSelecionado != 1 && algoritmoSelecionado != 2  && algoritmoSelecionado != 3)
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
  switch (choice)
  {
  case 1:
    sorting.mergeSortCases(*covidInfoSet, 0, covidInfoSet->size());
    break;
  case 2:
    sorting.shellSortCases(*covidInfoSet, covidInfoSet->size());
    break;
  case 3:
    sorting.quickSort(*covidInfoSet,0,covidInfoSet->size() , 'c');
    break;
  default:
    break;
  }
}

int Testing::selectFirstPhase(){
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
  clock_t tempo_processamento = clock();
  int firstPhase = selectFirstPhase();
  if(firstPhase == 1)
  preProcessing(filename , tempo_processamento);
  vector<CovidInfo> processedCovidInfo = this->selectRandomCases();
  this->executeSorting(this->SelecionarAlgoritmo(), &processedCovidInfo);
  int saida = this->SelecionarSaida();
  writeOutFile(processedCovidInfo,saida);

 
}