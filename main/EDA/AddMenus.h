#include <stdio.h>
#include "Estrutura.h"

void MainMenu();

void MenuMostraJob(Job* ListaDeJobs);

Job* MenuAdicionaOperacao(Job* ListaDeJobs);

Maquina* MenuAdicionaMaquina(Maquina* ListaDeMaquinas);

Job* MenuRemoveOperacao(Job* ListaDeJobs);

Job* MenuAlteraOperacao(Job* ListaDeJobs);

Operacao* MenuAlteraOperacaoEscolha(Operacao* OperacaoEscolhida, Operacao* ListaDeOperacoes);

void MenuInformacoes(Job* ListaDeJobs);
