#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 5

typedef struct {
    char usuario[20];
    char contrasena[20];
    float saldo;
} Usuario;

Usuario usuarios[MAX_USUARIOS] = {
    {"juan",   "1234",   5000.00},
    {"maria",  "abcd",   8500.50},
    {"carlos", "pass1",  3200.75},
    {"ana",    "qwerty", 12000.00},
    {"pedro",  "pedro1", 750.25}
};

int main() {
    printf("Sistema Cajero Automatico - En construccion\n");
    return 0;
}
