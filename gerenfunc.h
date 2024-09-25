#ifndef PROJETO_ESCOLA_GERENFUNC_H
#define PROJETO_ESCOLA_GERENFUNC_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct data{
    int dia;
    int mes;
    int ano;
};

struct pessoa {
    int ID;
    char nome[100];
    struct data nascimento;
};

struct disciplina {
    int codigo;
    char nome[100];
    int ID_prof;
};

struct turma {
    int codigo_turma;
    int codigo_disciplina;
    int ID_prof;
    int ID_alunos[100];
};

void clear(int n){
    for(int i = 0;i < n;i++){
        printf("\n");
    }
}

int char_is_number(char c) {
    char numeros[] = "0123456789";
    for (int i = 0; i < 10; i++) {
        if (c == numeros[i]) {
            return 1;
        }
    }
    return 0;
}

void readinput(char string[100], int is_data) {
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    for(int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '\n' && is_data == 0) {
            break;
        }
        string[i] = buffer[i];
    }
}

void ler_pessoas(int quantidade, struct pessoa *pessoas, char nome_da_gestao[12]) {
    FILE *f;
    for (int i = 0; i < quantidade; i++) {
        pessoas[i].ID = 0;
        for (int j = 0; j < 100; j++) {
            pessoas[i].nome[j] = 0;
        }
        pessoas[i].nascimento.dia = 0;
        pessoas[i].nascimento.mes = 0;
        pessoas[i].nascimento.ano = 0;
    }
    char arquivo[19];
    for (int i = 0; i < 19; i++) {
        if (i < 3) {
            arquivo[i] = "../"[i];
        }
        if (i >= 3 && i < (3 + strlen(nome_da_gestao))) {
            arquivo[i] = nome_da_gestao[i-3];
        }
        if (i >= (3 + strlen(nome_da_gestao))) {
            arquivo[i] = ".bin"[i-(3 + strlen(nome_da_gestao))];
        }
    }
    f = fopen(arquivo, "rb");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
    }
    fread(pessoas, sizeof(struct pessoa), 100, f);
    fclose(f);
}

void ler_disciplinas(int quantidade, struct disciplina *disciplinas) {
    FILE *f;
    for (int i = 0; i < quantidade; i++) {
        disciplinas[i].codigo = 0;
        for (int j = 0; j < 100; j++) {
            disciplinas[i].nome[j] = 0;
        }
        disciplinas[i].ID_prof = 0;
    }
    f = fopen("../disciplinas.bin", "rb");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
    }
    fread(disciplinas, sizeof(struct disciplina), 100, f);
    fclose(f);
}

void transformar_data_em_inteiro(char data[11], char *dia, char *mes, char *ano) {
    char *token, delimitador[2] = "/";
    token = strtok(data, delimitador);
    const char *diastring = token;
    sscanf(diastring, "%d", dia);
    token = strtok(NULL, delimitador);
    const char *messtring = token;
    sscanf(messtring, "%d", mes);
    token = strtok(NULL, delimitador);
    const char *anostring = token;
    sscanf(anostring, "%d", ano);
}

void cadastrar(int quantidade, char nome_da_gestao[12], char nome_da_gestao_singular[12]) {
    if (strcmp(nome_da_gestao, "disciplinas") == 0) {
        struct disciplina disciplina_cadastrada;
        struct disciplina disciplinas[quantidade];
        ler_disciplinas(quantidade, disciplinas);
        clear(20);
        //definir o ID do nova disciplina
        int index = 0;
        for (int i = 0; i < quantidade; i++) {
            if (disciplinas[i].codigo == 0) {
                index = i;
                break;
            }
        }
        if (index == 0) {
            disciplina_cadastrada.codigo = 1;
        }
        else {
            disciplina_cadastrada.codigo = disciplinas[index-1].codigo+1;
        }

        //pedir o nome da nova disciplina
        char buffer[100];
        bool formatocorreto = false;
        while (formatocorreto == false) {
            printf("Digite o nome da disciplina que deseja cadastrar:\n");
            readinput(buffer, 0);
            if (strlen(buffer) > 0) {
                formatocorreto = true;
            }
            if (formatocorreto == false) {
                clear(20);
                printf("Formato incorreto. Tente novamente.\n\n");
            }
        }
        for (int i = 0; i < strlen(buffer); i++) {
            disciplina_cadastrada.nome[i] = buffer[i];
        }

        //pedir o professor da nova disciplina
        struct pessoa professores[quantidade];
        char nome_prof[100];
        ler_pessoas(quantidade, professores, "professores");
        int ID_prof;
        clear(20);
        printf("Digite o ID ou o nome do professor que deseja associar:\n");
        readinput(nome_prof, 0);

        //pedir a partir de um nome
        char sID[100];
        int mesmonome = 0;
        if (sscanf(nome_prof, "%d", &ID_prof) != 1) {
            bool formatocorreto = false;
            while (formatocorreto == false) {
                formatocorreto = true;
                for (int i = 0; i < (sizeof(professores) / sizeof(professores[0])); i++) {

                    //quando chegar em um ID inválido, quer dizer que acabou a lista de professores e o programa sai do loop
                    if (professores[i].ID == 0) {
                        break;
                    }

                    //mostrar as informações apenas do professor com o mesmo nome
                    if (strcmp(nome_prof, professores[i].nome) == 0) {
                        ID_prof = professores[i].ID;
                        mesmonome++;
                        printf("\n");
                        printf("ID: %d\n", professores[i].ID);
                        printf("nome: %s\n", professores[i].nome);
                        printf("Data de nascimento: %d/%d/%d\n", professores[i].nascimento.dia, professores[i].nascimento.mes,
                               professores[i].nascimento.ano);
                    }
                }
                if (mesmonome == 1) {
                    printf("\nPressione Enter para continuar\n");
                    readinput(buffer, 0);
                }
                else {
                    if (mesmonome == 0) {
                        printf("Nao existe professor com esse nome\n");
                        printf("Pressione Enter para continuar\n");
                        readinput(buffer, 0);
                        break;
                    }
                    printf("\nEscolha o ID do professor que deseja atualizar:\n");
                    readinput(sID, 0);
                    if (sscanf(sID, "%d", &ID_prof) != 1) {
                        formatocorreto = false;
                        clear(20);
                        printf("Formato incorreto. Tente novamente.\n");
                    }
                    else {
                        for (int i = 0; i < (sizeof(professores) / sizeof(professores[0])); i++) {
                            if (ID_prof == professores[i].ID) {
                                if (strcmp(buffer, professores[i].nome) != 0) {
                                    formatocorreto = false;
                                    clear(20);
                                    printf("%s nao encontrado. Tente novamente.\n", nome_da_gestao_singular);
                                    break;
                                }
                                break;
                            }
                            else {
                                if (professores[i].ID == 0) {
                                    clear(20);
                                    printf("%s nao encontrado. Tente novamente.\n", nome_da_gestao_singular);
                                    formatocorreto = false;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

            //pedir a partir de um ID
        else {
            clear(20);
            for (int i = 0; i < (sizeof(professores) / sizeof(professores[0])); i++) {

                //quando chegar em um ID inválido, quer dizer que acabou a lista de professores e o programa sai do loop
                if (professores[i].ID == 0) {
                    break;
                }

                //mostrar as informações apenas do professor com o mesmo ID
                if (ID_prof == professores[i].ID) {
                    mesmonome++;
                    printf("\n");
                    printf("ID: %d\n", professores[i].ID);
                    printf("nome: %s\n", professores[i].nome);
                    printf("Data de nascimento: %d/%d/%d\n", professores[i].nascimento.dia, professores[i].nascimento.mes, professores[i].nascimento.ano);
                    break;
                }
            }
            if (mesmonome == 1) {
                printf("\nPressione Enter para continuar\n");
                readinput(buffer, 0);
            }
            else {
                printf("Nao existe professor com esse nome\n");
                printf("Pressione Enter para continuar\n");
                readinput(buffer, 0);
            }
        }
        disciplina_cadastrada.ID_prof = ID_prof;

        //salva o novo disciplina no arquivo
        if (mesmonome != 0) {
            FILE *f;
            f = fopen("../disciplinas.bin", "ab");
            if (f == NULL) {
                perror("Erro ao abrir o arquivo");
            }
            fwrite(&disciplina_cadastrada, sizeof(disciplina_cadastrada), 1, f);
            fclose(f);

            //imprime o ID da disciplina
            printf("\nDisciplina cadastrada com codigo: %d\n", disciplina_cadastrada.codigo);
            printf("Pressione Enter para continuar\n");
            readinput(buffer, 0);
        }
    }
    else if (strcmp(nome_da_gestao, "turmas") == 0) {
        
    }
    else {
        struct pessoa pessoa_cadastrada;
        struct pessoa pessoas[quantidade];
        ler_pessoas(quantidade, pessoas, nome_da_gestao);
        clear(20);
        //definir o ID do novo pessoa
        int index = 0;
        for (int i = 0; i < quantidade; i++) {
            if (pessoas[i].ID == 0) {
                index = i;
                break;
            }
        }
        if (index == 0) {
            pessoa_cadastrada.ID = 1;
        }
        else {
            pessoa_cadastrada.ID = pessoas[index-1].ID+1;
        }
    
        //pedir o nome do novo pessoa
        char buffer[100];
        bool formatocorreto = false;
        while (formatocorreto == false) {
            printf("Digite o nome do %s que deseja cadastrar:\n", nome_da_gestao_singular);
            readinput(buffer, 0);
            if (strlen(buffer) > 0) {
                formatocorreto = true;
            }
            if (formatocorreto == false) {
                clear(20);
                printf("Formato incorreto. Tente novamente.\n\n");
            }
        }
        for (int i = 0; i < strlen(buffer); i++) {
            pessoa_cadastrada.nome[i] = buffer[i];
        }
    
        //pedir a data de nascimento do novo pessoa
        char data[11];
        formatocorreto = false;
        while (formatocorreto == false) {
            printf("Digite a data de nascimento do %s no formato DD/MM/AAAA:\n", nome_da_gestao_singular);
            readinput(data, 1);
            formatocorreto = true;
    
            //vê se o tamanho da data está correto
            if (data[10] != '\n') {
                formatocorreto = false;
            }
    
            //passa por toda a string e vê se cada caractere está no formato correto
            for (int i = 0; i < 10; i++) {
                if (formatocorreto == false) {
                    break;
                }
                //olha as barras
                if (i == 2 || i == 5) {
                    if (data[i] != '/') {
                        formatocorreto = false;
                    }
                }
                    //olha os números
                else {
                    if (char_is_number(data[i]) == 0) {
                        formatocorreto = false;
                    }
                }
            }
            if (formatocorreto == false) {
                clear(20);
                printf("Formato incorreto. Tente novamente.\n\n");
            }
        }
        int dia, mes, ano;
        transformar_data_em_inteiro(data, &dia, &mes, &ano);
        pessoa_cadastrada.nascimento.dia = dia;
        pessoa_cadastrada.nascimento.mes = mes;
        pessoa_cadastrada.nascimento.ano = ano;
    
        //salva o novo pessoa no arquivo
        FILE *f;
    
        //definir nome do arquivo
        char arquivo[19];
        for (int i = 0; i < 19; i++) {
            if (i < 3) {
                arquivo[i] = "../"[i];
            }
            if (i >= 3 && i < (3 + strlen(nome_da_gestao))) {
                arquivo[i] = nome_da_gestao[i-3];
            }
            if (i >= (3 + strlen(nome_da_gestao))) {
                arquivo[i] = ".bin"[i-(3 + strlen(nome_da_gestao))];
            }
        }
        f = fopen(arquivo, "ab");
        if (f == NULL) {
            perror("Erro ao abrir o arquivo");
        }
        fwrite(&pessoa_cadastrada, sizeof(pessoa_cadastrada), 1, f);
        fclose(f);
    
        //imprime o ID do pessoa
        printf("\n%s cadastrado no ID: %d\n", nome_da_gestao_singular, pessoa_cadastrada.ID);
        printf("Pressione Enter para continuar\n");
        readinput(buffer, 0);
    }
}

void consultar(int quantidade, char nome_da_gestao[12], char nome_da_gestao_singular[12]) {
    if (strcmp(nome_da_gestao, "disciplinas") == 0) {
        char buffer[100];
        int codigo;
        struct disciplina disciplinas[quantidade];
        ler_disciplinas(quantidade, disciplinas);
        clear(20);
        printf("Digite o codigo ou o nome da disciplina que deseja consultar:\n");
        readinput(buffer, 0);

        clear(20);
        int mesmonome = 0;
        //Consultar a partir de um nome
        if (sscanf(buffer, "%d", &codigo) != 1) {
            for (int i = 0; i < (sizeof(disciplinas) / sizeof(disciplinas[0])); i++) {

                //quando chegar em um codigo inválido, quer dizer que acabou a lista de disciplinas e o programa sai do loop
                if (disciplinas[i].codigo == 0) {
                    break;
                }

                //mostrar as informações apenas da disciplina com o mesmo nome
                if (strcmp(buffer, disciplinas[i].nome) == 0) {
                    mesmonome++;
                    printf("\n");
                    printf("codigo: %d\n", disciplinas[i].codigo);
                    printf("nome: %s\n", disciplinas[i].nome);
                    printf("ID do professor: %d\n", disciplinas[i].ID_prof);
                }
            }
        }

            //Consultar a partir de um codigo
        else {
            for (int i = 0; i < (sizeof(disciplinas) / sizeof(disciplinas[0])); i++) {

                //quando chegar em um codigo inválido, quer dizer que acabou a lista de disciplinas e o programa sai do loop
                if (disciplinas[i].codigo == 0) {
                    break;
                }

                //mostrar as informações apenas da disciplina com o mesmo ID
                if (codigo == disciplinas[i].codigo) {
                    mesmonome++;
                    printf("\n");
                    printf("codigo: %d\n", disciplinas[i].codigo);
                    printf("nome: %s\n", disciplinas[i].nome);
                    printf("ID do professor: %d\n", disciplinas[i].ID_prof);
                }
            }
        }
        if (mesmonome == 0) {
            printf("\nNao existe disciplina com esse nome ou codigo\n");
            printf("Pressione Enter para continuar\n");
            readinput(buffer, 0);
        } else {
            printf("\nPressione Enter para continuar\n");
            readinput(buffer, 0);
        }
    }
    else if (strcmp(nome_da_gestao, "turmas") == 0) {

    }
    else {
        char buffer[100];
        int ID;
        struct pessoa pessoas[quantidade];
        ler_pessoas(quantidade, pessoas, nome_da_gestao);
        clear(20);
        printf("Digite o ID ou o nome do %s que deseja consultar:\n", nome_da_gestao_singular);
        readinput(buffer, 0);

        clear(20);
        int mesmonome = 0;
        //Consultar a partir de um nome
        if (sscanf(buffer, "%d", &ID) != 1) {
            for (int i = 0; i < (sizeof(pessoas) / sizeof(pessoas[0])); i++) {

                //quando chegar em um ID inválido, quer dizer que acabou a lista de pessoas e o programa sai do loop
                if (pessoas[i].ID == 0) {
                    break;
                }

                //mostrar as informações apenas do pessoa com o mesmo nome
                if (strcmp(buffer, pessoas[i].nome) == 0) {
                    mesmonome++;
                    printf("\n");
                    printf("ID: %d\n", pessoas[i].ID);
                    printf("nome: %s\n", pessoas[i].nome);
                    printf("Data de nascimento: %d/%d/%d\n", pessoas[i].nascimento.dia, pessoas[i].nascimento.mes, pessoas[i].nascimento.ano);
                }
            }
        }

        //Consultar a partir de um ID
        else {
            for (int i = 0; i < (sizeof(pessoas) / sizeof(pessoas[0])); i++) {

                //quando chegar em um ID inválido, quer dizer que acabou a lista de pessoas e o programa sai do loop
                if (pessoas[i].ID == 0) {
                    break;
                }

                //mostrar as informações apenas do pessoa com o mesmo ID
                if (ID == pessoas[i].ID) {
                    mesmonome++;
                    printf("\n");
                    printf("ID: %d\n", pessoas[i].ID);
                    printf("nome: %s\n", pessoas[i].nome);
                    printf("Data de nascimento: %d/%d/%d\n", pessoas[i].nascimento.dia, pessoas[i].nascimento.mes, pessoas[i].nascimento.ano);
                }
            }
        }
        if (mesmonome == 0) {
            printf("Nao existe %s com esse nome ou ID\n", nome_da_gestao_singular);
            printf("Pressione Enter para continuar\n");
            readinput(buffer, 0);
        }
        else {
            printf("Pressione Enter para continuar\n");
            readinput(buffer, 0);
        }
    }
}

void atualizar(int quantidade, char nome_da_gestao[12], char nome_da_gestao_singular[12]) {
    char buffer[100];
    int ID;
    struct pessoa pessoa_atualizada;
    struct pessoa pessoas[quantidade];
    ler_pessoas(quantidade, pessoas, nome_da_gestao);
    clear(20);
    printf("Digite o ID ou o nome do %s que deseja atualizar:\n", nome_da_gestao_singular);
    readinput(buffer, 0);
    clear(20);

    //Atualizar a partir de um nome
    char sID[100];
    int mesmonome = 0;
    if (sscanf(buffer, "%d", &ID) != 1) {
        bool formatocorreto = false;
        while (formatocorreto == false) {
            formatocorreto = true;
            for (int i = 0; i < (sizeof(pessoas) / sizeof(pessoas[0])); i++) {

                //quando chegar em um ID inválido, quer dizer que acabou a lista de pessoas e o programa sai do loop
                if (pessoas[i].ID == 0) {
                    break;
                }

                //mostrar as informações apenas do pessoa com o mesmo nome
                if (strcmp(buffer, pessoas[i].nome) == 0) {
                    ID = pessoas[i].ID;
                    mesmonome++;
                    printf("\n");
                    printf("ID: %d\n", pessoas[i].ID);
                    printf("nome: %s\n", pessoas[i].nome);
                    printf("Data de nascimento: %d/%d/%d\n", pessoas[i].nascimento.dia, pessoas[i].nascimento.mes,
                           pessoas[i].nascimento.ano);
                }
            }
            if (mesmonome == 1) {
                printf("\nPressione Enter para continuar\n");
                readinput(buffer, 0);
            }
            else {
                if (mesmonome == 0) {
                    printf("Nao existe %s com esse nome ou ID\n", nome_da_gestao_singular);
                    printf("Pressione Enter para continuar\n");
                    readinput(buffer, 0);
                    break;
                }
                printf("\nEscolha o ID do %s que deseja atualizar:\n", nome_da_gestao_singular);
                readinput(sID, 0);
                if (sscanf(sID, "%d", &ID) != 1) {
                    formatocorreto = false;
                    clear(20);
                    printf("Formato incorreto. Tente novamente.\n");
                }
                else {
                    for (int i = 0; i < (sizeof(pessoas) / sizeof(pessoas[0])); i++) {
                        if (ID == pessoas[i].ID) {
                            if (strcmp(buffer, pessoas[i].nome) != 0) {
                                formatocorreto = false;
                                clear(20);
                                printf("%s nao encontrado. Tente novamente.\n", nome_da_gestao_singular);
                                break;
                            }
                            break;
                        }
                        else {
                            if (pessoas[i].ID == 0) {
                                clear(20);
                                printf("%s nao encontrado. Tente novamente.\n", nome_da_gestao_singular);
                                formatocorreto = false;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    //Atualizar a partir de um ID
    else {
        clear(20);
        for (int i = 0; i < (sizeof(pessoas) / sizeof(pessoas[0])); i++) {

            //quando chegar em um ID inválido, quer dizer que acabou a lista de pessoas e o programa sai do loop
            if (pessoas[i].ID == 0) {
                break;
            }

            //mostrar as informações apenas do pessoa com o mesmo ID
            if (ID == pessoas[i].ID) {
                mesmonome++;
                printf("\n");
                printf("ID: %d\n", pessoas[i].ID);
                printf("nome: %s\n", pessoas[i].nome);
                printf("Data de nascimento: %d/%d/%d\n", pessoas[i].nascimento.dia, pessoas[i].nascimento.mes, pessoas[i].nascimento.ano);
                break;
            }
        }
        if (mesmonome == 1) {
            printf("\nPressione Enter para continuar\n");
            readinput(buffer, 0);
        }
        else {
            printf("Nao existe %s com esse nome ou ID\n", nome_da_gestao_singular);
            printf("Pressione Enter para continuar\n");
            readinput(buffer, 0);
        }
    }

    //pegar as novas informações
    if (mesmonome != 0) {
        int index = 0;
        for (int i = 0; i < quantidade; i++) {
            //quando chegar em um ID inválido, quer dizer que acabou a lista de pessoas e o programa sai do loop
            if (pessoas[i].ID == ID) {
                index = i;
                break;
            }
        }

        //atualizar o ID do pessoa
        pessoa_atualizada.ID = ID;

        //atualizar o nome do pessoa
        char novonome[100];
        printf("Digite o nome atualizado (deixe em branco para nao mudar!):\n");
        readinput(novonome, 0);

        //caso o usuário deixar em branco, não atualizar
        if (strcmp(novonome, "") == 0) {
            for (int i = 0; i < strlen(pessoas[index].nome); i++) {
                pessoa_atualizada.nome[i] = pessoas[index].nome[i];
            }
        }

            //caso o usuário NÃO deixar em branco, atualizar
        else {
            for (int i = 0; i < strlen(novonome); i++) {
                pessoa_atualizada.nome[i] = novonome[i];
            }
        }

        //atualizar a data de nascimento do pessoa
        bool formatocorreto = false;
        char data[10];
        while (formatocorreto == false) {
            printf("Digite a data de nascimento atualizada (deixe em branco para nao mudar!):\n");
            readinput(data, 1);
            formatocorreto = true;

            //caso o usuário deixar em branco, não atualizar
            if (data[0] == '\n') {
                pessoa_atualizada.nascimento.dia = pessoas[index].nascimento.dia;
                pessoa_atualizada.nascimento.mes = pessoas[index].nascimento.mes;
                pessoa_atualizada.nascimento.ano = pessoas[index].nascimento.ano;
            }

            //caso o usuário NÃO deixar em branco, atualizar
            else {
                //vê se o tamanho da data está correto
                if (data[10] != '\n') {
                    formatocorreto = false;
                }

                //passa por toda a string e vê se cada caractere está no formato correto
                for (int i = 0; i < 10; i++) {
                    if (formatocorreto == false) {
                        break;
                    }
                    //olha as barras
                    if (i == 2 || i == 5) {
                        if (data[i] != '/') {
                            formatocorreto = false;
                        }
                    }
                        //olha os números
                    else {
                        if (char_is_number(data[i]) == 0) {
                            formatocorreto = false;
                        }
                    }
                    i++;
                }
                if (formatocorreto == false) {
                    clear(20);
                    printf("Formato incorreto. Tente novamente.\n\n");
                }
            }
            int dia, mes, ano;
            transformar_data_em_inteiro(data, &dia, &mes, &ano);
            pessoa_atualizada.nascimento.dia = dia;
            pessoa_atualizada.nascimento.mes = mes;
            pessoa_atualizada.nascimento.ano = ano;
        }
        FILE *f;

        //definir nome do arquivo
        char arquivo[19];
        for (int i = 0; i < 19; i++) {
            if (i < 3) {
                arquivo[i] = "../"[i];
            }
            if (i >= 3 && i < (3 + strlen(nome_da_gestao))) {
                arquivo[i] = nome_da_gestao[i-3];
            }
            if (i >= (3 + strlen(nome_da_gestao))) {
                arquivo[i] = ".bin"[i-(3 + strlen(nome_da_gestao))];
            }
        }
        f = fopen(arquivo, "wb");
        for (int i = 0; pessoas[i].ID != 0; i++) {
            if (pessoas[i].ID == pessoa_atualizada.ID) {
                fwrite(&pessoa_atualizada, sizeof(pessoa_atualizada), 1, f);
            }
            else {
                fwrite(&pessoas[i], sizeof(pessoas[i]), 1, f);
            }
        }
        fclose(f);
        clear(20);
        printf("%s atualizado com sucesso!\n", nome_da_gestao_singular);
        printf("Pressione Enter para continuar\n");
        readinput(buffer, 0);
    }
}

void excluir(int quantidade, char nome_da_gestao[12], char nome_da_gestao_singular[12]) {
    char buffer[100];
    int ID;
    struct pessoa pessoas[quantidade];
    ler_pessoas(quantidade, pessoas, nome_da_gestao);
    clear(20);
    printf("Digite o nome do %s que deseja excluir:\n", nome_da_gestao_singular);
    readinput(buffer, 0);
    //Excluir a partir de um nome
    char sID[100];
    int mesmonome = 0;
    if (sscanf(buffer, "%d", &ID) != 1) {
        bool formatocorreto = false;
        while (formatocorreto == false) {
            formatocorreto = true;
            for (int i = 0; i < (sizeof(pessoas) / sizeof(pessoas[0])); i++) {

                //quando chegar em um ID inválido, quer dizer que acabou a lista de pessoas e o programa sai do loop
                if (pessoas[i].ID == 0) {
                    break;
                }

                //mostrar as informações apenas do pessoa com o mesmo nome
                if (strcmp(buffer, pessoas[i].nome) == 0) {
                    ID = pessoas[i].ID;
                    mesmonome++;
                    printf("\n");
                    printf("ID: %d\n", pessoas[i].ID);
                    printf("nome: %s\n", pessoas[i].nome);
                    printf("Data de nascimento: %d/%d/%d\n", pessoas[i].nascimento.dia, pessoas[i].nascimento.mes,
                           pessoas[i].nascimento.ano);
                }
            }
            if (mesmonome == 1) {
                printf("\nPressione Enter para continuar\n");
                readinput(buffer, 0);
            }
            else {
                if (mesmonome == 0) {
                    printf("Nao existe %s com esse nome\n", nome_da_gestao_singular);
                    printf("Pressione Enter para continuar\n");
                    readinput(buffer, 0);
                    break;
                }
                printf("\nEscolha o ID do %s que deseja excluir:\n", nome_da_gestao_singular);
                readinput(sID, 0);
                if (sscanf(sID, "%d", &ID) != 1) {
                    formatocorreto = false;
                    clear(20);
                    printf("Formato incorreto. Tente novamente.\n");
                }
                else {
                    for (int i = 0; i < (sizeof(pessoas) / sizeof(pessoas[0])); i++) {
                        if (ID == pessoas[i].ID) {
                            if (strcmp(buffer, pessoas[i].nome) != 0) {
                                formatocorreto = false;
                                clear(20);
                                printf("%s nao encontrado. Tente novamente.\n", nome_da_gestao_singular);
                                break;
                            }
                            break;
                        }
                        else {
                            if (pessoas[i].ID == 0) {
                                clear(20);
                                printf("%s nao encontrado. Tente novamente.\n", nome_da_gestao_singular);
                                formatocorreto = false;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

        //Excluir a partir de um ID
    else {
        clear(20);
        for (int i = 0; i < (sizeof(pessoas) / sizeof(pessoas[0])); i++) {

            //quando chegar em um ID inválido, quer dizer que acabou a lista de pessoas e o programa sai do loop
            if (pessoas[i].ID == 0) {
                break;
            }

            //mostrar as informações apenas dos sujeitos com o mesmo ID
            if (ID == pessoas[i].ID) {
                mesmonome++;
                printf("\n");
                printf("ID: %d\n", pessoas[i].ID);
                printf("nome: %s\n", pessoas[i].nome);
                printf("Data de nascimento: %d/%d/%d\n", pessoas[i].nascimento.dia, pessoas[i].nascimento.mes, pessoas[i].nascimento.ano);
                break;
            }
        }
        if (mesmonome == 1) {
            printf("\nPressione Enter para continuar\n");
            readinput(buffer, 0);
        }
        else {
            printf("Nao existe %s com esse nome\n", nome_da_gestao_singular);
            printf("Pressione Enter para continuar\n");
            readinput(buffer, 0);
        }
    }
    if (mesmonome != 0) {
        FILE *f;

        //definir nome do arquivo
        char arquivo[19];
        for (int i = 0; i < 19; i++) {
            if (i < 3) {
                arquivo[i] = "../"[i];
            }
            if (i >= 3 && i < (3 + strlen(nome_da_gestao))) {
                arquivo[i] = nome_da_gestao[i-3];
            }
            if (i >= (3 + strlen(nome_da_gestao))) {
                arquivo[i] = ".bin"[i-(3 + strlen(nome_da_gestao))];
            }
        }
        f = fopen(arquivo, "wb");
        for (int i = 0; pessoas[i].ID != 0; i++) {
            if (pessoas[i].ID != ID) {
                fwrite(&pessoas[i], sizeof(pessoas[i]), 1, f);
            }
        }
        fclose(f);
        clear(20);
        printf("%s excluido com sucesso!\n", nome_da_gestao_singular);
        printf("Pressione Enter para continuar\n");
        readinput(buffer, 0);
    }
}

#endif //PROJETO_ESCOLA_GERENFUNC_H