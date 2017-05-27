all:
	gcc -o liftMng liftMng.c `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g
	gcc -o liftCtrl liftCtrl.c `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g
	gcc -o liftBody liftBody.c `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g
	gcc -o liftSensor liftSensor.c `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g
	gcc opePanel1.c -o opePanel1 `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g -w
	gcc opePanel2.c -o opePanel2 `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g -w
	gcc opePanel3.c -o opePanel3 `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g -w
	gcc opePanel4.c -o opePanel4 `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g -w
	gcc opePanel5.c -o opePanel5 `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g -w
	gcc -o main main.c `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g -w	
	gcc -o main1 main1.c `pkg-config --libs gtk+-3.0` `pkg-config --cflags --libs gtk+-3.0` -g -w		
	ipcrm -M 5679	
	ipcrm -M 5678
