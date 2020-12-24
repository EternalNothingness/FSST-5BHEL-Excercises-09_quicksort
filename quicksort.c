/*
Titel: quicksort
Beschreibung: Dieses Programm vergleicht die Geschwindigkeit der Sortieralgorithmen quicksort
und bubblesort fuer 10, 100, 1.000, 10.000 und 100.000 Elementen und gibt die Zeitdauer aus.
Die Funktionen quicksort() und teile() entsprechen dem Schema des auf https://de.wikipedia.org/wiki/Quicksort
veroeffentlichten Pseudocodes.
Autor: Patrick Wintner
GitHub: https://github.com/EternalNothingness/FSST-5BHEL-Excercises-07_quicksort.git
Datum der letzten Bearbeitung: 24.12.2020
*/

// -- Standardbibliotheken --
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// -- andere Bibliotheken --
#include <assert.h> // fuer assert
#include <sys/time.h> // zur Messung der Zeitdauer

// -- Funktion int teile --
// Parameter:
//	* int *a ... Zeiger zum ersten Elements des zu sortierenden Arrays
//	* int us ... untere Grenze
//	* int os ... obere Grenze
// Beschreibung: Die Funktion teile() vergleicht die Elemente des Arrays a im Bereich [us, os-1]
// mit dem Pivotelement (a[os]); sollte das Element a[i] groesser als das Pivotelement sein und
// das Element a[j] kleiner als das Pivotelement sein, so werden, falls i kleiner j, diese getauscht.
// I entspricht dabei zu Beginn us und wird anschliessend erhoeht, waehrend j zu Beginn os entspricht
// und dann verringert wird. Dies wird so lange fortgesetzt, bis i gleich j wird. Zuletzt wird
// das Pivot-Element neu positioniert und zurueckgegeben.
// Rueckgabewert: neue Position des Pivot-Elements
int teile(int *a, int us, int os)
{
	int i = us;
	// Starte mit j ('1' unter Pivotelement)
	int j = os-1;
	int pivot = a[os];
	while(i<j) // solange i an j nicht vorbeigelaufen ist
	{
		// Suche von unten nach oben ein Element, welches groesser oder gleich dem Pivotelement ist
		// while((i<os) and (a[i]<pivot))
		while(1)
		{
			if(i<os)
			{
				if(a[i]<pivot)
				{
					i++;
				}
				else break;
			}
			else break;
		}

		// Suche von oben nach unten ein Element, welches kleiner als das Pivotelement ist
		// while((j>us) and (a[j]>=pivot))
		while(1)
		{
			if(j>us)
			{
				if(a[j]>=pivot)
				{
					j--;
				}
				else break;
			}
			else break;
		}
		if(i<j) // Tausche beide Elemente, falls a[i] weiter unten platziert als a[j]
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}

	// Tausche Pivotelement (a[os] mit neuer, endgueltiger Position (a[i])
	// und gib die neue Position des Pivotelements zurueck, beende Durchlauf
	if(a[i] > pivot)
	{
		int temp = a[i];
		a[i] = a[os];
		a[os] = temp;
	}
	return i;
}

// -- Funktion void qs --
// Parameter:
//	* int *a ... Zeiger zum ersten Element des zu sortierenden Arrays
//	* int us ... untere Grenze
//	* int os ... obere Grenze
//	* bool message_en ... enabelt Fehlernachrichten
// Beschreibung: Die Funktion qs() sortiert die Elemente des Arrays a aufsteigend, indem sie
// diesen in zwei Teile teilt, wobei alle Elemente einer dieser Teilmengen kleiner sind als die
// der anderen; anschliessend wird die Funktion rekursiv mit den Teilmengen als Parameter aufgerufen.
// Rueckgabewert: -
void qs(int *a, int us, int os, bool message_en)
{
	if(a == NULL) 
	{
	if(message_en == true) printf("array existiert nicht!");
	return;
	}

	if(us < os)
	{
		int teiler = teile(a, us, os);
		qs(a, us, teiler-1, message_en);
		qs(a, teiler+1, os, message_en);
	}
	else if(message_en == true) printf("ungueltige Grenzangaben!");
}

// creates a array of size size and fills it with random ints in range 0 to max_int
int *create_array(int size, int max_int)
{
	int *b = (int*)malloc(size * sizeof(int));

	for (int i=0; i<size; i++) {
		b[i] = rand() % max_int;
	}

	return b;
}

// -- Funktion void bs --
// Parameter:
//	* int *a ... Zeiger zum ersten Element des zu sortierenden Arrays
//	* int n ... Anzahl der Elemente des Arrays
// Beschreibung: Die Funktion bs() sortiert die Elemente des Arrays a nach aufsteigender Reihenfolge,
// indem jeweils zwei benachbarte Elemente verglichen und, sollte das weiter hinten stehende Element
// kleiner als das vorherige sein, tauscht.
// Rueckgabewert: -
void bs(int *a, int n)
{
	bool change;
	int temp;
	for(;;)
	{
		change = false;
		for(int i = 1; i < n; i++)
		{
			if(a[i-1] > a[i])
			{
				int temp = a[i-1];
				a[i-1] = a[i];
				a[i] = temp;
				if(change != true) change = true;
			}
		}
		if(change == false) break;
	}
}
// -- Funktion cmpfunc --
// Parameter:
//	* const void *a
//	* const void *b
// Beschreibung: Die Funktion cmpfunc liefert die Differenz a-b, wird fuer qsort benoetigt;
// wurde von https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm uebernommen.
// Rueckgabewert: Differenz a-b
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

#define MY_SIZE 100

int main(int argc, char **argv)
{
	// create random ints based in current time
	srand(time(NULL));
	/*
        int *a = create_array(MY_SIZE, MY_SIZE);

	//qs(a, 0, MY_SIZE-1, true);
	qsort(a, MY_SIZE, sizeof(int), cmpfunc);

	int old = -1;
	for (int i=0; i<MY_SIZE; ++i)      {
		if (old != -1) assert(old <= a[i]);
		printf("%d ", a[i]);
		old = a[i];
	}
	printf("\n");
	*/
	struct timeval t_begin_qs, t_end_qs, t_diff_qs;
	struct timeval t_begin_bs, t_end_bs, t_diff_bs;
	for(int i = 10; i <= 100000; i = 10*i)
	{
		int *a = create_array(i, i);
		gettimeofday(&t_begin_qs, NULL);
		//qs(a, 0, i-1, true);
		qsort(a, i, sizeof(int), cmpfunc);
		gettimeofday(&t_end_qs, NULL);
		timersub(&t_end_qs, &t_begin_qs, &t_diff_qs);
		printf("time ellapsed during quicksort of %i elements: %ld seconds %ld microseconds\n", i, t_diff_qs.tv_sec, t_diff_qs.tv_usec);

		int *b = create_array(i, i);
		gettimeofday(&t_begin_bs, NULL);
		bs(b, i);
		gettimeofday(&t_end_bs, NULL);
		timersub(&t_end_bs, &t_begin_bs, &t_diff_bs);
		printf("time ellapsed during bubblesort of %i elements: %ld seconds %ld microseconds\n\n", i, t_diff_bs.tv_sec, t_diff_bs.tv_usec);
	}
}