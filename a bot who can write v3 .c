#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 10000 // indicatore della posizione nel vocabolario della parola
#define MAX_LEN 100 // lettere della parola --> per ciascun indice ci sono massimo 100 lettere
                      //(indicata dalla parola chiave)  può essere fatta
#define data 10
#define verbii 1000
#define indicefrase 500
#define probud 6  //importanza verbo
#define probdd 8	// importanza nome
#define probtd 2	// importanza prefisso
int debugg=0; // 0 == false == no

int felice[MAX_WORDS], triste[MAX_WORDS], preoccupato[MAX_WORDS]; // categorie
char vocabolario[MAX_WORDS][MAX_LEN];
int vocab_size = 0;

int trova_parola(const char *parola) {
    for (int i = 0; i < vocab_size; i++) {
        if (strcmp(vocabolario[i], parola) == 0){
        	return i;
		} 
    }
    strcpy(vocabolario[vocab_size], parola);
     vocab_size++;
    return vocab_size-1;
   
    
}

int stop=0;

void classifica(const char *frase) {
    int score_felice = 0, score_triste = 0, score_preoccupato = 0;
    char copia[256];
    strcpy(copia, frase);
    char *token = strtok(copia, " ");

    while (token != NULL) {
        int idx = trova_parola(token);
        score_felice += felice[idx];
        score_triste += triste[idx];
        score_preoccupato += preoccupato[idx];
        token = strtok(NULL, " ");
    }
	if(debugg) printf("Frase: \"%s\"\n", frase);
    if (score_felice >= score_triste && score_felice >= score_preoccupato)
        printf("FELICE\n\n");
    else if (score_triste >= score_felice && score_triste >= score_preoccupato)
        printf("TRISTE\n\n");
    else
        printf("PREOCCUPATO\n\n");
        
    stop=67;
}


int lexicon[verbii];

void gram(const char *veer, const char *jet ){
	
	if(strcmp(jet, "verbo")==0) { lexicon[trova_parola(veer)]=1; }
	if(strcmp(jet, "nome")==0) { lexicon[trova_parola(veer)]=2; }
	if(strcmp(jet, "prefisso")==0) { lexicon[trova_parola(veer)]=3; }
	if(strcmp(jet, "chiave")==0) { lexicon[trova_parola(veer)]=6; }
}

int search_gram(const char *parola_da_cercare){
	return lexicon[trova_parola(parola_da_cercare)];
}

char frase[indicefrase][data][15];
int j=0;
int fag=0,gaf=0,ghh=0;
int paura=0;

void analyze_domande(const char *parol, const char *parola_chiave){
	//printf("parola: %s       indice parola in analyze: %d       parola ciave: %s \n",parol,trova_parola(parol),parola_chiave);
	//salva in frase la frase semplificata come stringa
	// divisione in verbo(1)1 verbo(2)2 nome(1)3 nome(2)4 prefisso5 parola chiave6
	strcpy(frase[paura][0], parola_chiave);
	
	//if(search_gram(parol)==1 && ghh==1) { strcpy(frase[paura][3], parol);}
	if(search_gram(parol)==1 && fag==1) { strcpy(frase[paura][2], parol); ghh=1; }
	if(search_gram(parol)==1 && fag==0) { strcpy(frase[paura][1], parol); fag=1; }
	
	if(search_gram(parol)==2 && gaf==1) { strcpy(frase[paura][4], parol);}
	if(search_gram(parol)==2 && gaf==0) { strcpy(frase[paura][3], parol); gaf=1;}
	
	
	if(search_gram(parol)==3 ) strcpy(frase[paura][5], parol);
}

void stampa_domanda_sempli(){
	
		for(int i=0;i<=6;i++){

			if(frase[paura][i][0]=='\0'){ printf("NNN ");} 
			else{ printf("%s ",frase[paura][i]);}
	}
	printf("\n");
}

int fla=0;
void call_frase(const char *cat, const char *valla){
	
	if(strcmp(cat,"domanda")==0) { if(debugg)stampa_domanda_sempli();} // viene eseguito quando si importa una domanda
	if(strcmp(cat,"domanda")!=0 && fla==1) classifica(valla);/*qui dentro viene eseguito	solo quando la frase presa non è una domanda*/
}




void data_import(const char *categoria, const char *idxx, const char *frase){
	
	
	//si ripete per ogni frase
	//if(strcmp("domanda",categoria)==0) paura++;
	char s[128];
	strcpy( s, frase);
	char *tok = strtok(s, " ");
	
	fag=0; gaf=0; ghh=0;//resetta la priorita di posizione sia del verbo che del nome in modo che rimangano salvati nell'ordine in cui sono scritti nella domanda
	while (tok != NULL) {
		
   //si ripete per ogni parola
    
     int idx = trova_parola(tok);
        if (strcmp(categoria, "felice") == 0) felice[idx]++;
        else if (strcmp(categoria, "triste") == 0) triste[idx]++;
        else if (strcmp(categoria, "preoccupato") == 0) preoccupato[idx]++;
        else if (strcmp(categoria, "domanda") == 0) { analyze_domande(tok,idxx); }
        
    tok = strtok(NULL, " ");
    
	}
	call_frase(categoria,frase);
	
	if(strcmp("domanda",categoria)==0 ){
		paura++;
	}else{
		j++;
	}
}

void dividi_domanda(char *kollo){
	
	char helloworld[122];
	char toke[50];
	char *tor;
	char alla[50];
	
	strcpy(alla,kollo);
	tor = strtok(kollo," ");
	
	if(strcmp("di",tor)==0 && tor !=NULL){
		
		while(tor !=NULL){
			
			if(strcmp("cosa",tor)==0) { strcpy(toke,"di cosa"); }
			if(strcmp("quale",tor)==0) { strcpy(toke,"di quale"); }
			if(strcmp("che",tor)==0) { strcpy(toke,"di che"); }
			
			tor = strtok(NULL," ");
		}
			strtok(alla," ");
			char *resto = alla+strlen(toke)+1;
			strcpy(helloworld,resto);
	} else{
			//toke = strtok(kollo," ");
			strcpy(toke, tor);
			char *resto = kollo+strlen(toke)+1;
			strcpy(helloworld,resto);
	
	}
	
	if(debugg) printf("\nfrase: %s \n",helloworld);
	if(helloworld[strlen(helloworld)-1]=='?'){
		helloworld[strlen(helloworld)-1]='\0';
	}
	
	if(debugg)printf("\nparola chiave: %s frase: %s \n",toke,helloworld);
	data_import("domanda",toke,helloworld);
	
}

char import[128];
	
void write_question(){
    scanf(" %[^\n]",import); 
	printf("\n");
	char copia[126];
	strcpy(copia,import);
	char *token = strtok(copia, " ");
	
	
    while (token != NULL) {
  		if(strcmp(token,"?")==0 || import[strlen(import)-1]=='?') fla=1;
        token = strtok(NULL, " ");
    }
    
    if(fla==1){
    	dividi_domanda(import);
	} else {
		if(debugg)printf("\n non è una domanda \n");
		classifica(import);
	}
    
}
char risposta_con_idx[indicefrase][128];
char soluzione[indicefrase][data][15];
int gey=0;

void stampa_soluzione_semplice(int indice_s,const char *soluzione_frase){
	printf("%d  ",indice_s);
	printf("%s     ",soluzione[indice_s][0]);
	for(int i=1;i<=5;i++){
		if(soluzione[indice_s][i][1]=='\0'){ printf("NNN "); } 
		else{ printf("%s ",soluzione[indice_s][i]);}
	}
	printf("            %s",soluzione_frase);
	printf("\n");
}

void rispondi(int idx_risposta){
	printf("\n%s \n",risposta_con_idx[idx_risposta]);
}


void data_import_soluz(const char *nome_soluzione,const char *verbi_soluzione,const char *testo_soluzione){
	int fags=0,gafs=0;
	
	//ripetuto ogni frase
	
	char copia[256];
	strcpy(copia,testo_soluzione);
	char *tolen=strtok(copia," ");
	strcpy(soluzione[gey][0], nome_soluzione);
	
	while(tolen !=NULL){
		//si ripete ogni parola in testo_soluzione[]
			// divisione in verbo(1)1 verbo(2)2 nome(1)3 nome(2)4 prefisso5 parola chiave6
		if(search_gram(tolen)==1 && fags==1) { strcpy(soluzione[gey][2], tolen); }
		if(search_gram(tolen)==1 && fags==0) { strcpy(soluzione[gey][1], tolen); fags=1; }
	
		if(search_gram(tolen)==2 && gafs==1) { strcpy(soluzione[gey][4], tolen);}
		if(search_gram(tolen)==2 && gafs==0) { strcpy(soluzione[gey][3], tolen); gafs=1;}
	
		if(search_gram(tolen)==3 ) strcpy(soluzione[gey][5], tolen);
		
		tolen=strtok(NULL," ");
	}
	if(debugg)stampa_soluzione_semplice(gey,testo_soluzione);
	strcpy(risposta_con_idx[gey],testo_soluzione);
	gey++;
	
	strcpy(copia,verbi_soluzione);
	char *toen=strtok(copia," ");
	int check_verbi=0;
	if(debugg){
	while(toen !=NULL){
		//si ripete per ogni verbo in verbi_soluzione[]
		
		if(strcmp(toen,soluzione[j][1])==0 ){
			printf("\nprimo verbo letto uguale che nella frase\n");
		}
		if(strcmp(toen,soluzione[j][2])==0 && check_verbi==1){
				printf("\nsecondo verbo letto uguale che nella frase\n");
		}
		toen=strtok(NULL," ");
		check_verbi=1;
		}
	}
}

int confronta_domanda(int x,int y){
	// x è ò'indice della domanda che gli ho appena fatto quindi frase[x][1/2/3/4/5] sara la domanda riassunta;
	// y è l'indice dell'ultima risposta imaprata dunque il numero di risposte che conosce dunque il numero di volte che deve cercare un confronto con frase[x][1/2/3/4/5]
	int prob=0,probi=0,indic_risp=0;
	
	for(int d=0;d<=y;d++){
	//	printf("\nelaborando la soluzione id indice:%d",d);
		for(int i=0;i<=5;i++){
		//	printf("\nconfrontando le parole di idx:%d",i);
			//printf("\n\nche sono: %s %s",soluzione[d][i],frase[x][i]);
			if(strcmp(soluzione[d][i],frase[x][i])==0){
					if(search_gram(frase[x][i])==1) prob +=probud;
					if(search_gram(frase[x][i])==2) prob +=probdd;
					if(search_gram(frase[x][i])==3) prob +=probtd;
					}
		}
		
		if(prob>probi) {
			indic_risp = d; 
			probi=prob;
		}
	}
	return indic_risp;
}

void stampa_frase_specifica(int kek){
	printf("\n");
	for(int i=0;i<=5;i++){
		printf("%s ",frase[kek][i]);
	}
}

void learn(){
	
	
	FILE *file = fopen("grammatica.txt", "r");

    char parola[128];
    char categoria[128];

    while (fscanf(file, "%127s %127s", parola, categoria) == 2) {
        gram(parola, categoria);
    }

    fclose(file);

	
	data_import("domanda","di quale","scuola fa parte il titolo migliore");
	data_import("domanda", "dove", "posso studiare in silenzio");
	data_import("domanda", "come", "si scrive un email formale");
	data_import("domanda", "quando", "arriva il treno regionale");
	data_import("domanda", "come", "si manda un messaggio");
	data_import("domanda", "quanto", "tempo serve per cuocere il pane");
	data_import("domanda", "chi", "lavora in quell ufficio");
	data_import("domanda", "perché", "non funziona il computer");
	data_import("domanda", "che", "musica ascolti di solito");
	data_import("domanda", "dove", "posso comprare un libro economico");
	data_import("domanda", "come", "si invia un messaggio su WhatsApp");
	data_import("domanda", "quando", "inizia la lezione di matematica");
	data_import("domanda", "quanto", "costa un caffè al bar");
	data_import("domanda", "chi", "ha scritto questa canzone");
	data_import("domanda", "perché", "l’amico non risponde al telefono");
	data_import("domanda", "che", "tempo fa nella tua città");
	data_import("domanda", "di cosa", "professione fai");
	data_import("domanda", "dove", "posso passeggiare al parco");
	data_import("domanda", "come", "si prepara la pasta al forno");
	data_import("domanda", "quando", "finisce il film di stasera");
	data_import("domanda", "perché", "le email finiscono nello spam");
	data_import("domanda", "quanto", "pesa un computer portatile");
	data_import("domanda", "come", "posso cuocere la pasta");
	data_import("domanda", "dove", "si può mangiare il pane fresco");
	data_import("domanda", "quando", "inizia il film stasera");
	data_import("domanda", "perché", "piove oggi");
	data_import("domanda", "quanto", "costa il biglietto del treno");
	data_import("domanda", "chi", "ha vinto la partita");
	data_import("domanda", "come", "si cambia una ruota");
	data_import("domanda", "che", "tempo farà domani");
	data_import("domanda", "dove", "posso trovare un ristorante aperto");
	data_import("domanda", "quando", "è il mio compleanno");
	data_import("domanda", "come", "imposto un timer sul cellulare");
	data_import("domanda", "perché", "la macchina non parte");
	data_import("domanda", "quanto", "è alto il monte Bianco");
	data_import("domanda", "chi", "è il presidente italiano");
	data_import("domanda", "dove", "posso andare in vacanza d’estate");
	data_import("domanda", "come", "preparo un caffè corretto");
	data_import("domanda", "che", "giorno è oggi");
	data_import("domanda", "quando", "iniziano le vacanze scolastiche");
	data_import("domanda", "perché", "i fiori appassiscono");
	data_import("domanda", "quanto", "pesa un pacco standard");
	data_import("domanda", "di che", "colore è il tavolo");
	data_import("domanda", "quanto", "costa il caffè");
	data_import("domanda", "come", "si prepara il caffè");
	data_import("domanda", "chi", "sei te bot");


    data_import("felice", "emo", "Oggi ho ricevuto una bellissima notizia che mi ha riempito di gioia");
	data_import("felice", "emo","Il sorriso dei bambini è il regalo più bello che la vita possa offrire");
	data_import("felice", "emo","Mi sento grato per ogni piccolo momento di felicità che incontro ogni giorno");
	data_import("felice", "emo","La luce del sole al mattino mi dà una sensazione di serenità e speranza");
	data_import("felice", "emo","Un abbraccio sincero può trasformare una giornata grigia in una giornata luminosa");
	data_import("felice", "emo","Il profumo dei fiori in primavera mi ricorda la bellezza della vita");
	data_import("felice", "emo","Passare del tempo con gli amici mi fa sentire amato e apprezzato");
	data_import("felice", "emo","Ogni passo verso i miei obiettivi mi dà una sensazione di realizzazione");
	data_import("felice", "emo","La musica che amo mi solleva lo spirito e mi fa sentire vivo");
	data_import("felice", "emo","Guardare un tramonto mozzafiato mi riempie di gratitudine per il mondo");
	
	data_import("triste", "emo","La pioggia incessante mi fa sentire malinconico e solo");
	data_import("triste", "emo","La perdita di una persona cara lascia un vuoto difficile da colmare");
	data_import("triste", "emo","Le parole non dette spesso pesano più di quelle pronunciate");
	data_import("triste", "emo","Il silenzio di una stanza vuota amplifica la solitudine nel cuore");
	data_import("triste", "emo","Ricordare momenti felici ormai lontani può scatenare una tristezza profonda");
	data_import("triste", "emo","Le lacrime che scendono senza motivo sembrano raccontare storie non dette");
	data_import("triste", "emo","La fine di un capitolo importante della vita lascia sempre un senso di smarrimento");
	data_import("triste", "emo","Guardare vecchie fotografie può riportare alla mente dolci ricordi e tristezza");
	data_import("triste", "emo","La solitudine in mezzo alla folla è una sensazione difficile da spiegare");
	data_import("triste", "emo","Le parole di conforto a volte non riescono a lenire il dolore interiore");
	
	data_import("preoccupato", "emo","Il futuro incerto mi tiene sveglio la notte, pensando a cosa mi aspetta");
	data_import("preoccupato", "emo","Le sfide quotidiane sembrano accumularsi, creando un senso di ansia");
	data_import("preoccupato", "emo","Le scelte che devo fare mi pongono davanti a dubbi e incertezze");
	data_import("preoccupato", "emo","La salute di un familiare mi preoccupa più di quanto vorrei ammettere");
	data_import("preoccupato", "emo","Le difficoltà finanziarie rendono ogni spesa una decisione ponderata");
	data_import("preoccupato", "emo","Le notizie negative sembrano prevalere, aumentando il senso di apprensione");
	data_import("preoccupato", "emo","Il cambiamento imminente mi fa sentire vulnerabile e insicuro");
	data_import("preoccupato", "emo","Le responsabilità che mi assumo mi pongono sotto una pressione costante");
	data_import("preoccupato", "emo","Le aspettative degli altri mi fanno temere di non essere all'altezza");
	data_import("preoccupato", "emo","La paura di fallire mi impedisce di agire con la determinazione necessaria");


	printf("\n");
	printf("\n");
	printf("\n");
	data_import_soluz("scuola", "fa parte", "il titolo migliore fa parte della scuola di eccellenza");
	data_import_soluz("biblioteca", "è studiare", "la biblioteca è il posto ideale per studiare in silenzio");
	data_import_soluz("email", "scrivere usare", "per scrivere un'email formale usa un tono cortese e chiaro");
	data_import_soluz("treno", "arriva", "il treno regionale arriva alle 18:45");
	data_import_soluz("pane", "servono cuocere", "servono circa 30 minuti per cuocere il pane");
	data_import_soluz("ufficio", "lavora", "in quell’ufficio lavora il signor Rossi");
	data_import_soluz("computer", "riavvia controlla", "se il computer non funziona riavvialo o controlla la connessione");
	data_import_soluz("musica", "ascolto scegliere", "ascolto musica pop e jazz di solito");
	data_import_soluz("libro", "puoi comprare", "puoi comprare un libro economico in libreria o online");
	data_import_soluz("messaggio", "scrivere inviare", "per inviare un messaggio su WhatsApp scrivi il testo e premi invia");
	data_import_soluz("lezione", "inizia", "la lezione di matematica inizia alle 9:00");
	data_import_soluz("caffè", "costa", "un caffè al bar costa circa 1 euro");
	data_import_soluz("canzone", "ha scritto", "questa canzone è stata scritta da Lucio Dalla");
	data_import_soluz("telefono", "rispondere controllare", "se l’amico non risponde controlla se ha il telefono scarico");
	data_import_soluz("tempo", "c’è", "oggi nella mia città c’è il sole");
	data_import_soluz("professione", "faccio", "faccio l’insegnante di lingue");
	data_import_soluz("parco", "passeggiare", "puoi passeggiare nel parco vicino al centro");
	data_import_soluz("pasta", "preparare", "per preparare la pasta al forno cuoci la pasta e aggiungi besciamella");
	data_import_soluz("film", "finisce", "il film di stasera finisce alle 22:15");
	data_import_soluz("email", "verifica", "verifica le impostazioni antispam nella tua casella di posta");
	data_import_soluz("computer", "pesa", "un computer portatile medio pesa circa 1,5 kg");
	data_import_soluz("pasta", "cuocere", "puoi cuocere la pasta in acqua bollente salata");
	data_import_soluz("pane", "comprare", "puoi comprare il pane fresco dal fornaio vicino casa");
	data_import_soluz("film", "inizia", "il film stasera inizia alle 20:30");
	data_import_soluz("piove", "piove", "oggi piove, porta l’ombrello");
	data_import_soluz("treno", "costa", "il biglietto del treno costa circa 12 euro");
	data_import_soluz("partita", "ha vinto", "la Juventus ha vinto la partita");
	data_import_soluz("ruota", "cambiare", "per cambiare una ruota solleva l’auto e sostituiscila");
	data_import_soluz("tempo", "sarà", "domani il tempo sarà sereno con qualche nuvola");
	data_import_soluz("ristorante", "trovare", "puoi trovare un ristorante aperto dalle 12 alle 15");
	data_import_soluz("compleanno", "è controllare", "il tuo compleanno è segnato nel calendario, controlla la data");
	data_import_soluz("timer", "impostare premere", "per impostare un timer scegli ore e minuti e premi start");
	data_import_soluz("macchina", "verificare", "se la macchina non va prova a verificare la batteria o la benzina");	
	data_import_soluz("monte Bianco", "è", "il monte Bianco è alto 4.809 metri");
	data_import_soluz("presidente", "è", "il presidente italiano è Sergio Mattarella");
	data_import_soluz("vacanza", "andare", "puoi andare in vacanza al mare in estate o in montagna in inverno");
	data_import_soluz("caffè", "preparare aggiungere", "per preparare un caffè corretto aggiungi un po’ di liquore all’espresso");
	data_import_soluz("giorno", "è", "oggi è sabato");
	data_import_soluz("vacanze", "iniziano", "le vacanze scolastiche iniziano il 10 luglio");
	data_import_soluz("pacco", "pesa", "un pacco standard pesa circa 2 chilogrammi");
	data_import_soluz("tavolo","è fatto","il tavolo è fatto di legno");
	data_import_soluz("mele","sono","le mele sono rosse verdi o gialle");
	data_import_soluz("mele","possono essere","le mele possono essere di colore rosse verdi o gialle");
	data_import_soluz("fiori", "appassiscono innaffiare", "i fiori appassiscono se non li innaffi o non ricevono luce");
	data_import_soluz("messaggio", "si manda", "un messaggio si manda con whatsapp");
	data_import_soluz("caffè","costa","il caffe costa circa 2euro");
	data_import_soluz("tu","sono","io sono un bot fatto da un matto stanco");
	data_import_soluz("sole","è","il sole è colorato di giallo");
	data_import_soluz("auto","è","auto è del colore che ti piace");
	data_import_soluz("libro","leggere","ti consiglio di leggere il piccolo principe");
	
}

void debug(int x){
	if(x){
		printf("numero domande:%d \n",paura-1);
		printf("numero non domande:%d \n",j);
		printf("risposte imparate:%d \n",gey-1);
		
		int kke;
		scanf("%d",&kke);
		stampa_frase_specifica(kke);

		printf("\n");
	
		int keke;
		scanf("%d",&keke);
		rispondi(keke);
	}
}

int main(){
	system("chcp 65001");
	system("cls");
	printf("want debug? 1 yes     0 no"); printf("\n"); scanf("%d",&debugg); int lalla=9;
	learn();
	if(!debugg)system("cls");
	ghig: ;
	if(lalla!=9) {	printf("want debug? 1 yes     0 no"); printf("\n"); scanf("%d",&debugg); if(!debugg) system("cls"); }
	write_question();
	debug(debugg); //0 è falso
	
	if(stop!=67){
		int indice_domanda_fatta=paura-1;
		int indice_risposte_imparate=gey-1;
	
		printf("\n");
		
		int risposta_probabile;
		risposta_probabile = confronta_domanda(indice_domanda_fatta,indice_risposte_imparate);
		if(debugg)printf("\nindice risposta probabile: %d",risposta_probabile);
		rispondi(risposta_probabile);
	}
	lalla=8;
	goto ghig;
	return 0;
	
}
