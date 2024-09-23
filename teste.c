#include <stdio.h>

int main() {
    while(1) {
        int input;
        printf("Digite um numero (ou pressione Enter para sair): ");

        // Lê uma linha inteira
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || buffer[0] == '\n') {
            break; // Sai do loop se apenas Enter foi pressionado
        }

        printf("%s", buffer);
        // Tenta converter a entrada para um inteiro
        if (sscanf(buffer, "%d", &input) == 1) {
            printf("Voce digitou: %d\n", input);
        } else {
            printf("Entrada invalida. Tente novamente.\n", input);
        }
    }
    return 0;
}