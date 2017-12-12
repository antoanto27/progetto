#include "sort.h"
extern sw_data sensible_data;

void sort_user(char nome_file[LEN_FILE_USER]){

    FILE *ptr_login;
	login scambio[sensible_data.utenti_registrati];
	login swap={"","",0};
	int i,j;
	strcat(nome_file,".dat");
	ptr_login=(fopen(nome_file,"rb"));
	i=0;

	while((fread(&scambio[i],sizeof(login),1,ptr_login))>0){
		i++;
	}

	for(i=1;i<sensible_data.utenti_registrati;i++){
		for(j=0;j<(sensible_data.utenti_registrati-1);j++){
			if(strcmp(scambio[j].nome_utente,scambio[j+1].nome_utente)>0){

				swap=scambio[j];
				scambio[j]=scambio[j+1];
				scambio[j+1]=swap;
			}
		}
	}

	fclose(ptr_login);
	ptr_login=(fopen(nome_file,"wb"));
	fwrite(&scambio,sizeof(login),sensible_data.utenti_registrati,ptr_login);
	fclose(ptr_login);

}

void sort_tornei(char nome_file[LEN_TORNEO_NAME]){

    FILE *ptr_torneo;
	torneo scambio[sensible_data.n_tornei];
	torneo swap={"",0};
	int i,j;
	strcat(nome_file,".dat");
	ptr_torneo=(fopen(nome_file,"rb"));
	i=0;

	while((fread(&scambio[i],sizeof(torneo),1,ptr_torneo))>0){
		i++;
	}

	for(i=1;i<sensible_data.n_tornei;i++){
		for(j=0;j<(sensible_data.n_tornei-1);j++){
			if(strcmp(scambio[j].nome_torneo,scambio[j+1].nome_torneo)>0){
				swap=scambio[j];
				scambio[j]=scambio[j+1];
				scambio[j+1]=swap;
			}
		}
	}

	fclose(ptr_torneo);
	ptr_torneo=(fopen(nome_file,"wb"));
	fwrite(&scambio,sizeof(torneo),sensible_data.n_tornei,ptr_torneo);
	fclose(ptr_torneo);
}

void sort_score(char nome_file[LEN_CLASSIFICA_NAME], int n_squadre){

    FILE *ptr_classifica;
	classifica scambio[n_squadre];
	classifica swap={"",0,0,0,0};
	int i,j;

	ptr_classifica=(fopen(nome_file,"rb"));
	i=0;

	while((fread(&scambio[i],sizeof(classifica),1,ptr_classifica))>0){
		i++;
	}

	for(i=1;i<n_squadre;i++){
		for(j=0;j<(n_squadre-1);j++){
			if(scambio[j].punti<scambio[j+1].punti){
				swap=scambio[j];
				scambio[j]=scambio[j+1];
				scambio[j+1]=swap;
			}
			else if(scambio[j].punti==scambio[j+1].punti){
				if(scambio[j].gf<scambio[j+1].gf){
					swap=scambio[j];
					scambio[j]=scambio[j+1];
					scambio[j+1]=swap;
				}
				else if(scambio[j].gf==scambio[j+1].gf){
					if(scambio[j].gs>scambio[j+1].gs){
						swap=scambio[j];
						scambio[j]=scambio[j+1];
						scambio[j+1]=swap;
					}
				}
			}
		}
	}

	fclose(ptr_classifica);
	ptr_classifica=(fopen(nome_file,"wb"));
	fwrite(&scambio,sizeof(classifica),n_squadre,ptr_classifica);
	fclose(ptr_classifica);
}

