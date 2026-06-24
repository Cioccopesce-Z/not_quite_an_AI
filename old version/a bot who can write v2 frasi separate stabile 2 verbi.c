#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 10000 // indicatore della posizione nel vocabolario della parola
#define MAX_LEN 100 // lettere della parola --> per ciascun indice ci sono massimo 100 lettere
                      //(indicata dalla parola chiave)  può essere fatta
#define data 10
#define verbii 1000
#define indicefrase 500

/*
 formato dati per fargli imparare
 
 			"domanda", qual la capitale di italia è roma
 			   ^     ^  ^  ^        ^        ^        ^
 			[cate    d  i  d   [key word]  [ass      [data]
 			goria]   i  d  i                cio
 				     v  x  v                ties]
 				   
 				   
 			"domanda", come la macchina si rompe perche ha il motore
 			   ^     ^  ^  ^        ^        ^                  ^
 			[cate    d  i  d   [key word]  [ass              [data]
 			goria]   i  d  i                cio
 				     v  x  v                ties]

			una volta specificato che si parla di una domanda e di che categoria(quale,come,perche) ogni parola se non gia ppresente 
			viene aggiunta al vocabolario tramite la funzione trova_parola() che restituisce l`indice il quale sara salvato in idx_quest 
			nell`array domande[idx_quest][key_words][associaties][data] in modo che quando sara letto l'input dell`utente ogni parola, divisa
			da uno spazio, sara cercata nel vocabolario esempio:       quale è la capitale dell italia  -->  token = trova_parola(quale) --> token = 5
			mettiamo caso che token sia 5 e che per ciasuna categoria(domande, felice, triste, rabbia) sia presente 5,
			
			in domande[5] sara fatta 
			la somma del numero di celle tra le 50 in [key_words] (#define key_words 50) che contengono un valore diverso da 0, questo dato sara salvato
			in score_domande (integer), stessa cosa verra fatta per invece la somma dei valori di felice[5] che saranno salvati in score_felice (integer),
			e per ciascuna delle altre categorie. Questi valori verranno confrontati e sara richiamata la funzione per cui il score_"categoria" è il maggiore
			  

*/

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

    printf("Frase: \"%s\"\n", frase);
    if (score_felice >= score_triste && score_felice >= score_preoccupato)
        printf("FELICE\n\n");
    else if (score_triste >= score_felice && score_triste >= score_preoccupato)
        printf("TRISTE\n\n");
    else
        printf("PREOCCUPATO\n\n");
}


int lexicon[verbii];
// divisione in verbo1 verbo(2)2 nome3 prefisso4
void gram(const char *veer, const char *jet ){
	if(strcmp(jet, "verbo")==0) { lexicon[trova_parola(veer)]=1; }
	if(strcmp(jet, "nome")==0) { lexicon[trova_parola(veer)]=2; }
	if(strcmp(jet, "prefisso")==0) { lexicon[trova_parola(veer)]=3;}	
}

int search_gram(const char *lasse){
	return lexicon[trova_parola(lasse)];
}
char frase[indicefrase][data][15];
int j=0;
int fag=0;

void analyze_domande(const char *parol, const char *parola_chiave){
	//printf("parola: %s       indice parola in analyze: %d        parola ciave: %s \n",parol,trova_parola(parol),parola_chiave);
	//salva in frase la frase semplificata come stringa
	strcpy(frase[j][0], parola_chiave);
	if(search_gram(parol)==1 && fag==1) { strcpy(frase[j][2], parol); }
	if(search_gram(parol)==1 && fag==0) { strcpy(frase[j][1], parol); fag=1; }
	if(search_gram(parol)==2 ) strcpy(frase[j][3], parol);
	if(search_gram(parol)==3 ) strcpy(frase[j][4], parol);
}

void stampa_domanda_sempli(){
	
		for(int i=0;i<=4;i++){
			if(i==2 && frase[j][i]!=0){
				printf("%s ",frase[j][i]);
			} else {
				printf("%s ",frase[j][i]);
			}
		
	}
	printf("\n");
}

int fla=0;
void call_frase(const char *cat, const char *valla){
	
	if(strcmp(cat,"domanda")==0) {stampa_domanda_sempli();} // viene eseguito quando si importa una domanda
	if(strcmp(cat,"domanda")!=0 && fla==1) classifica(valla);/*qui dentro viene eseguito	solo quando la frase presa non è una domanda*/
}




void data_import(const char *categoria, const char *idxx, const char *frase){
	
	
	//si ripete per ogni frase
	
	
	char s[128];
	strcpy( s, frase);
	char *tok = strtok(s, " ");
	
	fag=0;
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
	j++;
}

void dividi_domanda(char *kollo){
	char helloworld[122];
	char *toke;
	toke = strtok(kollo, " ");
	char *resto = kollo+strlen(toke)+1;
	strcpy(helloworld,resto);
	
	if(helloworld[strlen(helloworld)-1]=='?'){
		helloworld[strlen(helloworld)-1]='\0';
	}
	
	//printf(" 1 %s 2 %s \n",toke,helloworld);
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
		printf("\n non è una domanda \n");
		classifica(import);
	}
    
}


void stampa_frase_specifica(int kek){
	printf("\n");
	for(int i=0; i<=4; i++){
		printf("%s ",frase[kek][i]);
	}
}


void data_import_soluz(){
}

void learn(){
	
// --- VERBI ---
gram("prendere", "verbo");
gram("scade", "verbo");
gram("si", "verbo");
gram("rompe", "verbo");
gram("cuocere", "verbo");
gram("mangiare", "verbo");
gram("inizia", "verbo");
gram("posso", "verbo");
gram("può", "verbo");
gram("piove", "verbo");
gram("costa", "verbo");
gram("ha", "verbo");
gram("vinto", "verbo");
gram("cambia", "verbo");
gram("farà", "verbo");
gram("trovare", "verbo");
gram("è", "verbo");
gram("imposto", "verbo");
gram("parte", "verbo");
gram("andare", "verbo");
gram("preparo", "verbo");
gram("iniziano", "verbo");
gram("appassiscono", "verbo");
gram("vedere", "verbo");
gram("pesa", "verbo");
gram("arriva", "verbo");
gram("finiscono", "verbo");
gram("studiare", "verbo");
gram("lavorare", "verbo");
gram("telefonare", "verbo");
gram("arrivare", "verbo");
gram("filmare", "verbo");
gram("passeggiare", "verbo");
gram("correre", "verbo");
gram("leggere", "verbo");
gram("scrivere", "verbo");
gram("ascolti", "verbo");
gram("invio", "verbo");
gram("imposto", "verbo");
gram("preparo", "verbo");
gram("funziona", "verbo");
gram("fai", "verbo");

// --- NOMI ---
gram("latte", "nome");
gram("film", "nome");
gram("pasta", "nome");
gram("pane", "nome");
gram("notizia", "nome");
gram("macchina", "nome");
gram("biglietto", "nome");
gram("treno", "nome");
gram("partita", "nome");
gram("ruota", "nome");
gram("tempo", "nome");
gram("ristorante", "nome");
gram("compleanno", "nome");
gram("timer", "nome");
gram("monte", "nome");
gram("Bianco", "nome");
gram("presidente", "nome");
gram("vacanza", "nome");
gram("caffè", "nome");
gram("giorno", "nome");
gram("vacanze", "nome");
gram("fiori", "nome");
gram("pacco", "nome");
gram("professione", "nome");
gram("meteo", "nome");
gram("email", "nome");
gram("messaggio", "nome");
gram("computer", "nome");
gram("telefono", "nome");
gram("amico", "nome");
gram("biblioteca", "nome");
gram("scuola", "nome");
gram("ufficio", "nome");
gram("città", "nome");
gram("musica", "nome");
gram("canzone", "nome");
gram("libro", "nome");
gram("lezione", "nome");
gram("spam", "nome");
gram("parco", "nome");
gram("bar", "nome");
gram("matematica", "nome");
gram("ufficio", "nome");

// --- PREFISSI / PARTICELLE / ARTICOLI / AVVERBI INTERROGATIVI ---
gram("il", "prefisso");
gram("la", "prefisso");
gram("le", "prefisso");
gram("i", "prefisso");
gram("un", "prefisso");
gram("una", "prefisso");
gram("in", "prefisso");
gram("a", "prefisso");
gram("da", "prefisso");
gram("per", "prefisso");
gram("su", "prefisso");
gram("con", "prefisso");
gram("nello", "prefisso");
gram("dove", "prefisso");
gram("quando", "prefisso");
gram("come", "prefisso");
gram("perché", "prefisso");
gram("quanto", "prefisso");
gram("chi", "prefisso");
gram("che", "prefisso");
gram("di cosa", "prefisso");
gram("oggi", "prefisso");
gram("domani", "prefisso");
gram("stasera", "prefisso");


	
	data_import("domanda", "dove", "posso studiare in silenzio");
	data_import("domanda", "come", "si scrive un email formale");
	data_import("domanda", "quando", "arriva il treno regionale");
	data_import("domanda", "quanto", "tempo serve per cuocere il pane");
	data_import("domanda", "chi", "lavora in quell’ufficio");
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

	
	data_import_soluz("biblioteca", "studiare leggere concentrarsi", "la biblioteca è il posto ideale per studiare in silenzio");
	data_import_soluz("email", "scrivere inviare rispondere", "usa un tono formale e saluta correttamente");
	data_import_soluz("treno", "arrivare viaggiare partire", "il treno regionale arriva alle 18:45");
	data_import_soluz("pane", "cuocere impastare preparare", "ci vogliono circa 30 minuti di cottura");
	data_import_soluz("ufficio", "lavorare gestire rispondere", "in quell’ufficio lavora il signor Rossi");
	data_import_soluz("computer", "riparare controllare riavviare", "riavvia il computer o controlla la connessione");
	data_import_soluz("musica", "ascoltare scegliere ballare", "ascolto musica pop e jazz di solito");
	data_import_soluz("libro", "comprare leggere cercare", "puoi trovarlo in libreria o online");
	data_import_soluz("messaggio", "scrivere inviare leggere", "apri WhatsApp, scrivi il testo e premi invia");
	data_import_soluz("lezione", "iniziare seguire studiare", "la lezione inizia alle 9:00");
	data_import_soluz("caffè", "preparare bere offrire", "al bar costa circa 1 euro");
	data_import_soluz("canzone", "scrivere cantare ascoltare", "questa canzone è stata scritta da Lucio Dalla");
	data_import_soluz("telefono", "chiamare rispondere usare", "potrebbe essere scarico o senza campo");
	data_import_soluz("tempo", "guardare prevedere controllare", "oggi nella mia città c’è il sole");
	data_import_soluz("professione", "fare lavorare scegliere", "faccio l’insegnante di lingue");
	data_import_soluz("parco", "passeggiare correre rilassarsi", "puoi passeggiare nel parco vicino al centro");
	data_import_soluz("pasta", "preparare cuocere condire", "cuoci la pasta e mettila al forno con besciamella");
	data_import_soluz("film", "guardare vedere scegliere", "il film finisce alle 22:15");
	data_import_soluz("email", "controllare filtrare impostare", "verifica le impostazioni antispam nella casella");
	data_import_soluz("computer", "pesare confrontare acquistare", "un portatile medio pesa circa 1,5 kg");
	data_import_soluz("pasta", "bollire cuocere fare", "bollire l'acqua con il sale");
	data_import_soluz("ristorante", "mangiare ordinare cenare", "trovare un ristorante aperto dalle 12 alle 15");
	data_import_soluz("film", "guardare vedere scegliere", "il film inizia alle 20:30");
	data_import_soluz("piove", "mettere coprire proteggere", "portare l'ombrello perché piove");
	data_import_soluz("treno", "comprare viaggiare pagare", "il biglietto del treno costa 12 euro");
	data_import_soluz("partita", "giocare vincere seguire", "la Juventus ha vinto la partita");
	data_import_soluz("ruota", "cambiare svitare montare", "sollevare l'auto e cambiare la ruota");
	data_import_soluz("tempo", "controllare guardare prevedere", "domani sarà sereno con qualche nuvola");
	data_import_soluz("pane", "comprare cucinare assaggiare", "andare dal fornaio vicino casa");
	data_import_soluz("compleanno", "festeggiare ricordare preparare", "controllare la data del compleanno");
	data_import_soluz("timer", "impostare avviare fermare", "impostare ore e minuti e premere start");
	data_import_soluz("macchina", "controllare accendere riparare", "verificare batteria e benzina");
	data_import_soluz("monte Bianco", "scalare misurare ammirare", "altezza 4.809 metri");
	data_import_soluz("presidente", "identificare conoscere salutare", "il presidente è Sergio Mattarella");
	data_import_soluz("vacanza", "partire visitare rilassarsi", "andare al mare in estate o in montagna in inverno");
	data_import_soluz("caffè", "preparare servire gustare", "preparare l'espresso e aggiungere liquore");
	data_import_soluz("giorno", "controllare segnare ricordare", "oggi è sabato");
	data_import_soluz("vacanze", "iniziare pianificare organizzare", "iniziano il 10 luglio");
	data_import_soluz("fiori", "innaffiare potare curare", "mancanza d'acqua o luce fa appassire i fiori");
	data_import_soluz("pacco", "pesare spedire controllare", "pesa mediamente 2 kg");


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

}

int main(){
	learn();
	printf("\n");
	//system("cls");
	write_question();
	/*
	int keke=0;
	scanf("%d",&keke);
	stampa_frase_specifica(keke);
	*/
}
