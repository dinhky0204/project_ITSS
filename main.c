#include "lib.h"
void main(int argc, char const *argv[])
{
    pid_t pid;

    if((pid=fork()) !=0) {
		execl("./liftMng","./liftMng",NULL);
	}
	if((pid=fork())==0) {
		execl("./liftCtrl","./liftCtrl",NULL);
		return;
	}
	if((pid=fork())==0) {
		execl("./liftBody","./liftBody",NULL);
		return;
	}

	return;
}
