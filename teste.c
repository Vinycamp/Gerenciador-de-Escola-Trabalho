#include <stdio.h>
#include <string.h>

int char_in_string(char string[], char c) {
    for (int i = 0; i < strlen(string); i++) {
        if (c == string[i]) {
            return 1;
        }
    }
    return 0;
}

void main() {
    char data[10] = "12/12/12/1";
    char teste[] = "abcde";
    char numeros[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    if (char_in_string(numeros, data[8]) == 0) {
        printf(" Numero incorreto");
    }
}