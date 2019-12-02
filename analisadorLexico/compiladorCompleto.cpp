#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>    // std::binary_search, std::sort
#define Tam_Maximo 1000
//#include "reduceShift.cpp"
//#include "reduceShift.cpp"
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
vector<Lexema>listaTkSemantico;
vector<Lexema>listaTkGeraCodigo;
map <string,int> mapSimboAux; 
stack <int> pilha;

Lexema auxReduce;
bool flagSintatico=false;
bool flagLexic=true;

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

string matrizSlr[92][64]={ 

{"s2"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","1"," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","acc"," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","s4"," "," ","s5"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","3"," "," "," "," "," "," "," "," "," "," "," "},
{" ","s6"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8"," ","7","9","10","11"," ","12"," ","19"," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," "," "," "," "," "," "," "," "," "," ","26"," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8"," ","27","9","10","11"," ","12"," ","19"," "},
{" "," ","s28"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r9","r9"," ","r9"," ","r9","r9","r9"," ","r9","r9"," ","r9","r9"," ","r9"," ","r9","r9"," ","r9"," "," "," ","r9","r9","r9"," ","r9","r9"," "," "," "," "," "," "," "," "," "," "," ","r9"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r10","r10"," ","r10"," ","r10","r10","r10"," ","r10","r10"," ","r10","r10"," ","r10"," ","r10","r10"," ","r10"," "," "," ","r10","r10","r10"," ","r10","r10"," "," "," "," "," "," "," "," "," "," "," ","r10"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r11","r11"," ","r11"," ","r11","r11","r11"," ","r11","r11"," ","r11","r11"," ","r11"," ","r11","r11"," ","r11"," "," "," ","r11","r11","r11"," ","r11","r11"," "," "," "," "," "," "," "," "," "," "," ","r11"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r12","r12"," ","r12"," ","r12","r12","r12"," ","r12","r12"," ","r12","r12"," ","r12"," ","r12","r12"," ","r12"," "," "," ","r12","r12","r12"," ","r12","r12"," "," "," "," "," "," "," "," "," "," "," ","r12"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r13","r13"," ","r13"," ","r13","r13","r13"," ","r13","r13"," ","r13","r13"," ","r13"," ","r13","r13"," ","r13"," "," "," ","r13","r13","r13"," ","r13","r13"," "," "," "," "," "," "," "," "," "," "," ","r13"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13","s30","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","29","31","9","10","11"," ","12"," ","19"," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s33"," "," "," "," "," "," "," "," "," "," "," "," "," "," ","32"},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s37","s38"," "," "," ","s39"," "," "," ","s35"," "," "," "," ","s36"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","34"," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s37","s38"," "," "," ","s39"," "," "," ","s35"," "," "," "," ","s36"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","40"," "," "},
{" ","r21","r21"," ","r21"," ","r21","r21","r21"," ","r21","r21"," ","r21","r21"," ","r21"," ","r21","r21"," ","r21"," "," "," ","r21","r21","r21"," ","r21","r21"," "," "," "," "," "," "," "," "," "," "," ","r21","s33"," "," "," "," "," "," "," "," "," "," "," "," "," "," ","41"},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s42"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r24","r24"," ","r24"," ","r24","r24","r24"," ","r24","r24"," ","r24","r24"," ","r24"," ","r24","r24"," ","r24"," "," "," ","r24","r24","r24"," ","r24","r24"," "," "," "," "," "," "," "," "," "," "," ","r24"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r25","r25"," ","r25"," ","r25","r25","r25"," ","r25","r25"," ","r25","r25"," ","r25"," ","r25","r25"," ","r25"," "," "," ","r25","r25","r25"," ","r25","r25"," "," "," "," "," "," "," "," "," "," "," ","r25"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r26","r26"," ","r26"," ","r26","r26","r26"," ","r26","r26"," ","r26","r26"," ","r26"," ","r26","r26"," ","r26"," "," "," ","r26","r26","r26"," ","r26","r26"," "," "," "," "," "," "," "," "," "," "," ","r26"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s43"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s44"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s45"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r43","r43"," ","r43","r43","r43","r43","r43"," ","r43","r43"," ","r43","r43"," ","r43"," ","r43","r43"," ","r43"," "," "," ","r43","r43","r43"," ","r43","r43"," "," "," "," "," "," "," "," "," "," "," ","r43"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," ","s46"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," ","s47"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," ","s48"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," ","s49"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r6","r6"," ","r6"," ","r6","r6","r6"," ","r6","r6"," ","r6","r6"," ","r6"," ","r6","r6"," ","r6"," "," "," ","r6","r6","r6"," ","r6","r6"," "," "," "," "," "," "," "," "," "," "," ","r6"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13","r8","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","50","31","9","10","11"," ","12"," ","19"," "},
{" "," "," "," "," "," "," "," "," ","s51"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," ","r44"," "," "," "," "," "," "," "," "," "," ","r44"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","s52"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s53","s54","s55","s56"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s57"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s58"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s59"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s60"," ","s61"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s62"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s63"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s64","s65"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r27","r27"," ","r27"," ","r27","r27","r27"," ","r27","r27"," ","r27","r27"," ","r27"," ","r27","r27"," ","r27"," "," "," ","r27","r27","r27"," ","r27","r27"," "," "," "," "," "," "," "," "," "," "," ","r27"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r28","r28"," ","r28"," ","r28","r28","r28"," ","r28","r28"," ","r28","r28"," ","r28"," ","r28","r28"," ","r28"," "," "," ","r28","r28","r28"," ","r28","r28"," "," "," "," "," "," "," "," "," "," "," ","r28"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s37","s38"," "," "," ","s39"," "," "," ","s35"," "," "," "," ","s36"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","66"," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8"," ","67","9","10","11"," ","12"," ","19"," "},
{" "," "," ","s68"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","r2"," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r5","r5"," ","r5"," ","r5","r5","r5"," ","r5","r5"," ","r5","r5"," ","r5"," ","r5","r5"," ","r5"," "," "," ","r5","r5","r5"," ","r5","r5"," "," "," "," "," "," "," "," "," "," "," ","r5"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," ","r7"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8"," ","69","9","10","11"," ","12"," ","19"," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8"," ","70","9","10","11"," ","12"," ","19"," "},
{" ","r30","r30"," ","r30"," ","r30","r30","r30"," ","r30","r30","r30","r30","r30","r30","r30"," ","r30","r30"," ","r30"," "," "," ","r30","r30","r30"," ","r30","r30"," "," "," "," "," "," "," "," "," "," "," ","r30"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r31","r31"," ","r31"," ","r31","r31","r31"," ","r31","r31","r31","r31","r31","r31","r31"," ","r31","r31"," ","r31"," "," "," ","r31","r31","r31"," ","r31","r31"," "," "," "," "," "," "," "," "," "," "," ","r31"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r32","r32"," ","r32"," ","r32","r32","r32"," ","r32","r32","r32","r32","r32","r32","r32"," ","r32","r32"," ","r32"," "," "," ","r32","r32","r32"," ","r32","r32"," "," "," "," "," "," "," "," "," "," "," ","r32"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r33","r33"," ","r33"," ","r33","r33","r33"," ","r33","r33","r33","r33","r33","r33","r33"," ","r33","r33"," ","r33"," "," "," ","r33","r33","r33"," ","r33","r33"," "," "," "," "," "," "," "," "," "," "," ","r33"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s71"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s72"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s73"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s74"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s75"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8"," ","76","9","10","11"," ","12"," ","19"," "},
{" ","r20","r20"," ","r20"," ","r20","r20","r20"," ","r20","r20"," ","r20","r20"," ","r20"," ","r20","r20"," ","r20"," "," "," ","r20","r20","r20"," ","r20","r20"," "," "," "," "," "," "," "," "," "," "," ","r20"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r22","r22"," ","r22"," ","r22","r22","r22"," ","r22","r22"," ","r22","r22"," ","r22"," ","r22","r22"," ","r22"," "," "," ","r22","r22","r22"," ","r22","r22"," "," "," "," "," "," "," "," "," "," "," ","r22"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r23","r23"," ","r23"," ","r23","r23","r23"," ","r23","r23"," ","r23","r23"," ","r23"," ","r23","r23"," ","r23"," "," "," ","r23","r23","r23"," ","r23","r23"," "," "," "," "," "," "," "," "," "," "," ","r23"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r29","r29"," ","r29"," ","r29","r29","r29"," ","r29","r29"," ","r29","r29"," ","r29"," ","r29","r29"," ","r29"," "," "," ","r29","r29","r29"," ","r29","r29"," "," "," "," "," "," "," "," "," "," "," ","r29"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r4"," "," ","s5"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","77"," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","r1"," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," ","s78"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," ","s79"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r34","r34"," ","r34"," ","r34","r34","r34"," ","r34","r34","r34","r34","r34","r34","r34"," ","r34","r34"," ","r34"," "," "," ","r34","r34","r34"," ","r34","r34"," "," "," "," "," "," "," "," "," "," "," ","r34"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r35","r35"," ","r35"," ","r35","r35","r35"," ","r35","r35","r35","r35","r35","r35","r35"," ","r35","r35"," ","r35"," "," "," ","r35","r35","r35"," ","r35","r35"," "," "," "," "," "," "," "," "," "," "," ","r35"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r36","r36"," ","r36"," ","r36","r36","r36"," ","r36","r36","r36","r36","r36","r36","r36"," ","r36","r36"," ","r36"," "," "," ","r36","r36","r36"," ","r36","r36"," "," "," "," "," "," "," "," "," "," "," ","r36"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s82","s81"," "," "," "," "," "," "," "," "," "," "," "," ","s80"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s85","s84"," "," "," "," "," "," "," "," "," "," "," "," ","s83"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s86"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r3"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r14","r14"," ","r14"," ","r14","r14","r14"," ","r14","r14"," ","r14","r14"," ","r14"," ","r14","r14"," ","r14"," "," "," ","r14","r14","r14"," ","r14","r14"," "," "," "," "," "," "," "," "," "," "," ","r14"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r15","r15"," ","r15"," ","r15","r15","r15"," ","r15","r15"," ","r15","r15"," ","r15"," ","r15","r15"," ","r15"," "," "," ","r15","r15","r15"," ","r15","r15"," "," "," "," "," "," "," "," "," "," "," ","r15"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r37","r37"," ","r37"," ","r37","r37","r37"," ","r37","r37","r37","r37","r37","r37","r37"," ","r37","r37"," ","r37"," "," "," ","r37","r37","r37"," ","r37","r37"," "," "," "," "," "," "," "," "," "," "," ","r37"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r39","r39"," ","r39"," ","r39","r39","r39"," ","r39","r39","r39","r39","r39","r39","r39"," ","r39","r39"," ","r39"," "," "," ","r39","r39","r39"," ","r39","r39"," "," "," "," "," "," "," "," "," "," "," ","r39"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r41","r41"," ","r41"," ","r41","r41","r41"," ","r41","r41","r41","r41","r41","r41","r41"," ","r41","r41"," ","r41"," "," "," ","r41","r41","r41"," ","r41","r41"," "," "," "," "," "," "," "," "," "," "," ","r41"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r38","r38"," ","r38"," ","r38","r38","r38"," ","r38","r38","r38","r38","r38","r38","r38"," ","r38","r38"," ","r38"," "," "," ","r38","r38","r38"," ","r38","r38"," "," "," "," "," "," "," "," "," "," "," ","r38"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r40","r40"," ","r40"," ","r40","r40","r40"," ","r40","r40","r40","r40","r40","r40","r40"," ","r40","r40"," ","r40"," "," "," ","r40","r40","r40"," ","r40","r40"," "," "," "," "," "," "," "," "," "," "," ","r40"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r42","r42"," ","r42"," ","r42","r42","r42"," ","r42","r42","r42","r42","r42","r42","r42"," ","r42","r42"," ","r42"," "," "," ","r42","r42","r42"," ","r42","r42"," "," "," "," "," "," "," "," "," "," "," ","r42"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r17","r17"," ","r17"," ","r17","r17","r17"," ","r17","r17"," ","r17","r17"," ","r17","s88","r17","r17"," ","r17"," "," "," ","r17","r17","r17"," ","r17","r17"," "," "," "," "," "," "," "," "," "," "," ","r17"," "," "," "," "," "," "," "," "," "," "," ","87"," "," "," "," "},
{" ","r16","r16"," ","r16"," ","r16","r16","r16"," ","r16","r16"," ","r16","r16"," ","r16"," ","r16","r16"," ","r16"," "," "," ","r16","r16","r16"," ","r16","r16"," "," "," "," "," "," "," "," "," "," "," ","r16"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8"," ","89","9","10","11"," ","12"," ","19"," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s90"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r19","r19"," ","r19"," ","r19","r19","r19"," ","r19","r19"," ","r19","r19"," ","r19","s88","r19","r19"," ","r19"," "," "," ","r19","r19","r19"," ","r19","r19"," "," "," "," "," "," "," "," "," "," "," ","r19"," "," "," "," "," "," "," "," "," "," "," ","91"," "," "," "," "},
{" ","r18","r18"," ","r18"," ","r18","r18","r18"," ","r18","r18"," ","r18","r18"," ","r18"," ","r18","r18"," ","r18"," "," "," ","r18","r18","r18"," ","r18","r18"," "," "," "," "," "," "," "," "," "," "," ","r18"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},

};


struct token{
	string nome="";
	string conteudo="";
};

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
			flagLexic=false;
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
			cout << token << " -- Keyword " << endl; //auxToken.linha << " Coluna " << auxToken.coluna << endl;
			auxToken.nomeToken=token;
			auxToken.valorToken="Keyword";
			listaTokens.push_back(auxToken);
			}
		else {
			cout << token << " -- Identify " << endl; //auxToken.linha << " Coluna " << auxToken.coluna << endl;
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
			flagLexic=false;
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

void showstack(stack <int> pilha){ 
    while (!pilha.empty()){ 
        cout << '\t' << pilha.top(); 
        pilha.pop();} 
    cout << '\n'; 
} 

void empilha(int token, string auxItem){
	int auxEstado=stoi(auxItem);
	pilha.push(token);
	pilha.push(auxEstado);
	listaTokens.erase(listaTokens.begin());
}

void reduce1(){
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="PROGRAMA";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce2(){
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="PROGRAMA";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce3(){
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="DECLARACAO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce4(){
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="DECLARACAO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce5(){
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="BLOCO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce6(){
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="BLOCO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce7(){	
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO2";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce8(){
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO2";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce9(){
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce10(){
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce11(){
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce12(){
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce13(){
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce14(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="ITERACAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce15(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="LACO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce16(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICIONAL";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce17(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICIONAL";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce18(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICIONAL2";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce19(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICIONAL2";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce20(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce); 
}

void reduce21(){
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce22(){
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="INSTRUCAO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce23(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce24(){
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce25(){
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce26(){
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce27(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce28(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce29(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
	pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce30(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce31(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce32(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce33(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce34(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
} 

void reduce35(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce36(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}


void reduce37(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}


void reduce38(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}


void reduce39(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce40(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce41(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}


void reduce42(){
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce43(){
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="ID";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void reduce44(){
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="NUMERO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
}

void syntatic(){
	int token,estado;
	string itemTabSlr,auxItem,tokenLower;
	
	for(int i=0; i<listaTokens.size(); i++){
		tokenLower=listaTokens[i].nomeToken;
		transform(tokenLower.begin(), tokenLower.end(), tokenLower.begin(), ::tolower);
		listaTokens[i].nomeToken=tokenLower;
		
		if((listaTokens[i].valorToken.compare("Keyword")==0)){
			listaTokens[i].tipoToken=listaTokens[i].nomeToken;}
		if((listaTokens[i].valorToken.compare("Identify")==0)){
			listaTokens[i].tipoToken="identify";}
		if((listaTokens[i].valorToken.compare("Number")==0)){
			listaTokens[i].tipoToken="number";}
			
	}
	int x=0;
	while((!listaTokens.empty()) && (!flagSintatico)){
	//top da pilha inicia com 0
	estado=pilha.top();
	//valor do token no map auxiliar
	token=mapSimboAux[listaTokens.front().tipoToken]; 
	//acao na tabela dado a leitura do token
	itemTabSlr=matrizSlr[estado][token];	
	//caso o primeiro elemento seja s
	if(itemTabSlr[0]=='s'){
		//remove s and convert state for int
		auxItem=itemTabSlr.erase(0,1);
		empilha(estado,auxItem);
	}
	else if((itemTabSlr[0]>='0') && (itemTabSlr[0]<='9')){
		empilha(estado,itemTabSlr);
	}
	//estado de aceitacao
	else if((itemTabSlr.compare("acc")==0)){
		cout << "Aceito " <<endl;
		flagSintatico=true;
		x=999;
		break;}

	//estado de reduz
	else if(itemTabSlr[0]=='r'){
		if((itemTabSlr.compare("r1")==0)){
			reduce1(); 
		}

		else if((itemTabSlr.compare("r2")==0)){
			reduce2();
		}

		else if((itemTabSlr.compare("r3")==0)){
			reduce3();
		}

		else if((itemTabSlr.compare("r4")==0)){
			reduce4();
		}

		else if((itemTabSlr.compare("r5")==0)){
			reduce5(); 
		}

		else if((itemTabSlr.compare("r6")==0)){
			reduce6();
		}

		else if((itemTabSlr.compare("r7")==0)){
			reduce7();
		}

		else if((itemTabSlr.compare("r8")==0)){
			reduce8();
		}

		else if((itemTabSlr.compare("r9")==0)){
			reduce9();
		}

		else if((itemTabSlr.compare("r10")==0)){
			reduce10();
		}

		else if((itemTabSlr.compare("r11")==0)){
			reduce11();
		}

		else if((itemTabSlr.compare("r12")==0)){
			reduce12();
		}

		else if((itemTabSlr.compare("r13")==0)){
			reduce13();
		}

		else if((itemTabSlr.compare("r14")==0)){
			reduce14();
		}

		else if((itemTabSlr.compare("r15")==0)){
			reduce15();
		}

		else if((itemTabSlr.compare("r16")==0)){
			reduce16();
		}

		else if((itemTabSlr.compare("r17")==0)){
			reduce17();
		}

		else if((itemTabSlr.compare("r18")==0)){
			reduce18();
		}

		else if((itemTabSlr.compare("r19")==0)){
			reduce19();
		}

		else if((itemTabSlr.compare("r20")==0)){
			reduce20();
		}

		else if((itemTabSlr.compare("r21")==0)){
			reduce21();
		}

		else if((itemTabSlr.compare("r22")==0)){
			reduce22();
		}

		else if((itemTabSlr.compare("r23")==0)){
			reduce23();
		}

		else if((itemTabSlr.compare("r24")==0)){
			reduce24();
		}

		else if((itemTabSlr.compare("r25")==0)){
			reduce25();
		}

		else if((itemTabSlr.compare("r26")==0)){
			reduce26();
		}

		else if((itemTabSlr.compare("r27")==0)){
			reduce27();
		}

		else if((itemTabSlr.compare("r28")==0)){
			reduce28();
		}

		else if((itemTabSlr.compare("r29")==0)){
			reduce29();
		}

		else if((itemTabSlr.compare("r30")==0)){
			reduce30();
		}

		else if((itemTabSlr.compare("r31")==0)){
			reduce31();
		}

		else if((itemTabSlr.compare("r32")==0)){
			reduce32();
		}

		else if((itemTabSlr.compare("r33")==0)){
			reduce33();
		}

		else if((itemTabSlr.compare("r34")==0)){
			reduce34();
		}

		else if((itemTabSlr.compare("r35")==0)){
			reduce35();
		}

		else if((itemTabSlr.compare("r36")==0)){
			reduce36();
		}

		else if((itemTabSlr.compare("r37")==0)){
			reduce37();
		}

		else if((itemTabSlr.compare("r38")==0)){
			reduce38();
		}

		else if((itemTabSlr.compare("r39")==0)){
			reduce39();
		}

		else if((itemTabSlr.compare("r40")==0)){
			reduce40();
		}

		else if((itemTabSlr.compare("r41")==0)){
			reduce41();
		}

		else if((itemTabSlr.compare("r42")==0)){
			reduce42();
		}

		else if((itemTabSlr.compare("r43")==0)){
			reduce43();
		}

		else if((itemTabSlr.compare("r44")==0)){
			reduce44();	
		}
	}
	else{
		cout<<"Erro Sintatico encontrado no Token '" << listaTokens.front().nomeToken << "' Linha (" << listaTokens.front().linha << ") Coluna ("<< listaTokens.front().coluna << ")" << endl;
		break;		
	}
	x++;
	}
}

void imprimeTokens(){
	for (int i = 0; i < listaTokens.size(); i++){
	 cout<<"\n"<<listaTokens[i].nomeToken<<" "<<listaTokens[i].valorToken<<"\n";
	 cout<<listaTokens[i].linha<<" "<<listaTokens[i].coluna<<" "<<listaTokens[i].tipoToken<<"\n";
	}
}

void semantic(){
}

/*
void generatorCode(){

0 00000000 Não	executa	qualquer	ação.
1 00000001 Movimenta	para	frente.
2 00000010 Vira	para	esquerda.
3 00000011 Vira	para	direita.
4 00000100 Examina	um	objeto	usando	o	sensor.	Quando	a	tarefa	é	finalizada,	armazena	o	resultado	no	
registrador	de	dados	e	um	bit	1	no	registrador	de	estado.
5 00000101 Acende	uma	lâmpada
6 00000110 Apaga	uma	lâmpada

##Registrador de dados
255 11111111 Parede	à	frente
0 00000000 Nada	em	frente
7 00000111 Lâmpada	acessa	a	frente
8 00001000 Lâmpada	apagada	a	frente
9 00001001 Lâmpada	acessa	a	esquerda
10 00001010 Lâmpada	apagada	a	esquerda
11 00001011 Lâmpada	acessa	a	direita
12 00001100 Lâmpada	apagada	a	direita
240 11110000 Parede	à	esquerda
15 00001111 Parede	à	direita

//	for (int i = 0; i < listaTkGeraCodigo.size(); i++){
//		if(listaTkGeraCodigo)
//	}
	
	string foundS="vire";
	iterVec = find (listaTkGeraCodigo.begin(), listaTkGeraCodigo.end(), foundS); 
    if (iterVec != listaTkGeraCodigo.end()) { 
        cout << "Element " << foundS <<" found at position : " ; 
        cout << iterVec - listaTkGeraCodigo.begin() + 1 << "\n" ; 
    } 
    else
        cout << "Element not found.\n\n"; 

	//mapSimboAux[""]=0;

}

*/

void convertLowCase(){
	string tokenLow;

	for(int i=0; i<listaTkSemantico.size(); i++){
		tokenLow=listaTkSemantico[i].nomeToken;
		transform(tokenLow.begin(), tokenLow.end(), tokenLow.begin(), ::tolower);
		listaTkSemantico[i].nomeToken=tokenLow;
	}
}


int main(int argc, const char** argv) {
	string padrao;
	int linhaCursor=1,j=0,palRepeat=0,posicRepeat=0; 
	char leitura[Tam_Maximo];
	Lexema auxListToken;
	bool flagSemantic=true;
	

	int tamanhoLeitura = fread(leitura, sizeof(char), Tam_Maximo, stdin);

	for (int i=0; i < tamanhoLeitura; i++){
		if ((leitura[i]>126)){
		cout<<"erro Linha " << linhaCursor << " Coluna "  << i+1 << endl;
		return 0;}
	}

	//Inicio do analisador lexico
	cout << endl << "---ANALISADOR LEXICO---" << endl << endl;

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
					flagLexic=false;
					tratarOtherSymbols(leitura);
				}
				else{
					cout<<"Erro Encontrado no Caractere Desconhecido: " << lido << " Na Linha "<< linha << " Coluna " << coluna+1 << endl;
					flagLexic=false;
					tratarOtherSymbols(leitura);
				}		
			}
		q++;
	}

	//INICIO DO ANALISADOR SINTATICO

	cout << endl;

	mapSimboAux["programainicio"]=0;
	mapSimboAux["execucaoinicio"]=1;
	mapSimboAux["fimexecucao"]=2;
	mapSimboAux["fimprograma"]=3;
	mapSimboAux["definainstrucao"]=4;
	mapSimboAux["como"]=5;
	mapSimboAux["inicio"]=6;
	mapSimboAux["fim"]=7;
	mapSimboAux["repita"]=8;
	mapSimboAux["vezes"]=9;
	mapSimboAux["fimrepita"]=10;
	mapSimboAux["enquanto"]=11;
	mapSimboAux["faca"]=12;
	mapSimboAux["fimpara"]=13;
	mapSimboAux["se"]=14;
	mapSimboAux["entao"]=15;
	mapSimboAux["fimse"]=16;
	mapSimboAux["senao"]=17;
	mapSimboAux["fimsenao"]=18;
	mapSimboAux["mova"]=19;
	mapSimboAux["passos"]=20;
	mapSimboAux["vire"]=21;
	mapSimboAux["para"]=22;
	mapSimboAux["direita"]=23;
	mapSimboAux["esquerda"]=24;
	mapSimboAux["pare"]=25;
	mapSimboAux["finalize"]=26;
	mapSimboAux["apague"]=27;
	mapSimboAux["lampada"]=28;
	mapSimboAux["acenda"]=29;
	mapSimboAux["aguarde"]=30;
	mapSimboAux["ate"]=31;
	mapSimboAux["robo"]=32;
	mapSimboAux["pronto"]=33;
	mapSimboAux["ocupado"]=34;
	mapSimboAux["parado"]=35;
	mapSimboAux["movimentando"]=36;
	mapSimboAux["frente"]=37;
	mapSimboAux["bloqueada"]=38;
	mapSimboAux["acessa"]=39;
	mapSimboAux["a"]=40;
	mapSimboAux["apagada"]=41;
	mapSimboAux["identify"]=42;
	mapSimboAux["number"]=43;
	mapSimboAux["$"]=44;
	mapSimboAux["PROGRAMA’"]=45;
	mapSimboAux["PROGRAMA"]=46;
	mapSimboAux["DECLARACAO"]=47;
	mapSimboAux["BLOCO"]=48;
	mapSimboAux["COMANDO2"]=49;
	mapSimboAux["COMANDO"]=50;
	mapSimboAux["ITERACAO"]=51;
	mapSimboAux["LACO"]=52;
	mapSimboAux["CONDICIONAL"]=53;
	mapSimboAux["CONDICIONAL2"]=54;
	mapSimboAux["INSTRUCAO"]=55;
	mapSimboAux["CONDICAO"]=56;
	mapSimboAux["ID"]=57;
	mapSimboAux["NUMERO"]=58;

	auxListToken.tipoToken="$";
	listaTokens.push_back(auxListToken);
	pilha.push(0);
	listaTkSemantico=listaTokens;

	if(flagLexic){
		cout << "Analise Léxica concluida com sucesso!!" << endl << endl;
		cout << "---ANALISADOR SINTATICO---" << endl << endl;
		syntatic();
	}
	
	//Inicio do analisador Semantico
	if(flagSintatico){
		cout << endl <<"---ANALISADOR SEMANTICO---" << endl << endl;
			for (int i = 0; i < listaTkSemantico.size(); i++){
				convertLowCase(); 
				if((listaTkSemantico[i].nomeToken.compare("vire")==0) && (listaTkSemantico[i+1].nomeToken.compare("para")==0)){
					if(listaTkSemantico[i+2].nomeToken.compare("esquerda")==0){
							if((listaTkSemantico[i+3].nomeToken.compare("vire")==0) && (listaTkSemantico[i+4].nomeToken.compare("para")==0)){
								if(listaTkSemantico[i+5].nomeToken.compare("direita")==0){
									cout << "ERRO SEMANTICO !! COMANDO NAO ESPERADO FOI ENCONTRADO NA LINHA(" << listaTkSemantico[i+5].linha << ") Coluna(" << listaTkSemantico[i+5].coluna <<") " << endl;
									flagSemantic=false;
									}
							}
					}
					if(listaTkSemantico[i+2].nomeToken.compare("direita")==0){
							if((listaTkSemantico[i+3].nomeToken.compare("vire")==0) && (listaTkSemantico[i+4].nomeToken.compare("para")==0)){
								if(listaTkSemantico[i+5].nomeToken.compare("esquerda")==0){
									cout << "ERRO SEMANTICO !! COMANDO NAO ESPERADO FOI ENCONTRADO NA LINHA (" << listaTkSemantico[i+5].linha << ") Coluna(" << listaTkSemantico[i+5].coluna <<") " << endl;
									flagSemantic=false;
									}
							}
					}
				}
				if((listaTkSemantico[i].nomeToken.compare("mova")==0) && (listaTkSemantico[i+1].valorToken.compare("Number")==0)){
							if((listaTkSemantico[i+3].nomeToken.compare("aguarde")!=0)){
									cout << "ERRO SEMANTICO RELACIONADO A INSTRUCAO MOVA!! COMANDO NAO ESPERADO FOI ENCONTRADO NA LINHA(" << listaTkSemantico[i+3].linha << ") Coluna(" << listaTkSemantico[i+3].coluna <<") " << endl;
									flagSemantic=false;
							}
					}
			}
		for(int i=0; i < listaTkSemantico.size(); i++){
				if(listaTkSemantico[i].valorToken.compare("Identify")==0){
					for (int j=i+1; j<listaTkSemantico.size(); i++){
							if(listaTkSemantico[i].nomeToken.compare(listaTkSemantico[j].nomeToken)==0){
								palRepeat++;
								posicRepeat=j-1;
								break;
							}
					}
				}
		}
		if(palRepeat>0){
			cout << "ERRO SEMANTICO ENCONTRADO !! Identificador '" << listaTkSemantico[posicRepeat].nomeToken << "' Repetido Encontrado !! Na Linha (" << listaTkSemantico[posicRepeat].linha <<")" << endl;	
			flagSemantic=false;	
		}
	}
	//Geracao de codigo
	if(flagSemantic){
		listaTkGeraCodigo=listaTkSemantico;
		//cout<< "Geração de código concluido" << endl;
		//generatorCode();
	}
}
