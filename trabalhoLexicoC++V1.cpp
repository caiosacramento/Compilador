#include <iostream>
#include <string>
using namespace std;
int estado=0;

//substituir por EOF que é o fim do arquivo
int main() { 
    string palavra="baba";
    cout << palavra << endl;
    char c;
    int aux=0,i=0;//i eh usado para percorrer a string

    
    //Adicionar while infinito para que percorra todo o programa e remover aux
    cout << palavra.length() << endl;    
    while(aux<palavra.length()){
        c=palavra[i];
         switch(estado){
             case 0:
                 if(c=='a'){  
                    estado=1;
                    cout << "proximo estado é " << estado << endl;}
                 else if(c=='b'){
                    estado=0;
                    cout << "proximo estado é " << estado << endl;}
                 else{
                    cout << "Erro\n";}
                 break;
             case 1:
                 if(c=='b'){
                   estado=2;
                   cout << "proximo estado é " << estado << endl;}
                 else{
                    cout << "Erro\n";}                    
                 break;
             case 2:
                 if(c=='\n'){
                     cout << "Cadeia aceita!\n";}
                 else{
                    cout << "Erro\n";}
                 break;
         }
         aux++;
         i++;
         }

    return 0; 
    }
     


