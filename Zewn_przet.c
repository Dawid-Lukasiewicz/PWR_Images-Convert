#include"Zewn_przet.h"


int czytaj(FILE *plik_we,Obraz *obr) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego"*/
  if (fgets(buf,DL_LINII,plik_we)==NULL){   /* Wczytanie pierwszej linii pliku do bufora */
	koniec=1;                              /* Nie udalo sie? Koniec danych! */
	return(0);
	}
	//fgets(buf,DL_LINII,plik_we);
	if ((buf[0]!='P') || (buf[1]!='2' && buf[1]!='3')) {  /* Czy jest magiczne "P2 lub P3"*/
		fprintf(stderr,"Blad: To nie jest plik PGM\n");
		return(0);
	}

   obr->znak=buf[1];
  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",&obr->wymx,&obr->wymy,&obr->szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }

  if(obr->znak=='2')	{
	obr->obraz_pgm=malloc(obr->wymy*sizeof(int*));
	for(i=0; i<obr->wymy;i++)
		obr->obraz_pgm[i]=malloc(obr->wymx*sizeof(int));

	  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
	  for (i=0;i<obr->wymy;i++) {
		for (j=0;j<obr->wymx;j++) {
		  if (fscanf(plik_we,"%d",&(obr->obraz_pgm[i][j]))!=1) {
			fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
			return(0);
		  }
		}
	  }
  }
  else	{
	obr->R=malloc(obr->wymy*sizeof(int*));
	for(i=0; i<obr->wymy;i++)
	obr->R[i]=malloc(obr->wymx*sizeof(int));

	obr->G=malloc(obr->wymy*sizeof(int*));
   for(i=0; i<obr->wymy;i++)
    obr->G[i]=malloc(obr->wymx*sizeof(int));

             obr->B=malloc(obr->wymy*sizeof(int*));
   for(i=0; i<obr->wymy;i++)
    obr->B[i]=malloc(obr->wymx*sizeof(int));

  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obr->wymy;i++) {
    for (j=0;j<obr->wymx;j++) {
      if (fscanf(plik_we,"%d %d %d",&(obr->R[i][j]),&(obr->G[i][j]),&(obr->B[i][j]))!=3) {
			fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
			return(0);
      }
    }
  }
}


  return obr-> wymx * obr->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */

void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

void zapisz(FILE *plik, Obraz *obr) {
  int i, j;


  if(obr->znak=='2'){
    fprintf(plik,"P2\n");
    fprintf(plik,"%d %d %d ",obr->wymx, obr->wymy, obr->szarosci);

     for (i=0;i<obr->wymy;i++) {
       for (j=0;j<obr->wymx;j++) {

	 fprintf(plik,"%d ",obr->obraz_pgm[i][j]);
      }
    }
  }
  else
  {
    fprintf(plik,"P3\n");
    fprintf(plik,"%d %d %d ",obr->wymx, obr->wymy, obr->szarosci);

    for (i=0;i<obr->wymy;i++) {
        for (j=0;j<obr->wymx;j++) {

	       fprintf(plik,"%d %d %d ",obr->R[i][j],obr->G[i][j],obr->B[i][j]);

        }
     }
  }
}
