#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Função para exibir uma matriz
void exibirMatriz(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%5d", mat[i][j]);
        }
        printf("\n");
    }
}

// Função para gerar uma matriz aleatória
void gerarMatrizAleatoria(int **mat, int l, int c, int min, int max) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = rand() % (max - min + 1) + min;  // Gera números entre min e max
        }
    }
}

// Função recursiva para calcular produto escalar da matriz
int produtoescalar(int **mat1, int **mat2, int i, int j, int e, int j1 ) {
    if (e == j1) return 0;
    // multiplica l1 com c2 e soma os produtos com recusão
    return mat1[i][e] * mat2[e][j] + produtoescalar(mat1, mat2, i, j, e + 1, j1);
}

// Função recursiva para calcular toda a matriz resultante
void multiplicaMatrizes(int **mat1, int **mat2, int **resultado, int i, int j, int i1, int j1, int j2) {
    if (i >= i1) return;
    if (j >= j2) {
        // chama a própria função incrementando i (próxima linha)
        multiplicaMatrizes(mat1, mat2, resultado, i + 1, 0, i1, j1, j2);
        return;
    }
    // recebe os novos elementos
    resultado[i][j] = produtoescalar(mat1, mat2, i, j, 0, j1);
    // chama a própria função incrementando j (próxima coluna)
    multiplicaMatrizes(mat1, mat2, resultado, i, j + 1, i1, j1, j2);
}

int main() {
    int l1, c1, l2, c2, continuar = 1, i, j, escolha;
    int minValor = 1, maxValor = 20;  // Definindo intervalo dos valores aleatórios
    setlocale(LC_ALL, "");
    // Inicializa a função rand com um valor de semente baseado no tempo
    srand(time(NULL));

    // while para caso queira reiniciar
    while (continuar == 1) {
        // ler linha e coluna das matrizes
        printf("Digite o numero de linhas e colunas da primeira matriz: ");
        scanf("%d %d", &l1, &c1);
        printf("Digite o numero de linhas e colunas da segunda matriz: ");
        scanf("%d %d", &l2, &c2);

        // verificar se existe o produto das matrizes
        if (c1 != l2) {
            printf("\nNao e possivel calcular o produto das matrizes.\n");
        } else {
            // alocando memoria para o vetor de ponteiros (mat1) de tamanho l1 que apontam para inteiros
            int **mat1 = (int **)malloc(l1 * sizeof(int *));
            int **mat2 = (int **)malloc(l2 * sizeof(int *));
            int **resultado = (int **)malloc(l1 * sizeof(int *));

            // alocando a memória para os elementos das matrizes:
            for (i = 0; i < l1; i++) {
                mat1[i] = (int *)malloc(c1 * sizeof(int));
            }
            for (i = 0; i < l2; i++) {
                mat2[i] = (int *)malloc(c2 * sizeof(int));
            }
            for (i = 0; i < l1; i++) {
                resultado[i] = (int *)malloc(c2 * sizeof(int));
            }

            // Pergunta se o usuário quer gerar as matrizes aleatórias ou preenchê-las manualmente
            printf("\nDeseja preencher as matrizes manualmente ou gerar matrizes aleatorias?\n");
            printf("0 - Preencher manualmente\n");
            printf("1 - Gerar matrizes aleatorias\n");
            scanf("%d", &escolha);

            if (escolha == 0) {
                // Preenchendo a matriz 1 manualmente
                printf("\nDigite os numeros da primeira matriz:\n");
                for (i = 0; i < l1; i++) {
                    for (j = 0; j < c1; j++) {
                        printf("Elemento [%d][%d]: ", i+1, j+1);
                        scanf("%d", &mat1[i][j]);
                    }
                }

                // Exibe a matriz 1
                printf("\nMatriz 1 preenchida:\n");
                exibirMatriz(mat1, l1, c1);

                // Preenchendo a matriz 2 manualmente
                printf("\nDigite os numeros da segunda matriz:\n");
                for (i = 0; i < l2; i++) {
                    for (j = 0; j < c2; j++) {
                        printf("Elemento [%d][%d]: ", i+1, j+1);
                        scanf("%d", &mat2[i][j]);
                    }
                }

                // Exibe a matriz 2
                printf("\nMatriz 2 preenchida:\n");
                exibirMatriz(mat2, l2, c2);

            } else if (escolha == 1) {
                // Gerando as matrizes aleatórias
                gerarMatrizAleatoria(mat1, l1, c1, minValor, maxValor);
                gerarMatrizAleatoria(mat2, l2, c2, minValor, maxValor);

                // Exibe a matriz 1 gerada
                printf("\nMatriz 1 gerada aleatoriamente:\n");
                exibirMatriz(mat1, l1, c1);

                // Exibe a matriz 2 gerada
                printf("\nMatriz 2 gerada aleatoriamente:\n");
                exibirMatriz(mat2, l2, c2);
            } else {
                printf("\nOpcao invalida! Tente novamente.\n");
                continue;
            }

            // Chama a função para multiplicar as matrizes
            multiplicaMatrizes(mat1, mat2, resultado, 0, 0, l1, c1, c2);

            // Exibe a matriz resultado da multiplicação
            printf("\nMatriz resultado da multiplicacao:\n");
            for (i = 0; i < l1; i++) {
                for (j = 0; j < c2; j++) {
                    printf("%5d", resultado[i][j]);
                }
                printf("\n");
            }

            // Liberar memória alocada
            for (i = 0; i < l1; i++) free(mat1[i]);
            for (i = 0; i < l2; i++) free(mat2[i]);
            for (i = 0; i < l1; i++) free(resultado[i]);
            free(mat1);
            free(mat2);
            free(resultado);
        }

        printf("\nDeseja reiniciar? (sim=1 / nao=0): ");
        scanf("%d", &continuar);
        while (continuar != 1 && continuar != 0){
        printf("\nResposta Invalida !!!\n\nDeseja reiniciar? ( sim=1 / nao=0 ): ");
        scanf("%d", &continuar);}
        if (continuar == 1)
            system("cls");
    }

    return 0;
}
