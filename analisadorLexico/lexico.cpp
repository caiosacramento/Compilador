/* #include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <locale.h>*/
#include <bits/stdc++.h>
#define Tam_Maximo 1000

using namespace std;

int linha=1, coluna=1,q=0,auxPos=0;

//struct guarda o lexema e suas informacoes
struct Lexema{
	int linha;
	int coluna;
	string nomeToken;
	string valorToken;
	string tipoToken="";
};

vector<Lexema>listaTokens;
vector<Lexema>listaConcatTokens;

string palavrasReservadas[41]={	"programainicio",
								"execucaoinicio",
								"fimexecucao",
								"fimprograma",
								"definainstrucao",
								"como",
								"inicio",
								"fim",
								"repita",
								"vezes",
								"fimrepita",
								"se",
								"entao",
								"fimse",
								"senao",
								"fimsenao",
								"mova",
								"passos",
								"passo",
								"vire",
								"para",
								"pare",
								"finalize",
								"apague",
								"lampada",
								"acenda",
								"aguarde",
								"ate",
								"robo",
								"pronto",
								"robo",
								"ocupado",
								"parado",
								"povimentando",
								"frente",
								"bloqueada",
								"acessa",
								"a",
								"apagada",
								"esquerda",
								"direita"
};

struct token{
	string nome="";
	string conteudo="";
};

void atualizaLinha(){
	q++;
	
}
void atualizarColuna(){
	q++;
}	
	
string convertLower(char token[]){
	string auxToken;
}

void tratarOtherSymbols(char leitura[]){
	while (1){
		if((leitura[q]=='\n')){
			linha++;
			coluna=1;
			break;
			}
		if(leitura[q]==' '){
			break;
		}
		q++;
		coluna++;
		//adicionado break
		break;
	}
}

void tratarComentario(char leitura[]){
	while (1){
		if(leitura[q]=='\n'){
			linha++;
			break;}
		q++;
	}
}

void tratarComentarioErro(char leitura[]){
	while (1){
		if(leitura[q]=='\n'){
			break;}
		q++;
	}
}

void tratarReservadas(char leitura[Tam_Maximo]){
	bool flag=false;
	bool flag1=false;
	string token="";
	string tokenLower="";
	Lexema auxToken; 
	int i; 
	while(1){ 
		if(leitura[q]==10){
			linha++;
			coluna=1;
			break;
		}
		if((leitura[q]==' ')){
			break;}

		if(((leitura[q]<48) || (leitura[q]>57))  && ((leitura[q]<65) || (leitura[q]>90)) && ((leitura[q]<97) || (leitura[q]>122))){
			auxPos=coluna+1;
			flag1=true;
			cout << "Erro encontrado na Linha " << linha << " - Coluna "  << coluna << endl;	
			tratarOtherSymbols(leitura);
			break;
		}

		token+=leitura[q];	
		auxToken.linha=linha;
		auxToken.coluna=coluna;
		q++;
		coluna++;
	}
	//verifica se a palavra esta na lista de palvras reservadas
	for (int i=0; i<41; i++){
			tokenLower=token;
			transform(tokenLower.begin(), tokenLower.end(), tokenLower.begin(), ::tolower); 
			if (palavrasReservadas[i].compare(tokenLower) == 0){
				flag=true;
				break;}
	}
	if(!flag1){
		if (flag){
			cout << token << " -- Keyword --" << auxToken.linha << " Coluna " << auxToken.coluna << endl;
			auxToken.nomeToken=token;
			auxToken.valorToken="Keyword";
			listaTokens.push_back(auxToken);
			}
		else {
			cout << token << " -- Identify" << auxToken.linha << " Coluna " << auxToken.coluna << endl;
			auxToken.nomeToken=token;
			auxToken.valorToken="Identify";
			listaTokens.push_back(auxToken);
			}
	}
}

//funcao que verica se a palavra é um numero ou uma sequencia deles
void tratarNumeros(char leitura[Tam_Maximo]){
	bool flag=false;
	string token="";
	Lexema auxToken; 

	while(1){ 
		if(leitura[q]=='\n'){
			linha++;
			coluna=1;
			break;
		}
		if((leitura[q]==' ')){
			break;}

		//tratamento para leitura apenas dos numeros validos
		if((leitura[q]<48) || (leitura[q]>57)){
			auxPos=coluna+1;
			cout << "Erro encontrado na Linha " << linha << " - Coluna "  << coluna << endl;	
			flag=true;
			tratarOtherSymbols(leitura);
			break;
		}
		token+=leitura[q];	
		auxToken.linha=linha;
		auxToken.coluna=coluna;
		q++;
		coluna++;
	}
	if(!flag){
		cout<<token<< " -- Number" << auxToken.linha << "Coluna" << auxToken.coluna <<endl;	
		auxToken.nomeToken=token;
		auxToken.valorToken="Number";
		listaTokens.push_back(auxToken);
	}
}
//funcao para concatena palavras reservadas

int main(int argc, const char** argv) {
string padrao;
int linhaCursor=1,j=0;
char leitura[Tam_Maximo];

int tamanhoLeitura = fread(leitura, sizeof(char), Tam_Maximo, stdin);

for (int i=0; i < tamanhoLeitura; i++){
	if ((leitura[i]>126)){
	cout<<"erro Linha " << linhaCursor << " Coluna "  << i+1 << endl;
	return 0;}
}

while(q<tamanhoLeitura){
	char lido=leitura[q];
		if(lido>=65 && lido<=90 || lido>=97 && lido<=122){
			tratarReservadas(leitura);
			//"Tramento de Palavras Reservadas/ID"
		}
		else if((lido>=48) && (lido<=57)){
			//"Tratamento de numeros "
			tratarNumeros(leitura);
		}
		else if((lido==35) && (coluna==1)){
			tratarComentario(leitura);
		}
				
		else if(((lido!='\n')&&(lido!=' '))){
			if(lido==35){
				tratarComentarioErro(leitura);
			}
			if(coluna==1){
				cout<<"Erro Encontrado no Caractere Desconhecido: " << lido << " Na Linha "<< linha << " Coluna " << coluna << endl;
				tratarOtherSymbols(leitura);
			}
			else{
				cout<<"Erro Encontrado no Caractere Desconhecido: " << lido << " Na Linha "<< linha << " Coluna mais um " << coluna+1 << endl;
				tratarOtherSymbols(leitura);
			}		
		}
	q++;
}

cout << endl << endl;

for(int i=0; i<listaTokens.size(); i++){
		cout<<"\n"<<listaTokens[i].nomeToken<<" "<<listaTokens[i].valorToken<<"\n";
		cout<<listaTokens[i].linha<<" "<<listaTokens[i].coluna<<"\n";
}  

}
