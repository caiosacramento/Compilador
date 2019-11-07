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

string matrizSlr[93][64]={ 

{"s2"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","1"," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","acc"," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","s4"," "," ","s5"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","3"," "," "," "," "," "," "," "," "," "," "," "},
{" ","s6"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","7","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," "," "," "," "," "," "," "," "," "," ","26"," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","27","9","10","11"," ","12"," "," ","19"," "},
{" "," ","s28"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","29","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","30","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","31","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","32","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","33","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," ","s13","s35","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","34","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s37"," "," "," "," "," "," "," "," "," "," "," "," "," "," ","36"},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s41","s42"," "," "," ","s44"," "," "," ","s39"," "," "," "," ","s40","s43"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","38"," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s41","s42"," "," "," ","s44"," "," "," ","s39"," "," "," "," ","s40","s43"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","45"," "," "},
{" "," "," "," "," "," ","r19"," ","r19"," "," ","r19"," "," ","r19"," "," "," "," ","r19","s46"," ","r19"," "," "," ","r19","r19","r19"," ","r19","r19"," "," "," "," "," "," "," "," "," "," "," ","r19"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s47"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r22"," ","r22"," "," ","r22"," "," ","r22"," "," "," "," ","r22"," "," ","r22"," "," "," ","r22","r22","r22"," ","r22","r22"," "," "," "," "," "," "," "," "," "," "," ","r22"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r23"," ","r23"," "," ","r23"," "," ","r23"," "," "," "," ","r23"," "," ","r23"," "," "," ","r23","r23","r23"," ","r23","r23"," "," "," "," "," "," "," "," "," "," "," ","r23"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r24"," ","r24"," "," ","r24"," "," ","r24"," "," "," "," ","r24"," "," ","r24"," "," "," ","r24","r24","r24"," ","r24","r24"," "," "," "," "," "," "," "," "," "," "," ","r24"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s48"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s49"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s50"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," ","r42","r42"," ","r42"," "," ","r42"," "," ","r42"," "," "," "," ","r42"," "," ","r42"," "," "," ","r42","r42","r42"," ","r42","r42"," "," "," "," "," "," "," "," "," "," "," ","r42"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," ","s51"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," ","s52"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," ","s53"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r7","r7"," ","r7"," "," ","r7"," "," ","r7"," "," ","r7"," "," ","r7"," ","r7"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r8","r8"," ","r8"," "," ","r8"," "," ","r8"," "," ","r8"," "," ","r8"," ","r8"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r9","r9"," ","r9"," "," ","r9"," "," ","r9"," "," ","r9"," "," ","r9"," ","r9"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r10","r10"," ","r10"," "," ","r10"," "," ","r10"," "," ","r10"," "," ","r10"," ","r10"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r11","r11"," ","r11"," "," ","r11"," "," ","r11"," "," ","r11"," "," ","r11"," ","r11"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," ","s54"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r6"," ","r6"," "," ","r6"," "," ","r6"," "," "," "," ","r6"," "," ","r6"," "," "," ","r6","r6","r6"," ","r6","r6"," "," "," "," "," "," "," "," "," "," "," ","r6"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," ","s55"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," ","r43"," "," "," "," "," "," "," "," "," "," "," ","r43"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","s56"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s57","s58","s59","s60"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s61"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s62"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s63"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r35"," "," ","r35"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s64"," ","s65"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s66"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r17"," ","r17"," "," ","r17"," "," ","r17"," "," "," "," ","r17"," "," ","r17"," "," "," ","r17","r17","r17"," ","r17","r17"," "," "," "," "," "," "," "," "," "," "," ","r17"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s67","s68"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r25"," ","r25"," "," ","r25"," "," ","r25"," "," "," "," ","r25"," "," ","r25"," "," "," ","r25","r25","r25"," ","r25","r25"," "," "," "," "," "," "," "," "," "," "," ","r25"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r26"," ","r26"," "," ","r26"," "," ","r26"," "," "," "," ","r26"," "," ","r26"," "," "," ","r26","r26","r26"," ","r26","r26"," "," "," "," "," "," "," "," "," "," "," ","r26"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r27"," ","r27"," "," ","r27"," "," ","r27"," "," "," "," ","r27"," "," ","r27"," "," "," ","r27","r27","r27"," ","r27","r27"," "," "," "," "," "," "," "," "," "," "," ","r27"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","69","9","10","11"," ","12"," "," ","19"," "},
{" "," "," ","s70"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","r2"," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r5"," ","r5"," "," ","r5"," "," ","r5"," "," "," "," ","r5"," "," ","r5"," "," "," ","r5","r5","r5"," ","r5","r5"," "," "," "," "," "," "," "," "," "," "," ","r5"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","71","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","72","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r28"," "," ","r28"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r29"," "," ","r29"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r30"," "," ","r30"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r31"," "," ","r31"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s73"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s74"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r34"," "," ","r34"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s75"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s76"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","77","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," ","r20"," ","r20"," "," ","r20"," "," ","r20"," "," "," "," ","r20"," "," ","r20"," "," "," ","r20","r20","r20"," ","r20","r20"," "," "," "," "," "," "," "," "," "," "," ","r20"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r21"," ","r21"," "," ","r21"," "," ","r21"," "," "," "," ","r21"," "," ","r21"," "," "," ","r21","r21","r21"," ","r21","r21"," "," "," "," "," "," "," "," "," "," "," ","r21"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r4"," "," ","s5"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","78"," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","r1"," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," ","s79"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," ","s80"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r32"," "," ","r32"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r33"," "," ","r33"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s83","s82"," "," "," "," "," "," "," "," "," "," "," "," ","s81"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s86","s85"," "," "," "," "," "," "," "," "," "," "," "," ","s84"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s87"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" ","r3"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r12"," ","r12"," "," ","r12"," "," ","r12"," "," "," "," ","r12"," "," ","r12"," "," "," ","r12","r12","r12"," ","r12","r12"," "," "," "," "," "," "," "," "," "," "," ","r12"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r13"," ","r13"," "," ","r13"," "," ","r13"," "," "," "," ","r13"," "," ","r13"," "," "," ","r13","r13","r13"," ","r13","r13"," "," "," "," "," "," "," "," "," "," "," ","r13"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r36"," "," ","r36"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r38"," "," ","r38"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r40"," "," ","r40"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r37"," "," ","r37"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r39"," "," ","r39"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," ","r41"," "," ","r41"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s89"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","88"," "," "," "," "," "},
{" "," "," "," "," "," ","r14"," ","r14"," "," ","r14"," "," ","r14"," "," "," "," ","r14"," "," ","r14"," "," "," ","r14","r14","r14"," ","r14","r14"," "," "," "," "," "," "," "," "," "," "," ","r14"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","s13"," ","s14"," "," ","s15"," "," ","s16"," "," "," "," ","s17"," "," ","s18"," "," "," ","s20","s21","s22"," ","s23","s24"," "," "," "," "," "," "," "," "," "," "," ","s25"," "," "," "," "," ","8","90","9","10","11"," ","12"," "," ","19"," "},
{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","s91"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
{" "," "," "," "," "," ","r16"," ","r16"," "," ","r16"," "," ","r16"," "," ","s89"," ","r16"," "," ","r16"," "," "," ","r16","r16","r16"," ","r16","r16"," "," "," "," "," "," "," "," "," "," "," ","r16"," "," "," "," "," "," "," "," "," "," ","92"," "," "," "," "," "},
{" "," "," "," "," "," ","r15"," ","r15"," "," ","r15"," "," ","r15"," "," "," "," ","r15"," "," ","r15"," "," "," ","r15","r15","r15"," ","r15","r15"," "," "," "," "," "," "," "," "," "," "," ","r15"," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},


};

map <string,int> mapSimboAux; 



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

void syntatic(){
int token;

for(int i=0; i<listaTokens.size(); i++){
	cout<<"\n"<<listaTokens[i].nomeToken<<" "<<listaTokens[i].valorToken<<"\n";
	cout<<listaTokens[i].linha<<" "<<listaTokens[i].coluna<<" "<<listaTokens[i].tipoToken<<"\n";
	if((listaTokens[i].valorToken.compare("Keyword")==0)){
		//token=mapSimboAux[listaTokens[i].nomeToken];
		//matrizSlr[]
		listaTokens[i].tipoToken=listaTokens[i].nomeToken;
	}
	if((listaTokens[i].valorToken.compare("Identify")==0)){
		listaTokens[i].tipoToken="identify";
		}
	if((listaTokens[i].valorToken.compare("Number")==0)){
		listaTokens[i].tipoToken="Number";
		}

	cout <<"tipo Token: "<<listaTokens[i].tipoToken<<endl;		
}
//if(listaTokens[i].valorToken == mapSimboAux->first )

}

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

mapSimboAux["programainicio"]=1;
mapSimboAux["execucaoinicio"]=2;
mapSimboAux["fimexecucao"]=3;
mapSimboAux["fimprograma"]=4;
mapSimboAux["definainstrucao"]=5;
mapSimboAux["como"]=6;
mapSimboAux["inicio"]=7;
mapSimboAux["fim"]=8;
mapSimboAux["repita"]=9;
mapSimboAux["vezes"]=10;
mapSimboAux["fimrepita"]=11;
mapSimboAux["enquanto"]=12;
mapSimboAux["faca"]=13;
mapSimboAux["fimpara"]=14;
mapSimboAux["se"]=15;
mapSimboAux["entao"]=16;
mapSimboAux["fimse"]=17;
mapSimboAux["senao"]=18;
mapSimboAux["fimsenao"]=19;
mapSimboAux["mova"]=20;
mapSimboAux["passos"]=21;
mapSimboAux["vire"]=22;
mapSimboAux["para"]=23;
mapSimboAux["direita"]=24;
mapSimboAux["esquerda"]=25;
mapSimboAux["pare"]=26;
mapSimboAux["finalize"]=27;
mapSimboAux["apague"]=28;
mapSimboAux["lampada"]=29;
mapSimboAux["acenda"]=30;
mapSimboAux["aguarde"]=31;
mapSimboAux["ate"]=32;
mapSimboAux["robo"]=33;
mapSimboAux["pronto"]=34;
mapSimboAux["ocupado"]=35;
mapSimboAux["parado"]=36;
mapSimboAux["movimentando"]=37;
mapSimboAux["frente"]=38;
mapSimboAux["bloqueada"]=39;
mapSimboAux["acessa"]=40;
mapSimboAux["a"]=41;
mapSimboAux["apagada"]=42;
mapSimboAux["identify"]=43;
mapSimboAux["number"]=44;
mapSimboAux["$"]=45;
mapSimboAux["PROGRAMA’"]=46;
mapSimboAux["PROGRAMA"]=47;
mapSimboAux["DECLARACAO"]=48;
mapSimboAux["BLOCO"]=49;
mapSimboAux["COMANDO2"]=50;
mapSimboAux["COMANDO"]=51;
mapSimboAux["ITERACAO"]=52;
mapSimboAux["LACO"]=53;
mapSimboAux["CONDICIONAL"]=54;
mapSimboAux["CONDICIONAL2"]=55;
mapSimboAux["INSTRUCAO"]=56;
mapSimboAux["CONDICAO"]=57;
mapSimboAux["ID"]=58;
mapSimboAux["NUMERO"]=59;

syntatic();

}
