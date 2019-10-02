/* #include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <locale.h>*/
#include <bits/stdc++.h>

#define Tam_Maximo 1000

using namespace std;

int linha=1, coluna=1,q=0,auxPos=0;

string palavrasReservadas[40]={	"programainicio",
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
	//Strings de palavras reservadas
	
string convertLower(char token[]){
	string auxToken;
	cout << "Na funcao" << token;
	//cout << "Na funcao" << to_lower(token);

	//return auxToken;
}

void tratarComentario(char leitura[]){
	while (1){
		if(leitura[q]=='\n'){
			linha++;
			break;}
		q++;
	}
}

void tratarReservadas(char leitura[Tam_Maximo]){
	bool flag=false;
	string token="";
	string tokenLower="";
	int i; //verificar se esse i é aqui mesmo
	while(1){ // Varrer todo o buffer
		if(leitura[q]=='\n'){
			linha++;
			coluna=1;
		}
		if((leitura[q]==' ')||(leitura[q]=='\n')){
			//cout << "Fim de string" << endl;
			break;}

		if((leitura[q]=='#')){
			tratarComentario(leitura);
			break;
		}

		if(((leitura[q]<48) || (leitura[q]>57))  && ((leitura[q]<65) || (leitura[q]>90)) && ((leitura[q]<97) || (leitura[q]>122))){
			auxPos=coluna+1;
			cout << "Erro encontrado na Linha " << linha << " - Coluna "  << coluna << endl;	
			exit(0);
		}

		token+=leitura[q];	
		//atualizarColuna(); remover q++ 
		q++;
		coluna++;
	}
	//verifica se a palavras esta na lista de palvras reservadas
	for (int i=0; i<40; i++){
			tokenLower=token;
			transform(tokenLower.begin(), tokenLower.end(), tokenLower.begin(), ::tolower); 
			if (palavrasReservadas[i].compare(tokenLower) == 0){
				flag=true;
				break;}
	}
	if (flag){
		cout << token << " -- Keyword" << endl;}
	else {
		cout << token << " -- Identify" << endl;}
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

//funcao que verica se a palavra é um numero ou uma sequencia deles
void tratarNumeros(char leitura[Tam_Maximo]){
	bool flag=false;
	string token="";

	//int auxPos=0; //remover
	while(1){ // Varrer todo o buffer
		if(leitura[q]=='\n'){
			linha++;
			coluna=1;
		}
		if((leitura[q]==' ')||(leitura[q]=='\n')){
			// cout << "Fim de Numero" << endl;
			break;}

		if((leitura[q]=='#')){
			tratarComentario(leitura);
			break;
		}

		//tratamento para leitura apenas dos numeros validos
		if((leitura[q]<48) || (leitura[q]>57)){
			auxPos=coluna+1;
			cout << "Erro encontrado na Linha " << linha << " - Coluna "  << coluna << endl;	
			exit(0);
		}
		token+=leitura[q];	
		//atualizarColuna(); remover q++ 
		q++;
		coluna++;
	}
	cout<<token<< " -- Number" << endl;	
}



int main(int argc, const char** argv) {
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
			//cout<<"Tramento de Palavras Reservadas/ID"<< lido << endl;
		}
		else if((lido>=48) && (lido<=57)){
			//cout<< "Tratamento de numeros "<< lido << " tratar numeros"<< endl;
			tratarNumeros(leitura);
		}
		else if(lido==35){
			tratarComentario(leitura);
		}
				
		else{
			cout<<"Caractere Desconhecido "<< lido << endl;
			break;
		//adicionar caso de caracteres invalidos e especiais
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
