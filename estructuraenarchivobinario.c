/*
	Autor: Victor Manuel Gomez Solis
	Fecha: Junio 2021
	Descripcion: Este programa genera un menu en el cual se tienen varias operaciones para un alumno:
	altas, bajas, modificaciones y consultas.
	El manejo de la informacion se realiza en un archivo de texto (txt).
*/

#include <stdio.h>
#include <stdlib.h>
#define n 50

typedef struct{
	int iEdad;
	char cClave[8];
	char cNombre[31];
}ALUMNO;

void LeeArchivo(char cDatos1[15], char cDatos2[15], char cDatos3[15]);
void Guarda(char cDatos1[15], char cDatos2[15], char cDatos3[15], ALUMNO aAl[n], int *iRen);
void Inserta(char cArchivoB[15], ALUMNO aAl[n], int iRen);

int main(){
	ALUMNO aAlumno[n];
	char cOp;
	int iRenglones;
    do{
        printf("             Estructura a Archivo Binario\n");
		printf("1. Verificar si los archivos estan localizados\n");
		printf("2. Guardar los datos de los archivos de texto en una estructura                Presione <ESC> para salir\n");
		printf("3. Guardar la estructura en un archivo binario\n\n");
		printf("Seleccione una opci%cn:>",162);
		cOp=getch();
		system("cls");
		switch(cOp){
			case '1': LeeArchivo("Edades.txt", "Claves.txt", "Nombres.txt");
					  break;
			case '2': Guarda("Edades.txt", "Claves.txt", "Nombres.txt", aAlumno, &iRenglones);
					  break;
			case '3': Inserta("Estructura.dat", aAlumno, iRenglones);
					  break;
		}
		system("cls");
	}while(cOp!=27);
	printf("%cGracias por usar mi programa!",173);
    return 0;
}

void LeeArchivo(char cDatos1[15], char cDatos2[15], char cDatos3[15]){
    FILE *fArchivo1, *fArchivo2, *fArchivo3;
    fArchivo1=fopen(cDatos1,"r");
    fArchivo2=fopen(cDatos2,"r");
    fArchivo3=fopen(cDatos3,"r");
    if(fArchivo1!=NULL && fArchivo2!=NULL && fArchivo3!=NULL)
        printf("\n       ***Los 3 archivos han sido localizados.***\n\n");
    else
        printf("\n       ***Alguno de los archivos no esta localizado.***\n");
    fclose(fArchivo1);
    fclose(fArchivo2);
    fclose(fArchivo3);
    system("pause");
}

void Guarda(char cDatos1[15], char cDatos2[15], char cDatos3[15], ALUMNO aAl[n], int *iRen){
	int i=0;
	FILE *fArchivo1, *fArchivo2, *fArchivo3;
    fArchivo1=fopen(cDatos1,"r");
    fArchivo2=fopen(cDatos2,"r");
    fArchivo3=fopen(cDatos3,"r");
	do{
    	fscanf(fArchivo1,"%d",&aAl[i].iEdad);
		fscanf(fArchivo1,"\n");
		fgets(aAl[i].cClave,8,fArchivo2);
		fscanf(fArchivo2,"\n");
		fgets(aAl[i].cNombre,31,fArchivo3);
		fscanf(fArchivo3,"\n");
		i++;
	}while(!feof(fArchivo1) && !feof(fArchivo2) && !feof(fArchivo3));
	*iRen=i;
	fclose(fArchivo1);
    fclose(fArchivo2);
    fclose(fArchivo3);
}

void Inserta(char cArchivoB[15], ALUMNO aAl[n], int iRen){
	FILE *fArchivo;
	int i;
	fArchivo=fopen(cArchivoB,"wb");
	for(i=0;i<iRen;i++)
		fwrite(&aAl[i],sizeof(ALUMNO),1,fArchivo);
	fclose(fArchivo);
}
