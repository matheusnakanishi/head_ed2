#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int prioridade;
    int tempoEspera;
}  Processo;


int pai(int i) {
    return (i/2);
}

int esq(int i) {
    return (i*2);
}

int dir(int i) {
    return (i*2+1);
}

void subirMax(Processo *heap, int i) {
    int p = pai(i);

    if (p >= 1) {
        if (heap[i].prioridade > heap[p].prioridade) {
            Processo aux = heap[i];
            heap[i] = heap[p];
            heap[p] = aux;
            subirMax(heap, p);
        }
    }
}

void descerMax(Processo *heap, int i, int tamanhoAtual) {
    int e = esq(i);
    int d = dir(i);
    int maior = i;

    if (e <= tamanhoAtual && heap[e].prioridade > heap[maior].prioridade)
        maior = e;
    
    if (d <= tamanhoAtual && heap[d].prioridade > heap[maior].prioridade)
        maior = d;

    if (maior != i) {
        Processo aux = heap[i];
        heap[i] = heap[maior];
        heap[maior] = aux;
        descerMax(heap, maior, tamanhoAtual);
    }
}

Processo *inserirProcessoMax(Processo *heap, int* tamanhoAtual, Processo novoProcesso) {
    heap = (Processo*)realloc(heap, sizeof(Processo) * (*tamanhoAtual + 2));
    (*tamanhoAtual)++;

    heap[*tamanhoAtual] = novoProcesso;

    subirMax(heap, *tamanhoAtual);

    return heap;
}



void imprimirProcessos(Processo *heap, int tamanho) {
    for (int i = 1; i <= tamanho; i++) 
        printf("[%d] ", heap[i].pid);

    printf("\n");
}


int main() {
    Processo *heapMax = NULL;
    //int *heapMin = NULL;
    int tamanhoAtual = 0;

    Processo novo;
    novo.pid = 111;
    novo.prioridade = 95;
    heapMax = inserirProcessoMax(heapMax, &tamanhoAtual, novo);

    novo.pid = 222;
    novo.prioridade = 60;
    heapMax = inserirProcessoMax(heapMax, &tamanhoAtual, novo);

    novo.pid = 333;
    novo.prioridade = 78;
    heapMax = inserirProcessoMax(heapMax, &tamanhoAtual, novo);

    novo.pid = 444;
    novo.prioridade = 39;
    heapMax = inserirProcessoMax(heapMax, &tamanhoAtual, novo);

    novo.pid = 555;
    novo.prioridade = 28;
    heapMax = inserirProcessoMax(heapMax, &tamanhoAtual, novo);

    novo.pid = 777;
    novo.prioridade = 66;
    heapMax = inserirProcessoMax(heapMax, &tamanhoAtual, novo);

    novo.pid = 888;
    novo.prioridade = 70;
    heapMax = inserirProcessoMax(heapMax, &tamanhoAtual, novo);

    novo.pid = 999;
    novo.prioridade = 33;
    heapMax = inserirProcessoMax(heapMax, &tamanhoAtual, novo);

    imprimirProcessos(heapMax, tamanhoAtual);

    return 0;
}
