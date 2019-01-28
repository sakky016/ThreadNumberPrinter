#include <bits/stdc++.h>

using namespace std;

/* This defines the interval in which a thread
   will print numbers */
#define INTERVAL_MAX 8
#define THREADS INTERVAL_MAX

/* Start printing with 1 */
int g_printer = 1;

typedef struct param_tag
{
    int interval;
    int tmp;
}param_t;

void* NumberPrinter(void *p)
{
    int i = 0;
    param_t *param = (param_t *)(p);
    i = param->interval;
    printf("Thread started, interval: %d\n", i);
    while (i < INT_MAX)
    {
        /* Wait till we get signal from other 
        thread that we can now print ODD numbers */
        while (g_printer != param->interval);

        cout<<"Thread #"<<param->interval<<": "<<i<<endl;
        sleep (1);
        i += INTERVAL_MAX;
        g_printer = param->interval + 1;
        if (g_printer == INTERVAL_MAX + 1)
        {
            g_printer = 1;
        }
    }
}

/**************************** M A I N ***********************************/
int main()
{
    int retval = 0;
    pthread_t th[THREADS];
    int i = 1;
    param_t param[THREADS];

    /* Spawn threads */
    while (i <= THREADS)
    {
        param[i-1].interval = i;
        printf("Creating thread with interval %d\n", param[i-1].interval);

        retval = pthread_create(&th[i-1], NULL, &NumberPrinter, (void*)&param[i-1]);
        if (retval != 0)
        {
            printf("ERROR: Thread could not be created\n");
        }

        i++;
    }

    /* Wait for threads to complete */
    i = 0;
    printf("Waiting for threads to complete their job...\n");
    while (i < THREADS)
    {
        pthread_join(th[i], NULL);
        i++;
    }

    return 0;
}
