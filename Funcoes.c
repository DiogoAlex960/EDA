//Licenciatura Engenharia Informática Médica
//Diogo Alexandre Mendes Simões Nº15328
//Estrutura de Dados Avançadas

#include <stdio.h>
#include <stdlib.h>
#include "Estrutura.h"
//----------------------------- INDICADOR UTILIZADOR --------------------------------------------
int Dado(int min, int max)
{
    int ValorInt = -1;
    char ValorChar;
    printf("\n\t> ");
    scanf(" %d", &ValorInt);
    scanf("%c", &ValorChar);
    while (ValorInt > max || ValorInt < min)
    {
        printf("\n\t//Invalido//\n\n");
        printf("\nEstas aqui -> ");
        scanf(" %d", &ValorInt);
        scanf("%c", &ValorChar);
    }
    system("cls");
    return ValorInt;
}
//----------------------------- LEER FICHEIRO --------------------------------------------
job *read(FILE *jobFile, job *HeadJob)
{
    job *jobTmp;
    maquina *maquinaHead = NULL;
    maquina *maquinaTmp;
    operacao *operacaoHead = NULL;
    operacao *operacaoTmp;
    int jobNum = 0, maquinaNum, operacaoNum = 0;
    char Caracter = '>';

    jobFile = fopen("Jobs.txt", "r");
    if (jobFile == NULL)
    {
        printf("Não consegue abrir ficheiro Jobs.txt");
        return 0;
    }
    fscanf(jobFile, "%*c");
    while (!feof(jobFile))
    {
        jobNum++;
        if (Caracter == '>')
        {
            while (Caracter == '>')
            {
                operacaoNum++;
                while (fscanf(jobFile, " %d", &maquinaNum) == 1)
                {
                    maquinaTmp = CriarNovaMaquina(maquinaNum);
                    maquinaHead = FinalMaquina(&maquinaHead, maquinaTmp);
                }
                operacaoTmp = CriarNovaOperacao(operacaoNum, jobNum, &maquinaHead);
                operacaoHead = FinalOperacao(&operacaoHead, operacaoTmp);
                fscanf(jobFile, "%*c %c", &Caracter);
                maquinaTmp = maquinaHead;
                while (fscanf(jobFile, " %d", &maquinaNum) == 1)
                {
                    maquinaTmp->maquinaTempo = maquinaNum;
                    maquinaTmp = maquinaTmp->Seguinte;
                }
                fscanf(jobFile, "%*c %c", &Caracter);
                maquinaHead = NULL;
            }
        }
        fscanf(jobFile, "%*c %c", &Caracter);
        operacaoNum = 0;

        jobTmp = CriarNovoJob(jobNum, &operacaoHead);
        HeadJob = FinalJob(&HeadJob, jobTmp);
        operacaoHead = NULL;
    }
    fclose(jobFile);
    return HeadJob;
}

//------------------------------FIM TXT-------------------------------------------

//------------------------------LISTAGEM SISTEMA-------------------------------------------

//------------------------------LISTAGEM DE JOBS SISTEMA-------------------------------------------
void ListaJobs(job *HeadJob)
{
    job *jobTmp = HeadJob;
    printf("Lista de Jobs Existentes:\n\t\n");
    while (jobTmp != NULL)
    {
        printf(" - %d \t", jobTmp->jobNum);
        jobTmp = jobTmp->Seguinte;
    }
    ListaOperacao(SelecionaJob(HeadJob)->OperacaoHead);
}
//----------------------------- LISTAR OPERACOES --------------------------------------------
void ListaOperacao(operacao *operacaoHead)
{
    operacao *operacaoTmp = operacaoHead;

    while (operacaoTmp != NULL)
    {
        printf("\n\t -Operacao: %d\n\n", operacaoTmp->operacaoNum);
        ListaMaquina(operacaoTmp->MaquinaHead);
        operacaoTmp = operacaoTmp->Seguinte;
    }
}
//------------------------------ LISTAR MAQUINAS -------------------------------------------

void ListaMaquina(maquina *maquinaHead)
{
    maquina *maquinaTmp = maquinaHead;

    while (maquinaTmp != NULL)
    {
        printf("\t\t -Maquina: %d Tempo: %d\n", maquinaTmp->maquinaNum, maquinaTmp->maquinaTempo);
        maquinaTmp = maquinaTmp->Seguinte;
    }
}
//----------------------------- FIM LISTAGENS--------------------------------------------

//----------------------------- JOB--------------------------------------------

//----------------------------- CRIAR JOB--------------------------------------------

void CriarJob(job *HeadJob)
{
    job *jobTmp = HeadJob;
    int jobis = 1;
    job *Tempr;
    printf("\tJobs Existentes:\n\n");
    while (jobTmp != NULL)
    {
        printf("\t%d; ", jobTmp->jobNum);
        jobTmp = jobTmp->Seguinte;
    }
      jobTmp = (HeadJob);
      while (jobis != 0)
    {
        printf("\n\n\tId do Job que deseja Adicionar: ");
        scanf(" %d", &jobis);
       // if(jobis == jobTmp->Seguinte)
      //  {
        Tempr = CriarNovoJob(jobis);
        HeadJob = FinalJob(&HeadJob, Tempr);
      //  }
      //  else
       // {
       //     printf("\nerro\n");
      //  }
        printf("\nCarregue 0 para sair de Adicionar Jobs: ");
        scanf(" %d", &jobis);
    }
}

//------------------------------REMOVER UM DETERMINADO JOB-------------------------------------------
void RemoverJob(job *HeadJob)
{
    job *jobTmp = HeadJob;
    int jobis = 1;
    job *Tempr;
    operacao *operacaoTmp;
    maquina *maquinaTmp;
    maquina *maquinaHeadTmp;
    maquina *maquinaHead = NULL;
    int maquinaNum = 1;
    int jobNum;
    printf("\tJobs Existentes:\n\n");
    while (jobTmp != NULL)
    {
        printf("%d; ", jobTmp->jobNum);
        jobTmp = jobTmp->Seguinte;
    }
    jobTmp = (HeadJob);
    Tempr = jobTmp->Seguinte;
    printf("\nId do Job que deseja Remover : ");
    scanf(" %d", &jobNum);
    while (Tempr->Seguinte != NULL)
    {
        Tempr = Tempr->Seguinte;
        if (Tempr->Seguinte->jobNum == jobNum)
            break;
    }
    Tempr->Seguinte = NULL;
    free(Tempr);
}

//------------------------------ CRIAR UM NOVO JOB -------------------------------------------

job *CriarNovoJob(int jobNum, operacao **operacaoHead)
{
    job *result = malloc(sizeof(job));
    result->jobNum = jobNum;
    result->OperacaoHead = *operacaoHead;
    result->Seguinte = NULL;
    return result;
}
//------------------------------INSERIR NO FINAL DOS JOB(HEAD) -------------------------------------------

job *FinalJob(job **HeadJob, job *JobAInserir)
{
    JobAInserir->Seguinte = NULL;

    if (*HeadJob == NULL)
        *HeadJob = JobAInserir;
    else
    {
        job *last = *HeadJob;

        while (last->Seguinte != NULL)
        {
            last = last->Seguinte;
        }

        last->Seguinte = JobAInserir;
    }
    return *HeadJob;
}
//------------------------------SELECIONA UM JOB-------------------------------------------

job *SelecionaJob(job *HeadJob)
{
    job *HeadJob2 = HeadJob;
    int jobNum;

    printf("\n\n\tSeleciona o Job: ");
    while (HeadJob->Seguinte != NULL)
    {
        HeadJob = HeadJob->Seguinte;
    }
    jobNum = Dado(1, HeadJob->jobNum);
    HeadJob = HeadJob2;
    while (HeadJob != NULL)
    {
        if (HeadJob->jobNum == jobNum)
            return HeadJob;
        HeadJob = HeadJob->Seguinte;
    }
    return NULL;
}

//------------------------------FIM JOB-------------------------------------------


//--------------------------------- CRIAR OPERACAO---------------------------------------------------

void CriarOperacao(job *HeadJob)
{
    job *jobTmp = HeadJob;
    operacao *operacaoTmp;
    operacao *operacaoHead;
    maquina *maquinaTmp;
    maquina *maquinaHeadTmp;
    maquina *maquinaHead = NULL;
    int maquinaNum = 1;
    int operacaoNum;
    printf("Lista de Jobs Existentes:\n");
    while (jobTmp != NULL)
    {
        printf("%d; ", jobTmp->jobNum);
        jobTmp = jobTmp->Seguinte;
    }
    jobTmp = SelecionaJob(HeadJob);

    printf("\nOperacao Numero: ");
    scanf(" %d", &operacaoNum);

    while (maquinaNum != 0)
    {
        printf("\nMaquina numero: ");
        scanf(" %d", &maquinaNum);
        maquinaTmp = CriarNovaMaquina(maquinaNum);
        maquinaHead = FinalMaquina(&maquinaHead, maquinaTmp);

        printf("\nMaquina %d tempo: ", maquinaTmp->maquinaNum);
        scanf(" %d", &maquinaNum);
        maquinaTmp->maquinaTempo = maquinaNum;
        maquinaTmp = maquinaHead;

        printf("\nCarregue 0 para sair de adicionar: ");
        scanf(" %d", &maquinaNum);
    }
    while (jobTmp->OperacaoHead->Seguinte != NULL)
    {
        jobTmp->OperacaoHead = jobTmp->OperacaoHead->Seguinte;
    }
    operacaoTmp = CriarNovaOperacao(jobTmp->OperacaoHead->operacaoNum + 1, jobTmp->jobNum, &maquinaHead);
    while (jobTmp->OperacaoHead->Anterior != NULL)
    {
        jobTmp->OperacaoHead = jobTmp->OperacaoHead->Anterior;
    }
    operacaoHead = FinalOperacao(&jobTmp->OperacaoHead, operacaoTmp);
    operacaoTmp = ProcuraOperacao(jobTmp->OperacaoHead, operacaoNum, jobTmp->jobNum);
    while (operacaoTmp != NULL)
    {
        maquinaHeadTmp = operacaoTmp->MaquinaHead;
        operacaoTmp->MaquinaHead = maquinaTmp;
        maquinaTmp = maquinaHeadTmp;
        operacaoTmp = operacaoTmp->Seguinte;
    }
}
//--------------------------------- REMOVER OPERACAO ---------------------------------------------------
void RemoverOperacao(job *HeadJob)
{
    job *jobTmp = HeadJob;
    operacao *operacaoTmp;
    maquina *maquinaTmp;
    maquina *maquinaHeadTmp;
    maquina *maquinaHead = NULL;
    int maquinaNum = 1;
    int operacaoNum;
    printf("Jobs:\n");
    while (jobTmp != NULL)
    {
        printf("%d; ", jobTmp->jobNum);
        jobTmp = jobTmp->Seguinte;
    }
    jobTmp = SelecionaJob(HeadJob);
    operacaoTmp = jobTmp->OperacaoHead;

    printf("\nNumero da Operacao a Remover : ");
    scanf(" %d", &operacaoNum);

    while (operacaoTmp->Seguinte != NULL)
    {
        operacaoTmp = operacaoTmp->Seguinte;
    }
    while (operacaoTmp->Anterior != NULL)
    {
        maquinaHeadTmp = operacaoTmp->MaquinaHead;
        operacaoTmp->MaquinaHead = maquinaTmp;
        maquinaTmp = maquinaHeadTmp;
        operacaoTmp = operacaoTmp->Anterior;
        if (operacaoTmp->Seguinte->operacaoNum == operacaoNum)
            break;
    }

    while (operacaoTmp->Seguinte != NULL)
    {
        operacaoTmp = operacaoTmp->Seguinte;
    }
    operacaoTmp->Anterior->Seguinte = NULL;
    free(operacaoTmp);
}
//--------------------------------- ALTERAR OPERACAO (ORDEM)---------------------------------------------------
void AlterarOperacao(job *HeadJob)
{
    job *jobTmp = HeadJob;
    operacao *operacaoTmp;
    operacao *operacaoTmp2;
    maquina *maquinaTmp;
    maquina *maquinaHeadTmp;
    maquina *maquinaHead = NULL;
    int maquinaNum = 1;
    int operacaoNum;

    printf("Jobs:\n");
    while (jobTmp != NULL)
    {
        printf("%d; ", jobTmp->jobNum);
        jobTmp = jobTmp->Seguinte;
    }
    jobTmp = SelecionaJob(HeadJob);

    operacaoTmp = SelecionaOperacao(jobTmp->OperacaoHead);
    int Valor;

    printf("\t--- Alterar Operacao  ---\n"
           "\t Enter 1 - Adicionar Maquina\n"
           "\t Enter 2 - Remover Maquina  \n"
           "\t Enter 3 - Troca(exchange) Ordem de Operacao  \n"
           "\n\t Enter 0 - back\n");

    Valor = Dado(0, 5);
    switch (Valor)
    {
    case 1:
        while (maquinaNum != 0)
        {
            maquinaHead = operacaoTmp->MaquinaHead;
            printf("\nNumero da Maquina: ");
            scanf(" %d", &maquinaNum);
            maquinaTmp = CriarNovaMaquina(maquinaNum);
            maquinaHead = FinalMaquina(&maquinaHead, maquinaTmp);

            printf("\nMaquina %d Tempo: ", maquinaTmp->maquinaNum);
            scanf(" %d", &maquinaNum);
            maquinaTmp->maquinaTempo = maquinaNum;
            maquinaTmp = maquinaHead;

            printf("\nCarregue 0 para sair : ");
            scanf(" %d", &maquinaNum);
        }
        break;
    case 2:
        maquinaTmp = SelecionaMaquina(jobTmp->OperacaoHead->MaquinaHead);
        RemoveMaquina(&operacaoTmp->MaquinaHead, maquinaTmp->maquinaNum);
        break;
    case 3:
        printf("\n Troca de Operacao %d com: ", operacaoTmp->operacaoNum);
        scanf("%d", &operacaoNum);
        operacaoTmp2 = ProcuraOperacao(jobTmp->OperacaoHead, operacaoNum, jobTmp->jobNum);
        maquinaTmp = operacaoTmp->MaquinaHead;
        operacaoTmp->MaquinaHead = operacaoTmp2->MaquinaHead;
        operacaoTmp2->MaquinaHead = maquinaTmp;
        break;
    case 0:
        break;
    default:
        printf("\n\t//Invalidado//\n\n");
        break;
    }
}


//--------------------------------- CRIAR NOVA OPERACAO ---------------------------------------------------
operacao *CriarNovaOperacao(int operacaoNum, int jobNum, maquina **maquinaHead)
{
    operacao *result = malloc(sizeof(operacao));
    result->operacaoNum = operacaoNum;
    result->jobNum = jobNum;
    result->MaquinaHead = *maquinaHead;
    result->Seguinte = NULL;
    result->Anterior = NULL;
    return result;
}
//--------------------------------- INSERIR NO FINAL DA OPERACAO(HEAD)---------------------------------------------------
operacao *FinalOperacao(operacao **operacaoHead, operacao *operacaoToInsert)
{
    operacaoToInsert->Seguinte = NULL;

    if (*operacaoHead == NULL)
        *operacaoHead = operacaoToInsert;
    else
    {
        operacao *last = *operacaoHead;

        while (last->Seguinte != NULL)
        {
            last->Seguinte->Anterior = last;
            last = last->Seguinte;
        }

        last->Seguinte = operacaoToInsert;
        operacaoToInsert->Anterior = last;
    }
    return *operacaoHead;
}
//--------------------------------- PROCURAR OPERACAO ---------------------------------------------------
operacao *ProcuraOperacao(operacao *operacaoHead, int operacaoNum, int jobNum)
{
    operacao *operacaoTmp = operacaoHead;
    while (operacaoTmp != NULL)
    {
        if (operacaoTmp->operacaoNum == operacaoNum && operacaoTmp->jobNum == jobNum)
        {
            return operacaoTmp;
        }
        operacaoTmp = operacaoTmp->Seguinte;
    }
    return NULL;
}

//--------------------------------- SELECIONAR OPERACAO ---------------------------------------------------
operacao *SelecionaOperacao(operacao *operacaoHead)
{
    operacao *operacaoHead2 = operacaoHead;
    int operacaoNum;

    printf("\nSeleciona a Operacao: ");
    while (operacaoHead->Seguinte != NULL)
    {
        operacaoHead = operacaoHead->Seguinte;
    }
    operacaoNum = Dado(1, operacaoHead->operacaoNum);
    operacaoHead = operacaoHead2;
    while (operacaoHead != NULL)
    {
        if (operacaoHead->operacaoNum == operacaoNum)
            return operacaoHead;
        operacaoHead = operacaoHead->Seguinte;
    }
    return NULL;
}
//--------------------------------- FIM OPERACAO---------------------------------------------------

//-------------------------------------MAQUINA-------------------------------------------------

//-----------------------------CRAIR UMA NOVA MAQUINA --------------------------------------------
maquina *CriarNovaMaquina(int maquinaNum)
{
    maquina *result = malloc(sizeof(maquina));
    result->maquinaNum = maquinaNum;
    result->Seguinte = NULL;
    result->Anterior = NULL;
    return result;
}



//-----------------------------INSERIR NO FINAL DA MAQUINA(HEAD)--------------------------------------------
maquina *FinalMaquina(maquina **maquinaHead, maquina *maquinaToInsert)
{
    maquinaToInsert->Seguinte = NULL;

    if (*maquinaHead == NULL)
        *maquinaHead = maquinaToInsert;
    else
    {
        maquina *last = *maquinaHead;

        while (last->Seguinte != NULL)
        {
            last->Seguinte->Anterior = last;
            last = last->Seguinte;
        }
        last->Seguinte = maquinaToInsert;
        maquinaToInsert->Anterior = last;
    }
    return *maquinaHead;
}
//--------------------------------- SELECIONAR MAQUINA ---------------------------------------------------
maquina *SelecionaMaquina(maquina *maquinaHead)
{
    maquina *maquinaHead2 = maquinaHead;
    int maquinaNum;

    printf("\nSeleciona a Maquina: ");
    while (maquinaHead->Seguinte != NULL)
    {
        maquinaHead = maquinaHead->Seguinte;
    }
    maquinaNum = Dado(1, 999);//Limite
    maquinaHead = maquinaHead2;
    while (maquinaHead != NULL)
    {
        if (maquinaHead->maquinaNum == maquinaNum)
            return maquinaHead;
        maquinaHead = maquinaHead->Seguinte;
    }
    return NULL;
}
//--------------------------------- REMOVER MAQUINA---------------------------------------------------
void *RemoveMaquina(maquina **maquinaHead, int maquinaNum)
{
    maquina *maquinaTmp;

    if ((*maquinaHead)->maquinaNum == maquinaNum)
    {
        maquinaTmp = *maquinaHead;
        *maquinaHead = (*maquinaHead)->Seguinte;
        free(maquinaTmp);
    }
    else
    {
        maquina *Atual = *maquinaHead;
        while (Atual->Seguinte != NULL)
        {
            if (Atual->Seguinte->maquinaNum == maquinaNum)
            {
                maquinaTmp = Atual->Seguinte;
                Atual->Seguinte = Atual->Seguinte->Seguinte;
                free(maquinaTmp);
                break;
            }
            else
            {
                Atual = Atual->Seguinte;
            }
        }
    }
}
//--------------------------------- FIM MAQUINAS---------------------------------------------------

//---------------------------------   TEMPOS    ---------------------------------------------------

//--------------------------------- TEMPO MINIMO---------------------------------------------------

void TempoMinimo(job *HeadJob)
{
    int maquinaNum, minTempo = 333, totalTempo = 0;
    job *jobTmp = HeadJob;
    operacao *operacaoTmp = HeadJob->OperacaoHead;
    maquina *maquinaTmp;
    while (operacaoTmp != NULL)
    {
        maquinaTmp = operacaoTmp->MaquinaHead;
        while (maquinaTmp != NULL)
        {
            if (minTempo > maquinaTmp->maquinaTempo)
            {
                minTempo = maquinaTmp->maquinaTempo;
                maquinaNum = maquinaTmp->maquinaNum;
            }
            maquinaTmp = maquinaTmp->Seguinte;
        }
        printf("Tempo Minimo da Operacao %d: maquina: %d tempo: %d\n", operacaoTmp->operacaoNum, maquinaNum, minTempo);
        totalTempo += minTempo;
        minTempo = 333;
        operacaoTmp = operacaoTmp->Seguinte;
    }
    printf("\Tempo Minimo do Job %d: %d\n", HeadJob->jobNum, totalTempo);
    // jobTmp = HeadJob;
}
//--------------------------------- TEMPO MAXIMO ---------------------------------------------------

void TempoMaximo(job *HeadJob)
{
    int maquinaNum, maxTempo = 0, totalTempo = 0;
    job *jobTmp = HeadJob;
    operacao *operacaoTmp = HeadJob->OperacaoHead;
    maquina *maquinaTmp;
    while (operacaoTmp != NULL)
    {
        maquinaTmp = operacaoTmp->MaquinaHead;
        while (maquinaTmp != NULL)
        {
            if (maxTempo < maquinaTmp->maquinaTempo)
            {
                maxTempo = maquinaTmp->maquinaTempo;
                maquinaNum = maquinaTmp->maquinaNum;
            }
            maquinaTmp = maquinaTmp->Seguinte;
        }
        printf("Tempo Maximo da operação%d: maquina: %d tempo: %d\n", operacaoTmp->operacaoNum, maquinaNum, maxTempo);
        totalTempo += maxTempo;
        maxTempo = 0;
        operacaoTmp = operacaoTmp->Seguinte;
    }
    printf("\Tempo Maximo do Job %d: %d\n", HeadJob->jobNum, totalTempo);
}
//--------------------------------- TEMPO MEDIO ---------------------------------------------------

void TempoMedio(job *HeadJob)
{
    int maquinaCounter;
    job *jobTmp = HeadJob;
    operacao *operacaoTmp = HeadJob->OperacaoHead;
    maquina *maquinaTmp;
    float totalTempo;
    while (operacaoTmp != NULL)
    {
        maquinaCounter = 0;
        totalTempo = 0;
        maquinaTmp = operacaoTmp->MaquinaHead;
        while (maquinaTmp != NULL)
        {

            totalTempo += maquinaTmp->maquinaTempo;
            maquinaCounter++;
            maquinaTmp = maquinaTmp->Seguinte;
        }
        totalTempo = totalTempo / maquinaCounter;

        printf("Tempo Medio da Operacao %d: %.2f\n", operacaoTmp->operacaoNum, totalTempo);
        operacaoTmp = operacaoTmp->Seguinte;
    }
}
//---------------------------------- FIM --------------------------------------------------------------
