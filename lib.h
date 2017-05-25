#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gtk/gtk.h>
#include <math.h>
#define FIFO_NAME "my_fifo" /*Tạo đường ống*/
#define BUFFER_SIZE PIPE_BUF /*Vùng đệm dùng cho đường ống*/
#define TEN_MEG ( 1024 * 100 * 10 ) /*Dữ liệu*/
#define SHMSZ (1024*50)

GdkColor color;
GtkWidget *sensor1;
typedef struct Process {
    long PID;
}Process;
Process list_process[6];
typedef struct Actions {
    long PID;
    int point_start;
    int point_end;
}Action;
Action action;
Action list_action[50];
char* getStrByIndex(char *str, int index, char* split_char)
{
    char* str_cpy;
    char* result;
    int i = 0;
    str_cpy = (char*)malloc(sizeof(char)*(strlen(str)+1));
    strcpy(str_cpy, str);
    result = strtok(str_cpy, split_char);
    if(index == 0) return result;
    while((result = strtok(NULL, split_char))!= NULL){
        i++;
        if(i == index) return result;
    }
    return NULL;
}
