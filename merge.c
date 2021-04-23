#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
int numberOfBuckets = 10;
int randNums[10];
int childNum[];
int pids[10];
int length;

void childSortedHandler(int signum)
{

    printf("my array is sorted PID: %d\nContents of my memory are...\n", getpid());
    for (int i = 0; i < length; i++)
    {
        printf ("%d", childNum[i]);
    }
    
    sleep(1);
}
int main()
{
    for (int i = 0; i < 10; i++)
    {
        randNums[i] = (rand() % 300);
        printf("At bucket %d we have the random value %d \n", i, randNums[i]);
    }
    time_t t;
    srand((unsigned)time(&t));
    int length = numberOfBuckets / 2;

    for (int i = 0; i < 10; i++)
    {

        if (i % 2 == 0)
        {
            for (int k = 0; k < length; k++)
            {
                childNum[k] = randNums[k];
            }
        }
        else
        {
            int j = length;
            for (int l = length; l < length * 2; l++)
            {
                childNum[j] = randNums[l];
            }
        }

        sleep(.5);
        pid_t pid = fork();

        pids[i] = pid;
        if (pid < 0)
        {
            printf("Fork Failed\n");
            exit(1);
        }
        else if (pid == 0) //This is the child process
        {
            signal(SIGUSR2, childSortedHandler);
            pause();
            kill(pid, SIGUSR2);
        }
        else //This will be the adult
        {
            signal(SIGUSR2, childSortedHandler);
            //printf("%d \n", pid);
            kill(pid, SIGUSR2);
            //pause();
        }
        length = length / 2;
    }
}
