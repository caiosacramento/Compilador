#include <iostream>
define Tam_Maximo 1000
int linha=0, coluna=0,q=0;

struct token{
	string nome="";
	string conteudo="";
	}

void atualizarColuna(){
	q++;}

void atualizaLinha(){
	q++;};

string palavrasReservadas[3];
	palavrasReservadas[0]="Acendalampada";
	palavrasReservadas[1]="Acendalampada";
	palavrasReservadas[2]="Acendalampada";


void tratarID(char leitura[Tam_Maximo]){
	bool flag=false;
	string token="";
	while(){
		token+=leitura[i];
		atualizarColuna();
		}
	for(i<3){
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

	while(q<=tamanhoLeitura){
		char lido=leitura[q];
		if(lido>=65 && lido<=90 ||){
				tratarID(leitura);
		}
	}
}
