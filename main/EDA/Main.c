//Licenciatura Engenharia Informática Médica
//Diogo Alexandre Mendes Simões Nº15328
//Estrutura Dados Avançadas
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include "Estrutura.h"
#include "AddMenus.h"
#include <string.h>
void MainMenu()
{
    //Menu principal
    system("cls");
    int Escolha;
    printf("1");
    Job* ListaDeJobs = LerFicheiro();
    printf("10");
    do
    {
        printf(
               "------------------------------ MENU ------------------------------\n"
               "\t Enter 1 - Mostra Jobs\n"
               "\t Enter 2 - Adiciona Operacao\n"
               "\t Enter 3 - Remove Operacao\n"
               "\t Enter 4 - Altera Operacao\n"
               "\t Enter 5 - Informacoes\n"
               "\n\t Enter 0 - Quit\n"
               "------------------------------ <-> ------------------------------");

        Escolha = Valor(5, 0);

        switch (Escolha)
        {
        case 1:
            MenuMostraJob(ListaDeJobs);
            break;
        case 2:
            ListaDeJobs = MenuAdicionaOperacao(ListaDeJobs);
            break;

        case 3:
            ListaDeJobs = MenuRemoveOperacao(ListaDeJobs);
            break;

        case 4:
            ListaDeJobs = MenuAlteraOperacao(ListaDeJobs);
            break;

        case 5:
            MenuInformacoes(ListaDeJobs);
            break;
        case 0:
            break;

        default:
            printf("\nErro\n");
            MainMenu();
            break;
        }
    } while (Escolha != 0);

    GravarFicheiro(ListaDeJobs);
}

//---------------------------------------------------------------------------------------------
/**
 * @brief Mostra o Job Introduzido no Programa
 *
 * @param Lista de Jobs;
 */
void MenuMostraJob(Job* ListaDeJobs)
{
    system("cls");

    MostraListaJobs(ListaDeJobs);

    printf("Pressiona alguma Tecla para Continuar!");
    getche();
    system("cls");
    return;
}


/**
 * @brief Menu para Adicionar Operacoes
 *
 * @param Lista de Jobs
 * @return Lista de Jobs com Nova Operacao
 */
Job* MenuAdicionaOperacao(Job* ListaDeJobs)
{
    int IdOperacao;

    system("cls");

    printf("Id da Operacao que deseja Adicionar\n\t");
    scanf(" %d", &IdOperacao);

    if (ExisteOperacao(ListaDeJobs->Operacoes, IdOperacao) == true)
    {
        printf("\n\t//Opcao Invalida//\n\n");
        printf("\n\tOperacao ja Existe no Contexto Atual\n\n");
        printf("Pressiona alguma Tecla para Continuar!");
        getche();
        system("cls");
        return ListaDeJobs;
    }

    Operacao* auxOperacao = CriaOperacao(ListaDeJobs->Operacoes, IdOperacao);

    Maquina* auxMaquina;
    auxMaquina = MenuAdicionaMaquina(auxMaquina);

    auxOperacao->Maquinas = auxMaquina;

    ListaDeJobs->Operacoes = InsereJobLista(&ListaDeJobs->Operacoes, auxOperacao);

    system("cls");
    printf("\tOperacao Adicionada\n\n");
    printf("Pressiona alguma Tecla para Continuar!");
    getche();
    system("cls");
    return ListaDeJobs;
}




//---------------------------------------------------------------------------------------------
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
Maquina* MenuAdicionaMaquina(Maquina* ListaDeMaquinas)
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
Job* MenuRemoveOperacao(Job* ListaDeJobs)
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
    printf("Efetuado");
    getche();
    system("cls");
    return ListaDeJobs;
	}
	else{
	     system("cls");
    printf("Carregue Enter para continuar");
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

/**
 * @brief Menu para as Informacoes
 *
 * @param Lista de Jobs
 *
 * @param [out] Prints das Informacoes
 */
void MenuInformacoes(Job* ListaDeJobs)
{
    int Escolha, IdJob;

    system("cls");

    printf("Id do Job que deseja ser Informado\n\t");
    scanf(" %d", &IdJob);

    do
    {
        system("cls");
        printf("\t--- Informacoes ---\n"
               "\t Enter 1 - O Menor Tempo do Job \n"
               "\t Enter 2 - O Maior Tempo do Job \n"
               "\t Enter 3 - O Tempo Medio de uma Operacao \n"
               "\n\t Enter 0 - Confirmar\n");

        Escolha = Valor(3, 0);

        switch (Escolha)
        {
        case 1:
            system("cls");

            int TempoMinimo;

            TempoMinimo = TempoMinimoDeJob(ListaDeJobs, IdJob);

            printf("O Menor Tempo do Job e: %d\n\n", TempoMinimo);
            printf("Pressiona alguma Tecla para Continuar!");
            getche();
            system("cls");
            break;

        case 2:
            system("cls");

            int TempoMaximo;

            TempoMaximo = TempoMaximoDeJob(ListaDeJobs, IdJob);

            printf("O Maior Tempo do Job e: %d\n\n", TempoMaximo);
            printf("Pressiona alguma Tecla para Continuar!");
            getche();
            system("cls");
            break;

        case 3:
            system("cls");

            int Id, TempoMedio;

            printf("Insira o Id da Operacao:\n\t> ");
            scanf(" %d", &Id);

            Operacao* auxOperacao = ProcuraOperacao(ListaDeJobs->Operacoes, Id);

            if (auxOperacao == NULL)
            {
                printf("\n\t//Opcao Invalida//\n\n");
                printf("\n\tOperacao nao Existe no Contexto Atual\n\n");
                printf("Pressiona alguma Tecla para Continuar!");
                getche();
                system("cls");
                break;
            }

            TempoMedio = TempoMedioDaOperacao(ListaDeJobs->Operacoes, auxOperacao->Id);

            printf("O Tempo Medio da Operacao e: %d\n\n", TempoMedio);
            printf("Pressiona alguma Tecla para Continuar!");
            getche();
            system("cls");
            break;

        case 0:
            return;

        default:
            printf("\n\t//Opcao Invalida//\n\n");
            return;
        }
    } while (Escolha != 0);

}
// MENU

void main()
{
    MainMenu();
}
