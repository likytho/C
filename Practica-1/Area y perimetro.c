//Programa que, dadas la base y la altura, calcula el perímietro y el área de un triángulo.

#include <stdio.h>
#include <math.h>

int main (){
 int base,altura;
 float area;
 float perimetro;
 float hipotenusa;

printf("Por favor, introduzca base y altura\n");
scanf("%i%i",&base,&altura); //%i Lee variables enteras

 area = (1.0*base*altura)/2; //Se convierte uno de los operandos en real con el 1.0* para que muestre los decimales correctamente
hipotenusa = sqrt((base*base)+(altura*altura));
perimetro = base+altura+hipotenusa;

//Mostrar los resultados

printf("ALTURA: %i\t\tcm\n",altura);
printf("BASE: %i\t\tcm\n",base);
printf("AREA: %.2f\t\tcm\n",area);
printf("PERIMETRO: %.2f\tcm\n",perimetro);


return 0;
}
