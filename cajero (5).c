#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 5
#define MAX_INTENTOS 3
#define MAX_HISTORIAL 20

typedef struct {
    char descripcion[60];
} Transaccion;

typedef struct {
    char usuario[20];
    char contrasena[20];
    float saldo;
    int bloqueado;
    Transaccion historial[MAX_HISTORIAL];
    int numTransacciones;
} Usuario;

Usuario usuarios[MAX_USUARIOS] = {
    {"juan",   "1234",   5000.00,  0, {}, 0},
    {"maria",  "abcd",   8500.50,  0, {}, 0},
    {"carlos", "pass1",  3200.75,  0, {}, 0},
    {"ana",    "qwerty", 12000.00, 0, {}, 0},
    {"pedro",  "pedro1", 750.25,   0, {}, 0}
};

/* Agrega un movimiento al historial del usuario */
void agregarHistorial(Usuario *u, const char *texto) {
    if (u->numTransacciones < MAX_HISTORIAL) {
        strcpy(u->historial[u->numTransacciones].descripcion, texto);
        u->numTransacciones++;
    } else {
        int i;
        for (i = 0; i < MAX_HISTORIAL - 1; i++)
            strcpy(u->historial[i].descripcion, u->historial[i+1].descripcion);
        strcpy(u->historial[MAX_HISTORIAL-1].descripcion, texto);
    }
}

int buscarUsuario(const char *nombre) {
    int i;
    for (i = 0; i < MAX_USUARIOS; i++)
        if (strcmp(usuarios[i].usuario, nombre) == 0) return i;
    return -1;
}

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
        if (usuarios[idx].bloqueado) { printf("  [!] Cuenta bloqueada.\n"); return -1; }
        printf("Contrasena: ");
        scanf("%s", claveIngresada);
        if (strcmp(usuarios[idx].contrasena, claveIngresada) == 0) {
            printf("\n  Bienvenido/a, %s!\n", usuarios[idx].usuario);
            return idx;
        } else {
            intentos++;
            printf("  [!] Contrasena incorrecta. Intentos restantes: %d\n", MAX_INTENTOS - intentos);
        }
    }
    int idx = buscarUsuario(nombreIngresado);
    if (idx != -1) usuarios[idx].bloqueado = 1;
    printf("\n  [!] Cuenta bloqueada por exceso de intentos.\n");
    return -1;
}

void consultarSaldo(Usuario *u) {
    printf("\n  Saldo disponible: RD$ %.2f\n", u->saldo);
}

void depositar(Usuario *u) {
    float monto;
    printf("\n  Monto a depositar: RD$ ");
    scanf("%f", &monto);
    if (monto <= 0) { printf("  [!] Monto invalido.\n"); return; }
    u->saldo += monto;
    printf("  Deposito exitoso. Nuevo saldo: RD$ %.2f\n", u->saldo);
    char reg[60];
    sprintf(reg, "Deposito: +RD$ %.2f | Saldo: RD$ %.2f", monto, u->saldo);
    agregarHistorial(u, reg);
}

void retirar(Usuario *u) {
    float monto;
    printf("\n  Monto a retirar: RD$ ");
    scanf("%f", &monto);
    if (monto <= 0) { printf("  [!] Monto invalido.\n"); return; }
    if (monto > u->saldo) { printf("  [!] Fondos insuficientes. Saldo: RD$ %.2f\n", u->saldo); return; }
    u->saldo -= monto;
    printf("  Retiro exitoso. Nuevo saldo: RD$ %.2f\n", u->saldo);
    char reg[60];
    sprintf(reg, "Retiro:   -RD$ %.2f | Saldo: RD$ %.2f", monto, u->saldo);
    agregarHistorial(u, reg);
}

/* Muestra los ultimos movimientos del usuario */
void verHistorial(Usuario *u) {
    printf("\n  --- Historial de transacciones ---\n");
    if (u->numTransacciones == 0) { printf("  No hay movimientos registrados.\n"); return; }
    int i;
    for (i = 0; i < u->numTransacciones; i++)
        printf("  %d. %s\n", i+1, u->historial[i].descripcion);
    printf("  ----------------------------------\n");
}

void mostrarMenu() {
    printf("\n========================================\n");
    printf("            MENU PRINCIPAL              \n");
    printf("========================================\n");
    printf("  1. Consultar saldo\n");
    printf("  2. Depositar\n");
    printf("  3. Retirar\n");
    printf("  4. Ver historial de transacciones\n");
    printf("  5. Cambiar contrasena\n");
    printf("  6. Transferir a otro usuario\n");
    printf("  7. Salir\n");
    printf("========================================\n");
    printf("  Seleccione una opcion: ");
}

int main() {
    int idx = autenticar();
    if (idx == -1) { printf("\n  Acceso denegado.\n"); return 1; }

    Usuario *u = &usuarios[idx];
    int opcion;
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: consultarSaldo(u); break;
            case 2: depositar(u); break;
            case 3: retirar(u); break;
            case 4: verHistorial(u); break;
            case 5: printf("\n  [Cambiar contrasena - proximamente]\n"); break;
            case 6: printf("\n  [Transferir - proximamente]\n"); break;
            case 7: printf("\n  Hasta luego!\n"); break;
            default: printf("\n  [!] Opcion invalida.\n");
        }
    } while (opcion != 7);

    return 0;
}
