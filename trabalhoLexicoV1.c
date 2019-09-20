#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
int estado=0;

//substituir por EOF que é o fim do arquivo
int main() { 
    char palavra[]="baba\n";
    char c;
    int aux=0,i=0;//i eh usado para percorrer a string
    int tam=0;
    //Adicionar while infinito para que percorra todo o programa e remover aux
    
    tam=strlen(palavra);
    printf("%d\n", tam);
    while(aux<tam){
        c=palavra[i];
        //Switch case que checa estados do automato 
        switch(estado){
            case 0:
                if(c=='a'){  
                   estado=1;
                   printf("proximo estado é %d\n",estado);}
                else if(c=='b'){
                   estado=0;
                   printf("proximo estado é %d\n",estado);}
                else{
                   printf("Erro\n");}
                break;
            case 1:
                if(c=='b'){
                  estado=2;
                  printf("proximo estado é %d\n",estado);}
                else{
                   printf("Erro\n");}                    
                break;
            case 2:
                if(c=='\n'){
                    printf("Cadeia aceita!\n");}
                else{
                   printf("Erro\n");                    
                }
                break;
        }
        aux++;
        i++;
    }
    printf("Palavra analisada: %s",palavra);
    return 0;
}
