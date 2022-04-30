#include "st1.h"
#include <allegro.h>
void init();
void deinit();

int wysokos=1000;
int szerokosc=800;





void intit_gr(){
init_bufor(1000,1000); // pierwsza funcja w st1.h


}

int main() {
    srand(time(NULL));
	init(); // funkcja na dole, nie ma sie co w sumie nad nia rozwodzic,
            //jesl chodzi o deinit to warto dodac destruktory ;) ale mi sie nie chcialo
intit_gr();


show_mouse( screen );
s_timer czas_gry(1); // tworzymy sobie timer
int fps=0;
int pfps=0;


int pasek_menu_1_x=10;  // pozycje przyciskow
int pasek_menu_2_x=10;
int pasek_menu_1_y=600;
int pasek_menu_2_y=650;

int menu_glowne_x=375;
int menu_glowne_y=100;

int mpl=100;  // rozmiar sowakow itp
int mph=30;
int ust=1; // zmienna pomocnicza do obslogi menu

gra gra1;
gra1.resetuj_tablice();
gra1.losuj_tablice(gra1.tab_A);
gra1.losuj_tablice(gra1.tab_B);
grafika grafika1;
grafika1.generuj_grafike(mpl, mph);


	while (!key[KEY_ESC]) {//glowna petla gry



pfps=czas_gry.fps();
if(pfps!=-1)fps=pfps;// funkcja sprawdzajaca fpsy
gra1.rozgrywka(mouse_x,mouse_y,mouse_b); // wywolanie glownej funkci z st1.h

if(gra1.tura!=0){ // menu w rozgrywce

    grafika1.rysuj_plansze_A(gra1.tab_A,gra1.widocznosc_A); //  rysujemy plansze
grafika1.rysuj_plansze_B(gra1.tab_B,gra1.widocznosc_B);
if(gra1.tura!=3)textprintf_ex( bufor, font, 500, 500, makecol( 255, 255, 0 ), -1, gra1.msg.c_str()); // wypisujemy informacje otrafieniu chybieniu

grafika1.rysuj_menu(mpl,mph,pasek_menu_1_x,pasek_menu_1_y,pasek_menu_2_x, pasek_menu_2_y, gra1.ss, gra1.poziom_trudnosci, ust, gra1.tura);// wywolanie funkci z grafika.h
//obsluga menu
if(mouse_b==1){// sprawdzamy czy przycisk myszy  zostal wcisniety, jesli tak to nad jakim przyciskiem, sowakiem
                // i wykonujemy jakas tam akcje ktora sie z nim wiaze

    if(mouse_x+20>pasek_menu_1_x&&mouse_x<pasek_menu_1_x+mpl && mouse_y>pasek_menu_1_y&&mouse_y<pasek_menu_1_y+mph){

        gra1.ss=mouse_x-pasek_menu_1_x+20; // to jest obsloga tego paska do zmiany rozdzielczosci
gra1.ss/=2;

grafika1.czysc_grafike();// poz mianie rozdzielczosci przeladowuje grafike
grafika1.generuj_grafike(mpl,mph);
    }



    if((mouse_x>pasek_menu_2_x+220&&mouse_x<pasek_menu_2_x+320 && mouse_y>pasek_menu_1_y&&mouse_y<pasek_menu_1_y+50)){
if(ust==1){  // obloga przycisku ustaw

    gra1.tura=3;
for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++){
            gra1.tab_A[i][j]=0;

        }
    }
    ust=2;
gra1.trafienia_A=0;
gra1.trafienia_B=0;
Sleep(100);
}
else{
if(gra1.tura==3){// obloga przycisku gotowe

int ilosc=0;

for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++){
            if(gra1.tab_A[i][j]==1)ilosc++;

        }
    }
if(ilosc<23){

 allegro_message("Ustawiles za malo statkow!");
}
else if(ilosc>23) allegro_message("Ustawiles za duzo statkow!");
else if(gra1.poprwanosc==false)allegro_message("Statki nie moga sie stykac!");
else if(gra1.konfiguracja())allegro_message("Statk ustawione w zlej konfiguracji");
else{

    gra1.tura=1;
    ust=1;
}

Sleep(200);
}



}

    }


    if(mouse_x>pasek_menu_2_x+340&&mouse_x<pasek_menu_2_x+440 && mouse_y>pasek_menu_1_y&&mouse_y<pasek_menu_1_y+50){
// przycisk wyjdz (do menu )
for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++){
            gra1.tab_A[i][j]=0;

        }
    }
gra1.poprwanosc=gra1.sprawdz_ustawienie(gra1.tab_A, gra1.ilosc_okretow);

        gra1.tura=0;

    }

    if(mouse_x>pasek_menu_2_x+460&&mouse_x<pasek_menu_2_x+560 && mouse_y>pasek_menu_1_y&&mouse_y<pasek_menu_1_y+50){
// przycisk resetuj
        for(int i=0;i<10;i++){

            for(int j=0;j<10;j++){

                if(gra1.tab_A[i][j]==2)gra1.tab_A[i][j]=0;
                if(gra1.tab_A[i][j]==3)gra1.tab_A[i][j]=1;
                if(gra1.tab_B[i][j]==3)gra1.tab_B[i][j]=1;
                if(gra1.tab_B[i][j]==2)gra1.tab_B[i][j]=0;
            }
        }
gra1.trafienia_A=0;
gra1.trafienia_B=0;
    }



}





}else{ // obsloga menu glownego

clear_to_color( bufor, makecol(0, 255, 0 ) ); // ustawiamy kolor tla w RGB

grafika1.rysuj_menu_glowne(mpl,mph,menu_glowne_x,menu_glowne_y, gra1.poziom_trudnosci, ust);// wywolujemy funkcje rysowania menu glownego z grafika.h
//obsluga menu
if(mouse_b==1){


if(mouse_x>menu_glowne_x&&mouse_x<menu_glowne_x+100 && mouse_y>menu_glowne_y&&mouse_y<menu_glowne_y+50){

 gra1.poziom_trudnosci=mouse_x-menu_glowne_x; // obsloga poziomu trudnosci
    }

    if(mouse_x>menu_glowne_x&&mouse_x<menu_glowne_x+300 && mouse_y>menu_glowne_y+80&&mouse_y<menu_glowne_y+130){

// obsloga przycisku gra jednosobowa
    gra1.resetuj_tablice();
 gra1.losuj_tablice(gra1.tab_A);
 gra1.losuj_tablice(gra1.tab_B);
 gra1.trafienia_A=0;
 gra1.trafienia_B=0;
gra1.tura=1;
ust=1;

    }

 if(mouse_x>menu_glowne_x&&mouse_x<menu_glowne_x+300 && mouse_y>menu_glowne_y+180&&mouse_y<menu_glowne_y+230){
// obsloga przycisku gra dwuosobowa
 gra1.resetuj_tablice();
 gra1.losuj_tablice(gra1.tab_A);
 gra1.losuj_tablice(gra1.tab_B);
 gra1.trafienia_A=0;
 gra1.trafienia_B=0;
gra1.tura=4;
    }

    if(mouse_x>menu_glowne_x&&mouse_x<menu_glowne_x+100 && mouse_y>menu_glowne_y+260&&mouse_y<menu_glowne_y+310){
// obsloga przycisku wyjdz
return 0;
    }

}
}

if(gra1.tura==3){
    textprintf_ex( bufor, font, 500, 500, makecol( 255, 255, 0 ), -1, "Ilosc 5 masztowcow: %d/1 ", gra1.ilosc_okretow[5] );
    textprintf_ex( bufor, font, 500, 520, makecol( 255, 255, 0 ), -1, "Ilosc 4 masztowcow: %d/1 ", gra1.ilosc_okretow[4] );
    textprintf_ex( bufor, font, 500, 540, makecol( 255, 255, 0 ), -1, "Ilosc 3 masztowcow: %d/2 ", gra1.ilosc_okretow[3] );
    textprintf_ex( bufor, font, 500, 560, makecol( 255, 255, 0 ), -1, "Ilosc 2 masztowcow: %d/2 ", gra1.ilosc_okretow[2] );
    textprintf_ex( bufor, font, 500, 580, makecol( 255, 255, 0 ), -1, "Ilosc 1 masztowcow: %d/4 ", gra1.ilosc_okretow[1] );
}
textprintf_ex( bufor, font, 10, 10, makecol( 255, 255, 0 ), -1, "tura %d  ", gra1.tura );

//koniec obslogi menu
blit(bufor, screen, 0, 0, 0, 0, 1000, 1000); // rysuje obszar roboczy na ekranie
clear_to_color( bufor, makecol(0, 0, 0 ) ); // czysci obszar roboczy
	}




deinit();
return 0;
}
END_OF_MAIN()

void init() {

	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, wysokos, szerokosc, 0, 0); // tu mozna zmienic sposob wyswietlania, wysokosc, szerokosc i czy aplikacja ma byc
	if (res != 0) {                                                         // okienkowa czy ma sie wyswietlac na caly ekran
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();

}


void deinit() {// proponuje dorzucic destruktory

	clear_keybuf();
delete bufor;
}
