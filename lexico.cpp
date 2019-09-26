#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <locale.h>

#define Tam_Maximo 1000

using namespace std;

int linha=0, coluna=0,q=0;
string palavrasReservadas[4]={"programainicio","fimprograma","execucaoinicio","fimexecucao"};

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
	

void tratarID(char leitura[Tam_Maximo]){
	bool flag=false;
	string token="";
	int i; //verificar se esse i é aqui mesmo
	while(1){ // Varrer todo o buffer
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

/* string leitura = "programainicio @ + fimprograma";
int tamanhoLeitura = leitura.length();
 */
ifstream arquivo;
string line,line2;
string padrao;
int linhaCursor=1,j=0;
char leitura[Tam_Maximo];
arquivo.open("in.txt");
//int tamanhoLeitura = fread(arquivo, sizeof(char), Tam_Maximo, stdin);
	//for verifica se existe alguma caractere invalido e retorna erro caso encontre
	/* for (int i=0; i<tamanhoLeitura; i++){
		if(leitura[i]>126){
			cout<<"erro\n";
			return 0;}
	} */
while(getline(arquivo,line)){
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
	padrao += ' ';
	linhaCursor++;
}
arquivo.close();
cout<< padrao<<endl;
arquivo.open("in.txt");
//cout<<"Segundo getLine"<<endl;

while(q<padrao.length()){
	char lido=padrao[q];
	//cout<<lido<<endl;
		if(lido>=65 && lido<=90 || lido>=97 && lido<=122){
			//chamar funcao passanado inicio da sting
			cout<<"Segundo While Is Alpha "<< lido << endl;}	
		else{
			cout<<"Caractere Desconhecido"<< endl;}
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
