#include <iostream>

using namespace std;


void merge(int vet[], int p, int q, int r)
{
    int aux[8];
    int i = p;
    int j = q;
    int k = 0;

    while(i < q && j < r)
    {
        if (vet[i] < vet[j])
        {
            aux[k] = vet[i];
            i++;
        }
        else
        {
            aux[k] = vet[j];
            j++;
        }
        k++;
    }

    while(i < q)
    {
        aux[k] = vet[i];
        i++;
        k++;
    }

    while(j < r)
    {
        aux[k] = vet[j];
        j++;
        k++;
    }

    for(i = p; i < r; i++)
    {
        vet[i] = aux[i - p];
    }
}

///Funcao recursiva
void mergeSort(int vet[], int p, int r)
{
    if(p < r - 1)
    {
        int q = (p + r) / 2;
        mergeSort(vet, p, q); ///chama de p a q
        mergeSort(vet, q, r);  ///chama de q a r
        merge(vet, p, q, r);
    }

}

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
}
