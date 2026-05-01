#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 5
#define MAX_INTENTOS 3

typedef struct {
    char usuario[20];
    char contrasena[20];
    float saldo;
    int bloqueado;
} Usuario;

Usuario usuarios[MAX_USUARIOS] = {
    {"juan",   "1234",   5000.00,  0},
    {"maria",  "abcd",   8500.50,  0},
    {"carlos", "pass1",  3200.75,  0},
    {"ana",    "qwerty", 12000.00, 0},
    {"pedro",  "pedro1", 750.25,   0}
};

/* Busca un usuario por nombre y devuelve su indice o -1 si no existe */
int buscarUsuario(const char *nombre) {
    int i;
    for (i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuarios[i].usuario, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

/* Solicita credenciales y valida el acceso */
int autenticar() {
    char nombreIngresado[20];
    char claveIngresada[20];
    int intentos = 0;

    printf("\n========================================\n");
    printf("       CAJERO AUTOMATICO DIGITAL        \n");
    printf("========================================\n");

    while (intentos < MAX_INTENTOS) {
        printf("\nUsuario: ");
        scanf("%s", nombreIngresado);

        int idx = buscarUsuario(nombreIngresado);

        if (idx == -1) {
            printf("  [!] Usuario no encontrado.\n");
            intentos++;
            printf("  Intentos restantes: %d\n", MAX_INTENTOS - intentos);
            continue;
        }

        if (usuarios[idx].bloqueado) {
            printf("  [!] Cuenta bloqueada.\n");
            return -1;
        }

        printf("Contrasena: ");
        scanf("%s", claveIngresada);

        if (strcmp(usuarios[idx].contrasena, claveIngresada) == 0) {
            printf("\n  Bienvenido/a, %s!\n", usuarios[idx].usuario);
            return idx;
        } else {
            intentos++;
            printf("  [!] Contrasena incorrecta. Intentos restantes: %d\n",
                   MAX_INTENTOS - intentos);
        }
    }

    int idx = buscarUsuario(nombreIngresado);
    if (idx != -1) {
        usuarios[idx].bloqueado = 1;
        printf("\n  [!] Cuenta bloqueada por exceso de intentos.\n");
    }
    return -1;
}

int main() {
    int idx = autenticar();
    if (idx == -1) {
        printf("\n  Acceso denegado.\n");
        return 1;
    }
    printf("\n  Login exitoso!\n");
    return 0;
}
