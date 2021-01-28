#include "./Testing.h"

using namespace std;

Testing::Testing(){

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

void Testing::selectRandomCases(){
    int n;

    //@todo mudar para casos fixos 10.000,50.000,100.000,500.000,1.000.000
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "Selecione o número de instâncias para teste" << endl;
    cout << "Obs: (deve ser um número entre 1 e 1000000)" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cin >> n;
    while(n <= 1 || n >= 100000){
      cout << "Opção invalida" << endl;
      cin >>n;
    } 
    FileHandler fileHandler;
    vector<CovidInfo> covidArray =  fileHandler.getNCovidInfos(n);

    int i =0;
    for(CovidInfo a : covidArray){
      i++;
      if(i >20)
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

vector<CovidInfo> Testing::preProcessing(string filename, clock_t &processingTime)
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

void Testing::execute(string filename){
    clock_t tempo_processamento = clock();
    
    vector<CovidInfo>  processedCsv = preProcessing(filename , tempo_processamento);    
    cout << "Tempo total de execução do processamento: " << tempo_processamento << " segundos" << endl;
    this->selectRandomCases();
    int outType = this->SelecionarSaida();
    int selectedOrdering = this->SelecionarAlgoritmo();

}