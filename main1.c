#include "lib.h"
void main(int argc, char const *argv[])
{
    pid_t pid;
    if((pid=fork())==0){
		execl("./opePanel1","./opePanel1",NULL);
		return;
	}
    sleep(1);
	if((pid=fork())==0) {
		execl("./opePanel2","./opePanel2",NULL);
		return;
	}
	sleep(1);

	if((pid=fork())==0) {
		execl("./opePanel3","./opePanel3",NULL);
		return;
	}
	sleep(1);
	if((pid=fork())==0) {
		execl("./opePanel4","./opePanel4",NULL);
		return;
	}
	sleep(1);
	if((pid=fork())==0) {
		execl("./opePanel5","./opePanel5",NULL);
		return;
	}
	sleep(1);
	if((pid=fork())==0) {
		execl("./liftSensor","./liftSensor",NULL);
		return;
	}
}
