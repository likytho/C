//Librerías necesarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Definimos la estructura de las cartas
typedef struct Naipe{
  char palo;
  int num;
  int vis; 
} naipe;

//Prototipos de las funciones utilizadas.
int arreglarJugada(char[50], char[50]);
int comprobarSintaxis(char[50], char[50], char[50], char[50], int, int, int, int);
int comprobarMovimiento(naipe[14][48], int, int, int, int);
int controlJuego(naipe[14][48]);
int cargarJuego(naipe[14][48]);
int guardarJuego(naipe[14][48]);
void crearMazo(naipe[14][48]);
void barajarMazo(naipe[14][48]);
void repartirMazo(naipe[14][48]);
void imprimirTapete(naipe[14][48]);
int jugar(naipe[14][48]);
void limpiarJuego(char[50], char[50], char[50], char[50], char[50],naipe[14][48]);
void separarParametros(char[50], char[50], char[50], char[50], int);
void ejecutarMovimiento(naipe[14][48], int, int, int);

//Define funciones para el control del puntero del terminal en la pantalla.
#define gotoxy(x,y) printf("\x1b[%d;%dH",(y),(x))
#define moveup(x) printf("\x1b[%dA",(x))
#define movedown(x) printf("\x1b[%dB",(x))
#define moveright(y) printf("\x1b[%dC",(y))
#define moveleft(y) printf("\x1b[%dD",(y))

