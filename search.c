#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct search
{
	int x;
	int *T;
	int size;
};

int * init_vecteur(int *T, FILE *file){
	int buffer;
	int i=0;
	rewind(file);
	while(fscanf(file, "%d",&buffer) != EOF){
		T[i] = buffer;
		i++;
	}
	return T;
}

void afficherT(int *T, int size){
	//Afficher le tableau T après l'initialisation
	for (int i = 0; i < size; ++i)
	{
		if (i == 0)
			printf("T = [ ");
		printf("%d ", T[i]);
		if (i == size-1)
			printf("]\n");
	}
}

int search(void *arg){
	struct search *ma_recherce = (struct search *)arg;
	
}

int main(int argc, char const *argv[])
{
	/* code */
	FILE *fichier;
	int *T;
	int size=0, buffer, x;
	int nb_threads = 0 ;
  	pthread_t *tids ;

	if(argc != 3){
		(stderr, "usage : %s fichier valeur_a_chercher\n", argv[0]); 
		exit(-1);
	}
	fichier = fopen(argv[1], "r");
	if(fichier == NULL){
		fprintf(stderr, "Erreur d'ouverture du fichier donné\n");
		exit(1);
	}
	while(fscanf(fichier, "%d", &buffer) != EOF){
		size++;
	}

	T = malloc(sizeof(int)*size);

	if(T == NULL){
		fprintf(stderr, "Erreur d'allocation du tableau T\n");
		exit(2);
	}
		
	T = init_vecteur(T,fichier);
	afficherT(T,size);
	x = atoi(argv[2]); // l'élément cherché dans tab
	if(size >= 2){
		nb_threads = size/2;
		tids = malloc (nb_threads*sizeof(pthread_t));
		/* Create the threads */
  		for (i = 0 ; i < nb_threads; i++){
    		pthread_create (&tids[i], NULL, search, ) ;
  		}
	}	
	return 0;
}