/*
	Autor: Victor Manuel Gomez Solis
	Fecha: Junio 2021
	Descripcion: Este programa genera un menu en el cual se tienen varias operaciones para un alumno:
	altas, bajas, modificaciones y consultas.
	El manejo de la informacion se realiza en un archivo de texto (txt).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 5

typedef struct{
	char cNombreMateria[25];
	int iNumParciales;
	int iParciales[5];
}MATERIA;

typedef struct{
	int iClave;
	int iNumMaterias;
	char cNombre[30];
	MATERIA mMaterias[7];
}ALUMNO;

void Menu();
void CapturaDatos(char cArchivoF[15], ALUMNO aAl[n], int iCont);
void CapturaMaterias(char cArchivoF[15], ALUMNO aAl[n], int iCont);
void BajaAlumno(ALUMNO aAl[n], int iCont);
void ModificaAlumno(ALUMNO aAl[n], int iCont);
void ModificaMateria(ALUMNO aAl[n], int iNum);
void Sobreescribe(char cArchivoF[15], ALUMNO aAl[n], int iCont);
void ConsultaAlumno(ALUMNO aAl[n], int iCont);

int main(){
	Menu();
	printf("%cGracias por usar nuestro sistema!",173);
	return 0;
}

void Menu(){
	int iContador=0;
	char cOp;
	ALUMNO aAlumnos[n];
	do{
		printf("                  ||SISTEMA DE MATERIAS||\n");
		printf("[1] Dar de alta a un alumno\n");
		printf("[2] Dar de baja a un alumno                         Presione [ESC] para salir\n");
		printf("[3] Modificar a un alumno\n");
		printf("[4] Consultar informaci%cn de un alumno\n\n",162);
		printf("Seleccione una opci%cn ->",162);
		cOp=getch();
		system("cls");
		switch(cOp){
			case '1': CapturaDatos("Bases2020.txt", aAlumnos, iContador);
			          CapturaMaterias("Bases2020.txt", aAlumnos, iContador);
					  iContador++;
					  break;
			case '2': BajaAlumno(aAlumnos, iContador);
					  Sobreescribe("Bases2020.txt", aAlumnos, iContador);
					  break;
			case '3': ModificaAlumno(aAlumnos, iContador);
					  Sobreescribe("Bases2020.txt", aAlumnos, iContador);
					  break;
			case '4': ConsultaAlumno(aAlumnos, iContador);
					  break;
		}
		system("cls");
	}while(cOp!=27);
}

void CapturaDatos(char cArchivoF[15], ALUMNO aAl[n], int iCont){
	FILE *fArchivo;
	fArchivo=fopen(cArchivoF,"a");
	printf("Ingrese la clave del alumno: ");
	scanf("%d",&aAl[iCont].iClave);
	fprintf(fArchivo,"%d ",aAl[iCont].iClave);
	printf("Ingrese el nombre del alumno: ");
	fflush(stdin);
	gets(aAl[iCont].cNombre);
	fprintf(fArchivo,"%s",aAl[iCont].cNombre);
	fflush(stdin);
	fclose(fArchivo);
}

void CapturaMaterias(char cArchivoF[15], ALUMNO aAl[n], int iCont){
	int i, j, iSum;
	FILE *fArchivo;
	fArchivo=fopen(cArchivoF,"a");
	printf("\n%cCuantas materias agregaras? >",168);
	scanf("%d",&aAl[iCont].iNumMaterias);
	system("cls");
	if(aAl[iCont].iNumMaterias!=0 && aAl[iCont].iNumMaterias<8){
		for(i=0;i<aAl[iCont].iNumMaterias;i++){
			iSum=0;
			printf("Ingrese el nombre de la materia: ");
			fflush(stdin);
			gets(aAl[iCont].mMaterias[i].cNombreMateria);
			fprintf(fArchivo," |%s| ",aAl[iCont].mMaterias[i].cNombreMateria);
			fflush(stdin);
			printf("\n%cCuantos parciales agregaras a la materia %s? >",168,aAl[iCont].mMaterias[i].cNombreMateria);
			scanf("%d",&aAl[iCont].mMaterias[i].iNumParciales);
			for(j=0;j<aAl[iCont].mMaterias[i].iNumParciales;j++){
				printf("   Ingrese la calificaci%cn del parcial %d: ",162,j+1);
				scanf("%d",&aAl[iCont].mMaterias[i].iParciales[j]);
				if(iSum==aAl[iCont].mMaterias[i].iNumParciales-1)
					fprintf(fArchivo,"%d",aAl[iCont].mMaterias[i].iParciales[j]);
				else
					fprintf(fArchivo,"%d ",aAl[iCont].mMaterias[i].iParciales[j]);
				iSum++;
			}
			system("cls");
		}
	}
	fprintf(fArchivo,"\n");
	fclose(fArchivo);
}

void BajaAlumno(ALUMNO aAl[n], int iCont){
	int i, iClave;
	printf("Ingrese la clave del alumno a eliminar:-> ");
	scanf("%d",&iClave);
	for(i=0;i<iCont;i++){
		if(aAl[i].iClave==iClave)
			aAl[i].iClave=-666;
	}
}

void ModificaAlumno(ALUMNO aAl[n], int iCont){
	int i, iClave, iBand=0, cOp;
	printf("Ingrese la clave del alumno a modificar:-> ");
	scanf("%d",&iClave);
	system("cls");
	for(i=0;i<iCont;i++){
		if(aAl[i].iClave==iClave){
			iBand=1;
			printf("[1] Modificar nombre\n");
			printf("[2] Modificar calificaci%cn de una materia\n\n",162);
			printf("Seleccione una opci%cn ->",162);
			cOp=getch();
			system("cls");
			switch(cOp){
				case '1': printf("Ingrese el nuevo nombre: ");
					      fflush(stdin);
						  gets(aAl[i].cNombre);
						  fflush(stdin);
						  break;
				case '2': ModificaMateria(aAl, i);
						  break;
			}		
		}
	}
	if(iBand==0){
		printf("El alumno con la clave %d no se encuentra en nuestro sistema.\n",iClave);
		system("pause");
	}
}

void ModificaMateria(ALUMNO aAl[n], int iNum){
	int i, j, iBand=0;
	char cMateria[25];
	printf("Ingrese el nombre de la materia a modificar: ");
	fflush(stdin);
	gets(cMateria);
	fflush(stdin);
	for(i=0;i<aAl[iNum].iNumMaterias;i++){
		if(strcmp(cMateria,aAl[iNum].mMaterias[i].cNombreMateria)==0){
			iBand=1;
			printf("\n%cCuantos parciales agregaras a la materia %s? >",168,aAl[iNum].mMaterias[i].cNombreMateria);
			scanf("%d",&aAl[iNum].mMaterias[i].iNumParciales);
			for(j=0;j<aAl[iNum].mMaterias[i].iNumParciales;j++){
				printf("   Ingrese la calificaci%cn del parcial %d: ",162,j+1);
				scanf("%d",&aAl[iNum].mMaterias[i].iParciales[j]);
			}
		}
	}
	if(iBand==0){
		printf("\nEl alumno no cursa la materia %s.\n",cMateria);
		system("pause");
	}
}

void Sobreescribe(char cArchivoF[15], ALUMNO aAl[n], int iCont){
	int i, j, k, iSum;
	FILE *fArchivo;
	fArchivo=fopen(cArchivoF,"w");
	for(i=0;i<iCont;i++){
		if(aAl[i].iClave!=-666){
			fprintf(fArchivo,"%d ",aAl[i].iClave);
			fprintf(fArchivo,"%s",aAl[i].cNombre);
			for(j=0;j<aAl[i].iNumMaterias;j++){
				iSum=0;
				fprintf(fArchivo," |%s| ",aAl[i].mMaterias[j].cNombreMateria);
				for(k=0;k<aAl[i].mMaterias[j].iNumParciales;k++){
					if(iSum==aAl[i].mMaterias[j].iNumParciales-1)
						fprintf(fArchivo,"%d",aAl[i].mMaterias[j].iParciales[k]);
					else
						fprintf(fArchivo,"%d ",aAl[i].mMaterias[j].iParciales[k]);
					iSum++;
				}
			}
			fprintf(fArchivo,"\n");
		}
	}
	fclose(fArchivo);
}

void ConsultaAlumno(ALUMNO aAl[n], int iCont){
	int i, j, k, iClave, iBand=0;
	printf("Ingrese la clave del alumno a consultar:-> ");
	scanf("%d",&iClave);
	system("cls");
	for(i=0;i<iCont;i++){
		if(aAl[i].iClave==iClave){
			iBand=1;
			printf("Alumno: %s\n",aAl[i].cNombre);
			printf("Clave: %d\n\n",aAl[i].iClave);
			printf("     --Materias cursadas--\n");
			for(j=0;j<aAl[i].iNumMaterias;j++){
				printf("%s\n",aAl[i].mMaterias[j].cNombreMateria);
				printf("\nCalificaciones\n");
				for(k=0;k<aAl[i].mMaterias[j].iNumParciales;k++)
					printf("Calificaci%cn parcial %d: %d\n",162,k+1,aAl[i].mMaterias[j].iParciales[k]);
				printf("\n\n");
			}
		}
	}
	if(iBand==0)
		printf("El alumno con la clave %d no se encuentra en nuestro sistema.\n",iClave);
	system("pause");
}
