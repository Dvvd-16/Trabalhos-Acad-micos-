//LISTA DE CADASTRO DE CLIENTES OFICINA MECANICA AUTOMOTIVA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h> //fornecer funções de entrada e saída de console

//Struct geral
typedef struct Elemento_LISTA {
    char nome[100];
    char datadeCadastro[11];
    char telefone[15];
    char email[100];
    char carro[30];
    char cor_carro[20];
    char placa_carro[7];
    char servico[1000];


    struct Elemento_LISTA* proximo;
    struct Elemento_LISTA* anterior; //ponteiros que apontam para a própria struct
} Elemento_LISTA;

typedef struct Lista {
    Elemento_LISTA* inicio;
    Elemento_LISTA* fim; //ponteiros que apontam para o inicio e fim da lista
} Lista;

// Função para inicializar a lista
Lista* criarLista() {
    Lista* novalista = (Lista*)malloc(sizeof(Lista));
    //Verifica alocação
    if (novalista == NULL){
        printf("Erro ao alocar memoria ");
        exit(1);
    }
    novalista->inicio = NULL;
    novalista->fim = NULL;
    return novalista;
}

//Função que exibe o elemento
void exibir_elemento (Elemento_LISTA *aux) {
    printf("\n------------------------------------------\n");
    printf("\nNome: %s\nData de Cadastro: %s\nTelefone: %s\nEmail: %s\nCarro: %s\nCor predominante: %s\nPlaca do carro: %s\nServiço(s) realizado(s): %s\n", aux->nome, aux->datadeCadastro, aux->telefone, aux->email, aux->carro, aux->cor_carro, aux->placa_carro, aux->servico);
    printf("\n------------------------------------------\n");
}

//Exibe lista completa
void exibir_lista(Lista* novalista) {
    int qtd=0,  num = 1;

    if (novalista->inicio == NULL) {
        system("cls");
        printf("\nLista Vazia!\n");
        return;
    }
    system("cls"); //limpa tela

    Elemento_LISTA *aux = novalista->inicio;

    printf("\n\n--------------------------------------------------------------------------\n");
    printf("\n                              Lista de Clientes\n");
    printf("\n----------------------------------------------------------------------------\n");
    while (aux != NULL) {
        printf("\nContato %d", num);
        exibir_elemento(aux);
        aux = aux->proximo;
        qtd++;
        num++;
    }
    printf("\n");
    printf("\nQUANTIDADE DE CONTATOS: %d\n", qtd);
}

// Função para inserir um novo elemento na lista
void inserir(Lista* novalista) {
    Elemento_LISTA* novoElemento = (Elemento_LISTA*)malloc(sizeof(Elemento_LISTA));
    //Verifica alocação
    if (novoElemento == NULL){
        printf("Erro ao alocar memoria ");
        exit(1);
    }
    system("cls");
    printf("\n------------------------------\n");
    printf(" Entre com os dados do cliente:\n ");
    printf("\n------------------------------\n");
    printf("Digite o nome: ");
    scanf(" %[^\n]", novoElemento->nome);
    printf("Digite a data de cadastro (DD/MM/AAAA): ");
    scanf(" %[^\n]", novoElemento->datadeCadastro);
    printf("Digite o telefone: ");
    scanf(" %[^\n]", novoElemento->telefone);
    printf("Digite o email: ");
    scanf(" %[^\n]", novoElemento->email);
    printf("Digite o modelo do carro: ");
    scanf(" %[^\n]", novoElemento->carro);
    printf("Digite a cor do carro: ");
    scanf(" %[^\n]", novoElemento->cor_carro);
    printf("Digite a placa do carro: ");
    scanf(" %[^\n]", novoElemento->placa_carro);
    printf("Digite o(s) serviço(s) realizado(s): ");
    scanf(" %[^\n]", novoElemento->servico);


    novoElemento->proximo = NULL;
    novoElemento->anterior = novalista->fim;

    if (novalista->fim == NULL) {
        novalista->inicio = novoElemento;
    } else {
        novalista->fim->proximo = novoElemento;
    }
    novalista->fim = novoElemento;

    system("cls");
    printf("\nContato salvo!\n\n");
}

// Função para buscar e exibir um cliente por nome (sem editar/remover)
void buscar_exibir_cliente(Lista* novalista) {
    char nomeBusca[100];
    int encontrado = 0;

    if (novalista->inicio == NULL) {
        system("cls");
        printf("\nLista Vazia!\n");
        return;
    }

    system("cls");
    printf("Digite o nome do cliente que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    Elemento_LISTA* aux = novalista->inicio;
    while (aux != NULL) {
        if (strcmp(aux->nome, nomeBusca) == 0) {
            printf("\nCliente encontrado:\n");
            exibir_elemento(aux);
            encontrado = 1;
            break;
        }
        aux = aux->proximo;
    }

    if (!encontrado) {
        printf("\nCliente não encontrado.\n");
    }

    printf("\nPressione qualquer tecla para continuar...");
    //ler um único caractere do teclado e Pausa o programa até que uma tecla seja pressionada
    getche();
    system("cls");
}

// Função para remover a lista completa
void remover_lista(Lista* novalista) {
    if (novalista->inicio == NULL) {
        printf("\nLista vazia! Não há elementos para remover.\n\n");
        return;
    }

    Elemento_LISTA* remv = novalista->inicio;
    printf("Removendo: %s\n", remv->nome);
    novalista->inicio = novalista->inicio->proximo;

    if (novalista->inicio == NULL) {
        novalista->fim = NULL;
    } else {
        novalista->inicio->anterior = NULL;
    }
    free(remv);
}

//Libera a lista completa
void liberarLista(Lista* novalista) {

    if (novalista->inicio == NULL) {
        printf("\nLista Vazia!\n");
        return;
    }

    while (novalista->inicio != NULL) {
        remover_lista(novalista);
    }
    free(novalista);
}

//função para percorrer lista
void percorrer(Lista *novalista) {
    int tecla, num = 1;

    if (novalista->inicio == NULL) {
        system("cls");
        printf("\nLista Vazia!\n");
        return;
    }

    system("cls");
    Elemento_LISTA *elemento = novalista->inicio;
    printf("\nContato 1:\n");
    exibir_elemento(elemento);

    do {

        printf("\n\nUse as setas para cima e para baixo para percorrer a lista ou ESC para sair.\n");
        tecla = getch(); //lê um caractere do teclado sem esperar o ENTER e exibi-lo

        //Verifica se a tecla é uma tecla especial
        if (tecla == 0 || tecla == 224){
            tecla = getch(); //lê o segundo código para identificar qual tecla especial foi pressionada
            switch (tecla){
            case (72): //Seta para cima
                if (elemento->proximo != NULL){
                    system("cls");
                    num++;
                    printf("\nContato %d",num);
                    elemento = elemento->proximo; //Move o ponteiro elemento para o próximo elemento na lista
                    exibir_elemento(elemento);
                } else {
                    printf("\nFIM DA LISTA");
                }
                break;
            case(80):  //Seta para baixo
                if (elemento->anterior != NULL){
                    system("cls");
                    num--;
                    printf("\nContato %d",num);
                    elemento = elemento->anterior; //Move o ponteiro elemento para o elemento anterior na lista
                    exibir_elemento(elemento);
                } else {
                    printf("\nINICIO DA LISTA");
                }
                break;
            }
        }
    } while(tecla != 27); //enquanto a tecla pressionada não for ESC
    system("cls");
}

// Função para editar/remover contato
void remover_contato(Lista *novalista) {

    char contato[100];
    int opcao;
    int edicao;

    if (novalista->inicio == NULL) {
        system("cls");
        printf("\nLista Vazia!\n");
        return;
    }
    system("cls");
    printf("\nDigite o nome do contato: ");
    scanf(" %[^\n]", contato);

    Elemento_LISTA *elemento = novalista->inicio;
    while (elemento != NULL) {
        if (strcmp(elemento->nome, contato) == 0) {
            printf("\nContato encontrado:\n");
            exibir_elemento(elemento);

            printf("\nEscolha uma opção:\n");
            printf("1. Editar\n");
            printf("2. Remover\n");
            printf("3. Cancelar\n");
            printf("\nOpção: ");
            scanf("%d", &opcao);

                if (opcao == 1) {
                    system("cls");
                    printf("\nO que você deseja editar?\n");
                    printf("\nEscolha uma opção:\n");
                    printf("1. Nome\n");
                    printf("2. Data de Cadastro\n");
                    printf("3. Telefone\n");
                    printf("4. Email\n");
                    printf("5. Modelo do carro\n");
                    printf("6. Cor do carro\n");
                    printf("7. Placa do carro\n");
                    printf("8. Serviço realizado\n");
                    printf("10. Tudo\n");
                    printf("0. Voltar\n");
                    printf("\nOpção: ");
                    scanf("%d", &edicao);

                        switch (edicao) {
                            case 1:
                                printf("Digite o novo nome: ");
                                scanf(" %[^\n]", elemento->nome);
                                system("cls");
                                exibir_elemento(elemento);
                                printf("\nContato atualizado com sucesso!\n");
                                getche();
                            break;

                            case 2:
                                printf("Digite a nova data de cadastro (DD/MM/AAAA): ");
                                scanf(" %[^\n]", elemento->datadeCadastro);
                                system("cls");
                                exibir_elemento(elemento);
                                printf("\nContato atualizado com sucesso!\n");
                                getche();
                            break;

                            case 3:
                                printf("Digite o novo telefone: ");
                                scanf(" %[^\n]", elemento->telefone);
                                system("cls");
                                exibir_elemento(elemento);
                                printf("\nContato atualizado com sucesso!\n");
                                getche();
                            break;

                            case 4:
                                printf("Digite o novo email: ");
                                scanf(" %[^\n]", elemento->email);
                                system("cls");
                                exibir_elemento(elemento);
                                printf("\nContato atualizado com sucesso!\n");
                                getche();
                            break;

                            case 5:
                                printf("Digite o modelo do carro: ");
                                scanf(" %[^\n]", elemento->carro);
                                system("cls");
                                exibir_elemento(elemento);
                                printf("\nContato atualizado com sucesso!\n");
                                getche();
                            break;

                            case 6:
                                printf("Digite a cor do carro: ");
                                scanf(" %[^\n]", elemento->cor_carro);
                                system("cls");
                                exibir_elemento(elemento);
                                printf("\nContato atualizado com sucesso!\n");
                                getche();
                            break;

                            case 7:
                                printf("Digite a placa do carro: ");
                                scanf(" %[^\n]", elemento->placa_carro);
                                system("cls");
                                exibir_elemento(elemento);
                                printf("\nContato atualizado com sucesso!\n");
                                getche();
                            break;

                            case 8:
                                printf("Digite o(s) serviço(s) realizado(s): ");
                                scanf(" %[^\n]", elemento->servico);
                                system("cls");
                                exibir_elemento(elemento);
                                printf("\nContato atualizado com sucesso!\n");
                                getche();
                            break;

                            case 10:
                                printf("Digite o novo nome: ");
                                scanf(" %[^\n]", elemento->nome);
                                printf("Digite a nova data de nascimento (DD/MM/AAAA): ");
                                scanf(" %[^\n]", elemento->datadeCadastro);
                                printf("Digite o novo telefone: ");
                                scanf(" %[^\n]", elemento->telefone);
                                printf("Digite o novo email: ");
                                scanf(" %[^\n]", elemento->email);
                                printf("Digite o modelo do carro: ");
                                scanf(" %[^\n]", elemento->carro);
                                printf("Digite a cor do carro: ");
                                scanf(" %[^\n]", elemento->cor_carro);
                                printf("Digite a placa do carro: ");
                                scanf(" %[^\n]", elemento->placa_carro);
                                printf("Digite o(s) serviço(s) realizado(s): ");
                                scanf(" %[^\n]", elemento->servico);
                                system("cls");
                                exibir_elemento(elemento);
                            printf("\nContato atualizado com sucesso!\n");
                            getche();
                            break;

                            case 0:
                            system("cls");
                            printf("Edição cancelada. Aperte enter para voltar\n");
                            getche();
                            return;
                            }
                }
        else if (opcao == 2) {
                if (elemento->anterior != NULL) {
                    elemento->anterior->proximo = elemento->proximo;
                } else {
                    novalista->inicio = elemento->proximo;
                }
                if (elemento->proximo != NULL) {
                    elemento->proximo->anterior = elemento->anterior;
                } else {
                    novalista->fim = elemento->anterior;
                }
                system("cls");
                free(elemento);
                printf("\nRemovido com sucesso!\n");
                getche();
        }
        system("cls");
        return;
        }
        elemento = elemento->proximo;
    }
    printf("\nContato não encontrado.\n");
}


// Função para salvar os contatos em um arquivo de texto
void salvarEmArquivo(Lista* novalista) {
    FILE* arquivo = fopen("contatos.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Elemento_LISTA* aux = novalista->inicio;
    while (aux != NULL) {
        fprintf(arquivo, "%s\n", aux->nome);
        fprintf(arquivo, "%s\n", aux->datadeCadastro);
        fprintf(arquivo, "%s\n", aux->telefone);
        fprintf(arquivo, "%s\n", aux->email);
        fprintf(arquivo, "%s\n", aux->carro);
        fprintf(arquivo, "%s\n", aux->cor_carro);
        fprintf(arquivo, "%s\n", aux->placa_carro);
        fprintf(arquivo, "%s\n", aux->servico);
        aux = aux->proximo;
    }

    fclose(arquivo);
    printf("Arquivo salvo.\n");
}

// Função para carregar os contatos de um arquivo de texto
void carregarDeArquivo(Lista* novalista) {
    FILE* arquivo = fopen("contatos.txt", "r");
    if (!arquivo) {
        printf("Nenhum arquivo encontrado ou erro ao abrir!\n");
        return;
    }

    while (!feof(arquivo)) {
        Elemento_LISTA* novoElemento = (Elemento_LISTA*)malloc(sizeof(Elemento_LISTA));

        if (fscanf(arquivo, " %[^\n]", novoElemento->nome) == EOF) break;
        fscanf(arquivo, " %[^\n]", novoElemento->datadeCadastro);
        fscanf(arquivo, " %[^\n]", novoElemento->telefone);
        fscanf(arquivo, " %[^\n]", novoElemento->email);
        fscanf(arquivo, " %[^\n]", novoElemento->carro);
        fscanf(arquivo, " %[^\n]", novoElemento->cor_carro);
        fscanf(arquivo, " %[^\n]", novoElemento->placa_carro);
        fscanf(arquivo, " %[^\n]", novoElemento->servico);

        novoElemento->proximo = NULL;
        novoElemento->anterior = novalista->fim;

        if (novalista->fim == NULL) {
            novalista->inicio = novoElemento;
        } else {
            novalista->fim->proximo = novoElemento;
        }
        novalista->fim = novoElemento;
    }

    fclose(arquivo);
    printf("Contatos carregados com sucesso!\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Lista* novalista = criarLista();
    int opcao;

    printf("\n\n-----------------------------------\n");
    printf("\n        _______            ");
    printf("\n       //  ||\  \\         Oficina  ");
    printf("\n _____//___||_\__\\___       ");
    printf("\n )  _          _    \\      ");
    printf("\n |_/ \\________/ \\___|      ADSL ");
    printf("\n___\\_/________\\_/____      ");
    printf("\n------------------------------------\n");

    carregarDeArquivo(novalista); // Carregar contatos do arquivo ao iniciar o programa

    do {
        printf("\n\nMenu:\n");
        printf("0. Exibir lista de clientes\n");
        printf("1. Inserir cliente\n");
        printf("2. Buscar cliente  \n");
        printf("3. Remover lista completa de clientes\n");
        printf("4. Percorrer lista de clientes\n");
        printf("5. Editar ou Remover Cliente\n");
        printf("6. Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                exibir_lista(novalista);
                break;
            case 1:
                inserir(novalista);
                exibir_elemento(novalista->fim); //exibir o elemento criado
                break;
            case 2:
                buscar_exibir_cliente(novalista);
                break;
            case(3):
                system("cls");
                liberarLista(novalista);
                break;
            case 4:
                percorrer(novalista);
                break;
            case 5:
                remover_contato(novalista);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    salvarEmArquivo(novalista);
    liberarLista(novalista);

    return 0;

    printf("Hello world!\n");
    return 0;
}
