#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

int shm_id;
size_t size = sizeof(double);
int shmflg = IPC_CREAT | 0666;
key_t key = 45;
double *number;

shm_id = shmget(key,size,shmflg);

if(shm_id == -1){
	perror("Error");
	exit(0);
}

number = shmat(shm_id, NULL, 0);

if(number == (double*)-1){
	perror("Error");
	exit(0);
}

printf("The value stored in the first process is: %.2f\n",*number);
*number = 64.64;

if(shmdt(number)==-1){
	perror("Error");
}
shmctl(shm_id,IPC_RMID,NULL);
return 0;
}
