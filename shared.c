#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <stdio.h>

int main(){
int shm_id;
size_t size = sizeof(double);
key_t key = 45;
int shmflg = IPC_CREAT | 0666;

double *number;
shm_id = shmget(key,size,shmflg);

if(shm_id == -1){
	perror("Error");
	exit(0);
}
number = shmat(shm_id,NULL,0);

if(number == (double *) - 1){
	perror("Error");
	exit(0);
}
*number = 54.54;
while(*number == 54.54){
	sleep(1);
}
printf("The other process changed the value to: %.2f\n",*number);
if(shmdt(number)==-1){
	perror("Error");

}
shmctl(shm_id,IPC_RMID,NULL);
return 0;
}
