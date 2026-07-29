#include <stdio.h>

int contar_divisores(int numero) {
    int cantidad = 0;

    for (int divisor = 1; divisor <= numero; divisor++) {
        if (numero % divisor == 0) {
            cantidad++;
        }
    }

    return cantidad;
}

int main(void) {
    int numeros[15] = {0};

    // Ingreso de los 15 numeros enteros positivos.
    for (int i = 0; i < 15; i++) {
        printf("Ingrese el numero %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    printf("\nEl arreglo es:\n");
    for (int i = 0; i < 15; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n\nResultados:\n");

    for (int i = 0; i < 15; i++) {
        int numero = numeros[i];
        int cantidad = contar_divisores(numero);

        printf("%d -> %d divisor", numero, cantidad);
        if (cantidad != 1) {
            printf("es");
        }

        if (numero == 1) {
            printf(" -> No es primo ni compuesto\n");
        } else if (cantidad == 2) {
            printf(" -> Primo\n");
        } else if (cantidad == 4) {
            printf(" -> Semiprimo\n");
        } else if (cantidad > 2) {
            printf(" -> Compuesto\n");
        }
    }

    return 0;
}
