#ifndef STDIO_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
#endif
#ifndef TYPE_DATA
	 #define TYPE_DATA
	     	struct struttura_data{
	        int giorno;
	        int mese;
	        int anno;
	    	};
		typedef struct struttura_data date;
#endif   
#ifndef CONTROL_H
	#define CONTROL_H
		#include <time.h>
		#include <ctype.h>
		int data_control(date var);
		int choose_control(char control);
#endif
