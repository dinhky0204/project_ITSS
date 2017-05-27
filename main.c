#include "lib.h"
void main(int argc, char const *argv[])
{
    pid_t pid;

    if((pid=fork()) !=0) {
		execl("./liftMng","./liftMng",NULL);
	}
	sleep(1);
	if((pid=fork())==0) {
		execl("./liftCtrl","./liftCtrl",NULL);
		return;
	}
	sleep(1);
	if((pid=fork())==0) {
		execl("./liftBody","./liftBody",NULL);
		return;
	}

	return;
}
