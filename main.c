#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int prioridade;
    int tempoEspera;
} *Processo, Heap;


int pai(int i) {
    return (i/2);
}

int esq(int i) {
    return (i*2);
}

int dir(int i) {
    return (i*2+1);
}

Heap criarProcesso(int *id, int prioridade, int tempoEspera) {
    Heap novo;

    novo.pid = *id;
    novo.prioridade = prioridade;
    novo.tempoEspera = tempoEspera;
    (*id)++;

    return novo;
}

void subirMax(Processo heap, int i) {
    int p = pai(i);

    if (p >= 1) {
        if (heap[i].prioridade > heap[p].prioridade) {
            Heap aux = heap[i];
            heap[i] = heap[p];
            heap[p] = aux;
            subirMax(heap, p);
        }
    }
}

void subirMin(Processo heap, int i) {
    int p = pai(i);

    if (p >= 1) {
        if (heap[i].prioridade < heap[p].prioridade) {
            Heap aux = heap[i];
            heap[i] = heap[p];
            heap[p] = aux;
            subirMax(heap, p);
        }
    }
}

void descerMax(Processo heap, int i, int tamanhoAtual) {
    int e = esq(i);
    int d = dir(i);
    int maior = i;

    if (e <= tamanhoAtual && heap[e].prioridade > heap[maior].prioridade)
        maior = e;
    
    if (d <= tamanhoAtual && heap[d].prioridade > heap[maior].prioridade)
        maior = d;

    if (maior != i) {
        Heap aux = heap[i];
        heap[i] = heap[maior];
        heap[maior] = aux;
        descerMax(heap, maior, tamanhoAtual);
    }
}

void descerMin(Processo heap, int i, int tamanhoAtual) {
    int e = esq(i);
    int d = dir(i);
    int menor = i;

    if (e <= tamanhoAtual && heap[e].prioridade < heap[menor].prioridade)
        menor = e;
    
    if (d <= tamanhoAtual && heap[d].prioridade < heap[menor].prioridade)
        menor = d;

    if (menor != i) {
        Heap aux = heap[i];
        heap[i] = heap[menor];
        heap[menor] = aux;
        descerMax(heap, menor, tamanhoAtual);
    }
}

void inserirProcesso(Processo *heap, int* tamanhoAtual, Processo novoProcesso, int tipoHeap) {
    *heap = (Processo)realloc(*heap, sizeof(Heap) * (*tamanhoAtual + 2));
    (*tamanhoAtual)++;

    heap[*tamanhoAtual] = novoProcesso;

    if (tipoHeap == 0)
        subirMax(*heap, *tamanhoAtual);
    else
        subirMin(*heap, *tamanhoAtual);

    return heap;
}

void removeProcessoTopo(Processo *heap, int* tamanhoAtual, int tipoHeap) {
    if (heapVazio(tamanhoAtual) == 1)
        printf("\nHeap Vazio\n");
    else {
        heap[1] = heap[*tamanhoAtual];
        (*tamanhoAtual)--;
        *heap = (Processo)realloc(*heap, sizeof(Heap) * (*tamanhoAtual + 1));

        if (tipoHeap == 0)    
            descerMax(*heap, 1, *tamanhoAtual);
        else
            descerMin(*heap, 1, *tamanhoAtual);
    }
}

int heapVazio(int tamanhoAtual) {
    return (tamanhoAtual <= 0)? 1 : 0;
}

void imprimirProcessos(Processo *heapMax, Processo *heapMin, int tamanho, int fator) {
    if (fator == 0) {
        printf("Prioridade\n");
        printf("Heap Maximo: ");
        for (int i = 0; i <= tamanho; i++) {
            printf("[%d] ", (*heapMax)[i].prioridade);
        }
        printf("\nHeap Minimo: ");
        for (int i = 0; i <= tamanho; i++) {
            printf("[%d] ", (*heapMin)[i].prioridade);
        }
    }
    else {
        printf("Tempo de Espera\n");
        printf("Heap Maximo: ");
        for (int i = 0; i <= tamanho; i++) {
            printf("[%d] ", (*heapMax)[i].tempoEspera);
        }
        printf("\nHeap Minimo: ");
        for (int i = 0; i <= tamanho; i++) {
            printf("[%d] ", (*heapMin)[i].tempoEspera);
        }
    }
}

void constroiHeapMax(Processo *heapMax, int tamanho) {
    int i;
    int j = (tamanho/2);

    for (i = j; i >= 1; i--)
        descerMax(*heapMax, i, tamanho);
}

void constroiHeapMin(Processo *heapMin, int tamanho) {
    int i;
    int j = (tamanho/2);

    for (i = j; i >= 1; i--)
        descerMin(*heapMin, i, tamanho);
}

int main() {
    Heap novo;
    Processo heapMax = (Processo)malloc(sizeof(Heap));
    Processo heapMin = (Processo)malloc(sizeof(Heap));
    int tamanhoMax = 0, tamanhoMin = 0, id = 1;

    
    
    

    return 0;
}
