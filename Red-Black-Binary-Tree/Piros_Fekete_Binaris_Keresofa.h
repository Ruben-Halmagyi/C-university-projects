#ifndef __PIROS_FEKETE_BINARIS_KERESOFA_H_INCLUDED__
#define __PIROS_FEKETE_BINARIS_KERESOFA_H_INCLUDED__
#include <fstream>
using namespace std;
typedef enum szin {piros,fekete};
struct bunozo
{
    string nev, szul_datum, szemelyi_szam;
    int bolti_lopas, nagyobb_lopas, bank_rablas;
    int nem_szandekos_emberoles, gyilkossag, nemi_eroszak;
    int csempeszet, drogkereskedelem, emberkereskedelem;
    int fizikai_bantalmazas;
    string lakcim, elzarva, gyakran_megfordul;
    string banda, fuggoseg_gyogyszer;
    string birtokolt_telkek;
    string buntarsak;
    string auto_rendszam;
};
bunozo Beolvas_bunozo();
struct elem{
    elem *jobb, *bal, *szulo;
    int info;
    bunozo ficko;
    szin sz;
    elem(bunozo p)
    {
        bal=jobb=szulo=NULL;
        ficko=p;
        int rossz=0;
        if(p.bolti_lopas==1)
            rossz+=p.bolti_lopas;
        else
            rossz+=p.bolti_lopas*2;
        if(p.nagyobb_lopas==1)
            rossz+=2;
        else
            rossz+=p.nagyobb_lopas*3;
        if(p.bank_rablas==1)
            rossz+=3;
        else
            rossz+=p.bank_rablas*4;
        if(p.nem_szandekos_emberoles==1)
            rossz+=5;
        else{
            rossz+=(p.nem_szandekos_emberoles*5)*(p.nem_szandekos_emberoles*5);
        }
        if(p.gyilkossag==1)
            rossz+=7;
        else{
            rossz+=(p.gyilkossag*7)*(p.gyilkossag*7)*(p.gyilkossag*7);
        }
        if(p.nemi_eroszak==1)
            rossz+=6;
        else{
            rossz+=(p.nemi_eroszak*6)*(p.nemi_eroszak*6);
        }
        if(p.csempeszet==1)
            rossz+=4;
        else{
            rossz+=(p.csempeszet*4)*2;
        }
        if(p.drogkereskedelem==1)
            rossz+=5;
        else{
            rossz+=(p.drogkereskedelem*5)*2;
        }
        if(p.emberkereskedelem==1)
            rossz+=6;
        else{
            rossz+=(p.emberkereskedelem*6)*(p.emberkereskedelem*6)*(p.emberkereskedelem*6);
        }
        if(p.fizikai_bantalmazas==1)
            rossz+=5;
        else{
            rossz+=(p.fizikai_bantalmazas*5)*3;
        }
        (this)->info=rossz;
    }
};
class PFBK{
elem *gyoker;
public:
    PFBK(){ gyoker=NULL; }
    void Keres(string nev){pf_keres(nev, gyoker);};
    void Inorder(){pf_inorder(gyoker);}
    void Maximum();
    void Minimum();
    void Hozzaad_elem(bunozo p);
    void Torles(elem* n);
    void Beolvas_fajlbol_bunozo(ifstream &f);
    void Balraforgat(elem *&gyoker, elem *&p);
    void Jobbraforgat(elem *&gyoker, elem *&p);
    void Bovites(elem *&gyoker, elem *&p);
    void Problema_megoldas(elem *&gyoker, elem *&uj);
    void pf_inorder(elem *gyoker);
    elem* Megvan(string nev){return keres_pf(nev, gyoker);}
    elem* Keres_terit(string nev){return keres_pf(nev, gyoker);};
    void pf_keres(string nev, elem *gyoker);
    elem* keres_pf(string nev, elem *gyoker);
    void Kiir_adatok(elem *p);
    void modosit_lakcim(string nev, string lakcim);
    void modosit_elzarva(string nev, string elzarva);
    void modosit_gyakran_megfordul(string nev, string gyakran_mefordul);
    void modosit_banda(string nev, string banda);
    void modosit_fuggoseg_gyogyszer(string nev, string fuggoseg_gyogyszer);
    void modosit_birtokolt_telkek(string nev, string birtokolt_telkek);
    void modosit_buntarsak(string nev, string buntarsak);
    void modosit_auto_rendszam(string nev, string auto_rendszam);
    void elkovetett_bolti_lopas(string nev);
    void elkovetett_nagyobb_lopas(string nev);
    void elkovetett_bank_rablas(string nev);
    void elkovetett_nem_szandekos_emberoles(string nev);
    void elkovetett_gyilkossag(string nev);
    void elkovetett_nemi_eroszak(string nev);
    void elkovetett_csempeszet(string nev);
    void elkovetett_drogkereskedelem(string nev);
    void elkovetett_emberkereskedelem(string nev);
    void elkovetett_fizikai_bantalmazas(string nev);
    void veszelyesseg(elem *p);
    elem* Minimum(elem* p);
    elem* Kovetkezo(string nev);
    elem* Kovetkezo(elem *p);
    elem* Maximum(elem *p);
    elem* Elozo(string nev);
    void Masol_adat(elem *p, elem *q);
    void Torles_eset1(elem* n);
    void Torles_eset2(elem* n);
    elem* Teso(elem* n);
    void Torles_eset3(elem* n);
    void Torles_eset4(elem* n);
    void Torles_eset5(elem* n);
    void Torles_eset6(elem* n);
    szin elem_szin(elem* n);
    void Csere(elem* oldn, elem* newn);
};
void adatbazis();
void jatek(int n, bool &acces);
int random_szam_generalasa(int &n);
#endif
