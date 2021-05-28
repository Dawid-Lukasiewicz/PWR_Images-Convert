/*Dawid Łukasiewicz, przetwarzanie obrazów 2 27.12.2019
 Funckcje programu mogą obsługiwać obrazy kolorowe*/

#include"Zewn_przet.h"
#include"Funkcje.h"

int main(int argc, char *argv[]) {
   Obraz obr;

  int i, numer, czern, biel;
  int odczytano = 0;
  FILE *plik, *plik_tmp;
  char w_koloru, nazwa[100];

	w_koloru = 'x';	/*JEŻELI NIE ZOSTANIE WYBRANY KONKRETNY KOLOR DO PRZETWORZENIA, WSZYSTKIE KOLORY BĘDĄ PRZETWARZANE*/
	if(--argc > 0 && argv[1][0] == '-' && argv[1][1] == 'i'){
		for(i=1; i<=argc; i++){
		if(argv[i][0] != '-'){
			printf("Niepoprawna opcja. Brakuje: '-'\n");
			return 0;
		}

	switch(argv[i][1]) {
	
	case 'm':
	if(++i <= argc){
        if(argv[i][0] != '-'){
            if(argv[i][0]!='r' && argv[i][0]!='g' && argv[i][0]!='b' && argv[i][0]!='x' && argv[i][0]!='s'){
                fprintf(stderr, "Podano złe parametry koloru\nPoprawne to: 'r', 'g', 'b' lub 's'\n'x'-Powrót do przetwarzania wszystkich kolorów\n");
                return 0;
            }
            else
                if(argv[i][0] != 's')
                    w_koloru = argv[i][0]; /*IGNOROwANE SĄ NASTEPNE LITERAŁY ZNAKOWE W TYM WIERSZU*/
                else
                    konwersja( &obr);
        }
        else{
            fprintf(stderr, "Nie podano koloru do przetwarzania\n");
            return 0;
        }
	}
	break;
/*ODCZYT*/
	case 'i':
		if(++i <= argc)	{
            if(argv[i][0] != '-'){
                plik = fopen(argv[i], "r");
                if(plik != NULL)	{
                    odczytano = czytaj(plik, &obr);
                    if (odczytano != 0) {
                        printf("Pomyslnie wczytano plik\n");
                        fclose(plik);
                    }
                }
                else{
                    fprintf(stderr, "Nieistniejący plik\n");
                    return 0;
                }
            }
            else{
                fprintf(stderr, "Nie podano nazwy pliku\n");
                return 0;
            }
                
		}
		else{
			fprintf(stderr, "Nie podano nazwy pliku\n");
			return 0;
		}
	break;

	/*WYŚWIETLANIE OBRAZU*/
    case 'd':
		if (odczytano != 0){
			plik_tmp = fopen("p_tmp", "w");
			zapisz(plik_tmp, &obr);
			fclose(plik_tmp);
			wyswietl("p_tmp");
		}

    break;

	/*ZAPIS*/
    case 'o':
		if(++i <= argc){
            if(argv[i][0] != '-'){
                plik = fopen(argv[i], "w");
                zapisz(plik, &obr);
                fclose(plik);
                printf("Pomyślnie zapisano plik pod nazwą: %s\n", argv[i]);
            }
            else{
                fprintf(stderr, "Nazwa nowego pliku nie powinna zaczynać się od '-'\n");
                return 0;
            }
		}
        else{
            fprintf(stderr, "Nie podano nazwy pod jaką chcesz zapisać obraz\n");
            return 0;
        }
    break;
 
/*NEGATYW*/
    case 'n':
		negatyw(&obr, w_koloru);
    break;

/*PROGOWANIE*/
    case 'p':
    if(++i <= argc){
        if(argv[i][0] != '-'){
            if(atoi(argv[i]) > 0 && atoi(argv[i]) < 100){
                progowanie(&obr, atoi(argv[i]), w_koloru);
            }
            else{
                fprintf(stderr, "Ppodano zły przedział progowania, powinien być mniejszy od 100 i większy od 0\n");
                return 0;
            }
        }
        else{
            fprintf(stderr, "Nie podano parametru progowania\n");
            return 0;
        }
    }
    else{
        fprintf(stderr, "Nie podano parametru progowania\n");
        return 0;
        }
    break;

/*KONTUROWANIE NARUSZENIE PAMIECI*/
    case 'k':
	konturowanie(&obr, w_koloru);
    break;

/*ROZCIĄGNIECIE HOSTOGRAMU*/
    case 'h':
	roz_histogramu(&obr, w_koloru);
	break;

/*ROZMYCIE*/
    case 'r':
    if(argv[i][2] == 'x')
        roz_poziome(&obr, w_koloru);
    else if(argv[i][2] == 'y')
        roz_pionowe(&obr, w_koloru);
    else{
        fprintf(stderr, "Złe wywołanie opcji rozmycia poziomego lub pionowego. Powinno być: '-rx- lub '-ry'\n");
        return 0;
    }        
    break;
            
/*ZMIANA POZIOMÓW*/
    case 'z':
    if(++i <= argc){
        if(argv[i][0] != '-'){
            czern = atoi(argv[i]);
            if(++i <= argc){
                if(argv[i][0] != '-'){
                    biel = atoi(argv[i]);
                    if(czern < biel && czern >= 0 && biel <= 100)
                        zmiana_poz(&obr, w_koloru, czern, biel);
                    else{
                        fprintf(stderr, "Parametr czerni powinien być mniejszy od bieli. Oba powinny znajdować się w przedziale od 0 do 100\n");
                        return 0;
                    }
                }
                else{
                    fprintf(stderr, "Nie podano parametru bieli\n");
                    return 0;
                }
            }
            else{
                fprintf(stderr, "Nie podano parametru bieli\n");
                return 0;
            }
        }
        else{
            fprintf(stderr, "Nie podano parametru czerni i bieli\n");
            return 0;
        }

    }
    else{
        fprintf(stderr, "Nie podano parametru czerni i bieli\n");
        return 0;
    }
    break;

    }
}
/*USUNIECIE PLIKU TYMCZASOWEGO*/
		sleep(1);
		system("rm p_tmp");
		return 0;
	}
/*BŁAD PLIKU*/
    else{
        fprintf(stderr, "Nie podano nazwy pliku lub sposobu wczytania pliku, powinno być: -i nazwa_pliku\n");
        return 0;
    }
}

/*Przed przystąpieniem do dokumentacji zamieszczam opis działania funnkcji, jak je wywołać i z jakimi parametrami. Na wypadek mojego złego zrozumienia opisu ze strony głównej:

-i <nazwa_pliku> Rezerwuje tablice i wczytuje do niej wartości pikseli z pliku podanego jako następny argument. W przypadku błędu program informuje czego zabrakło, a następnie zwraca wartość 0.

-o <nazwa_pliku> Zapisuje do pliku podanego jako następny argument obraz jaki znajduje się w pamięci tymczasowej. Nazwa pliku nie powinna zaczynać się od '-'. Po to aby uniknąć sytuacji gdy przez przypadek zapisujemy obraz pod nazwą opcji i pomijamy jedną z komend.

-d Wyświetla obraz. Do wyświetlenia obrazu program potrzebuje stworzenie tymczasowego pliku, który jest usuwany po zakończenia programu. Zastosowałem funkcję sleep, aby móc wyświetlić obraz zapisany do tymczasowego pliku zanim ten zostanie usunięty. Jest to niedoskonałe i toporne rozwiązanie.

-m Służy do wybrania jednego koloru który chcemy przetwarzać lub do skonwertowania obrazu do szarości. Do momentu aż program nie zostanie zakończony lub nie wywołamy owej funkcji jeszcze raz będzie przetwarzana tylko jedna z opcji. W przypadku kiedy chcemy znowu wrócić do przetwarzania wszystkich kolorów Jest możliwość zmienienia koloru lub powrotu do przetwarzania wszystkich kolorów bez potrzeby. Nie jest to jednak możliwe po skonwertowaniu obrazu do szarości. Wtedy komenda -m nic nie zmienia. W przypadku błędu program wyświetla jakie opcje są poprwane i zwraca 0.

-n Funkcja negatyw dla obrazów szarych i kolorowych.

-p <przedział progowania> Progowanie obrazu. Następny argument to parametr, który powinien być większy od 0 i mniejszy od 100. W przypadku błędu program wyświetla komunikat o poprawnym przedziale wartości progowania i zwraca 0.

-k Konturowanie obrazu.

-h Rozciągnięcie hostogramu.

-rx Rozciągnięcie poziome.

-ry Rozciągnięcie pionowe.

-z <próg_czerni><próg_bieli> Zmiana poziomów i dwa następne parametry progów. W przypadku braku któregokolwiek lub podania ich w złych przedziałach program wyświetla komunikat i zwraca 0.

DOKUMENTACJA:
Wszystkie testy były przeprowadznane na pliku kubus.pgm i kubus.ppm

TEST 1: Sprawdzenie poprawności wczytwania i wyświetlanie obrazów szarych i kolorowych

    1.Komenda: ./images2 -i kubus.pgm -d
    Wynik: Poprawne wyświetlenie szarego obrazu.

    2.Komenda: ./images2 -i kubus.ppm -d
    Wynik: Poprawne wyświetlenie szarego obrazu.

WNIOSKI: Przy poprawnie wprowadzonych danych program poprawnie odczytuje i wyświetla obraz.

TEST 2: Obsługa źle wprowadzonych danych i błędów dla odczytu.

    1.Komenda: ./images2 - kubus.pgm 
    Wynik: Wyświetlenie "Nie podano nazwy pliku lub sposobu wczytania pliku, powinno być: -i nazwa_pliku" i zakończenie działania programu.
    
    2.Komenda: ./images2 i kubus.pgm 
    Wynik: Wyświetlenie "Nie podano nazwy pliku lub sposobu wczytania pliku, powinno być: -i nazwa_pliku" i zakończenie działania programu.
    
    3.Komenda: ./images2 -i -d
    Wynik: Wyświetlenie komunikatu "Nie podano nazwy pliku" i zakończenie działania programu.
    
    4.Komenda: ./images2 -i
    Wynik:  Wyświetlenie komunikatu "Nie podano nazwy pliku" i zakończenie działania programu.
    
    5.Komenda: ./images2 -i kbs.pgm
    Wynik:  Wyświetlenie komunikatu "Nieistniejący plik" i zakończenie działania programu.
    
WNIOSKI: Program do wywołania opcji zawsze oczekuje na odpowiedni znak "flagę", czyli '-'. Potrafi rozróżnić parametr od opcji, a w przypadku braku wymaganego parametru komunikuje nas i przerywa pracę programu. Jednakże nie potrafi odczytać ze standardowego wejścia przy wpisaniu samej flagi '-'.

TEST 3: Sprawdzenie poprawności działania zapisu '-o' dla obrazów szarych i kolorowych.

    1.Komenda: ./images2 -i kubus.pgm -o kubus2.pgm
    Wynik: Program zapisał obraz w nowym pliku pod podaną nazwą i wyświetlił komunikat "Pomyślnie zapisano plik pod nazwą: kubus2.pgm".
    
    2.Komenda: ./images2 -i kubus.ppm -o kubus2.ppm
    Wynik: Program zapisał obraz w nowym pliku pod podaną nazwą i wyświetlił komunikat "Pomyślnie zapisano plik pod nazwą: kubus2.pgm".
    
WNIOSKI: Poprawnie są obsługiwane obrazy szare i kolorowe przy dobrze wprowadzonych danych.

TEST 4: Obsługa źle wprowadzonych danych i błędów dla zapisu '-o'.

    1.Komenda: ./images2 -i kubus.pgm -o -d
    Wynik: Wyświetlany jest komunikat "Nazwa nowego pliku nie powinna zaczynać się od '-'" i przerywane jest działanie.
    
    2.Komenda: ./images2 -i kubus.pgm -o
    Wynik: Wyświetlany jest komunikat "Nie podano nazwy pod jaką chcesz zapisać obraz" i przerywane jest działanie.
    
    3.Komenda: ./images2 -i kubus.ppm - kubus2.ppm
    Wynik: WYświetlany jest komunikat "Niepoprawna opcja. Brakuje: '-'" i przerywane jest działanie.
    
WNIOSKI: Poprawnie przerywa działanie w 1 i 2 przypadku. W 3 przypadku program ignoruje samotny znak '-' a dla argument 'kubus2.ppm' rozpoznaje jako próba wywołania opcji i przerywa działanie. Nie jest to do końca poprawne. Brakuje także wypisania obrazu na standardowym wyjściu.

TEST 5: Działanie negatywu '-n' dla szarych i kolorowych obrazów.

    1.Komenda: ./images2 -i kubus.pgm -n -d
    Wynik:  Wyświetlany jest obraz odpowiednio przetworzony. Porównanie z pliku pdf ze strony głównej.
    
    2.Komenda: ./images2 -i kubus.ppm -n -d
    Wynik:  Wyświetlany jest obraz, ale nie jestem w stanie porównać go z żadnym pierwowzorem.
    
WNIOSKI: Ta opcja działa poprawnie.

TEST 6: Działanie wyboru koloru '-m' i obsługa błędów przy jej wywołaniu.

    1.Komenda: ./images2 -i kubus.ppm -m r -n -d
    Wynik:  Wyświetlany jest obraz, który został przetworzony inaczej niż dla wszyskich kolorów.
    
    2.Komenda: ./images2 -i kubus.ppm -m g -n -d
    Wynik:  Wyświetlany jest obraz, który został przetworzony inaczej niż dla koloru czerwonego.
    
    3.Komenda: ./images2 -i kubus.ppm -m b -n -d
    Wynik:  Ten obraz także różni się od poprzednich.
    
    4.Komenda: ./images2 -i kubus.ppm -m s -n -d
    Wynik:  Poprawnie skonwertowany obraz do szarości, a także dalsze przetworzenie obrazu.
    
    5.Komenda: ./images2 -i kubus.ppm -m s -o kubus3.pgm
    
    Następnie: ./images2 -i kubus3.pgm -d 
    Wynik: Obraz został przetworzony do szarości, zapisany jako obraz z P2 i odczytany jako obraz szary.
    
    6.Komenda: ./images2 -i kubus.ppm -m r -n -m x -n -d
    Wynik: Podana komenda powinna wpierw wybrać kolor czerwony do przetworzenia, a następnie przez podanie '-m x' wracamy do przetwarzania wszystkich kolorów.
    
    7.Komenda: ./images2 -i kubus.ppm -m n -d
    Wynik: Wyświetlany jest komunikat "Podano złe parametry koloru
    Poprawne to: 'r', 'g', 'b' lub 's'
    'x'-Powrót do przetwarzania wszystkich kolorów".
    
    8.Komenda: ./images2 -i kubus.ppm -m -d
    Wynik: Wyświetlany jest komunikat "Nie podano koloru do przetwarzania".
    
WNIOSKI: Błędy przy podawaniu parametrów są obługiwane poprawnie. Z faktu, że każdy obraz po wybraniu innego koloru różnił się od drugiego stwierdzam poprawność działanie tej opcji.

TEST 7:  Działanie progowania '-p' dla szarych i kolorowych obrazów, a także obsługa błędów.

    1.Komenda: ./images2 -i kubus.pgm -p 50 -d
    Wynik: Poprawnie zmodyfikowany obraz. Porównany z pliku pdf.
    
    2.Komenda: ./images2 -i kubus.ppm -p 50 -d
    Wynik: Wyświetlany jest zmodyfikowany obraz. Brak porównania.
    
    3.Komenda: ./images2 -i kubus.ppm -p 150 -d
    Wynik: Wyświetlany jest komunikat "Podano zły przedział progowania, powinien być mniejszy od 100 i większy od 0".
    
    4.Komenda: ./images2 -i kubus.ppm -p -d
    Wynik: Wyświetlany jest komunikat "Nie podano parametru progowania".
    
WNIOSEK: Poprawne działanie opcji i obsługa błędów.

TEST 8: Działanie konturowania '-k' dla szarych i kolorowych obrazów.

    1.Komenda: ./images2 -i kubus.pgm -k -d
    Wynik: Poprawnie skonturowany obraz. Porównanie z pliku pdf.
    
    2.Komenda: ./images2 -i kubus.ppm -k -d
    Wynik: Poprawnie skonturowany obraz. Jednak brak porównania.
    
WNIOSEK: Poprawne działanie opccji konturowania.

Test 9: Działanie rozciągnięcia histogramu '-h' dla szarych i kolorowych obrazów.

    1.Komenda: ./images2 -i kubus.pgm -h -d
    Wynik: Wyświetlenie obrazu, nie widać różnicy jednak.
    
    2.Komenda: ./images2 -i kubus.ppm -h -d
    Wynik: Wyświetlenie obrazu, nie widać różnicy jednak.
    
WNIOSEK: Powodem może być błąd ludzkiego oka.

TEST 10: Działanie rozmycia poziomego '-rx' dla szarych i kolorowych obrazów.

    1.Komenda: ./images2 -i kubus.pgm -rx -d
    Wynik: Wyświetlenie obrazu z  widocznym rozmyciem poziomym.
    
    2.Komenda: ./images2 -i kubus.ppm -rx -d
    Wynik: Wyświetlenie obrazu kolorowego z  widocznym rozmyciem poziomym.
    
    3.Komenda: ./images2 -i kubus.ppm -r -d
    Wynik: Wyświetlenie komunikatu "Złe wywołanie opcji rozmycia poziomego lub pionowego. Powinno być: '-rx- lub '-ry'"
    
WNIOSKI: Poprawne działanie opcji, a także obługa błędu przy wywołaniu tej opcji.

TEST 11: Działanie rozmycia pionowego '-ry' dla szarych i kolorowych obrazów i obsługa błędów.

    1.Komenda: ./images2 -i kubus.pgm -ry -d
    Wynik: Wyświetlenie obrazu z  widocznym rozmyciem pionowym.
    
    2.Komenda: ./images2 -i kubus.ppm -ry -d
    Wynik: Wyświetlenie obrazu kolorowego z  widocznym rozmyciem pionowym.
    
    3.Komenda: ./images2 -i kubus.ppm -r -d
    Wynik: Wyświetlenie komunikatu "Złe wywołanie opcji rozmycia poziomego lub pionowego. Powinno być: '-rx- lub '-ry'"
    
WNIOSKI: Poprawne działanie opcji, a także obługa błędu przy wywołaniu tej opcji.

TEST 12: Działanie zmiany poziomów '-z' dla szarych i kolorowych obrazów.

    1.Komenda: ./images2 -i kubus.pgm -z 30 70 -d
    Wynik: Wyświetlenie obrazu po zmianie poziomów. Porówanie z pliku pdf.
    
    2.Komenda: ./images2 -i kubus.ppm -z 30 70 -d
    Wynik: Wyświetlenie obrazu kolorowego po zmianie poziomów. Ewidentnie rózni się od oryginału.
    
    3.Komenda: ./images2 -i kubus.pgm -z -d
    Wynik: Wyświetlenie komunikatu "Nie podano parametru czerni i bieli".
    
    4.Komenda: ./images2 -i kubus.pgm -z 30 -d
    Wynik: Wyświetlenie komunikatu "Nie podano parametru bieli".
    
    5.Komenda: ./images2 -i kubus.pgm -z 30 110 -d
     Wynik: Wyświetlenie komunikatu "Parametr czerni powinien być mniejszy od bieli. Oba powinny znajdować się w przedziale od 0 do 100".
     
    6,Komenda: ./images2 -i kubus.pgm -z 60 20 -d
    Wynik: Wyświetlenie komunikatu "Parametr czerni powinien być mniejszy od bieli. Oba powinny znajdować się w przedziale od 0 do 100".
     
WNIOSKI: Poprawne działanie opcji.

TEST 13: Wywołanie bardziej złożonej kombinacji przetwarzania a także sprawdzenie działania programu przy przestawieniu kolejności wywołania opcji.

    1.Komenda: ./images2 -i kubus.ppm -m r -k -m x -n -z 30 70 -rx -k -d
    2.Komenda: ./images2 -i kubus.ppm -m r -k -m x -k -n -z 30 70 -rx -d
    Wynik: Przestawienie opcji konturowania drastycznie zmienia rezultat.
    
    3.Komenda ./images2 -i kubus.pgm -k -n -d
    4.Komenda ./images2 -i kubus.pgm -n -k -d
    Wynik: Zmiana kolejności wpływa na rezultat.
    
    
    5.Komenda ./images2 -i kubus.ppm -k -n -d
    6.Komenda ./images2 -i kubus.ppm -n -k -d
    Wynik: To samo dla obrazów kolorowych.
    
    7.Komenda ./images2 -i kubus.ppm -n -m g -k -m r -z 30 50 -m r -k -m b -p 70 -d
    Wynik: Wyświetlenie obrazu bez przeszkód.
    
    8.Komenda ./images2 -i kubus.pgm -n -z 20 80 -h -ry -n -p 50 -d
    Wynik: Wyświetlenie obrazu bez przeszkód.
WNIOSKI:
    
*/ 

