//Licenciatura Engenharia Informática Médica
//Diogo Alexandre Mendes Simões Nº15328
//Estrutura Dados Avançadas
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include "Estrutura.h"
#include <string.h>
void MainMenu()
{
    //Menu principal
    system("cls");
    int Escolha;
    Job* ListaDeJobs = LerFicheiro();

    do
    {
        printf(
               "------------------------------ MENU ------------------------------\n"
               "1 - Adiciona Operacao\n"
               "2 - Remove Operacao\n"
               "3 - Altera Operacao\n"
               "4 - Jobs\n"
               "5 - Minimo\n"
               "6 - Maximo\n"
               "7 - Media\n"
               "\n"
               "0 - Quit\n"
               "------------------------------ <-> ------------------------------");

        Escolha = Valor(7, 0);

        switch (Escolha)
        {
        case 1:
        ListaDeJobs = AdicionaOperacao(ListaDeJobs);


            break;

        case 2:
        ListaDeJobs = RemoveOperacao(ListaDeJobs);

            break;

        case 3:
        ListaDeJobs = AlteraOperacao(ListaDeJobs);

            break;

        case 4:

              system("cls");

                MostraListaJobs(ListaDeJobs);

                getche();
                system("cls");
            break;

        case 5:
            system("cls");

            int TempoMinimo;

            TempoMinimo = TempoMinimoDeJob(ListaDeJobs, ListaDeJobs->Id);

            printf("Menor Tempo do Job: %d\n\n", TempoMinimo);
            getche();
            system("cls");
            break;


        case 6:
            int TempoMaximo;

            TempoMaximo = TempoMaximoDeJob(ListaDeJobs, ListaDeJobs->Id);

            printf("Maior Tempo do Job: %d\n\n", TempoMaximo);
            getche();
            system("cls");
            break;

        case 7:

    MostraOperacoes(ListaDeJobs->Operacoes);


            int Id, TempoMedio;

            printf("Introduza o Id da Operacao:\n\t> ");
            scanf(" %d", &Id);

            Operacao* auxOperacao = ProcuraOperacao(ListaDeJobs->Operacoes, Id);

            if (auxOperacao == NULL)
            {

                printf("Erro");
                getche();
                system("cls");
                break;
            }

            TempoMedio = TempoMedioDaOperacao(ListaDeJobs->Operacoes, auxOperacao->Id);

            printf("Tempo Medio da Operacao: %d\n", TempoMedio);
            getche();
            system("cls");
            break;


        case 0:
            break;

        default:
            printf("\nErro\n");
            MainMenu();
            break;
        }
    } while (Escolha != 0);

    GravarJobs(ListaDeJobs->Operacoes);
}



//Adicionar Operações
Job* AdicionaOperacao(Job* ListaDeJobs)
{
    int IdOperacao;

    system("cls");

    printf("Id da Operacao que deseja Adicionar\n");
    scanf(" %d", &IdOperacao);

    if (ExisteOperacao(ListaDeJobs->Operacoes, IdOperacao) == true)
    {
        printf("\nOperacao ja Existe\n");
        getche();
        system("cls");
        return ListaDeJobs;
    }

    Operacao* auxOperacao = CriaOperacao(IdOperacao);

    Maquina* auxMaquina;
    auxMaquina = AdicionaMaquina(auxMaquina);

    auxOperacao->Maquinas = auxMaquina;

    ListaDeJobs->Operacoes =  InsereOperacao(&ListaDeJobs->Operacoes, auxOperacao);


    system("cls");
    return ListaDeJobs;
}

//Adicionar Maquinas
Maquina* AdicionaMaquina(Maquina* ListaDeMaquinas)
{
    int Escolha;
    ListaDeMaquinas = NULL;

    do
    {
        system("cls");
        printf("1 - Adicionar uma Maquina \n"
               "0 - Sair\n");

        Escolha = Valor(1, 0);

        switch(Escolha)
        {
        case 1:
            system("cls");

            int IdMaquina, Tempo;

            printf("Introduzir o ID da Maquina: ");
            scanf(" %d", &IdMaquina);
            printf("Introduzir o Tempo da Maquina que Deseja: ");
            scanf(" %d", &Tempo);

            Maquina* auxMaquina = CriaMaquina(IdMaquina, Tempo);
            ListaDeMaquinas = InsereMaquina(&ListaDeMaquinas, auxMaquina);
            break;

        case 0:
            return ListaDeMaquinas;

        default:
            printf("\nErro\n\n");
            return ListaDeMaquinas;
        }
    } while (Escolha != 0);
}

//Remover uma operação
Job* RemoveOperacao(Job* ListaDeJobs)
{
    system("cls");

    int IdOperacao;

    MostraOperacoes(ListaDeJobs->Operacoes);

    printf("Introduza o Id da Operacao que quer Remover\n");
    scanf(" %d", &IdOperacao);

    int a;
	 printf("Deseja realizar mesmo esta operacao?: \n\t"
	 "Se sim, carregue 1.\n\t"
	 "Se nao, carregue 0.\n\t");
     printf("->");
	scanf ("%d",&a);


	if (a==1)
	{
    if (ExisteOperacao(ListaDeJobs->Operacoes, IdOperacao) == false)
    {
        printf("Erro");
        getche();
        system("cls");
        return ListaDeJobs;
    }

    Job* auxJob = ProcuraJob(ListaDeJobs, ListaDeJobs->Id);
    Operacao* auxOperacao = ProcuraOperacao(ListaDeJobs->Operacoes, IdOperacao);

    if (auxOperacao != NULL)
    {
        Operacao* auxOperacao2 = ProcuraOperacao(ListaDeJobs->Operacoes, IdOperacao - 1);
        if (auxOperacao2 != NULL)
        {
            auxOperacao2->Seguinte = auxOperacao->Seguinte;
        }
        else
        {
            auxJob->Operacoes = auxOperacao->Seguinte;
        }
        free(auxOperacao);//desalocar dinamicamente a memória.
        auxOperacao = auxJob->Operacoes;
        IdOperacao = 1;
        while (auxOperacao != NULL)
        {
            auxOperacao->Id = IdOperacao;
            IdOperacao++;
            auxOperacao = auxOperacao->Seguinte;
        }
    }

    system("cls");
    printf("Erro");
    getche();
    system("cls");
    return ListaDeJobs;
	}
	else{
	     system("cls");
    printf("Erro");
    getche();
        system("cls");
        return ListaDeJobs;
	}
}

//Operação para alterar
Job* AlteraOperacao(Job* ListaDeJobs)
{
    system("cls");

    int IdOperacao;

    MostraOperacoes(ListaDeJobs->Operacoes);

    printf("Introduza o Id da Operacao que gostaria de Alterar: ");
    scanf(" %d", &IdOperacao);

    if (ExisteOperacao(ListaDeJobs->Operacoes, IdOperacao) == false)
    {
        printf("Erro");
        getche();
        system("cls");
        return ListaDeJobs;
    }

    Operacao* auxOperacao = ProcuraOperacao(ListaDeJobs->Operacoes, IdOperacao);

    auxOperacao = AlteraOperacaoEscolhida(auxOperacao, ListaDeJobs->Operacoes);

    system("cls");
    printf("Erro");
    getche();
    system("cls");
    return ListaDeJobs;
}

//Alterar operação escolhida pelo utilizador
Operacao* AlteraOperacaoEscolhida(Operacao* OperacaoEscolhida, Operacao* ListaDeOperacoes)
{
    int Escolha;

    do
    {
        system("cls");
        printf("--- Alterar Operacao ---\n"
               "1 - Adicionar uma Maquina \n"
               "2 - Remover uma Maquina \n"
               "3 - Alterar Tempo de uma Maquina \n"
               "4 - Trocar uma Operacoes \n"
               "\n0 - Confirmar\n");

        Escolha = Valor(4, 0);
        switch(Escolha)
        {
        case 1:
            system("cls");

            int Id, Tempo;

            printf("Introduza o Id da Maquina:");
            scanf(" %d", &Id);
            printf("Introduza o Tempo da Maquina:");
            scanf(" %d", &Tempo);

            Maquina* NovaMaquina = CriaMaquina(Id, Tempo);
            OperacaoEscolhida->Maquinas = InsereMaquina(&OperacaoEscolhida->Maquinas, NovaMaquina);
            break;

        case 2:
            system("cls");

            int Id2;

            printf("Introduza o Id da Maquina:> ");
            scanf(" %d", &Id2);

            Maquina* auxMaquina = ProcuraMaquina(OperacaoEscolhida->Maquinas, Id2);

            if (auxMaquina == NULL)
            {
                printf("Erro");
                getche();
                system("cls");
                break;
            }

            OperacaoEscolhida->Maquinas = RemoveMaquina(OperacaoEscolhida->Maquinas, auxMaquina->Id);
            break;

        case 3:
            system("cls");

            int Id3, NovoTempo;

            printf("Introduza o Id da Maquina:> ");
            scanf(" %d", &Id3);

            Maquina* auxMaquina2 = ProcuraMaquina(OperacaoEscolhida->Maquinas, Id3);

            if (auxMaquina2 == NULL)
            {

                printf("Erro");
                getche();
                system("cls");
                break;
            }

            printf("Insira o novo Tempo da Maquina Escolhida:> ");
            scanf(" %d", &NovoTempo);

            auxMaquina2->Tempo = NovoTempo;

            printf("Tempo Mudado");
            getche();
            system("cls");
            break;

        case 4:
            system("cls");

            int IdOperacao;

            printf("Introduza o Id da Operacao para que deseja trocar:> ");
            scanf(" %d", &IdOperacao);

            if (IdOperacao == OperacaoEscolhida->Id)
            {

                printf("Erro, a mesma operação não funciona");
                getche();
                system("cls");
                break;
            }

            Operacao* auxOperacao = ProcuraOperacao(ListaDeOperacoes, IdOperacao);

            if (auxOperacao == NULL)
            {

                printf("Erro");
                getche();
                system("cls");
                break;
            }

            Maquina* auxMaquina3;

            auxMaquina3 = OperacaoEscolhida->Maquinas;
            OperacaoEscolhida->Maquinas = auxOperacao->Maquinas;
            auxOperacao->Maquinas = auxMaquina3;

            printf("Troca Realizada");
            getche();
            system("cls");
            break;

        case 0:
            return ListaDeOperacoes;

        default:

            return ListaDeOperacoes;
        }
    } while (Escolha != 0);

}


void main()
{
    MainMenu();
}
