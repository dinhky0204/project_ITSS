#include "lib.h"
int main()
{
    union sigval value;
    key_t key;
    key = 5679;
    int choose;
    int shmid;
    char id[10];
    char *shm, *p;
    long point, id_p1;
    char buff[1024];
    //Tạo một shared memory voi key = 5679 để lưu các id của tiến trình opepanel1 -> opepanel5 va liftMng
    //Create the segment.
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    //Now we attach the segment to our data space.
    if ((shm = (char*)shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    strcpy(buff,shm);
    p = strtok(buff,"|");
    p =strtok(p,"-");
    p =strtok(NULL,"-");
    point=(long)atof(p);

    printf("point: %ld\n", point);

    id_p1 = (int)getpid();

    sprintf(id,"%ld",id_p1);
    printf("%ld\n",id_p1);
    //strcat(shm,id);
    strcat(shm,"1-");
    strcat(shm,id);
    strcat(shm,"|");
    //sprintf(shm,"1-%d|",id_p1);
    list_process[1].PID = id_p1;
    printf("list process : %ld\n",list_process[1].PID);
    while(1) {
        sleep(5);
        printf("Chon Tang: ");
        scanf("%d%*c", &choose);
        value.sival_int = choose;
        if(sigqueue(point, SIGTERM, value) == 0) {
            printf("signal sent successfully!!\n");
        }
    }


    return 0;
}
