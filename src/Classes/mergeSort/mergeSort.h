#include <iostream>

using namespace std;

class mergeSort 
{
    public:
        mergeSort();
        void merge(int vet[], int p, int q, int r);
        void mergeSort(int vet[], int p, int r);

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