/*
Baseado no C�digo de Berenger Bramas
http://berenger.eu/blog/c-openmp-examples-of-basic-parallel-programming/
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//Prot�tipos
void TempoGasto();
void emParalelo();
void apenasDoisThreads();
void barreiraImpl�cita();
void usandoSecoes();
void usandoFor();
void exemploBarreira();
void usandoCritical();


int main(int argc, char **argv){
	//testando a gera��o de threads
	for ( int i = 0; i < 3; i++ ){
		omp_set_num_threads(4);
#pragma omp parallel default(none)
		{
			printf("Hello, World... Thread #%d!\n", omp_get_thread_num());
		}
		printf("\n");
	}
	system("Pause");
	system("Cls");

	TempoGasto();
	emParalelo();
	system("Pause");
	system("Cls");

	apenasDoisThreads();
	system("Pause");
	system("Cls");

	barreiraImpl�cita();
	system("Pause");
	system("Cls");

	usandoSecoes();
	system("Pause");
	system("Cls");

	usandoFor();
	system("Pause");
	system("Cls");

	exemploBarreira();
	system("Pause");
	system("Cls");

	usandoCritical();
	system("Pause");
	return 0;
}

/*
* Usa as fun��es do openMP para contar o tempo gasto
* para realizar uma determinada tarefa.
*/
void TempoGasto(){
	printf("Entramos em TempoGasto\n");
	const double startTime = omp_get_wtime();

	// Coloque aqui as declara��es que precisa medir

	const double endTime = omp_get_wtime();
	printf("Dura��o = %lf segundos\n", (endTime - startTime));
	printf("----------------------\n");
}

/*
* Apenas para fazer alguma coisa em paralelo
* usando os threads limitados pelo hardware.
* Al�m de informar o n�mero dos threads abertos vamos informar
* quantos threads podemos abrir.
*
* Quantos cores podemos acessar? num = omp_get_num_procs( );
* Determinando o n�mero de threads = n�mero de cores: num = omp_set_num_threads(omp_get_num_procs( ));
* Quantos threads estamos usando? num = omp_get_num_threads( );
* Qual thread est� em uso? me = omp_get_thread_num( );
*/
void emParalelo(){
	printf("Testando os Threads ---\n");
	// Aqui come�amos a trabalhar em paralelo
	// o thread original ser� o num zero.
#pragma omp parallel
	{
		// Cada thread imprime seu n�mero
		printf("Thread numero %d de %d threads\n", omp_get_thread_num(), omp_get_num_threads());
	}
	printf("Estamos de volta ao thread original ---\n");
}

/*
* Vamos ver como especificar o n�mero de threads que
* podemos abrir
*/
void apenasDoisThreads(){
	printf("Apenas 2 threads ---\n");
	// Primeiro temos que desativar o n�mero de threads autom�tico
	omp_set_dynamic(0);
	// Depois setar o n�mero de threads que queremos abrir
	omp_set_num_threads(2);
#pragma omp parallel
	{
		printf("Eu sou o thread numero %d de %d threads\n", omp_get_thread_num(), omp_get_num_threads());
	}

	printf("Agora quero 3 threads\n");
	// Podemos definir o n�mero de threads diretamente na diretiva pragma
#pragma omp parallel num_threads(3)
	{
		printf("Eu sou o thread numero %d de %d threads\n", omp_get_thread_num(), omp_get_num_threads());
	}
	printf("Estamos de volta ao thread original ---\n");
}

/*
* Para sincronizar existe uma barreira impl�cita.
* Todos os threads devem terminar antes que o fluxo chegue
* ao thread principal.
*/
void barreiraImpl�cita(){
	printf("Barreira Implicita ---\n");
#pragma omp parallel num_threads(4)
	{
		// cada thread ir� espera 2 vezes o seu id segundos
		double startTime = omp_get_wtime();
		while ( (omp_get_wtime() - startTime) < 2 * double(omp_get_thread_num()) );
		printf("Eu sou o thread %d e terminei de esperar!\n", omp_get_thread_num());
	}
	printf("Estamos de volta ao thread original ---\n");
}

/*
* Usamos se��es para determinar que parte do c�digo ir� para qual thread
* o OpenMP ir� atribuir o c�digo de cada se��o para um thread diferente se
* existir algum thread dispon�vel.
*/
void usandoSecoes(){
	printf("Usando Secoes ---\n");

	//vamos come�ar o processamento paralelo com dois threads e tr�s se��es
	printf("Iniciando com 2 threads e 3 secoes\n");
#pragma omp parallel sections num_threads(2)
	{
#pragma omp section
		{
			printf("Abrindo trabalho 1\n");
			double startTime = omp_get_wtime();
			printf("Eu sou o thread %d!\n", omp_get_thread_num());
			while ( (omp_get_wtime() - startTime) < 2.0 );
			printf("Fechando trabalho 1\n");
		}
#pragma omp section
		{
			printf("Abrindo trabalho 2\n");
			double startTime = omp_get_wtime();
			printf("Eu sou o thread %d!\n", omp_get_thread_num());
			while ( (omp_get_wtime() - startTime) < 2.0 );
			printf("Fechando trabalho 2\n");
		}
#pragma omp section
		{
			printf("Abrindo trabalho 3\n");
			double startTime = omp_get_wtime();
			printf("Eu sou o thread %d!\n", omp_get_thread_num());
			while ( (omp_get_wtime() - startTime) < 2.0 );
			printf("Fechando trabalho 3\n");
		}
	}

	// N�mero de se��es menor que o n�mero de threads
	printf("Trabalhando com 4 threads e 3 se��es ---\n");
#pragma omp parallel sections num_threads(4)
	{
#pragma omp section
		{
			printf("Abrindo trabalho 1\n");
			double startTime = omp_get_wtime();
			printf("Eu sou o thread %d!\n", omp_get_thread_num());
			while ( (omp_get_wtime() - startTime) < 2.0 );
			printf("Fechando trabalho 1\n");
		}
#pragma omp section
		{
			printf("Abrindo trabalho 2\n");
			double startTime = omp_get_wtime();
			printf("Eu sou o thread %d!\n", omp_get_thread_num());
			while ( (omp_get_wtime() - startTime) < 2.0 );
			printf("Fechando trabalho 2\n");
		}
#pragma omp section
		{
			printf("Abrindo trabalho 3\n");
			double startTime = omp_get_wtime();
			printf("Eu sou o thread %d!\n", omp_get_thread_num());
			while ( (omp_get_wtime() - startTime) < 2.0 );
			printf("Fechando trabalho 3\n");
		}
	}
}

/*
* Usando o For
*		default(none)
*		Ir� for�ar que voc� defina todas as vari�veis como privadas ou compartilhadas
*
*		private(x)
*		Significa que cada thread ter� su� pr�pria c�pia da vari�vel x
*
*		shared(x)
*		Significa que todos os threads usar�o a mesma vari�vel x.
*
*		reduction
*		Provoca a redu��ode vari�veis externas utilizadas dentro do for.
*/
void usandoFor(){
	printf("Usando For ---\n");
	printf("Sem se preocupar com o n�mero de threads\n");

	// criando threads para um for
#pragma omp parallel for
	for ( int idx = 0; idx < 10; ++idx ){
		printf("Thread %d trabalhando com o idx %d\n", omp_get_thread_num(), idx);
	}

	printf("For com 4 threads \n");

	// Definimos o n�mero de threads antes
	omp_set_num_threads(4);
#pragma omp parallel for
	for ( int idx = 0; idx < 10; ++idx ){
		printf("Thread %d trabalhando com idx %d\n", omp_get_thread_num(), idx);
	}

	// Para ver vari�veis depois do for
	printf("For com vari�veis externas \n");
	int sum = 0;
	int dec = 0;
#pragma omp parallel for reduction(+:sum) reduction(-:dec)
	for ( int idx = 0; idx < 10; ++idx ){
		++sum;
		--dec;
		printf("Thread %d soma = %d\n", omp_get_thread_num(), sum);
	}
	printf("Soma fora do for = %d\n", sum);
	printf("Dec fora do for %d\n", dec);

	printf("------------------------------------------------------\n");
}


/*
* Exemplo usando as diretivas de barreira
*
*		ordered: especifica que cada intera��o em um la�os ser� executada na mesma ordem
*		que seria executada se o algoritmo fosse executado em s�rie. Os threads ter�o que esperar at�
*		o conjunto intera��es anterior tenha sido executado.
*
*		single: especifica que o c�digo ser� executado por um �nico thread
*
*		nowait: especifica que o threads n�o devem esperar na barreira
*
*		master: especifica que o c�digo s� poder� ser executado pelo thread master
*
*/
void exemploBarreira(){
	printf("Exemplo Barreira --\n");

#pragma omp parallel num_threads(4)
	{
		double startTime = omp_get_wtime();
		while ( (omp_get_wtime() - startTime) < double(omp_get_thread_num()) );
		printf("Me (%d)  I finish to count\n", omp_get_thread_num());
		// cada thread ir� esperar a barreira
#pragma omp barrier
		printf("Passamos a barreira\n");
	}
	printf("Em paralelo e ordenado\n");

	// Um la�o ordenado
#pragma omp parallel for num_threads(4) ordered
	for ( int idx = 0; idx < 4; ++idx ){
#pragma omp ordered
		{
			printf("Thread %d\n", omp_get_thread_num());
			double startTime = omp_get_wtime();
			while ( (omp_get_wtime() - startTime) < 2.0 );
			printf("Thread %d  Terminou de contar\n", omp_get_thread_num());
		}
	}

	// Diretiva single
	printf("Usando a diretiva single\n");
#pragma omp parallel num_threads(4)
	{
		// s� o primeiro que chegar
#pragma omp single
		{
			printf("O single %d \n", omp_get_thread_num());
		} // todos os outros threads ficam aqui esperando na barreira
		printf("Thread %d finalizou\n", omp_get_thread_num());
	}

	// Diretiva single nowait
	printf("Usando a diretiva single com nowait\n");
#pragma omp parallel num_threads(4)
	{
		// s� o primeiro que chegar
#pragma omp single nowait
		{
			printf("o single %d \n", omp_get_thread_num());
		} //  other continue
		printf("Thread %d Finalizou\n", omp_get_thread_num());
	}

	//Diretiva master
	printf("Usando a diretiva master\n");
#pragma omp parallel num_threads(4)
	{
		//s� o master ser� executado
#pragma omp master
		{
			printf("O master: %d \n", omp_get_thread_num());
		} // nowait can not be stated so others continue
		printf("O thread %d\n finalizando", omp_get_thread_num());
	}
}

/*
* Usando uma se��o cr�tica
*
* critical: especifica que o c�digo deve ser executado por um �nico thread de cada vez.
*
* atomic: especifica que uma localiza��o de mem�ria espec�fica deve ser atualizada atomicamente.
*/
void usandoCritical(){
	printf("Usando Critical ---\n");
	// com diretiva ordered 
#pragma omp parallel num_threads(4)
	{
		// um por um sem conhecer a ordem
#pragma omp critical
		{
			printf("Thread %d\n", omp_get_thread_num());
			double startTime = omp_get_wtime();
			while ( (omp_get_wtime() - startTime) < 2.0 );
			printf("Thread (%d) terminando de contar \n", omp_get_thread_num());
		}
	}

	// usando atomic */
	int result = 0;
#pragma omp parallel num_threads(4)
	{
#pragma omp atomic
		++result;
	}
	printf("Resultado %d\n", result);

}


