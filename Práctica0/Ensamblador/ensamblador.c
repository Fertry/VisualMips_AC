#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TAMTABLASIMB 200

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct st_etiqueta
{
	char id[256];
	u16 dir;
} tEtiqueta;

tEtiqueta tsimb[TAMTABLASIMB];
int itsimb=0;

char nffuente[1024];
char nfobjeto[1024];

int ContadorPosiciones=0;
int NumeroLinea=0;
u16 DirInicial=0, DirExec=0;

void fin_programa (void)
{
    printf ("\nPrograma ENSAMBLADOR terminado. Pulse una tecla para salir.\n");
    fflush (stdin);
    getchar();
}

void QuitarComentarios (char *linea)
{
	int i;
	
	for (i=0;i<strlen(linea);i++)
		if (linea[i]==';')
		{
			linea[i]='\0';
			break;
		}
}

void QuitarEspacios (char *linea)
{
	int i;
	int j=0;
	
	for (i=0;i<strlen(linea);i++)
		if (!isspace(linea[i]))
			linea[j++]=linea[i];
	linea[j]='\0';
}

void QuitarEtiqueta (char *linea)
{
	int i;
	int j=0;
	
	for (i=0;i<strlen(linea);i++)
		if (linea[i]==':')
		{
			while (i<strlen(linea))
				linea[j++]=linea[++i];
			linea[j]='\0';
			break;
		}
}

void PasarMinusculas (char *linea)
{
	strlwr(linea);
}

u16 BuscarValorEtiqueta (char *id)
{
	int i;
	
	for (i=0;i<itsimb;i++)
		if (!strcmp(tsimb[i].id, id))
			break;
	
	if (i==itsimb)
	{
		printf ("ERROR en linea %d. La etiqueta '%s' no esta definida.\n", NumeroLinea, id);
		exit(1);
	}
	return tsimb[i].dir;
}

int ValorExpresion (char *s)
{
	char temp[1024];
	int v;
	
	if (!strncmp(s,"hi(",3))
	{
		strcpy (temp, s+3);
		temp[strlen(temp)-1]='\0';
		v=ValorExpresion(temp);
		return (((v&0xFFFF)>>8)&0xFF);
	}
	else if (!strncmp(s,"lo(",3))
	{
		strcpy (temp, s+3);
		temp[strlen(temp)-1]='\0';
		v=ValorExpresion(temp);
		return (v&0xFF);
	}
	else if (!strncmp(s,"0x",2))
	{
		sscanf (s+2,"%x",&v);
		return v;
	}
	else if ((s[0]>='0' && s[0]<='9') || s[0]=='-')
	{
		sscanf (s,"%d",&v);
		return v;
	}
	else
		return DirInicial+BuscarValorEtiqueta(s);
}

int PosicionesOcupadasDS (char *linea)
{
	int pos;
	
	pos=ValorExpresion(linea+2);
	if (pos<0)
		pos=0;
	return pos;
}

void PosicionesOcupadas (char *linea)
{
	if (!strncmp (linea,"org",3))
		return;
	else if (!strncmp (linea,"ent",3))
		return;
	else if (!strncmp (linea,"ds",2))
		ContadorPosiciones+=PosicionesOcupadasDS (linea);
	else if (strlen(linea)>0)
		ContadorPosiciones++;
}

void AddEtiqueta (char *linea)
{
	int i;
	int j=0;
	tEtiqueta et;
	
	et.dir=0;
	for (i=0;i<strlen(linea);i++)
	{
		et.id[i]=linea[i];
		if (linea[i]==':')
		{
			et.id[i]='\0';
			et.dir=ContadorPosiciones;
			break;
		}
	}
	
	if (i<strlen(linea))
	{
		for (j=0;j<itsimb;j++)
			if (tsimb[j].id==et.id)
			{
				printf ("ERROR en linea %d. La etiqueta '%s' esta duplicada.\n", NumeroLinea, et.id);
				exit(1);
			}
		if (itsimb==TAMTABLASIMB)
		{
			printf ("ERROR en linea %d. Se ha excedido el numero de etiquetas permitidas (%d)\n", NumeroLinea, TAMTABLASIMB);
			exit(1);
		}
		tsimb[itsimb++]=et;
	}
}

void PrimeraPasada (void)
{
	FILE *f;
	char linea[1024];
	
	f=fopen(nffuente,"rt");
	if (!f)
	{
		printf ("ERROR. No se puede leer el fichero %s\n", nffuente);
		exit(1);
	}

	ContadorPosiciones=0;
	NumeroLinea=1;
	fgets (linea,1023,f);
	while (!feof(f))
	{
		PasarMinusculas (linea);
		QuitarComentarios (linea);
		QuitarEspacios (linea);
		AddEtiqueta (linea);
		QuitarEtiqueta (linea);
		PosicionesOcupadas (linea);
		fgets (linea,1023,f);
		NumeroLinea++;
	}
	fclose(f);
}

void Ensamblar (char *linea, FILE *fsalida)
{
	int i;
	u16 valor;
	s16 desplaz;
	u8 inm8, nri, nrs, nr1, nr2, nrd, nrds;
	
	if (!strncmp (linea,"org",3))
	{
		DirInicial=ContadorPosiciones=ValorExpresion(linea+3);
		printf ("%4.4X        ", ContadorPosiciones);
		fprintf (fsalida, "%4.4X\n", DirInicial);
	}
	else if (!strncmp (linea,"ent",3))
	{
		DirExec=ValorExpresion(linea+3);
		printf ("      %4.4X  ", DirExec);
		fprintf (fsalida, "%4.4X\n", DirExec);
	}
	else if (!strncmp (linea,"dw",2))
	{
		valor=ValorExpresion(linea+2);
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, valor);
		fprintf (fsalida, "%4.4X\n", valor);
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"ds",2))
	{
		valor=ValorExpresion(linea+2);
		printf ("%4.4X  ....  ", ContadorPosiciones);
		for (i=0;i<valor;i++)
			fprintf (fsalida, "0000\n");
		ContadorPosiciones+=valor;
	}
	else if (!strncmp (linea,"movlr",5))  /* 00 100 Rd inm8 */
	{
		nrd=linea[5]-'0';
		if (nrd>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		inm8=ValorExpresion(linea+7);
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x2000 | (nrd)<<8 | inm8);
		fprintf (fsalida, "%4.4X\n", 0x2000 | (nrd)<<8 | inm8);
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"movhr",5))  /* 00 101 Rd inm8 */
	{
		nrd=linea[5]-'0';
		if (nrd>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		inm8=ValorExpresion(linea+7);
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x2800 | (nrd)<<8 | inm8);
		fprintf (fsalida, "%4.4X\n", 0x2800 | (nrd)<<8 | inm8);
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"mov[r",5))  /* 00 010 Ri Rs 00000 */
	{
		nri=linea[5]-'0';
		nrs=linea[9]-'0';
		if (nrs>7 || nri>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x1000 | (nri<<8) | (nrs<<5));
		fprintf (fsalida, "%4.4X\n", 0x1000 | (nri<<8) | (nrs<<5));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"movr",4) && !strncmp(linea+6,"[r",2))  /* 00 001 Rd Ri 00000 */
	{
		nrd=linea[4]-'0';
		nri=linea[8]-'0';
		if (nrd>7 || nri>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x0800 | (nrd<<8) | (nri<<5));
		fprintf (fsalida, "%4.4X\n", 0x0800 | (nrd<<8) | (nri<<5));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"movr",4))  /* 00 000 Rd Rs 00000 */
	{
		nrd=linea[4]-'0';
		nrs=linea[7]-'0';
		if (nrd>7 || nrs>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, (nrd<<8) | (nrs<<5));
		fprintf (fsalida, "%4.4X\n", (nrd<<8) | (nrs<<5));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"stop",4))   /* 3800h */
	{
		printf ("%4.4X  3800  ", ContadorPosiciones);
		fprintf (fsalida, "3800\n");
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"addr",4))  /* 01 00000 Rd Rs1 Rs2 */
	{
		nrd=linea[4]-'0';
		nr1=linea[7]-'0';
		nr2=linea[10]-'0';
		if (nrd>7 || nr1>7 || nr2>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x4000 | (nrd<<6) | (nr1<<3) | nr2);
		fprintf (fsalida, "%4.4X\n", 0x4000 | (nrd<<6) | (nr1<<3) | nr2);
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"subr",4))  /* 01 00001 Rd Rs1 Rs2 */
	{
		nrd=linea[4]-'0';
		nr1=linea[7]-'0';
		nr2=linea[10]-'0';
		if (nrd>7 || nr1>7 || nr2>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x4200 | (nrd<<6) | (nr1<<3) | nr2);
		fprintf (fsalida, "%4.4X\n", 0x4200 | (nrd<<6) | (nr1<<3) | nr2);
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"orr",3))  /* 01 00010 Rd Rs1 Rs2 */
	{
		nrd=linea[3]-'0';
		nr1=linea[6]-'0';
		nr2=linea[9]-'0';
		if (nrd>7 || nr1>7 || nr2>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x4400 | (nrd<<6) | (nr1<<3) | nr2);
		fprintf (fsalida, "%4.4X\n", 0x4400 | (nrd<<6) | (nr1<<3) | nr2);
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"andr",4))  /* 01 00011 Rd Rs1 Rs2 */
	{
		nrd=linea[4]-'0';
		nr1=linea[7]-'0';
		nr2=linea[10]-'0';
		if (nrd>7 || nr1>7 || nr2>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x4600 | (nrd<<6) | (nr1<<3) | nr2);
		fprintf (fsalida, "%4.4X\n", 0x4600 | (nrd<<6) | (nr1<<3) | nr2);
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"xorr",4))  /* 01 00100 Rd Rs1 Rs2 */
	{
		nrd=linea[4]-'0';
		nr1=linea[7]-'0';
		nr2=linea[10]-'0';
		if (nrd>7 || nr1>7 || nr2>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x4800 | (nrd<<6) | (nr1<<3) | nr2);
		fprintf (fsalida, "%4.4X\n", 0x4800 | (nrd<<6) | (nr1<<3) | nr2);
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"compr",5))  /* 01 00111 Rs1 Rs2 000 */
	{
		nr1=linea[5]-'0';
		nr2=linea[8]-'0';
		if (nr1>7 || nr2>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x4E00 | (nr1<<6) | (nr2<<3));
		fprintf (fsalida, "%4.4X\n", 0x4E00 | (nr1<<6) | (nr2<<3));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"notr",4))  /* 01 01000 Rds 000000 */	
	{
		nrds=linea[4]-'0';
		if (nrds>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x5000 | (nrds<<6));
		fprintf (fsalida, "%4.4X\n", 0x5000 | (nrds<<6));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"incr",4))  /* 01 01001 Rds 000000 */	
	{
		nrds=linea[4]-'0';
		if (nrds>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x5200 | (nrds<<6));
		fprintf (fsalida, "%4.4X\n", 0x5200 | (nrds<<6));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"decr",4))  /* 01 01010 Rds 000000 */	
	{
		nrds=linea[4]-'0';
		if (nrds>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x5400 | (nrds<<6));
		fprintf (fsalida, "%4.4X\n", 0x5400 | (nrds<<6));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"negr",4))  /* 01 01011 Rds 000000 */	
	{
		nrds=linea[4]-'0';
		if (nrds>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x5600 | (nrds<<6));
		fprintf (fsalida, "%4.4X\n", 0x5600 | (nrds<<6));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"clrr",4))  /* 01 01100 Rds 000000 */	
	{
		nrds=linea[4]-'0';
		if (nrds>7)
		{
			printf ("ERROR en linea %d. El numero de registro es erroneo.\n", NumeroLinea);
			exit(1);
		}
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x5800 | (nrds<<6));
		fprintf (fsalida, "%4.4X\n", 0x5800 | (nrds<<6));
		ContadorPosiciones++;
	}
	else if (!strncmp (linea,"jmp",3))   /* 10 desplaz14 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+3)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0x8000 | (desplaz&0x3FFF));
		fprintf (fsalida,"%4.4X\n", 0x8000 | (desplaz&0x3FFF));
	}
	else if (!strncmp (linea,"brc",3))   /* 11000 desplaz11 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+3)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0xC000 | (desplaz&0x7FF));
		fprintf (fsalida,"%4.4X\n", 0xC000 | (desplaz&0x7FF));
	}
	else if (!strncmp (linea,"brnc",4))   /* 11001 desplaz11 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+4)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0xC800 | (desplaz&0x7FF));
		fprintf (fsalida,"%4.4X\n", 0xC800 | (desplaz&0x7FF));
	}
	else if (!strncmp (linea,"bro",3))   /* 11010 desplaz11 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+3)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0xD000 | (desplaz&0x7FF));
		fprintf (fsalida,"%4.4X\n", 0xD000 | (desplaz&0x7FF));
	}
	else if (!strncmp (linea,"brno",4))   /* 11011 desplaz11 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+4)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0xD800 | (desplaz&0x7FF));
		fprintf (fsalida,"%4.4X\n", 0xD800 | (desplaz&0x7FF));
	}
	else if (!strncmp (linea,"brz",3))   /* 11100 desplaz11 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+3)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0xE000 | (desplaz&0x7FF));
		fprintf (fsalida,"%4.4X\n", 0xE000 | (desplaz&0x7FF));
	}
	else if (!strncmp (linea,"brnz",4))   /* 11101 desplaz11 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+4)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0xE800 | (desplaz&0x7FF));
		fprintf (fsalida,"%4.4X\n", 0xE800 | (desplaz&0x7FF));
	}
	else if (!strncmp (linea,"brs",3))   /* 11110 desplaz11 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+3)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0xF000 | (desplaz&0x7FF));
		fprintf (fsalida,"%4.4X\n", 0xF000 | (desplaz&0x7FF));
	}
	else if (!strncmp (linea,"brns",4))   /* 11111 desplaz11 */
	{
		ContadorPosiciones++;
		desplaz=ValorExpresion(linea+4)-ContadorPosiciones;
		printf ("%4.4X  %4.4X  ", ContadorPosiciones, 0xF800 | (desplaz&0x7FF));
		fprintf (fsalida,"%4.4X\n", 0xF800 | (desplaz&0x7FF));
	}
	else
	{
		printf ("ERROR en linea %d. No se reconoce la instruccion.\n", NumeroLinea);
		exit(1);
	}
}

void SegundaPasada (void)
{
	FILE *f;
	FILE *fo;
	char linea[1024];
	char lineao[1024];
	
	f=fopen(nffuente,"rt");
	if (!f)
	{
		printf ("ERROR. No se puede leer el fichero %s\n", nffuente);
		exit(1);
	}

	fo=fopen(nfobjeto,"wt");
	if (!fo)
	{
		printf ("ERROR. No se puede crear el fichero %s\n", nfobjeto);
		exit(1);
	}
		
	ContadorPosiciones=0;
	NumeroLinea=1;
	fgets (lineao,1023,f);
	while (!feof(f))
	{
		strcpy (linea, lineao);
		PasarMinusculas (linea);
		QuitarComentarios (linea);
		QuitarEspacios (linea);
		QuitarEtiqueta (linea);
		printf ("%5d  ", NumeroLinea);
		if (strlen(linea)>0)
			Ensamblar (linea,fo);
		printf ("%s", lineao);
		fgets (lineao,1023,f);
		NumeroLinea++;
	}
	fclose(fo);
	fclose(f);
}

int main (int argc, char *argv[])
{
	atexit(fin_programa);
	if (argc<2)
	{
		printf ("Fichero fuente? ");
		fflush (stdin);
		gets (nffuente);
		strcpy (nfobjeto, "memoria.txt");
	}
	else if (argc<3)
	{
		strcpy (nffuente, argv[1]);
		strcpy (nfobjeto, "memoria.txt");
	}
	else
	{
		strcpy (nffuente, argv[1]);
		strcpy (nfobjeto, argv[2]);
	}
	
	printf ("Ensamblando %s...\n", nffuente);
	printf ("Primera pasada... ");
	PrimeraPasada();
	printf ("OK\nSegunda pasada.\n");
	SegundaPasada();
	printf ("Fichero %s creado.\n", nfobjeto);

	return 0;
}

