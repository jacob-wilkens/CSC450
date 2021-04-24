#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>

int numberOfBuckets = 10;
int randNums[10];
int *l, *ll, *lr, *rl, *r, *rr;
int pids[10];
int length;

void childSortedHandler(int signum)
{
    printf("my PID: %d\nContents of my memory are...\n", getpid());

    for (int i = 0; i < 10; i++)
    {
        printf("%d,", ll[i]);
    }
    sleep(1);
}
int main()
{
    for (int i = 0; i < 10; i++)
    {
        randNums[i] = (rand() % 300);
        printf("%d,", randNums[i]);
    }

    time_t t;
    srand((unsigned)time(&t));

    int length = numberOfBuckets / 2;
    int sortingLeft = 1;
    int sortingRight = 1;

    int processcounter = 0;

    int leftLength = length;
    int rightLength = length;

    l = malloc(length * sizeof(int));
    memcpy(l, randNums, length * sizeof(int));

    r = malloc(length * sizeof(int));
    memcpy((int *)r, (int *)&randNums[length], length * sizeof(int));

    while (sortingLeft == 1 && sortingRight == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (leftLength == 0)
            {
                sortingLeft = 0;
                break;
            }

            ll = malloc(leftLength * sizeof(int));
            memcpy(ll, l, leftLength * sizeof(int));

            printf("\n left = ");

            for (int i = 0; i < leftLength; i++)
            {
                printf("%d,", ll[i]);
            }

            // pid_t pid = fork();
            // sleep(1);

            // if (pid < 0)
            // {
            //     printf("Fork Failed\n");
            //     exit(1);
            // }
            // else if (pid == 0) //This is the child process
            // {
            //     signal(SIGUSR2, childSortedHandler);
            //     pause();
            // }

            //kill(pids[processcounter], SIGUSR2);

            // pids[processcounter] = pid;
            // processcounter++;

            if (i == 0)
            {
                leftLength = leftLength / 2;
                continue;
            }

            lr = malloc(leftLength * sizeof(int));
            memcpy((int *)lr, (int *)&l[leftLength], leftLength * sizeof(int));

            printf("\n right = ");

            for (int i = 0; i < leftLength; i++)
            {
                printf("%d,", lr[i]);
            }

            leftLength = leftLength / 2;
        }

        for (int i = 0; i < 10; i++)
        {

            if (rightLength == 0)
            {
                sortingRight = 0;
                break;
            }

            rl = malloc(rightLength * sizeof(int));
            memcpy(rl, r, rightLength * sizeof(int));

            printf("\n left = ");

            for (int i = 0; i < rightLength; i++)
            {
                printf("%d,", rl[i]);
            }

            if (i == 0)
            {
                rightLength = rightLength / 2;
                continue;
            }

            rr = malloc(rightLength * sizeof(int));
            memcpy((int *)rr, (int *)&r[rightLength], rightLength * sizeof(int));

            printf("\n right = ");

            for (int i = 0; i < rightLength; i++)
            {
                printf("%d,", rr[i]);
            }

            rightLength = rightLength / 2;
        }
    }
}
