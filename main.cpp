
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <spawn.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <wait.h>
#include <getopt.h>

using namespace std;

struct Process
{
    int DelayTime;
    char* ProcessName;
};
struct Process *m_Process;

void *Spawn(void *ptr);

void RunProcess(char* ProcessName)
{

    pid_t pid;
    char* argv[] = {(char *)"sh", (char *)"-c", ProcessName,NULL};
    int status;
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
    if (status == 0) {
        //printf(" Child id: %i \n", pid);
        fflush(NULL);
        if (waitpid(pid, &status, 0) != -1) {
            //printf(" Child exited with status %i\n", status);
        } else {
            perror("wait pid");
        }
    } else {
        printf("\n posix_spawn: %s", strerror(status));
    }
}
void *Spawn(void *ptr)
{
    long x_ptr = (long)ptr;
    char * ProcessName = m_Process[x_ptr].ProcessName;
    int DelayTime = m_Process[x_ptr].DelayTime;

    while(1)
    {
        RunProcess(ProcessName);
        usleep(DelayTime*1000);
    }
}


int main(int argc,char *argv[])
{
    int c;
    int size = 0;
    int Counter = 0;
    m_Process = (Process*)malloc(1*sizeof(Process));
    cout << "Starting Launcher" << endl;

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
                {"time",       1, 0, 't' },
                {"process",    1, 0, 'p' },
                {0,            0, 0,  0 }
        };

        c = getopt_long(argc, argv, "t:p:",
                        long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 'p':
                if (optarg) {
                    size++;
                    m_Process = (struct Process*)realloc(m_Process,(size)*sizeof(Process));

                    m_Process[Counter].ProcessName =(char*)malloc(strlen(optarg) + 1);
                    strcpy(m_Process[Counter].ProcessName,optarg);
                    //printf("\n Process Name : %s , c: %d", m_Process[Counter].ProcessName,Counter);

                    Counter++;
                }else{
                    printf("\n Please Enter Process Name to Run");
                    exit(EXIT_FAILURE);
                }

                break;

            case 't':
                if(size > 0) {
                    if (optarg) {
                        m_Process[Counter-1].DelayTime = atoi(optarg);
                        //printf("\n Delay Time : %d , c: %d", m_Process[Counter-1].DelayTime,Counter-1);
                    } else {
                        m_Process[Counter-1].DelayTime = 0;
                    }
                }
                break;
            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    pthread_t inc_x_thread;


    for (long i = 0; i < Counter; i++) {
        if(pthread_create(&inc_x_thread, NULL, &Spawn, (void *)i)) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    while (1) sleep(1);


}
