#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

int **grafo;
int *visitado;
int V, K;

#ifdef _WIN32
    #define clear system("cls");
#else
    #define clear system("clear");
#endif

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
    clear;
    char linea[256] , nombre_archivo[100];
    clock_t inicio, fin;

    while(1){
        int fila = 0, GradMax = 0, GradMin = 0, Grad = 0, Lock = 0;
        char Opcion1[] = " ", Opcion2[] = " ";
        printf("\033[1;34m¿Qué quieres hacer?\033[0m\n\033[1;32m(1) Cargar grafo\033[0m\n\033[1;31m(2) Salir\033[0m\n\033[1;34mOpción = \033[0m");
        scanf(" %[^\n]", Opcion1);
        if(strcmp(Opcion1, "2") == 0){
            printf("\033[1;31mSaliendo del programa...\033[0m\n");
            exit(0);
        }
        else if(strcmp(Opcion1, "1") == 0){
            printf("\033[1;36mIngrese el nombre del archivo: \033[0m");
            scanf(" %[^\n]", nombre_archivo);
            FILE *file = fopen(nombre_archivo, "r");
            if (file == NULL) {
                clear;
                printf("\n\033[1;31mError: \033[1;33mNo se pudo abrir el archivo o no existe.\033[0m\n\n");

            } else{
                clear;
                inicio = clock();
                int fila = 0, GradMax = 0, GradMin = 0, Grad = 0, Lock = 4;

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

                    while (fgets(linea, sizeof(linea), file) != NULL && fila < V) {
                        if(strchr(linea, ' ') != NULL){
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
                    }
                    fclose(file);
                    if(!esConexo()){
                        K = 0;
                    } else{
                        K = 1;
                        for(int i = 0; i < V && Lock > 1; i++){
                            visitado[i] = 1;
                            if(!esConexo()){
                                K = 1;
                                Lock = 1;
                            } else{
                                K = 2;
                            }
                            for(int j = 0; j < V && Lock > 2; j++){
                                if (j != i && V > 2){
                                    visitado[i] = 1;
                                    visitado[j] = 1;
                                    if(!esConexo()){
                                        K = 2;
                                        Lock = 2;
                                    } else{
                                        K = 3;
                                    }
                                    for(int k = 0; k < V && Lock > 3; k++){
                                        if ( k != i && k != j && V > 3){
                                            visitado[i] = 1;
                                            visitado[j] = 1;
                                            visitado[k] = 1;
                                            if(!esConexo()){
                                                K = 3;
                                                Lock = 3;
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
                } else{
                    K = V;
                }

                fin = clock();
                while(1){
                    printf("\n\033[1;36m[Numero de vertices = \033[1;33m%d\033[1;36m]\n[Tiempo de ejecucion = \033[1;32m%fs\033[1;36m]\033[0m\n\n", V, ((double)(fin - inicio)) / CLOCKS_PER_SEC);
                    printf("\033[1;34m¿Qué quieres saber del grafo?\033[0m\n\033[1;33m(1) Grado Máximo\033[0m\n\033[1;35m(2) Grado Mínimo\033[0m\n\033[1;36m(3) Conexidad\033[0m\n\033[1;32m(4) Conectividad\033[0m\n\033[1;31m(5) Cerrar Grafo\033[0m\n\033[1;37m(6) Salir\033[0m\n\033[1;34mOpción = \033[0m");
                    scanf(" %[^\n]", Opcion2);
                    if(strcmp(Opcion2, "1") == 0){
                        clear;
                        printf("\n\033[1;35m[El grado máximo es: \033[1;35m%d\033[1;35m]\033[0m\n", GradMax);
                    }
                    else if(strcmp(Opcion2, "2") == 0){
                        clear;
                        printf("\n\033[1;36m[El grado mínimo es: \033[1;36m%d\033[1;36m]\033[0m\n", GradMin);
                    }
                    else if(strcmp(Opcion2, "3") == 0){
                        clear;
                        if(K > 0 || V == 0){
                            printf("\n\033[1;32m[Es conexo]\033[0m\n");

                        } else{
                            printf("\n\033[1;31m[No es conexo]\033[0m\n");

                        }
                    }
                    else if(strcmp(Opcion2, "4") == 0){
                        clear;
                        printf("\n\033[1;36m[Es \033[1;33m%d-Conexo\033[1;36m]\033[0m\n", K);

                        
                    }
                    else if(strcmp(Opcion2, "5") == 0){
                        clear;
                        break;
                    }
                    else if(strcmp(Opcion2, "6") == 0){
                        exit(0);
                    }
                    else{
                        clear;
                            printf("\n\033[1;31mERROR: \033[1;33mNo es una opción válida.\033[0m\n");

                    }
                }
            }
        }
        else{
            clear;
            printf("\n\033[1;31mERROR: \033[1;33mNo es una opción válida.\033[0m\n\n");

        }
    }
}
