#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_NODES 20

void dfs(int nodo, bool visited[], int matriz_ad[][MAX_NODES]) {
    visited[nodo] = true;
    for (int i = 0; i < MAX_NODES; i++) {
        if (matriz_ad[nodo][i] == 1 && !visited[i]) {
            dfs(i, visited, matriz_ad);
        }
    }
}

bool es_conexo(int matriz_ad[][MAX_NODES]) {
    bool visited[MAX_NODES] = {false};
    dfs(0, visited, matriz_ad);
    for (int i = 0; i < MAX_NODES; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[]){
	FILE *file = fopen("grafo.txt", "r");
	char linea[256];
	int n;

	if(fgets(linea, sizeof(linea), file) != NULL){
		linea[strcspn(linea, "\n")] = '\0';
		n = atoi(linea);
	}
	
	int matriz_ad[n][n];
	int fila = 0;

	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++){
			matriz_ad[x][y] = 0;
		}
	}

	while(fgets(linea, sizeof(linea), file) != NULL){
		for(int x = 2; x < strlen(linea); x++){
			if(isdigit(linea[x]) && (atoi(&linea[x]) <= n)){
				matriz_ad[fila][atoi(&linea[x]) - 1] = 1;
			}
		}
		fila += 1;
	}

	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++){
			printf("%d ", matriz_ad[x][y]);
		}
		printf("\n");
	}

	if (es_conexo(matriz_ad, n)) {
        printf("El grafo es conexo.\n");
    } else {
        printf("El grafo no es conexo.\n");
    }

    return 0;
}


