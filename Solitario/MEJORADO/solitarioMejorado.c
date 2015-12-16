/* Código fuente del juego solitario, desarrollado por:

  --> Pedro Tubío Figueira (Grupo 9)
  --> Jose Vilas Villamarín (Grupo 9)
  --> David Cordeiro de la Torre (Grupo 9)

En la implementación de este código hemos buscado, más que eficiencia de código y de uso de recursos o de memoria, sencillez de sintaxis. Queremos que el código sea fácil de entender, manejar e incluso mejorar o modificar para aumentar eficiencia, además de ser más sencillo para todos pasarnos código mutuamente y entenderlo a la hora de exponerlo en la entrevista de su defensa. A día de hoy, los ordenadores cuentan con recursos suficientes para ejecutar programas tan sencillos, no obstante, somos conscientes de que el programa aquí mostrado es extenso en líneas e incluso no muy ortodoxo a nivel de ahorro de memoria u otros factores, y de que en ciertos aspectos es mejorable, pero la cuestión a la hora de realizar el proyecto era escribir un código de acuerdo con las características expuestas en el pdf del proyecto. 

No hay mucho más que decir. A lo largo del código se han colocado diferentes comentarios para intentar en cierta medida orientar a los programadores que revisen este código sobre su funcionamiento. Esperamos haber sido lo suficientemente claros en este aspecto. 

Si nos gustaría destacar lo costoso de la parte de tratar con los datos que el usuario introduce por el teclado, pues hay infinidad de posibilidades a introducir, sobretodo para intentar 'buguear' el código de alguna manera para que no funcione correctamente. Creemos que esa parte la hemos dejado bien solucionada, tratando prácticamente todas las posibilidades de error, no obstante, es posible que alguna se nos haya quedado en el tintero, aunque está muy pulido el código.

En este código, el mejorado, algunas partes pueden no estar explícitamente comentadas o incluso puede haber código no utilizado como comentario. Esto es debido a que algunas cosas se afilaron a última hora y puede que no quede todo lo "correcto" que debería, pero la idea es que funcionen (pues son eso, mejoras).

Sin más dilación, aquí está el código. */

#include"bibliotecaSolitarioMejorado.h"

/* Función 'main', que contiene el menú principal y, desde él, se desemboca en las demás funcionalidades del juego */

int main(){

  naipe mazo[14][48], mazoDeshacer[14][48]; //Mazo de juego.
  char leoTeclado[50]={};
  int juegoEjecutado=0, comprobacion=0, mensaje=0, cargar=0, space=0, spaceStart=0, i, fin=0, chosenProfile=0, errorPerfiles=0, control=0;
  jugador perfil[2], HOF[3];
  
  //Inicialmente, se crea y se baraja el mazo.
  crearMazo(mazo, mazoDeshacer);
  barajarMazo(mazo);

  //Cargamos el Hall of Fame
  FILE *halloffame;

  if((halloffame=fopen("hallOfFame","r"))!=NULL){ 
  fread(HOF,sizeof(jugador[3]),1,halloffame);
  fclose(halloffame);
  }
  
  do{

  imprimirTapete(mazo);
  gotoxy(0,30); atributo(1); atributo(3);
  printf("\tJUEGO SOLITARIO.\n\n");
    printf("\t\tOpción 1 -> Crear perfil nuevo.\n");
    printf("\t\tOpción 2 -> Seleccionar perfil.\n");
    printf("\t\tOpción 3 -> Salir del juego.\n\n");
    printf("\t(Elija una opción pulsando 1, 2 ó 3 según corresponda): "); atributo(0);


    //Si hay mensaje de error que mostrar, se muestra
    if(errorPerfiles==1){
      atributo(91); atributo(1); atributo(3); printf("\n\n\t\tEl perfil no existe o no se ha podido cargar ó crear correctamente."); atributo(0);
      moveup(2); moveleft(19);
    }

    //Si hay mensaje de error que mostrar, se muestra
    if(errorPerfiles==2){
      atributo(91); atributo(1); atributo(3); printf("\n\n\t\tOpción incorrecta, introduzca 1, 2 ó 3 según corresponda."); atributo(0);
      moveup(2); moveleft(9);
    }

    errorPerfiles=0; control=0;
    memset(leoTeclado,'\0', strlen(leoTeclado)); //Limpiamos la cadena de entrada de parámetros.
    fgets (leoTeclado, 50, stdin);

    //Contamos los espacios que hay antes del primer carácter
    for(i=0; i<49; i++){
      if(leoTeclado[i]==' ') spaceStart++; //Contamos los espacios que hay para eliminarlos del tamaño final.
      else break;
    }


    for(i=0; i<49; i++){
      if(leoTeclado[i]==' ') space++; 
    }
        
    //Si no se ha introducido un solo carácter seguido de un salto de linea, se ha introducido algo incorrecto.
    comprobacion=strlen(leoTeclado)-space;

    if(comprobacion==2){
  
        switch (leoTeclado[spaceStart]){

        case '1': {
          control=createProfile(mazo,perfil);
          if(control==0) errorPerfiles=1; else chosenProfile=1;
	  break;
        }

        case '2': {
          control=choseProfile(mazo,perfil);
	  if(control==0) errorPerfiles=1; else {chosenProfile=1; perfil[1].partidasIniciadas=perfil[0].partidasIniciadas; perfil[1].partidasCompletadas=perfil[0].partidasCompletadas; perfil[1].porcentajeVictorias=perfil[0].porcentajeVictorias;}
	  break;
        }

        case '3': {
	  movedown(4);
	  return 0;
        }

        default: {
          errorPerfiles=2;
	  break;
        }
      }
    }


  }while(chosenProfile!=1);



  do{

    //Se imprime el menú principal
    imprimirTapete(mazo);

    gotoxy(0,30); atributo(1); atributo(3);
    printf("\tJUEGO SOLITARIO.\n\n");
    printf("\t\tOpción 1 -> Iniciar nuevo juego.\n");
    printf("\t\tOpción 2 -> Recuperar juego guardado.\n");
    printf("\t\tOpción 3 -> Guardar juego.\n"); 
    printf("\t\tOpción 4 -> Continuar juego actual.\n");
    printf("\t\tOpción 5 -> Estadísticas del perfil.\n");
    printf("\t\tOpción 6 -> Hall of Fame.\n");
    printf("\t\tOpción 7 -> Salir del juego.\n\n"); atributo(93);
    printf("\t\tPara acceder al menú de ayuda, pulse 'h' ó 'H'.\n\n"); atributo(0); atributo(1); atributo(3);
    printf("\t(Elija una opción pulsando 1, 2, 3 ó 4, según corresponda): "); atributo(0);
    
    //Si hay mensaje de error que mostrar, se muestra
    if(mensaje==1){
      atributo(91); atributo(1); atributo(3); printf("\n\n\t\tLo sentimos, no existe o no se puede abrir la partida indicada."); atributo(0);
      moveup(2); moveleft(11);
    }
    
    if(mensaje==2){
      atributo(91); atributo(1); atributo(3); printf("\n\n\t\tNo existe juego que guardar.");atributo(0);
      moveup(2); moveright(24);
    }
    
    if(mensaje==3){
      atributo(91); atributo(1); atributo(3); printf("\n\n\t\tJuego guardaro.");atributo(0);
      moveup(2); moveright(37);
    }
    
    if(mensaje==4){
      atributo(91); atributo(1); atributo(3); printf("\n\n\t\tElección incorrecta, pulsar 1, 2, 3, 4, 5, 6 ó 7.");atributo(0);
      moveup(2); moveright(3);
    }

    if(mensaje==5){
      atributo(91); atributo(1); atributo(3); printf("\n\n\t\tNo hay ningún juego comenzado para continuar.");atributo(0);
      moveup(2); moveright(7);
    }

    if(mensaje==10){
      atributo(91); atributo(1); atributo(3); printf("\n\n\t\tNo puedes introducir tu nombre de perfil.");atributo(0);
      moveup(2); moveright(11);
    }
    //Se reinician las variables mensaje y space a 0 y se pide al usuario que escoja opción en el menú principal.
    mensaje=0;
    space=0; spaceStart=0;
    memset(leoTeclado,'\0', strlen(leoTeclado)); //Limpiamos la cadena de entrada de parámetros.
    fgets (leoTeclado, 50, stdin);

    //Contamos los espacios que hay antes del primer carácter
    for(i=0; i<49; i++){
      if(leoTeclado[i]==' ') spaceStart++; //Contamos los espacios que hay para eliminarlos del tamaño final.
      else break;
    }


    for(i=0; i<49; i++){
      if(leoTeclado[i]==' ') space++; 
    }
        
    //Si no se ha introducido un solo carácter seguido de un salto de linea, se ha introducido algo incorrecto.
    comprobacion=strlen(leoTeclado)-space;
     
    //Si el formato es el correcto, se entra en el switch
    if(comprobacion==2){

      switch (leoTeclado[spaceStart]){

      //En el caso de escoger 'Iniciar nuevo juego', debemos dirijirnos al juego, repartiendo el mazo de cartas a ls distintas columnas.
      case '1': {

        //Si se ha ejecutado un juego con anterioridad, se deben reiniciar todas las variables y las cartas.
	if (juegoEjecutado==1){ 
	  crearMazo(mazo, mazoDeshacer); 
	  barajarMazo(mazo);
	}
	
	repartirMazo(mazo);
        fin=0; mazo[13][20].num=0; //Parámetro de control para deshacer el último movimiento. Indica si ya se ha ejecutado algún movimiento con anterioridad.
	fin=jugar(mazo, mazoDeshacer, perfil);
	if(fin!=0) revisarHOF(HOF,perfil);
	juegoEjecutado=1; perfil[0].partidasIniciadas++; //Parámetro de control para reiniciar las cartas y demás, que también sirve para comprobar si existe juego que guardar o no.
        perfil[0].porcentajeVictorias=((float)perfil[0].partidasCompletadas/(float)perfil[0].partidasIniciadas)*100;
	break;
      }
     
      //En el caso de escoger 'Recuperar juego guardado', llamamos a la función 'cargarJuego', que se encarga de recuperar el juego o de avisar si no se puede hacer. 	
      case '2': {
	cargar=cargarJuego(mazo, mazoDeshacer, perfil); //esta función devuelve un parámetro que indica, en caso de ser 1, que no se ha podido recuperar el juego, o que no hay juego que recuperar.

	if (cargar==1){
	  mensaje=1; 
	  break;
	}
	
        //Se procede a jugar.
        fin=0;
	fin=jugar(mazo, mazoDeshacer, perfil);
	juegoEjecutado=1;
	if(fin!=0) revisarHOF(HOF,perfil);
	break;
      }
      	
      //En el caso de escoger 'Guardar Juego', se llama a una función que guarda el juego y se muestra el mensaje correspondiente, bien sea error o satisfactorio.
      case '3': {
	if (juegoEjecutado==0){
	  mensaje=2;
	  break;
	}

	cargar=guardarJuego(mazo, mazoDeshacer, perfil);

	if (cargar==1){
	  mensaje=1; 
	  break;
	}

	mensaje=3;		
	break;
      }

      case '4':{
	if (juegoEjecutado==0){
	  mensaje=5;
	  break;
	}


        fin=jugar(mazo,mazoDeshacer, perfil);
  	break;
      }
      


      case '5':{
          optionsProfile(perfil);
	  break;
	}

      case '6':{
          hallOfFame(HOF);
	  break;
	}


      //En el caso de escoger 'Salir del juego', se sale del juego, simplemente.
      case '7':{

        FILE *pf;

        if((pf=fopen(perfil[0].nombre,"wb"))==NULL) {atributo(91); atributo(1); atributo(3); printf("\n\n\t\tNo se ha podido actualizar el perfil al salir."); atributo(0);}
        fwrite(perfil,sizeof(jugador[2]),1,pf);
        fclose(pf);

        FILE *hall;

        hall=fopen("hallOfFame","wb");
        fwrite(HOF,sizeof(jugador[3]),1,pf);
        fclose(hall);


	movedown(3);
	break;
      }

      case 'h':{
        help();
	break;
      }

      case 'H':{
        help();
	break;
      }

      //Si la opción introducida es otra, se muestra un mensaje de error.
      default:{
	mensaje=4;
	break;
      }
	
      }
      
    }else mensaje=4;

  if (fin!=0) juegoEjecutado=0;     
        

  } while (leoTeclado[0]!='7');
  
  return 0;
}

/* La función 'jugar' es la función principal del juego. Desde ella se piden los movimientos, se imprimen los menús y errores correspondientes.  */ 

int jugar(naipe mazo[14][48], naipe mazoDeshacer[14][48], jugador perfil[2]){
  
  char opcionIntroducida[50]={}, opcionCorrecta[50]={}, origen[50]={}, destino[50]={}, cantidad[50]={}, final[50];
  int parametros, error=0, comp1, comp2, comp3, movValido=1, orig, dest, cant, fin=0, i, k, control=0, noCantidad=0;
  pista ayuda[2]={};
  
  do{
    limpiarJuego(opcionIntroducida,opcionCorrecta,origen,destino,cantidad, mazo); //Se limpian las cadenas
    
    imprimirTapete(mazo);
    
    //Se imprime el menú de juego
    gotoxy(0,30); atributo(1); atributo(3);
    printf("\tPor favor, introduzca un movimiento para jugar.\n");
    printf("\n\t\tMOVIMIENTO: ");
    atributo(93); printf("\n\n\n\t(Pulsa 'h' ó 'H' para acceder al manual de ayuda)."); atributo(0);
    atributo(91); atributo(2); printf("\n\t(Pulsa 'z' ó 'Z' para deshacer un movimiento)."); atributo(0);
    atributo(2); atributo(3); printf("\n\t(Pulsa 'p' ó 'P' para obtener una pista)."); atributo(0);
    moveup(5); moveleft(21);
    
    //Se imprimen los diferentes errores que puedan ocurrir en este momento del juego.
    if(error==1){
      atributo(91); atributo(1); atributo(3); printf("\n\n\n\n\n\n\n\tEntrada incorrecta"); atributo(0);
      moveup(7); moveright(2);
    }
    
    if(error==3){
      atributo(91); atributo(1); atributo(3); printf("\n\n\n\n\n\n\n\tMovimiento no válido"); atributo(0);
      moveup(7);
    }

    if(error==5){
      control=0;
      control=pistas(mazo,ayuda);
      gotoxy(35,6); atributo(1); atributo(4); atributo(91); printf("PISTA ->"); atributo(0);
      atributo(35); printf("   Origen:"); atributo(0); atributo(2); printf(" %i   ",ayuda[control].origen); atributo(0);
      atributo(35); printf("Destino:"); atributo(0); atributo(2); printf(" %i   ",ayuda[control].destino); atributo(0);
      if(((ayuda[control].origen==0)&&(ayuda[control].destino==12))||((ayuda[control].origen==12)&&(ayuda[control].destino==0))) noCantidad=1; 
      if(noCantidad!=1){
        atributo(35); printf("Cantidad:"); atributo(0); atributo(2); printf(" %i\n",ayuda[control].cantidad); atributo(0); movedown(25); moveright(28);
      } else {printf("\n"); movedown(25); moveright(28);}
      
    }
    
    if(error==8){
      atributo(91); atributo(1); atributo(3); printf("\n\n\n\n\n\tNo hay movimiento que deshacer"); atributo(0);
      moveup(7); moveleft(10);
    }

    if(error==7){
      atributo(91); atributo(1); atributo(3); printf("\n\n\n\n\n\tSólo se puede deshacer el último movimiento"); atributo(0);
      moveup(7); moveleft(23);
    }

    //Se reinician los contadores
    error=0;
    movValido=1;
    control=0;
    noCantidad=0;
    

    //Pedimos al usuario que introduzca la jugada.
    fgets (opcionIntroducida, 50, stdin);

    //Tratamos la cadena de caracteres
    parametros=arreglarJugada(opcionIntroducida,opcionCorrecta); //Eliminamos los espacios a mayores y contamos cuantos hay.
    separarParametros(opcionCorrecta,origen,destino,cantidad,parametros); //Separamos los parámetros a cadenas auxiliares
    comp1=strlen(origen);    comp2=strlen(destino);    comp3=strlen(cantidad); //Cogemos la longitud de las cadenas y las pasamos como parámetro a la función 'comprobarSintaxis'.

/* A la función 'comprobarSintaxis', en realidad, no es necesario pasarle la longitud de las cadenas 'origen', 'destino' y 'cantidad', pues estos parámetros se podrían obtener desde dentro de la misma, pero esto se hizo así debido a que dicha función es reciclaje de una anterior que se descartó. */
    
    error=comprobarSintaxis(opcionCorrecta,origen,destino,cantidad,parametros,comp1,comp2,comp3); //Comprobamos si la sintaxis del movimiento es la correcta
            

    if(error==6) help();

    if (error==0){
      orig=atoi(origen);
      dest=atoi(destino);
      cant=atoi(cantidad);
            
      //Hasta aquí, ya hemos discernido que la sintaxis del movimiento es correcto. Ahora toca comprobar si es un movimiento válido. Después, ejecutarlo.
      movValido=comprobarMovimiento(mazo,orig,dest,cant,parametros);

      //Asociamos al resultado de comprobar el movimiento el error correspondiente.
      if (movValido==0) error=3;
      if (movValido==2) error=1;

    }

    //Si no existe error, se ejecuta el movimiento.
    if (error==0){
      //Copiamos la matriz para dar la posibilidad de deshacer el movimiento, lo ejecutamos y colocamos el contador de control como mocimientoEjecutado.
      for(i=0; i<14; i++){
        for(k=0; k<48; k++){
	  mazoDeshacer[i][k].num=mazo[i][k].num;
	  mazoDeshacer[i][k].palo=mazo[i][k].palo;
	  mazoDeshacer[i][k].vis=mazo[i][k].vis;
	  mazoDeshacer[i][k].atributo=mazo[i][k].atributo;
        }
      }
      mazo[13][40].num=ejecutarMovimiento(mazo,orig,dest,cant);
      mazo[13][20].num=1;
    }

    //Deshacer el juego sin haber movido nada, y únicamente se puede deshacer el último movimiento
    if((error==9)&&(mazo[13][20].num==0)) error=8;
    if((error==9)&&(mazo[13][20].num==2)) error=7;

    //Deshacer el juego (nota, solo se podrá deshacer un movimiento)
    if((error==9)&&(mazo[13][20].num==1)){

      for(i=0; i<14; i++){
        for(k=0; k<48; k++){
	  mazo[i][k].num=mazoDeshacer[i][k].num;
	  mazo[i][k].palo=mazoDeshacer[i][k].palo;
	  mazo[i][k].vis=mazoDeshacer[i][k].vis;
	  mazo[i][k].atributo=mazoDeshacer[i][k].atributo;
        }
      }
      mazo[13][20].num=2;
    }

    //Si se introduce un único parámetro y este es un carácter o similiar, se debe reiterar este error, por eso está aquí al final, para salir del juego al introducir la 'm' ó 'M' en dicho bucle.
    if (error==2){
      
      do{
	limpiarJuego(opcionIntroducida,opcionCorrecta,origen,destino,cantidad, mazo);
	
	imprimirTapete(mazo);
	
	//Se pide al jugador que introduzca una 'm' ó 'M' para volver al menú y se reitera el error mientras no se haga.
	gotoxy(0,30); atributo(1); atributo(3);
	printf("\tPor favor, introduzca un movimiento para jugar.\n");
	printf("\n\t\tMOVIMIENTO: ");
	atributo(91); atributo(1); atributo(3); printf("\n\n\n\t(Por favor, pulsa 'm' ó 'M' para volver al menú principal)."); atributo(0);
	moveup(3); moveleft(39);
	fgets (opcionIntroducida, 50, stdin);
	parametros=arreglarJugada(opcionIntroducida,opcionCorrecta);
	
	//Si se introduce más de un parámetro, se cambia el primer carácter a 0 para que no se salga del bucle y se reitere el error.
	if (parametros!=0) opcionCorrecta[0]='0';

	//Si se introduce un parámetro, se comprueba que sea una 'm' y un salto de linea.
	if (parametros==0) {
	  if (opcionCorrecta[1]==10) continue;
	  if (opcionCorrecta[1]!=10) opcionCorrecta[0]='0';
	}
      }while((opcionCorrecta[0]!='m')&&(opcionCorrecta[0]!='M'));	
      
    }

    if(error==5) mazo[13][40].num=mazo[13][40].num-(mazo[13][0].num+(mazo[13][12].num))*0.9;
    if(mazo[13][40].num<=0) mazo[13][40].num=0;

    //Se comprueba si se ha alcanzado el final del juego y se devuelve un parámetro de control, que está inicializado a 0 por defecto. Si no es 0, se entra en el switch.
    fin=controlJuego(mazo);
    

    if (fin!=0){

      perfil[1].maximaPuntuacion=mazo[13][40].num;
      perfil[0].maximaPuntuacion=perfil[1].maximaPuntuacion;
      

	control=mazo[13][40].num;

      switch(fin){

      //El caso 1 es que se acabe el juego en la primera ronda.
      case 1:{
	imprimirTapete(mazo);
	gotoxy(0,30); atributo(1); atributo(3); atributo(95); printf("\t¡Enhorabuena, has completado el juego en la primera ronda!\n\t\tTu puntuación: %i puntos.\n", control); atributo(0);
	perfil[0].partidasCompletadas++; 
	break;
      }
	
      //El caso 2 es que se acabe el juego en la segunda o tercera ronda ronda.
      case 2:{
	crearMazo(mazo, mazoDeshacer);
	gotoxy(0,30); atributo(1); atributo(3); atributo(95); printf("\t¡Enhorabuena, has completado el juego!\n\t\tTu puntuación: %i punto(s).\n", control); atributo(0);
	perfil[0].partidasCompletadas++; 
	break;
      }

      //El caso 3 es que no se complete el juego.
      case 3:{
	imprimirTapete(mazo);
	gotoxy(0,30); atributo(1); atributo(3); atributo(91); printf("\t¡No has podido completar el juego!\n\t\tGAME OVER\n\t\t\tTu puntuación: %i punto(s).\n", control); atributo(0);
	break;
      }

      case 4:{
	imprimirTapete(mazo);
	gotoxy(0,30); atributo(1); atributo(3); atributo(91); printf("\t¡No has podido completar el juego, tu puntuación ha llegado a 0!\n\t\tGAME OVER\n"); atributo(0);

	break;
      }

      } 



    }

  //Si no se introduce exactamente M seguido de un salto de linea, no se puede volver al menú (para el caso de múltipes parámetros, en los que no se reitera el error)
  if(((opcionCorrecta[0]=='m')||(opcionCorrecta[0]=='M'))&&(opcionCorrecta[1]!=10)) opcionCorrecta[0]='0';

    //Como se ha entrado en el switch, es que el juego se ha acabado. Se ha imprimido un mensaje informando del caso en el que se encuentra el jugador, así que se espera a que el usuario pulse algo para volver al menú principal, forzándose la salida.
    if(fin!=0){
      fgets(final, 50, stdin); //Lectura sin utilidad, sólo pausa la ejecución del programa. Hago esto en vez de un system("sleep 5") porque este último me daba algunos contratiempos a la hora de volver al menú principal.
	crearMazo(mazo, mazoDeshacer);
	barajarMazo(mazo);
      opcionCorrecta[0]='m'; //Forzamos la salida
      perfil[0].porcentajeVictorias=((float)perfil[0].partidasCompletadas/(float)perfil[0].partidasIniciadas)*100;
    }

  
  }while((opcionCorrecta[0]!='m')&&(opcionCorrecta[0]!='M'));

return fin;
}


/* Se genera un mazo de cartas para jugar al Solitario */

void crearMazo(naipe mazo[14][48], naipe mazoDeshacer[14][48]){

  /* El mazo seguirá la siguiente distribución:
     
     0- Mazo
     1- Columna1
     2- Columna2
     3- Columna3
     4- Columna4
     5- Columna5
     6- Columna6
     7- Columna7
     8- Salida8
     9- Salida9
     10- Salida10
     11- Salida11
     12- Descarte
     13- Contadores
     
     Vis:
     if 0 -> Boca abajo
     if 1 -> Boca arriba
     if 2 -> Vacía
     
  */

  int k,q,i;
  
  //Se generan las cartas en Mazo boca abajo.

  //Palo de Oros
  q=1;  
  for(k=0;k<12;k++){
    mazo[0][k].palo='O';
    mazo[0][k].num=q;
    mazo[0][k].vis=0;
    mazo[0][k].atributo=93;
    q++;
  }
  
  //Palo de Copas
  q=1;
  for(k=12;k<24;k++){
    mazo[0][k].palo='C';
    mazo[0][k].num=q;
    mazo[0][k].vis=0;
    mazo[0][k].atributo=91;
    q++;
  }
  
  //Palo de Espadas
  q=1;
  for(k=24;k<36;k++){
    mazo[0][k].palo='E';
    mazo[0][k].num=q;
    mazo[0][k].vis=0;
    mazo[0][k].atributo=96;
    q++;
  }
  
  //Palo de bastos
  q=1;
  for(k=36;k<48;k++){
    mazo[0][k].palo='B';
    mazo[0][k].num=q;
    mazo[0][k].vis=0;
    mazo[0][k].atributo=92;
    q++;
  }
  
  //Se rellena el resto de la matriz con 'nada'
  for(i=1; i<14; i++){
    for(k=0; k<48; k++){
      mazo[i][k].palo='0';
      mazo[i][k].num=0;
      mazo[i][k].vis=2;
      mazo[i][k].atributo=0;
    }
  }

  //Se genera la matriz mazoDeshacer con 'nada'
  for(i=0; i<14; i++){
    for(k=0; k<48; k++){
      mazoDeshacer[i][k].palo='0';
      mazoDeshacer[i][k].num=0;
      mazoDeshacer[i][k].vis=2;
      mazoDeshacer[i][k].atributo=0;
    }
  }

  //CONTADORES: En la columna 13 estarán los contadores que se emplearán en el transcurso del juego.

  mazo[13][0].num=47; //MAZO
  mazo[13][1].num=0; //Columnas 1 a 7
  mazo[13][2].num=0;
  mazo[13][3].num=0;
  mazo[13][4].num=0;
  mazo[13][5].num=0;
  mazo[13][6].num=0;
  mazo[13][7].num=0;
  mazo[13][8].num=0; //Salidas 8 a 11
  mazo[13][9].num=0;
  mazo[13][10].num=0;
  mazo[13][11].num=0;
  mazo[13][12].num=0; //Descarte
  mazo[13][13].num=0; //Contador vueltas dadas a Mazo

  mazo[13][40].num=0; //Puntuación
   
}


/* En esta función se barajan las cartas en mazo. Se cogen dos cartas aleatorias y se intercambian entre sí. Se repite el proceso 1000 veces, para asegurar una buena aleatoriedad de las cartas. */

void barajarMazo(naipe mazo[14][48]){

  int j,k,i;
  naipe temp;

  srand(time(NULL));
  
  for(i=0;i<1000;i++){
    j=rand()%48;
    k=rand()%48;
    temp=mazo[0][j];
    mazo[0][j]=mazo[0][k];
    mazo[0][k]=temp;
  }
}

/* Esta función se encarga de repartir las cartas a las diferentes columnas y poner los valores correspondientes en los contadores. */

void repartirMazo(naipe mazo[14][48]){
  
  int i,k,m,c,f;

  i=1;
  m=47;
  f=1;
  
  //Esta función copia las cartas en las columnas correspondientes y pone la visibilidad correspondiente en la cima.
  do{
    for (k=0; k<f; k++){
      mazo[i][k]=mazo[0][m];
      mazo[i][k].atributo=mazo[0][m].atributo;
      mazo[i][k].vis=0;
      mazo[0][m].vis=2;
      c=k;
      m--;
    }
    
    mazo[i][c].vis=1;
    i++;
    f++;
    
  }while(f!=8);
  
  //CONTADORES: 
  mazo[13][0].num=19;
  mazo[13][1].num=0;
  mazo[13][2].num=1;
  mazo[13][3].num=2;
  mazo[13][4].num=3;
  mazo[13][5].num=4;
  mazo[13][6].num=5;
  mazo[13][7].num=6;
  mazo[13][8].num=0;
  mazo[13][9].num=0;
  mazo[13][10].num=0;
  mazo[13][11].num=0;
  mazo[13][12].num=0;
  mazo[13][13].num=1;
  mazo[13][40].num=500;

}



/* Sencilla función que se encarga de cargar el último juego guardado. En caso de que no exista dicho juego guardado, se devuelve 1, que le indica al programa principal que hay un error */

int cargarJuego(naipe mazo[14][48], naipe mazoDeshacer[14][48], jugador perfil[2]){

  char nombrePartida[20];

  FILE *pf;

  system("clear");
  imprimirTapete(mazo);
  gotoxy(0,30); atributo(1); atributo(3); printf("\tPor favor, introduzca el nombre de la partida: "); atributo(0);

      atributo(91); atributo(1); atributo(3); printf("\n\n\t\t¡¡POR FAVOR, NO UTILICE EL NOMBRE DE SU PERFIL PARA ESTE FIN!!\n."); atributo(0); moveup(3); moveright(54);//Hacerlo haría que el juego no funcionase correctamente. Este error no dio tiempo de arreglarlo, con lo que se mostraría este mensaje y si el usuario hace caso omiso, será bajo su propia responsabilidad.
  memset(nombrePartida,'\0', strlen(nombrePartida));
  fgets(nombrePartida,20,stdin);
  
  if((pf=fopen(nombrePartida,"r"))==NULL) return 1; 
  //if(strcmp(nombrePartida,perfil[0].nombre)==0) nombrePartida[0]=5; 
  
  fread(mazo,sizeof(naipe[14][48]),1,pf);
  fread(mazoDeshacer,sizeof(naipe[14][48]),1,pf);
  fclose(pf);
  
  return 0;
}

/* La función 'guardarJuego' se encarga de copiar el contenido de mazo en un archivo. */

int guardarJuego(naipe mazo[14][48], naipe mazoDeshacer[14][48], jugador perfil[2]){
  
  char nombrePartida[20];

  system("clear");
  imprimirTapete(mazo);
  gotoxy(0,30); atributo(1); atributo(3); printf("\tPor favor, introduzca el nombre de la partida: "); atributo(0);

      atributo(91); atributo(1); atributo(3); printf("\n\n\t\t¡¡POR FAVOR, NO UTILICE EL NOMBRE DE SU PERFIL PARA ESTE FIN!!\n."); atributo(0); moveup(3); moveright(54); //Hacerlo haría que el juego no funcionase correctamente. Este error no dio tiempo de arreglarlo, con lo que se mostraría este mensaje y si el usuario hace caso omiso, será bajo su propia responsabilidad.
  memset(nombrePartida,'\0', strlen(nombrePartida));
  fgets(nombrePartida,20,stdin);

  FILE *pf;

  if((pf=fopen(nombrePartida,"wb"))==NULL) return 1; 
  //if(strcmp(nombrePartida,perfil[0].nombre)!=0) return 10; 

  fwrite(mazo,sizeof(naipe[14][48]),1,pf);
  fwrite(mazoDeshacer,sizeof(naipe[14][48]),1,pf);
  fclose(pf);
  
  return 0;
}


/* Esta función se encarga de imprimir el tablero de juego. En las columnas se salta de linea en linea en función de la cantidad de cartas que haya. */ 

void imprimirTapete(naipe mazo[14][48]){

  int k,p;

  system("clear");

  //MAZO
  gotoxy(3,1); atributo(1); atributo(35); if((mazo[13][0].num==0)&&(mazo[0][mazo[13][0].num].vis==2)) printf("MAZO [%i]", mazo[13][0].num); else printf("MAZO [%i]", mazo[13][0].num+1); atributo(0);
  gotoxy(4,3);
  k=mazo[13][0].num;
  
  if(mazo[0][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);} else {atributo(2); printf("???"); atributo(0);}
  
  //CONTADOR
  gotoxy(15,1); atributo(1); atributo(35); printf("RONDA"); atributo(0);
  gotoxy(17,3); atributo(3); printf("%i",mazo[13][13].num); atributo(0);

  //PUNTUACIÓN
  gotoxy(25,1); atributo(1); atributo(35); printf("PUNTUACIÓN"); atributo(0);
  gotoxy(28,3); atributo(3); printf("%i",mazo[13][40].num); atributo(0);
  
  //Salida8
  gotoxy(39,1); atributo(1); atributo(35); printf("Salida (8)"); atributo(0);
  gotoxy(41,3);
  k=mazo[13][8].num; 
  
  if(mazo[8][k].vis==1) {atributo(1); atributo(mazo[8][k].atributo); printf("%i %c",mazo[8][k].num,mazo[8][k].palo); atributo(0);}
  if(mazo[8][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
  if(mazo[8][k].vis==0) {atributo(2); printf("???"); atributo(0);}
  
  //Salida9
  gotoxy(52,1); atributo(1); atributo(35); printf("Salida (9)"); atributo(0);
  gotoxy(54,3);
  k=mazo[13][9].num; 
  
  if(mazo[9][k].vis==1) {atributo(1); atributo(mazo[9][k].atributo); printf("%i %c",mazo[9][k].num,mazo[9][k].palo); atributo(0);}
  if(mazo[9][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
  if(mazo[9][k].vis==0) {atributo(2); printf("???"); atributo(0);}
  
  //Salida10
  gotoxy(65,1); atributo(1); atributo(35); printf("Salida (10)"); atributo(0);
  gotoxy(67,3);
  k=mazo[13][10].num; 
  
  if(mazo[10][k].vis==1) {atributo(1); atributo(mazo[10][k].atributo); printf("%i %c",mazo[10][k].num,mazo[10][k].palo); atributo(0);}
  if(mazo[10][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
  if(mazo[10][k].vis==0) {atributo(2); printf("???"); atributo(0);}
  
  //Salida11
  gotoxy(79,1); atributo(1); atributo(35); printf("Salida (11)"); atributo(0);
  gotoxy(81,3);
  k=mazo[13][11].num; 

  if(mazo[11][k].vis==1) {atributo(1); atributo(mazo[11][k].atributo); printf("%i %c",mazo[11][k].num,mazo[11][k].palo); atributo(0);}
  if(mazo[11][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
  if(mazo[11][k].vis==0) {atributo(2); printf("???"); atributo(0);}
  
  //DESCARTE
  gotoxy(5,6); atributo(1); atributo(35); printf("DESCARTE: "); atributo(0);
  k=mazo[13][12].num; 

  if(mazo[12][k].vis==1) {atributo(1); atributo(mazo[12][k].atributo); printf("%i %c",mazo[12][k].num,mazo[12][k].palo); atributo(0);}
  if(mazo[12][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
  if(mazo[12][k].vis==0) {atributo(2); printf("???"); atributo(0);}
  
  //Columna1
  gotoxy(3,9); atributo(1); atributo(35); printf("Columna (1)"); atributo(0);
  
  p=11;
  for(k=0;k<=mazo[13][1].num;k++){

    gotoxy(5,p);
    if(mazo[1][k].vis==1) {atributo(1); atributo(mazo[1][k].atributo); printf("%i %c",mazo[1][k].num,mazo[1][k].palo); atributo(0);}
    if(mazo[1][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
    if(mazo[1][k].vis==0) {atributo(2); printf("???"); atributo(0);}
    
    p++; 
  }
  
  //Columna2
  gotoxy(16,9); atributo(1); atributo(35); printf("Columna (2)"); atributo(0);
  
  p=11;
  for(k=0;k<=mazo[13][2].num;k++){

    gotoxy(18,p);    
    if(mazo[2][k].vis==1) {atributo(1); atributo(mazo[2][k].atributo); printf("%i %c",mazo[2][k].num,mazo[2][k].palo); atributo(0);}
    if(mazo[2][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
    if(mazo[2][k].vis==0) {atributo(2); printf("???"); atributo(0);}
    
    p++; 
  }
  
  //Columna3
  gotoxy(29,9); atributo(1); atributo(35); printf("Columna (3)"); atributo(0);
  
  p=11;
  
  for(k=0;k<=mazo[13][3].num;k++){

    gotoxy(31,p);  
    if(mazo[3][k].vis==1) {atributo(1); atributo(mazo[3][k].atributo); printf("%i %c",mazo[3][k].num,mazo[3][k].palo); atributo(0);}
    if(mazo[3][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
    if(mazo[3][k].vis==0) {atributo(2); printf("???"); atributo(0);}
    
    p++; 
  }
  
  //Columna4
  gotoxy(42,9); atributo(1); atributo(35); printf("Columna (4)"); atributo(0);
  
  p=11;
  
  for(k=0;k<=mazo[13][4].num;k++){

    gotoxy(44,p);    
    if(mazo[4][k].vis==1) {atributo(1); atributo(mazo[4][k].atributo); printf("%i %c",mazo[4][k].num,mazo[4][k].palo); atributo(0);}
    if(mazo[4][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
    if(mazo[4][k].vis==0) {atributo(2); printf("???"); atributo(0);}
    
    p++; 
  }
  
  //Columna5
  gotoxy(55,9); atributo(1); atributo(35); printf("Columna (5)"); atributo(0);
  
  p=11;
  
  for(k=0;k<=mazo[13][5].num;k++){

    gotoxy(57,p);    
    if(mazo[5][k].vis==1) {atributo(1); atributo(mazo[5][k].atributo); printf("%i %c",mazo[5][k].num,mazo[5][k].palo); atributo(0);}
    if(mazo[5][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
    if(mazo[5][k].vis==0) {atributo(2); printf("???"); atributo(0);}
    
    p++; 
  }
  
  //Columna6
  gotoxy(68,9); atributo(1); atributo(35); printf("Columna (6)"); atributo(0);
  
  p=11;
  
  for(k=0;k<=mazo[13][6].num;k++){

    gotoxy(70,p);   
    if(mazo[6][k].vis==1) {atributo(1); atributo(mazo[6][k].atributo); printf("%i %c",mazo[6][k].num,mazo[6][k].palo); atributo(0);}
    if(mazo[6][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
    if(mazo[6][k].vis==0) {atributo(2); printf("???"); atributo(0);}

    p++;
  }
  
  //Columna7
  gotoxy(81,9); atributo(1); atributo(35); printf("Columna (7)"); atributo(0);
  
  p=11;
  
  for(k=0;k<=mazo[13][7].num;k++){

    gotoxy(83,p);   
    if(mazo[7][k].vis==1) {atributo(1); atributo(mazo[7][k].atributo); printf("%i %c",mazo[7][k].num,mazo[7][k].palo); atributo(0);}
    if(mazo[7][k].vis==2) {atributo(2); printf("Vacía"); atributo(0);}
    if(mazo[7][k].vis==0) {atributo(2); printf("???"); atributo(0);}

    p++; 
  } 
 
}

/* Esta función se encarga de limpiar las cadenas de parámetros para evitar errores. Se hace uso de la función 'memset'. */

void limpiarJuego(char opcionIntroducida[50], char opcionCorrecta[50],char origen[50], char destino[50], char cantidad[50], naipe mazo[14][48]){

  int i, k;

  memset(opcionIntroducida,'\0', strlen(opcionIntroducida));
  memset(opcionCorrecta,'\0', strlen(opcionCorrecta));
  memset(origen,'\0', strlen(origen));
  memset(destino,'\0', strlen(destino));
  memset(cantidad,'\0', strlen(cantidad));

  for(i=0; i<13; i++){
    for(k=0; k<47; k++) {
      if(mazo[i][k].vis==2){
	mazo[i][k].num=0;
        mazo[i][k].palo='0';
        mazo[i][k].atributo=0;

      }
    }

  }
  
}

/* Este código comprueba si la sintaxis del movimiento que se ha introducido es correcta o no. Como ya tenemos el número de parámetros, en función del mismo, se comprueba que sea un movimiento correcto.*/ 

int comprobarSintaxis(char opcionCorrecta[50], char origen[50], char destino[50], char cantidad[50], int parametros, int comp1, int comp2, int comp3){
  
//La cuestión es: si empieza por carácter, error!

  int error=0;
  int i,c=0, hayCaracter=0;
  
  switch (parametros){
    
  case 0:{
    error=0;
    c=0;

    //Si se ha metido una 'm' o una 'M', es correcto.
    if ((opcionCorrecta[1]==10)&&((opcionCorrecta[0]=='m')||(opcionCorrecta[0]=='M'))){
      error=0;
      return error;
    }   

    //Si se ha metido una 'z' o una 'Z', es correcto.
    if ((opcionCorrecta[1]==10)&&((opcionCorrecta[0]=='z')||(opcionCorrecta[0]=='Z'))){
      error=9;
      return error;
    }  

    //Si se ha metido una 'h' o una 'H', es correcto.
    if ((opcionCorrecta[1]==10)&&((opcionCorrecta[0]=='h')||(opcionCorrecta[0]=='H'))){
      error=6;
      return error;
    } 

    //Si se ha metido una 'p' o una 'P', es correcto.
    if ((opcionCorrecta[1]==10)&&((opcionCorrecta[0]=='p')||(opcionCorrecta[0]=='P'))){
      error=5;
      return error;
    } 


    //Los números negativos no entran en este tipo de errores, por eso, si el parámetro introducido empieza por un signo menos, este se salta. Lo mismo en los demás casos del switch.
    if(origen[0]=='-') c++;

    //Comprobamos si el primer caracter a comprobar no es un número. Si no es número, (es decir, letra o símbolo), se tira error de reiterar 'm' ó 'M'
    if((origen[c]<'0')||(origen[c]>'9')){
      error=2;
      return error;
    }  

    //Llegados a este punto, hemos descartado que el primer parámetro introducido sea un carácter, con lo cual va a ser un número y se tirará el error de 'Entrada incorrecta'.
    error=1;		
        
    break;
  }

//En los otros dos casos del switch la idea es la misma.    
  case 1:{
    error=0;
    c=0;

    //Los números negativos no entran en este tipo de errores, por eso, si el parámetro introducido empieza por un signo menos, este se salta. Lo mismo en los demás casos del switch.
    if(origen[0]=='-') c++;

    //Comprobamos si el primer caracter a comprobar no es un número. Si no es número, (es decir, letra o símbolo), se tira error de reiterar 'm' ó 'M'
    if((origen[c]<'0')||(origen[c]>'9')){
      error=2;
      return error;
    }  
    
    for(i=c; i<comp1; i++){
      if((origen[i]!=10)&&((origen[i]<'0')||(origen[i]>'9'))) hayCaracter=1;
    }
      
    c=0;
    if(destino[0]=='-') c++;
    
    for(i=c; i<comp2; i++){
      if((destino[i]!=10)&&((destino[i]<'0')||(destino[i]>'9'))) hayCaracter=1;
    }					

    if(hayCaracter==1) error=1;
    
    break;
  }
    
  case 2:{
    error=0;
    c=0;

    //Los números negativos no entran en este tipo de errores, por eso, si el parámetro introducido empieza por un signo menos, este se salta. Lo mismo en los demás casos del switch.
    if(origen[0]=='-') c++;

    //Comprobamos si el primer caracter a comprobar no es un número. Si no es número, (es decir, letra o símbolo), se tira error de reiterar 'm' ó 'M'
    if((origen[c]<'0')||(origen[c]>'9')){
      error=2;
      return error;
    } 

    for(i=c; i<comp1; i++){      
      if((origen[i]!=10)&&((origen[i]<'0')||(origen[i]>'9'))) hayCaracter=1;
    }
       
    c=0;
    if(destino[0]=='-') c++;
    
    for(i=c; i<comp2; i++){     
      if((destino[i]!=10)&&((destino[i]<'0')||(destino[i]>'9'))) hayCaracter=1;
    }					
    
    c=0;
    if(cantidad[0]=='-') c++;
    
    for(i=c; i<comp3; i++){  
      if((cantidad[i]!=10)&&((cantidad[i]<'0')||(cantidad[i]>'9'))) hayCaracter=1;
    }
    
    if(hayCaracter==1) error=1;
    
    break;
  }
    
  }	       
  
  return error;
}

/* La función 'arreglarJugada' se encarga de coger la cadena de caracteres que el usuario haya introducido por el prompt y eliminar los espacios a mayores que el usuario haya podido introducir, para más adelante tratar los espacios que haya en dicha cadena como parámetros de juego. Esta parte se podría sustituir por la función 'strtok', pero cuando descubrí su existencia ya estaba todo programado y preparado para funcionar a través de este método. */

int arreglarJugada(char opcionIntroducida[50], char opcionCorrecta[50]){

  int i, l, control;
  int contEspacios=0;
  i=0, l=0;

  //Si dos posiciones consecutivasd del array 'opcionIntroducida' son espacios, no se hace nada, y si no lo son, se copia el contenido de dicha posición en opcionCorrecta
  for(i=0;i<49;i++){
	
    if((opcionIntroducida[i]==' ')&&(opcionIntroducida[i-1]==' ')) continue;
    else {
      opcionCorrecta[l]=opcionIntroducida[i];
      l++;
    }
  }
  
  //Si despueś de la copia el contenido de la primera posición de 'opcionCorrecta' es un espacio, este se elimina
  if (opcionCorrecta[0]==' '){
    for(i=0;i<49;i++){
      opcionCorrecta[i]=opcionCorrecta[i+1];
    }
  }
  
  //Se busca el salto de linea en 'opcionCorrecta'
  for (i=0; i<49; i++){
    if (opcionCorrecta[i]==10){ 
      control=i;
      break;
    }
  }
  
  //Si antes del salto de linea hay un espacio, este también se anula.
  if((opcionCorrecta[control]==10)&&(opcionCorrecta[control-1]==' ')){
    opcionCorrecta[control-1]=10;
    opcionCorrecta[control]='0';
  }
  
  //Contamos los espacios que hay en el array, que nos vendrá dando el número de parámetros que el jugador ha introducido por el prompt.
  for(i=0;i<49;i++){
    if(opcionCorrecta[i]==' ') {
      contEspacios++;
    } else continue;
  }
  
  return contEspacios;
}

/* Esta función se encarga de copiar en cadenas auxiliares los parámetros que el usuario haya decidido introducir por teclado. */

void separarParametros(char opcionCorrecta[50], char origen[50], char destino[50], char cantidad[50], int parametros){

  int i,k, control;

  switch (parametros){
  
  //En caso de que sea sólo un parámetro, se copia el contenido tal cual hasta que se encuentre con un salto de linea. Esto se puede hacer tanto con un do-while como con un for, aunque para cambiar un poco de costumbres, aquí se ha hecho con un do-while.  
  case 0:{
    i=0;
    k=0;

    do{ 
      origen[k]=opcionCorrecta[i];
      i++; k++;      
    }while(opcionCorrecta[i]!=10);
    
    break; 
  }
  
  //Si son dos parámetros:  
  case 1:{ 
    i=0;
    k=0;
    
    //Se copia la primera parte
    do{ 
      origen[k]=opcionCorrecta[i];
      i++; k++;
      control=i; 
    }while(opcionCorrecta[i]!=' ');
    
    control++;
    i=control;
    k=0;	
    
    //Se copia la segunda
    do{
      destino[k]=opcionCorrecta[i];
      i++; k++;
    }while(opcionCorrecta[i]!=10);	
    
    //Si no se introduce tercer parámetro (pues es opcional) se tiene que suponer a 1, para mover una sola carta.
    cantidad[0]='1';
    break;
  }
    
  //En caso de introducir tres parámetros, simplemente se copian a las correspondientes cadenas auxiliares.
  case 2:{
    i=0;
    k=0;
    do{
      origen[k]=opcionCorrecta[i];
      i++; k++; control=i;
    }while(opcionCorrecta[i]!=' ');

    control++;
    i=control;
    k=0;	
    
    do{
      destino[k]=opcionCorrecta[i];
      i++; k++; control=i;
    }while(opcionCorrecta[i]!=' ');	
    
    control++;
    i=control;	
    k=0;
    
    do{  
      cantidad[k]=opcionCorrecta[i];
      i++; k++;      
    }while(opcionCorrecta[i]!=10);	
    
  }
    
  }

}

/* En esta función se comprueba que el movimiento que el usuario ha introducido es válido. */

int comprobarMovimiento(naipe mazo[14][48], int orig, int dest, int cant, int parametros){

  int movValido=1;

  //Comprobación de los rangos de los parámetros (es decir, que origen y destino esté entre 0 y 12 y que la cantidad no sea ni mayor que 12 ni 0. (FUNCIONA)
  if (((orig>12)||(orig<0))||((dest>12)||(dest<0))||((cant>12)||(cant<=0))){
    movValido=2;
    return movValido;
  }

  //Una comprobación muy básica antes de profundizar más en la función, sería que no se esté moviendo a la misma columna / salida. 
  if (orig==dest){
    movValido=0;
    return movValido;
  }
  
  //Además, no se puede mover entre salidas ni de MAZO a otro sitio que no sea DESCARTE. 
  if (((orig>=8)&&(orig<=11))&&((dest>=8)&&(dest<=11))){
    movValido=0;
    return movValido;
  }
  
  //Error al mover de MAZO a fuera de descarte o de FUERA DE MAZO a descarte. 
  if (((orig==0)&&(dest!=12))||((dest==12)&&(orig!=0))){ 
    movValido=0;
    return movValido;
  }
  
  //Y, finalmente, no se puede mover de salidas a columnas. 
  if (((orig>=8)&&(orig<=11))&&((dest>=1)&&(dest<=7))){
    movValido=0;
    return movValido;
  }
  
  //Pretender mover más de una carta de columnas a salidas.
  if(((orig>=1)&&(orig<=7))&&((dest>=8)&&(dest<=11))&&(cant!=1)){  
    movValido=0;
    return movValido;
  }
  
  //Si origen está vacío, no se puede mover nada (esta condición es necesaria porque, si bien está contemplado ya dentro de otras casuísticas, no lo está en todas. Así pues, esta es una condición general para impedir el movimiento de una carta, que el origen esté vacío.
  if(mazo[orig][mazo[13][orig].num].vis==2){  
    movValido=0;
    return movValido;
  }

  //Si mazo y descarte están vacíos, no se puede mover nada entre ninguno de ellos:
  if(((orig==12)&&(dest==0))||((orig==0)&&(dest==12))){
    if((mazo[12][0].vis==2)&&(mazo[0][0].vis==2)){
      movValido=0;
      return movValido;
    }
  }
  
  /* Ahora que hemos superado la barrera de que el movimiento tiene el rango correcto, procedemos a separar los movimientos. Haremos esencialmente 4 distinciones, para hacer el trabajo más sencillo:
    
    --> Movimiento entre columnas
    --> Movimientos entre columnas y salidas
    --> Movimientos de mazo a descarte, descarte a mazo y de descarte a las diferentes columnas/salidas.
    --> Movimientos con tercer parámetro (es decir, a mover más de una carta).
    
  */
  

  //Empezamos por los movimientos entre columnas. (En esta fase asumimos que se mueve sólo una carta)
  if ((((orig>=1)&&(orig<=7))||(orig==12))&&((dest>=1)&&(dest<=7))&&(cant==1)){
    
    //Si origen está vacío, no se puede mover nada. 
    if(mazo[orig][mazo[13][orig].num].vis==2){ 
      movValido=0;
      return movValido;
    }
    
    //Si destino está vacío, únicamente se puede mover un REY. 
    if(mazo[dest][mazo[13][dest].num].vis==2){
      if(mazo[orig][mazo[13][orig].num].num!=12) { 
	movValido=0;
	return movValido;
      } else  return movValido; //Asumimos que, si se ha llegado a esta parte del if, es porque se está intentando mover una carta a una columna vacía. Si es un REY, se puede mover.
    }
    
    //Aquí ya tenemos descartado que origen esté vacía, y también hemos acotado la posibilidad a mover tan solo un rey a una columna vacía. Nos faltaría comprobar el número sea una unidad menor y el palo distinto.
    if((mazo[orig][mazo[13][orig].num].num!=mazo[dest][mazo[13][dest].num].num-1)||(mazo[orig][mazo[13][orig].num].palo==mazo[dest][mazo[13][dest].num].palo)){ 
      movValido=0;
      return movValido;
    }	
    
  }
  
  
  
  //Continuamos con los movimientos de Columnas a Salidas: (En esta fase asumimos que se mueve sólo una carta, porque en realidad no se puede mover más de una carta a salida (definido arriba))
  if((((orig>=1)&&(orig<=7))||(orig==12))&&((dest>=8)&&(dest<=11))&&(cant==1)){
    
    //Si en origen no cogemos un AS, no podremos mover nada a las SALIDAS, si estas están vacías.
    if(mazo[dest][mazo[13][dest].num].vis==2){ 
      if(mazo[orig][mazo[13][orig].num].num!=1){
	movValido=0;
	return movValido;
      }
    }
    
    //Deberán coincidir el palo de la salida con el de la columna, y ser la carta una unidad superior a la que se encuentre en la salida.
    if(mazo[dest][mazo[13][dest].num].vis==1){ 
      if((mazo[orig][mazo[13][orig].num].palo!=mazo[dest][mazo[13][dest].num].palo)||(mazo[orig][mazo[13][orig].num].num!=mazo[dest][mazo[13][dest].num].num+1)){
	movValido=0;
	return movValido;
      }
    }
    
  }
  
  //Procedemos con los movimientos de mazo a descarte, descarte a mazo y de descarte a las diferntes columnas/salidas.
  
  //Si no hay cartas en MAZO, no se puede mover.
  if((orig==0)&&(dest==12)){ 
    if(mazo[orig][mazo[13][orig].num].vis==2){
      movValido=0;
      return movValido;
    }
    
  }
  
  //No se puede mover más de una carta de mazo a descarte.
  if((orig==0)&&(dest==12)&&(cant!=1)){
    movValido=0;
    return movValido;
  }
  
  
  
  //Mover de Descarte a mazo sólo es posible si mazo está vacio, y no puede haber tercer parámetro 
  if((orig==12)&&(dest==0)){
    
    if(mazo[dest][mazo[13][dest].num].vis==2){
      
      if (parametros==1){
	movValido=1;
	return movValido;
      }
      
      if (parametros==2){
	movValido=0;
	return movValido;
	
      }
      
    } else {
      movValido=0;
      return movValido;
    } 
  }
  
  //No se puede mover nada a mazo ni a descarte 
  if(((orig>=1)&&(orig<=11))){
    if((dest==0)||(dest==12)){
      movValido=0;
      return movValido;
    }
  }

  //No se puede mover nada de descarte si este está vacío
  if((orig==12)&&(mazo[12][0].vis==2)){
    movValido=0;
    return movValido;
  }

  //No se puede mover nada de descarte si este está vacío
  if((orig==12)&&(cant!=1)){
    movValido=0;
    return movValido;
  }
 
  
  //Para finalizar, procedemos a analizar los movimientos con tercer parámetro:
  if(((orig>=1)&&(orig<=7))&&((dest<8)&&(dest>0))){
    
    if((cant>=1)&&(cant<=12)){
      
      //No se puede mover una pila de cartas a las salidas
      if((dest>=8)&&(dest<=11)&&(cant!=1)){ 
	movValido=0;
	return movValido;
      }
      
      //Si la carta que deseamos mover no está visible, entonces tiramos error
      if(mazo[orig][mazo[13][orig].num-(cant-1)].vis!=1){ 
	movValido=0;
	return movValido;
      }

      //Si intentamos mover un rey a una columna no vacía, tiramos error.
      if((mazo[orig][mazo[13][orig].num-(cant-1)].num==12)&&(mazo[dest][mazo[13][dest].num].vis!=2)){ 
	movValido=0;
	return movValido;
      }

      //Si por el contrario la columna sí que está vacía, entonces ejecutamos el movimiento. En este caso no podemos poner un else, porque no es toda la condición la que no se debe cumplir.
      if((mazo[orig][mazo[13][orig].num-(cant-1)].num==12)&&(mazo[dest][mazo[13][dest].num].vis==2)){ 
	movValido=1;
	return movValido;
      }
      
      //No podemos mover cartas a columnas cuya última carta coincida en palo con la que se va a mover de la cima de la pila.
      if(mazo[orig][mazo[13][orig].num-(cant-1)].palo==mazo[dest][mazo[13][dest].num].palo){ 
	movValido=0;
	return movValido;
      }
      
      //Para que se puedan mover las cartas, además de la condición del palo, la carta (o la cima de las cartas) del origen debe ser una unidad menor que la de la cima del destino.
      if(mazo[orig][mazo[13][orig].num-(cant-1)].num!=mazo[dest][mazo[13][dest].num].num-1){ 
	movValido=0;
	return movValido;
      }

    }

  }
  
  return movValido;
}

/* Esta función ejecuta el movimiento de cartas. Se distinguen tres casos: el movimiento de descarte a mazo, el movimiento de una única carta y el movimiento de múltiples cartas. */

int ejecutarMovimiento(naipe mazo[14][48], int orig, int dest, int cant){

  int i, k, h, temp;
  
  //Movimiento de Descarte a Mazo
  if((orig==12)&&(dest==0)){
    temp=mazo[13][orig].num; //Se copia el contador de cartas de DESCARTE a un sitio de forma temporal
    for(h=0; h<temp; h++){
      i=mazo[13][orig].num; //Se cogen ambos contadores
      k=mazo[13][dest].num;
      
      //Se copian ambas caras y se colocan las visibilidades correspondientes.
      mazo[dest][k]=mazo[orig][i];
      mazo[dest][k].vis=0;
      mazo[orig][i].vis=2;

      //El contador nunca puede ser -1, por eso solo puede autodecrementarse hasta 0.
      if(mazo[13][orig].num!=0) mazo[13][orig].num--;

      mazo[13][dest].num++;
    }
    mazo[13][13].num++;
  }
  
  //Casuísticas para mover una única carta.
  if (cant==1){
    i=mazo[13][orig].num;
    k=mazo[13][dest].num;

    //Si el mazo está vacío, se copia la carta, y si no lo está, además se aumenta el contador.
    if (mazo[dest][k].vis==2) mazo[dest][k]=mazo[orig][i];
    else {
      mazo[dest][k+1]=mazo[orig][i]; 
      mazo[13][dest].num++;
    }
    
    //Se cambian las visibilidades correspondientes y se colocan los contadores como corresponda.
    mazo[orig][i].vis=2;
    mazo[orig][i-1].vis=1;
    mazo[13][orig].num--;

    if(dest==12) mazo[12][mazo[13][dest].num].vis=1;

    if (mazo[13][orig].num==-1){
      mazo[13][orig].num++;
      mazo[13][orig].vis=2;
    }  
  }
  
  //Casuísticas para mover múltiples cartas. (igual que con las otras casuísticas)
  if (cant!=1){
    for(h=0; h<cant; h++){
      i=mazo[13][orig].num;

      if((mazo[13][dest].num==0)&&(mazo[dest][mazo[13][dest].num].vis==2)) mazo[13][dest].num--;
      
      k=mazo[13][dest].num+(cant-h);
      
      mazo[dest][k]=mazo[orig][i];
      mazo[dest][k].vis=1;
      mazo[orig][i].vis=2;
      
      mazo[13][orig].num--;
      
    }
    
    if(mazo[13][orig].num==-1){
      mazo[13][orig].num++;
      mazo[orig][mazo[13][orig].num].vis=2; 
    }
    
    mazo[13][dest].num=mazo[13][dest].num+cant;
    
    if (mazo[orig][mazo[13][orig].num].vis==0) mazo[orig][mazo[13][orig].num].vis=1;
  }

  //Puntuación
  if((orig==12)&&(dest==0)) mazo[13][40].num=mazo[13][40].num/mazo[13][13].num;
  if(orig==12){
    if((dest>=1)&&(dest<=7)) mazo[13][40].num=mazo[13][40].num+(15*(mazo[dest][mazo[13][dest].num].num)/10);
    if((dest>=8)&&(dest<=11)) mazo[13][40].num=mazo[13][40].num+(80*(mazo[13][dest].num+1/10));
  }

  if(((orig>=1)&&(orig<=7))&&((dest>=1)&&(dest<=7))) mazo[13][40].num=mazo[13][40].num-(20/cant+1);

  if(((orig>=1)&&(orig<=7))&&((dest>=8)&&(dest<=11))) mazo[13][40].num=mazo[13][40].num+(50*(mazo[dest][mazo[13][dest].num].num+1/10));

 return mazo[13][40].num;
}

/* La utilidad de esta función es simple: comprobar que el usuario ha terminado el juego. */

int controlJuego(naipe mazo[14][48]){
  int fin=0;

  //Si en las salidas están todas las cartas:
  if((mazo[8][mazo[13][8].num].num==12)&&(mazo[9][mazo[13][9].num].num==12)&&(mazo[10][mazo[13][10].num].num==12)&&(mazo[11][mazo[13][11].num].num==12)){
    
    //En la primera vuelta: máxima puntuación
    if(mazo[13][13].num==1){
      fin=1;
      mazo[13][40].num=mazo[13][40].num+400;
      return fin;
    }
    
    //En la segunda vuelta: juego terminado
    if(mazo[13][13].num==2){
      fin=2;
      mazo[13][40].num=mazo[13][40].num+175;
      return fin;
    }   

    //En la tercera vuelta: juego terminado
    if(mazo[13][13].num==3){
      fin=2;
      mazo[13][40].num=mazo[13][40].num+45;
      return fin;
    } 

  }
  
  //Si se dan más de 3 vueltas: se termina el juego.
  if (mazo[13][13].num==4){
    fin=3;
    return fin;
  }

  //Si la puntuación llega a 0, se pierde la partida.
  if(mazo[13][40].num==0){
    fin=4;
    return fin;
  }
  
  return fin;
}

/* Muestra un menú de ayuda por pantalla. */

void help(){
char cosa[50];
system("clear");
atributo(1); atributo(91); printf("\n\n\tAYUDA DEL JUEGO SOLITARIO.");

atributo(1); atributo(4); atributo(96); printf("\n\n\t\tCómo mover cartas:"); atributo(0);
atributo(1); atributo(96); printf("\n\t\t\t- Para realizar un movimiento en el juego se deben introducir por teclado el origen, el destino y la cantidad de cartas a mover.\n\t\t\t- La forma de introducir estos parámetros es mediante el teclado.\n\t\t\t- Se introducirán siguiento el orden de 'Origen', 'Destino' y 'Cantidad'.\n\t\t\t- Para que se ejecute el movimiento, se debe pulsar la tecla 'Enter' una vez escritos los parámetros.\n\t\t\t- Cada una de las posiciones de juego se corresponde con el siguiente número:\n\n\t\t\t\t0 -> Mazo\n\t\t\t\t1 -> Columna 1\n\t\t\t\t2 -> Columna 2\n\t\t\t\t3 -> Columna 3\n\t\t\t\t4 -> Columna 4\n\t\t\t\t5 -> Columna 5\n\t\t\t\t6 -> Columna 6\n\t\t\t\t7 -> Columna 7\n\t\t\t\t8 -> Salida 8 \n\t\t\t\t9 -> Salida 9\n\t\t\t\t10 -> Salida 10\n\t\t\t\t11 -> Salida 11\n\t\t\t\t12 -> Descarte\n\n\t\t\t- Algunos ejemplos de movimientos válidos son:\n\t\t\t\t-> 0 12 (Mueve de mazo a descarte)\n\t\t\t\t-> 5 2 3 (Mueve de la columna 5 a la columna 2, 3 cartas).\n\n\t\t\t- El tercer parámetro es opcional.\n\t\t\t- Al mover de descarte a mazo, se mueven todas las cartas.\n\t\t\t- Pulsando 'p' se obtiene una pista, y pulsando 'z' se deshace el último movimiento."); atributo(0);

atributo(1); atributo(4); atributo(93); printf("\n\n\n\t\tReglas de juego:"); atributo(0);
atributo(1); atributo(93); printf("\n\t\t\t- Al mover cartas que impliquen a descarte o a mazo, sólo se podrá mover una carta.\n\t\t\t- No se pueden devolver las cartas de descarte a mazo a no ser que el segundo esté vacío.\n\t\t\t- No se pueden mover cartas de las salidas a ningún otro sitio, ni entre las propias salidas.\n\t\t\t- Para mover cartas entre columnas, la carta (o la cima de la pila de cartas en caso de ser varias) debe ser una unidad menor que la última carta de destino y no coincidir el palo.\n\t\t\t- Si las salidas están vacías, sólo se podrá mover a ellas un AS.\n\t\t\t- Si las Columnas están vacías, sólo se podrá mover a ellas un REY.\n\t\t\t- A las salidas sólo se podrán mover cartas del mismo palo, desde el AS hasta el REY.\n\t\t\t- Para completar el juego, deben juntarse en las 4 salidas las 12 cartas de cada palo.\n\t\t\t- Sólo se podrán devolver las cartas de descarte a mazo 3 veces. A la tercera, se acabará el juego.\n\t\t\t- No se podrán mover pilas de cartas que impliquen alguna carta boja-abajo."); atributo(0);

atributo(1); atributo(4); atributo(95); printf("\n\n\n\t\tVolver al menú principal:"); atributo(0);
atributo(1); atributo(95); printf("\n\t\t\t- Si en algún momento durante el transcurso del juego se desea volver al menú principal, se debe introducir el carácter 'm'.\n\t\t\t- Si se introduce un movimiento que, por error, empieza por carácter, se obligará al jugador a volver al menú principal."); atributo(0);

atributo(1); atributo(3); atributo(4); atributo(92); printf("\n\nJuego desarrollado por:"); atributo(0); atributo(1); atributo(3); atributo(92); printf("\n\tDavid Cordeiro de la Torre\n\tJosé Vilas Villamarín\n\tPedro Tubío Figueira\n"); atributo(91); printf("\nEscuela Técnica Superior de Ingeniería de Telecomunicación. Universidad de Vigo."); fgets(cosa,50,stdin);
}

/* Esta función recorre el juego con todas las permutaciones posibles hasta encontrar un movimiento posible que no sea mazo-descarte o descarte-mazo. Si solo hay este, será el que se muestre. */

int pistas(naipe mazo[14][48], pista ayuda[2]){

  int origen=0, destino=1, cantidad=1, parametros=1;
  int pistaValida;
  int cantPistas=0;

  for(parametros=1; parametros<2; parametros++){
    for(origen=0; origen<=13; origen++){
      for(destino=0; destino<=13; destino++){
        for(cantidad=1; cantidad<=13; cantidad++){
	  pistaValida=comprobarMovimiento(mazo,origen,destino,cantidad,parametros);
	  if (pistaValida==1){
	    ayuda[cantPistas].origen=origen;
	    ayuda[cantPistas].destino=destino;
	    ayuda[cantPistas].cantidad=cantidad;
	    cantPistas++;
          }
	
	  if(cantPistas==2) return 1;
	}
      }
    }
  }

return 0;
}

/* Crea un perfil de juego para recopilar estadísticas. */

int createProfile (naipe mazo[14][48], jugador perfil[2]){

  imprimirTapete(mazo);

  perfil[0].partidasIniciadas=0;
  perfil[0].partidasCompletadas=0;
  perfil[0].maximaPuntuacion=0;
  perfil[0].porcentajeVictorias=0;
  perfil[1].partidasIniciadas=0;
  perfil[1].partidasCompletadas=0;
  perfil[1].maximaPuntuacion=0;
  perfil[1].porcentajeVictorias=0;

  gotoxy(0,30); atributo(1); atributo(3);
  printf("\tIntroduce un nombre para tu nuevo perfil: ");
  memset(perfil[0].nombre,'\0', strlen(perfil[0].nombre));
  fgets(perfil[0].nombre, 20, stdin);



  FILE *pf;

  if((pf=fopen(perfil[0].nombre,"wb"))==NULL) return 0; 
  fwrite(perfil,sizeof(jugador[2]),1,pf);
  fclose(pf);

return 1;
}

/* Al ejecutar el juego, se pedirá al usuario que cargue un perfil ya existente. */
int choseProfile (naipe mazo[14][48], jugador perfil[2]){

  imprimirTapete(mazo);

  gotoxy(0,30); atributo(1); atributo(3);
  printf("\tIntroduce el nombre de tu perfil: ");
  memset(perfil[0].nombre,'\0', strlen(perfil[0].nombre));
  fgets(perfil[0].nombre, 20, stdin);

  FILE *pf;

  if((pf=fopen(perfil[0].nombre,"r"))==NULL) return 0; 
  fread(perfil,sizeof(jugador[2]),1,pf);
  fclose(pf);

return 1;
}

/* Muestra las estadísticas del jugador */

void optionsProfile(jugador perfil[2]){

  char cosa[50];
  system("clear");
  atributo(1); atributo(91); printf("\n\n\tESTADÍSTICAS DEL PERFIL %s.", perfil[0].nombre);

  atributo(1); atributo(4); atributo(96); printf("\n\n\t\tJuego general:"); atributo(0);
  atributo(1); atributo(96); printf("\n\t\t\t- Total de partidas jugadas: %i\n\t\t\t- Total de partidas ganadas: %i\n\t\t\t- Porcentaje de victorias: %f por ciento.\n\t\t\t- Mayor puntuación lograda: %i",perfil[0].partidasIniciadas, perfil[0].partidasCompletadas, perfil[0].porcentajeVictorias, perfil[0].maximaPuntuacion); atributo(0);

  atributo(1); atributo(4); atributo(93); printf("\n\n\n\t\tEstadísticas de sesión"); atributo(0);
  atributo(1); atributo(93); printf("\n\t\t\t- Partidas iniciadas hoy: %i\n\t\t\t- Partidas ganadas hoy: %i", perfil[0].partidasIniciadas-perfil[1].partidasIniciadas, perfil[0].partidasCompletadas-perfil[1].partidasCompletadas); atributo(0);

  fgets(cosa,50,stdin);


}

/* Muestra las 3 mayores puntuaciones hasta el momento (guardadas en un archivo). */

void hallOfFame(jugador HOF[3]){

  char cosa[50];
  system("clear");
  atributo(1); atributo(91); printf("\n\n\tHALL OF FAME DEL SOLITARIO.");

  atributo(1); atributo(4); atributo(96); printf("\n\n\t\tNº 1:"); atributo(0);
  atributo(1); atributo(96); printf("\n\t\t\t- Nombre: %s\n\t\t\t- Mejor puntuación: %i\n",HOF[0].nombre, HOF[0].maximaPuntuacion); atributo(0);

  atributo(1); atributo(4); atributo(96); printf("\n\n\t\tNº 2:"); atributo(0);
  atributo(1); atributo(96); printf("\n\t\t\t- Nombre: %s\n\t\t\t- Mejor puntuación: %i\n",HOF[1].nombre, HOF[1].maximaPuntuacion); atributo(0);

  atributo(1); atributo(4); atributo(96); printf("\n\n\t\tNº 3:"); atributo(0);
  atributo(1); atributo(96); printf("\n\t\t\t- Nombre: %s\n\t\t\t- Mejor puntuación: %i\n",HOF[2].nombre, HOF[2].maximaPuntuacion); atributo(0);

  fgets(cosa,50,stdin);

}

/* Comprueba al finalizar un juego si se ha conseguido un nuevo record de puntos. */

void revisarHOF(jugador HOF[3], jugador perfil[2]){

int k;

k=perfil[0].maximaPuntuacion;

if(HOF[0].maximaPuntuacion<k) {


  HOF[2]=HOF[1];
  HOF[1]=HOF[0];
  HOF[0]=perfil[0];

  return;

}

if(HOF[1].maximaPuntuacion<k) {


  HOF[1]=HOF[0];
  HOF[0]=perfil[0];

  return;

}

if(HOF[2].maximaPuntuacion<k) {


  HOF[0]=perfil[0];

  return;

}


}
