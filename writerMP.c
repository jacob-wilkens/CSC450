// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include "rot13.h"
#define MAX 20
  
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[MAX];
} message;
  
int main()
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("progfile", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
    char* plaintext = malloc(sizeof(char) * MAX);

    printf("What do you want to write? : ");
    fgets(plaintext,MAX + 1,stdin);

    memcpy((void*)message.mesg_text, (void*)encodeRot13String(plaintext), stringLength(plaintext));
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    printf("Data send is : %s \n", message.mesg_text);

    return 0;
}