#include "delete.h"
#include <unistd.h>


extern sw_data sensible_data;
extern FILE *ptr_system;

int elimina_utente(){
	
	int return_value;
	login temp={"","",0};
	int i=0;
	int j=0;
	int z=0;//i,j,z contatori
	int flag=0;
	int flag2=0;
	char nome_utente[LEN_USER];
	int posizione;
	login *p;
	FILE *ptr_login;
	FILE *ptr_system;

	visualizza_utenti();
	printf("Inserisci il nome dell'utente da eliminare: ");
	scanf("%s", nome_utente);

	printf("\nStai per eliminare l'utente %s. Continuare? S/N  \n", nome_utente);

	if(getch()=='s'||getch()=='S'){

		ptr_login=fopen("dati_login.dat","rb");

		p = (login *) calloc (sensible_data.utenti_registrati, sizeof(login));

		while((fread(&temp, sizeof(login),1,ptr_login))>0) {
			p[z]=temp;
			z++;
		}

		for (i=0;i<sensible_data.utenti_registrati;i++) {
			if(((strcmp(nome_utente,p[i].nome_utente)==0))){
				if(p[i].codice==5){
					printf("Impossibile eliminare questo utente!\n");
					flag=1;
					flag2=1;
					return_value=1;
				}
			}
		}

		fclose(ptr_login);

		while(flag2!=1){
			for (i=0;i<sensible_data.utenti_registrati;i++) {
				
				if(((strcmp(nome_utente,p[i].nome_utente)==0))){
		
					ptr_login=fopen("dati_login.dat","wb");
					posizione=i;

					for(i=0;i<sensible_data.utenti_registrati; i++){

						if(i==posizione);
						else{
							temp=p[i];
							fwrite(&temp,sizeof(login),1,ptr_login);
							j++;
						}
					}
					sensible_data.utenti_registrati--;

				if((ptr_system=fopen("system_data.dat","wb"))==NULL){
					printf("File system non trovato\n");
					return_value=0;
				}
				else{
					fwrite(&sensible_data,sizeof(sw_data),1,ptr_system);
					fclose(ptr_system);	
					printf("Utente eliminato con successo!\n");
					return_value=1;
					flag=1;
				}
				break;
				}
			}
			flag2=1;
		}

		if(flag==0){
			printf("Utente non trovato!\n");
			return_value=0;
		}

		free(p);
		fclose(ptr_login);
	}
	system("PAUSE");
	return return_value;
}

int elimina_torneo(){
	
	int return_value;
	char nome_torneo[LEN_TORNEO_NAME];
	int z=0;
	int i;
	int j;
	int posizione;
	short int stato;
	FILE *ptr_lista;
	torneo *p;
	torneo temp;
	int flag=1;

	printf("Elenco dei tornei disponibili:\n");
	
    flag=visualizza_tornei(1);
    
    if(flag==1){
    	
		ptr_lista=fopen("lista_tornei.dat","rb");
		p = (torneo *) calloc (sensible_data.n_tornei, sizeof(torneo)); //allocazione puntatore ad array temporaneo

		while((fread(&temp, sizeof(torneo),1,ptr_lista))>0){
			p[z]=temp;
			z++;
		}

		fclose(ptr_lista);
		

		do{
			
			printf("Inserisci nome torneo da eliminare: ");
			scanf("%s", nome_torneo);
			
			printf("\nStai per eliminare il torneo %s. Continuare? S/N  \n", nome_torneo);
	
			if(getch()=='s'||getch()=='S'){
				
				ptr_lista=fopen("lista_tornei.dat","wb");
				
				for (i=0;i<sensible_data.n_tornei;i++){
					if(((strcmp (nome_torneo,p[i].nome_torneo)==0))){ //ricerca del nome torneo da eliminare
	
						posizione=i;
		
						for(i=0;i<sensible_data.n_tornei; i++){
		
							if(i==posizione);
							
							else {
								temp=p[i];
								fwrite(&temp,sizeof(torneo),1,ptr_lista);
								j++;
							}
						}
						stato=1;
						return_value=0;
						break;
					}
				}
			
				if(stato!=1){
					printf("Torneo non trovato! Ridigita\n");
				}
				fclose(ptr_lista);
			}
			else{
				stato=0;
				return_value=1;
			}
		}while(stato!=1);

		free(p);
		if(stato==1){
		
			sensible_data.n_tornei--;
			ptr_system=fopen("system_data.dat","wb");
			fwrite(&sensible_data,sizeof(sw_data),1,ptr_system);
			fclose(ptr_system);
			
			char nome_classifica[LEN_CLASSIFICA_NAME];
			char nome_calendario[LEN_CALENDARIO_NAME];
			
			strcpy(nome_classifica,nome_torneo);
			strcpy(nome_calendario,nome_torneo);
			strcat(nome_classifica,"_classifica");
			strcat(nome_calendario,"_calendario");
			
			_fcloseall();

			remove(nome_torneo);
			remove(nome_classifica);
			remove(nome_calendario);
			
			ptr_system=fopen("system_data.dat","rb");
			fread(&sensible_data,sizeof(sw_data),1,ptr_system);
			fclose(ptr_system);
			
			printf("\nTorneo eliminato con successo!\n");
			return_value=0;
			system("PAUSE");
		}
	}
	else{
		return_value=1;
	}
	return return_value;
}

