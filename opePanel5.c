#include <gtk/gtk.h>
#include "lib.h"
typedef struct {
    long point;
    union sigval value;
}ButtonInfo;
ButtonInfo buttoninfo;


int choose = 0;
void show_info1(GtkWidget *widget, gpointer window)
{
    //buttonInfo *buttoninfo = (buttonInfo *)data;
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Bạn đã chọn 1");
    gtk_window_set_title(GTK_WINDOW(dialog), "Information");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    buttoninfo.value.sival_int = 1;
    if(sigqueue(buttoninfo.point, SIGTERM, buttoninfo.value) == 0) {
        printf("signal sent successfully!!\n");
    }

}

void show_info2(GtkWidget *widget, gpointer window)
{

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Bạn đã chọn 2");
    gtk_window_set_title(GTK_WINDOW(dialog), "Information");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
     buttoninfo.value.sival_int = 2;
    if(sigqueue(buttoninfo.point, SIGTERM, buttoninfo.value) == 0) {
        printf("signal sent successfully!!\n");
    }
}

void show_info3(GtkWidget *widget, gpointer window)
{

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Bạn đã chọn 3");
    gtk_window_set_title(GTK_WINDOW(dialog), "Information");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    buttoninfo.value.sival_int = 3;
    if(sigqueue(buttoninfo.point, SIGTERM, buttoninfo.value) == 0) {
        printf("signal sent successfully!!\n");
    }
}

void show_info4(GtkWidget *widget, gpointer window)
{

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Bạn đã chọn 4");
    gtk_window_set_title(GTK_WINDOW(dialog), "Information");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    buttoninfo.value.sival_int = 4;
    if(sigqueue(buttoninfo.point, SIGTERM, buttoninfo.value) == 0) {
        printf("signal sent successfully!!\n");
    }
}

int main(int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *table;

    GtkWidget *info;
    GtkWidget *warn;
    GtkWidget *que;
    GtkWidget *err;

    key_t key;
    key = 5679;
    int choose;
    int shmid;
    char id[10];
    char *shm, *p;
    long id_p1;
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
    buttoninfo.point=(long)atof(p);

    printf("point: %ld\n", buttoninfo.point);

    id_p1 = (int)getpid();

    sprintf(id,"%ld",id_p1);
    printf("%ld\n",id_p1);
    //strcat(shm,id);
    strcat(shm,"5-");
    strcat(shm,id);
    strcat(shm,"|");
    //sprintf(shm,"1-%d|",id_p1);
    list_process[1].PID = id_p1;
    printf("list process : %ld\n",list_process[1].PID);

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 150);
    gtk_window_set_title(GTK_WINDOW(window), "Điều khiển tầng 5");

    table = gtk_table_new(2, 2, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 4);
    gtk_table_set_col_spacings(GTK_TABLE(table), 2);

    info = gtk_button_new_with_label("　Tầng 3");
    warn = gtk_button_new_with_label("Tầng 4");
    que = gtk_button_new_with_label("Tầng 1");
    err = gtk_button_new_with_label("Tầng 2");

    gtk_table_attach(GTK_TABLE(table), info, 0, 1, 0, 1,
                     GTK_FILL, GTK_FILL, 3, 3);
    gtk_table_attach(GTK_TABLE(table), warn, 1, 2, 0, 1,
                     GTK_FILL, GTK_FILL, 3, 3);
    gtk_table_attach(GTK_TABLE(table), que, 0, 1, 1, 2,
                     GTK_FILL, GTK_FILL, 3, 3);
    gtk_table_attach(GTK_TABLE(table), err, 1, 2, 1, 2,
                     GTK_FILL, GTK_FILL, 3, 3);


    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_container_set_border_width(GTK_CONTAINER(window), 40);

    g_signal_connect(G_OBJECT(info), "clicked",
                     G_CALLBACK(show_info3), (gpointer) window);

    g_signal_connect(G_OBJECT(warn), "clicked",
                     G_CALLBACK(show_info4), (gpointer) window);

    g_signal_connect(G_OBJECT(que), "clicked",
                     G_CALLBACK(show_info1), (gpointer) window);

    g_signal_connect(G_OBJECT(err), "clicked",
                     G_CALLBACK(show_info2), (gpointer) window);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), G_OBJECT(window));


    gtk_widget_show_all(window);

    gtk_main();


    return 0;
}
