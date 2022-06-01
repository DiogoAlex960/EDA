//Licenciatura Engenharia Informática Médica
//Diogo Alexandre Mendes Simões Nº15328
//Estrutura de Dados Avançadas

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Estrutura.h"
void MainMenu();

void main()
{
   system("cls");
   MainMenu();
}

void MainMenu()
{
    FILE *jobFile;
    job *HeadJob = NULL;
    HeadJob = read(jobFile, HeadJob);
    int Valor;

    do
    {
        printf("##----------------- Menu Principal Jobs ------------------##\n"
               "\t\n"
               "\t > 1 - Listar \n"
               "\t > 2 - Inserir Job \n"
               "\t > 3 - Remover Job \n"
               "\t > 4 - Adicionar Operacoes\n"
               "\t > 5 - Remover Operacoes\n"
               "\t > 6 - Alterar Operacoes\n"
               "\t > 7 - Minimo Tempo\n"
               "\t > 8 - Maximo Tempo\n"
               "\t > 9 - Media Tempo\n"
               "\t > 10 - Escalonamento\n"//Obras
               "\t > 11 - Representacao Process\n"//Obras
               "\t\n"
               "\n\t > 0 - Quit\n"
              "##---------------------------------------------------------##");

        Valor = Dado(0, 11);
        switch (Valor)
        {
        case 1:
            ListaJobs(HeadJob);
            break;
        case 2:
            CriarJob(HeadJob);
            break;
        case 3:
            RemoverJob(HeadJob);
            break;
        case 4:
            CriarOperacao(HeadJob);
            break;
        case 5:
            RemoverOperacao(HeadJob);
            break;
        case 6:
             AlterarOperacao(HeadJob);
            break;
        case 7:
              TempoMinimo(SelecionaJob(HeadJob));
            break;
        case 8:
              TempoMaximo(SelecionaJob(HeadJob));
            break;
        case 9:
              TempoMedio(SelecionaJob(HeadJob));
            break;
        case 10:
           // Escalonamento(HeadJob);
            break;
        case 11:
            // Representa(HeadJob);
            break;
        case 0:
            break;
        default:
            printf("\n\t//Valor Invalido//\n\n");
            MainMenu();
            break;
        }
        if (Valor != 0 && Valor != 6)
        {
            printf("\nEnter para Voltar Atras...");
            getch();
            system("cls");
        }

    } while (Valor != 0);
    write(jobFile, HeadJob);
    _Exit(0);
}
