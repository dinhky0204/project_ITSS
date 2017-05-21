#include "lib.h"

int main()
{
    union sigval value;
    char *shm1, *p;
    int shmid1, id_mng;
    char id[10];
    int choose;
    long point, id_p1;
    char buff[1024];
    key_t key, key_p1;
    key_p1 = 5679;

    if ((shmid1 = shmget(key_p1, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
        }
    //Now we attach the segment to our data space.
    if ((shm1 = shmat(shmid1, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    strcpy(buff,shm1);
    p = strtok(buff,"|");
    p =strtok(p,"-");
    p =strtok(NULL,"-");
    point=(long)atof(p);

    printf("point: %ld\n", point);

    id_mng = (int)getpid();
    sprintf(id,"%d",id_mng);
    printf("%d\n",id_mng);
    strcat(shm1,"4-");
    strcat(shm1,id);
    strcat(shm1,"|");
    //sprintf(shm1,"1-%d|",id_p1);
    list_process[4].PID = id_p1;
    printf("list process : %ld\n",list_process[4].PID);
    printf("%s\n",shm1);
    while(1) {
        sleep(5);
        printf("Chon Tang: ");
        scanf("%d%*c", &choose);
        value.sival_int = choose;
        if(sigqueue(point, SIGTERM, value) == 0) {
                printf("signal sent successfully!!\n");
        }
    }

}

