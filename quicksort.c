/*
Titel: quicksort
Beschreibung:
Autor: Patrick Wintner
GitHub: https://github.com/EternalNothingness/FSST-5BHEL-Excercises-07_quicksort.git
Datum der letzten Bearbeitung: 22.12.2020
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int teile(int *a, int us, int os)
{
	int i = us;
	// Starte mit j links vom Pivotelement
	int j = os-1;
	int pivot = a[os];
	while(i<j) // solange i an j nicht vorbeigelaufen ist
	{
		// Suche von links ein Element, welches groesser oder gleich dem Pivotelement ist
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

		// Suche von rechts ein Element, welches kleiner als das Pivotelement ist
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
		if(i<j)
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

void qs(int *a, int us, int os)
{
	if(us < os)
	{
		int teiler = teile(a, us, os);
		qs(a, us, teiler-1);
		qs(a, teiler+1, os);
	}
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

#define MY_SIZE 100

int main(int argc, char **argv)
{
	// create random ints based in current time
	srand(time(NULL));

        int *a = create_array(MY_SIZE, MY_SIZE);

	qs(a, 0, MY_SIZE-1);

	int old = -1;
	for (int i=0; i<MY_SIZE; ++i)      {
		if (old != -1) assert(old <= a[i]);
		printf("%d ", a[i]);
		old = a[i];
	}
	printf("\n");
}