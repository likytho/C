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
  int atributo;
} naipe;

typedef struct Pista{
  int origen;
  int destino;
  int cantidad;
} pista;

typedef struct Jugador{
  char nombre[20];
  int partidasIniciadas;
  int partidasCompletadas;
  int maximaPuntuacion;
  float porcentajeVictorias;
} jugador;

//Prototipos de las funciones utilizadas.
int arreglarJugada(char[50], char[50]);
int comprobarSintaxis(char[50], char[50], char[50], char[50], int, int, int, int);
int comprobarMovimiento(naipe[14][48], int, int, int, int);
int controlJuego(naipe[14][48]);
int cargarJuego(naipe[14][48], naipe[14][48], jugador[2]);
int guardarJuego(naipe[14][48], naipe[14][48], jugador[2]);
void crearMazo(naipe[14][48], naipe[14][48]);
void barajarMazo(naipe[14][48]);
void repartirMazo(naipe[14][48]);
void imprimirTapete(naipe[14][48]);
int jugar(naipe[14][48], naipe[14][48], jugador[2]);
void limpiarJuego(char[50], char[50], char[50], char[50], char[50],naipe[14][48]);
void separarParametros(char[50], char[50], char[50], char[50], int);
int ejecutarMovimiento(naipe[14][48], int, int, int);
void help();
int pistas(naipe[14][48], pista[2]);
int choseProfile(naipe[14][48], jugador[2]);
int createProfile(naipe[14][48], jugador[2]);
void optionsProfile(jugador[2]);
void hallOfFame(jugador[3]);
void revisarHOF(jugador[3], jugador[2]);

//Define funciones para el control del puntero del terminal en la pantalla.
#define gotoxy(x,y) printf("\x1b[%d;%dH",(y),(x))
#define moveup(x) printf("\x1b[%dA",(x))
#define movedown(x) printf("\x1b[%dB",(x))
#define moveright(y) printf("\x1b[%dC",(y))
#define moveleft(y) printf("\x1b[%dD",(y))

//Define una función que modifica los atributos de la terminal para imprimir las variables de forma "bonita"
#define atributo(x) printf("\x1b[%dm",(x)) 

/* El parámetro (x) equivale a los siguientes atributos:

  --> 0: Nada
  --> 1: Negrita
  --> 2: Oscurecido
  --> 3: Subrayado
  --> 4: Cursiva
  --> 91: Rojo
  --> 92: Verde
  --> 93: Amarillo
  --> 96: Azul

*/
