#include "lib.h"

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
	//printf ("Sending PID: %ld, UID: %ld\n", (long)siginfo->si_pid, (long)siginfo->si_value.sival_int);
    //return siginfo->si_value.sival_int;
    action.PID = (long)siginfo->si_pid;
    action.point_end = siginfo->si_value.sival_int;
    printf("PID: %ld\tAction: %d\n",action.PID,action.point_end);
}

int main() {
    struct sigaction act;
    int pipe_fd, kc;
    int res;
    int open_mode = O_WRONLY;
    int bytes_sent = 0;
    char buffer[BUFFER_SIZE + 1], id[10], buff[20];
    int shmid, shmid1;
    key_t key, key_p1;
    char *shm, *shm1;
    long id_mng;

    memset (&act, '\0', sizeof(act));
    act.sa_sigaction = &hdl;
    act.sa_flags = SA_SIGINFO;
    key = 5678;

    key_p1 = 5679;
    action.PID = 0;
    action.point_end = 0;
    if (sigaction(SIGTERM, &act, NULL) < 0) {
		perror ("sigaction");
		return 1;
	}
    //Create the segment.

    if ((shmid1 = shmget(key_p1, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
        }
    //Now we attach the segment to our data space.
    if ((shm1 = shmat(shmid1, NULL, 0)) == (char *) -1) {
        printf("error\n");
    }
    else {
        printf("===> %ld\n", action.PID);
    }
    id_mng = (long)getpid();
    sprintf(id,"%ld",id_mng);
    printf("%ld\n",id_mng);
    strcat(shm1,"0-");
    strcat(shm1,id);
    strcat(shm1,"|");
    list_process[0].PID = id_mng;
    printf("list process: %ld\n", list_process[0].PID);
    /*Tạo pipe nếu chưa có*/

    if ( access( FIFO_NAME, F_OK ) == -1 )
    {
        res = mkfifo( FIFO_NAME, (S_IRUSR | S_IWUSR) );
        if ( res != 0 )
        {
            fprintf( stderr, "FIFO object not created [%s]\n", FIFO_NAME);
            exit( EXIT_FAILURE );
        }
    }
    printf( "Process %d starting to write on pipe\n", getpid() );
    //pipe_fd = open( FIFO_NAME, open_mode);

    //sprintf(shm1,"1-%d|",id_p1);
    pipe_fd = open( FIFO_NAME, open_mode);
    while (1)
    {
        if(action.PID!=0)
        {
            if ((shm1 = shmat(shmid1, NULL, 0)) == (char *) -1) {
                printf("error\n");
            }
            else
            {
                for(int i = 1; i<=5; i++) {
                    if(getStrByIndex(shm1,i,"|")!=NULL)
                    {
                        strcpy(buff,getStrByIndex(shm1,i,"|"));
                        if(action.PID == (long)atof(getStrByIndex(buff,1,"-")))
                        {
                            action.point_start = (int)atof(getStrByIndex(buff,0,"-"));
                        }
                    }
                    else
                        break;

                }
                printf("strtok: %s\n", buff);
            }

            printf("===>PID: %ld\tTang: %d\n", action.PID, action.point_end);
            for(int i = 1; i<=5; i++) {
                if(list_process[i].PID==action.PID)
                {
                    kc = i;
                }
            }
            sprintf(buffer,"%d-%ld-%d",action.point_start,action.PID,action.point_end);
           // strcpy(buffer,"abc");
            if(pipe_fd!=-1) {

                res = write( pipe_fd, buffer, BUFFER_SIZE );
                if ( res == -1 )
                {
                    fprintf( stderr, "Write error on pipe\n" );
                    exit( EXIT_FAILURE );
                }
                else printf("write ok\n");
            }

            bytes_sent += res;
            action.PID = 0;
        }

        sleep (1);
    }

}
