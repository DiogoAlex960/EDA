

#ifndef Structs
#define Structs

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#pragma region GravarFicheiros
void GravarFicheiro(Operacao* ListaDeOperacoes);
Job* LerFicheiro();

#pragma endregion
#pragma region Estruturas
typedef struct Operacao
{
    int Id;//Contem um ID
    struct Maquina* Maquinas;//Contem Nº Maquinas
    struct Operacao* Next; // Proxima Operação
} Operacao;

typedef struct Maquina
{
    int Id;//Contem ID
    int Tempo;//Contem Tempo
    struct Maquina* Next;//Proxima Máquina
} Maquina;


typedef struct Job
{
    int Id;//Contem um ID
    struct Operacao* Operacoes;//Contem Nº uma Operação
    struct Job* Next;////Proximo Job
} Job;


#pragma endregion

#pragma region Externas
extern Operacao* ListaDeOperacoes;
extern Maquina* ListaDeMaquinas; //Declaração fora Função
extern Job* ListaDeJobs;
#pragma endregion


#pragma region Jobs

Job* CriaJob(int Id);
Job* InsereJob(Job** ListaDeJobs, Job* NovoJob);
Job* ProcuraJob(Job* ListaDeJobs, int Id);
void MostraListaJob(Job* ListaDeJobs);
bool ExisteJob(Job* ListaDeJobs, int Id);
int TempoMinimoJob(Job* ListaDeJobs, int Id);
int TempoMaximoJob(Job* ListaDeJobs, int Id);


#pragma endregion

