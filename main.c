#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Gera um Array de inteiros aleatórios
void geraArray(int vet[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        vet[i] = rand() % 1001; // Gera um número aleatório de 0 até 1000
    }
    printf("\nVetor de inteiros gerado!\n");
}
// Troca 
void troca(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

// Selection Sort Recursivo
void selectionSort(int vet[], int n, int i) {
    if (i == n - 1) 
        return; // Caso base: quando i chega ao final do array
    
    int aux = i;
    for (int j = i + 1; j < n; j++) {
        if (vet[j] > vet[aux]) {
            aux = j;
        }
    }

    if (aux != i) 
        troca(&vet[i], &vet[aux]);
    
    // Chama recursivamente para o próximo elemento
    selectionSort(vet, n, i + 1);
}

// Insertion Sort Recursivo
void insertionSort(int vet[], int n, int i) {
    if (i <= 0) 
        return; // Caso base: quando i chega a 0 ou menos, o array está ordenado
    
    int chave = vet[i];
    int j = i - 1;

    while (j >= 0 && vet[j] < chave) {
        vet[j + 1] = vet[j];
        j--;
    }

    vet[j + 1] = chave;

    // Chama recursivamente para o próximo elemento
    insertionSort(vet, n, i - 1);
}

// intercala - Merge Sort
void intercala(int vet[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // L e R é alocado dinamicamente no heap usando a função malloc.
    int *L = (int *)malloc(sizeof(int) * n1);
    int *R = (int *)malloc(sizeof(int) * n2);

    for (int i = 0; i < n1; i++) 
        L[i] = vet[inicio + i];

    for (int j = 0; j < n2; j++) 
        R[j] = vet[meio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            vet[k] = L[i];
            i++;
        } else {
            vet[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vet[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vet[k] = R[j];
        j++;
        k++;
    }

    // Libera a memória alocada
    free(L);
    free(R);
}

// Merge Sort
void mergeSort(int vet[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio + 1, fim);
        intercala(vet, inicio, meio, fim);
    }
}

// Separa - Quick Sort
int separa(int vet[], int inicio, int fim) {
    int x = vet[inicio];
    int i = inicio - 1;
    int j = fim + 1;

    while (1) {
        do {
            j--;
        } while (vet[j] < x);

        do {
            i++;
        } while (vet[i] > x);

        if (i >= j)
            return j;

        troca(&vet[i], &vet[j]);
    }
}

// Quick Sort
void quickSort(int vet[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = separa(vet, inicio, fim);
        quickSort(vet, inicio, pivo);
        quickSort(vet, pivo + 1, fim);
    }
}

void imprimeArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void encerra();

int main(void) {
    int n, opcao, imprime;
    clock_t start, end;
    double tempoDeProcessamento;

    do {
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &n);

        if(n <= 0) {
            printf("Tamanho invalido! Digite um valor maior que 0.\n");
            continue;
        }

        int *arr = (int *)malloc(sizeof(int) * n); //arr é alocado dinamicamente no heap usando a função malloc.
        geraArray(arr, n);

        if(arr == NULL) {
    	    printf("Erro na alocacao da memoria");
    	    return 1;
        }

        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("|               ESCOLHA UM ALGORITMO DE ORDENACAO:                |\n");
        printf("|                       1. Selection Sort                         |\n");
        printf("|                       2. Insertion Sort                         |\n");
        printf("|                       3. Merge Sort                             |\n");
        printf("|                       4. Quick Sort                             |\n");
        printf("|                       0. SAIR                                   |\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            start = clock();
            selectionSort(arr, n, 0);
            end = clock();
            break;

        case 2:
            start = clock();
            insertionSort(arr, n, n - 1);
            end = clock();
            break;

        case 3:
            start = clock();
            mergeSort(arr, 0, n - 1);
            end = clock();
            break;

        case 4:
            start = clock();
            quickSort(arr, 0, n - 1);
            end = clock();
            break;

        case 0:
            printf("                  ----- PROGRAMA ENCERRADO -----\n\n");
            free(arr);
            encerra();
            return 0;
            
        default:
            printf("----- OPCAO INVALIDA! -----\nTente novamente.\n\n");
            free(arr);
            continue;
        }

        tempoDeProcessamento = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\nTempo de processamento: %lf segundo.\n\n", tempoDeProcessamento);

        
        printf("Deseja imprimir o vetor ordenado na ordem decrescente? (1 - SIM | 0 - NAO)\n");
        scanf("%d", &imprime);

        if (imprime) {
            printf("Vetor ordenado: ");
            imprimeArray(arr, n);
        }else{
            printf("Vetor nao impresso!\n");
        }

        free(arr); // Libera a memória alocada no heap

    } while (opcao != 0);

    return 0;
}

void encerra() {
    printf("                                                                  ..  .,.\n");
    printf("                                                              .ed$$$$???$$e\n");
    printf("                                                           .e$$$P\",zebbc`9$\n");
    printf("                                                         z$$$P\"ud$$$$$$P.dF\n");
    printf("                                                       e$$$\" z$$$$$$$P\"d$\n");
    printf("                                                    .e$$P\".d$$$$$$$P\"z$\"\n");
    printf("                                      zdd$$bbe=-  zd$P\"ud$$$$$$$$P\"z$\"\n");
    printf("                  .,uuu,.           z$$$$$$$$$$$bc:\"4d$$$$$$$P\",zdP\"\n");
    printf("            ,=.c$$$$$$$$$$bc.      J$$$$$$$$$$$$$P\"  3$$$P\".eP\"\"\n");
    printf("        .zd$,d$$$$$$$$$$$$$$$c.    \"$$$$$PPFF\"\":.zd$$b\"\".+=\"\n");
    printf("      .d$$$$$$$$$$$$$$$$$$?$$$$c    $$$Fu rx$\"d$PF\"  ``\n");
    printf("     d$$$$$$$$$$$$$$$\"   =q,`\"?$  $$$$F9 $\"/\"\n");
    printf("   .$$$$$$$$$$$$$$P\"        \"?$c`?c `$$$ EJE.\n");
    printf("  u$$$$$$$$$$$$$\"             `\"$c`?e`$$' ??\"\n");
    printf(" d$$$$$$$$$$$$$\"                  \"?`\"zed$E9\"`\\.\n");
    printf("d$$$$$$$$$$$$P\"                       $ ud$$d\"?c\n");
    printf("$$$$$$$$$$$F                         `$J$',,`?$b`.\n");
    printf("4$$$$?$$P\"                           `$$'<$$$e\"$$b.\n");
    printf("\"`          Mbc                      \"$.<$$$$$`$$$c      ,zc,.\n");
    printf("             `?MMc                     ?$ $$???$\"`\"\"..,cd$$$$$$C  _.- ~\n");
    printf("        ec,    \"MMb.         .eWe       $b`    `i   ,$$$$$$9$$$\"~   _ .\n");
    printf("        \"MMMb.  `?MM.       dMMP\"zbc,,..9$$. .,db  ,$$$$$L\"d$$F- ~\n");
    printf("          \"?MMbu  \"MMc     9MMP d$$$$$$$$$$6kuLdbP\"\"``\"$$F<$$\" = -- -\n");
    printf("             \"?MMe.P5Mbu.  9MM 9$$$$$$C\"\",$$$$$E:dx(xd`J$>)\"'\n");
    printf("               `?M\"zMMMMMMMMMM $$$$$$$$$$bc\"??$$ecu,,ud$$'\n");
    printf("       ,,umu,,.  \"dMMMMMMMMMMML`\"??$$$$$$$$$bc\"????????\"\n");
    printf("      ?MMMMMMMMMMkMMMMMMMMMMMME -~  / `\"\"\"\"\"\"`  bc-=\n");
    printf("             ``''\"?MMMMMMMMMcMF    '             \"$L   z;Cr\n");
    printf("                   `?MMMMMMM\",u   '       :(C;u   $F ,??;CF\n");
    printf("                       \"\"\",mP\"           `;?;CC= `r +;?;e;\"\n");
    printf("                          \"\",u             \"CCC:C><;?;/CcJb\n");
    printf("                            \"$k            .c'C>\">C'J?.'P JcL\n");
    printf("                             $$u         .d$E >\" dddk u,\",d$$c,\n");
    printf("                              $$$k    d$$$\"      d$$'$$$>?)'    \"?$$$b.\n");
}


