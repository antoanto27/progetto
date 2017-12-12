#include "menage_torneo.h"

extern sw_data sensible_data;
extern FILE *ptr_system;
extern login logged_in;

int crea_torneo(){
	
	int return_value;
	FILE *ptr_admin;//puntatore al file riservato all'amministratore (lista tornei)
	FILE *ptr_torneo;//puntatore al file riserbato all'organizzatore
	char nome_torneo[LEN_TORNEO_NAME];
	torneo info_torneo;
	char lista_tornei[]="lista_tornei";
	int stato;
    torneo control;
    
	ptr_admin=fopen("lista_tornei.dat","ab+");
	rewind(ptr_admin);
	
	    do{
			system("cls");
			printf("Insersci il nome del nuovo torneo!  ");
			scanf("%s", nome_torneo);
					
			while(!feof(ptr_admin)){
				fread(&control, sizeof(torneo),1,ptr_admin);
				if((strcmp(control.nome_torneo,nome_torneo))==0){
					printf("Esiste gia' un torneo con questo nome.\n");
					system("PAUSE");
					rewind(ptr_admin);
					stato=0;
					break;
				}
					
				else{
					stato=1;
					return_value=0;
				}
				
			}	
			rewind(ptr_admin);			
		}while(stato!=1);
		
		fclose(ptr_admin);
		if(stato==1){
			
			ptr_admin=fopen("lista_tornei.dat","ab");
			strcpy(info_torneo.nome_torneo,nome_torneo);
			strcpy(info_torneo.nome_proprietario,logged_in.nome_utente);
			info_torneo.codice=1;
		
			fwrite(&info_torneo,sizeof(torneo),1,ptr_admin);
			fclose(ptr_admin);
		
		
			if ((ptr_torneo=fopen(nome_torneo,"wb"))==NULL){
				printf("Impossibile aprire il file\n");
				return_value=1;
			}
			else{
				fclose(ptr_torneo);
			}
		
			sensible_data.n_tornei++;
			ptr_system=fopen("system_data.dat","wb");
			fwrite(&sensible_data,sizeof(sw_data),1,ptr_system);
			fclose(ptr_system);
			fclose(ptr_torneo);
			sort_tornei(lista_tornei);
			printf("Torneo registrato con successo!\n");
			system("PAUSE");
		}
		return return_value;
	}


int avvia_torneo(){

	char nome_torneo[LEN_TORNEO_NAME];
	char nome_classifica[LEN_CLASSIFICA_NAME];
	iscrizioni squadre_iscritte={""};
	classifica score={"",0,0,0,0};
	torneo lista;
	FILE *ptr_torneo;
	FILE *ptr_lista;
	FILE *ptr_classifica;
	int n_squadre=0;
	date inizio;
	short int flag_control;
	int return_value;
	int controllo;
	short int flag2=0;
	int read;
	
	controllo=visualizza_tornei(2);
	
	if(controllo==1){
		
		printf("Inserisci il nome del torneo da avviare: ");
		scanf("%s", nome_torneo);
		
		strcpy(nome_classifica,nome_torneo);
		strcat(nome_classifica,"_classifica");
	
		
		
		if(((ptr_torneo=fopen(nome_torneo,"rb"))==NULL)){
			printf("Impossibile avviare il torneo.\nIl torneo non esiste o non ci sono squadre iscritte.\n");
			fclose(ptr_torneo);
			flag2=1;
			return_value=1;
		}
		
		else{
			ptr_lista=fopen("lista_tornei.dat","rb");
			while(!feof(ptr_lista)){
				fread(&lista,sizeof(torneo),1,ptr_lista);
				if((strcmp(nome_torneo,lista.nome_torneo))==0){
					if(lista.codice==0||lista.codice==2){
						printf("Torneo gia' avviato!\n");
						flag2=1;
						return_value=1;
					}
					if((strcmp(lista.nome_proprietario,logged_in.nome_utente))!=0){
						printf("Impossibile avviare questo torneo: il proprietario di questo torneo e' %s\n",lista.nome_proprietario);
						flag2=1;
						return_value=1;
					}
				}
			}
			fclose(ptr_lista);
		}
		
		ptr_torneo=fopen(nome_torneo,"rb");
		read=fread(&squadre_iscritte,sizeof(iscrizioni),1,ptr_torneo);
		rewind(ptr_torneo);
		
		if(read<=0){
			printf("Nessuna squadra iscritta in questo torneo. Impossibile avviare!\n");
			flag2=1;
			return_value=1;
		}
			
		if(flag2==0){
			
			ptr_classifica=fopen(nome_classifica,"wb");
			printf("Squadre iscritte a questo torneo:\n");
			
			while(fread(&squadre_iscritte,sizeof(iscrizioni),1,ptr_torneo)>0){
				strcpy(score.squadra,squadre_iscritte.nome_squadra);
				fwrite(&score,sizeof(classifica),1,ptr_classifica);
				printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
				printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);	
				printf("%c%-30s%c\n",186,squadre_iscritte.nome_squadra,186);
				printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
				printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
				n_squadre++;
			}
			
			fclose(ptr_torneo);
			fclose(ptr_classifica);
			return_value=0;
			ptr_lista=fopen("lista_tornei.dat","rb+");
	
			while(!feof(ptr_lista)) {
				fread(&lista, sizeof(torneo),1,ptr_lista);
	
				if(strcmp(nome_torneo,lista.nome_torneo)==0){
					lista.codice=0;
					fseek(ptr_lista,(-1)*sizeof(torneo),SEEK_CUR);
					fwrite(&lista, sizeof(torneo),1,ptr_lista);
					break;
				}
			}
			
			fclose(ptr_lista);
			printf("Inserire la data di inizio del torneo:\n");
			
			do{
				printf("Giorno (GG) ");
				scanf("%d", &inizio.giorno);
				printf("Mese (MM)");
				scanf("%d",&inizio.mese);
				printf("Anno (AAAA) ");
				scanf("%d", &inizio.anno);
			}while((data_control(inizio))!=0);
				
			printf("\nCalendario delle partite\n\n");
			calendario(n_squadre,nome_torneo,inizio);
			printf("Torneo avviato con successo!\n");
		}
		else{
			fclose(ptr_torneo);
		}
		system("PAUSE");
	}
	else{
		return_value=1;
	}
	return return_value;
}



int registrazione_torneo(){

	FILE *ptr_torneo;
	FILE *ptr_lista;

    char nome_torneo[LEN_TORNEO_NAME];
    torneo control;
    iscrizioni squadra={""};
    char nome_squadra[LEN_SQUADRE];
    int stato;
    int return_value;
	
	if(!(visualizza_tornei(2)==0)){
	
	    printf("A quale torneo vuoi registrarti? \n");
	    scanf("%s",nome_torneo);
	    
	    ptr_lista=fopen("lista_tornei.dat","rb");
	    
	    while(!feof(ptr_lista)){
	    	fread(&control,sizeof(torneo),1,ptr_lista);
	    	if((strcmp(control.nome_torneo,nome_torneo))==0){
	    		if(control.codice==0||control.codice==2){
	    			printf("Impossibile registrarsi! Le iscrizioni sono chiuse.\n");
	    			system("PAUSE");
	    			fclose(ptr_lista);
	    			return 1;
				}
			}
		}
	    
	    if((ptr_torneo=fopen(nome_torneo,"rb"))== NULL){
	            printf("Il torneo %s non esiste\n",nome_torneo);
	            fclose(ptr_torneo);
	            return_value=1;
	    }
	    
	    else{
	    	fclose(ptr_torneo);
			ptr_torneo=fopen(nome_torneo,"rb");
			
			do{
				system("cls");
				printf("Inserisci il nome della squadra\n");
		        scanf("%s",nome_squadra);
		        
				while(!feof(ptr_torneo)){
					
					fread(&squadra, sizeof(iscrizioni),1,ptr_torneo);
					
					if((strcmp(squadra.nome_squadra,nome_squadra))==0){
						printf("Esiste gia' una squadra con questo nome.\n");
						system("PAUSE");
						rewind(ptr_torneo);
						stato=0;
						break;
					}
						
					else{
						stato=1;
					}
				}
					
				rewind(ptr_torneo);	
						
			}while(stato!=1);
			
	        fclose(ptr_torneo);
	        
	        if(stato==1){
		        strcpy(squadra.nome_squadra,nome_squadra);
		        ptr_torneo=fopen(nome_torneo,"ab");
		    	fwrite(&squadra.nome_squadra,sizeof(iscrizioni),1,ptr_torneo);
		        fclose(ptr_torneo);
				printf("Registrazione effettuata con successo!\n");
				return_value=0;
			}
	    }
	    
	    system("PAUSE");
	    fclose(ptr_lista);
	}
	else{
		return_value=1;;
	}
	return return_value;
}


void calendario(int n, char name_torneo[LEN_TORNEO_NAME], date inizio_torneo){
	
	int return_value;
    int t;
    int d=0;//contatore da passare alla funzione data per contare le giornate
	int i=0;
	int j;
	int h;
	int temp=0;
	partite calendariop[n/2][n-1]; //matrice per squadre pari
	partite calendariod[(n-1)/2][n];//matrice per squadre dispari
	int s_array=(n-1);
	int teamsp[s_array];
	int teamsd[n];
	int riposo[n];

	iscrizioni teams_names[n];
	FILE *ptr_torneo;
	FILE *ptr_calendario;
	char nome_file[LEN_CALENDARIO_NAME];
	char temporaneo[LEN_TORNEO_NAME];
	strcpy(nome_file,name_torneo);
	strcat(nome_file,"_calendario");

	ptr_calendario=fopen(nome_file,"wb");
	ptr_torneo=fopen(name_torneo,"rb");
	int g;//serve a fare l'associazione numero-nome

	file_squadre nomi_squadre={"",0,0,"",0,0,0};

	while(!feof(ptr_torneo)){
		fread(&teams_names[i].nome_squadra,sizeof(iscrizioni),1,ptr_torneo);
		i++;
	}

	fclose(ptr_torneo);

	if((n%2)==0){
		
		for(i=0;i<s_array;i++){
			teamsp[i]=i;
		}
	
		for(i=0;i<(n-1);i++){
			
			calendariop[0][i].casa=teamsp[0];
			calendariop[0][i].trasferta=(n-1);
			h=1;
	
			for(j=1;j<(n/2);j++){
				calendariop[j][i].casa=teamsp[j];
				calendariop[j][i].trasferta=teamsp[s_array-h];
				h++;
			}
	
			temp=teamsp[s_array-1];
			
			for(j=(s_array-1);j>0;j--){
				teamsp[j]=teamsp[j-1];
			}
			
			teamsp[0]=temp;
		}
	
		for(i=0;i<(n-1);i++){
	
	            nomi_squadre.giornata=data_torneo(inizio_torneo,d);
	
			for(j=0;j<(n/2);j++){
				g=calendariop[j][i].casa;
				strcpy(temporaneo,teams_names[g].nome_squadra);
				strcpy(nomi_squadre.casa,temporaneo);
				g=calendariop[j][i].trasferta;
				strcpy(temporaneo,teams_names[g].nome_squadra);
				strcpy(nomi_squadre.trasferta,temporaneo);
				fwrite(&nomi_squadre,sizeof(file_squadre),1,ptr_calendario);
			}
			inizio_torneo=nomi_squadre.giornata;
			d++;
		}
	}
	
	else{
		
		for(i=0;i<n;i++){
			teamsd[i]=i;
		}
	
		for(i=0;i<n;i++){
	
			h=2;
	
			for(j=0;j<(n-1)/2;j++){
				calendariod[j][i].casa=teamsd[j];
				calendariod[j][i].trasferta=teamsd[n-h];
				h++;
			}
	
			temp=teamsd[n-1];
			riposo[i]=temp;
			
			for(j=(n-1);j>0;j--){
				teamsd[j]=teamsd[j-1];
			}
			
			teamsd[0]=temp;
		}
		//Associazione squadre-vettore di int
	
		for(i=0;i<n;i++){
			
	            nomi_squadre.giornata=data_torneo(inizio_torneo,d);
	            
			for(j=0;j<((n-1)/2);j++){
				g=calendariod[j][i].casa;
				strcpy(nomi_squadre.casa,teams_names[g].nome_squadra);
				g=calendariod[j][i].trasferta;
				strcpy(nomi_squadre.trasferta,teams_names[g].nome_squadra);
				fwrite(&nomi_squadre,sizeof(file_squadre),1,ptr_calendario);
			}
			
			inizio_torneo=nomi_squadre.giornata;
			d++;
			g=riposo[i];
			strcpy(nomi_squadre.casa,"RIPOSA");
			strcpy(nomi_squadre.trasferta,teams_names[g].nome_squadra);
			fwrite(&nomi_squadre,sizeof(file_squadre),1,ptr_calendario);
		}
	
	}
	
	fclose(ptr_calendario);
	stampa_calendario(nome_file,name_torneo);
}



date data_torneo(date inizio, int cont){

    date data_aggiornata={0,0,0};
    short int flag=0; //flag per anno bisestile
    int mesi[12]={31,28,31,30,31,30,31,31,30,31,30,31};

    if((inizio.anno%4)==0){
        mesi[1]+=1;
    }

    if(cont==0){
        data_aggiornata=inizio;
    }

    else{

        if(((inizio.giorno)+7)>mesi[inizio.mese-1]){

            data_aggiornata.giorno=7-(mesi[inizio.mese-1]-inizio.giorno);
            data_aggiornata.mese=inizio.mese+1;

            if((inizio.mese+1)>12){

            data_aggiornata.mese=01;
            data_aggiornata.anno=inizio.anno+1;
            }

            else{
            data_aggiornata.anno=inizio.anno;
            }
        }

        else{
            data_aggiornata=inizio;
            data_aggiornata.giorno+=7;
		}
    }

    return data_aggiornata;
}

int aggiorna_risultati(){
	
    int counter=0;
    int exit_loop=0;
    int n_match;
    int total_matches;
    FILE *ptr_calendario;
    FILE *ptr_torneo;
    FILE *ptr_classifica;
    FILE *ptr_lista;
    char nome_torneo[LEN_TORNEO_NAME];
    char nome_calendario[LEN_CALENDARIO_NAME];
    char nome_classifica[LEN_CLASSIFICA_NAME];
    int i=0;
    file_squadre flag_tmp={"",0,0,"",0,0,0,0};
    iscrizioni *n_teams; //conta il numero di squadre
    int h=0; //contatore per ciclo while.
	classifica score={"",0,0,0,0};
	int return_value;
	int fine_torneo=0;
	torneo file_lista;
	int flag=0;
	int controllo;
	
	controllo=visualizza_tornei(3);
	
	printf("Inserisci il nome del torneo da aggiornare!\n");
	scanf("%s",nome_torneo);
	
	ptr_lista=fopen("lista_tornei.dat","rb");
		while(!feof(ptr_lista)){
			fread(&file_lista,sizeof(torneo),1,ptr_lista);
			if((strcmp(file_lista.nome_torneo,nome_torneo))==0){
				if((strcmp(file_lista.nome_proprietario,logged_in.nome_utente))!=0){
					printf("Impossibile aggiornare questo torneo: il proprietario di questo torneo e' %s",file_lista.nome_proprietario);
					controllo=0;
					system("PAUSE");
					break;
				}
			}
		}	
	fclose(ptr_lista);
	
	if(controllo==1){
		
	    
	    strcpy(nome_calendario,nome_torneo);
	    strcat(nome_calendario,"_calendario");
	    strcpy(nome_classifica,nome_torneo);
	    strcat(nome_classifica,"_classifica");
	    
	    
	    if((ptr_torneo=fopen(nome_torneo,"rb"))==NULL){
	        printf("File non trovato");
	        flag=1;
	        return_value=1;
	        fclose(ptr_torneo);
	    }
	    
	    if((ptr_classifica=fopen(nome_classifica,"rb"))==NULL){
	        printf("File non trovato");
	        flag=1;
	        return_value=1;
	        fclose(ptr_classifica);
	    }
	
	    if((ptr_calendario=fopen(nome_calendario,"rb"))==NULL){
	    	printf("file non trovato\n");
	    	flag=1;
	    	return_value=1;
	    	fclose(ptr_calendario);
	    } 
	    
	    if(flag==0){
		    ptr_classifica=fopen(nome_classifica,"rb+");
		    ptr_calendario=fopen(nome_calendario,"rb+");
		    
			fseek(ptr_calendario,-1*sizeof(file_squadre),SEEK_END);
		    fread(&flag_tmp,sizeof(file_squadre),1,ptr_calendario);
		    
		    if(flag_tmp.flag==1){
		    	printf("Torneo concluso! Non e' possibile aggiornare i risultati\n");
		    	system("PAUSE");
		    	return_value=1;
		    	fclose(ptr_classifica);
		    	fclose(ptr_calendario);
			}
			
			else{
				
		  		rewind(ptr_calendario);
		  		
		  		n_teams=(iscrizioni *) calloc(1,sizeof(iscrizioni));
		  		
				while((fread(n_teams[i].nome_squadra,sizeof(iscrizioni),1,ptr_torneo))>0){
						i++;
						n_teams=(iscrizioni *) realloc(n_teams,(i+1)*sizeof(iscrizioni));
			       	 }
				free(n_teams);
		
				stampa_calendario(nome_calendario,nome_torneo);
				
		        if(i%2==0){
		            n_match=i/2;
		            total_matches=n_match*(i-1);
		        }
		        
		        else{
		            n_match=(i+1)/2;
		            total_matches=n_match*i;
		        }
		        
		        file_squadre risultati[n_match];
		        
		        while(exit_loop==0){
		        	
			        fread(&flag_tmp,sizeof(file_squadre),1,ptr_calendario);
			        
			        if(flag_tmp.flag==0){
			            fseek(ptr_calendario,-1*sizeof(file_squadre),SEEK_CUR);
			            exit_loop=1;
			        }
		        }
		        
		        while(h < n_match){
		        	
		            fread(&risultati[h],sizeof(file_squadre),1,ptr_calendario);
		            
		        	if((strcmp(risultati[h].casa,"RIPOSA")==0)){
		        		risultati[h].flag=1;
		        		h++;
					}
					
		        	else{
		        		
		          	  	printf("Inserisci il risultato:%s-%s \n",risultati[h].casa,risultati[h].trasferta);
		            	scanf("%d",&risultati[h].gc);
		            	scanf("%d",&risultati[h].gt);
		            	
		            	do{
		            		fread(&score,sizeof(classifica),1,ptr_classifica);
		            	}while((strcmp(score.squadra,risultati[h].casa))!=0);
		            	
		            	fseek(ptr_classifica,-1*sizeof(classifica),SEEK_CUR);
		            	
		            	if(risultati[h].gc>risultati[h].gt){
		            		score.punti+=3;
		            		score.gf+=risultati[h].gc;
		            		score.gs+=risultati[h].gt;
		            		score.dr+=risultati[h].gc-risultati[h].gt;
		            		fwrite(&score,sizeof(classifica),1,ptr_classifica);
						}
						
						else if(risultati[h].gc==risultati[h].gt){
		            		score.punti+=1;
		            		score.gf+=risultati[h].gc;
		            		score.gs+=risultati[h].gt;
		            		fwrite(&score,sizeof(classifica),1,ptr_classifica);
						}
						
						else{
							score.punti+=0;
		            		score.gf+=risultati[h].gc;
		            		score.gs+=risultati[h].gt;
		            		score.dr+=risultati[h].gc-risultati[h].gt;
		            		fwrite(&score,sizeof(classifica),1,ptr_classifica);
						}
						
						rewind(ptr_classifica);
						do{
		            		fread(&score,sizeof(classifica),1,ptr_classifica);
		            	}while((strcmp(score.squadra,risultati[h].trasferta))!=0);
		            	
		            	fseek(ptr_classifica,-1*sizeof(classifica),SEEK_CUR);
		            	
		            	if(risultati[h].gt>risultati[h].gc){
		            		score.punti+=3;
		            		score.gf+=risultati[h].gt;
		            		score.gs+=risultati[h].gc;
		            		score.dr+=risultati[h].gt-risultati[h].gc;
		            		fwrite(&score,sizeof(classifica),1,ptr_classifica);
						}
						
						else if(risultati[h].gc==risultati[h].gt){
		            		score.punti+=1;
		            		score.gf+=risultati[h].gt;
		            		score.gs+=risultati[h].gc;
		            		fwrite(&score,sizeof(classifica),1,ptr_classifica);
						}
						
						else {
							score.punti+=0;
		            		score.gf+=risultati[h].gt;
		            		score.gs+=risultati[h].gc;
		            		score.dr+=risultati[h].gt-risultati[h].gc;
		            		fwrite(&score,sizeof(classifica),1,ptr_classifica);
						}
						
						rewind(ptr_classifica);
		            	risultati[h].flag=1;
						h++;
					}
		        }
		        
		        h=0;
		        fseek(ptr_calendario,-n_match*sizeof(file_squadre),SEEK_CUR);
		        
		        while(h < n_match){
		        	fwrite(&risultati[h],sizeof(file_squadre),1,ptr_calendario);
		      		h++;
				}
				
		        rewind(ptr_calendario);
		        fseek(ptr_calendario,(-1)*sizeof(file_squadre),SEEK_END);
		        fread(&flag_tmp,sizeof(file_squadre),1,ptr_calendario);
		        
		        if(flag_tmp.flag==1){
		        	fine_torneo=1;
				}
		        
				if(fine_torneo==1){
					
					printf("Torneo Concluso!\n");
					ptr_lista=fopen("lista_tornei.dat","rb+");
	
					while((fread(&file_lista,sizeof(torneo),1,ptr_lista))>0){
						
						if((strcmp(file_lista.nome_torneo,nome_torneo))==0){
							file_lista.codice=2;
							fseek(ptr_lista,-1*sizeof(torneo),SEEK_CUR);
							fwrite(&file_lista,sizeof(torneo),1,ptr_lista);
							
							break;
						}
					}
					
					fclose(ptr_classifica);
					fclose(ptr_lista);
					sort_score(nome_classifica,i);
					ptr_classifica=fopen(nome_classifica,"rb");
					fread(&score,sizeof(classifica),1,ptr_classifica);
					printf("La squadra %s ha vinto il torneo! Complimenti vivissimi a voi e famiglia.\n",score.squadra);
					fclose(ptr_classifica);
				}
				
				
				fclose(ptr_calendario);
				fclose(ptr_torneo);
		        fclose(ptr_classifica);
		        return_value=0;
				sort_score(nome_classifica,i);
		        stampa_calendario(nome_calendario,nome_torneo);
			}
		}
	}
	else{
		return_value=1;
	}
	return return_value;
}
