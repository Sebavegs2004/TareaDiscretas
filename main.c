#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int **grafo;
int *visitado;
int V;

void DFS(int v) {
    visitado[v] = 1;
    for (int i = 0; i < V; i++) {
        if (grafo[v][i] == 1 && !visitado[i]) {
            DFS(i);
        }
    }
}

int esConexo() {
    for (int i = 0; i < V; i++) {
        visitado[i] = 0;
    }
    DFS(0);

    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE *file = fopen("grafo.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    char linea[256];
    if (fgets(linea, sizeof(linea), file) != NULL) {
        linea[strcspn(linea, "\n")] = '\0';
        V = atoi(linea);
    }

    grafo = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        grafo[i] = (int *)malloc(V * sizeof(int));
    }
    visitado = (int *)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            grafo[i][j] = 0;
        }
    }

    int fila = 0;
    while (fgets(linea, sizeof(linea), file) != NULL && fila < V) {
        for (int x = 2; x < strlen(linea); x++) {
            if (isdigit(linea[x]) && (atoi(&linea[x]) <= V)) {
                grafo[fila][atoi(&linea[x]) - 1] = 1;
            }
        }
        fila += 1;
    }
    fclose(file);

    printf("Matriz de adyacencia:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }

    if (esConexo()) {
        printf("El grafo es conexo\n");
    } else {
        printf("El grafo no es conexo\n");
    }

    for (int i = 0; i < V; i++) {
        free(grafo[i]);
    }
    free(grafo);
    free(visitado);

    return 0;
}
