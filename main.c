#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include <string.h>


//------------------------------------------------------------

//Estrutura para definir um Processo
typedef struct Processo{
	int maquina;
	time_t t = time(NULL);
}Processo;

//Lista de n processos
typedef struct ListadeProcessos{
	Processo processo;
	struct ListadeProcessos* proximoprocesso;
	
}ListadeProcessos;




//------------------------------------------------------------




//Estrutura para definir uma OperaÃ§Ã£o
typedef struct Operacao{
	int idOperacao;
}Operacao;

//Lista de n operaÃ§Ãµes
typedef struct ListadeOperacoes{
	Operacao operacao;
	struct ListadeOperacoes* proximaoperacao;
}ListadeOperacoes;


ListadeOperacoes* InserirOperacao(ListadeOperacoes* listadeoperacoes, Operacao newOperacao)
//
Operacao InserirOperacao(int idOperacao) {
	Operacao criarelemento;

	
	criarelemento.operacao = operacao;

	return criarelemento;
}


ListadeOperacoes* RemoverOperacao(ListadeOperacoes* listadeoperacoes)
if (ListadeOperacoes && (ListadeOperacoes->operacao.idOperacao == idOperacao)) {

	ListadeOperacoes* aux = ListadeOperacoes->nextOperation;

	(ListadeOperacoes->operacao.);

	free(ListadeOperacoes);

	return aux;
}


int AlterarOperacao(ListadeOperacoes* listadeoperacoes, int id_operacao, int novo_id_operacao);



//------------------------------------------------------------------------------------------------------


int AlterarOperacao(ListadeOperacoes* listadeoperacoes, int id_operacao, int novo_id_operacao) {

	// Get Operacao, based on id
	ListadeOperacoes* operacao = ProcuraOperacao(listadeoperacoes, novo_id_operacao);

	// If Operacao not found, there's no id to change
	// This may occur because of empty lists
	if (!operacao) return 0;

	// Attribution of new value
	operacao->operacao.idOperacao = novo_id_operacao;
	return 1;
}






//----------------------------------------------------------------------------------------------------
int CalcularTempoOperacao(ListadeOperacoes* listadeoperacoes);


	float a = 0, tempooperacao, tempoprocesso;
	int soma = 0;
	while (listadeoperacoes) {

		tempoprocesso = calcular_tempo_processo(operationList->operation.alternProcesses);
		
		if (tempoprocesso != -1) sum += tempoprocesso;
		count++;

		listadeoperacoes = listadeoperacoes->next;
	}
	
	tempooperacao = (float)a / count;

	return tempooperacao;
}




//------------------------------------------------------------



//Estrutura para definir um job
typedef struct Job{
	string jobid;
	ListadeOperacoes* operacoes
}Job;

// Adicionar toda duraÃ§Ã£o do job (DuracaoJob)
typedef struct DuracaoJob{
	float job;
	float duracao;
}ListadeOperacoes;



//------------------------------------------------------------
//-----------------------MAIN---------------------------------
//------------------------------------------------------------



int main() {
	
	
	Ficheiro Job = ImportJob("../EDA.txt");

	system("cls");
	int ChoiceInt;
	job* jobHead = read_job(ImportJob);

	do
	{
	do
	{
		printf("\t--- MAIN MENU ---\n"
			"\t  1 - Listar Job\n"
			"\t  2 - Adicionar Operação\n"
			"\t  3 - Remover Operação\n"
			"\t  4 - Alterar Operação\n"
			"\n\t  0 - Sair\n");

		ChoiceInt = GetInt(0, 6);
		switch (ChoiceInt)
		{
		case 1:
			(jobHead);
			break;
		case 2:
			jobHead = InserirOperacao(jobHead);
			break;
		case 3:
			jobHead = RemoverOperacao(jobHead);
			break;
		case 4:
			jobHead = AlterarOperacao(jobHead);
			break;
		case 5:
			
			break;
		case 6:
			
			break;
		case 0:
			break;
		default:
			printf("\n\t//Opção Invalida//\n\n");
			MainMenu();
			break;
		}

	} while (ChoiceInt != 0);
}

	
}


