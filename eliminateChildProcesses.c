#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "random.c"

int hp;
pid_t children[];

void sig_handler_parent(int signum)
{
  for (int i = 0; i < hp; i++)
  {
    printf("Killing child process with id of  %d\n", children[i]);
    kill(children[i], SIGKILL); //sends kill command to child
  }
  
}

int main()
{
  pid_t pid = getpid();
  hp = random_number(5, 6);
  children[hp];

  if (pid != 0)
  {
    printf("Parent: I have %d children. %d\n", hp, getpid());
  }

  for (int i = 0; i < hp; i++)
  {
    if (pid == 0)
    {
      break; // if child do not proceed forking
    }
    else
    {
      if ((pid = fork()) < 0) //forks
      {
        printf("Fork Failed\n");
        exit(1);
      }
      children[i] = pid; // adds to child list
      sleep(1); // wait 1 second
    }
  }

  /* Child Process */
  if (pid == 0)
  {
    printf("Child: I am waiting %d\n", getpid());
    pause(); //Keeps child alive
  }
  //* Parent Process */
  else
  {
    signal(SIGINT, sig_handler_parent); //register kill signal
    sleep(1);
    printf("waiting to get kill command\n");
    pause(); //wait for signal
  }

  return 0;
}
