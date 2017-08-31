/*
Baseado no Código de Berenger Bramas
http://berenger.eu/blog/c-openmp-examples-of-basic-parallel-programming/
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//Protótipos
void TempoGasto();
void emParalelo();
void apenasDoisThreads();
void barreiraImplícita();
void usandoSecoes();
void usandoFor();
void exemploBarreira();
void usandoCritical();


int main(int argc, char **argv){
	//testando a geração de threads
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

	barreiraImplícita();
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
* Usa as funções do openMP para contar o tempo gasto
* para realizar uma determinada tarefa.
*/
void TempoGasto(){
	printf("Entramos em TempoGasto\n");
	const double startTime = omp_get_wtime();

	// Coloque aqui as declarações que precisa medir

	const double endTime = omp_get_wtime();
	printf("Duração = %lf segundos\n", (endTime - startTime));
	printf("----------------------\n");
}

/*
* Apenas para fazer alguma coisa em paralelo
* usando os threads limitados pelo hardware.
* Além de informar o número dos threads abertos vamos informar
* quantos threads podemos abrir.
*
* Quantos cores podemos acessar? num = omp_get_num_procs( );
* Determinando o número de threads = número de cores: num = omp_set_num_threads(omp_get_num_procs( ));
* Quantos threads estamos usando? num = omp_get_num_threads( );
* Qual thread está em uso? me = omp_get_thread_num( );
*/
void emParalelo(){
	printf("Testando os Threads ---\n");
	// Aqui começamos a trabalhar em paralelo
	// o thread original será o num zero.
#pragma omp parallel
	{
		// Cada thread imprime seu número
		printf("Thread numero %d de %d threads\n", omp_get_thread_num(), omp_get_num_threads());
	}
	printf("Estamos de volta ao thread original ---\n");
}

/*
* Vamos ver como especificar o número de threads que
* podemos abrir
*/
void apenasDoisThreads(){
	printf("Apenas 2 threads ---\n");
	// Primeiro temos que desativar o número de threads automático
	omp_set_dynamic(0);
	// Depois setar o número de threads que queremos abrir
	omp_set_num_threads(2);
#pragma omp parallel
	{
		printf("Eu sou o thread numero %d de %d threads\n", omp_get_thread_num(), omp_get_num_threads());
	}

	printf("Agora quero 3 threads\n");
	// Podemos definir o número de threads diretamente na diretiva pragma
#pragma omp parallel num_threads(3)
	{
		printf("Eu sou o thread numero %d de %d threads\n", omp_get_thread_num(), omp_get_num_threads());
	}
	printf("Estamos de volta ao thread original ---\n");
}

/*
* Para sincronizar existe uma barreira implícita.
* Todos os threads devem terminar antes que o fluxo chegue
* ao thread principal.
*/
void barreiraImplícita(){
	printf("Barreira Implicita ---\n");
#pragma omp parallel num_threads(4)
	{
		// cada thread irá espera 2 vezes o seu id segundos
		double startTime = omp_get_wtime();
		while ( (omp_get_wtime() - startTime) < 2 * double(omp_get_thread_num()) );
		printf("Eu sou o thread %d e terminei de esperar!\n", omp_get_thread_num());
	}
	printf("Estamos de volta ao thread original ---\n");
}

/*
* Usamos seções para determinar que parte do código irá para qual thread
* o OpenMP irá atribuir o código de cada seção para um thread diferente se
* existir algum thread disponível.
*/
void usandoSecoes(){
	printf("Usando Secoes ---\n");

	//vamos começar o processamento paralelo com dois threads e três seções
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

	// Número de seções menor que o número de threads
	printf("Trabalhando com 4 threads e 3 seções ---\n");
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
*		Irá forçar que você defina todas as variáveis como privadas ou compartilhadas
*
*		private(x)
*		Significa que cada thread terá suá própria cópia da variável x
*
*		shared(x)
*		Significa que todos os threads usarão a mesma variável x.
*
*		reduction
*		Provoca a reduçãode variáveis externas utilizadas dentro do for.
*/
void usandoFor(){
	printf("Usando For ---\n");
	printf("Sem se preocupar com o número de threads\n");

	// criando threads para um for
#pragma omp parallel for
	for ( int idx = 0; idx < 10; ++idx ){
		printf("Thread %d trabalhando com o idx %d\n", omp_get_thread_num(), idx);
	}

	printf("For com 4 threads \n");

	// Definimos o número de threads antes
	omp_set_num_threads(4);
#pragma omp parallel for
	for ( int idx = 0; idx < 10; ++idx ){
		printf("Thread %d trabalhando com idx %d\n", omp_get_thread_num(), idx);
	}

	// Para ver variáveis depois do for
	printf("For com variáveis externas \n");
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
*		ordered: especifica que cada interação em um laços será executada na mesma ordem
*		que seria executada se o algoritmo fosse executado em série. Os threads terão que esperar até
*		o conjunto interações anterior tenha sido executado.
*
*		single: especifica que o código será executado por um único thread
*
*		nowait: especifica que o threads não devem esperar na barreira
*
*		master: especifica que o código só poderá ser executado pelo thread master
*
*/
void exemploBarreira(){
	printf("Exemplo Barreira --\n");

#pragma omp parallel num_threads(4)
	{
		double startTime = omp_get_wtime();
		while ( (omp_get_wtime() - startTime) < double(omp_get_thread_num()) );
		printf("Me (%d)  I finish to count\n", omp_get_thread_num());
		// cada thread irá esperar a barreira
#pragma omp barrier
		printf("Passamos a barreira\n");
	}
	printf("Em paralelo e ordenado\n");

	// Um laço ordenado
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
		// só o primeiro que chegar
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
		// só o primeiro que chegar
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
		//só o master será executado
#pragma omp master
		{
			printf("O master: %d \n", omp_get_thread_num());
		} // nowait can not be stated so others continue
		printf("O thread %d\n finalizando", omp_get_thread_num());
	}
}

/*
* Usando uma seção crítica
*
* critical: especifica que o código deve ser executado por um único thread de cada vez.
*
* atomic: especifica que uma localização de memória específica deve ser atualizada atomicamente.
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


