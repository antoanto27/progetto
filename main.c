#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "reg_log/reg_log.h"
#include "delete/delete.h"
#include "output/output.h"
#include "menage_torneo/menage_torneo.h"
#include "sort/sort.h"
#include "control/control.h"

FILE *ptr_system;//puntatore al file system
sw_data sensible_data={0,0,""};//variabile di tipo dati_sw
login logged_in={"","",0};


int main () {
	
	system("color F1");
	system("mode 100,30");
	char input;
	char scelta;
	int pass;
	int loop=1;//serve per non uscire mai dal programma;
	short int flag=0;

	FILE *ptr_login;

	if((ptr_system=fopen("system_data.dat","rb"))!=NULL){
		fread(&sensible_data,sizeof(sw_data),1,ptr_system);
		fclose(ptr_system);
	}
	printf("\t\t*****************************************\n");
	printf("\t\t*          !!RUN YOUR TOURNEY!!         *\n");
	printf("\t\t*****************************************\n");
	printf("\n\t   Software per la gestione di campionati di calcetto\n");
	printf("\n\nDeveloped by: Antonio Soldano\n");
	printf("              Nicola Scommegna\n");
	printf("              Ruggiero Rizzi\n\n");
	system("PAUSE");
	do{
		system("cls");
		do{
			printf("Premi 1 per registrarti\nPremi 2 per effettuare il login\n");
		
			//Controllo sull'inserimento
		
			input=getch();
			pass=choose_control(input);
			if(pass!=1&&pass!=2){
				flag=1;
				printf("!!!Scelta non valida! Reinserire!!!\n\n");
				system("PAUSE");
				system("cls");
			}
			else{
				break;
			}
		}while(flag!=0);
		
		//Fine controllo sull'inserimento

		if(pass==1) {
				if ((ptr_login=fopen("dati_login.dat","rb"))==NULL){
					printf("L'utente seguente sara' memorizzato come admin\n");
					sensible_data.n_tornei=0;
					registrazione(5);
				}
				else{
					registrazione(2);
				}
		}
		
		else {

			switch(loginfnz()) {
				
			case 1: //organizzatore
		        do{ 
					do{
						system("cls");
						utente_loggato();
						printf("1)Creazione Torneo\n");
						printf("2)Avvia torneo\n");
						printf("3)Visualizza calendario\n");
						printf("4)Inserimento risultati\n");
						printf("5)Visualizza classifica\n");
						printf("6)Visualizza squadre iscritte ad un torneo\n");
						printf("0)Logout\n");
			
						input=getch();
						pass=choose_control(input);
						if(!(pass>=0 && pass<=6)){
							flag=1;
							printf("!!!Scelta non valida! Reinserire!!!\n\n");
							system("PAUSE");
						}
						else{
							flag=0;
						}
					}while(flag!=0);
		            
					switch(pass){
						case 1: crea_torneo(); break;
						case 2: avvia_torneo(); break;
						case 3: {
									char nome_file[50];
									char name_torneo[30];
									short int return_value;
									return_value=visualizza_tornei(3);
									if(return_value==1){
	
										printf("Inserisci il nome del torneo da visualizzare: ");
										scanf("%s", name_torneo);
										strcpy(nome_file,name_torneo);
										strcat(nome_file,"_calendario");
										stampa_calendario(nome_file,name_torneo);
										break;
									}
									else{
										break;
									}
								}
						case 4: aggiorna_risultati(); break;
						case 5: {
									char nome_file[50];
									visualizza_tornei(3);
									printf("Inserisci il nome del torneo da visualizzare: ");
									scanf("%s", nome_file);
									strcat(nome_file,"_classifica");
									stampa_classifica(nome_file);
									break;
								} 
						case 6: {
									char nome_file[50];
									visualizza_tornei(1);
									printf("Inserisci il nome del torneo da visualizzare: ");
									scanf("%s", nome_file);
									stampa_squadre(nome_file);
									break;
								} 
						case 0: break;
					}
						
				}while(pass!=0);
				break;	
				
	
			case 2: //capitano
				do{
					do{
						system("cls");
						utente_loggato();
						printf("1)Registrati al Torneo\n");
						printf("2)Visualizza lista tornei\n");
						printf("3)Visualizza calendario\n");
						printf("4)Visualizza classifica\n");
						printf("5)Visualizza squadre iscritte ad un torneo\n");
						printf("0)Logout\n");
						
						input=getch();
						pass=choose_control(input);
						if(!(pass>=0&&pass<=5)){
							flag=1;
							printf("!!!Scelta non valida! Reinserire!!!\n\n");
							system("PAUSE");
						}
						else{
							flag=0;
						}
					}while(flag!=0);
					
					switch(pass){
						do{
							case 1: registrazione_torneo(); break;
							case 2: visualizza_tornei(2); break;
							case 3: {
									char nome_file[50];
									char name_torneo[30];
									short int return_value;
									return_value=visualizza_tornei(3);
									if(return_value==1){
	
										printf("Inserisci il nome del torneo da visualizzare: ");
										scanf("%s", name_torneo);
										strcpy(nome_file,name_torneo);
										strcat(nome_file,"_calendario");
										stampa_calendario(nome_file,name_torneo);
										break;
									}
									else{
										break;
									}
									}
							case 4: {	char nome_file[50];
										short int return_value;
										return_value=visualizza_tornei(3);
										if(return_value==1){
								
											printf("Inserisci il nome del torneo da visualizzare: ");
											scanf("%s", nome_file);
											strcat(nome_file,"_classifica");
											stampa_classifica(nome_file);
											break;
										}
										else{
											break;
										}
									}
							case 5: {
									char nome_file[50];
									visualizza_tornei(1);
									printf("Inserisci il nome del torneo da visualizzare: ");
									scanf("%s", nome_file);
									stampa_squadre(nome_file);
									break;
									} 
							case 0: break;
							default:  printf("Scelta non valida\n");
						}while(pass!=0);
					}
				}while(pass!=0);
				break;
				
			case 5:	
			case 4: //amministratore
				do{
					do{
						system("cls");
						utente_loggato();
						printf("1)Registrazione nuovo admin\n");
						printf("2)Registrazione nuovo organizzatore\n");
						printf("3)Elimina utente\n");
						printf("4)Elimina torneo\n");
						printf("5)Visualizza elenco tornei\n");
						printf("6)Visualizza elenco utenti\n");
						printf("0)Logout\n");
			
						input=getch();
						pass=choose_control(input);
						if(!(pass>=0&&pass<=6)){
							flag=1;
							printf("!!!Scelta non valida! Reinserire!!!\n\n");
							system("PAUSE");
						}
						else{
							flag=0;
							}
					}while(flag!=0);
		
					switch(pass){
						do{
							case 1: printf("L'utente seguente sara' memorizzato come admin\n");
									registrazione(4); break;
							case 2: registrazione(1); break;
							case 3: elimina_utente(); break;
							case 4: elimina_torneo(); break;
							case 5: visualizza_tornei(1); break;
							case 6: visualizza_utenti(); break;
							case 0: break;
							default:  printf("Scelta non valida\n");
						}while(pass!=0);
					}
				}while(pass!=0);
				break;
			}	
		}
	}while(loop!=0);

	return 0;
}   

