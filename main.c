#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int **grafo;
int *visitado;
int V;

void DFS(int v) {
    printf("\nDFS v = %d \n", v + 1);
    visitado[v] = 1;
    for (int i = 0; i < V; i++) {
        printf("matriz[%d][%d] = ", v, i);
        printf("%d\n", grafo[v][i]);
        for (int i = 0; i < V; i++) {
            printf("%d ", visitado[i]);
        }
        printf("\n");
        if (grafo[v][i] == 1 && !visitado[i]) {
            DFS(i);
        }
    }
}

void ResetVisitados(){
    for (int i = 0; i < V; i++) {
        visitado[i] = 0;
    }
}

char *esConexo() {
    for(int r = 0; r < V; r++){
        if(visitado[r] == 0){
            DFS(r);
            break;
        }
    }
    printf("\n");
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            ResetVisitados();
            printf("----------------fin dfs -------------------------------\n");
            return "no";
        }
    }
    ResetVisitados();
    printf("----------------fin dfs -------------------------------\n");
    return "si";
}

int main() {
    FILE *file = fopen("grafo.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    char linea[256] , k1[] = "si", k2[] = "si", k3[] = "si", k4[] = "si", Conex[] = "Si";
    if (fgets(linea, sizeof(linea), file) != NULL) {
        linea[strcspn(linea, "\n")] = '\0';
        V = atoi(linea);
    }

    grafo = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        grafo[i] = (int *)malloc(V * sizeof(int));
    }
    visitado = (int *)malloc(V * sizeof(int));

    ResetVisitados(); 

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            grafo[i][j] = 0;
        }
    }

    int fila = 0, GradMax = 0, GradMin = 0, Grad = 0;

    while (fgets(linea, sizeof(linea), file) != NULL && fila < V) {
        for (int x = 2; x < strlen(linea); x++) {
            if (isdigit(linea[x]) && (atoi(&linea[x]) <= V)) {
                grafo[fila][atoi(&linea[x]) - 1] = 1;
                Grad += 1;
            }
        }
        if(Grad > GradMax){
            GradMax = Grad;
            if(fila == 0){
                GradMin = Grad;
            }
        }
        if(Grad < GradMin){
            GradMin = Grad;
        }
        Grad = 0;
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


    if(strcmp(k1, "si") == 0){
        strcpy(k1, esConexo(0));
        ResetVisitados();
        strcpy(Conex, esConexo(0));
        ResetVisitados();
    }

    for (int i = 0; i < V; i++) {
        printf("%d ", visitado[i]);
    }
    printf("\n");

    printf("\n");
    for(int i = 0; i < V; i++){
        visitado[i] = 1;
        if(strcmp(k2, "si") == 0){
            printf("Test 2-Conexidad\nVertices quitados q%d", i + 1);
            strcpy(k2, esConexo());
        }
        for(int j = 0; j < V; j++){
            if (j != i && V > 2){
                visitado[i] = 1;
                visitado[j] = 1;
                if(strcmp(k3, "si") == 0){
                    printf("Test 3-Conexidad\nVertices quitados q%d q%d", i + 1, j + 1);
                    strcpy(k3, esConexo());
                } 
                for(int k = 0; k < V; k++){
                    if ( k != i && k != j && V > 3){
                        visitado[i] = 1;
                        visitado[j] = 1;
                        visitado[k] = 1;
                        if(strcmp(k4, "si") == 0){
                            printf("Test 4-Conexidad\nVertices quitados q%d q%d q%d", i + 1, j + 1, k + 1);
                            strcpy(k4, esConexo());
                        }
                        visitado[k] = 0;
                    }
                    else{
                        strcpy(k4, "no");
                    }
                }  
                visitado[j] = 0;
            }
            else{
                strcpy(k3, "no");
            }
        }
        visitado[i] = 0;
    } 

    printf("Grado Minimo = %d\nGrado Maximo = %d\n", GradMin, GradMax);
    printf("%s es Conexo\n", Conex);
    printf("%s es 1-Conexo\n", k1);
    printf("%s es 2-Conexo\n", k2);
    printf("%s es 3-Conexo\n", k3);
    printf("%s es 4-Conexo\n", k4);

    for (int i = 0; i < V; i++) {
        free(grafo[i]);
    }
    free(grafo);
    free(visitado);

    return 0;
}
