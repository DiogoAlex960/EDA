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


//Gravar informação no Jobs
void GravarJobs(Operacao* ListaDeOperacoes)
{
    FILE* Jobs;
    Jobs = fopen("Jobs.txt", "w");

    while (ListaDeJobs != NULL)
    {
        while (ListaDeJobs->Operacoes != NULL)
        {
            while (ListaDeJobs->Operacoes->Maquinas != NULL)
            {
                fprintf(Ficheiro, "- %d %d\n", ListaDeJobs->Operacoes->Maquinas->Id, ListaDeJobs->Operacoes->Maquinas->Tempo);
                ListaDeJobs->Operacoes->Maquinas = ListaDeJobs->Operacoes->Maquinas->Next;
            }

            fprintf(Ficheiro, "- - %d\n", ListaDeJobs->Operacoes->Id);
            ListaDeJobs->Operacoes = ListaDeJobs->Operacoes->Next;
        }
        fprintf(Ficheiro, "%d", ListaDeJobs->Id);
        if (ListaDeJobs->Next != NULL)
        {
            fprintf(Ficheiro, "\n");
        }
        ListaDeJobs = ListaDeJobs->Next;
    }
}

Job* LerFicheiro()
{
    FILE* Ficheiro;
    int Temp, IdJobs,IdOperacoes, IdMaquinas, TempoMaquinas;
    char Buffer = '-';
    Operacao* auxOperacao,* ListaDeOperacoes = NULL;
    Maquina* auxMaquina,* ListaDeMaquinas = NULL;
    Job* auxJob,* ListaDeJobs = NULL;

    Ficheiro = fopen("TotalJobs.txt", "r");

    if (Ficheiro == NULL)
    {
        return false;
    }
    printf("2");
    while (!feof(Ficheiro))//Esta função retorna um valor diferente de zero quando o indicador End-of-File associado ao fluxo é definido, caso contrário, zero é retornado.
    {
        printf("3");
        while (fscanf(Ficheiro, "%d", &IdJobs) != 1)//A função fscanf() é usada para ler a entrada formatada do fluxo fornecido na linguagem C. Retorna zero, se não for bem-sucedido. Caso contrário, ele retornará A string de entrada, se for bem-sucedida.
        {
            printf("4");
            if (fscanf(Ficheiro, " %d", &IdMaquinas) == 1)
            {
                printf("5");
                fscanf(Ficheiro, " %d", &TempoMaquinas);
                auxMaquina = CriaMaquinaFicheiro(IdMaquinas, TempoMaquinas);
                ListaDeMaquinas = InsereMaquinaListaFinal(&ListaDeMaquinas, auxMaquina);

                fscanf(Ficheiro, "%*c");
            }
            else
            {
                fscanf(Ficheiro, " %d", &IdOperacoes);
                auxOperacao = CriaOperacaoFicheiro(IdOperacoes);
                auxOperacao->Maquinas = ListaDeMaquinas;
                ListaDeOperacoes = InsereOperacaoListaFinal(&ListaDeOperacoes, auxOperacao);
                ListaDeMaquinas = NULL;

                fscanf(Ficheiro, "%*c");
            }
        }
        fscanf(Ficheiro, " %d", &IdJobs);
        auxJob = CriaJobFicheiro(IdJobs);
        auxJob->Operacoes = ListaDeOperacoes;
        ListaDeJobs = InsereJobListaFinal(&ListaDeJobs, auxJob);
        ListaDeOperacoes = NULL;

        fscanf(Ficheiro, "%*c");
    }

    return ListaDeJobs;
}
#pragma endregion

#pragma region Operacoes

//Cria uma Operacao no Ficheiros (se não existe)
Operacao* CriaOperacaoNoFicheiro(int Id)
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


//Cria Operacao na HeadLista
Operacao* CriaOperacao(Operacao* ListaDeOperacoes, int Id)
{
    if (ExisteOperacao(ListaDeOperacoes, Id) == false)
    {
        return NULL;
    }

    Operacao* NovaOperacao = (Operacao*)malloc(sizeof(Operacao));

    if (NovaOperacao == NULL)
    {
        return NULL;
    }

    NovaOperacao->Id = Id;
    NovaOperacao->Maquinas = NULL;
    NovaOperacao->Next = NULL;

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

//Trocar uma determinada operação ( Id da Operacao que quer Trocar pelo ID2 da Operacao desejada
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

    int TempoMinimoDaOperacao = 50, IdMaquina;
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
   // printf("Menor Tempo - Operacao %d: Maquina %d, Tempo %d\n", aux->Id, IdMaquina, TempoMinimoDaOperacao);

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
        return -1;
    }

    int SomaDeMaquinas = 0; // Será somado todas operaçôpes
    int TotalDeMaquinas = 0; //Armazenado todas as operações
    Operacao* aux = ProcuraOperacao(ListaDeOperacoes, Id);
    Maquina* auxMaquina = aux->Maquinas;


    while (auxMaquina != NULL)
    {
        SomaDeMaquinas += auxMaquina->Tempo;
        TotalDeMaquinas++;
        auxMaquina = auxMaquina->Seguinte;
    }

    return (SomaDeMaquinas / TotalDeMaquinas); //Resultado Final
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



//Criar uma Maquina
Maquina* CriaMaquinaFicheiro(int Id, int Tempo)
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


Maquina* CriaMaquina(Maquina* ListaDeMaquinas, int Id, int Tempo)
{
    if (ExisteMaquina(ListaDeMaquinas, Id) == NULL)
    {
        return NULL;
    }

    Maquina* NovaMaquina = (Maquina*)malloc(sizeof(Maquina));

    if (NovaMaquina == NULL)
    {
        return NULL;
    }

    NovaMaquina->Id = Id;
    NovaMaquina->Tempo = Tempo;
    NovaMaquina->Next = NULL;

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
Job* CriaJobFicheiro(int Id)
{
    Job* NovoJob = (Job*)malloc(sizeof(Job));
    if (NovoJob == NULL) return NULL;

    NovoJob->Id = Id;
    NovoJob->Operacoes = NULL;
    NovoJob->Seguinte = NULL;

    return NovoJob;
}

//Criar um Job na ListadeJobs
Job* CriaJob(Job* ListaDeJobs, int Id)
{
    if (ExisteJob(ListaDeJobs, Id) == false)
    {
        return NULL;
    }

    Job* NovoJob = (Job*)malloc(sizeof(Job));

    if (NovoJob == NULL) return NULL;

    NovoJob->Id = Id;
    NovoJob->Operacoes = NULL;
    NovoJob->Next = NULL;

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

//Remover Job
Job* RemoveJob(Job* ListaDeJobs, int Id)
{
    if (ListaDeJobs == NULL)
    {
        return NULL;
    }

    if (ExisteJob(ListaDeJobs, Id) == false)
    {
        return NULL;
    }

    if (ListaDeJobs->Id == Id)
    {
        Job* auxJob = ListaDeJobs;
        ListaDeJobs = auxJob->Next;
        free(auxJob);
    }
    else
    {
        Job* auxJob = ListaDeJobs;
        Job* auxJobAnt = auxJob;

        while (auxJob && auxJob->Id != Id)
        {
            auxJobAnt = auxJob;
            auxJob = auxJob->Next;
        }
        if (auxJob != NULL)
        {
            auxJobAnt->Next = auxJob->Next;
            free(auxJob);
        }
    }
    return ListaDeJobs;
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

//Inicia a HashTable

void IniciaHash(Job* HashTable[], int Max)
{
    for (int i = 0; i < Max; i++)
    {
        HashTable[i] = NULL;
    }
}

/**
 * @brief Encontra a Key que serÃ¡ precisa na HashTable
 *
 * @param Id do Job usado para encontrar a Key
 * @return Key usada para Encontrar o Job na HashTable
 */
int KeyHash(char* Id)
{
    int Soma = 0;

    for (int i = 0; i < strlen(Id); i++)
    {
        Soma += (int)Id[i];
    }

    return Soma % MAX;
}

/**
 * @brief Insere um Job numa HashTable -> Substitui o InsereJobListaFinal
 *
 * @param HashTable para Inserir
 * @param JobInserir
 * @return Hashtable com job novo
 */
Job** InserirJobHashTableInicio(Job* HashTable[], Job* JobInserir)
{
    int Pos = KeyHash(JobInserir->Id);

    JobInserir->Next = HashTable[Pos];
    HashTable[Pos] = JobInserir;

    return *HashTable;
}

/**
 * @brief Procura o Job na HashTable -> Substitui o ProcuraJob
 *
 * @param Id do Job que quer encontrar
 * @param HashTable Utilizada para encontrar o Job
 * @return Job encontrado
 */
Job* ProcurarJobHashTable(char* Id, Job* HashTable[])
{
    int Pos = KeyHash(Id);

    if (HashTable[Pos] == NULL)
    {
        return NULL;
    }

    //Mudar o ProcuraJob para (headListaJobs, char* Id)

    return ProcuraJob(HashTable[Pos], (int)Id);
}

/**
 * @brief Remove um Job de uma HashTable -> Substitui o RemoveJob
 *
 * @param HashTable para encontrar o Job que quer Remover
 * @param Id do Job que quer remover
 * @return HashTable sem o Job que retirou
 */
Job* RemoveJobHashTable(Job* HashTable[], char* Id)
{
    int Pos = KeyHash(Id);

    if (HashTable[Pos] == NULL)
    {
        return NULL;
    }

    //Remover no Inicio da Hash Table

    if (HashTable[Pos]->Id == Id)
    {
        Job* auxJob = HashTable[Pos];
        HashTable[Pos] = auxJob->Next;
        free(auxJob);
    }

    //Remover no Meio ou no Final da Hash Table

    else
    {
        Job* auxJob = HashTable[Pos];
        Job* auxAnt = auxJob;

        while (auxJob && auxJob->Id == Id)
        {
            auxAnt = auxJob;
            auxJob = auxAnt->Next;
        }

        if (auxJob != NULL)
        {
            auxAnt->Next = auxJob->Next;
            free(auxJob);
        }
    }
}

/**
 * @brief Mostra a HashTable -> Substitui o MostraListaJobs
 *
 * @param HashTable para Printar
 */
void MostraHashTable(Job* HashTable[])
{
    for (int i = 0; i < MAX; i++)
    {
        if (HashTable[i] != NULL)
        {
            printf("Index: %d\n", i);
            MostraListaOperacoes(HashTable[i]->Operacoes);
            printf("\n");
        }
    }
}

#pragma endregion

