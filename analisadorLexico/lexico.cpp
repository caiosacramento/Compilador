/* #include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <locale.h>*/
#include <bits/stdc++.h>
#include <algorithm>    // std::binary_search, std::sort
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
vector<Lexema>listaTkSemantico;
map <string,int> mapSimboAux; 
stack <int> pilha;

Lexema auxReduce;
bool flagSintatico=false;

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

void showstack(stack <int> pilha){ 
    while (!pilha.empty()){ 
        cout << '\t' << pilha.top(); 
        pilha.pop();} 
    cout << '\n'; 
} 

void empilha(int token, string auxItem){
	
	//cout << "Empilha ";
	//cout << "token " << token << endl;
	//cout << "auxItem " << auxItem << endl;

	int auxEstado=stoi(auxItem);
	pilha.push(token);
	pilha.push(auxEstado);
	listaTokens.erase(listaTokens.begin());
	//listaTokens.erase(listaTokens.begin(), listaTokens.begin() + 1); 
	//cout << "Estado SHIFT INTEIRO: " << auxEstado << endl;
}

//testado
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
	////showstack(pilha);
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
	////showstack(pilha);
}

//testar reduce
void reduce3(){
	//showstack(pilha);
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
	//showstack(pilha);
}

//testado
void reduce4(){
	//showstack(pilha);
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
	//showstack(pilha);
}

//testado
void reduce5(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="BLOCO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//testar reduce
void reduce6(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="BLOCO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//testado
void reduce7(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO2";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//testado
void reduce8(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO2";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//testado
void reduce9(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//falta testar
void reduce10(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//falta testar
void reduce11(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//testado
void reduce12(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//testado
void reduce13(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="COMANDO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//falta testar
void reduce14(){
	//showstack(pilha);
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
    //showstack(pilha);
}

//falta testar
void reduce15(){
    //showstack(pilha);
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
    //showstack(pilha);
}

//testado
void reduce16(){
    //showstack(pilha);
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
    //showstack(pilha);
}

//testado
void reduce17(){
   //showstack(pilha);
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
    //showstack(pilha);
}

//falta testar
void reduce18(){
    //showstack(pilha);
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
    //showstack(pilha);
}

//testado 
void reduce19(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICIONAL2";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha); 
}

//testado
void reduce20(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
 
}

//falta testar
void reduce21(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//testado
void reduce22(){
	//showstack(pilha);
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	pilha.pop();
	auxReduce.tipoToken ="INSTRUCAO";
	listaTokens.insert(listaTokens.begin(), auxReduce);
	//showstack(pilha);
}

//testado
void reduce23(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce24(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce25(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce26(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//testado
void reduce27(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce28(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//testado
void reduce29(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
	pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="INSTRUCAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//testado
void reduce30(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce31(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce32(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce33(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce34(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}
 
//falta testar
void reduce35(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce36(){
    //showstack(pilha);
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="CONDICAO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);
}

//falta testar
void reduce37(){
    //showstack(pilha);
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
    //showstack(pilha);
}

//falta testar
void reduce38(){
    //showstack(pilha);
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
    //showstack(pilha);
}

//falta testar
void reduce39(){
    //showstack(pilha);
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
    //showstack(pilha); 
}

//falta testar
void reduce40(){
    //showstack(pilha);
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
    //showstack(pilha);
}

//falta testar
void reduce41(){
    //showstack(pilha);
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
    //showstack(pilha); 
}

//falta testar
void reduce42(){
    //showstack(pilha);
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
    //showstack(pilha); 
}

//testado
void reduce43(){
   //showstack(pilha);
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="ID";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha);    
}

//testado
void reduce44(){
	//showstack(pilha);
    pilha.pop();
    pilha.pop();
    auxReduce.tipoToken ="NUMERO";
    listaTokens.insert(listaTokens.begin(), auxReduce);
    //showstack(pilha); 
}




void syntatic(){
int token,estado;
string itemTabSlr,auxItem,tokenLower;

for(int i=0; i<listaTokens.size(); i++){
	//auxila na impressao da lista de tokens
	//cout<<"\n"<<listaTokens[i].nomeToken<<" "<<listaTokens[i].valorToken<<"\n";
	//cout<<listaTokens[i].linha<<" "<<listaTokens[i].coluna<<" "<<listaTokens[i].tipoToken<<"\n";
	//transformar em minuscula		
	tokenLower=listaTokens[i].nomeToken;
	transform(tokenLower.begin(), tokenLower.end(), tokenLower.begin(), ::tolower);
	listaTokens[i].nomeToken=tokenLower;
	
	if((listaTokens[i].valorToken.compare("Keyword")==0)){
		listaTokens[i].tipoToken=listaTokens[i].nomeToken;}
	if((listaTokens[i].valorToken.compare("Identify")==0)){
		listaTokens[i].tipoToken="identify";}
	if((listaTokens[i].valorToken.compare("Number")==0)){
		listaTokens[i].tipoToken="number";}

	//cout <<"tipo Token: "<<listaTokens[i].tipoToken<<endl;
		
}
	int x=0;

	//for(int i=0 ; i<listaTokens.size();i++){
	//while(x!=999){ 
	while((!listaTokens.empty()) && (!flagSintatico)){
	//while(x<25){ 
	//cout << "Analisando " << listaTokens.front().nomeToken << endl;
	//top da pilha inicia com 0
	estado=pilha.top();
	//valor do token no map auxiliar
	//token=mapSimboAux[listaTokens[i].nomeToken];
	
	token=mapSimboAux[listaTokens.front().tipoToken]; 
	//cout<<"Estado na tabela: " << estado << " token na tabela: " << token  << endl;
	//acao na tabela dado a leitura do token
	
	//cout << "Estado valor " << estado << endl;
	//cout << "Token valor " << token << endl;
	//cout << "Nome " << listaTokens.front().nomeToken << endl;

	itemTabSlr=matrizSlr[estado][token];	
	
	//cout<<"Item da tabela: " << itemTabSlr << endl;
	
	//caso o primeiro elemento seja s
	if(itemTabSlr[0]=='s'){
		//remove s and convert state for int
		auxItem=itemTabSlr.erase(0,1);
		empilha(estado,auxItem);
		////showstack(pilha);		
		//listaTokens.erase(listaTokens[i]);
	}
	else if((itemTabSlr[0]>='0') && (itemTabSlr[0]<='9')){
		empilha(estado,itemTabSlr);
		////showstack(pilha);
		//listaTokens.erase(listaTokens.begin());
		//listaTokens.erase(listaTokens.begin());
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
			//cout << "Ja foi FEITO R1"<< endl;
		}

		else if((itemTabSlr.compare("r2")==0)){
			reduce2();
			//cout << "Falta implementar R2"<< endl;
		}

		else if((itemTabSlr.compare("r3")==0)){
			reduce3();
			//cout << "Falta implementar R3"<< endl;
		}

		else if((itemTabSlr.compare("r4")==0)){
			reduce4();
			//cout << "Falta implementar R4"<< endl;
		}

		else if((itemTabSlr.compare("r5")==0)){
			reduce5(); 
			//cout << "Falta implementar R5"<< endl;
		}

		else if((itemTabSlr.compare("r6")==0)){
			reduce6();
			//cout << "Falta implementar R6"<< endl;
		}

		else if((itemTabSlr.compare("r7")==0)){
			reduce7();
			//cout << "Falta implementar R7"<< endl;

		}

		else if((itemTabSlr.compare("r8")==0)){
			reduce8();
			//cout << "Falta implementar R8"<< endl;
		}

		else if((itemTabSlr.compare("r9")==0)){
			reduce9();
			//cout << "Falta implementar R9"<< endl;
		}

		else if((itemTabSlr.compare("r10")==0)){
			reduce10();
			//cout << "Falta implementar R10"<< endl;
		}

		else if((itemTabSlr.compare("r11")==0)){
			reduce11();
			//cout << "Falta implementar R11"<< endl;
		}

		else if((itemTabSlr.compare("r12")==0)){
			reduce12();
			//cout << "Falta implementar R12"<< endl;
		}

		else if((itemTabSlr.compare("r13")==0)){
			reduce13();
			//cout << "Falta implementar R13"<< endl;
		}

		else if((itemTabSlr.compare("r14")==0)){
			reduce14();
			//cout << "Falta implementar R14"<< endl;
		}

		else if((itemTabSlr.compare("r15")==0)){
			reduce15();
			//cout << "Falta implementar R15"<< endl;
		}

		else if((itemTabSlr.compare("r16")==0)){
			reduce16();
			//cout << "Falta implementar R16"<< endl;
		}

		else if((itemTabSlr.compare("r17")==0)){
			reduce17();
			//cout << "Falta implementar R17"<< endl;
		}

		else if((itemTabSlr.compare("r18")==0)){
			reduce18();
			//cout << "Falta implementar R18"<< endl;
		}

		else if((itemTabSlr.compare("r19")==0)){
			reduce19();
			//cout << "Falta implementar R19"<< endl;
		}

		else if((itemTabSlr.compare("r20")==0)){
			reduce20();
			//cout << "Falta implementar R20"<< endl;
		}

		else if((itemTabSlr.compare("r21")==0)){
			reduce21();
			//cout << "Falta implementar R21"<< endl;
		}

		else if((itemTabSlr.compare("r22")==0)){
			reduce22();
		}

		else if((itemTabSlr.compare("r23")==0)){
			reduce23();
			//cout << "Falta implementar R23"<< endl;
		}

		else if((itemTabSlr.compare("r24")==0)){
			reduce24();
			//cout << "Falta implementar R24"<< endl;
		}

		else if((itemTabSlr.compare("r25")==0)){
			reduce25();
			//cout << "Falta implementar R25"<< endl;
		}

		else if((itemTabSlr.compare("r26")==0)){
			reduce26();
			//cout << "Falta implementar R26"<< endl;
		}

		else if((itemTabSlr.compare("r27")==0)){
			reduce27();
			//cout << "Falta implementar R27"<< endl;
		}

		else if((itemTabSlr.compare("r28")==0)){
			reduce28();
			//cout << "Falta implementar R28"<< endl;
		}

		else if((itemTabSlr.compare("r29")==0)){
			reduce29();
			//cout << "Falta implementar R29"<< endl;
		}

		else if((itemTabSlr.compare("r30")==0)){
			reduce30();
			//cout << "Falta implementar R30"<< endl;
		}

		else if((itemTabSlr.compare("r31")==0)){
			reduce31();
			//cout << "Falta implementar R31"<< endl;
		}

		else if((itemTabSlr.compare("r32")==0)){
			reduce32();
			//cout << "Falta implementar R32"<< endl;
		}

		else if((itemTabSlr.compare("r33")==0)){
			reduce33();
			//cout << "Falta implementar R33"<< endl;
		}

		else if((itemTabSlr.compare("r34")==0)){
			reduce34();
			//cout << "Falta implementar R34"<< endl;
		}

		else if((itemTabSlr.compare("r35")==0)){
			reduce35();
			//cout << "Falta implementar R35"<< endl;
		}

		else if((itemTabSlr.compare("r36")==0)){
			reduce36();
			//cout << "Falta implementar R36"<< endl;
		}

		else if((itemTabSlr.compare("r37")==0)){
			reduce37();
			//cout << "Falta implementar R37"<< endl;
		}

		else if((itemTabSlr.compare("r38")==0)){
			reduce38();
			//cout << "Falta implementar R38"<< endl;
		}

		else if((itemTabSlr.compare("r39")==0)){
			reduce39();
			//cout << "Falta implementar R39"<< endl;
		}

		else if((itemTabSlr.compare("r40")==0)){
			reduce40();
			//cout << "Falta implementar R40"<< endl;
		}

		else if((itemTabSlr.compare("r41")==0)){
			reduce41();
			//cout << "Falta implementar R41"<< endl;
		}

		else if((itemTabSlr.compare("r42")==0)){
			reduce42();
			//cout << "Falta implementar R42"<< endl;
		}

		else if((itemTabSlr.compare("r43")==0)){
			reduce43();
			//cout << "Falta implementar R43"<< endl;
		}

		else if((itemTabSlr.compare("r44")==0)){
			reduce44();	
			//cout << "Falta implementar R44"<< endl;
		}
	}
	else{
		cout<<"Erro Sintatico encontrado no Token '" << listaTokens.front().nomeToken << "' Linha (" << listaTokens.front().linha << ") Coluna ("<< listaTokens.front().coluna << ")" << endl;
		break;		
	}
	
	x++;

	//lerEstado=slr.top(); ler o top da pilha
	//lerToken=mapaSimbolos[listaTokens.front().tokenName];
	//lerMatriz=matrizSlr[lerEstado][lerToken];
	//if(listaTokens[i].valorToken == mapSimboAux->first )
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


int tamanhoLeitura = fread(leitura, sizeof(char), Tam_Maximo, stdin);

for (int i=0; i < tamanhoLeitura; i++){
	if ((leitura[i]>126)){
	cout<<"erro Linha " << linhaCursor << " Coluna "  << i+1 << endl;
	return 0;}
}

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
				tratarOtherSymbols(leitura);
			}
			else{
				cout<<"Erro Encontrado no Caractere Desconhecido: " << lido << " Na Linha "<< linha << " Coluna mais um " << coluna+1 << endl;
				tratarOtherSymbols(leitura);
			}		
		}
	q++;
}

//INICIO DO ANALISADOR SINTATICO

cout << endl << endl;

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

cout << "---ANALISADOR SINTATICO---" << endl << endl;

syntatic();

//cout << "Sintatic Lista Tokens Tamanho: " << listaTokens.size() << endl;
//cout << "Lista de Tokens " << endl;
//imprimeTokens();
////showstack(pilha);

cout << endl <<"---ANALISADOR SEMANTICO---" << endl << endl;

if(flagSintatico){
	//semantic();
	cout << "Concluiu sintatico" << endl;
	for (int i = 0; i < listaTkSemantico.size(); i++){
		convertLowCase(); 
		if((listaTkSemantico[i].nomeToken.compare("vire")==0) && (listaTkSemantico[i+1].nomeToken.compare("para")==0)){
			if(listaTkSemantico[i+2].nomeToken.compare("esquerda")==0){
					if((listaTkSemantico[i+3].nomeToken.compare("vire")==0) && (listaTkSemantico[i+4].nomeToken.compare("para")==0)){
						if(listaTkSemantico[i+5].nomeToken.compare("direita")==0){
							cout << "ERRO SEMANTICO !! COMANDO NAO ESPERADO FOI ENCONTRADO NA LINHA(" << listaTkSemantico[i+5].linha << ") Coluna(" << listaTkSemantico[i+5].coluna <<") " << endl;}
					}
			}
			if(listaTkSemantico[i+2].nomeToken.compare("direita")==0){
					if((listaTkSemantico[i+3].nomeToken.compare("vire")==0) && (listaTkSemantico[i+4].nomeToken.compare("para")==0)){
						if(listaTkSemantico[i+5].nomeToken.compare("esquerda")==0){
							cout << "ERRO SEMANTICO !! COMANDO NAO ESPERADO FOI ENCONTRADO NA LINHA (" << listaTkSemantico[i+5].linha << ") Coluna(" << listaTkSemantico[i+5].coluna <<") " << endl;}
					}
			}
		}
		if((listaTkSemantico[i].nomeToken.compare("mova")==0) && (listaTkSemantico[i+1].valorToken.compare("Number")==0)){
					if((listaTkSemantico[i+3].nomeToken.compare("aguarde")!=0)){
							cout << "ERRO SEMANTICO !! COMANDO NAO ESPERADO FOI ENCONTRADO NA LINHA(" << listaTkSemantico[i+3].linha << ") Coluna(" << listaTkSemantico[i+3].coluna <<") " << endl;
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
  }

}
}