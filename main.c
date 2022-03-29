#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include <string>


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
	int operation;
}Operacao;

//Lista de n operações
typedef struct ListadeOperacoes{
	Operacao operation;
	struct ListadeOperacoes* proximooperacao;
}ListadeOperacoes;









//------------------------------------------------------------


//
//Estrutura para definir um job
typedef struct Job{
	string jobid;
	ListadeOperacoes* operacoes
}Job;

// Adicionar toda duração do job (DuracaoJob)
typedef struct DuracaoJob{
	int job;
	int duracao;
}ListadeOperacoes;



//------------------------------------------------------------
//-----------------------MAIN---------------------------------
//------------------------------------------------------------



int main() {
	
	
	
	
	
	
}



