#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//HEADERS FOR SERVER LIBRARY
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
//HEADERS FOR THREADS LIBRARY
#include <pthread.h>
//FUZZY LIBRARY
#include "fuzzy.h"
//---------------------------------------------------------------------
#define MINHAPORTA 20000    /* Porta que os usuarios irão se conectar*/
#define BACKLOG 10     /* Quantas conexões pendentes serão indexadas */

float e;  
float ed;
float out;
char res[40];

pthread_t THREADS[2];

void *runFuzzy(){
	
//Funções de pertinencia.--------
	float pGN[4] = {-1,-1,-0.75,-0.5};
	float pMN[3] = {-0.75,-0.5,-0.25};
	float pPN[3] = {-0.5,-0.25,0};
	float pZZ[3] = {-0.25,0,0.25};
	float pPP[3] = {0,0.25,0.5};
	float pMP[3] = {0.25,0.5,0.75};
	float pGP[4] = {0.5,0.75,1,1};

	pertinence GN = {&pGN,4};
	pertinence MN = {&pMN,3};
	pertinence PN = {&pPN,3};
	pertinence ZZ = {&pZZ,3};
	pertinence PP = {&pPP,3};
	pertinence MP = {&pMP,3};
	pertinence GP = {&pGP,4};
	
//Range de X e Y das funções de pertinencia
	float xi = -1;
	float xf = 1;
	float yi = -1;
	float yf = 1;
	float step = 0.04;

	system("echo -n 'out' > /sys/class/gpio/gpio27/direction");

	printf("Starting loop\n");
	while(1){
	// 	Regras-------------------------
			srand(time(NULL));
			e = rand()%1000;
			e = (e*2/1000.0)-1;

			srand(time(NULL));
			ed = rand()%1000;
			ed = (ed*2/1000.0)-1;
			
			system("echo -n '1' > /sys/class/gpio/gpio27/value");

			rule rules[49] = {
				{andOp(fuzzify(e,GN),fuzzify(ed,GN)), &GN},
				{andOp(fuzzify(e,GN),fuzzify(ed,MN)), &GN},
				{andOp(fuzzify(e,GN),fuzzify(ed,PN)), &MN},
				{andOp(fuzzify(e,GN),fuzzify(ed,ZZ)), &MN},
				{andOp(fuzzify(e,GN),fuzzify(ed,PP)), &PN},
				{andOp(fuzzify(e,GN),fuzzify(ed,MP)), &PN},
				{andOp(fuzzify(e,GN),fuzzify(ed,GP)), &ZZ},

				{andOp(fuzzify(e,MN),fuzzify(ed,GN)), &GN},
				{andOp(fuzzify(e,MN),fuzzify(ed,MN)), &MN},
				{andOp(fuzzify(e,MN),fuzzify(ed,PN)), &MN},
				{andOp(fuzzify(e,MN),fuzzify(ed,ZZ)), &PN},
				{andOp(fuzzify(e,MN),fuzzify(ed,PP)), &PN},
				{andOp(fuzzify(e,MN),fuzzify(ed,MP)), &ZZ},
				{andOp(fuzzify(e,MN),fuzzify(ed,GP)), &PP},

				{andOp(fuzzify(e,PN),fuzzify(ed,GN)), &MN},
				{andOp(fuzzify(e,PN),fuzzify(ed,MN)), &MN},
				{andOp(fuzzify(e,PN),fuzzify(ed,PN)), &PN},
				{andOp(fuzzify(e,PN),fuzzify(ed,ZZ)), &PN},
				{andOp(fuzzify(e,PN),fuzzify(ed,PP)), &ZZ},
				{andOp(fuzzify(e,PN),fuzzify(ed,MP)), &PP},
				{andOp(fuzzify(e,PN),fuzzify(ed,GP)), &PP},

				{andOp(fuzzify(e,ZZ),fuzzify(ed,GN)), &MN},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,MN)), &PN},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,PN)), &PN},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,ZZ)), &ZZ},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,PP)), &PP},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,MP)), &PP},
				{andOp(fuzzify(e,ZZ),fuzzify(ed,GP)), &MP},

				{andOp(fuzzify(e,PP),fuzzify(ed,GN)), &PN},
				{andOp(fuzzify(e,PP),fuzzify(ed,MN)), &PN},
				{andOp(fuzzify(e,PP),fuzzify(ed,PN)), &ZZ},
				{andOp(fuzzify(e,PP),fuzzify(ed,ZZ)), &PP},
				{andOp(fuzzify(e,PP),fuzzify(ed,PP)), &PP},
				{andOp(fuzzify(e,PP),fuzzify(ed,MP)), &MP},
				{andOp(fuzzify(e,PP),fuzzify(ed,GP)), &MP},

				{andOp(fuzzify(e,MP),fuzzify(ed,GN)), &PN},
				{andOp(fuzzify(e,MP),fuzzify(ed,MN)), &ZZ},
				{andOp(fuzzify(e,MP),fuzzify(ed,PN)), &PP},
				{andOp(fuzzify(e,MP),fuzzify(ed,ZZ)), &PP},
				{andOp(fuzzify(e,MP),fuzzify(ed,PP)), &MP},
				{andOp(fuzzify(e,MP),fuzzify(ed,MP)), &MP},
				{andOp(fuzzify(e,MP),fuzzify(ed,GP)), &GP},

				{andOp(fuzzify(e,GP),fuzzify(ed,GN)), &ZZ},
				{andOp(fuzzify(e,GP),fuzzify(ed,MN)), &PP},
				{andOp(fuzzify(e,GP),fuzzify(ed,PN)), &PP},
				{andOp(fuzzify(e,GP),fuzzify(ed,ZZ)), &MP},
				{andOp(fuzzify(e,GP),fuzzify(ed,PP)), &MP},
				{andOp(fuzzify(e,GP),fuzzify(ed,MP)), &GP},
				{andOp(fuzzify(e,GP),fuzzify(ed,GP)), &GP}
			};


		//-------------------------------
			out = defuzzify(rules,49);
			system("echo -n '0' > /sys/class/gpio/gpio27/value");
	}	

}

void *server(){
	int Meusocket, Novosocket;  /* escuta em Meusocket, nova conexão
	                               em Novosocket */
	struct sockaddr_in meu_endereco;    /* informação do meu endereco */
	struct sockaddr_in endereco_dele; /* informação do endereco do conector */
	int tamanho;

	if ((Meusocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}

	meu_endereco.sin_family = AF_INET;
	meu_endereco.sin_port = htons(MINHAPORTA);
	meu_endereco.sin_addr.s_addr = INADDR_ANY; /* coloca IP automaticamente */
	bzero(&(meu_endereco.sin_zero), 8);        /* Zera o resto da estrutura */

	if (bind(Meusocket, (struct sockaddr *)&meu_endereco, sizeof(struct sockaddr))== -1) 
	{
		perror("bind");
		exit(1);
	}
	if (listen(Meusocket, BACKLOG) < 0) 
	{
		perror("listen");
		exit(1);
	}

	//tamanho = sizeof(struct sockaddr_in);
	//Novosocket = accept(Meusocket, (struct sockaddr *)&endereco_dele,&tamanho);
	//if(Novosocket < 0){
		//perror("accept");
		//exit(1);
	//}
	while(1){
		tamanho = sizeof(struct sockaddr_in);
		Novosocket = accept(Meusocket, (struct sockaddr *)&endereco_dele,&tamanho);
		if(Novosocket < 0){
			perror("accept");
			continue;
		}
		printf("Servidor: chegando conexão de %s\n",inet_ntoa(endereco_dele.sin_addr));
		if (!fork()) {
			sprintf (res, "e = %.3f, ed = %.3f, out = %.3f", e,ed,out);
			if (send(Novosocket, res, 40, 0) == -1)
			{
				perror("send");
				close(Novosocket);
				exit(0);
			}
		}
		//sleep(10);
		close(Novosocket);
		while(waitpid(-1,NULL,WNOHANG) > 0); /* Limpa o processo crianca.fork() */
	}
}

int main(int argc, char *argv[]){
	printf("Creating Trheads...\n");
	pthread_create(&(THREADS[0]), NULL, runFuzzy, NULL);
	pthread_create(&(THREADS[1]), NULL, server, NULL);

	printf("Join on Threads\n");
	pthread_join(THREADS[0], NULL);
	pthread_join(THREADS[1], NULL);

	return 0;
}
