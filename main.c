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




//Estrutura para definir uma Operação
typedef struct Operacao{
	int idOperacao;
}Operacao;

//Lista de n operações
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






//------------------------------------------------------------



//Estrutura para definir um job
typedef struct Job{
	string jobid;
	ListadeOperacoes* operacoes
}Job;

// Adicionar toda duração do job (DuracaoJob)
typedef struct DuracaoJob{
	float job;
	float duracao;
}ListadeOperacoes;



//------------------------------------------------------------
//-----------------------MAIN---------------------------------
//------------------------------------------------------------



int main() {
	
	
	
	
	
	
}



