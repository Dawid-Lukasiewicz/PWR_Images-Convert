#include"Funkcje.h"

void negatyw(Obraz *obr, char w_koloru ) {
  int i, j;

  if(obr->znak == '2'){
  for(i=0;i<obr->wymy;i++) {
    for(j=0;j<obr->wymx;j++) {
    obr->obraz_pgm[i][j] = obr->szarosci - obr->obraz_pgm[i][j];
      }
    }
  }
/*DLA P3*/
else{
      /*CZERWONY*/
	if(w_koloru == 'r' || w_koloru == 'x'){
		for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
				obr->R[i][j] = obr->szarosci - obr->R[i][j];
			}
		}
	}
	/*ZIELONY*/
	if(w_koloru == 'g' || w_koloru == 'x'){
		for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
			     obr->G[i][j] = obr->szarosci - obr->G[i][j];
			}
		}
	}	
	/*NIEBIESKI*/
	if(w_koloru == 'b' || w_koloru == 'x'){
	   for(i=0;i<obr->wymy;i++) {
	       for(j=0;j<obr->wymx;j++) {
		      obr->B[i][j] = obr->szarosci - obr->B[i][j];
		  }
	   }
	}	
}
}

void konwersja(Obraz *obr) {
      int i,j;
      obr->znak='2';
  obr->obraz_pgm=malloc(obr->wymy*sizeof(int*));
   for(i=0; i<obr->wymy;i++)
    obr->obraz_pgm[i]=malloc(obr->wymx*sizeof(int));

  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obr->wymy;i++) {
    for (j=0;j<obr->wymx;j++) {
    obr->obraz_pgm[i][j]=(obr->R[i][j]+obr->G[i][j]+obr->B[i][j])/3.0;
    }
  }


   for(i=0; i<obr->wymy;i++)
    free(obr->R[i]);

      free(obr->R);

   for(i=0; i<obr->wymy;i++)
    free(obr->G[i]);

      free(obr->G);


   for(i=0; i<obr->wymy;i++)
    free(obr->B[i]);

      free(obr->B);


}

void progowanie(Obraz *obr, int prog, char w_koloru) {/*MAŁO EFEKTYWNIE ZARZĄDZANE ZMIENNE*/
  int i, j, granica, piksel;

  if(obr->znak == '2'){

        granica = obr->szarosci * (prog/100.0);
      
        for(i=0;i<obr->wymy;i++) {
        for(j=0;j<obr->wymx;j++) {

          piksel = obr->obraz_pgm[i][j];

            if(granica < piksel)
                obr->obraz_pgm[i][j] = obr->szarosci;

            else
                obr->obraz_pgm[i][j] = 0;
      }
    }
  }
/*DLA P3*/
else{
	/*CZERWONY*/
	if(w_koloru == 'x' || w_koloru == 'r'){
        
        granica = obr->szarosci * (prog/100.0);
        
		for(i=0;i<obr->wymy;i++) {
		for(j=0;j<obr->wymx;j++) {

        piksel = obr->R[i][j];

            if(granica < piksel)
	           obr->R[i][j] = obr->szarosci;

	       else
	           obr->R[i][j] = 0;
		}
	}
}
	/*ZIELONY*/
	if(w_koloru == 'x' || w_koloru == 'g'){
        
        granica = obr->szarosci * (prog/100.0);
        
		for(i=0;i<obr->wymy;i++) {
		for(j=0;j<obr->wymx;j++) {

        piksel = obr->G[i][j];

            if(granica < piksel)
	           obr->G[i][j] = obr->szarosci;

            else
	           obr->G[i][j] = 0;
		}
	}
}
	/*NIEBIESKI*/
	if(w_koloru == 'x' || w_koloru == 'b'){
        
        granica = obr->szarosci * (prog/100.0);
        
        for(i=0;i<obr->wymy;i++) {
        for(j=0;j<obr->wymx;j++) {

        piksel = obr->B[i][j];

            if(granica < piksel)
                obr->B[i][j] = obr->szarosci;

            else
                obr->B[i][j] = 0;
				}
			}
		}
	}
}

void konturowanie(Obraz *obr, char w_koloru) {
  int i, j;
/*DZIWNY PRZYPADEK NARUSZENIA PAMIĘCI->USUNIETY KOSZTEM ZREZYGNOWANIA Z POPRAWNOŚCI WZORU!!!*/
  if(obr->znak == '2'){
  for(i=0;i<obr->wymy;i++){
    for(j=0;j<obr->wymx;j++){
		if(i==obr->wymy && j==obr->wymx)
			obr->obraz_pgm[i][j] = abs(obr->obraz_pgm[i-1][j] - obr->obraz_pgm[i][j]) + abs(obr->obraz_pgm[i][j-1] - obr->obraz_pgm[i][j]);
		else if(i==obr->wymy)	{
		  obr->obraz_pgm[i][j] = abs(obr->obraz_pgm[i-1][j] - obr->obraz_pgm[i][j]) + abs(obr->obraz_pgm[i][j+1] - obr->obraz_pgm[i][j]);
		}
		else if(j==obr->wymx)
		  obr->obraz_pgm[i][j] = abs(obr->obraz_pgm[i+1][j] - obr->obraz_pgm[i][j]) + abs(obr->obraz_pgm[i][j-1] - obr->obraz_pgm[i][j]);
		else	{
			obr->obraz_pgm[i][j] = abs(obr->obraz_pgm[i/*+1*/][j] - obr->obraz_pgm[i][j]) + abs(obr->obraz_pgm[i][j+1] - obr->obraz_pgm[i][j]);
		}
      }
    }
  }
  /*DLA P3*/
  else{
	/*CZERWONY*/
	if(w_koloru == 'x' || w_koloru == 'r'){
		for(i=0;i<obr->wymy;i++){
			for(j=0;j<obr->wymx;j++){
				if(i==obr->wymy && j==obr->wymx){
					obr->R[i][j] = abs(obr->R[i-1][j] - obr->R[i][j]) + abs(obr->R[i][j-1] - obr->R[i][j]);
				}
				else if(i==obr->wymy){
					obr->R[i][j] = abs(obr->R[i-1][j] - obr->R[i][j]) + abs(obr->R[i][j+1] - obr->R[i][j]);
				}
				else if(j==obr->wymx){
					obr->R[i][j] = abs(obr->R[i+1][j] - obr->R[i][j]) + abs(obr->R[i][j-1] - obr->R[i][j]);
				}
				else{
					obr->R[i][j] = abs(obr->R[i/*+1*/][j] - obr->R[i][j]) + abs(obr->R[i][j+1] - obr->R[i][j]);
				}
			}
		}
	}
	/*ZIELONY*/
	if(w_koloru == 'x' || w_koloru == 'g'){
		for(i=0;i<obr->wymy;i++){
			for(j=0;j<obr->wymx;j++){
				if(i==obr->wymy && j==obr->wymx){
					obr->G[i][j] = abs(obr->G[i-1][j] - obr->G[i][j]) + abs(obr->G[i][j-1] - obr->G[i][j]);
				}
				else if(i==obr->wymy){
					obr->G[i][j] = abs(obr->G[i-1][j] - obr->G[i][j]) + abs(obr->G[i][j+1] - obr->G[i][j]);
				}
				else if(j==obr->wymx){
					obr->G[i][j] = abs(obr->G[i+1][j] - obr->G[i][j]) + abs(obr->G[i][j-1] - obr->G[i][j]);
				}
				else{
					obr->G[i][j] = abs(obr->G[i/*+1*/][j] - obr->G[i][j]) + abs(obr->G[i][j+1] - obr->G[i][j]);
				}
			}
		}
	}
    /*NIEBIESKI*/
	if(w_koloru == 'x' || w_koloru == 'b'){
		for(i=0;i<obr->wymy;i++){
			for(j=0;j<obr->wymx;j++){
				if(i==obr->wymy && j==obr->wymx){
					obr->B[i][j] = abs(obr->B[i-1][j] - obr->B[i][j]) + abs(obr->B[i][j-1] - obr->B[i][j]);
				}
				else if(i==obr->wymy){
					obr->B[i][j] = abs(obr->B[i-1][j] - obr->B[i][j]) + abs(obr->B[i][j+1] - obr->B[i][j]);
				}
				else if(j==obr->wymx){
					obr->B[i][j] = abs(obr->B[i+1][j] - obr->B[i][j]) + abs(obr->B[i][j-1] - obr->B[i][j]);
				}
				else{
				obr->B[i][j] = abs(obr->B[i/*+1*/][j] - obr->B[i][j]) + abs(obr->B[i][j+1] - obr->B[i][j]);
				}
			}
		}
	}
  }
}

void roz_histogramu(Obraz *obr, char w_koloru ){
  int i, j;
  int min, max;
  int minR, minG, minB;
  int maxR, maxG, maxB;

  if(obr->znak == '2'){
      
    min = obr->obraz_pgm[0][0];
    max = obr->obraz_pgm[0][0];
      
    for(i=0;i<obr->wymy;i++) {
        for(j=0;j<obr->wymx;j++) {

        if(min > obr->obraz_pgm[i][j])
            min = obr->obraz_pgm[i][j];

        if(max < obr->obraz_pgm[i][j])
            max = obr->obraz_pgm[i][j];
    }
}

  for(i=0;i<obr->wymy;i++) {
    for(j=0;j<obr->wymx;j++) {
      obr->obraz_pgm[i][j] = (obr->obraz_pgm[i][j] - min) * (obr->szarosci/(max - min));
            }
        }
    }
    /*DLA P3*/
    else{
        
        maxR = obr->R[0][0];
        maxG = obr->G[0][0];
        maxB = obr->B[0][0];
        minR = obr->R[0][0];
        minG = obr->G[0][0];
        minB = obr->B[0][0];
        
		/*CZERWONY*/
		if(w_koloru == 'x' || w_koloru == 'r'){
			for(i=0;i<obr->wymy;i++) {
				for(j=0;j<obr->wymx;j++) {
                    
				if(minR > obr->R[i][j])
					minR = obr->R[i][j];
				if(maxR < obr->R[i][j])
					maxR = obr->R[i][j];
				}
			}
			for(i=0;i<obr->wymy;i++) {
				for(j=0;j<obr->wymx;j++) {
					obr->R[i][j] = (obr->R[i][j] - minR) * (obr->szarosci/(maxR - minR));
				}
			}
		}
		/*ZIELONY*/
		if(w_koloru == 'x' || w_koloru == 'g'){
			for(i=0;i<obr->wymy;i++) {
				for(j=0;j<obr->wymx;j++) {
                    
					if(minG > obr->G[i][j])
						minG = obr->G[i][j];
					if(maxG < obr->G[i][j])
						maxG = obr->G[i][j];
				    
                }
			}
			for(i=0;i<obr->wymy;i++) {
				for(j=0;j<obr->wymx;j++) {
					obr->G[i][j] = (obr->G[i][j] - minG) * (obr->szarosci/(maxG - minG));
				}
			}
		}
		/*NIEBIESKI*/
		if(w_koloru == 'x' || w_koloru == 'b'){
			for(i=0;i<obr->wymy;i++) {
				for(j=0;j<obr->wymx;j++) {
                    
					 if(minB > obr->B[i][j])
						minB = obr->B[i][j];
					if(maxB < obr->B[i][j])
						maxB = obr->B[i][j];

                }
			}
			for(i=0;i<obr->wymy;i++) {
				for(j=0;j<obr->wymx;j++) {
					obr->B[i][j] = (obr->B[i][j] - minB) * (obr->szarosci/(maxB - minB));
				}
			}
		}
    }
}

void roz_poziome(Obraz *obr, char w_koloru){
  int i, j;

  if(obr->znak == '2'){
    for(i=0;i<obr->wymy;i++) {
        for(j=0;j<obr->wymx;j++) {
        if(j == 0)
        obr->obraz_pgm[i][j] = (1/3.0) * (obr->obraz_pgm[i][j] + obr->obraz_pgm[i][j] + obr->obraz_pgm[i][j+1]);

        else if(j == obr->wymx)
       	obr->obraz_pgm[i][j] = (1/3.0) * (obr->obraz_pgm[i][j-1] + obr->obraz_pgm[i][j] + obr->obraz_pgm[i][j]);

        else
        obr->obraz_pgm[i][j] = (1/3.0) * (obr->obraz_pgm[i][j-1] + obr->obraz_pgm[i][j] + obr->obraz_pgm[i][j+1]);
            }
        }
    }
	/*DLA P3*/
    else{
		/*CZERWONY*/
		if(w_koloru == 'x' || w_koloru == 'r'){
			for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
			if(j == 0)
				obr->R[i][j] = (1/3.0) * (obr->R[i][j] + obr->R[i][j] + obr->R[i][j+1]);
			else if(j == obr->wymx)
				obr->R[i][j] = (1/3.0) * (obr->R[i][j-1] + obr->R[i][j] + obr->R[i][j]);
			else
				obr->R[i][j] = (1/3.0) * (obr->R[i][j-1] + obr->R[i][j] + obr->R[i][j+1]);
			}
			}
		}
		/*ZIELONY*/
		if(w_koloru == 'x' || w_koloru == 'g'){
			for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
			if(j == 0)
				obr->G[i][j] = (1/3.0) * (obr->G[i][j] + obr->G[i][j] + obr->G[i][j+1]);
			else if(j == obr->wymx)
				obr->G[i][j] = (1/3.0) * (obr->G[i][j-1] + obr->G[i][j] + obr->G[i][j]);
			else
				obr->G[i][j] = (1/3.0) * (obr->G[i][j-1] + obr->G[i][j] + obr->G[i][j+1]);
			}
			}
		}
		/*NIEBIESKI*/
		if(w_koloru == 'x' || w_koloru == 'b'){
			for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
			if(j == 0)
				obr->B[i][j] = (1/3.0) * (obr->B[i][j] + obr->B[i][j] + obr->B[i][j+1]);
			else if(j == obr->wymx)
				obr->B[i][j] = (1/3.0) * (obr->B[i][j-1] + obr->B[i][j] + obr->B[i][j]);
			else
				obr->B[i][j] = (1/3.0) * (obr->B[i][j-1] + obr->B[i][j] + obr->B[i][j+1]);
			}
			}
		}
	}
}

void roz_pionowe(Obraz *obr, char w_koloru){
  int i, j;

	if(obr->znak == '2'){
		for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
				if(i == 0)
					obr->obraz_pgm[i][j] = (1/3.0) * (obr->obraz_pgm[i][j] + obr->obraz_pgm[i][j] + obr->obraz_pgm[i+1][j]);

					else if(i == obr->wymy-1)
					obr->obraz_pgm[i][j] = (1/3.0) * (obr->obraz_pgm[i-1][j] + obr->obraz_pgm[i][j] + obr->obraz_pgm[i][j]);

					else
					obr->obraz_pgm[i][j] = (1/3.0) * (obr->obraz_pgm[i-1][j] + obr->obraz_pgm[i][j] + obr->obraz_pgm[i+1][j]);
						}
					}
	}
    /*DLA P3*/
	else{
		/*CZERWONY*/
		if(w_koloru == 'x' || w_koloru == 'r'){
		for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
				if(i == 0)
					obr->R[i][j] = 1/3.0 * (obr->R[i][j] + obr->R[i][j] + obr->R[i+1][j]);
				else if(i == obr->wymy-1)
					obr->R[i][j] = 1/3.0 * (obr->R[i][j] + obr->R[i][j] + obr->R[i-1][j]);
				else
					obr->R[i][j] = 1/3.0 * (obr->R[i-1][j] + obr->R[i][j] + obr->R[i+1][j]);
			}
		}
	}
		/*ZIELONY*/
		if(w_koloru == 'x' || w_koloru == 'g'){
		for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
				if(i == 0)
					obr->G[i][j] = 1/3.0 * (obr->G[i][j] + obr->G[i][j] + obr->G[i+1][j]);
				else if(i == obr->wymy-1)
					obr->G[i][j] = 1/3.0 * (obr->G[i][j] + obr->G[i][j] + obr->G[i-1][j]);
				else
					obr->G[i][j] = 1/3.0 * (obr->G[i-1][j] + obr->G[i][j] + obr->G[i+1][j]);
			}
		}
	}
		/*NIEBIESKI*/
		if(w_koloru == 'x' || w_koloru == 'b'){
		for(i=0;i<obr->wymy;i++) {
			for(j=0;j<obr->wymx;j++) {
				if(i == 0)
					obr->B[i][j] = 1/3.0 * (obr->B[i][j] + obr->B[i][j] + obr->B[i+1][j]);
				else if(i == obr->wymy-1)
					obr->B[i][j] = 1/3.0 * (obr->B[i][j] + obr->B[i][j] + obr->B[i-1][j]);
				else
					obr->B[i][j] = 1/3.0 * (obr->B[i-1][j] + obr->B[i][j] + obr->B[i+1][j]);
			}
		}
		}
	}
}

void zmiana_poz(Obraz *obr, char w_koloru, int czern, int biel){
    int i, j;
    if(czern < biel){
        czern = ((float)czern/100.0)*obr->szarosci;
        biel = ((float)biel/100.0)*obr->szarosci;

        if(obr->znak == '2'){
            for(i=0;i<obr->wymy;i++) {
                for(j=0;j<obr->wymx;j++) {
                    if(obr->obraz_pgm[i][j] <= czern){
                        obr->obraz_pgm[i][j] = 0;
                    }
                    else if(obr->obraz_pgm[i][j] >= biel ){
                        obr->obraz_pgm[i][j] = obr->szarosci;
                    }
                    else{
                        obr->obraz_pgm[i][j] =(obr->obraz_pgm[i][j] - czern)*(obr->szarosci/(biel-czern));
                    }
                }
            }
        }
        /*DLA P3*/
        else{
            /*CZERWONY*/
            if(w_koloru == 'x' || w_koloru == 'r'){
                for(i=0;i<obr->wymy;i++) {
                    for(j=0;j<obr->wymx;j++) {
                        if(obr->R[i][j] <= czern)
                            obr->R[i][j] = 0;
                        else if(obr->R[i][j] >= biel )
                            obr->R[i][j] = obr->szarosci;
                        else{
                            obr->R[i][j] = (obr->R[i][j] -czern)*(obr->szarosci)/(biel-czern);
                        }
                    }
                }
            }
            /*ZIELONY*/
            if(w_koloru == 'x' || w_koloru == 'g'){
                for(i=0;i<obr->wymy;i++) {
                    for(j=0;j<obr->wymx;j++) {
                        if(obr->G[i][j] <= czern)
                            obr->G[i][j] = 0;
                        else if(obr->G[i][j] >= biel )
                            obr->G[i][j] = obr->szarosci;
                        else{
                            obr->G[i][j] = (obr->G[i][j] -czern)*(obr->szarosci)/(biel-czern);
                        }
                    }
                }
            }
            /*NIEBIESKI*/
            if(w_koloru == 'x' || w_koloru == 'b'){
                for(i=0;i<obr->wymy;i++) {
                    for(j=0;j<obr->wymx;j++) {
                        if(obr->B[i][j] <= czern)
                            obr->B[i][j] = 0;
                        else if(obr->B[i][j] >= biel )
                            obr->B[i][j] = obr->szarosci;
                        else{
                            obr->B[i][j] = (obr->B[i][j] -czern)*(obr->szarosci)/(biel-czern);
                        }
                    }
                }
            }
        }
    }
    else
        fprintf(stderr, "Złe parametry czerni i bieli. Parametr czerni powinien być mniejszy od bieli\n");
}