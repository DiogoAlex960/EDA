#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Estruturas.h"

//Apontador
int Valor(int Maximo, int Minimo)
{
    int num = -1;

    printf("\nVoce esta aqui - ");
    scanf(" %d", &num);

    while (num > Maximo || num < Minimo)
    {
        printf("\nFail\n");
        printf("\nVoce esta aqui - ");
        scanf(" %d", &num);
    }
    system("cls");
    return num;
}


Job* LerFicheiro()
{
    FILE* Ficheiro;
    int Temp, IdOperacoes, IdMaquinas, TempoMaquinas;
    Operacao* auxOperacao,* ListaDeOperacoes = NULL;
    Maquina* auxMaquina,* ListaDeMaquinas = NULL;
    Job* ListaDeJobs = NULL;

    Ficheiro = fopen("Jobs.txt", "r");

    if (Ficheiro == NULL)
    {
        return false;
    }

    while (!feof(Ficheiro))
    {
        while (fscanf(Ficheiro, "%d", &IdMaquinas) == 1)
        {
            fscanf(Ficheiro, " %d", &TempoMaquinas);
            auxMaquina = CriaMaquina(IdMaquinas, TempoMaquinas);
            ListaDeMaquinas = InsereMaquina(&ListaDeMaquinas, auxMaquina);

            fscanf(Ficheiro, "%*c");
        }
        fscanf(Ficheiro, " %d", &IdOperacoes);
        auxOperacao = CriaOperacao(IdOperacoes);
        auxOperacao->Maquinas = ListaDeMaquinas;
        ListaDeOperacoes = InsereOperacao(&ListaDeOperacoes, auxOperacao);
        ListaDeMaquinas = NULL;
    }

    Job* auxJob = CriaJob(1);
    auxJob->Operacoes = ListaDeOperacoes;
    ListaDeJobs = InsereJob(&ListaDeJobs, auxJob);

    return ListaDeJobs;
}

Operacao* CriaOperacao(int Id)
{
}



Operacao* InsereOperacao(Operacao** ListaDeOperacoes, Operacao* NovaOperacao)
{
}

Operacao* MenuRemoveOperacao(Operacao* ListaDeOperacoes, int Id)
{~}

Operacao* ProcuraOperacao(Operacao* ListaDeOperacoes, int Id)
{
}

int TempoMinimoDaOperacao(Operacao* ListaDeOperacoes, int Id)
{
}

//Calcular o tempo médio da operação
//Calcular o tempo maximo da operação
//Verificar se a operação existe
//Visualizar ID´s das operações
//Inserir uma maquina
//Criar uma Maquina
//Remover uma determinada maquina

//Procurar uma maquina
//Verificar se existe a maquina
//Inserir um JOB
//Procurar um JOB
//Calcuar tempo minimo de um Job
//Calcular tempo maximo de um job


