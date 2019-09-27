/* #include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <locale.h>*/
#include <bits/stdc++.h>
#define Tam_Maximo 1000

using namespace std;

int linha=0, coluna=0,q=0;

string palavrasReservadas[23]={	"Execucaoinicio",
								"fimexecucao",
								"Acendalampada",
								"Aguarde",
								"ate",
								"Definainstrucao",
								"como",
								"Enquanto",
								"faca",
								"Finalize",
								"Mova",
								"Pare",
								"Programainicio",
								"fimprograma",
								"Repita",
								"VEZES",
								"fimrepita",
								"se",
								"entao", 
								"fimse",
								"senao",
								"fimsenao",
								"VirePara"							
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
	//Strings de palavras reservadas
	
void tratarReservadas(char leitura[Tam_Maximo]){
	bool flag=false;
	string token="";
	int i; //verificar se esse i é aqui mesmo
	while(1){ // Varrer todo o buffer
		if((leitura[q]==' ')||(leitura[q]=='\n')){
			cout << "Fim de string" << endl;
			break;}
		token+=leitura[q];	
		//atualizarColuna(); remover q++ 
		q++;
	}
	for (int i=0; i<23; i++){
			if (palavrasReservadas[i].compare(token) == 0){
				flag=true;
				break;}
	}
	if (flag){
		cout << token << " -- palavra reservada" << endl;}
	else {
		cout << token << " -- ID" << endl;}
	/* 	for(int i=0;i<4;i++){
		if(token==palavrasReservadas[i]){
			flag=true;
			break;}
		}
		if(flag){
		}
		else{
		} */
}

void tratarNumeros(char leitura[Tam_Maximo]){
	bool flag=false;
	string token="";

	int i; //verificar se esse i é aqui mesmo
	while(1){ // Varrer todo o buffer
		if((leitura[q]==' ')||(leitura[q]=='\n')){
			cout << "Fim de string" << endl;
			break;}
		token+=leitura[q];	
		//atualizarColuna(); remover q++ 
		q++;
	}
	if (flag){
		cout << token << " -- palavra reservada" << endl;}
	else {
		cout << token << " -- ID" << endl;}
}

	
int main(int argc, const char** argv) {

/* string leitura = "programainicio @ + fimprograma";
int tamanhoLeitura = leitura.length();
 */
string padrao;
int linhaCursor=1,j=0;
char leitura[Tam_Maximo];
int tamanhoLeitura = fread(leitura, sizeof(char), Tam_Maximo, stdin);

for (int i=0; i < tamanhoLeitura; i++){
		/* char aux=line[i];
		 padrao += aux;
		 cout<<"caractere "<<line[i]<< " Coluna "<< i+1 << endl; 
         //falta tratamento de cararcteres acentuados
		 //i representa a coluna, linhaCursor representa a Linha */
	if ((leitura[i]>126)){
	cout<<"erro Linha " << linhaCursor << " Coluna "  << i+1 << endl;
	return 0;}
}
	//for verifica se existe alguma caractere invalido e retorna erro caso encontre
	/* for (int i=0; i<tamanhoLeitura; i++){
		if(leitura[i]>126){
			cout<<"erro\n";
			return 0;}
	} */
/* while(getline(arquivo,line)){
    for (int i=0; i < line.length(); i++){
		char aux=line[i];
		padrao += aux;
		cout<<"caractere "<<line[i]<< " Coluna "<< i+1 << endl;
         //falta tratamento de cararcteres acentuados
		 //i representa a coluna, linhaCursor representa a Linha
		 if ((line[i]>126)||(line[i]=='!')){
		 cout<<"erro Linha " << linhaCursor << " Coluna "  << i+1 << endl;
			return 0;}
    }
	//padrao += ' ';
	linhaCursor++;
}
arquivo.close(); 
cout<< padrao<<endl;
arquivo.open("in.txt");
//cout<<"Segundo getLine"<<endl;*/

while(q<tamanhoLeitura){
	char lido=leitura[q];
		 //65-> "A" && 90-> "Z" 97-> a && 122->z
		if(lido>=65 && lido<=90 || lido>=97 && lido<=122){
			tratarReservadas(leitura);
			//chamar funcao passanado inicio da sting
			//cout<<"Segundo While Is Alpha "<< lido << endl;
		}
		else if((lido>=48) && (lido<=57)){
			//tratarNumeros(leitura);
			cout<< "O valor de lido é: "<< lido << " tratar numeros"<< endl;
		}		
		else{
			cout<<"Caractere Desconhecido "<< lido << endl;
		}
	q++;
}
	/* while(q<=tamanhoLeitura){
		char lido=leitura[q];
		if(lido>=65 && lido<=90 || lido>=97 && lido<=122){
				//tratarID(leitura);
				cout<<"texto " << lido <<endl;}
		else{
			cout<<"erro caractere desconhecido " << lido <<endl;
		}
		q++;
	} */
}
