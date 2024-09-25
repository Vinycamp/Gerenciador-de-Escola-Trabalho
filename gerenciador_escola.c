#include <stdio.h>
#include "gerenfunc.h"

void gestao(char nome_da_gestao[12]){
    char buffer[100];
    int input;
    int opcaoinvalida = 0;
    char nome_da_gestao_singular[12];
    int n = 1;
    if (strcmp(nome_da_gestao, "professores") == 0) {
        n = 2;
    }
    for (int i = 0; i < strlen(nome_da_gestao)-n; i++) {
            nome_da_gestao_singular[i] = nome_da_gestao[i];
    }
    while (1) {
        clear(20);
        if (opcaoinvalida == 0) {
            printf("Gestao de %s!\n", nome_da_gestao);
        }
        else {
            printf("Voce digitou uma opcao invalida.\n");
        }
        printf("Digite o numero correspondente a opcao que deseja:\n");
        printf("\n");
        printf("(1) Cadastrar %s   (2) Consultar %s\n", nome_da_gestao_singular, nome_da_gestao_singular);
        printf("(3) Atualizar %s   (4) Excluir %s\n", nome_da_gestao_singular, nome_da_gestao_singular);
        printf("(5) Sair da Gestao\n");
        buffer[0] = '\0';
        readinput(buffer, 0);
        if (sscanf(buffer, "%d", &input) != 1 || input > 5 || input < 1) {
            opcaoinvalida = 1;
            input = 0;
        }

        // Definições de variáveis para o switch
        int quantidade = 100;

        switch (input) {
            case 1:
                cadastrar(quantidade, nome_da_gestao, nome_da_gestao_singular);
                break;
            case 2:
                consultar(quantidade, nome_da_gestao, nome_da_gestao_singular);
                break;
            case 3:
                atualizar(quantidade, nome_da_gestao, nome_da_gestao_singular);
                break;
            case 4:
                excluir(quantidade, nome_da_gestao, nome_da_gestao_singular);
                break;
        }
        if(input == 5){
            break;
        }
    }
}

void main(){
    char buffer[100];
    int input;

    int opcaoinvalida = 0;
    while (1) {
        clear(20);
        if (opcaoinvalida == 0) {
            printf("Bem-vindo ao sistema de gerenciamento da escola!\n");
        }
        else {
            printf("Voce digitou uma opcao invalida.\n");
        }
        printf("Digite o numero correspondente a opcao que deseja:\n");
        printf("\n");
        printf("(1) Gestao de Estudantes    (2) Gestao de Professores\n");
        printf("(3) Gestao de Disciplinas   (4) Gestao de Turmas\n");
        printf("(5) Sair do Sistema\n");
        buffer[0] = '\0';
        readinput(buffer, 0);
        if (sscanf(buffer,"%d", &input) != 1 || input > 5 || input < 1) {
            opcaoinvalida = 1;
            input = 0;
        }
        switch (input) {
            case 1:
                gestao("estudantes");
                break;
            case 2:
                gestao("professores");
                break;
            case 3:
                gestao("disciplinas");
                break;
            case 4:
                gestao("turmas");
                break;
        }
        if(input == 5){
            clear(20);
            printf("Programa finalizado!");
            break;
        }
    }
}