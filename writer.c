#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>  
#include "rot13.c"
  
int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 

    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 

    printf("Write Data : \n"); 
    scanf("%s", str);
    
    memcpy((void*)str, (void*)encodeRot13String(str), stringLength(str));

    printf("Data written in memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 
  
    return 0; 
} 