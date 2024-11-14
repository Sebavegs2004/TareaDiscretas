#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

int **grafo;
int *visitado;
int V, K;

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

bool esConexo() {
    for(int r = 0; r < V; r++){
        if(visitado[r] == 0){
            DFS(r);
            break;
        }
    }
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            ResetVisitados();
            return false;
        }
    }
    ResetVisitados();
    return true;
}

int main() {
    char linea[256] , nombre_archivo[100];
    clock_t inicio, fin;

    while(1){
        int fila = 0, GradMax = 0, GradMin = 0, Grad = 0, Lock = 0, Opcion1, Opcion2;
        printf("¿Que quieres hacer?\n(1) Cargar grafo\n(2) Salir\nOpcion = ");
        scanf("%d", &Opcion1);
        if(Opcion1 == 2){
            exit(0);
        }
        else if(Opcion1 == 1){
            printf("Ingrese el nombre del archivo = ");
            scanf(" %[^\n]", nombre_archivo);
            FILE *file = fopen(nombre_archivo, "r");
            if (file == NULL) {
                printf("Error al abrir el archivo o no existe.\n\n");
            } else{
                inicio = clock();
                int vertice = 0, GradMax = 0, GradMin = 0, Grad = 0, Lock = 0, Opcion1, Opcion2;

                if (fgets(linea, sizeof(linea), file) != NULL) {
                    linea[strcspn(linea, "\n")] = '\0';
                    V = atoi(linea);
                }

                if(V != 0 && V != 1){
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

                    while (fgets(linea, sizeof(linea), file) != NULL) {
                        if(strchr(linea, ' ') != NULL){
                            char *token = strtok(strchr(linea, ' '), ", ");
                            while(token != NULL){
                                grafo[vertice][atoi(token) - 1] = 1;
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
                            vertice += 1;
                        }
                    }
                    fclose(file);

                    if(!esConexo()){
                        K = 0;
                    } else{
                        K = 1;
                        for(int i = 0; i < V && Lock < 3; i++){
                            visitado[i] = 1;
                            if(!esConexo()){
                                K = 1;
                                Lock = 3;
                            } else{
                                K = 2;
                            }
                            for(int j = 0; j < V && Lock < 2; j++){
                                if (j != i && V > 2){
                                    visitado[i] = 1;
                                    visitado[j] = 1;
                                    if(!esConexo()){
                                        K = 2;
                                        Lock = 2;
                                    } else{
                                        K = 3;
                                    }
                                    for(int k = 0; k < V && Lock < 1; k++){
                                        if ( k != i && k != j && V > 3){
                                            visitado[i] = 1;
                                            visitado[j] = 1;
                                            visitado[k] = 1;
                                            if(!esConexo()){
                                                K = 3;
                                                Lock = 1;
                                            } else{
                                                K = 4;
                                            }
                                            visitado[k] = 0;
                                        }
                                    }  
                                    visitado[j] = 0;
                                }
                            }
                            visitado[i] = 0;
                        }
                    }

                    for (int i = 0; i < V; i++) {
                        free(grafo[i]);
                    }
                    free(grafo);
                    free(visitado);

                    fin = clock();
                } else{
                    K = V;
                }

                printf("\n");
                printf("[Tiempo de ejecucion = %fs]\n\n", ((double)(fin - inicio)) / CLOCKS_PER_SEC);
                while(1){
                    printf("¿Que quieres saber del grafo?\n(1) Grado Maximo\n(2) Grado Minimo\n(3) Conexidad\n(4) Conectividad\n(5) Cerrar Grafo\nOpcion = ");
                    scanf("%d", &Opcion2);
                    if(Opcion2 == 1){
                        printf("\n[El grado maximo es %d]\n\n", GradMax);
                    }
                    else if(Opcion2 == 2){
                        printf("\n[El grado minimo es %d]\n\n", GradMin);
                    }
                    else if(Opcion2 == 3){
                        if(K > 0 || V == 1 || V == 0){
                            printf("\n[Es conexo]\n\n");
                        } else{
                            printf("\n[No es conexo]\n\n");
                        }
                    }
                    else if(Opcion2 == 4){
                        if(K > 0 || V == 0){
                            printf("\n[Es %d-Conexo]\n\n", K);
                        }
                        else{
                            printf("\n[No hay conectividad ya que es disconexo]\n\n");
                        }
                    }
                    else if(Opcion2 == 5){
                        printf("\n");
                        break;
                    }
                    else{
                        printf("ERROR no es opcion valida\n\n");   
                    }
                }
            }
        }
        else{
            printf("ERROR no es opcion valida\n\n");
        }
    }
}
