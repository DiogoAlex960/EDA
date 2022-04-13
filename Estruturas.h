

#ifndef Structs
#define Structs

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


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

#pragma region GravarFicheiros
void GravarFicheiro(Operacao* ListaDeOperacoes);
Job* LerFicheiro();

#pragma region Jobs

//Cria um Job
Job* CriaJob(int Id);
//Inserir um Job
Job* InsereJob(Job** ListaDeJobs, Job* NovoJob);
//Procurar um Job
Job* ProcuraJob(Job* ListaDeJobs, int Id);
//Mostrar a lista de Jobs
void MostraListaJob(Job* ListaDeJobs);
//Verificar se existe Job
bool ExisteJob(Job* ListaDeJobs, int Id);
//Visualizar o tempo minimo dos Jobs
int TempoMinimoJob(Job* ListaDeJobs, int Id);
//Visualizar o tempo máximo dos Jobs
int TempoMaximoJob(Job* ListaDeJobs, int Id);


#pragma endregion


#pragma region Operações

//Cria uma Operação
Operacao* CriaOperacao(int Id);

//Insere uma Operação
Operacao* InsereOperacao(Operacao** ListaDeOperacoes, Operacao* NovaOperacao);

//Remove uma Operação
Operacao* RemoveOperacao(Operacao* ListaDeOperacoes, int Id);

//Procura uma Operação
Operacao* ProcuraOperacao(Operacao* ListaDeOperacoes, int Id);

//Troca uma Operação por outra Operação
Operacao* TrocaOperacao(Operacao* ListaDeOperacoes, int IdOperacao, int IdOperacaoTroca);

//Visualisar o tempo minimo da Operação
int TempoMinimoOperacao(Operacao* ListaDeOperacoes, int Id);

//Visualizar o tempo máximo da Operação
int TempoMaximoOperacao(Operacao* ListaDeOperacoes, int Id);

//Visualizar o tempo médio da Operação
float TempoMedioOperacao(Operacao* ListaDeOperacoes, int Id);

//Verificar se existe operação
bool ExisteOperacao(Operacao* ListaDeOperacoes, int Id);

//Mostrar Lista de Operações
void MostraListaOperacoes(Operacao* ListaDeOperacoes);

//Mostrar a operação
void MostraOperacoes(Operacao* ListaDeOperacoes);


#pragma endregion

#pragma region Máquinas
//Cria uma máquina
Maquina* CriaMaquina(int Id, int Tempo);

//Insere a máquina
Maquina* InsereMaquina(Maquina** ListaDeMaquinas, Maquina* NovaMaquina);

//Remove a máquina
Maquina* RemoveMaquina(Maquina* ListaDeMaquinas, int Id);

//Procura a máquina
Maquina* ProcuraMaquina(Maquina* ListaDeMaquinas, int Id);

//Se existe a máquina
bool ExisteMaquina(Maquina* ListaDeMaquinas, int Id);

//Mostra a lista de máquina
void MostraListaDeMaquinas(Maquina* ListaDeMaquinas);

#pragma endregion



#endif
