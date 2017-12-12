#include "control.h"

int data_control(date var){
	
	short int flag=1;
	int mesi[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int flagdate;
	//Variabili per il tempo locale
	time_t rawtime;
    time (&rawtime);
    struct tm* locale;

    locale = localtime(&rawtime);
    
	if((var.anno-1900)>=locale->tm_year){
		if((var.anno-1900)==locale->tm_year){
			if(var.mese>=(locale->tm_mon)+1){
				if(var.mese==(locale->tm_mon)+1){
					if(var.giorno==locale->tm_mday){
						flagdate=1;
					}
					else if(var.giorno>locale->tm_mday){
						flagdate=1;
					}
					else{
						flagdate=0;
					}
				}
				else if(var.mese>(locale->tm_mon)+1){
					flagdate=1;
				}
			}
			else{
				flagdate=0;
			}
		}
		else if((var.anno-1900)>locale->tm_year){
			flagdate=1;
		}
	
	}
	else{
		flagdate=0;
	}
	
	if(var.anno>0&&flagdate==1){
		if(var.mese>0&&var.mese<13){
			if(var.giorno>0&&var.giorno<=mesi[var.mese-1]){
				flag=0;
			}
		}
	}
	
	if(flag==1){
		printf("Data errata! Reinserire\n");
	}
	
	return flag;
}
	
int choose_control(char control){
		
	int choose;
		
	if((isdigit(control))!=0){
		choose=(int)control-48;
	}
	
	else{
		printf("\n!!!Scelta non valida! Reinserire!!!\n");
		}
		
	return choose;
	
}
