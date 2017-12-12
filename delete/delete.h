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

#ifndef TYPE_LOGIN
	#define TYPE_LOGIN
		struct dati_utente {
		char nome_utente[LEN_USER];
		char password[LEN_PSW];
		short int codice;
	};
	typedef struct dati_utente login;
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

#ifndef TYPE_TORNEO
	#define TYPE_TORNEO
	struct dati_torneo {
	char nome_torneo[LEN_TORNEO_NAME];
	short int codice; //1 Iscrizioni aperte 0 Iscrizioni chiuse 2 concluso
	char nome_proprietario[LEN_USER];
	};
	typedef struct dati_torneo torneo;
#endif

#ifndef DELETE_H
	#define DELETE_H 
	int elimina_utente();
	int elimina_torneo();
#endif
