
#include "timer.h"
#include "bufor.h"
#include "grafika.h"
#include <winalleg.h>
#include <windows.h>
#include <string.h>
using namespace std;
#ifndef s1_h
#define s1_h
s_timer game_time(1);
    //ret_s

void init_bufor(int a,int b){ // tworzymy graficzny obszar roboczy do ktorego mamy dostep z z kazdego punktu programu
bufor=create_bitmap(a,b);     // fajny motyw bo nigdy nie wiadomo gdzie bedzie najwygodniej wstawic funkcje rysujaca
clear_to_color( bufor, makecol(0, 0, 0 ) );
}






struct point{
int x;
int y;

};

class gra{ // czesc funkcji mogla by byc prywatna ale rabać,
public:

    int** tab_A; //plansza lewa
    int** tab_B; //plansza prawa
    int * ilosc_okretow; //ilosc okretow o konkretnej liczbie masztow
    int** t_pom1; //tablica do sprawdzania poprawnosci usawienia okretow
bool widocznosc_A; //jesli true widzisz wszystko na tablicy, jesli false tylko pudla i trafienia
bool widocznosc_B;
bool poprwanosc; // tu zapisujemy wynik funkcji sprawdzjacej poprawnosc ustawienia
int poziom_trudnosci=12; // od 1 do 100
int tura; //zmienna do obslogi menu i rozgrywki
int ss=33; //sauare size taka sama wartosc jak w bibliotece grafika.h
int trafienia_A=0; // trafienia
int trafienia_B=0;

string msg; // komunikat o trafieniu
void resetuj_tablice(){ //przeladowuje i czysci tablice
tab_A=new int*[10];
tab_B=new int*[10];
t_pom1=new int*[10];
ilosc_okretow=new int[6];

for(int i=0;i<6;i++)ilosc_okretow[i]=0;

for(int i=0;i<10;i++){
tab_A[i]=new int[10];
tab_B[i]=new int[10];
t_pom1[i]=new int[10];
    for(int j=0;j<10;j++){

        tab_A[i][j]=0;
        tab_B[i][j]=0;
    }
}
poprwanosc=true;
msg="";

}

point losuj(){  // funkcja losujaca pozycje
point ret;
ret.x=rand()%10;
ret.y=rand()%10;

return ret;
}

int sprawdz(point a, int ** tab){ // funkcja sprawdza czy dany punkt moze zostac postawiony na planszy

if(a.x<0 || a.y<0 || a.x>9 || a.y>9) return 0;

if(tab[a.x][a.y]==1)return 0;
if(a.x<9)if(tab[a.x+1][a.y]==1)return 0;
if(a.x>0)if(tab[a.x-1][a.y]==1)return 0;
if(a.y<9)if(tab[a.x][a.y+1]==1)return 0;
if(a.y>0)if(tab[a.x][a.y-1]==1)return 0;

return 1;
}

void ustaw(point a, int ** tab, int wartosc){ // w sumie przerost formy nad trescia

tab[a.x][a.y]=wartosc;
}

int postaw(int i, int ** tab){// jedna z najwazniejszych funkcji, stawia statek o zadanej dlogosci na planszy
    point a2;
    int p=0; // zmienna pomocnicza, zlicza obroty petli, jeśli bedzie ich za duzo czyli statku nie da sie postawic od wylosowanego punktu startowego zwroci -1
int p1=i; // zmienna przechowujaca dlogosc statku

 point a; // losowany punkt
 point tab_p[i+1]; // tablica przechowujaca pozycje kolejnych masztow, jezeli funkcja dojdzie do konca stawia statki na przechowywanych w niej wartosciach

 int p3=rand()%2; // losujemy czy statki maja byc w pionie czy w pozomie
       int p2=rand()%2; // czyli czy punkty maja byc dokladane na pozycji x+/- y+/-
while(i>0){

if(p1==i){// na poczatku losujemy puste pole
     a=losuj();

while(sprawdz(a,tab)==0)a=losuj();
}
else{



        do{// prubujemy dolozyc do tego pola i-1 pol w wylosowanym kierunku

            a2.x=a.x; // zapisujemy poprzednia pozycje
            a2.y=a.y;


            if(p3==0){// tworzymy nowa

if(p2==0)a2.x+=1;
else a2.x-=1;

if(a2.x<0 || a2.x>9)p=301;
            }
            else{
if(p2==0)a2.y+=1;
else a2.y-=1;

if(a2.y<0 || a2.y>9)p=301;
            }

       p++;
if(p>=300){


    return -1;
}

    }while(sprawdz(a2,tab)==0); //to mialo wiecej sensu gdy statki generowaly sie losow xD ale nie chce mi się tego zmieniać, i tak wiem ze nie jest to optymalne
                                //bo w sumie wystarczy ze sprawdz chociaz raz zwroci zero i proba postawienia jest do wyjebania xD

    a.x=a2.x;
    a.y=a2.y;
}

//ustaw(a,tab,1);
tab_p[i].x=a.x;
tab_p[i].y=a.y;
i--;

}
// stawiamy statek na wyznaczonych pozycjach
ustaw(a2,tab,1);
 while(i<p1){
        i++;
           ustaw(tab_p[i],tab,1);

        }

return 0;
}

void losuj_tablice(int ** tab){ // stawianie statkow na planszy
while(postaw(5, tab)==-1);
while(postaw(4, tab)==-1);
while(postaw(3, tab)==-1);
while(postaw(3, tab)==-1);
while(postaw(2, tab)==-1);
while(postaw(2, tab)==-1);
while(postaw(1, tab)==-1);
while(postaw(1, tab)==-1);
while(postaw(1, tab)==-1);
while(postaw(1, tab)==-1);

widocznosc_A=false;  // to powinno byc gdzie indziej chyba ;/
widocznosc_B=true;
tura=0;
}

int sprawdz_dlogosc(int ** tab, int x, int y){ // funcja dostaje tablice i pozycje od ktorej ma sprawdzic logosc statku, filozofi tu nie ma

int l=1;
bool p=true;
int kierunek=0;
tab[x][y]=0;
if(x<9 ){if(tab[x+1][y]==1)kierunek=0;}
if(y<9){if(tab[x][y+1]==1)kierunek=1;}
while(p){
p=false;
    if(x<9 && kierunek==0)if(tab[x+1][y]==1){
        x++;
        l++;
        tab[x][y]=0;
        p=true;
    }
if(y<9 && kierunek==1)if(tab[x][y+1]==1){
        y++;
        l++;
        tab[x][y]=0;
        p=true;
    }

}
return l; //zwraca dlugosc


}




int sprawdz_poprawnosc(int ** tab, int x, int y){ // funkcja sprawdza czy statk sie nie stykaja jesli tak zwraca -1, jesli nie zwraca 1


bool p=true;
int kierunek=0;

if(x<9 ){if(tab[x+1][y]==1)kierunek=0;}
if(y<9){if(tab[x][y+1]==1)kierunek=1;}
while(p){
p=false;

if(y<9 && kierunek==1)if(tab[x][y]==1){

        if(x>0)if(tab[x-1][y]==1)return -1;
       if(x<9)if(tab[x+1][y]==1)return -1;
        y++;
        p=true;
    }

}
return 1;


}

void sprawdz_zatopienie(int ** tab, int x, int y){ // nie wiem czemu to jest az tak dlogie ale dziela wiec co tam, jak sama nazwa wskazuje funkcja sprawdza
                                                    //czy zatoplismy, czy tylko trafilismy w statek, pewnie da sie to jakos zoptymalizować,

bool p=true;
int kierunek=0;
int t=0; //trafione;
int nt=0; //nietrafione
if(tab[x][y]==1)nt++;
else t++;
if(x<9 ){if(tab[x+1][y]==1 || tab[x+1][y]==3)kierunek=0;}
if(y<9){if(tab[x][y+1]==1 || tab[x][y+1]==3)kierunek=1;}
if(y>0){if(tab[x][y-1]==1 || tab[x][y-1]==3)kierunek=2;}
if(x>0 ){if(tab[x-1][y]==1 || tab[x-1][y]==3)kierunek=3;}
while(p){
p=false;

if(y<9 && kierunek==1){

    if(tab[x][y]==1 || tab[x][y]==3){
 y++;
       if(tab[x][y]==1)nt++;
       else t++;

        p=true;
    }
}

    if(x<9 && kierunek==0){
  x++;
        if(tab[x][y]==1 || tab[x][y]==3){

       if(tab[x][y]==1)nt++;
       else t++;

        p=true;
    }
    }

   if(y>0 && kierunek==2){
 y--;
    if(tab[x][y]==1 || tab[x][y]==3){

       if(tab[x][y]==1)nt++;
       else t++;

        p=true;
    }
   }

    if(x>0 && kierunek==3)
    {
         if(tab[x][y]==1 || tab[x][y]==3){
x--;
       if(tab[x][y]==1)nt++;
       else t++;

        p=true;
    }
    }


}

msg="Pud³o";
if(t>0)msg="Trafiony zatopiony!";
if(nt>0)msg="Trafiony niezatopiony!";

}



bool sprawdz_ustawienie(int ** tab, int * tab2){// tu lonczymy wiekszosc wczesniejszych funkcji do sprawdzania ustawienia statkow w 1 spujna dzialajaca calosc
    int p1=0;
for(int i=0;i<6;i++)tab2[i]=0;


bool ret =true;

for(int i=0;i<10;i++){

    for(int j=0;j<10;j++){

        t_pom1[i][j]=tab[i][j];
    }
}

for(int i=0;i<10;i++){

    for(int j=0;j<10;j++){

        if(t_pom1[i][j]==1)
        {
            p1=sprawdz_dlogosc(t_pom1,i,j);   // przez to sie wczesniej krzaczylo bo nie dalem warunku dotyczacego dlugosci i wychodzilo poza petle
            if( p1<=5)tab2[p1]++;
        }

        if(sprawdz_poprawnosc(tab, i, j)==-1)ret=false;
    }
}

return ret;
}



void rozgrywka(int mx,int my,int mb){ // glowna funkcja


if(tura==0){




}




if(tura==1){// tura gracza

    widocznosc_A=true;
    widocznosc_B=false;


    if(mb==1){// stan przycisku myszy  PPM=2 LPM=1

mx=mx-13*ss; // od wspulzednych myszki odejmujemy dlogosc 1 planszy i 1 kolumny 2 planszy, potem dzielimy przez rozmiar pojedynczego kwadracika i dostajemy pozycje w x
my=my-ss;    // od pozycji y odejmujemy tylko 1 wiersz planszy  po podzieleniu przez rozmiar kwadracika dostajemy pozycje y
int x=int(mx/ss);
int y=int(my/ss);

if(x>=0 && x<10 && y>=0 && y<10)//sprawdzamy czy myszka znajduje sie na planszy
{
if(tab_B[x][y]==0){ // zmieniamy wartosc w tablicy dla chybienia

    tab_B[x][y]=2;
tura=2;
msg="podlo";
}
if(tab_B[x][y]==1){ // w przypadku trafienia dodoatkowo zliczamy sobie punkty i sprawdzamy "zatopienie"

    tab_B[x][y]=3;
    sprawdz_zatopienie(tab_B,x,y);

trafienia_A++;
if(trafienia_A>=23) {

    allegro_message("Wygrales"); // coś tu nie dokonca resetuje, pewnie trzeba dodac jakies opuznienie czy cos
    resetuj_tablice();
    losuj_tablice(tab_A);
    losuj_tablice(tab_B);
    trafienia_A=0;
    trafienia_B=0;
}
tura=2; // oddajemy ture "sztucznej inteligencji"
}

}

    }
}


if(tura==2){ // tura SI


int p1=rand()%101; // losujemy sobie liczbę
if(p1<poziom_trudnosci)p1=1; //jeżeli p1 < poziomu trudnosci to będze się starała trafić
else p1=0; // w przeciwnym razie będzie chciała spudłować
point p2=losuj();// losujemy punkt
int p3=0; // zmienna pomocnicza, jeśli przez 20 losowan nie uda się jej trafic lub spudlowac to "zmienia zdanie"
while(tab_A[p2.x][p2.y]!=p1 && p3<20){

    p2=losuj();
    p3++;
}
if(p3>=20)while(tab_A[p2.x][p2.y]!=1)p2=losuj();// i proboje wykonac odwrotny ruch od pierwotnie wylosowanego, nie dokonca zoptymalizowane moze sie wykrzaczyc
                                                // dla bezpieczenstwa mozna ustawic więcej niz 20
if(tab_A[p2.x][p2.y]==0){ // to samo co w tura 1

    tab_A[p2.x][p2.y]=2;

}
if(tab_A[p2.x][p2.y]==1){

    tab_A[p2.x][p2.y]=3;
trafienia_B++;
if(trafienia_B>=23) {

    allegro_message("Przegrales");
    resetuj_tablice();
    losuj_tablice(tab_A);
    losuj_tablice(tab_B);
    trafienia_A=0;
    trafienia_B=0;
}
}
tura=1; // oddajemy ruch graczowi
Sleep(100 ); // czekamy 100 ms
}

if(tura==3){// ustawiamy statki na planszy

if(mb==1){

mx=mx-ss;// poniewaz ustawiamy na 1 planszy odejmujemy tylko dlogosc 1 kolumny
my=my-ss;
int x=int(mx/ss);
int y=int(my/ss);

if(x>=0 && x<10 && y>=0 && y<10)
{


    tab_A[x][y]=1;




}
poprwanosc=sprawdz_ustawienie(tab_A, ilosc_okretow);
    }

if(mb==2){

mx=mx-ss;
my=my-ss;
int x=int(mx/ss);
int y=int(my/ss);

if(x>=0 && x<10 && y>=0 && y<10)
{


    tab_A[x][y]=0;




}
poprwanosc=sprawdz_ustawienie(tab_A, ilosc_okretow);
    }


}



if(tura==4){ // 1v1


    widocznosc_A=false; //ustawiamy odpowiednia widocznosc
    widocznosc_B=true;


    if(mb==1){

mx=mx-ss;
my=my-ss;
int x=int(mx/ss);
int y=int(my/ss);

if(x>=0 && x<10 && y>=0 && y<10)
{
if(tab_A[x][y]==0){

    tab_A[x][y]=2;


   msg="Podlo";
    clear_to_color( bufor, makecol(0, 0, 0 ) );   // ten fragment kodu odpowiada za znikniecie plansz na 5 s i wyswietlenie komunikatu

    textprintf_ex( bufor, font, 500, 500, makecol( 255, 255, 0 ), -1, msg.c_str());
 blit(bufor, screen, 0, 0, 0, 0, 1000, 1000);
Sleep(5000);

tura=5;
}
if(tab_A[x][y]==1){

    tab_A[x][y]=3;
    sprawdz_zatopienie(tab_A,x,y);
    clear_to_color( bufor, makecol(0, 0, 0 ) );

    textprintf_ex( bufor, font, 500, 500, makecol( 255, 255, 0 ), -1, msg.c_str());
 blit(bufor, screen, 0, 0, 0, 0, 1000, 1000);
Sleep(5000);

tura=5;
}

}

    }


}


if(tura==5){


    widocznosc_A=true;
    widocznosc_B=false;


    if(mb==1){

mx=mx-13*ss;
my=my-ss;
int x=int(mx/ss);
int y=int(my/ss);

if(x>=0 && x<10 && y>=0 && y<10)
{
if(tab_B[x][y]==0){

    tab_B[x][y]=2;
    msg="Podlo";
    clear_to_color( bufor, makecol(0, 0, 0 ) );

    textprintf_ex( bufor, font, 500, 500, makecol( 255, 255, 0 ), -1, msg.c_str());
 blit(bufor, screen, 0, 0, 0, 0, 1000, 1000);
Sleep(5000);
tura=4;
}
if(tab_B[x][y]==1){

    tab_B[x][y]=3;

    tab_A[x][y]=3;
    sprawdz_zatopienie(tab_B,x,y);
    clear_to_color( bufor, makecol(0, 0, 0 ) );

    textprintf_ex( bufor, font, 500, 500, makecol( 255, 255, 0 ), -1, msg.c_str());
 blit(bufor, screen, 0, 0, 0, 0, 1000, 1000);
Sleep(5000);

tura=4;
}

}

    }


}






}


bool konfiguracja(){ //to wywolujemy w mainie kiedy chcemy zatwierdzic ustawienie okretow

if(ilosc_okretow[5]==1 &&ilosc_okretow[4]==1 &&ilosc_okretow[3]==2 &&ilosc_okretow[2]==2 &&ilosc_okretow[1]==4  )return false;
return true;
}









};







#endif
