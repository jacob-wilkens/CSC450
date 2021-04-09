#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int random_number(int min_num, int max_num)
{
  int result = 0, low_num = 0, hi_num = 0;

  if (min_num < max_num)
  {
    low_num = min_num;
    hi_num = max_num + 1; // include max_num in output
  }
  else
  {
    low_num = max_num + 1; // include max_num in output
    hi_num = min_num;
  }

  srand(time(NULL));
  result = (rand() % (hi_num - low_num)) + low_num;
  return result;
}

void sig_handler_parent(int signum)
{
  printf("Parent: Ouch \n");
}

void sig_handler_child(int signum)
{
  sleep(1);
  kill(getppid(), SIGUSR1);
}

int main()
{

  pid_t pid = getpid();
  int hp = random_number(5, 20);

  if (pid != 0)
  {
    printf("Parent: I have %d hitpoints. \n", hp);
  }

  for (int i = 0; i < hp; i++)
  {
    if (pid == 0)
    {
      break;
    }
    else
    {
      if ((pid = fork()) < 0)
      {
        printf("Fork Failed\n");
        exit(1);
      }
    }
  }

  /* Child Process */
  if (pid == 0)
  {
    signal(SIGUSR1, sig_handler_child); // Register signal handler
    printf("Child: I am waiting for my brothers....\n");
    pause();
  }
  //* Parent Process */
  else
  {
    sleep(.5);

    signal(SIGUSR1, sig_handler_parent); // Register signal handler
    for (int i = 0; i < hp * 2; i++)
    {
      if (i == 0)
      {
        printf("Child: Attack!!!!!!!\n");
      }
      kill(pid, SIGUSR1);
      sleep(1);
    }
    printf("Parent: You have slain me!\n");
  }

  return 0;
}
