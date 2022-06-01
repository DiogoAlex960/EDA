//Licenciatura Engenharia Informática Médica
//Diogo Alexandre Mendes Simões Nº15328
//Estrutura Dados Avançadas
#ifndef Structs
#define Structs

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 3

#pragma warning( disable : 4996 )

#pragma region Estruturas

//Jobs
typedef struct Job
{
    int Id;//Cont�m um ID
    struct Operacao* Operacoes;//Cont�m N�Opera��es
    struct Job* Seguinte;////Pr�ximo Job
} Job;
//Maquina
typedef struct Maquina
{
    int Id;//Cont�m ID
    int Tempo;//Cont�m Tempo
    struct Maquina* Seguinte;//Pr�xima M�quina
} Maquina;
//Opera��o
typedef struct Operacao
{
    int Id;//Cont�m um ID
    struct Maquina* Maquinas;//Cont�m N�Maquinas
    struct Operacao* Seguinte; // Pr�xima Opera��o
} Operacao;




//Declara��es Externas
extern Maquina* ListaDeMaquinas;
extern Operacao* ListaDeOperacoes;//Declara��o fora do Contexto
extern Job* ListaDeJobs;

//Auxiliar Menu
int Valor(int Maximo, int Minimo);


//Gravar ficheiro todas as opera��es
void GravarFicheiro(Operacao* ListaDeOperacoes);
Job* LerFicheiro();

//Opera��es


//Criar Opera��o
Operacao* CriaOperacao(int Id);

//Criar Opera��o no Ficheiro
Operacao* CriaOperacaoNoFicheiro(Operacao* ListaDeOperacoes, int Id)

//Inserir uma Nova Opera��o
Operacao* InsereOperacao(Operacao** ListaDeOperacoes, Operacao* NovaOperacao);

//Remover Uma Determinada Opera��o
Operacao* MenuRemoveOperacao(Operacao* ListaDeOperacoes, int Id);

//Procura uma Determinada Opera��o
Operacao* ProcuraOperacao(Operacao* ListaDeOperacoes, int Id);

//Troca uma Opera��o por outra
Operacao* TrocaOperacao(Operacao* ListaDeOperacoes, int IdOperacao, int IdOperacaoTroca);

//Tempo minimo de uma determinada opera��o
int TempoMinimoDaOperacao(Operacao* ListaDeOperacoes, int Id);

//Tempo m�dio de uma opera��o
float TempoMedioDaOperacao(Operacao* ListaDeOperacoes, int Id);

//Tempo Maximo de uma Opera��o
int TempoMaximoDaOperacao(Operacao* ListaDeOperacoes, int Id);

//Verifica se existe uma determinada opera��o
bool ExisteOperacao(Operacao* ListaDeOperacoes, int Id);

//Mostra a lista de todas as opera��es
void MostraListaDeOperacoes(Operacao* ListaDeOperacoes);

//Mostra as opera��es
void MostraOperacoes(Operacao* ListaDeOperacoes);




//Maquinas
//Criar uma maquina
Maquina* CriaMaquina(Maquina* ListaDeMaquinas, int Id, int Tempo);

//Criar Maquina no Ficheiro
Maquina* CriaMaquinaFicheiro(int Id, int Tempo);

//Inserir uma maquina nova
Maquina* InsereMaquina(Maquina** ListaDeMaquinas, Maquina* NovaMaquina);

//Verifica se existe a maquina solicitada
bool ExisteMaquina(Maquina* ListaDeMaquinas, int Id);

//Mostra a lista de maquinas presentes
void MostraListaDeMaquinas(Maquina* ListaDeMaquinas);

//Remove uma determinada maquina
Maquina* RemoveMaquina(Maquina* ListaDeMaquinas, int Id);

//Procura uma determinada maquina
Maquina* ProcuraMaquina(Maquina* ListaDeMaquinas, int Id);



//Jobs
//Cria um Job no ficheiro
Job* CriaJobFicheiro(int Id);

//Cria Job
Job* CriaJob(Job* ListaDeJobs, int Id);

//Insere um determinado Job//**Lista Ligada de uma lista ligada, Um apontador que irá ter outro apontador. Apontadore de Apontadores
Job* InsereJob(Job** ListaDeJobs, Job* NovoJob);

//Verifica de existe um job
bool ExisteJob(Job* ListaDeJobs, int Id);

//Visualiza��o da lista de Jobs
void MostraListaJobs(Job* ListaDeJobs);

//Procura um job existente ou n�o
Job* ProcuraJob(Job* ListaDeJobs, int Id);

//Tempo minino de um determinado job
int TempoMinimoDeJob(Job* ListaDeJobs, int Id);

//Tempo maximo de um  determinado job
int TempoMaximoDeJob(Job* ListaDeJobs, int Id);




//Menus gerais
//Menu principal
void IniciaHash(Job* HashTable[], int Max);

int KeyHash(char* Id);

Job** InserirJobHashTableInicio(Job* HashTable[], Job* JobInserir);

Job* ProcurarJobHashTable(char* Id, Job* HashTable[]);

Job* RemoveJobHashTable(Job* HashTable[], char* Id);

void MostraHashTable(Job* HashTable[]);

#pragma endregion

#endif
