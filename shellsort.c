#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Feito por Lucas Nascimento, 2/2/2022

static int ciura[20] = {1, 4, 10, 23, 57, 132, 301, 701, 1577, 3548, 7983, 17961, 40412, 90927, 204585, 460316, 1035711};

int main (int argc, char** argv) {
    FILE * input1;
    FILE * input2;
    FILE * output1;
    FILE * output2;
    char line[256];
    char *bigLine = (char*) malloc(sizeof(char)*10000000);

    int array1a[100];
    int array1b[100];
    int array1c[100];

    int *array2a = (int*) malloc(sizeof(int)*1000000);
    int *array2b = (int*) malloc(sizeof(int)*1000000);
    int *array2c = (int*) malloc(sizeof(int)*1000000);

    int arrayCounter;
    int arrayNumber;
    int arraySize;

    //Exercício 1

    input1 = fopen("entrada1.txt", "r");
    output1 = fopen("saida1.txt", "w");

    while(fgets(line, sizeof(line), input1)) {

        arrayNumber = strtok(line, " ");
        arraySize = atoi(arrayNumber);
        arrayCounter = 0;
        arrayNumber = strtok(NULL, " ");
        while(arrayNumber) {
            array1a[arrayCounter] = atoi(arrayNumber);
            array1b[arrayCounter] = atoi(arrayNumber);
            array1c[arrayCounter] = atoi(arrayNumber);
            arrayCounter++;
            arrayNumber = strtok(NULL, " ");
        }
        shellsortStepShell(array1a, arraySize, output1);
        shellsortStepKnuth(array1b, arraySize, output1);
        shellsortStepCiura(array1c, arraySize, output1);
    }

    fclose(output1);
    fclose(input1);

    //Exercício 2

    input2 = fopen("entrada2.txt", "r");
    output2 = fopen("saida2.txt", "w");

    while(fgets(bigLine, 10000000, input2)) {
        arrayNumber = strtok(bigLine, " ");
        arraySize = atoi(arrayNumber);
        arrayCounter = 0;
        arrayNumber = strtok(NULL, " ");
        while(arrayNumber) {
            array2a[arrayCounter] = atoi(arrayNumber);
            array2b[arrayCounter] = atoi(arrayNumber);
            array2c[arrayCounter] = atoi(arrayNumber);
            arrayCounter++;
            arrayNumber = strtok(NULL, " ");
        }
        shellsortTimeShell(array2a, arraySize, output2);
        shellsortTimeKnuth(array2b, arraySize, output2);
        shellsortTimeCiura(array2c, arraySize, output2);
    }

    fclose(output2);
    fclose(input2);

    printf("Arquivo gerado com sucesso. \nAperte qualquer tecla para continuar.");
    getchar();

}

void printArray(int *dados, int size, FILE *output) {
    for(int i=0; i<size; i++){
        fprintf(output, "%d ", dados[i]);
    }
}

void shellsortStepShell(int *dados, int size, FILE *output) {
    int i, j, h, aux;
    h = 1;
    printArray(dados, size, output);
    fprintf(output, "SEQ-SHELL\n");
    while (h < size) {
        h = h * 2;
    }
    while (h > 1) {
        h /= 2;
        for (i=h; i<size; i++) {
            aux = dados[i];
            j = i - h;
            while (j>= 0 && aux < dados[j]) {
                dados[j + h] = dados[j];
                j -= h;
            }
            dados[j + h] = aux;
        }
        printArray(dados, size, output);
        fprintf(output, "INCR-%d: ", h);
        fprintf(output, "\n");
    }
    fprintf(output, "\n");
}

void shellsortStepKnuth(int *dados, int size, FILE *output) {
    int i, j, h, aux;
    h = 1;
    printArray(dados, size, output);
    fprintf(output, "SEQ-KNUTH\n");
    while (h < size) {
        h = 3 * h + 1;
    }
    while (h > 1) {
        h /= 3;
        for (i=h; i<size; i++) {
            aux = dados[i];
            j = i - h;
            while (j>= 0 && aux < dados[j]) {
                dados[j + h] = dados[j];
                j -= h;
            }
            dados[j + h] = aux;
        }
        printArray(dados, size, output);
        fprintf(output, "INCR-%d: ", h);
        fprintf(output, "\n");
    }
    fprintf(output, "\n");
}

void shellsortStepCiura(int *dados, int size, FILE *output) {

    int i, j, h, aux;
    int ciuraIndex = 0;
    h = 1;
    printArray(dados, size, output);
    fprintf(output, "SEQ-CIURA\n");
    while (h < size && size > ciura[ciuraIndex]) {
        h = ciura[ciuraIndex];
        ciuraIndex++;
    }
    while (h > 1) {
        ciuraIndex--;
        h = ciura[ciuraIndex];
        for (i=h; i<size; i++) {
            aux = dados[i];
            j = i - h;
            while (j>= 0 && aux < dados[j]) {
                dados[j + h] = dados[j];
                j -= h;
            }
            dados[j + h] = aux;
        }
        printArray(dados, size, output);
        fprintf(output, "INCR-%d: ", h);
        fprintf(output, "\n");
    }
    fprintf(output, "\n");
}

void shellsortTimeShell(int *dados, int size, FILE *output) {
    clock_t start, end;
    int i, j, h, aux;
    h = 1;
    start = clock();
    while (h < size) {
        h = h * 2;
    }
    while (h > 1) {
        h /= 2;
        for (i=h; i<size; i++) {
            aux = dados[i];
            j = i - h;
            while (j>= 0 && aux < dados[j]) {
                dados[j + h] = dados[j];
                j -= h;
            }
            dados[j + h] = aux;
        }
    }
    end = clock();
    float executionTime = (float) (end - start) / CLOCKS_PER_SEC;
    fprintf(output, "SHELL, %d, %.6f\n", size, executionTime);
}

void shellsortTimeKnuth(int *dados, int size, FILE *output) {
    clock_t start, end;
    int i, j, h, aux;
    h = 1;
    start = clock();
    while (h < size) {
        h = 3 * h + 1;
    }
    while (h > 1) {
        h /= 3;
        for (i=h; i<size; i++) {
            aux = dados[i];
            j = i - h;
            while (j>= 0 && aux < dados[j]) {
                dados[j + h] = dados[j];
                j -= h;
            }
            dados[j + h] = aux;
        }
    }
    end = clock();
    float executionTime = (float) (end - start) / CLOCKS_PER_SEC;
    fprintf(output, "KNUTH, %d, %.6f\n", size, executionTime);
}

void shellsortTimeCiura(int *dados, int size, FILE *output) {
    clock_t start, end;
    int i, j, h, aux;
    int ciuraIndex = 0;
    h = 1;
    start = clock();
    while (h < size && size > ciura[ciuraIndex]) {
        h = ciura[ciuraIndex];
        ciuraIndex++;
    }
    while (h > 1) {
        ciuraIndex--;
        h = ciura[ciuraIndex];
        for (i=h; i<size; i++) {
            aux = dados[i];
            j = i - h;
            while (j>= 0 && aux < dados[j]) {
                dados[j + h] = dados[j];
                j -= h;
            }
            dados[j + h] = aux;
        }
    }
    end = clock();
    float executionTime = (float) (end - start) / CLOCKS_PER_SEC;
    fprintf(output, "CIURA, %d, %.6f\n", size, executionTime);
}
