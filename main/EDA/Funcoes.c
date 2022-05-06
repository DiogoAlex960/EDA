//Licenciatura Engenharia Informática Médica
//Diogo Alexandre Mendes Simões Nº15328
//Estrutura Dados Avançadas
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Estrutura.h"


//Função Escolha Main
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


#pragma region Jobss

//Gravar informação no Jobs
void GravarJobs(Operacao* ListaDeOperacoes)
{
    FILE* Jobs;
    Jobs = fopen("Jobs.txt", "w");
    while (ListaDeOperacoes != NULL)
    {
        while (ListaDeOperacoes->Maquinas != NULL)
        {
            printf(Jobs, "\n %d \n %d\n", ListaDeOperacoes->Maquinas->Id, ListaDeOperacoes->Maquinas->Tempo);
            ListaDeOperacoes->Maquinas = ListaDeOperacoes->Maquinas->Seguinte;
        }

        printf(Jobs, "- %d", ListaDeOperacoes->Id);
        if (ListaDeOperacoes->Seguinte != NULL)
        {
            printf(Jobs, "\n");
        }
        ListaDeOperacoes = ListaDeOperacoes->Seguinte;
    }
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

    while (!feof(Ficheiro)) //Esta função retorna um valor diferente de zero quando o indicador End-of-File associado ao fluxo é definido, caso contrário, zero é retornado.
    {
        while (fscanf(Ficheiro, "%d", &IdMaquinas) == 1) //A função fscanf() é usada para ler a entrada formatada do fluxo fornecido na linguagem C. Retorna zero, se não for bem-sucedido. Caso contrário, ele retornará A string de entrada, se for bem-sucedida.
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

#pragma endregion

#pragma region Operacoes

//Criar uma operação
Operacao* CriaOperacao(int Id)
{
    Operacao* NovaOperacao = (Operacao*)malloc(sizeof(Operacao));
    if (NovaOperacao == NULL)
    {
        return NULL;
    }

    NovaOperacao->Id = Id;
    NovaOperacao->Maquinas = NULL;
    NovaOperacao->Seguinte = NULL;

    return NovaOperacao;
}

//Inserir uma operação na lista de operações
Operacao* InsereOperacao(Operacao** ListaDeOperacoes, Operacao* NovaOperacao)
{
    NovaOperacao->Seguinte = NULL;

    if (*ListaDeOperacoes == NULL)
    {
        *ListaDeOperacoes = NovaOperacao;
    }
    else
    {
        Operacao* Ultimo = *ListaDeOperacoes;

        while (Ultimo->Seguinte != NULL)
        {
            Ultimo = Ultimo->Seguinte;
        }

        Ultimo->Seguinte = NovaOperacao;
    }

    return *ListaDeOperacoes;
}

//Remover uma operação
Operacao* MenuRemoveOperacao(Operacao* ListaDeOperacoes, int Id)
{
    if (ListaDeOperacoes == NULL)
    {
        return NULL;
    }

    if (!ExisteOperacao(ListaDeOperacoes, Id))
    {
        return NULL;
    }

    Operacao* aux = ProcuraOperacao(ListaDeOperacoes, Id);
    Operacao* auxOperacao = ListaDeOperacoes;

    while (auxOperacao != NULL)
    {
        if (auxOperacao == aux)
        {
                ListaDeOperacoes = auxOperacao->Seguinte;
            free(aux);
            return ListaDeOperacoes;
        }
        if (auxOperacao->Seguinte == aux)
        {
            auxOperacao->Seguinte = aux->Seguinte;
            free(aux);
            return ListaDeOperacoes;
        }
    }
    return ListaDeOperacoes;
}

//Procurar uma determinada operação
Operacao* ProcuraOperacao(Operacao* ListaDeOperacoes, int Id)
{
    if (ListaDeOperacoes == NULL)
    {
        return NULL;
    }
    else
    {
        Operacao* aux = ListaDeOperacoes;

        while (aux != NULL)
        {
            if (aux->Id == Id)
            {
                return (aux);
            }
            aux = aux->Seguinte;
        }
        return NULL;
    }
}

//Trocar uma determinada operação
Operacao* TrocaOperacao(Operacao* ListaDeOperacoes, int IdOperacao, int IdOperacaoTroca)
{
    if (ListaDeOperacoes == NULL)
    {
        return NULL;
    }

    Operacao* auxOperacao = ProcuraOperacao(ListaDeOperacoes, IdOperacao);
    Operacao* auxOperacaoTroca = ProcuraOperacao(ListaDeOperacoes, IdOperacaoTroca);
    Operacao* temp;

    auxOperacao->Maquinas = temp->Maquinas;
    auxOperacao->Maquinas = auxOperacaoTroca->Maquinas;
    auxOperacaoTroca->Maquinas = temp->Maquinas;

    return ListaDeOperacoes;
}

//Calcular o tempo minimo da operação
int TempoMinimoDaOperacao(Operacao* ListaDeOperacoes, int Id)
{
    if (ListaDeOperacoes == NULL)
    {
        return 0;
    }

    int TempoMinimoDaOperacao = 5, IdMaquina;
    Operacao* aux = ProcuraOperacao(ListaDeOperacoes, Id);
    Maquina* auxMaquina = aux->Maquinas;

    while (auxMaquina != NULL)
    {
        if (auxMaquina->Tempo < TempoMinimoDaOperacao)
        {
            IdMaquina = auxMaquina->Id;
            TempoMinimoDaOperacao = auxMaquina->Tempo;
        }
        auxMaquina = auxMaquina->Seguinte;
    }
    printf("Menor Tempo - Operacao %d: Maquina %d, Tempo %d\n", aux->Id, IdMaquina, TempoMinimoDaOperacao);

    return TempoMinimoDaOperacao;
}

//Calcular o tempo maximo da operação
int TempoMaximoDaOperacao(Operacao* ListaDeOperacoes, int Id)
{
    if (ListaDeOperacoes == NULL)
    {
        return 0;
    }

    int TempoMaximoDaOperacao = 0, IdMaquina;
    Operacao* aux = ProcuraOperacao(ListaDeOperacoes, Id);
    Maquina* auxMaquina = aux->Maquinas;

    while (auxMaquina != NULL)
    {
        if (auxMaquina->Tempo > TempoMaximoDaOperacao)
        {
            IdMaquina = auxMaquina->Id;
            TempoMaximoDaOperacao = auxMaquina->Tempo;
        }
        auxMaquina = auxMaquina->Seguinte;
    }
    printf("Maior Tempo - Operacao %d: Maquina %d, Tempo %d\n", aux->Id, IdMaquina, TempoMaximoDaOperacao);

    return TempoMaximoDaOperacao;

}
//Calcular o tempo médio da operação
//Lista de Operações e os IDs
float TempoMedioDaOperacao(Operacao* ListaDeOperacoes, int Id)
{
    //Se a lista for igual a 0
    if (ListaDeOperacoes == NULL)
    {
        scanf("Lista Vazia");
    }

    int Soma = 0; // Será somado todas operaçôpes
    int Total = 0; //Armazenado todas as operações
    Operacao* aux = ProcuraOperacao(ListaDeOperacoes, Id);
    Maquina* auxMaquina = aux->Maquinas;


    while (auxMaquina != NULL)
    {
        Soma += auxMaquina->Tempo;
        Total++;
        auxMaquina = auxMaquina->Seguinte;
    }

    return (Soma / Total); //Resultado Final
}

//Verificar se a operação existe
bool ExisteOperacao(Operacao* ListaDeOperacoes, int Id)
{
    if (ListaDeOperacoes == NULL)
    {
        return false;
    }

    Operacao* aux = ListaDeOperacoes;
    while (aux != NULL)
    {
        if (aux->Id == Id)
        {
            return true;
        }
        aux = aux->Seguinte;
    }
    return false;
}

//Vissualizar lista de Operações
void MostraListaDeOperacoes(Operacao* ListaDeOperacoes)
{
    Operacao* aux = ListaDeOperacoes;

    while (aux != NULL)
    {
        printf("\n---------------- Operacao:%d"
               "---------------------- \n", aux->Id);
        MostraListaDeMaquinas(aux->Maquinas);
        aux = aux->Seguinte;
    }
}

//Visualizar ID´s das operações
void MostraOperacoes(Operacao* ListaDeOperacoes)
{
    Operacao* aux = ListaDeOperacoes;
    printf("-----Operacoes Disponiveis-----:\n");
    while (aux != NULL)
    {
        printf("Operacao com o ");
        printf("Id: Numero %d\n", aux->Id);
        aux = aux->Seguinte;
    }
    printf("\n");
}

#pragma endregion

#pragma region Maquinas

//Criar uma Maquina
Maquina* CriaMaquina(int Id, int Tempo)
{
    Maquina* NovaMaquina = (Maquina*)malloc(sizeof(Maquina));

    if (NovaMaquina == NULL)
    {
        return NULL;
    }

    NovaMaquina->Id = Id;
    NovaMaquina->Tempo = Tempo;
    NovaMaquina->Seguinte = NULL;

    return NovaMaquina;
}
//**Lista Ligada de uma lista ligada, Um apontador, lista ligada, que irá ter outro apontador, outra lista ligada. Apontadore de Apontadores.
//Inserir uma maquina
Maquina* InsereMaquina(Maquina** ListaDeMaquinas, Maquina* NovaMaquina)
{
    NovaMaquina->Seguinte = NULL;

    if (*ListaDeMaquinas == NULL)
    {
        *ListaDeMaquinas = NovaMaquina;
    }
    else
    {
        Maquina* Ultimo = *ListaDeMaquinas;

        while (Ultimo->Seguinte != NULL)
        {
            Ultimo = Ultimo->Seguinte;
        }

        Ultimo->Seguinte = NovaMaquina;
    }

    return *ListaDeMaquinas;
}

//Remover uma determinada maquina
Maquina* RemoveMaquina(Maquina* ListaDeMaquinas, int Id)
{
    if (ListaDeMaquinas == NULL)
    {
        return NULL;
    }

    if (!ExisteMaquina(ListaDeMaquinas, Id))
    {
        return NULL;
    }

    if (ListaDeMaquinas->Id == Id)
    {
        Maquina* aux = ListaDeMaquinas;
        ListaDeMaquinas = ListaDeMaquinas->Seguinte;
        free(aux);
    }
    else
    {
        Maquina* aux = ListaDeMaquinas;
        Maquina* auxAnt = aux;

        while (aux && aux->Id != Id)
        {
            auxAnt = aux;
            aux = aux->Seguinte;
        }
        if (aux != NULL)
        {
            auxAnt->Seguinte = aux->Seguinte;
            free(aux);
        }
    }
    return ListaDeMaquinas;
}

//Procurar uma maquina
Maquina* ProcuraMaquina(Maquina* ListaDeMaquinas, int Id)
{
    if (ListaDeMaquinas == NULL)
    {
        return NULL;
    }
    else
    {
        Maquina* aux = ListaDeMaquinas;

        while (aux != NULL)
        {
            if (aux->Id == Id)
            {
                return (aux);
            }
            aux = aux->Seguinte;
        }
    }
    return NULL;
}

//Verificar se existe a maquina
bool ExisteMaquina(Maquina* ListaDeMaquinas, int Id)
{
    if (ListaDeMaquinas == NULL)
    {

        return false;
    }

    Maquina* aux = ListaDeMaquinas;
    while (aux != NULL)
    {
        if (aux->Id == Id)
        {
            return true;
        }
        aux = aux->Seguinte;
    }
    return false;
}

//Mostrar a lista de maquinas
void MostraListaDeMaquinas(Maquina* ListaDeMaquinas)
{
    Maquina* aux = ListaDeMaquinas;
    while (aux != NULL)
    {
        printf("\nMaquina: %d   \t\nTempo: %d\n", aux->Id, aux->Tempo);
        aux = aux->Seguinte;
    }
}

#pragma endregion

#pragma region Jobs

//Criar um JOB
Job* CriaJob(int Id)
{
    Job* NovoJob = (Job*)malloc(sizeof(Job));
    if (NovoJob == NULL) return NULL;

    NovoJob->Id = Id;
    NovoJob->Operacoes = NULL;
    NovoJob->Seguinte = NULL;

    return NovoJob;
}

//Inserir um JOB
Job* InsereJob(Job** ListaDeJobs, Job* NovoJob)
{
    NovoJob->Seguinte = NULL;

    if (*ListaDeJobs == NULL)
    {
        *ListaDeJobs = NovoJob;
    }
    else
    {
        Job* Ultimo = *ListaDeJobs;

        while (Ultimo->Seguinte != NULL)
        {
            Ultimo = Ultimo->Seguinte;
        }

        Ultimo->Seguinte = NovoJob;
    }

    return *ListaDeJobs;
}

//Procurar um JOB
Job* ProcuraJob(Job* ListaDeJobs, int Id)
{
    if (ListaDeJobs == NULL)
    {
        return NULL;
    }
    else
    {
        Job* aux = ListaDeJobs;

        while (aux != NULL)
        {
            if (aux->Id == Id)
            {
                return (aux);
            }
            aux = aux->Seguinte;
        }
    }
    return NULL;
}

//Calcuar tempo minimo de um Job
int TempoMinimoDeJob(Job* ListaDeJobs, int Id)
{
    if (ListaDeJobs == NULL)
    {
        return -1;
    }

    int SomaMinima = 0;
    Job* aux = ProcuraJob(ListaDeJobs, Id);
    Operacao* auxOperacao = aux->Operacoes;

    while (auxOperacao != NULL)
    {
        SomaMinima += TempoMinimoDaOperacao(auxOperacao, auxOperacao->Id);
        auxOperacao = auxOperacao->Seguinte;
    }
    return SomaMinima;
}

//Calcular tempo maximo de um job
int TempoMaximoDeJob(Job* ListaDeJobs, int Id)
{
    if (ListaDeJobs == NULL)
    {
        return -1;
    }

    int SomaMaxima = 0;
    Job* aux = ProcuraJob(ListaDeJobs, Id);
    Operacao* auxOperacao = aux->Operacoes;

    while (auxOperacao != NULL)
    {
        SomaMaxima += TempoMaximoDaOperacao(auxOperacao, auxOperacao->Id);
        auxOperacao = auxOperacao->Seguinte;
    }
    return SomaMaxima;
}

//Verificar se o job existe
bool ExisteJob(Job* ListaDeJobs, int Id)
{
    if (ListaDeJobs == NULL)
    {

        return false;
    }

    Job* aux = ListaDeJobs;
    while (aux != NULL)
    {
        if (aux->Id == Id)
        {
            return true;
        }
        aux = aux->Seguinte;
    }
    return false;
}

//Visualizar a lista de Jobs
void MostraListaJobs(Job* ListaDeJobs)
{
    Job* aux = ListaDeJobs;
    while (aux != NULL)
    {
        printf("Job: %d\n", aux->Id);
        MostraListaDeOperacoes(aux->Operacoes);
        aux = aux->Seguinte;
    }
}

#pragma endregion
