#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void clear(int n){
    for(int i = 0;i < n;i++){
        printf("\n");
    }
}

struct data{
    int dia;
    int mes;
    int ano;
};

struct estudante {
    int ID;
    char nome[100];
    struct data nascimento;
};

void gestao_estudantes(){
    int input = 0;
    while (1) {
        clear(20);
        printf("Gestao de Estudantes!\n");
        printf("Digite o numero correspondente a opcao que deseja:\n");
        printf("\n");
        printf("(1) Cadastrar Estudante   (2) Consultar Estudante\n");
        printf("(3) Atualizar Estudante   (4) Excluir Estudante\n");
        printf("(5) Sair da Gestao\n");
        scanf("%d", &input);
        FILE *f;
        f = fopen("../estudantes.bin", "rb");

        // Definições de variáveis para o switch
        int i = 0, quantidade_de_estudantes = 100;
        char nome[100];
        char pausar[20];
        struct estudante estudantes[quantidade_de_estudantes];
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        while (fread(&estudantes[i], sizeof(struct estudante), 1, f) == 1) {
            i++;
        }
        fclose(f);

        switch (input) {
            case 1:
                char data[10], *token, delimitador[2] = "/";
                char *endptr;
                long int dia, mes, ano;
                struct estudante estudante_cadastrado;
                clear(20);
                for (i = 0; i < quantidade_de_estudantes; i++) {
                    if (estudantes[i].ID == 0) {
                        break;
                    }
                }
                estudante_cadastrado.ID = estudantes[i-1].ID+1;
                printf("Digite o nome do Estudante que deseja cadastrar:\n");
                scanf("%s", &estudante_cadastrado.nome);
                printf("Digite a data de nascimento do Estudante no formato DD/MM/AAAA:\n");
                scanf("%s", &data);

                token = strtok(data, delimitador);
                const char *stringlegal1 = token;
                dia = strtol(stringlegal1, &endptr, 10);
                estudante_cadastrado.nascimento.dia = dia;
                token = strtok(NULL, delimitador);
                const char *stringlegal2 = token;
                mes = strtol(stringlegal2, &endptr, 10);
                estudante_cadastrado.nascimento.mes = mes;
                token = strtok(NULL, delimitador);
                const char *stringlegal3 = token;
                ano = strtol(stringlegal3, &endptr, 10);
                estudante_cadastrado.nascimento.ano = ano;

                printf("\nEstudante cadastrado no ID: %d\n", estudante_cadastrado.ID);
                printf("Pressione Enter para continuar\n");
                while ((c = getchar()) != '\n' && c != EOF);
                scanf("%[^\n]", pausar);
                f = fopen("../estudantes.bin", "ab");
                if (f == NULL) {
                    perror("Erro ao abrir o arquivo");
                }
                fwrite(&estudante_cadastrado, sizeof(estudante_cadastrado), 1, f);
                fclose(f);
                break;
            case 2:
                clear(20);
                printf("Digite o nome do Estudante que deseja consultar:\n");
                scanf("%s", &nome);
                for (i = 0; i < (sizeof(estudantes)/sizeof(estudantes[0])); i++) {
                    if (estudantes[i].ID == 0) {
                        break;
                    }
                    if (!strcmp(nome, estudantes[i].nome)) {
                        clear(20);
                        printf("ID: %d\n", estudantes[i].ID);
                        printf("nome: %s\n", estudantes[i].nome);
                        printf("Data de nascimento: %d/%d/%d\n", estudantes[i].nascimento.dia, estudantes[i].nascimento.mes, estudantes[i].nascimento.ano);
                        printf("\nPressione Enter para continuar\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        scanf("%[^\n]", pausar);
                        break;
                    }
                }
                break;
            case 3:
                break;
            case 4:
                bool nomesiguais;
                clear(20);
                printf("Digite o nome do Estudante que deseja excluir:\n");
                scanf("%s", &nome);
                f = fopen("../estudantes.bin", "wb");
                for (i = 0; i < quantidade_de_estudantes; i++) {
                    nomesiguais = true;
                    if (strlen(nome) == strlen(estudantes[i].nome)) {
                        int i2;
                        for (i2 = 0; i2 < strlen(nome); i2++) {
                            if (nome[i2] != estudantes[i].nome[i2]){
                                nomesiguais = false;
                                break;
                            }
                        }
                    }
                    else {
                        nomesiguais = false;
                    }
                    if (estudantes[i].ID == 0) {
                        break;
                    }
                    if (nomesiguais == false) {
                        fwrite(&estudantes[i], sizeof(estudantes[i]), 1, f);
                    }
                }
                fclose(f);
                break;
        }
        if(input == 5){
            break;
        }
    }
}

void gestao_professores(){
    int input = 0;
    while (1) {
        clear(20);
        printf("Gestao de Professores!\n");
        printf("Digite o numero correspondente a opcao que deseja:\n");
        printf("\n");
        printf("(1) Cadastrar Professor   (2) Consultar Professor\n");
        printf("(3) Atualizar Professor   (4) Excluir Professor\n");
        printf("(5) Sair da Gestao\n");
        scanf("%d", &input);
        switch (input) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
        if(input == 5){
            break;
        }
    }
}

void gestao_disciplinas(){
    int input = 0;
    while (1) {
        clear(20);
        printf("Gestao de Disciplinas!\n");
        printf("Digite o numero correspondente a opcao que deseja:\n");
        printf("\n");
        printf("(1) Cadastrar Disciplina   (2) Consultar Disciplina\n");
        printf("(3) Atualizar Disciplina   (4) Excluir Disciplina\n");
        printf("(5) Sair da Gestao\n");
        scanf("%d", &input);
        switch (input) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
        if(input == 5){
            break;
        }
    }
}

void gestao_turmas(){
    int input = 0;
    while (1) {
        clear(20);
        printf("Gestao de Turmas!\n");
        printf("Digite o numero correspondente a opcao que deseja:\n");
        printf("\n");
        printf("(1) Cadastrar Turma   (2) Consultar Turma\n");
        printf("(3) Atualizar Turma   (4) Excluir Turma\n");
        printf("(5) Sair da Gestao\n");
        scanf("%d", &input);
        switch (input) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }
        if(input == 5){
            break;
        }
    }
}

void main(){
    int input = 0;
    while (1) {
        clear(20);
        printf("Bem-vindo ao sistema de gerenciamento da escola!\n");
        printf("Digite o numero correspondente a opcao que deseja:\n");
        printf("\n");
        printf("(1) Gestao de Estudantes    (2) Gestao de Professores\n");
        printf("(3) Gestao de Disciplinas   (4) Gestao de Turmas\n");
        printf("(5) Sair do Sistema\n");
        scanf("%d", &input);
        switch (input) {
            case 1:
                gestao_estudantes();
                break;
            case 2:
                gestao_professores();
                break;
            case 3:
                gestao_disciplinas();
                break;
            case 4:
                gestao_turmas();
                break;
        }
        if(input == 5){
            clear(20);
            printf("Programa finalizado!");
            break;
        }
    }
}