#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

void clear(int n){
    for(int i = 0;i < n;i++){
        printf("\n");
    }
}

void ler_estudantes(int quantidade_de_estudantes, struct estudante *estudantes) {
    FILE *f;
    for (int i = 0; i < quantidade_de_estudantes; i++) {
        estudantes[i].ID = 0;
        for (int i2 = 0; i2 < 100; i2++) {
            estudantes[i].nome[i2] = 0;
        }
        estudantes[i].nascimento.dia = 0;
        estudantes[i].nascimento.mes = 0;
        estudantes[i].nascimento.ano = 0;
    }
    f = fopen("../estudantes.bin", "rb");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
    }
    fread(estudantes, sizeof(struct estudante), 100, f);
    fclose(f);
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

void cadastrar(int quantidade_de_estudantes) {
    struct estudante estudante_cadastrado;
    struct estudante estudantes[quantidade_de_estudantes];
    ler_estudantes(quantidade_de_estudantes, estudantes);
    clear(20);
    //definir o ID do novo estudante
    int i;
    for (i = 0; i < quantidade_de_estudantes; i++) {
        if (estudantes[i].ID == 0) {
            break;
        }
    }
    int novoid;
    if (i == 0) {
        novoid = 1;
    } else novoid = estudantes[i-1].ID+1;
    estudante_cadastrado.ID = novoid;

    //pedir o nome do novo estudante
    char buffer[100];
    printf("\nDigite o nome do Estudante que deseja cadastrar:\n");
    fgets(buffer, sizeof(buffer), stdin);
    for (i = 0; i < strlen(buffer)-1; i++) {
        estudante_cadastrado.nome[i] = buffer[i];
    }

    //pedir a data de nascimento do novo estudante
    bool formatocorreto = false;
    char data[11];
    while (formatocorreto == false) {
        data[0] = '\0';
        printf("Digite a data de nascimento do Estudante no formato DD/MM/AAAA:\n");
        fgets(data, sizeof(data), stdin);
        formatocorreto = true;
        i = 0;
        //passa por toda a string e vê se cada caractere está no formato correto
        while (i < 10) {
            //olha as barras
            if (i == 2 || i == 5) {
                if (data[i] != '/') {
                    formatocorreto = false;
                    break;
                }
            }
            //olha os números
            else {
                if (char_is_number(data[i]) == 0) {
                    formatocorreto = false;
                    break;
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
    estudante_cadastrado.nascimento.dia = dia;
    estudante_cadastrado.nascimento.mes = mes;
    estudante_cadastrado.nascimento.ano = ano;

    //imprime o ID do estudante e salva no arquivo
    printf("\nEstudante cadastrado no ID: %d\n", estudante_cadastrado.ID);
    buffer[0] = '\0';
    printf("Pressione Enter para continuar\n");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Aqui você pode processar a entrada, se necessário
        printf("Voce pressionou Enter.\n");
    } else {
        printf("Erro ao ler a entrada.\n");
    }
    FILE *f;
    f = fopen("../estudantes.bin", "ab");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
    }
    fwrite(&estudante_cadastrado, sizeof(estudante_cadastrado), 1, f);
    fclose(f);
}

void consultar(int quantidade_de_estudantes) {
    char buffer[100];
    int input;
    struct estudante estudantes[quantidade_de_estudantes];
    struct estudante *ponteiro_estudantes;
    ler_estudantes(quantidade_de_estudantes, ponteiro_estudantes);
    clear(20);
    printf("Digite o ID ou o nome do Estudante que deseja consultar:\n");
    fgets(buffer, sizeof(buffer), stdin);
    //consultar a partir de um nome
    if (sscanf(buffer, "%d", &input) != 1) {
        for (int i = 0; i < (sizeof(estudantes) / sizeof(estudantes[0])); i++) {
            //quando chegar em um ID inválido, quer dizer que acabou a lista de estudantes e o programa sai do loop
            if (estudantes[i].ID == 0) {
                break;
            }

            //mostrar as informações apenas do estudante com o mesmo nome
            if (!strcmp(buffer, estudantes[i].nome)) {
                clear(20);
                printf("ID: %d\n", estudantes[i].ID);
                printf("nome: %s\n", estudantes[i].nome);
                printf("Data de nascimento: %d/%d/%d\n", estudantes[i].nascimento.dia,
                       estudantes[i].nascimento.mes, estudantes[i].nascimento.ano);
                printf("\nPressione Enter para continuar\n");
                fgets(buffer, sizeof(buffer), stdin);
                break;
            }
        }
    }
        //Consultar a partir de um ID
    else {
        for (int i = 0; i < (sizeof(estudantes) / sizeof(estudantes[0])); i++) {
            //quando chegar em um ID inválido, quer dizer que acabou a lista de estudantes e o programa sai do loop
            if (estudantes[i].ID == 0) {
                break;
            }

            //mostrar as informações apenas do estudante com o mesmo ID
            if (input == estudantes[i].ID) {
                clear(20);
                printf("ID: %d\n", estudantes[i].ID);
                printf("nome: %s\n", estudantes[i].nome);
                printf("Data de nascimento: %d/%d/%d\n", estudantes[i].nascimento.dia,
                       estudantes[i].nascimento.mes, estudantes[i].nascimento.ano);
                printf("\nPressione Enter para continuar\n");
                fgets(buffer, sizeof(buffer), stdin);
                break;
            }
        }
    }
}

void atualizar(int quantidade_de_estudantes) {
    char buffer[100];
    int input;
    char nome_atualizado[100];
    int data_atualizada;
    struct estudante estu_atualizado;
    struct estudante estudantes[quantidade_de_estudantes];
    struct estudante *ponteiro_estudantes;
    ler_estudantes(quantidade_de_estudantes, ponteiro_estudantes);
    FILE *f;
    clear(20);
    printf("Digite o ID ou o nome do Estudante que deseja atualizar:\n");
    fgets(buffer, sizeof(buffer), stdin);
    //atualizar a partir de um nome
    if (sscanf(buffer, "%d", &input) != 1) {
        f = fopen("../estudantes.bin", "wb");
        //passar por cada estudante
        for (int i = 0; i < quantidade_de_estudantes; i++) {
            //quando chegar em um ID inválido, quer dizer que acabou a lista de estudantes e o programa sai do loop
            if (estudantes[i].ID == 0) {
                break;
            }

            //escrever no arquivo as informações dos estudantes com nomes diferente do escolhido
            if (strcmp(buffer, estudantes[i].nome) != 0) {
                fwrite(&estudantes[i], sizeof(estudantes[i]), 1, f);
            }

                //escrever no arquivo as novas informações do estudante com o nome escolhido
            else {
                //atualizar o nome do estudante
                printf("\nDigite o nome atualizado (deixe em branco para nao mudar!):\n");
                fgets(estu_atualizado.nome, sizeof(estu_atualizado.nome), stdin);

                //caso o usuário deixar em branco, não atualizar
                if (!strcmp(estu_atualizado.nome, "")) {
                    for (int i2 = 0; i2 < strlen(estudantes[i].nome); i2++) {
                        estu_atualizado.nome[i2] = estudantes[i].nome[i2];
                    }
                }

                //atualizar a data de nascimento do estudante
                bool formatocorreto = false;
                char data[10];
                char numeros[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
                while (formatocorreto == false) {
                    printf("\nDigite a data de nascimento atualizada (deixe em branco para nao mudar!):\n");
                    fgets(data, sizeof(data), stdin);
                    formatocorreto = true;
                    i = 0;

                    //caso o usuário deixar em branco, não atualizar
                    if (!strcmp(estu_atualizado.nome, "")) {
                        estu_atualizado.nascimento.dia = estudantes[i].nascimento.dia;
                        estu_atualizado.nascimento.mes = estudantes[i].nascimento.mes;
                        estu_atualizado.nascimento.ano = estudantes[i].nascimento.ano;
                        break;
                    }

                    //passa por toda a string e vê se cada caractere está no formato correto
                    while (i < 10) {
                        //olha as barras
                        if (i == 2 || i == 5) {
                            if (data[i] != '/') {
                                formatocorreto = false;
                                break;
                            }
                        }
                            //olha os números
                        else if (!strchr(numeros, data[i])) {
                            formatocorreto = false;
                            break;
                        }
                        i++;
                    }
                    if (formatocorreto == false) {
                        clear(20);
                        printf("Formato incorreto. Tente novamente.\n\n");
                    }
                }

                //caso o usuário deixar em branco, não atualizar
                if (strcmp(estu_atualizado.nome, "")) {
                    break;
                }

                    //caso o usuário NÃO deixar em branco, atualizar
                else {
                    int dia, mes, ano;
                    int *d, *m, *a;
                    transformar_data_em_inteiro(data, d, m, a);
                    estu_atualizado.nascimento.dia = dia;
                    estu_atualizado.nascimento.mes = mes;
                    estu_atualizado.nascimento.ano = ano;
                    fwrite(&estu_atualizado, sizeof(estudantes[i]), 1, f);
                }
            }
        }
        fclose(f);
    }
        //Atualizar a partir de um ID
    else {
        f = fopen("../estudantes.bin", "wb");
        //passar por cada estudante
        for (int i = 0; i < quantidade_de_estudantes; i++) {
            //quando chegar em um ID inválido, quer dizer que acabou a lista de estudantes e o programa sai do loop
            if (estudantes[i].ID == 0) {
                break;
            }

            //escrever no arquivo as informações dos estudantes com nomes diferente do escolhido
            if (input != estudantes[i].ID) {
                fwrite(&estudantes[i], sizeof(estudantes[i]), 1, f);
            }

                //escrever no arquivo as novas informações do estudante com o nome escolhido
            else {
                //atualizar o nome do estudante
                printf("\nDigite o nome atualizado (deixe em branco para nao mudar!):\n");
                fgets(estu_atualizado.nome, sizeof(estu_atualizado.nome), stdin);

                //caso o usuário deixar em branco, não atualizar
                if (!strcmp(estu_atualizado.nome, "")) {
                    for (int i2 = 0; i2 < strlen(estudantes[i].nome); i2++) {
                        estu_atualizado.nome[i2] = estudantes[i].nome[i2];
                    }
                }

                //atualizar a data de nascimento do estudante
                bool formatocorreto = false;
                char data[10];
                char numeros[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
                while (formatocorreto == false) {
                    printf("\nDigite a data de nascimento atualizada (deixe em branco para nao mudar!):\n");
                    fgets(data, sizeof(data), stdin);
                    formatocorreto = true;
                    i = 0;

                    //caso o usuário deixar em branco, não atualizar
                    if (!strcmp(estu_atualizado.nome, "")) {
                        estu_atualizado.nascimento.dia = estudantes[i].nascimento.dia;
                        estu_atualizado.nascimento.mes = estudantes[i].nascimento.mes;
                        estu_atualizado.nascimento.ano = estudantes[i].nascimento.ano;
                        break;
                    }

                    //passa por toda a string e vê se cada caractere está no formato correto
                    while (i < 10) {
                        //olha as barras
                        if (i == 2 || i == 5) {
                            if (data[i] != '/') {
                                formatocorreto = false;
                                break;
                            }
                        }
                            //olha os números
                        else if (!strchr(numeros, data[i])) {
                            formatocorreto = false;
                            break;
                        }
                        i++;
                    }
                    if (formatocorreto == false) {
                        clear(20);
                        printf("Formato incorreto. Tente novamente.\n\n");
                    }
                }

                //caso o usuário deixar em branco, não atualizar
                if (strcmp(estu_atualizado.nome, "")) {
                    break;
                }

                    //caso o usuário NÃO deixar em branco, atualizar
                else {
                    int dia, mes, ano;
                    int *d, *m, *a;
                    transformar_data_em_inteiro(data, d, m, a);
                    estu_atualizado.nascimento.dia = dia;
                    estu_atualizado.nascimento.mes = mes;
                    estu_atualizado.nascimento.ano = ano;
                    fwrite(&estu_atualizado, sizeof(estudantes[i]), 1, f);
                }
            }
        }
        fclose(f);
    }
}

void excluir(int quantidade_de_estudantes) {
    char buffer[100];
    int input;
    FILE *f;
    struct estudante estudantes[quantidade_de_estudantes];
    struct estudante *ponteiro_estudantes;
    ler_estudantes(quantidade_de_estudantes, ponteiro_estudantes);
    clear(20);
    printf("Digite o nome do Estudante que deseja excluir:\n");
    fgets(buffer, sizeof(buffer), stdin);
    //atualizar a partir de um nome
    if (sscanf(buffer, "%d", &input) != 1) {
        f = fopen("../estudantes.bin", "wb");
        for (int i = 0; i < quantidade_de_estudantes; i++) {
            if (estudantes[i].ID == 0) {
                break;
            }
            if (strcmp(buffer, estudantes[i].nome)) {
                fwrite(&estudantes[i], sizeof(estudantes[i]), 1, f);
            }
        }
        fclose(f);
        clear(20);
        printf("%s excluido com sucesso!\n", buffer);
        printf("Pressione Enter para continuar\n");
        fgets(buffer, sizeof(buffer), stdin);
    }
    else {
        f = fopen("../estudantes.bin", "wb");
        for (int i = 0; i < quantidade_de_estudantes; i++) {
            if (estudantes[i].ID == 0) {
                break;
            }
            if (input != estudantes[i].ID) {
                fwrite(&estudantes[i], sizeof(estudantes[i]), 1, f);
            }
        }
        fclose(f);
        clear(20);
        printf("%s excluido com sucesso!\n", buffer);
        printf("Pressione Enter para continuar\n");
        fgets(buffer, sizeof(buffer), stdin);
    }
}

void gestao_estudantes(){
    char buffer[100];
    int input;
    int opcaoinvalida = 0;
    while (1) {
        clear(20);
        if (opcaoinvalida == 0) {
            printf("Gestao de Estudantes!\n");
        }
        else {
            printf("Voce digitou uma opcao invalida.\n");
        }
        printf("Digite o numero correspondente a opcao que deseja:\n");
        printf("\n");
        printf("(1) Cadastrar Estudante   (2) Consultar Estudante\n");
        printf("(3) Atualizar Estudante   (4) Excluir Estudante\n");
        printf("(5) Sair da Gestao\n");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &input) != 1 || input > 5 || input < 1) {
            opcaoinvalida = 1;
        }

        // Definições de variáveis para o switch
        int quantidade_de_estudantes = 100;


        switch (input) {
            case 1:
                cadastrar(quantidade_de_estudantes);
                break;
            case 2:
                consultar(quantidade_de_estudantes);
                break;
            case 3:
                atualizar(quantidade_de_estudantes);
                break;
            case 4:
                excluir(quantidade_de_estudantes);
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
        switch (input){
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
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer,"%d", &input) != 1 || input > 5 || input < 1) {
            opcaoinvalida = 1;
        }
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