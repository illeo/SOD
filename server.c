#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHMSZ 25 //dimensione segmento
char SEM_NAME[]= "gigi"; //nome del semaforo

int main()
{
	char ch;
	int shmid;
	key_t key;
	char *shm,*s;
	sem_t *mutex;
	
	//chiave statica
	key = 1000;
	
	//crea & inizializza il named semaphore
	
	printf("\n Serv: creo named semaphore ");
	mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
	if(mutex == SEM_FAILED)
    {
		perror("Impossibile creare semaphore");
		sem_unlink(SEM_NAME);
		exit(-1);
    }
	
	//crea  shared memory segment 
	printf("\n Serv: creo shared memory ");
	shmid = shmget(key,SHMSZ,IPC_CREAT|0666);
	if(shmid<0)
    {
		perror("Serv: Errore in shmget");
		exit(-1);
    }
	
	//attach 
	shm = (char *)shmat(shmid,NULL,0);
	
    /* descrittori di socket e numero di porta del server */
    int server_socket, client_socket, port_number;

    /* indirizzi del server e del client */
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;

    /* identificativo del thread che serve una connessione */ 
    pthread_t tid;

    /* verifica la presenza di un argomento */
    if (argc < 2) {
        error("ERROR, no port provided\n");
    }
     
    /* apre la socket del server e verifica che tutto
       sia andato bene */       
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) 
        error("ERROR opening socket");

    /* Riempie di zeri l'indirizzo del server */   
    bzero((char *) &server_addr, sizeof(server_addr));

    /* recupera il numero di porta */
    port_number = atoi(argv[1]);

    /* Compila i campi per l'indirizzo del server */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_number);

    /* associa la socket del server alla porta
       e la abilita a ricevere messaggi */
    if (bind(server_socket, (struct sockaddr *) &server_addr,
            sizeof(server_addr)) < 0) 
        error("ERROR on binding");
    listen(server_socket, 5);

    /* calcola una volta per tutte la lunghezza di client_addr */
    client_addr_len = sizeof(client_addr);

    /* forever padre*/
    if (pid > 0){
    sem_wait(mutex);
    /*variabile di conteggio*/
    int n = 0;
    s = shm;
		sem_wait(mutex);
		printf("\n Inizializzo la variabile\n");
		*s = (char) n;
		sem_post(mutex);
    }
    sem_post (mutex);
    	while (1) {
        	/* attende l'arrivo di un messaggio */
        	/* crea un figlio che gestisca la connessione */
        	if (struct sockaddr *) &client_addr, &client_addr_len));
        		pid = fork();
        	/* verifica che tutto sia andato bene */
        	if (client_socket < 0) 
        	    error("ERROR on accept");
     	}/* end while */
     }
     /*figlio*/

     if (pid == 0)
     {
     int x, num;
	/*gestione del client*/
	if ((num=read(NuovoSocket,buffer,sizeof(buffer)))<0)
      {
         printf("Impossibile leggere il messaggio.\n");
         ChiudiSocket(NuovoSocket);
      }
	sem_wait(mutex);
	num = atoi (*s);
	*s = (char) (num + x);
	sem_post(mutex);
	close(client_socket);
}//fine
     
	sem_close(mutex);
	printf("\n Serv: chiuso semaforo");
	sem_unlink(SEM_NAME);
	printf("\n Serv: eliminato semaforo");
	shmctl(shmid, IPC_RMID, 0);
	printf("\n Serv: rimossa shared memory. Exit....");
	exit(0);
}
