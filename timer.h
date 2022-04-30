
#include <time.h>

using namespace std;
#ifndef timer_h
#define timer_h

//taka moja  biblioteka, jak dla mnie timery w allego sa zjebane wiec napisalem sobie wlasne
//przydatne w optymalizajci bo widac po fpsach jak cos zjebales
class s_timer{
public:
time_t czas;
struct tm * ptr;
int takt; //ms
char * data;
~s_timer(){

delete ptr;

}

int f; //fps
s_timer(int a){
time( & czas );
ptr = localtime( & czas );
data = asctime( ptr );
takt=a;
f=0;
}

char * ret_char_s(){

char * ret;
ret=new char[2];
ret[0]=data[17];
ret[1]=data[18];
return ret;
}

int ret_s(){
    time( & czas );
ptr = localtime( & czas );
data = asctime( ptr );
    int ret=(data[17]-'0')*10;
    ret+=(data[18]-'0');
    return ret;
}
int as;//aktualna sekunda
int os;//stara sekunda



int fps(){
    int ret=-1;
    f++;
as=ret_s();

if(as!=os){

    os=as;
   ret=f;
   f=0;
}

return ret;
}

};





#endif
