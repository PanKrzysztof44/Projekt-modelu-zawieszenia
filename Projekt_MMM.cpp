#include <windows.h>
#include <cmath>
#include <cstdio>
#include "funkcje.hpp"

#define ID_PRZYCISK1 101
#define ID_PRZYCISK2 102
#define ID_PRZYCISK3 103
#define ID_PRZYCISK4 104
#define ID_PRZYCISK5 105
#define ID_COMBO 201

using namespace std;

LPSTR NazwaKlasy = "Klasa Okienka";
MSG Komunikat;
PAINTSTRUCT ps;

HWND g_hPrzycisk;
HWND etyk_Skala_X_p;
HWND etyk_Skala_Y_p;
HWND hB2;
HWND hB1;
HWND hL2;
HWND hL1;
HWND hK2;
HWND hK1;
HWND hM2;
HWND hM1;
HWND hstala;
HWND hX;
HWND hY;

DWORD dlugosc_stala;
DWORD dlugosc_M1;
DWORD dlugosc_M2;
DWORD dlugosc_B1;
DWORD dlugosc_B2;
DWORD dlugosc_K1;
DWORD dlugosc_K2;
DWORD dlugosc_L1;
DWORD dlugosc_L2;
DWORD dlugosc_hX;
DWORD dlugosc_hY;

LPSTR wart_stala;
LPSTR wart_M1;
LPSTR wart_M2;
LPSTR wart_B1;
LPSTR wart_B2;
LPSTR wart_K1;
LPSTR wart_K2;
LPSTR wart_L1;
LPSTR wart_L2;
LPSTR wart_hX;
LPSTR wart_hY;

double b2,b1,l2,l1,k2,k1,m2,m1,stala;

char t_skala_X[16];
char t_skala_Y[16];

int typ_pobudzenia; //1 - fala prostok¹ta
					//2 - skok
					//3 - sinusoida

int wysokosc_okna = 820;
int szerokosc_okna = 1500;

float f,g;
	
float skala_X = 1;
float skala_Y = 5.2;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

void rysuj_graf(HWND hwnd, int typ_pobudzenia, double stala, double skala_Y, double skala_X, double k1, double k2, double m1, double m2, double b1, double b2);
void rysuj_osie(HWND hwnd);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    
    // WYPE£NIANIE STRUKTURY
    WNDCLASSEX wc;
    
    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
    

    
    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( NULL, "Blad rejestracji okna", "Blad",
        MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }
    
    // TWORZENIE OKNA
    HWND hwnd;
    
    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Projekt_MMM", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, szerokosc_okna, wysokosc_okna, NULL, NULL, hInstance, NULL );
    
    if( hwnd == NULL )
    {
        MessageBox( NULL, "Blad wyswietlania", "Blad", MB_ICONEXCLAMATION );
        return 1;
    }
    
    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );
    
    
    int szer_pola = 50;
    int ile_w_lewo = 70;
    //Rysuj
    HWND hRysuj = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Rysuj", WS_CHILD | WS_VISIBLE | WS_BORDER, 1360 - ile_w_lewo, 680, 110, 30, hwnd,( HMENU ) ID_PRZYCISK1, hInstance, NULL );
	
    //Skladowa stala
	HWND etyk_hstala = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 1260 - ile_w_lewo, 680, 80, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_hstala, "Skladowa stala" );
	
	hstala = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 1260 - ile_w_lewo, 710, 80, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_stala = GetWindowTextLength( hstala );
	wart_stala =( LPSTR ) GlobalAlloc( GPTR, dlugosc_stala + 1 );
	GetWindowText( hstala, wart_stala, dlugosc_stala + 1 );
	stala = atof(wart_stala);
    
	f = skala_X;
	snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", f);	
	g = skala_Y;
	snprintf(t_skala_Y, sizeof(t_skala_Y), "%.2f", g);
	  
	//Skala X+
    HWND hSkala_X_p = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Skala x+", WS_CHILD | WS_VISIBLE | WS_BORDER, 1100 - ile_w_lewo, 680, 65, 30, hwnd,( HMENU ) ID_PRZYCISK2, hInstance, NULL );
	hX = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", t_skala_X, WS_CHILD | WS_VISIBLE | WS_BORDER, 1100 - ile_w_lewo, 710, 65, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_hX = GetWindowTextLength( hX );
	wart_hX =( LPSTR ) GlobalAlloc( GPTR, dlugosc_hX + 1 );
    
    //Skala X-
    HWND hSkala_X_n = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Skala x-", WS_CHILD | WS_VISIBLE | WS_BORDER, 1090 - ile_w_lewo*2, 680, 65, 30, hwnd,( HMENU ) ID_PRZYCISK3, hInstance, NULL );
    
    //Skala Y+
    HWND hSkala_Y_p = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Skala y+", WS_CHILD | WS_VISIBLE | WS_BORDER, 1080 - ile_w_lewo*3, 680, 65, 30, hwnd,( HMENU ) ID_PRZYCISK4, hInstance, NULL );
    hY = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", t_skala_Y, WS_CHILD | WS_VISIBLE | WS_BORDER, 1080 - ile_w_lewo*3, 710, 65, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_hY = GetWindowTextLength( hY );
	wart_hY =( LPSTR ) GlobalAlloc( GPTR, dlugosc_hY + 1 );
    
    //Skala Y-
    HWND hSkala_Y_n = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Skala y-", WS_CHILD | WS_VISIBLE | WS_BORDER, 1070 - ile_w_lewo*4, 680, 65, 30, hwnd,( HMENU ) ID_PRZYCISK5, hInstance, NULL );
    
	//B2
	HWND etyk_b2 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 1210 - ile_w_lewo*7, 680, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_b2, "b2" );
	
	hB2 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 1210 - ile_w_lewo*7, 710, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_B2 = GetWindowTextLength( hB2 );
	wart_B2 =( LPSTR ) GlobalAlloc( GPTR, dlugosc_B2 + 1 );
	GetWindowText( hB2, wart_B2, dlugosc_B2 + 1 );
	b2 = atof(wart_B2);
	
	//B1
	HWND etyk_b1 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 1060 - ile_w_lewo*6, 680, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_b1, "b1" );
	
	hB1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 1060 - ile_w_lewo*6, 710, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_B1 = GetWindowTextLength( hB1 );
	wart_B1 =( LPSTR ) GlobalAlloc( GPTR, dlugosc_B1 + 1 );
	GetWindowText( hB1, wart_B1, dlugosc_B1 + 1 );
	b1 = atof(wart_B1);
	
	//L2
	HWND etyk_L2 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 910 - ile_w_lewo*5, 680, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_L2, "l2" );
	
	hL2 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 910 - ile_w_lewo*5, 710, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_L2 = GetWindowTextLength( hL2 );
	wart_L2 =( LPSTR ) GlobalAlloc( GPTR, dlugosc_L2 + 1 );
	GetWindowText( hL2, wart_L2, dlugosc_L2 + 1 );
	l2 = atof(wart_L2);
	
	//L1
	HWND etyk_L1 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 760 - ile_w_lewo*4, 680, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_L1, "l1" );
	
	hL1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 760 - ile_w_lewo*4, 710, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_L1 = GetWindowTextLength( hL1 );
	wart_L1 =( LPSTR ) GlobalAlloc( GPTR, dlugosc_L1 + 1 );
	GetWindowText( hL1, wart_L1, dlugosc_L1 + 1 );
	l1 = atof(wart_L1);
		
	//K2
	HWND etyk_K2 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 610 - ile_w_lewo*3, 680, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_K2, "k2" );
	
	hK2 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 610 - ile_w_lewo*3, 710, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_K2 = GetWindowTextLength( hK2 );
	wart_K2 =( LPSTR ) GlobalAlloc( GPTR, dlugosc_K2 + 1 );
	GetWindowText( hK2, wart_K2, dlugosc_K2 + 1 );
	k2 = atof(wart_K2);
	
	//K1
	HWND etyk_K1 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 460 - ile_w_lewo*2, 680, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_K1, "k1" );
	
	hK1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 460 - ile_w_lewo*2, 710, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_K1 = GetWindowTextLength( hK1 );
	wart_K1 =( LPSTR ) GlobalAlloc( GPTR, dlugosc_K1 + 1 );
	GetWindowText( hK1, wart_K1, dlugosc_K1 + 1 );
	k1 = atof(wart_K1);
	
	//M2
	HWND etyk_M2 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 310 - ile_w_lewo, 680, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_M2, "m2" );
	
	hM2 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 310 - ile_w_lewo, 710, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_M2 = GetWindowTextLength( hM2 );
	wart_M2 =( LPSTR ) GlobalAlloc( GPTR, dlugosc_M2 + 1 );
	GetWindowText( hM2, wart_M2, dlugosc_M2 + 1 );
	m2 = atof(wart_M2);
	
	//M1
	HWND etyk_M1 = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 160, 680, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	SetWindowText( etyk_M1, "m1" );
	
	hM1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "1.00", WS_CHILD | WS_VISIBLE | WS_BORDER, 160, 710, szer_pola, 20, hwnd, NULL, hInstance, NULL );
	
	dlugosc_M1 = GetWindowTextLength( hM1 );
	wart_M1 =( LPSTR ) GlobalAlloc( GPTR, dlugosc_M1 + 1 );
	GetWindowText( hM1, wart_M1, dlugosc_M1 + 1 );
	m1 = atof(wart_M1);

	HWND hFuncje = CreateWindowEx( WS_EX_CLIENTEDGE, "COMBOBOX", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 10, 680, 110, 100, hwnd, ( HMENU ) ID_COMBO, hInstance, NULL );
	SendMessage( hFuncje, CB_ADDSTRING, 0,( LPARAM ) "Fala prost." );
	SendMessage( hFuncje, CB_ADDSTRING, 0,( LPARAM ) "Skok" );
	SendMessage( hFuncje, CB_ADDSTRING, 0,( LPARAM ) "Sinusoida" );
	
	DWORD dlugosc_hFuncje = GetWindowTextLength( hFuncje );
	LPSTR wart_pola_f =( LPSTR ) GlobalAlloc( GPTR, dlugosc_hFuncje + 1 );
	GetWindowText( hFuncje, wart_pola_f, dlugosc_hFuncje + 1 );
	
	rysuj_osie(hwnd);
	
	GlobalFree( wart_B2 ); //czyszczenie
	GlobalFree( wart_B1 );
	GlobalFree( wart_L2 );
	GlobalFree( wart_L1 );
	GlobalFree( wart_K2 );
	GlobalFree( wart_K1 );
	GlobalFree( wart_M2 );
	GlobalFree( wart_M1 );
	

    // Pêtla komunikatów
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

// OBS£UGA ZDARZEÑ
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{	
	HDC hdcOkno = GetDC( hwnd ); //uchwyt okna

    switch( msg )
    {   
    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;
        
    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
        
        default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    case WM_COMMAND:
    	if(HIWORD(wParam) == CBN_SELCHANGE)
        { 
            int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
            TCHAR  ListItem[256];
            (TCHAR) SendMessage((HWND) lParam, (UINT) CB_GETLBTEXT, (WPARAM) ItemIndex, (LPARAM) ListItem);
            if(ListItem[0] == 'F' )
				typ_pobudzenia = 1;
            else if(ListItem[1] == 'k' )
				typ_pobudzenia = 2;
            else if(ListItem[1] == 'i' )
				typ_pobudzenia = 3;                         
        }
		switch( wParam )
		{
		case ID_PRZYCISK1:
			BitBlt(hdcOkno, 0, 0, dlugosc, wysokosc, 0, 0, 0, WHITENESS); // wyczyszczenie okna
			
			GetWindowText( hstala, wart_stala, dlugosc_stala + 1 );
			stala = atof(wart_stala);
			GetWindowText( hM1, wart_M1, dlugosc_M1 + 1 );
			m1 = atof(wart_M1);
			GetWindowText( hM2, wart_M2, dlugosc_M2 + 1 );
			m2 = atof(wart_M2);
			GetWindowText( hB1, wart_B1, dlugosc_B1 + 1 );
			b1 = atof(wart_B1);
			GetWindowText( hB2, wart_B2, dlugosc_B2 + 1 );
			b2 = atof(wart_B2);
			GetWindowText( hK1, wart_K1, dlugosc_K1 + 1 );
			k1 = atof(wart_K1);
			GetWindowText( hK2, wart_K2, dlugosc_K2 + 1 );
			k2 = atof(wart_K2);
			GetWindowText( hL1, wart_L1, dlugosc_L1 + 1 );
			l1 = atof(wart_L1);
			GetWindowText( hL2, wart_L2, dlugosc_L2 + 1 );
			l2 = atof(wart_L2);
			GetWindowText( hX, wart_hX, dlugosc_hX + 1 );
			skala_X = atof(wart_hX);
			GetWindowText( hY, wart_hY, dlugosc_hY + 1 );
			skala_Y = atof(wart_hY);
			
			rysuj_osie(hwnd);
		    rysuj_graf(hwnd, typ_pobudzenia, stala, skala_Y, skala_X, k1, k2, m1, m2, b1, b2);
		    
		    f = skala_X;
			snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", f);	
			g = skala_Y;
			snprintf(t_skala_Y, sizeof(t_skala_Y), "%.2f", g);
			
		    SetWindowText( hX, t_skala_X );
		    SetWindowText( hY, t_skala_Y );
		    
		    float mnoznik;
		    
		    for(int i=0; i < dlugosc_X/odstep_podzialki/2; i++)
			{
				mnoznik = 2*1/skala_X * (i+1);
				snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 42 + i*2*odstep_podzialki, wysokosc/2 + dl_linii_podzialki, t_skala_X, 4 );
			}
			
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = 2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 - 2*i*odstep_podzialki-48, t_skala_Y, 4 );
			}
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = -2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 + 2*i*odstep_podzialki+32, t_skala_Y, 5 );
			}	    
		    break;
		
		case ID_PRZYCISK2:
			skala_X += 0.1;
			BitBlt(hdcOkno, 0, 0, dlugosc, wysokosc, 0, 0, 0, WHITENESS); // wyczyszczenie okna
			
			f = skala_X;
			snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", f);	
			
			rysuj_osie(hwnd);
		    rysuj_graf(hwnd, typ_pobudzenia, stala, skala_Y, skala_X, k1, k2, m1, m2, b1, b2);
		    
		    SetWindowText( hX, t_skala_X );
		    
		    for(int i=0; i < dlugosc_X/odstep_podzialki/2; i++)
			{
				mnoznik = 2*1/skala_X * (i+1);
				snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 42 + i*2*odstep_podzialki, wysokosc/2 + dl_linii_podzialki, t_skala_X, 4 );
			}
			
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = 2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 - 2*i*odstep_podzialki-48, t_skala_Y, 4 );
			}
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = -2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 + 2*i*odstep_podzialki+32, t_skala_Y, 5 );
			}
		    break;
		case ID_PRZYCISK3:
			if(skala_X > 0.1)
				skala_X -= 0.1;
			BitBlt(hdcOkno, 0, 0, dlugosc, wysokosc, 0, 0, 0, WHITENESS); // wyczyszczenie okna
			
		    f = skala_X;
			snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", f);	
			
			rysuj_osie(hwnd);
		    rysuj_graf(hwnd, typ_pobudzenia, stala, skala_Y, skala_X, k1, k2, m1, m2, b1, b2);
		    
		    SetWindowText( hX, t_skala_X );
		    		    
		    for(int i=0; i < dlugosc_X/odstep_podzialki/2; i++)
			{
				mnoznik = 2*1/skala_X * (i+1);
				snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 42 + i*2*odstep_podzialki, wysokosc/2 + dl_linii_podzialki, t_skala_X, 4 );
			}
			
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = 2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 - 2*i*odstep_podzialki-48, t_skala_Y, 4 );
			}
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = -2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 + 2*i*odstep_podzialki+32, t_skala_Y, 5 );
			}
		    break;
		case ID_PRZYCISK4:
			skala_Y += 0.1;
			BitBlt(hdcOkno, 0, 0, dlugosc, wysokosc, 0, 0, 0, WHITENESS); // wyczyszczenie okna

			g = skala_Y;
			snprintf(t_skala_Y, sizeof(t_skala_Y), "%.2f", g);

			rysuj_osie(hwnd);
		    rysuj_graf(hwnd, typ_pobudzenia, stala, skala_Y, skala_X, k1, k2, m1, m2, b1, b2);
		    
		    SetWindowText( hY, t_skala_Y );
		    
		    for(int i=0; i < dlugosc_X/odstep_podzialki/2; i++)
			{
				mnoznik = 2*1/skala_X * (i+1);
				snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 42 + i*2*odstep_podzialki, wysokosc/2 + dl_linii_podzialki, t_skala_X, 4 );
			}
			
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = 2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 - 2*i*odstep_podzialki-48, t_skala_Y, 4 );
			}
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = -2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 + 2*i*odstep_podzialki+32, t_skala_Y, 5 );
			}
		    break;
		case ID_PRZYCISK5:
			if(skala_Y > 0.1)
				skala_Y -= 0.1;
			BitBlt(hdcOkno, 0, 0, dlugosc, wysokosc, 0, 0, 0, WHITENESS); // wyczyszczenie okna

			g = skala_Y;
			snprintf(t_skala_Y, sizeof(t_skala_Y), "%.2f", g);

			rysuj_osie(hwnd);
		    rysuj_graf(hwnd, typ_pobudzenia, stala, skala_Y, skala_X, k1, k2, m1, m2, b1, b2);
		    SetWindowText( hY, t_skala_Y );
		    
		    for(int i=0; i < dlugosc_X/odstep_podzialki/2; i++)
			{
				mnoznik = 2*1/skala_X * (i+1);
				snprintf(t_skala_X, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 42 + i*2*odstep_podzialki, wysokosc/2 + dl_linii_podzialki, t_skala_X, 4 );
			}
			
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = 2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 - 2*i*odstep_podzialki-48, t_skala_Y, 4 );
			}
			for(int i=0; i < wysokosc/(odstep_podzialki)/4-1  ; i++)
			{
				mnoznik = -2*1/skala_Y * (i+1);
				snprintf(t_skala_Y, sizeof(t_skala_X), "%.2f", mnoznik);
				TextOut( hdcOkno, 30, wysokosc/2 + 2*i*odstep_podzialki+32, t_skala_Y, 5 );
			}
		    break;
		}
	break;	
    }
    
    return 0;
}
