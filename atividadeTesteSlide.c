#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0

bool  analise(char  palavra[])  { 
    int k  =  0; 
    while  (palavra[k]  ==  '$'  ||   palavra[k]  ==  '+'  ||  palavra[k]  ==  '-'  ){ 
        printf("%c\n",palavra[k]);
        k++;
        }
    if  ( palavra[k]  ==  '0'  ||  palavra[k]  ==  '1'  ) {
        printf("%c\n",palavra[k]);
        k++; 
        }
    //else         return  FALSE; 
    if  (palavra[k]  ==  '#'  ) { 
        printf("%c\n",palavra[k]); 
        k++; 
        }
    if  (palavra[k]  >=  'a'   &&   palavra[k]  <=  'z' )  { 
        printf("%c\n",palavra[k]);
        k++; 
        return  TRUE; 
    } 
    else 
        return  FALSE; 
} 

//funcao main adicionada para executar funcao do slide
int main() { 

    char palavra[]="+6678\n";
    printf("Palavra: %s",palavra);
    printf("retorno: %d",analise(palavra));
    return 0;

}
