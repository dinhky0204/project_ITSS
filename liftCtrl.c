#include "lib.h"

int status;
int current_point = 1;

int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    int bytes_read = 0;
    char buffer[BUFFER_SIZE + 1];
    int point_start;
    int point_end;
    status = 0;

    printf( "Process %d starting to read on pipe\n", getpid() );
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

                printf("Current point(%d): %d  ->  %d\n",current_point, point_start, point_end);
                if(point_start==1)
                {
                    printf("Sleep: %d\n",abs(point_end-point_start)*6+3+3);
                    printf("from %d   to %d\n", current_point, point_end);
                    sleep(abs(point_end-point_start)*6+3+3);
                    printf("from %d   to   %d\n", point_end, 1);
                    sleep(abs(point_end-1)*6);
                }
                else {
                    printf("Sleep: %d\n",abs(point_start-1)*6);  // 1 => point_start
                    printf("from %d   to %d\n", 1,point_start);
                    sleep((point_start-1)*6);

                    printf("Sleep: %d\n",abs(point_end-point_start)*6);
                    printf("from %d   to %d\n", point_start,point_end);
                    sleep(abs(point_end-point_start)*6 +3 +3 );

                    printf("from %d   to   %d\n", point_end, 1);
                    sleep(abs(point_end-1)*6);

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
