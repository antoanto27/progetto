#ifndef STDIO_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
#endif
#ifndef LEN_DEFINE
	#define LEN_DEFINE
    #define LEN_CALENDARIO_NAME 42
	#define LEN_TORNEO_NAME 30
	#define LEN_CLASSIFICA_NAME 42
	#define LEN_TIPO 25
	#define LEN_SQUADRE 30
	#define LEN_USER 21
	#define LEN_PSW 13
#endif
#ifndef TYPE_SW_DATA
	#define TYPE_SW_DATA
	struct dati_sw {	//dati sensibili del programma
		int utenti_registrati;
		int n_tornei;
		char first[LEN_USER];
	};
	typedef struct dati_sw sw_data;
#endif

#ifndef TYPE_LOGIN
	#define TYPE_LOGIN
		struct dati_utente {
		char nome_utente[LEN_USER];
		char password[LEN_PSW];
		short int codice;
	};
	typedef struct dati_utente login;
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
 
#ifndef TYPE_TORNEO
	#define TYPE_TORNEO
	struct dati_torneo {
	char nome_torneo[LEN_TORNEO_NAME];
	short int codice; //1 Iscrizioni aperte 0 Iscrizioni chiuse 2 concluso
	char nome_proprietario[LEN_USER];
};
typedef struct dati_torneo torneo;
#endif

#ifndef TYPE_ISCRIZIONI
	#define TYPE_ISCRIZIONI
	struct squadre_file_torneo{
	char nome_squadra[LEN_SQUADRE];
	};
	typedef struct squadre_file_torneo iscrizioni;
#endif	

#ifndef TYPE_FILE_SQUADRE
	#define TYPE_FILE_SQUADRE
	struct file_calendario{
	
			char casa[LEN_SQUADRE];
			int gc;
			int gt;
			char trasferta[LEN_SQUADRE];
			date giornata;
			int flag;
		};	
		typedef struct file_calendario file_squadre;
#endif			
	
#ifndef TYPE_PARTITE
	#define TYPE_PARTITE	
		struct squadre{
		int casa;
		int trasferta;
	};
	typedef struct squadre partite;
	#endif	

#ifndef TYPE_CLASSIFICA
	#define TYPE_CLASSIFICA
		struct struttura_classifica{
		char squadra[LEN_SQUADRE];
		int punti;
		int gf;
		int gs;
		int dr;
		};
	   
		typedef struct struttura_classifica classifica;
#endif	 	
	
#ifndef MENAGE_TORNEO_H
	#define MENAGE_TORNEO_H
	int crea_torneo();	
	int avvia_torneo();
	int registrazione_torneo();
	void calendario(int n, char nome_torneo[30],date inizio_torneo);
	date data_torneo(date inizio, int cont);
	int aggiorna_risultati();
	#endif
	
#ifndef OUTPUT_h	
 	#define OUTPUT_H
 		int visualizza_utenti();
		int visualizza_tornei(short int code); //Codice 1 per amministratore, codice 2 per capitano
		int stampa_calendario(char nome_file[LEN_CALENDARIO_NAME], char nome_torneo[LEN_TORNEO_NAME]);
		int stampa_classifica(char nome_classifica[LEN_CLASSIFICA_NAME]);
		int stampa_squadre(char nome_torneo[LEN_TORNEO_NAME]);
		void utente_loggato();
	#endif

