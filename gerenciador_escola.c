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
        switch (input) {
            case 1:
                char data[10], dia[2], mes[2], ano[4];
                struct estudante estudante_cadastrado;
                clear(20);
                estudante_cadastrado.ID = 1;
                printf("Digite o nome do Estudante:\n");
                scanf("%s", &estudante_cadastrado.nome);
                printf("Digite a data de nascimento do Estudante no formato DD/MM/AAAA:\n");
                scanf("%s", &data);
                dia[0] = data[0];
                dia[1] = data[1];
                printf("%s", dia);

                FILE *f;
                f = fopen("../estudantes.bin", "ab");
                if (f == NULL) {
                    perror("Erro ao abrir o arquivo");
                }
                fwrite(&estudante_cadastrado, sizeof(estudante_cadastrado), 1, f);
                fclose(f);
                break;
            case 2:
                char nome[100];
                struct estudante estudantes;
                clear(20);
                printf("Digite o nome do Estudante:\n");
                scanf("%s", &nome);
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                f = fopen("../estudantes.bin", "rb");
                while (fread(&estudantes, sizeof(struct estudante), 1, f) == 1) {
                    if (!strcmp(nome, estudantes.nome)) {
                        clear(20);
                        printf("ID: %d\n", estudantes.ID);
                        printf("nome: %s\n", estudantes.nome);
                        printf("Data de nascimento: %d/%d/%d\n", estudantes.nascimento.dia, estudantes.nascimento.mes, estudantes.nascimento.ano);
                        printf("\nPressione Enter para continuar\n");
                        char pausar[20];
                        scanf("%[^\n]", pausar);
                    }
                }
                fclose(f);
                break;
            case 3:
                break;
            case 4:
                bool nomesiguais;
                char nome2[100];
                struct estudante estudantes2[10];
                clear(20);
                printf("Digite o nome do Estudante que deseja excluir:\n");
                scanf("%s", &nome2);
                f = fopen("../estudantes.bin", "rb");
                int i = 0;
                while (fread(&estudantes2[i], sizeof(struct estudante), 1, f) == 1) {
                    i++;
                }
                fclose(f);
                f = fopen("../estudantes.bin", "wb");
                for (i = 0; i < (sizeof(estudantes2)/sizeof(estudantes2[0])); i++) {
                    nomesiguais = true;
                    if (strlen(nome2) == strlen(estudantes2[i].nome)) {
                        for (int i2 = 0; i2 < strlen(nome2); i2++) {
                            if (nome2[i2] != estudantes2[i].nome[i2]){
                                nomesiguais = false;
                                break;
                            }
                        }
                    }
                    else {
                        nomesiguais = false;
                    }
                    printf("%s\n", nome2);
                    printf("%s\n", estudantes2[i].nome);
                    printf("%d\n", nomesiguais);
                    if (nomesiguais == false) {
                        fwrite(&estudantes2[i], sizeof(estudantes2[i]), 1, f);
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