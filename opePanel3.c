#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include "lib.h"
GtkWidget *info;
GtkWidget *warn;
GtkWidget *que;
GtkWidget *err;

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
                                    "Called");
    gtk_window_set_title(GTK_WINDOW(dialog), "Information");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    buttoninfo.value.sival_int = 1;
    if(sigqueue(buttoninfo.point, SIGTERM, buttoninfo.value) == 0) {
        printf("signal sent successfully!!\n");
    }

}



void myCSS(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
	//printf ("Sending PID: %ld, UID: %ld\n", (long)siginfo->si_pid, (long)siginfo->si_value.sival_int);
    //return siginfo->si_value.sival_int;
    if(siginfo->si_value.sival_int==1) {
        printf("Den xanh\n");
        gdk_color_parse ("blue", &color);

        gtk_widget_modify_bg (sensor1, GTK_STATE_NORMAL, &color);
    }
    else {
        gdk_color_parse ("red", &color);

        gtk_widget_modify_bg (sensor1, GTK_STATE_NORMAL, &color);
    }

}

int main(int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *darea;
    GtkBuilder *builder;



    key_t key;
    key = 5679;
    int choose;
    int shmid;
    char id[10];
    char *shm, *p;
    long id_p1;
    char buff[1024];
    struct sigaction act;
    memset (&act, '\0', sizeof(act));
    act.sa_sigaction = &hdl;
    act.sa_flags = SA_SIGINFO;
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
    strcat(shm,"3-");
    strcat(shm,id);
    strcat(shm,"|");
    printf("list process : %s\n",shm);

    gtk_init(&argc, &argv);

    myCSS();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
    gtk_window_set_default_size(GTK_WINDOW(window), 150, 150);
    gtk_window_set_title(GTK_WINDOW(window), "Điều khiển tầng 3");

    darea = gtk_drawing_area_new();  //plus
    //gtk_container_add(GTK_CONTAINER(window), darea); //plus

    table = gtk_table_new(2, 2, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 4);
    gtk_table_set_col_spacings(GTK_TABLE(table), 2);

    info = gtk_button_new_with_label("　Call");
    sensor1 = gtk_button_new_with_label("sensor");

    gtk_widget_set_size_request(sensor1, 50, 50);
//    gtk_widget_set_name(abc, "myButton_blue");


    gdk_color_parse ("red", &color);

    gtk_widget_modify_bg (sensor1, GTK_STATE_NORMAL, &color);


    gtk_table_attach(GTK_TABLE(table), info, 0, 1, 0, 1,
                     GTK_FILL, GTK_FILL, 3, 3);

    gtk_table_attach(GTK_TABLE(table), sensor1, 0, 1, 1, 2,
                     GTK_FILL, GTK_FILL, 3, 3);

    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    g_signal_connect(G_OBJECT(info), "clicked",
                     G_CALLBACK(show_info1), (gpointer) window);



    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    //g_signal_connect(G_OBJECT(darea), "draw",
     // G_CALLBACK(on_draw_event), NULL);


    if (sigaction(SIGTERM, &act, NULL) < 0) {
		perror ("sigaction");
		return 1;
	}
    gtk_widget_show_all(window);

    gtk_main();


    return 0;
}
