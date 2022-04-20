#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Estruturas.h"
void MenuPrincipal()
{
    system("cls");
    int num = NULL;
    Job* ListaDeJobs = LerFicheiro();

    do
    {
        printf("JOB SHOP FLEXIBLE\n"
               "--------------- Pagina Principal  ---------------\n"
               " 1 - Adiciona uma Operacao\n"
               " 2 - Remover uma Operacao\n"
               " 3 - Alterar uma Operacao\n"
			   
			   " 4 - Quantidade Minima de Tempo\n"
			   " 5 - Quantidade Máxima de Tempo\n"
			   " 6 - Média de Tempo\n"
			   " 7 - Jobs\n"
               "\n 0 - Sair\n");

        num = GetInt(7, 0);
        switch (num)
        {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;
			
        case 6:
            break;


        case 7:
            break;


        case 0:
            break;

        default:
            printf("\n//Opção Incorreta, tente novamente!!//\n\n");
            MainMenu();
            break;
        }
    } while (Escolha != 0);

    GravarFicheiro(ListaDeJobs->Operacoes);
}
//Adicionar menu //Adicionar Maquinas
//Adicionar menu alterar op��o do utilizador


