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
        if (heap[i].tempoEspera < heap[p].tempoEspera) {
            Heap aux = heap[i];
            heap[i] = heap[p];
            heap[p] = aux;
            subirMin(heap, p);
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

    if (e <= tamanhoAtual && heap[e].tempoEspera < heap[menor].tempoEspera)
        menor = e;
    
    if (d <= tamanhoAtual && heap[d].tempoEspera < heap[menor].tempoEspera)
        menor = d;

    if (menor != i) {
        Heap aux = heap[i];
        heap[i] = heap[menor];
        heap[menor] = aux;
        descerMin(heap, menor, tamanhoAtual);
    }
}

void inserirProcesso(Processo *heap, int* tamanhoAtual, Heap novoProcesso, int tipoHeap) {
    *heap = (Processo)realloc(*heap, sizeof(Heap) * (*tamanhoAtual + 2));
    (*tamanhoAtual)++;

    (*heap)[*tamanhoAtual] = novoProcesso;

    if (tipoHeap == 0)
        subirMax(*heap, *tamanhoAtual);
    else
        subirMin(*heap, *tamanhoAtual);
}

void inserirN(Processo *heapMax, Processo *heapMin, int *tamanhoMax, int *tamanhoMin, int *id) {
    int n, prioridade, tempo;

    printf("\nQuantidade de Processos a inserir: ");
    scanf("%d",&n);

    for (int i = 0; i < n; i++) {
        printf("\nProcesso %d\n", i);
        printf("Prioridade: ");
        scanf("%d",&prioridade);
        printf("Tempo de Espera: ");
        scanf("%d",&tempo);

        Heap novo;
        novo.pid = *id;
        novo.prioridade = prioridade;
        novo.tempoEspera = tempo;

        inserirProcesso(heapMax, tamanhoMax, novo, 0);
        inserirProcesso(heapMin, tamanhoMin, novo, 1);

        (*id)++;
    }
    
}

int heapVazio(int tamanhoAtual) {
    return (tamanhoAtual <= 0)? 1 : 0;
}

void removeProcessoTopo(Processo *heap, int* tamanhoAtual, int tipoHeap) {
    if (heapVazio(*tamanhoAtual) == 1)
        printf("\nHeap Vazio\n");
    else {
        (*heap)[1] = (*heap)[*tamanhoAtual];
        (*tamanhoAtual)--;
        *heap = (Processo)realloc(*heap, sizeof(Heap) * (*tamanhoAtual + 1));

        if (tipoHeap == 0)    
            descerMax(*heap, 1, *tamanhoAtual);
        else
            descerMin(*heap, 1, *tamanhoAtual);
    }
}



void imprimirProcessos(Processo heapMax, Processo heapMin, int tamanho, int fator) {
    if (heapVazio(tamanho) == 1) {
        printf("\nHeap Vazio\n");
        return;
    }
    
    if (fator == 0) {
        printf("Prioridade\n");
        printf("Heap Maximo: ");
        for (int i = 1; i <= tamanho; i++) {
            printf("[%d] ", heapMax[i].prioridade);
        }
        printf("\nHeap Minimo: ");
        for (int i = 1; i <= tamanho; i++) {
            printf("[%d] ", heapMin[i].prioridade);
        }
    }
    else {
        printf("\nTempo de Espera\n");
        printf("Heap Maximo: ");
        for (int i = 1; i <= tamanho; i++) {
            printf("[%d] ", heapMax[i].tempoEspera);
        }
        printf("\nHeap Minimo: ");
        for (int i = 1; i <= tamanho; i++) {
            printf("[%d] ", heapMin[i].tempoEspera);
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
    int tamanhoMax = 0, tamanhoMin = 0, id = 1, op;

    do {
        printf("\n[1]Inserir Processo unico\n[2]Inserir varios Processos\n[3]Remover Processo\n[4]Mostrar Processos\n[0]Sair\nOpcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\nProcesso %d\n", id);
            printf("Prioridade: ");
            scanf("%d",&novo.prioridade);
            printf("Tempo de Espera: ");
            scanf("%d",&novo.tempoEspera);
            inserirProcesso(&heapMax, &tamanhoMax, novo, 0);
            inserirProcesso(&heapMin, &tamanhoMin, novo, 1);

            break;
        
        case 2:
            inserirN(&heapMax, &heapMin, &tamanhoMax, &tamanhoMin, &id);
            break;

        case 3:
            removeProcessoTopo(&heapMax, &tamanhoMax, 0);
            removeProcessoTopo(&heapMin, &tamanhoMin, 1);
            break;

        case 4: 
            imprimirProcessos(heapMax, heapMin, tamanhoMax, 0);
            imprimirProcessos(heapMax, heapMin, tamanhoMin, 1);
            break;
        
        default:
            break;
        }


    } while (op != 0);
    
    return 0;
}
