#include "reg_log.h"
extern FILE *ptr_system;
extern sw_data sensible_data;
extern login logged_in;

short int loginfnz() {

	login dati_accesso={"","",0};
	char nome_array[LEN_USER]; 
	char password_array[LEN_PSW];
	int stato=0;

	FILE *ptr_login;

	if ((ptr_login=fopen("dati_login.dat","rb"))==NULL){
		printf("\nNon ci sono utenti memorizzati!\n");
		system("PAUSE");
	}
	
	else{
		printf("\nStai per effettuare il login. Continuare? S/N  ");
		if(getch()=='s'||getch()=='S'){
			do{
				printf("\nInserire nome utente:  ");
				scanf("%s", nome_array);
	
				printf("\nInserisci password:  ");
				scanf("%s", password_array);
	
				while(!feof(ptr_login)) {
					
					fread(&dati_accesso, sizeof(login),1,ptr_login);
		
					if(strcmp(nome_array,dati_accesso.nome_utente)==0) {
						if(strcmp(password_array, dati_accesso.password)==0){
		
							printf("Accesso effettuato\n");
							stato=1;
							break;
						}
					}
				}
				
				if(stato!=1){
					system("cls");
					printf("Dati errati. Reinserire\n");
					system("PAUSE");
				}
			
				rewind(ptr_login);
			
			}while(stato!=1);
			
			logged_in=dati_accesso;
			system("PAUSE");
			fclose(ptr_login);
		}
	}
	
	return dati_accesso.codice;
	
}

int registrazione (short int code) {
	
	int return_value;
	login dati_accesso={"","",0};
	char nome_array[LEN_USER];
	char password_array[LEN_PSW];
	char password_confirm[LEN_PSW];
	short int stato=0;
	char file_name[]="dati_login";
	login flag={"","",0};

	FILE *ptr_login;

	printf("\nStai per effettuare la registrazione. Continuare? S/N  \n");

	if(getch()=='s'||getch()=='S'){

		ptr_login=fopen("dati_login.dat","ab+");

		do{
			system("cls");
			printf("Inserire nome utente:  ");
			scanf("%s", nome_array);

			while(!feof(ptr_login)){

				fread(&flag, sizeof(login),1,ptr_login);

				if((strcmp(flag.nome_utente,nome_array))==0){
					printf("Esiste gia' un utente con questo nome.\n");
					system("PAUSE");
					rewind(ptr_login);
					stato=0;
					break;
				}

				else{
					stato=1;
					return_value=0;
				}
			}
		}while(stato!=1);

		fclose(ptr_login);
		stato=0;

		while(stato!=1){

			printf("\nInserisci password:  ");
			scanf("%s", password_array);
			printf("\nReinserisci password:  ");
			scanf("%s", password_confirm);

			ptr_login=fopen("dati_login.dat","ab+");

			if(strcmp(password_array,password_confirm)==0){

				strcpy(dati_accesso.nome_utente,nome_array);
				strcpy(dati_accesso.password,password_array);
				dati_accesso.codice=code;
				fwrite(&dati_accesso, sizeof(login),1,ptr_login);
				fclose(ptr_login);
				stato=1;
			}
			else{
				printf("\nPASSWORD NON CORRISPONDENTI!\n");
				system("PAUSE");
				system("cls");
			}
		}

		sensible_data.utenti_registrati++;

		if((ptr_system=fopen("system_data.dat","wb"))==NULL){
			printf("File system non trovato\n");
			return_value=1;
		}
		else{
			fwrite(&sensible_data,sizeof(sw_data),1,ptr_system);
			fclose(ptr_system);
		}
		sort_user(file_name);

		printf("Utente registrato con successo!\n");
		return_value=0;
		system("PAUSE");
	}
	else{
		printf("Ritorno al menu\n");
		system("PAUSE");
		return_value=1;
	}
	return return_value;
}
