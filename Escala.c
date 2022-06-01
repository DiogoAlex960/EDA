//Licenciatura Engenharia Informática Médica
//Diogo Alexandre Mendes Simões Nº15328
//Estrutura de Dados Avançadas


#include <stdio.h>
#include <stdlib.h>
#include "Estrutura.h"
#include "Escala.h"




//-------------------------------------------------------------------------
//void write(FILE *jobFile, job *HeadJob)
{//job *jobTmp = HeadJob;
   maquina *maquinaTmp;
   jobFile = fopen("Gravar.txt", "w");
    while (jobTmp != NULL)
   {
      while (jobTmp->OperacaoHead != NULL)
       {
        fprintf(jobFile, ">");
         
          fprintf(jobFile, ",\n");
           while (maquinaTmp->Anterior != NULL)
           {
              maquinaTmp = maquinaTmp->Anterior;
           }
           fprintf(jobFile, ">");
           fprintf(jobFile, ",\n");
           jobTmp->OperacaoHead = jobTmp->OperacaoHead->Seguinte;
      }
      if (jobTmp->Seguinte != NULL)
           fprintf(jobFile, "\n");
     jobTmp = jobTmp->Seguinte;
 }
   fclose(jobFile);
//}
//----------

//! Calculo do escalonamento
void escalonamento(Processo* inicio) {
	Job* Jobaux = inicio;
	Maquinas* inicioMaquinas = NULL;
	Escalonamento* inserirInicioEscala = NULL;
	Escala* lista = NULL;

void Procura(Job* inicio, Maquinas* inicioMaquinas, Escalonamento* inserirInicioEscala, Escalonamento* inserirInicioEscala) {
//	Job* Jobaux = inicio;
//	Maquinas* auxMaq = inicioMaquinas;
	//getchar(); getchar();
	return 0;
}

