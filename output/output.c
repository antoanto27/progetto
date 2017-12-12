#include "output.h"
extern login logged_in;
int visualizza_utenti(){
	
	int return_value=0;
	login dati_accesso={"","",0};
	char tipo[LEN_TIPO];
	
	FILE *ptr_login;
	if((ptr_login=fopen("dati_login.dat","rb"))==NULL){
		return_value=1;
	}

	printf("\n%-30s%-30s%-30s\n","Nome Utente","Password","Tipo Account");


	while((fread(&dati_accesso, sizeof(login),1,ptr_login))>0){

		switch(dati_accesso.codice){
			case 1: strcpy(tipo,"Organizzatore");
					break;
			case 2: strcpy(tipo,"Capitano");
					break;

			case 5:strcpy(tipo,"Amministratore(First)");
					break;
			case 4: strcpy(tipo,"Amministratore");
					break;
		}

		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205);

		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);

		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%",205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

		printf("\n%c%-30s%-29s%-30s%c\n",186,dati_accesso.nome_utente,dati_accesso.password,tipo,186);

		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205);

		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);

		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
	}

	fclose(ptr_login);
	system("PAUSE");
	return return_value;
}

int visualizza_tornei(short int code){

	FILE *ptr_torneo;
	torneo var_torneo;
	char tipo[LEN_TIPO];
	int return_value;

	if((ptr_torneo=fopen("lista_tornei.dat","rb"))==NULL){
		printf("Non ci sono tornei registrati\n");
		system("PAUSE");
		return_value=0;
	}
	
	else if(fread(&var_torneo,sizeof(torneo),1,ptr_torneo)<=0){
		printf("Non ci sono tornei registrati\n");
		return_value=0;
		system("PAUSE");
	}
	
	

	else{
		rewind(ptr_torneo);
		if(code==3){
			printf("%-30s%-30s\n\n","Nome Torneo","Proprietario");
			while((fread(&var_torneo, sizeof(torneo),1,ptr_torneo))>0){
				if(var_torneo.codice==0||var_torneo.codice==2){
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);	
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
					printf("%c%-31s%-30s%c\n",186,var_torneo.nome_torneo,var_torneo.nome_proprietario,186);
				  	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);	
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
				}
			}
		}
		
		if(code==2){
			printf("%-30s%-30s\n\n","Nome Torneo","Proprietario");
			while((fread(&var_torneo, sizeof(torneo),1,ptr_torneo))>0){
				if(var_torneo.codice==1){
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);	
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
					printf("%c%-31s%-30s%c\n",186,var_torneo.nome_torneo,var_torneo.nome_proprietario,186);
				  	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);	
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
				}
			}
		}
		
		else if(code==1){
			
			printf("%-30s%-30s%-30s\n","Nome Torneo", "Stato", "Proprietario");
			
			while((fread(&var_torneo, sizeof(torneo),1,ptr_torneo))>0){
				
				switch(var_torneo.codice){

				case 1: strcpy(tipo,"Iscrizioni Aperte"); 
						break;
				case 0: strcpy(tipo,"Iscrizioni Chiuse"); 
						break;
				case 2: strcpy(tipo,"Torneo Concluso"); 
						break;
						
				}

			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205);
				
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
				
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%",205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
				
			printf("\n%c%-30s%-29s%-30s%c\n",186,var_torneo.nome_torneo,tipo,var_torneo.nome_proprietario,186);
				
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205);
				
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
				
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
			}
		}
		
	fclose(ptr_torneo);
	system("PAUSE");
	return_value=1;
	
	}
	fclose(ptr_torneo);
	return return_value;

}
	
int stampa_calendario(char name_file[LEN_CALENDARIO_NAME],char nome_torneo[LEN_TORNEO_NAME]){

	FILE *ptr_calendario;
	FILE *ptr_torneo;
	FILE *ptr_lista;
	
	int return_value;
	file_squadre *nomi_squadre;
	iscrizioni *n_teams;
	torneo control;
	int i=0;
	int n=0;
	int flag=1;
	
	n_teams=(iscrizioni *) calloc(1,sizeof(iscrizioni)); //allocazione array delle squadre
	
	if((ptr_torneo=(fopen(nome_torneo,"rb")))!=NULL){
		ptr_lista=fopen("lista_tornei.dat","rb");
		while((fread(&control,sizeof(torneo),1,ptr_lista))>0){
			if((strcmp(control.nome_torneo,nome_torneo))==0){
				if(control.codice==1){
					flag=0;
					printf("Impossibile visualizzare il torneo: le iscrizioni sono ancora aperte\n");
					return_value=1;
				}
			}
		}
		
		if(flag!=0){
			ptr_calendario=(fopen(name_file,"rb"));
			
			
			while((fread(n_teams[n].nome_squadra,sizeof(iscrizioni),1,ptr_torneo))>0){
					n++;
					n_teams=(iscrizioni *) realloc(n_teams,(n+1)*sizeof(iscrizioni));
		       	 }
			free(n_teams);
		       	 
			if(n%2==0){
				
				file_squadre nomi_squadre[(n-1)*(n/2)];
				
				while(!feof(ptr_calendario)){
				fread(&nomi_squadre[i],sizeof(file_squadre),1,ptr_calendario);
				i++;
				}
				
				for(i=0;i<((n-1)*(n/2));i++){
					
		            if(i%(n/2)==0){
		            	printf("\n%2d/%-2d/%-2d ",nomi_squadre[i].giornata.giorno,nomi_squadre[i].giornata.mese,nomi_squadre[i].giornata.anno);
					}
				
					printf("%s %2d - %-2d %-30s ",nomi_squadre[i].casa,nomi_squadre[i].gc,nomi_squadre[i].gt,nomi_squadre[i].trasferta);
				}
			}
			
			else{
				
				file_squadre nomi_squadre[(n)*((n+1)/2)];
				while(!feof(ptr_calendario)){
				fread(&nomi_squadre[i],sizeof(file_squadre),1,ptr_calendario);
				i++;
				}
				
				for(i=0;i<((n)*((n+1)/2));i++){
				    	
					if(i%((n+1)/2)==0){
						printf("\n");
						printf("\n%2d/%-2d/%-2d ",nomi_squadre[i].giornata.giorno,nomi_squadre[i].giornata.mese,nomi_squadre[i].giornata.anno);
					}
						
					if((strcmp(nomi_squadre[i].casa,"RIPOSA")==0)){
						printf("%8s %-8s  ",nomi_squadre[i].casa, nomi_squadre[i].trasferta);
					}
						
					else{
						printf("%8s %2d - %-2d %-8s  ",nomi_squadre[i].casa,nomi_squadre[i].gc,nomi_squadre[i].gt,nomi_squadre[i].trasferta);
					}
				}
			}
			
			fclose(ptr_calendario);	
			return_value=0;
		}
		fclose(ptr_lista);
		fclose(ptr_torneo);
	}
	else{
		fclose(ptr_torneo);
		printf("Non esiste un torneo con questo nome!\n");
		return_value=1;
	}
	
	printf("\n");
	system("PAUSE");
	return return_value;
}



int stampa_classifica(char nome_classifica[LEN_CLASSIFICA_NAME]){
	
	int return_value;
	classifica score={"",0,0,0,0};
	FILE *ptr_classifica;

	if((ptr_classifica=fopen(nome_classifica,"rb"))==NULL){
        printf("File non trovato");
        printf("\n");
        return_value=1;
    }

    else{

     	printf("\n%-30s%-7s%-14s%-11s%12s\n", "Nome Squadra", "Punti", "Goal Fatti", "Goal Subiti", "Diff. Reti");

    	while((fread(&score,sizeof(classifica),1,ptr_classifica))>0){
    		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,203);
    		printf("%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,203);
			printf("%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,203);
    		printf("%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,203);
    		printf("%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,187);
    		printf("%c%-30s%c%-6d%c%-14d%c%-11d%c%-10d%c\n",186,score.squadra,186,score.punti,186,score.gf,186,score.gs,186,score.dr,186);
    		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,202);
	    	printf("%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,202);
			printf("%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,202);
    		printf("%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,202);
    		printf("%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,188);
		}
		return_value=0;
	}

	fclose(ptr_classifica);
	system("PAUSE");
	return return_value;
}

int stampa_squadre(char nome_torneo[LEN_TORNEO_NAME]){
	
	iscrizioni squadre_iscritte={""};
	FILE *ptr_torneo;
	int return_value;
	
	if((ptr_torneo =fopen(nome_torneo,"rb"))!=NULL){
		if(fread(&squadre_iscritte,sizeof(iscrizioni),1,ptr_torneo)<=0){
			printf("Nessuna squadra iscritta a queto torneo!\n");
			return_value=1;
			system("PAUSE");
		}
		else{
			rewind(ptr_torneo);
			printf("Squadre iscritte a questo torneo:\n");

		while(fread(&squadre_iscritte,sizeof(iscrizioni),1,ptr_torneo)>0){
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);	
			printf("%c%-30s%c\n",186,squadre_iscritte.nome_squadra,186);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
		}
		system("PAUSE");
		return_value=0;
	}
	}
    else{
    	printf("Nome del torneo errato o inesistente!\n");
    	system("PAUSE");
    	return_value=1;
	}
	fclose(ptr_torneo);
	return return_value;
}
void utente_loggato(){
	
	char tipo[LEN_TIPO];
	
	switch(logged_in.codice){
			case 1: strcpy(tipo,"Organizzatore"); 
					break;
			case 2: strcpy(tipo,"Capitano"); 
					break;
					
			case 5:
			case 4: strcpy(tipo,"Amministratore");
					break;
		}
		
	printf("Benvenuto %s! In qualita' di %s queste sono le operazioni che puoi effettuare:\n\n", logged_in.nome_utente,tipo);
}
