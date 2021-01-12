#include "./Sorting.h"
#include "../CovidStatistics/CovidStatistics.h"
#include "../CovidInfo/CovidInfo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

Sorting::Sorting()
{
    cout << "Objeto sorting montado" << endl;
}

void Sorting::merge(vector<CovidInfo> &covidInfoList, int p, int q, int r)
{

    vector<CovidInfo> auxCovidInfoList;
    int i = p;
    int j = q;
    int k = q;

    while (i < q && j < r)
    {

        /*cout << "no i " << covidInfoList.at(i).city << endl;
        cout << "no j " << covidInfoList.at(j).city << endl;
        cout << "Comparando "  << covidInfoList.at(i).city.compare(covidInfoList.at(j).city) << endl;*/

        if ((covidInfoList.at(i).state.compare(covidInfoList.at(j).state) == -1))
        {
            auxCovidInfoList.push_back(covidInfoList.at(i));
            i++;
            
        }
        else if((covidInfoList.at(i).state.compare(covidInfoList.at(j).state) == 0))
        {
            if((covidInfoList.at(i).city.compare(covidInfoList.at(j).city) == -1))
            {
                auxCovidInfoList.push_back(covidInfoList.at(i));
                i++;
            }
            else
            {
                auxCovidInfoList.push_back(covidInfoList.at(j));
                j++;
            }
            
        }
        else
        {
            auxCovidInfoList.push_back(covidInfoList.at(j));
            j++;
        }
    }

    while (i < q)
    {
        auxCovidInfoList.push_back(covidInfoList.at(i));
        k++;
        i++;
    }

    while (j < r)
    {
        auxCovidInfoList.push_back((covidInfoList.at(j)));
        k++;
        j++;
    }

    for (i = p; i < r; i++)
    {
        covidInfoList.at(i) = auxCovidInfoList.at(i - p);
    }

}

///Funcao recursiva
void Sorting::mergeSort(vector<CovidInfo> &covidInfoList, int p, int r)
{
    
    if (p < r - 1)
    {
        int q = (p + r) / 2;
        mergeSort(covidInfoList, p, q); ///chama de p a q
        mergeSort(covidInfoList, q, r); ///chama de q a r
        merge(covidInfoList, p, q, r);
    }
        
}
void Sorting::shellSort(vector<CovidInfo> &covidInfoList){
     // Start with a big gap, then reduce the gap 
      for (int gap = 8/2; gap > 0; gap /= 2) 
        { 
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements a[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is 
        // gap sorted  
        for (int i = gap; i < 8; i += 1) 
        { 
            // add a[i] to the elements that have been gap sorted 
            // save a[i] in temp and make a hole at position i 
            CovidInfo aux = covidInfoList.at(i); 
  
            // shift earlier gap-sorted elements up until the correct  
            // location for a[i] is founde 
            int j;             
            for (j = i; j >= gap && covidInfoList.at(j-gap).city > aux.city; j -= gap) 
                covidInfoList.at(j) = covidInfoList.at(j-gap); 

            //  put temp (the original a[i]) in its correct location 
            covidInfoList.at(j) = aux; 
        } 
    } 
 
}
void Sorting::imprimir(vector<CovidInfo> covidInfoList, int r)
{
    int totalCasos = 0;

    cout << endl;

     for (int i = 0; i < r; i++)
    {
        cout << covidInfoList.at(i).date << "," << covidInfoList.at(i).state << "," << covidInfoList.at(i).city << "," << 
        covidInfoList.at(i).code << "," << covidInfoList.at(i).cases << "," << covidInfoList.at(i).deaths << endl;
        
        totalCasos += covidInfoList.at(i).cases;

    }

    cout << endl;

    cout << " O numero total de casos diarios eh de: " << totalCasos << endl;

}

//Teste feito na main()

/*
int main()
{
    int tam = 8;
    int vet[tam] = {39, 5, 12, 1, 34, 64, 7, 76};

    mergeSort(vet, 0, tam);

    cout<<"Vetor ordenado: "<<endl;
    for(int i = 0; i < tam; i++)
    {
        cout<<" "<<vet[i];
    }

    cout<<endl;

    return 0;
}*/
