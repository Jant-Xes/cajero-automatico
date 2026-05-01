# Cajero Automático Digital

Sistema que simula el funcionamiento básico de un cajero automático, desarrollado en lenguaje C. Permite gestionar cuentas de usuarios registrados con operaciones bancarias comunes.

---

## Funcionalidades implementadas

- **Autenticación de usuarios**: acceso mediante usuario y contraseña
- **Consultar saldo**: visualización del saldo disponible
- **Depositar dinero**: ingreso de fondos a la cuenta
- **Retirar dinero**: extracción de fondos con validación de saldo suficiente
- **Salir del sistema**: cierre seguro de sesión

---

## Mejoras adicionales

### 1. Bloqueo tras 3 intentos fallidos
**Qué se agregó:** El sistema bloquea la cuenta automáticamente si el usuario ingresa credenciales incorrectas 3 veces seguidas.  
**Por qué:** Evita accesos no autorizados mediante fuerza bruta.  
**Cómo funciona:** Se lleva un contador de intentos fallidos. Al llegar a 3, la cuenta se marca como bloqueada y no permite más accesos.

### 2. Historial de transacciones
**Qué se agregó:** Registro de los últimos 20 movimientos de cada cuenta (depósitos, retiros, transferencias).  
**Por qué:** Permite al usuario revisar sus operaciones recientes, mejorando la transparencia del sistema.  
**Cómo funciona:** Cada operación exitosa guarda una descripción en un arreglo interno del usuario. Si se supera el límite de 20, se descarta el más antiguo.

### 3. Cambio de contraseña
**Qué se agregó:** Opción para que el usuario actualice su contraseña desde el menú principal.  
**Por qué:** Es una funcionalidad esencial de seguridad en cualquier sistema bancario.  
**Cómo funciona:** El sistema solicita la contraseña actual, luego la nueva y su confirmación. Solo actualiza si todos los datos son correctos.

### 4. Transferencia entre usuarios
**Qué se agregó:** Posibilidad de enviar dinero a otro usuario registrado en el sistema.  
**Por qué:** Amplía las funcionalidades del cajero acercándolo a un sistema bancario real.  
**Cómo funciona:** El usuario ingresa el nombre del destinatario y el monto. El sistema valida que el destinatario exista, que no sea el mismo usuario y que haya saldo suficiente. Luego actualiza ambos saldos y registra la operación en el historial de los dos usuarios.

---

## Usuarios de prueba

| Usuario | Contraseña | Saldo inicial |
|---------|-----------|---------------|
| juan    | 1234      | RD$ 5,000.00  |
| maria   | abcd      | RD$ 8,500.50  |
| carlos  | pass1     | RD$ 3,200.75  |
| ana     | qwerty    | RD$ 12,000.00 |
| pedro   | pedro1    | RD$ 750.25    |

---

## Instrucciones para compilar

### Requisitos
- Compilador GCC instalado (viene con MinGW en Windows)

### Compilar en Windows
```bash
gcc cajero.c -o cajero.exe
```

### Compilar en Linux / Mac
```bash
gcc cajero.c -o cajero
```

---

## Instrucciones para ejecutar

### En Windows
```bash
cajero.exe
```

### En Linux / Mac
```bash
./cajero
```

---

## Estructura del proyecto

```
cajero-automatico/
├── cajero.c       # Código fuente principal
└── README.md      # Documentación del proyecto
```
