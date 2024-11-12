#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int **grafo;
int *visitado;
int V;
char k1[] = "si", k2[] = "si", k3[] = "si", k4[] = "si", Conex[] = "si";

void DFS(int v) {
    visitado[v] = 1;
    for (int i = 0; i < V; i++) {
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
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            ResetVisitados();
            return "no";
        }
    }
    ResetVisitados();
    return "si";
}

int main() {
    char linea[256] , nombre_archivo[100];
    int Opcion;
    while(1){
        printf("Que desea hacer\n[1] Cargar Grafo\n[2] Salir\n");
        scanf("%d", &Opcion);
        if (Opcion == 2){
            exit(0);
        }
        if(Opcion == 1){
            int fila = 0, GradMax = 0, GradMin = 0, Grad = 0;
            printf("Ingrese el nombre del archivo = ");
            scanf(" %[^\n]", nombre_archivo); 
            FILE *file = fopen(nombre_archivo, "r");
            if (file == NULL) {
                printf("Error al abrir el archivo o no existe.\n");
                return 1;
            }

            printf("\n\n------------------------------ %s ------------------------------\n", nombre_archivo);

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

            while (fgets(linea, sizeof(linea), file) != NULL && fila < V) {
                char *token = strtok(strchr(linea, ' '), ", ");
                while(token != NULL){
                    grafo[fila][atoi(token) - 1] = 1;
                    Grad += 1;
                    token = strtok(NULL, ", ");
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

            if(strcmp(k1, "si") == 0){
                strcpy(k1, esConexo(0));
                ResetVisitados();
                strcpy(Conex, esConexo(0));
                ResetVisitados();
            }

            for(int i = 0; i < V; i++){
                visitado[i] = 1;
                if(strcmp(k2, "si") == 0){
                    strcpy(k2, esConexo());
                }
                for(int j = 0; j < V; j++){
                    if (j != i && V > 2){
                        visitado[i] = 1;
                        visitado[j] = 1;
                        if(strcmp(k3, "si") == 0){
                            strcpy(k3, esConexo());
                        } 
                        for(int k = 0; k < V; k++){
                            if ( k != i && k != j && V > 3){
                                visitado[i] = 1;
                                visitado[j] = 1;
                                visitado[k] = 1;
                                if(strcmp(k4, "si") == 0){
                                    strcpy(k4, esConexo());
                                }
                                visitado[k] = 0;
                            }
                        }  
                        visitado[j] = 0;
                    }
                }
                visitado[i] = 0;
            } 

            printf("Grado Minimo = %d\nGrado Maximo = %d\n", GradMin, GradMax);
            printf("%s es Conexo\n", Conex);
            printf("%s es 1-Conexo\n", k1);
            printf("%s es 2-Conexo\n", k2);
            printf("%s es 3-Conexo\n", k3);
            printf("%s es 4-Conexo\n\n\n", k4);

            for (int i = 0; i < V; i++) {
                free(grafo[i]);
            }
            free(grafo);
            free(visitado);   
        }
    }
    return 0;
}
