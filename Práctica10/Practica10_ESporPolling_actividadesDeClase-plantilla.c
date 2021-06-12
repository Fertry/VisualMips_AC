//Inclusiones de librerías
#include <stdio.h>
#include <sys/io.h>

// Definición de las constantes utilizadas (Nº puertos)



//Prototipo de la función de lectura de un valor del RTC  (paso 2)
// TODO

//Prototipo de la función de escritura de un valor del RTC  (paso 5)
// TODO

//Prototipo de la función de traducción de unsigned char a BCD empaquetado (paso 5)
// TODO

//Declaración de variable global (facilita la representación del día de la semana)
char* dia_semana[8] = {"Domingo","Domingo","Lunes","Martes","Miercoles","Jueves","Viernes", "Sabado"};

//Función principal
int main()
{
	unsigned char semana, dia, mes, anyo1, anyo2, segundos, minutos, horas, horaModificada;

	//1. Desprotección los puertos de E/S  (paso 1)
	// TO DO
	


	//2. Modificación de la hora: se pide la hora y se actualiza el RTC (paso 5)
	// TO DO




	//3. Bucle continuo{ (paso 4)
	// TO DO




	//3.1. Espera activa mientras el bit 7 del registro 0x0A vale 0 (paso 3)
	// TO DO



	//3.2. Espera activa mientras el bit 7 del registro 0x0A vale 1 (paso 3)
	// TO DO



	//3.3. Lectura de cada dato del RTC y almacenamiento en variables (paso 4)
	// TO DO



	//3.4. Se muestra por pantalla los valores leídos (paso 4) -- TO MODIFY
	printf("", dia_semana[semana], dia, mes, anyo1, anyo2, horas, minutos, segundos);
		//Falta el formato de muestreo
	

	//}Fin Bucle continuo (paso 4)
	// TODO
	
	//Fin del programa
	return 0;
}

//Implementación de la función de lectura de un valor del RTC (paso 2)
// TODO

//Implementación de la función de escritura de un valor del RTC  (paso 5)
// TODO

//Implementación de la función de traducción de unsigned char a BCD empaquetado (paso 5)
// TODO


