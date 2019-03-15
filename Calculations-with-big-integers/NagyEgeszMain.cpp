#include <iostream>
#include "NagyEgesz.h"
using namespace std;
int main()
{
    int sor[100]={ 2,4,6,8,1,0,1,2,1,4,1,6,1,8};
    int sor2[100]={ 1,2,3,4,5,6,7,8,9,1,6,5};
    NagyEgesz a(1,14,sor); ///where to start, how many numbers to take, from where
    NagyEgesz b(1,8,sor2);

    ///a.osszead(b); /// a+b
    ///a.kivon();   ///a-b
    ///a.szoroz(b); /// a*b
    ///a.oszt(b);   /// a/b
    ///a.osszehasonlit(b) /// check whether a>b
    ///a.egyenlo(b)       /// a==b

    a.kiir();
    b.kiir();
    //try{
    a.oszt(b);
    //}
    //catch(NagyEgesz::NullavalValoOsztas)
    //{
     //   cout<<"Nullaval valo osztas nem lehetseges.";
    //}
    a.kiir();
    //}
    //catch(const char*)
   // {
    //    cout<<"Nem szabad 0 val kezdodjon a szam";
    //}
    return 0;
}
