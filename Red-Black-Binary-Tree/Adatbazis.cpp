#include <iostream>
#include <fstream>
#include <windows.h>
#include "Piros_Fekete_Binaris_Keresofa.h"
using namespace std;
void adatbazis()
{
    bool futas=true;
    bool print= true;
    PFBK fa;
    while(futas)
    {
        if(print)
        {
            cout<<"1.Adatbazis feltoltese. (N)"<<endl;
            cout<<"2.Adatbazis szerkesztese. (E)"<<endl;
            cout<<"3.Informaciok lekerese. (K)"<<endl;
            cout<<"4.Kilepes. (Q) "<<endl;
        }
        print=false;
        if( GetAsyncKeyState( 'Q' ) & 0x8000 ){
            futas=false;
            system("CLS");
        }
        if( GetAsyncKeyState( 'N' ) & 0x8000 ){
            bool letrehozas=true;
            system("CLS");
            bool print1=true;
            while(letrehozas)
            {
                if(print1)
                {
                    cout<<"1.Beolvasunk adatokat egy filebol. (B)"<<endl;
                    cout<<"2.Vissza a fomenube. (Backspace)"<<endl;
                }
                print1=false;
                if( GetAsyncKeyState( 'B' ) & 0x8000 )
                {
                    string fajlnev;
                    cout<<"Fajl neve: ";
                    cin>>fajlnev;
                    ifstream f(fajlnev);
                    if( f.fail())
                        cout<<"Nem letezik ilyen file."<<endl;
                    else
                    {
                        fa.Beolvas_fajlbol_bunozo(f);
                        cout<<"Sikeres beolvasas!"<<endl;
                    }
                    system("PAUSE");
                    system("CLS");
                    print1=true;
                }
                if( GetAsyncKeyState( VK_BACK ) & 0x8000 )
                {
                    letrehozas=false;
                    print=true;
                    system("CLS");
                }
            }
        }
        if( GetAsyncKeyState( 'E' ) & 0x8000 )
        {
            bool szerkesztes=true;
            system("CLS");
            bool print2=true;
            while(szerkesztes)
            {
                if(print2)
                {
                    cout<<"1.Uj szemely hoszzaadasa (N)"<<endl;
                    cout<<"2.Szemely adatainak szerkesztese (I)"<<endl;
                    cout<<"3.Szemely elkovetett ujabb buncselekmenyt. (U)"<<endl;
                    cout<<"4.Szemely torlese az adatbazisbol. (T)"<<endl;
                    cout<<"5.Vissza a fomenube. (Backspace)"<<endl;
                }
                print2=false;
                if( GetAsyncKeyState( 'N' ) & 0x8000 ){
                    system("CLS");
                    bunozo uj=Beolvas_bunozo();
                    fa.Hozzaad_elem(uj);
                    cout<<"Sikeres hozzaadas!"<<endl;
                    system("PAUSE");
                    system("CLS");
                    print2=true;
                }
                if( GetAsyncKeyState( 'I' ) & 0x8000 ){
                    string knev,csnev,nev;
                    cout<<"Keresztnev: ";
                    cin>>knev;
                    cout<<"Csaladnev: ";
                    cin>>csnev;
                    nev=knev+" "+csnev;
                    elem* van=fa.Megvan(nev);
                    if(van==NULL)
                    {
                        cout<<"Nincs ilyen szemely az adatbazisban"<<endl;
                    }
                    else
                    {
                        system("CLS");
                        bool modositas=true;
                        bool modositas_print=true;
                        while(modositas)
                        {
                            if(modositas_print)
                            {
                                fa.Kiir_adatok(van);
                                cout<<endl<<"######################################################"<<endl<<endl;
                                cout<<"1.Lakcim modositasa. (1)"<<endl;
                                cout<<"2.Fogvatartas modositasa. (2)"<<endl;
                                cout<<"3.Gyakran latogatott helyszin modositasa. (3)"<<endl;
                                cout<<"4.Bandahoz tartozas modositasa. (4)"<<endl;
                                cout<<"5.Fuggosegek/gyogyszeres kezelesek modositasa. (5)"<<endl;
                                cout<<"6.Birtokolt telkek modositasa. (6)"<<endl;
                                cout<<"7.Buntarsak modositasa. (7)"<<endl;
                                cout<<"8.Auto rendszam modositasa. (8)"<<endl;
                                cout<<"9.Vissza (Backspace)"<<endl;
                            }
                            modositas_print=false;
                            if( GetAsyncKeyState( VK_NUMPAD1 ) & 0x8000 ){
                                cout<<"Uj lakcim: ";
                                string lakcim;
                                cin>>lakcim;
                                fa.modosit_lakcim(nev,lakcim);
                                system("PAUSE");
                                system("CLS");
                                modositas_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD2 ) & 0x8000 ){
                                cout<<"Uj fogvatartasi hely: ";
                                string elzarva;
                                cin>>elzarva;
                                fa.modosit_elzarva(nev,elzarva);
                                system("PAUSE");
                                system("CLS");
                                modositas_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD3 ) & 0x8000 ){
                                cout<<"Uj gyakran latogatott helyszin: ";
                                string gyakran_mefordul;
                                cin>>gyakran_mefordul;
                                fa.modosit_gyakran_megfordul(nev,gyakran_mefordul);
                                system("PAUSE");
                                system("CLS");
                                modositas_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD4 ) & 0x8000 ){
                                cout<<"Uj banda, amelybe tagsagot nyert: ";
                                string banda;
                                cin>>banda;
                                fa.modosit_banda(nev,banda);
                                system("PAUSE");
                                system("CLS");
                                modositas_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD5 ) & 0x8000 ){
                                cout<<"Uj fuggoseg/gyogyszeres kezeles: ";
                                string fuggoseg_gyogyszer;
                                cin>>fuggoseg_gyogyszer;
                                fa.modosit_fuggoseg_gyogyszer(nev,fuggoseg_gyogyszer);
                                system("PAUSE");
                                system("CLS");
                                modositas_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD6 ) & 0x8000 ){
                                cout<<"Uj birtokolt telkek: ";
                                string birtokolt_telkek;
                                cin>>birtokolt_telkek;
                                fa.modosit_birtokolt_telkek(nev,birtokolt_telkek);
                                system("PAUSE");
                                system("CLS");
                                modositas_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD7 ) & 0x8000 ){
                                cout<<"Uj buntarsak: ";
                                string buntarsak;
                                cin>>buntarsak;
                                fa.modosit_buntarsak(nev,buntarsak);
                                system("PAUSE");
                                system("CLS");
                                modositas_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD8 ) & 0x8000 ){
                                cout<<"Uj auto rendszam: ";
                                string auto_rendszam;
                                cin>>auto_rendszam;
                                fa.modosit_auto_rendszam(nev,auto_rendszam);
                                system("PAUSE");
                                system("CLS");
                                modositas_print=true;
                            }
                            if( GetAsyncKeyState( VK_BACK ) & 0x8000 ){
                            modositas=false;
                            print2=true;
                            system("CLS");
                        }
                    }
                    }
                    system("PAUSE");
                    system("CLS");
                    print2=true;
                }
                if( GetAsyncKeyState( 'U' ) & 0x8000 ){
                    string knev,csnev,nev;
                    cout<<"Keresztnev: ";
                    cin>>knev;
                    cout<<"Csaladnev: ";
                    cin>>csnev;
                    nev=knev+" "+csnev;
                    elem* van=fa.Megvan(nev);
                    if(van==NULL)
                    {
                        cout<<"Nincs ilyen szemely az adatbazisban"<<endl;
                    }
                    else{
                        system("CLS");
                        bool elkovetett=true;
                        bool elkovetett_print=true;
                        while(elkovetett)
                        {
                            if(elkovetett_print)
                            {
                                fa.Kiir_adatok(van);
                                cout<<endl<<"######################################################"<<endl<<endl;
                                cout<<"Milyen buncselekmenyt kovetett el az illeto?"<<endl;
                                cout<<"0.bolti_lopas (0)"<<endl;
                                cout<<"1.nagyobb_lopas (1)"<<endl;
                                cout<<"2.bank_rablas (2)"<<endl;
                                cout<<"3.nem_szandekos_emberoles (3)"<<endl;
                                cout<<"4.gyilkossag (4)"<<endl;
                                cout<<"5.nemi_eroszak (5)"<<endl;
                                cout<<"6.csempeszet (6)"<<endl;
                                cout<<"7.drogkereskedelem (7)"<<endl;
                                cout<<"8.emberkereskedelem (8)"<<endl;
                                cout<<"9.fizikai_bantalmazas (9)"<<endl;
                                cout<<"10.Vissza (Backspace)"<<endl;
                            }
                            elkovetett_print=false;
                            if( GetAsyncKeyState( VK_NUMPAD0 ) & 0x8000 ){
                                cout<<"Megerositest kerek (I/N): ";
                                char c;
                                cin>>c;
                                if(c=='I' || c=='i')
                                    fa.elkovetett_bolti_lopas(nev);
                                else
                                    cout<<"Modositast elvetettuk."<<endl;
                                system("PAUSE");
                                system("CLS");
                                elkovetett_print=true;
                        }
                            if( GetAsyncKeyState( VK_NUMPAD1 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_nagyobb_lopas(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD2 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_bank_rablas(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD3 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_nem_szandekos_emberoles(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD4 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_gyilkossag(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD5 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_nemi_eroszak(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD6 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_csempeszet(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD7 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_drogkereskedelem(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD8 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_emberkereskedelem(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_NUMPAD9 ) & 0x8000 ){
                                    cout<<"Megerositest kerek (I/N): ";
                                    char c;
                                    cin>>c;
                                    if(c=='I' || c=='i')
                                        fa.elkovetett_fizikai_bantalmazas(nev);
                                    else
                                        cout<<"Modositast elvetettuk."<<endl;
                                    system("PAUSE");
                                    system("CLS");
                                    elkovetett_print=true;
                            }
                            if( GetAsyncKeyState( VK_BACK ) & 0x8000 ){
                                    elkovetett=false;
                                    print2=true;
                                    system("CLS");
                            }
                        }
                    }
                    system("PAUSE");
                    system("CLS");
                    print2=true;
                }
                if( GetAsyncKeyState( VK_BACK ) & 0x8000 ){
                    szerkesztes=false;
                    print=true;
                    system("CLS");
                }
                if( GetAsyncKeyState( 'T' ) & 0x8000 ){
                    string knev,csnev,nev;
                    cout<<"Keresztnev: ";
                    cin>>knev;
                    cout<<"Csaladnev: ";
                    cin>>csnev;
                    nev=knev+" "+csnev;
                    elem *p=fa.Keres_terit(nev);
                    if(p==NULL)
                        cout<<"Torlendo szemely nincs benne az adatbazisban."<<endl;
                    else{
                        fa.Torles(p);
                        cout<<"Sikeres torles!"<<endl;
                    }
                    system("PAUSE");
                    print2=true;
                    system("CLS");
                }
            }
        }
        if( GetAsyncKeyState( 'K' ) & 0x8000 )
        {
            bool kereses=true;
            system("CLS");
            bool print3=true;
            while(kereses)
            {
                if(print3)
                {
                    cout<<"1.Kereses nev szerint (N)"<<endl;
                    cout<<"2.Kiiras. (O)"<<endl;
                    cout<<"3.Vissza a fomenube. (Backspace)"<<endl;
                }
                print3=false;
                if( GetAsyncKeyState( 'N' ) & 0x8000 )
                {
                    string knev,csnev,nev;
                    cout<<"Keresztnev: ";
                    cin>>knev;
                    cout<<"Csaladnev: ";
                    cin>>csnev;
                    nev=knev;
                    nev+=" "+csnev;
                    fa.Keres(nev);
                    system("PAUSE");
                    system("CLS");
                    print3=true;
                }
                if( GetAsyncKeyState( 'O' ) & 0x8000 )
                {
                    cout<<"Nyilvantartott szemelyek listaja: "<<endl<<endl;
                    fa.Inorder();
                    system("PAUSE");
                    system("CLS");
                    print3=true;
                }
                if( GetAsyncKeyState( VK_BACK ) & 0x8000 )
                {
                    kereses=false;
                    print=true;
                    system("CLS");
                }
            }
        }
    }
}
