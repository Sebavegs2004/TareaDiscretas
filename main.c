#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char const *argv[]){
	FILE *file = fopen("grafo.txt", "r");
	char linea[256];
	char *inicio_tok;
	char *tok;
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
		inicio_tok = strstr(linea, " ");
		tok = strtok(inicio_tok, ", ");
	    while (tok != NULL) {
	    	matriz_ad[fila][atoi(tok) - 1] = 1;
	        tok = strtok(NULL, ", "); 
	    }	
		fila += 1;
	}

	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++){
			printf("%d ", matriz_ad[x][y]);
		}
		printf("\n");
	}



}


