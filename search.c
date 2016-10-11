#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct search
{
	int portion;
	int indice;
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

void *search(void *arg){
	struct search *s = (struct search *)arg;
	pthread_t tid = pthread_self();
	srand((int)tid); 
	int i = s->portion;
	while(i>0){
		if(s->x == s->T[s->indice]){
			printf("Processus %d Thread %x : Found !\n", getpid(), (unsigned int)tid);
			usleep(rand()/RAND_MAX*1000000.);
			return (void *)tid;
		}
		s->indice++;
		i--;
	}
	printf("Processus %d Thread %x : Not found...\n", getpid(), (unsigned int)tid);
	usleep(rand()/RAND_MAX*1000000.);
	return (void *)tid;
}

int main(int argc, char **argv)
{
	/* code */
	FILE *fichier;
	int *T;
	int size=0, buffer;
	int nb_threads = 0 ;
  	pthread_t *tids ;

	if(argc != 3){
		fprintf(stderr, "usage : %s fichier valeur_a_chercher\n", argv[0]); 
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

	struct search * s = malloc(sizeof(struct search));
	if (s == NULL)
	{
		fprintf(stderr, "Erreur d'allocation de la structure search\n");
		exit(3);
	}
	s->T = T;
	s->size = size;printf("Size : %d\n",size);
	s->x = atoi(argv[2]); // l'élément cherché dans tab
	s->portion = 2;

	if(size >= s->portion){
		nb_threads = size/s->portion;
		tids = malloc (nb_threads*sizeof(pthread_t));
		/* Create the threads */
  		for (int i = 0 ; i < nb_threads; i++){
  			s->indice = i*(s->portion);
  			if(i==nb_threads-1)
  				s->portion = s->size - s->indice;
  			printf("indice = %d | s->portion = %d\n",s->indice,s->portion);
    		pthread_create (&tids[i], NULL, search, s);
  		}

  		for (int i = 0; i < nb_threads; ++i)
  		{
  			pthread_join(tids[i], NULL);
  		}

  		free(tids);
  		return EXIT_SUCCESS;
	}	
	return 0;
}