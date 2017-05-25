#include "lib.h"
void sensor(float height) {
    if(height>0 && height<=3)
    printf("Sensor1: ON");
    if(height>3 && height<=6)
    printf("Sensor2: ON");
    if(height>6 && height<=9)
    printf("Sensor3: ON");
    if(height>9 && height<=12)
    printf("Sensor4: ON");
    if(height>12 && height<=15)
    printf("Sensor5: ON");
}
int main() {
    int shmid, shmid1;
    key_t key, key1;
    char *shm, *s, *shm1;
    long pid;
    float height = 0;
    union sigval value;
    char tmp[100], process_id[20];
    int key_id = 0;

    GtkBuilder *builder;
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "diaglog.c", NULL);


    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 5678;
    key1 = 5679;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
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


    if ((shmid1 = shmget(key1, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
        }
    //Now we attach the segment to our data space.
    if ((shm1 = shmat(shmid1, NULL, 0)) == (char *) -1) {
        printf("error\n");
    }
    strcpy(tmp, shm1);
    for(int i = 1; i <= 5; i++) {
        if(getStrByIndex(tmp, i, "|")!=NULL)
        {
            strcpy(process_id, getStrByIndex(tmp, i, "|"));
            key_id = atoi(getStrByIndex(process_id, 0, "-"));
            switch(key_id) {
                case 1:
                    list_process[1].PID = (long)atof(getStrByIndex(process_id, 1, "-"));
                break;
                case 2:
                    list_process[2].PID = (long)atof(getStrByIndex(process_id, 1, "-"));
                break;
                case 3:
                    list_process[3].PID = (long)atof(getStrByIndex(process_id, 1, "-"));
                break;
                case 4:
                    list_process[4].PID = (long)atof(getStrByIndex(process_id, 1, "-"));
                break;

                case 5:
                    list_process[5].PID = (long)atof(getStrByIndex(process_id, 1, "-"));
                break;
                default:
                break;
            }
            list_process[i].PID = (long)atof(getStrByIndex(process_id, 1, "-"));
        }
        else break;

    }


    while(1) {
        height = atof(shm);
        if(height>0 && height<=3)
        {
            printf("Sensor1: ON\n");
            value.sival_int = 1;
            pid = list_process[1].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            value.sival_int = 0;
            pid = list_process[2].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            pid = list_process[3].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            pid = list_process[4].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            pid = list_process[5].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

        }

        if(height>3 && height<=6)
        {
            value.sival_int = 1;
            pid = list_process[2].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            value.sival_int = 0;
            pid = list_process[1].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            pid = list_process[3].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
            pid = list_process[4].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
            pid = list_process[5].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

        }

        if(height>6 && height<=9)
        {
            printf("Sensor3: ON\n");
            value.sival_int = 1;
            pid = list_process[3].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            value.sival_int = 0;
            pid = list_process[1].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            pid = list_process[2].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
            pid = list_process[4].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
            pid = list_process[5].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
        }

        if(height>9 && height<=12)
        {
            printf("Sensor4: ON\n");
            value.sival_int = 1;
            pid = list_process[4].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            value.sival_int = 0;
            pid = list_process[1].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            pid = list_process[2].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
            pid = list_process[3].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
            pid = list_process[5].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
        }

        if(height>12 && height<=15)
        {
            printf("Sensor5: ON\n");
            value.sival_int = 1;
            pid = list_process[5].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            value.sival_int = 0;
            pid = list_process[1].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }

            pid = list_process[2].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
            pid = list_process[3].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
            pid = list_process[4].PID;
            if(sigqueue(pid, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
            }
        }

        sleep(2);
    }


    shmdt((void *)shm);
    exit(0);
}
