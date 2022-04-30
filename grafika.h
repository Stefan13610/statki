#include "bufor.h"
#include <allegro.h>
#include <string>
#include <stdio.h>
#ifndef GRAFIKA_H_INCLUDED
#define GRAFIKA_H_INCLUDED
using namespace std;



BITMAP * pole_zasloniete;
BITMAP * pole_ze_statkiem;
BITMAP * chybienie;
BITMAP * zatopienie;
BITMAP * plansza_A;
BITMAP * plansza_B;
BITMAP * sowak;
BITMAP * pasek;
BITMAP * menu_1;
BITMAP * menu_2;
BITMAP * resetuj;
BITMAP * ustaw;
BITMAP * losuj;
BITMAP * wyjdz;
BITMAP * gra_jednoosobowa;
BITMAP * gra_dwuosobowa;
BITMAP * pomocniczy;
BITMAP * pomocniczy2;
BITMAP * gotowe;
class grafika{
private:
   int square_size=33; //rozmiar pojedynczego prostok¹ta ;)
public:
void generuj_grafike(int mpl, int mph){ //menu_pasek_h menu_pasek_l

ustaw=create_bitmap(50,25); // ustawiamy szerokosc i wysokosc bitmapy (obrazka)
gotowe=create_bitmap(50,25);
wyjdz=create_bitmap(50,25);
resetuj=create_bitmap(50,25);
losuj=create_bitmap(50,25);
gra_jednoosobowa=create_bitmap(150,25);
gra_dwuosobowa=create_bitmap(150,25);
pomocniczy=create_bitmap(42,19);
pomocniczy2=create_bitmap(144,19);

clear_to_color( ustaw, makecol(255, 240, 40 ) ); // ustawiamy kolor w rgb
clear_to_color( wyjdz, makecol(255, 240, 40 ) );
clear_to_color( resetuj, makecol(255, 240, 40 ) );
clear_to_color( losuj, makecol(255, 240, 40 ) );
clear_to_color( gra_jednoosobowa, makecol(240, 240, 40 ) );
clear_to_color( gra_dwuosobowa, makecol(240, 240, 40 ) );
clear_to_color( pomocniczy, makecol(255, 240, 40 ) );
clear_to_color( pomocniczy2, makecol(40, 240, 40 ) );

blit(pomocniczy2, gra_jednoosobowa,0, 0, 3, 3,  144, 19); // tworzymy przyciski
blit(pomocniczy2, gra_dwuosobowa,0, 0, 3, 3,  144, 19);   // rysujemy mniejszy na wiekszym rzeby dostac efekt ramki
clear_to_color( pomocniczy, makecol(100, 255, 100 ) );
blit(pomocniczy, ustaw,0, 0, 3, 3,  42, 19);
clear_to_color( pomocniczy, makecol(255, 100, 100 ) );
blit(pomocniczy, wyjdz,0, 0, 3, 3,  42, 19);
clear_to_color( pomocniczy, makecol(200, 200, 200 ) );
blit(pomocniczy, resetuj,0, 0, 3, 3,  42, 19);
clear_to_color( pomocniczy, makecol(100, 100, 255 ) );
blit(pomocniczy, losuj,0, 0, 3, 3,  42, 19);
blit(ustaw, gotowe,0, 0, 0, 0,  50, 25);

textprintf_ex( gra_jednoosobowa, font,5 , 5, makecol( 255, 255, 0 ), -1,  "Gra jednoosobowa" ); // wstawiamy odpowiednie napisy
textprintf_ex( gra_dwuosobowa, font,5 , 5, makecol( 255, 255, 0 ), -1,  "Gra dwuosobowa" );
 textprintf_ex( ustaw, font,5 , 5, makecol( 255, 255, 0 ), -1,  "Ustaw" );
 textprintf_ex( wyjdz, font,5 , 5, makecol( 255, 255, 0 ), -1,  "Wyjdz" );
 textprintf_ex( resetuj, font,5 , 5, makecol( 255, 255, 0 ), -1,  "Resetuj" );
 textprintf_ex( losuj, font,5 , 5, makecol( 255, 255, 0 ), -1,  "Losuj" );
textprintf_ex( gotowe, font,5 , 5, makecol( 255, 255, 0 ), -1,  "Gotowe" );

pole_zasloniete=create_bitmap(square_size,square_size); // tworzymy kwadraciki do mapy
clear_to_color( pole_zasloniete, makecol(200, 200, 200 ) );
line( pole_zasloniete,0,0,square_size,0, makecol(0,0,0)); // rysujemy czarna obwodke dookola kwadracika
line( pole_zasloniete,0,0,0,square_size, makecol(0,0,0));
line( pole_zasloniete,square_size,0,square_size,square_size, makecol(0,0,0));
line( pole_zasloniete,0,square_size,square_size,square_size, makecol(0,0,0));

pole_ze_statkiem=create_bitmap(square_size,square_size);
chybienie=create_bitmap(square_size,square_size);
zatopienie=create_bitmap(square_size,square_size);
plansza_A=create_bitmap(11*square_size,11*square_size);// tworzymy plansze
plansza_B=create_bitmap(11*square_size,11*square_size);
blit(pole_zasloniete, pole_ze_statkiem, 0, 0, 0, 0, square_size, square_size);// rysujemy pierwszy stworzony kwadracki (pole zasloniete ) na pozostalych
blit(pole_zasloniete, chybienie, 0, 0, 0, 0, square_size, square_size);
blit(pole_zasloniete, zatopienie, 0, 0, 0, 0, square_size, square_size);
floodfill(zatopienie,10,10,makecol(255,80,80)); // wypelniamy czerownym kolorem pole zatopione

circlefill( zatopienie, int(square_size/2), int(square_size/2), int(square_size/2.5), makecol( 0, 0, 0 )); // rysujemy kolko na kwadracikach
circlefill( pole_ze_statkiem, int(square_size/2), int(square_size/2), int(square_size/2.5), makecol( 0, 0, 0 ));
line( chybienie,0,0,square_size,square_size, makecol(0,0,0)); // rysujemy x
line( chybienie,0,square_size,square_size,0, makecol(0,0,0));

sowak=create_bitmap(20,mph); // tworzymy sowak, pasek i osobny graficzny obszar roboczy
clear_to_color( sowak, makecol(50, 200, 255) );
pasek=create_bitmap(mpl+40,mph-10);
clear_to_color( pasek, makecol(50, 200, 50 ) );
menu_1=create_bitmap(mpl+40,mph);
menu_2=create_bitmap(mpl+40,mph);

for(int i=1;i<11;i++){  // "numerujemy" pola planszy B
    string a1="ABCDEFGHIJ";
    string a2="12345678910";

if(i==10)textprintf_ex( plansza_B, font, int(square_size/3),square_size*i+int(square_size/2) ,  makecol( 255, 255, 0 ), -1,  a2.substr(i-1,3).c_str() );
else textprintf_ex( plansza_B, font, int(square_size/2),square_size*i+int(square_size/2) ,  makecol( 255, 255, 0 ), -1,  a2.substr(i-1,1).c_str() );
   textprintf_ex( plansza_B, font,square_size*i+int(square_size/2) , int(square_size/2), makecol( 255, 255, 0 ), -1,  a1.substr(i-1,1).c_str() );

}
blit(plansza_B, plansza_A,0, 0,0,0, square_size*11, square_size*11);
for(int i=1;i<11;i++){

    for(int j=1;j<11;j++){

    blit(pole_zasloniete, plansza_A,0, 0, square_size*i, square_size*j,  square_size, square_size); //rysujemy plansze B na A zeby nie numerowac 2razy
    blit(pole_zasloniete, plansza_B,0, 0, square_size*i, square_size*j,  square_size, square_size);
}

}

}

void czysc_grafike(){// niekompletny destruktor

destroy_bitmap(pole_zasloniete);
destroy_bitmap(pole_ze_statkiem);
destroy_bitmap(chybienie);
destroy_bitmap(zatopienie);
destroy_bitmap(plansza_A);
destroy_bitmap(plansza_B);
destroy_bitmap(sowak);
destroy_bitmap(pasek);
destroy_bitmap(menu_2);










}

void rysuj_plansze_A(int ** tab, bool widocznosc){
for(int i=1;i<11;i++){

    for(int j=1;j<11;j++){

    if(tab[i-1][j-1]==0)blit(pole_zasloniete, plansza_A,0, 0, square_size*i, square_size*j,  square_size, square_size);
    else if(tab[i-1][j-1]==1){

            if(widocznosc)blit(pole_ze_statkiem, plansza_A,0, 0, square_size*i, square_size*j,  square_size, square_size);
    else blit(pole_zasloniete, plansza_A,0, 0, square_size*i, square_size*j,  square_size, square_size);
    }
    else if(tab[i-1][j-1]==2)blit(chybienie, plansza_A,0, 0, square_size*i, square_size*j,  square_size, square_size);
    else if(tab[i-1][j-1]==3)blit(zatopienie, plansza_A,0, 0, square_size*i, square_size*j,  square_size, square_size);

}

}
blit( plansza_A,bufor,0, 0, 0,0, square_size*11, square_size*11);
}

void rysuj_plansze_B(int ** tab,bool widocznosc){
for(int i=1;i<11;i++){

    for(int j=1;j<11;j++){

    if(tab[i-1][j-1]==0)blit(pole_zasloniete, plansza_B,0, 0, square_size*i, square_size*j,  square_size, square_size);
    else if(tab[i-1][j-1]==1){

            if(widocznosc)blit(pole_ze_statkiem, plansza_B,0, 0, square_size*i, square_size*j,  square_size, square_size);
    else blit(pole_zasloniete, plansza_B,0, 0, square_size*i, square_size*j,  square_size, square_size);
    }
    else if(tab[i-1][j-1]==2)blit(chybienie, plansza_B,0, 0, square_size*i, square_size*j,  square_size, square_size);
    else if(tab[i-1][j-1]==3)blit(zatopienie, plansza_B,0, 0, square_size*i, square_size*j,  square_size, square_size);

}

}
blit( plansza_B,bufor,0, 0, square_size*12,0, square_size*11, square_size*11);
}

void rysuj_menu(int mpl, int mph,int x1,int y1, int x2, int y2, int ss, int pt, int m,int tura){
if(square_size!=ss)square_size=ss;
blit(pasek, menu_1,0, 0, 0, 5,  mpl+40, mph);

blit(sowak, menu_1,0, 0, ss*2+1, 0,  20, mph);

textprintf_ex( bufor, font, x1, y1-10, makecol( 255, 255, 0 ), -1, "Skala: %d ", ss );
blit(menu_1, bufor,0,0,x1,y1,mpl+40,mph);


clear_to_color( menu_1, makecol(0, 0, 0 ) );


 if(m==1 && tura==1 )stretch_blit(ustaw, bufor,0,0,50,25,x2+220,y1,100,50);
 else if(tura==3) {stretch_blit(gotowe, bufor,0,0,50,25,x2+220,y1,100,50);}
 stretch_blit(wyjdz, bufor,0,0,50,25,x2+340,y1,100,50);
if(tura==1)stretch_blit(resetuj, bufor,0,0,50,25,x2+460,y1,100,50);


}



void rysuj_menu_glowne(int mpl, int mph,int x1,int y1, int pt, int m){

blit(pasek, menu_2,0, 0, 0, 5,  mpl+40, mph);
blit(sowak, menu_2,0, 0, pt, 0,  20, mph);
textprintf_ex( bufor, font, x1, y1-10, makecol( 255, 255, 0 ), -1, "Poziom trudnosci: %d ", pt );
blit(menu_2, bufor,0,0,x1,y1,mpl+40,mph);

clear_to_color( menu_2, makecol(0, 0, 0 ) );

 stretch_blit(gra_jednoosobowa, bufor,0,0,150,25,x1,y1+80,300,50);
 stretch_blit(gra_dwuosobowa, bufor,0,0,150,25,x1,y1+180,300,50);

 stretch_blit(wyjdz, bufor,0,0,50,25,x1,y1+260,100,50);



}






};





#endif // GRAFIKA_H_INCLUDED
