#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main(int argq, char *argv[]){
    time_t t; //necessário para a máquina fazer uma escolha aleatória
	srand((unsigned) time(&t)); //necessário para a máquina fazer uma escolha aleatória
	enum states {NADA, Pedra, Papel, Tesoura}; // estados de escolha
	enum victor {Vitoria, Derrota, Empate, Indecisao}; // estados de resultado
	int partidas; // número de partidas a ser decidido
	if(argq == 2){ // caso queira começar o programa com uma linha de comando com um argumento adicional (ex.: $./a.out x)
		int procuraalfa;
		for(procuraalfa = 0; procuraalfa < strlen(argv[1]);procuraalfa++){
			if (isdigit(argv[1][procuraalfa]) == 0){ // se houver algum caractere que não seja digito, o programa responderá com uma mensagem de erro
				fprintf(stderr,"Erro, argumento não é inteiro.");
				exit(-1);
			}
		}
		partidas = atoi(argv[1]); // o número de partidas foi definido pelo primeiro argumento
	}
	else if (argq > 2){ // caso tenha mais de um argumento na linha de comando, o programa responderá com uma mensagem de erro
		fprintf(stderr,"Erro, mais de um argumento na linha de comando.");
		exit(-2);
	}
	else{ // se não houver nenhum argumento adicional na linha de comando, o programa em si perguntará o número de partidas
		printf("Qual o número de partidas a serem definidas?\n");
		scanf("%i", &partidas);
	}
	if (partidas > 0){
		int vitoriasJogador = 0; // definindo o número de vitórias do jogador
		int vitoriasOponente = 0; // definindo o número de vitórias do computador
		int i;
		for (i = 1; i <= partidas; i++){ //loop de partida
			enum victor confronto = Indecisao; //resultado ainda não definido
			enum states estadoJogador = NADA; // escolha do jogador não definida
			enum states estadoOponente = NADA; // escolha da maquina não definida
			char est[10]; // string a ser scaneado e usado como entrada
			char * escpd;
			char * escpp;
			char * escts;
			while (estadoJogador == NADA){
				printf("Escolha entre Pedra, Papel ou Tesoura.\n"); // o jogador DEVERÁ escrever sua escolha para definir o estadoJogador
				scanf("%s", est);
				escpd = strstr(est, "Pedra");
				escpp = strstr(est, "Papel");
				escts = strstr(est, "Tesoura"); // a seguir as condicionais caso o jogador escolha pedra, papel ou tesoura
				if (escpd != NULL){
					estadoJogador = Pedra;
				}
				else if (escpp != NULL){
					estadoJogador = Papel;
				}
				else if (escts != NULL){
					estadoJogador = Tesoura;
				}
			}
			printf("Você escolheu: %s\n",est);
			int numeroaleatorio = rand()% 3 + 1; // gerador de número aleatório para definir a escolha da máquina
			while (estadoOponente == NADA){
				switch (numeroaleatorio){
					case 1:
						estadoOponente = Pedra;
						printf("O oponente escolheu: Pedra\n");
						break;
					case 2:
						estadoOponente = Papel;
						printf("O oponente escolheu: Papel\n");
						break;
					case 3:
						estadoOponente = Tesoura;
						printf("O oponente escolheu: Tesoura\n");
						break;
				}
			}
			while (confronto == Indecisao){ // enquanto o resultado ainda não for definido pelas escolhas do jogador e máquina, fique em loop
				switch(estadoJogador){
					case Pedra:
						if (estadoOponente == Pedra){
							confronto = Empate;}
						else if (estadoOponente == Papel){
							confronto = Derrota;}
						else if (estadoOponente == Tesoura){
							confronto = Vitoria;}
						break;
					case Papel:
						if (estadoOponente == Pedra){
							confronto = Vitoria;}
						else if (estadoOponente == Papel){
							confronto = Empate;}
						else if (estadoOponente == Tesoura){
							confronto = Derrota;}
						break;
					case Tesoura:
						if (estadoOponente == Pedra){
							confronto = Derrota;}
						else if (estadoOponente == Papel){
							confronto = Vitoria;}
						else if (estadoOponente == Tesoura){
							confronto = Empate;}
						break;
				}
			}
			switch(confronto){ // mensagem de resultado da partida atual
				case Vitoria:
					printf("Jogador ganha da Maquina.\n");
					vitoriasJogador++;
					break;
				case Derrota:
					printf("Jogador perde para a Maquina.\n");
					vitoriasOponente++;
					break;
				case Empate:
					printf("Houve um empate!\n");
					break;
			}
			printf("Partida N°: %d Jogador: %d Maquina: %d\n", i, vitoriasJogador, vitoriasOponente); // pontuação após a i-ésima partida
		}
		if (vitoriasJogador > vitoriasOponente){// mensagens de vitória ou empate
			printf("O jogador vence!");
		}
		else if (vitoriasJogador < vitoriasOponente){
			printf("A maquina vence!");
		}
		else{
			printf("Não há vencedor!");
		}
		return (0);
	}	
}