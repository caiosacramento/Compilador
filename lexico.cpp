#include <iostream>
#include <string>
#define Tam_Maximo 1000

using namespace std;

int linha=0, coluna=0,q=0;

struct token{
	string nome="";
	string conteudo="";
	}

void atualizarColuna(){
	q++;
	
	}

void atualizaLinha(){
	q++;
	
	}
	
	//Strings de palavras reservadas
	string palavrasReservadas[4];
	palavrasReservadas[0]="programainicio";
	palavrasReservadas[1]="fimprograma";
	palavrasReservadas[2]="execucaoinicio";
	palavrasReservadas[3]="fimexecucao";


void tratarID(char leitura[Tam_Maximo]){
	bool flag=false;
	string token="";
	while(){ // Varrer todo o buffer
		token+=leitura[i];
		atualizarColuna();
		}
	for(int i=0;i<4;i++){
		token==palavrasReservadas[i];
		flag=true;
		break;
		}
		if(flag){
			
			}else{}
	}
	
int main(){
	
char leitura[Tam_Maximo];
int tamanhoLeitura = fread(leitura, sizeof(char), Tam_Maximo, stdin);


	for (int i=0; i<tamanhoLeitura; i++){
		if(leitura[i]>126){
			cout<<"erro\n";
			return 0;
			}
		
	}

	//while que vai até o fim do tamanho do arquivo a ser verificado
	while(q<=tamanhoLeitura){
		char lido=leitura[q];
		if(lido>=65 && lido<=90 || lido>=97 && lido<=122){
				tratarID(leitura);
		}
	}
}
