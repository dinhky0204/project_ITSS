#include "lib.h"

int status;
int current_point = 1;

int main()
{
    float height = 1.5;
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    int bytes_read = 0;
    char buffer[BUFFER_SIZE + 1];
    int point_start;
    int point_end;
    int shmid;
    key_t key;
    char *shm;
    status = 0;
    key = 5678;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = (char*)shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }


    printf( "Process %d starting to read on pipe\n", getpid() );

    pipe_fd = open( FIFO_NAME, open_mode);



    sprintf(shm,"%f",height);
    if(status==0)
    {
    pipe_fd = open( FIFO_NAME, open_mode);
        if ( pipe_fd != -1 )
        {
            do
            {
                res = read( pipe_fd, buffer, BUFFER_SIZE );
                point_start = atoi(getStrByIndex(buffer,0,"-"));
                point_end = atoi(getStrByIndex(buffer,2,"-"));

                if(point_start==1)
                {
                    sprintf(shm, "%f", 1.5);
                    printf("Leep 3s xep do \n");
                    sleep(3);
                    printf("Xep do xong, bat dau di chuyen: \n");
                    for(int i = 2; i<=point_end; i++)
                    {
                        if(i==2) {
                            sleep(4);
                            height = 3.5;
                            sprintf(shm,"%f",height);
                            printf("Sleep 4s(1->2)\n");
                        }
                        else
                        {
                            sleep(6);
                            height = height + 3;
                            sprintf(shm,"%f",height);
                            printf("Sleep 6s(%d->%d)\n", i-1, i);
                        }
                    }

                    sleep(2);
                    height = height + 1;
                    sprintf(shm,"%f",height);
                    printf("Xep do o diem dich\n");
                    sleep(3);
                    //di chuyen xong tang 1
                    for(int i = (point_end-1); i>=1; i--) {
                        if(i==(point_end - 1)) {
                            sleep(4);
                            height = height - 2;
                            sprintf(shm,"%f",height);
                            printf("Sleep 4s(%d -> %d)\n", point_end, point_end-1);
                        }
                        else {
                            sleep(6);
                            height = height - 3;
                            sprintf(shm,"%f",height);
                            printf("Sleep 6s(%d->%d)\n", i+1, i);
                        }
                    }
                    sleep(2);
                    height = height - 1;
                    sprintf(shm,"%f",height);

                }
                else {

                    for(int i = 2; i<=point_start; i++)   //1 => point_start
                    {
                        if(i==2) {
                            sleep(4);
                            height = 3.5;
                            sprintf(shm,"%f",height);
                            printf("Sleep 4s(1->2)\n");
                        }
                        else
                        {
                            sleep(6);
                            height = height + 3;
                            sprintf(shm,"%f",height);
                            printf("Sleep 6s(%d->%d)\n", i-1, i);
                        }
                    }
                    sleep(2);
                    height = height + 1;
                    sprintf(shm,"%f",height);

                    printf("Sleep 3s bat dau xep do\n");
                    sleep(3);

                    if(point_start > point_end) {

                        for(int i = (point_start-1); i>=point_end; i--) {
                            if(i==(point_start - 1)) {
                                sleep(4);
                                height = height - 2;
                                sprintf(shm,"%f",height);
                                printf("Sleep 4s(%d -> %d)\n", i+1, i);
                            }
                            else {
                                sleep(6);
                                height = height - 3;
                                sprintf(shm,"%f",height);
                                printf("Sleep 6s(%d->%d)\n", i+1, i);
                            }
                        }
                        sleep(2);
                        height = height - 1;
                        sprintf(shm,"%f",height);
                        printf("Xep do o diem dich\n");
                        sleep(3);
                    }
                    else {
                        for(int i = (point_start+1); i<=point_end; i++)
                        {
                            if(i==(point_start+1)) {
                                sleep(4);
                                height = height + 2;
                                sprintf(shm,"%f",height);
                                printf("Sleep 4s(%d->%d)\n", point_start, point_start+1);
                            }
                            else
                            {
                                sleep(6);
                                height = height + 3;
                                sprintf(shm,"%f",height);
                                printf("Sleep 6s(%d->%d)\n", i-1, i);
                            }
                        }

                        sleep(2);
                        height = height + 1;
                        sprintf(shm,"%f",height);
                        printf("Xep do o diem dich\n");
                        sleep(3);
                    }

                    printf("Xep do o diem dich\n");
                    sleep(3);
                    for(int i = (point_end-1); i>=1; i--) {
                        if(i==(point_end - 1)) {
                            sleep(4);
                            height = height - 2;
                            sprintf(shm,"%f",height);
                            printf("Sleep 4s(%d -> %d)\n", point_end, point_end-1);
                        }
                        else {
                            sleep(6);
                            height = height - 3;
                            sprintf(shm,"%f",height);
                            printf("Sleep 6s(%d->%d)\n", i+1, i);
                        }
                    }
                    if(point_end!=1) {
                        sleep(2);
                        height = height - 1;
                        sprintf(shm,"%f",height);
                    }


                }
                //current_point = point_end;
                bytes_read += res;
            }
            while ( res > 0 );
            ( void ) close( pipe_fd );
            /*Kết thúc đọc*/
        }
        else
        {
            exit( EXIT_FAILURE );
        }
        printf( "Process %d finished, %d bytes read\n", getpid(), bytes_read );
        exit( EXIT_SUCCESS );
    }

}
