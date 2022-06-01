//Licenciatura Engenharia Informática Médica
//Diogo Alexandre Mendes Simões Nº15328
//Estrutura de Dados Avançadas

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Estrutura.h"


Escalonamento* inserirInicioEscala(Escalonamento* inicio, Escala* lista, int Maquina);
Escalonamento* inserirFimEscala(Escalonamento* inicio, Escala* lista, int Maquina);
Escala* inserirInicioJob(Escala* inicio, int Job, int Operacao);
Escala* inserirFimJob(Escala* inicio, int Job, int Operacao);


void Escalonamento(Job* inicio);
