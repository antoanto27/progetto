#ifndef STDIO_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
#endif

#ifndef REG_LOG_H
	#define REG_LOG_H
	#define LEN_USER 21
	#define LEN_PSW 13
	short int loginfnz();
	int registrazione(short int code);
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

//variabile di tipo dati_sw


