#ifndef funkcje_hpp
#define funkcje_hpp

struct macierz
{
	double M[4][4];
};

const int liczba_krokow = 10000;
float dl_kroku = 0.01;

void rysuj_graf(HWND hwnd, int typ_pobudzenia, double stala, double skala_Y, double skala_X, double k1, double k2, double m1, double m2, double b1, double b2);
void rysuj_osie(HWND hwnd);
void rysuj_funkcje(double y[], HDC hdcOkno, double skala_Y, double skala_X);
void licz_x(double k1, double k2, double m1, double m2, double b1, double b2);

HPEN CzerwonePioro = CreatePen( PS_SOLID, 1, 0x0000FF ); //x2
HPEN ZielonePioro = CreatePen( PS_SOLID, 1, 0x00FF00 ); //x1
HPEN NiebieskiePioro = CreatePen( PS_DOT, 0, 0xff0000 ); //pobudzenie
HPEN SzarePioro = CreatePen( PS_SOLID, 0, 0xd3d3d3 ); //linie siatki
HPEN CzarnePioro = CreatePen( PS_SOLID, 0, 0x000000 ); //linie siatki

int wysokosc = 650;
int dlugosc = 1470;
int dlugosc_X = dlugosc - 15; //aktualnie 1455px
int odstep_podzialki = 20;
int dl_linii_podzialki = 5;

float wartosc_jednostkowa_X = odstep_podzialki;
float wartosc_jednostkowa_Y = odstep_podzialki;

double pobudzenie[liczba_krokow];
double x1[liczba_krokow];
double x2[liczba_krokow];

macierz operator+(macierz U, macierz W)
{
	macierz Z;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			Z.M[i][j] = U.M[i][j] + W.M[i][j];
		}
	}
	
	return Z;
}

macierz operator*(double k, macierz W)
{
	macierz Z;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			Z.M[i][j] = k * W.M[i][j];
		}
	}
	
	return Z;
}

macierz operator*(macierz A, macierz B)
{
	macierz Z;
	for(int i = 0; i < 4; i++)
	    for(int j = 0; j < 4; j++)
	    {
	      double s = 0;
	      for(int k = 0; k < 4; k++) s += A.M[i][k] * B.M[k][j];
	      Z.M[i][j] = s;
	    }
	
	return Z;
}

void rysuj_graf(HWND hwnd, int typ_pobudzenia, double stala, double skala_Y, double skala_X, double k1, double k2, double m1, double m2, double b1, double b2)
{
	HDC hdcOkno = GetDC( hwnd ); //uchwyt okna
								
	if(typ_pobudzenia == 1)//fala prost.
	{		
		int szerokosc_fali = 100;	
		int k = 0;
		
		while(k < liczba_krokow)//liczenie pobudzenia
		{	
			for(int j = 0; j<szerokosc_fali; j++)
			{	
				pobudzenie[j+k] = stala;
			}			
			k += szerokosc_fali;
		
			for(int j = 0; j<szerokosc_fali; j++)
			{	
				pobudzenie[j+k] = 0;
			}		
			k += szerokosc_fali;		
		}
		
		licz_x(k1, k2, m1, m2, b1, b2);
		
		SelectObject( hdcOkno, NiebieskiePioro );
		rysuj_funkcje(pobudzenie, hdcOkno, skala_Y, skala_X);
		SelectObject( hdcOkno, ZielonePioro );
		rysuj_funkcje(x1, hdcOkno, skala_Y, skala_X);
		SelectObject( hdcOkno, CzerwonePioro );
		rysuj_funkcje(x2, hdcOkno, skala_Y, skala_X);
		
		
	}
	else if(typ_pobudzenia == 2)//skok
	{
				
		for(int i = 0; i < liczba_krokow; i++)
		{
			pobudzenie[i] = stala;
		}
		licz_x(k1, k2, m1, m2, b1, b2);
		
		SelectObject( hdcOkno, NiebieskiePioro );
		rysuj_funkcje(pobudzenie, hdcOkno, skala_Y, skala_X);
		SelectObject( hdcOkno, ZielonePioro );
		rysuj_funkcje(x1, hdcOkno, skala_Y, skala_X);
		SelectObject( hdcOkno, CzerwonePioro );
		rysuj_funkcje(x2, hdcOkno, skala_Y, skala_X);
	}
	else if(typ_pobudzenia == 3)//sinus
	{
		double x = 0.0;
				
		for(int i = 0; i < liczba_krokow; i++)
		{
			pobudzenie[i] = stala + sin(x);
			x += dl_kroku;
		}
	
		licz_x(k1, k2, m1, m2, b1, b2);
		
		SelectObject( hdcOkno, NiebieskiePioro );
		rysuj_funkcje(pobudzenie, hdcOkno, skala_Y, skala_X);
		SelectObject( hdcOkno, ZielonePioro );
		rysuj_funkcje(x1, hdcOkno, skala_Y, skala_X);
		SelectObject( hdcOkno, CzerwonePioro );
		rysuj_funkcje(x2, hdcOkno, skala_Y, skala_X);
	}
	

}


void rysuj_osie(HWND hwnd)
{
	
	
	HDC hdcOkno = GetDC( hwnd );//obszar rysowania	
	
	Rectangle( hdcOkno, 5, 0, dlugosc+1, wysokosc+1 );
		
	MoveToEx( hdcOkno, 15, 0, NULL );//os Y
	LineTo( hdcOkno, 15, wysokosc);
	
	MoveToEx( hdcOkno, 15, 0, NULL ); //strzalka Y
	LineTo( hdcOkno, 10, 10);
	
	MoveToEx( hdcOkno, 15, 0, NULL );
	LineTo( hdcOkno, 20, 10);
	
	MoveToEx( hdcOkno, dlugosc, wysokosc/2, NULL );//strzalka X
	LineTo( hdcOkno, dlugosc - 10, wysokosc/2 - 5);

	MoveToEx( hdcOkno, dlugosc, wysokosc/2, NULL );
	LineTo( hdcOkno, dlugosc - 10, wysokosc/2 + 5);
	
	// rysowanie szarych linii
	SelectObject( hdcOkno, SzarePioro );
	
	for(int i=0; i < dlugosc_X/odstep_podzialki; i++)
	{
		MoveToEx( hdcOkno, 35 + i*odstep_podzialki, 1 , NULL );//os X podzialka
		LineTo( hdcOkno, 35 + i*odstep_podzialki, wysokosc);
	}
	
	int j = 0;
	for(int i=1; i < wysokosc/(odstep_podzialki)  ; i++)
	{
		if(i < (wysokosc/odstep_podzialki)/2)
		{
			MoveToEx( hdcOkno, 15, wysokosc/2 - i*odstep_podzialki , NULL );//os Y podzialka
			LineTo( hdcOkno, dlugosc, wysokosc/2 - i*odstep_podzialki);
		}
		else
		{
			MoveToEx( hdcOkno, 15, wysokosc/2 + j*odstep_podzialki , NULL );//os Y podzialka
			LineTo( hdcOkno, dlugosc, wysokosc/2 + j*odstep_podzialki);
			j++;
		}
	}
	
	// rysowanie czarnych linii
	SelectObject( hdcOkno, CzarnePioro );
	
	MoveToEx( hdcOkno, 5, wysokosc/2, NULL );//os X
	LineTo( hdcOkno, dlugosc +1, wysokosc/2);
	
	for(int i=0; i < dlugosc_X/odstep_podzialki; i++)
	{
		MoveToEx( hdcOkno, 35 + i*odstep_podzialki, wysokosc/2 + dl_linii_podzialki , NULL );//os X podzialka
		LineTo( hdcOkno, 35 + i*odstep_podzialki, wysokosc/2 - dl_linii_podzialki);
	}
	
	j = 0;
	for(int i=0; i < wysokosc/(odstep_podzialki)  ; i++)
	{
		if(i < (wysokosc/odstep_podzialki)/2)
		{
			MoveToEx( hdcOkno, 15 - dl_linii_podzialki, wysokosc/2 - i*odstep_podzialki , NULL );//os Y podzialka
			LineTo( hdcOkno, 15 + dl_linii_podzialki, wysokosc/2 - i*odstep_podzialki);
		}
		else
		{
			MoveToEx( hdcOkno, 15 - dl_linii_podzialki, wysokosc/2 + j*odstep_podzialki , NULL );//os Y podzialka
			LineTo( hdcOkno, 15 + dl_linii_podzialki, wysokosc/2 + j*odstep_podzialki);
			j++;
		}
	}
}


void rysuj_funkcje(double y[], HDC hdcOkno, double skala_Y, double skala_X)
{
		for(int i = 0; i < liczba_krokow; i++)
		{
			y[i] = y[i] * wartosc_jednostkowa_Y*skala_Y + wysokosc/2;
			
			if( y[i] < wysokosc/2)
			{
				y[i] =  y[i] + 2*(wysokosc/2 - y[i]);
			}
			
			else if( y[i] > wysokosc/2)
			{
				y[i] =  y[i] - 2*(y[i] - wysokosc/2);
			}
		}
		
		MoveToEx( hdcOkno, 15, wysokosc/2 , NULL );
		LineTo( hdcOkno, 15, y[0]);
		MoveToEx( hdcOkno, 15, y[0] , NULL );
	    for(int i=0; i < liczba_krokow  ; i++)
		{
			if(15 + i * dl_kroku * wartosc_jednostkowa_X*skala_X >=dlugosc )
				break;
			LineTo( hdcOkno, 15 + i * dl_kroku * wartosc_jednostkowa_X*skala_X, y[i]);
		}
}

void licz_x(double k1, double k2, double m1, double m2, double b1, double b2)
{
	macierz x;
	macierz x_next;
	macierz trap;
	macierz trap2;
	macierz A;
	macierz B;

	A.M[0][0] = 0;
	A.M[0][1] = 0;
	A.M[0][2] = 1;
	A.M[0][3] = 0;
	A.M[1][0] = 0;
	A.M[1][1] = 0;
	A.M[1][2] = 0;
	A.M[1][3] = 1;
	A.M[2][0] = (-k1-k2)/m1;
	A.M[2][1] = (k2)/m1;		
	A.M[2][2] = (-b1-b2)/m1;
	A.M[2][3] = (b2)/m1;
	A.M[3][0] = k2/m2;
	A.M[3][1] = -k2/m2;
	A.M[3][2] = b2/m2;
	A.M[3][3] = -b2/m2;
		
	for(int i=0; i<4; i++)//wartosci B
	{
		for(int j=0; j<4; j++)
		{
			B.M[i][j] = 0;
		}
	}
	B.M[3][0] = 1/m2;
	
	
	
	double temp1;
	double temp2;
	
	for(int i=0; i<liczba_krokow; i++)
	{
		/*temp1 = pobudzenie[i];
		temp2 = pobudzenie[i+1];
		trap = 0.5*(dl_kroku*A*x + temp1*dl_kroku*B + (dl_kroku+dl_kroku)*A*x + temp2*dl_kroku*B);
		x_next = x + trap;
		x1[i] = x_next.M[0][0];
		x2[i] = x_next.M[1][0];
		x = x_next;*/
		
		temp1 = pobudzenie[i];
		trap = dl_kroku*A*x + temp1*dl_kroku*B; //metoda prostokatow
		x_next = x + trap;
		x1[i] = x_next.M[0][0];
		x2[i] = x_next.M[1][0];
		x = x_next;
	}
		
}

#endif
