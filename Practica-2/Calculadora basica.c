//Calculadora (switch)

#include <stdio.h>

int main (){
  float A, B, res;
  char simbolo;
  
  printf("Introduzca la operación a realizar: ");
  scanf("%f %c %f",&A, &simbolo, &B);//Respetar loe espacios entre las variables.

  switch(simbolo){
  case '+': res=A+B;
    break;
  case '*': res=A*B;
    break;
  case '-': res=A-B;
    break;
  case '%': res=((int)A)%((int)B);//El int funciona como operador convirtiendo a A y a B en entero.
    break;
}

  printf("El resultado es: %.2f\n",res);

   return 0;
}
