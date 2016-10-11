#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define NB_SONG 3
#define TAILLE_MAX 100


struct chanter{
  int nbr_chanter;
  char *chanson;
};

void *supporter (void *arg){
  struct chanter *team_chanter = (struct chanter *)arg;
  int       i ;
  int       pid ;
  pthread_t tid ;  
  pid = getpid () ;
  tid = pthread_self () ;
  srand ((int) tid) ;


  for (i = 0; i < team_chanter->nbr_chanter; i++){
    printf ("Processus %d Thread %x : %s \n", pid, (unsigned int) tid, team_chanter->chanson) ;
    usleep (rand() / RAND_MAX * 1000000.) ;
  }
  return (void *) tid ;
}

int main (int argc, char **argv){

  struct chanter *team1_chanter;
  struct chanter *team2_chanter;

  int team1 ;
  int team2 ;
  int i ;
  int nb_threads = 0 ;
  pthread_t *tids ;

  if (argc != 5){
    fprintf(stderr, "usage : %s team1 nombre_chanter team2 nombre_chanter\n", argv[0]) ;
    exit (-1) ;
  }

  team1_chanter = malloc(sizeof(struct chanter));
  team2_chanter = malloc(sizeof(struct chanter));

  team1_chanter->nbr_chanter = atoi(argv[2]);
  team2_chanter->nbr_chanter = atoi(argv[4]);

  team1_chanter->chanson = malloc(sizeof(char)*TAILLE_MAX);
  team2_chanter->chanson = malloc(sizeof(char)*TAILLE_MAX);

  strcpy(team1_chanter->chanson, "Allons enfants de la patrie");
  strcpy(team2_chanter->chanson, "Swing low, sweet chariot");

  team1 = atoi (argv[1]) ;
  team2  = atoi (argv[3]) ;
  nb_threads = team1 + team2; 
  tids = malloc (nb_threads*sizeof(pthread_t)) ;


  /* Create the threads for team1 */
  for (i = 0 ; i < team1; i++){
    pthread_create (&tids[i], NULL, supporter, team1_chanter) ;
  }
  /* Create the other threads (ie. team2) */
  for ( ; i < nb_threads; i++){
    pthread_create (&tids[i], NULL, supporter, team2_chanter) ;
  }  

  /* Wait until every thread ened */ 
  for (i = 0; i < nb_threads; i++){
    pthread_join (tids[i], NULL) ;
  }
  
  free (tids) ;
  return EXIT_SUCCESS;
}
