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
    int shmid;
    key_t key;
    char *shm, *s;
    float height = 0;

    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 5678;

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

    while(1) {
        height = atof(shm);
        if(height>0 && height<=3)
        printf("Sensor1: ON\n");
        if(height>3 && height<=6)
        printf("Sensor2: ON\n");
        if(height>6 && height<=9)
        printf("Sensor3: ON\n");
        if(height>9 && height<=12)
        printf("Sensor4: ON\n");
        if(height>12 && height<=15)
        printf("Sensor5: ON\n");
        sleep(2);
    }


    shmdt((void *)shm);
    exit(0);
}
