#include <iostream>
#include <fstream>
#include <cassert>
#include <windows.h>
#include "Piros_Fekete_Binaris_Keresofa.h"
using namespace std;
void PFBK::Balraforgat(elem *&gyoker, elem *&p){
    elem *p_jobb=p->jobb;
    p->jobb=p_jobb->bal;
    if(p_jobb->bal!=NULL)
        p_jobb->bal->szulo=p;
    p_jobb->szulo=p->szulo;
    if(p->szulo==NULL)
        gyoker=p_jobb;
    else if(p==p->szulo->bal)
        p->szulo->bal=p_jobb;
    else
        p->szulo->jobb=p_jobb;
    p_jobb->bal=p;
    p->szulo=p_jobb;
}
void PFBK::Jobbraforgat(elem *&gyoker, elem *&p){
    elem *p_bal=p->bal;
    p->bal=p_bal->jobb;
    if(p->bal!=NULL)
        p->bal->szulo=p;
    p_bal->szulo=p->szulo;
    if(p->szulo==NULL)
        gyoker=p_bal;
    else if(p==p->szulo->bal)
        p->szulo->bal=p_bal;
    else
        p->szulo->jobb=p_bal;
    p_bal->jobb=p;
    p->szulo=p_bal;
}
void PFBK::pf_inorder(elem *gyoker){
    if(gyoker==NULL)
        return;
    pf_inorder(gyoker->bal);
    cout<<gyoker->ficko.nev;/**<<"  "<<gyoker->sz<<" ";
    if(gyoker->bal!=NULL)
        cout<<gyoker->bal->ficko.nev<<"  ";
    if(gyoker->jobb!=NULL)
        cout<<gyoker->jobb->ficko.nev<<"  ";*/
    cout<<endl;
    pf_inorder(gyoker->jobb);
}
void PFBK::Bovites(elem *&gyoker, elem *&uj){
    elem *q=NULL;
    elem *p=gyoker;
    while(p!=NULL)
    {
        q=p;
        if(uj->ficko.nev<p->ficko.nev)
            p=p->bal;
        else
            p=p->jobb;
    }

    uj->szulo=q;
    if(q==NULL)
        gyoker=uj;
    else{
        if(uj->ficko.nev<q->ficko.nev)
            q->bal=uj;
        else
            q->jobb=uj;
    }
}
void PFBK::Problema_megoldas(elem *&gyoker, elem *&uj){
    elem *szulo_uj = NULL;
    elem *nagyszulo_uj = NULL;
    while((uj != gyoker)&&(uj->sz != fekete)&&(uj->szulo->sz == piros))
    {
        szulo_uj=uj->szulo;
        nagyszulo_uj=uj->szulo->szulo;
        if(szulo_uj==nagyszulo_uj->bal)
        {
            elem *nagybacsi_uj = nagyszulo_uj->jobb;
            if (nagybacsi_uj != NULL && nagybacsi_uj->sz == piros)
            {
                nagyszulo_uj->sz = piros;
                szulo_uj->sz = fekete;
                nagybacsi_uj->sz = fekete;
                uj = nagyszulo_uj;
            }
            else
            {
                if (uj == szulo_uj->jobb)
                {
                    Balraforgat(gyoker, szulo_uj);
                    uj = szulo_uj;
                    szulo_uj = uj->szulo;
                }
                Jobbraforgat(gyoker, nagyszulo_uj);
                swap(szulo_uj->sz, nagyszulo_uj->sz);
                uj = szulo_uj;
            }
        }
        else
        {
            elem *nagybacsi_uj = nagyszulo_uj->bal;
            if ((nagybacsi_uj != NULL) && (nagybacsi_uj->sz == piros))
            {
                nagyszulo_uj->sz = piros;
                szulo_uj->sz = fekete;
                nagybacsi_uj->sz = fekete;
                uj = nagyszulo_uj;
            }
            else
            {
                if (uj == szulo_uj->bal)
                {
                    Jobbraforgat(gyoker, szulo_uj);
                    uj = szulo_uj;
                    szulo_uj = uj->szulo;
                }
                Balraforgat(gyoker, nagyszulo_uj);
                swap(szulo_uj->sz, nagyszulo_uj->sz);
                uj = szulo_uj;
            }
        }
    }
    gyoker->sz = fekete;
}
void PFBK::pf_keres(string nev, elem *gyoker){
    if(gyoker==NULL)
        cout<<"Az adatbazis ures.";
    if(gyoker->ficko.nev==nev)
        Kiir_adatok(gyoker);
    else if(gyoker->ficko.nev<=nev)
    {
        if(gyoker->jobb!=NULL)
            pf_keres(nev, gyoker->jobb);
        else
            cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
    }
    else
    {
        if(gyoker->bal!=NULL)
            pf_keres(nev, gyoker->bal);
        else
            cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
    }
}
void PFBK::Kiir_adatok(elem *p){
    cout<<"Nev: "<<p->ficko.nev<<endl;
    cout<<"Szuletesi datum: "<<p->ficko.szul_datum<<endl;
    cout<<"Szemelyi szam: "<<p->ficko.szemelyi_szam<<endl;
    cout<<"Lakcim: "<<p->ficko.lakcim<<endl;
    cout<<"Elzarva: "<<p->ficko.elzarva<<endl;
    cout<<"Gyakran megfordult: "<<p->ficko.gyakran_megfordul<<endl;
    cout<<"Banda: "<<p->ficko.banda<<endl;
    cout<<"Fuggosegek/gyogyszeres kezeles: "<<p->ficko.fuggoseg_gyogyszer<<endl;
    cout<<"Birtokolt telkek: "<<p->ficko.birtokolt_telkek<<endl;
    cout<<"Buntarsak: "<<p->ficko.buntarsak<<endl;
    cout<<"Auto rendszama: "<<p->ficko.auto_rendszam<<endl;
    if(p->ficko.bolti_lopas!=0)
        cout<<"Bolti lopast elkovetett: "<<p->ficko.bolti_lopas<<endl;
    if(p->ficko.nagyobb_lopas!=0)
        cout<<"Nagyobbmeretu lopast elkovetett: "<<p->ficko.nagyobb_lopas<<endl;
    if(p->ficko.bank_rablas!=0)
        cout<<"Bankrablast elkovetett: "<<p->ficko.bank_rablas<<endl;
    if(p->ficko.nem_szandekos_emberoles!=0)
        cout<<"Nem szandekos emberoles: "<<p->ficko.nem_szandekos_emberoles<<endl;
    if(p->ficko.gyilkossag!=0)
        cout<<"Gyilkossag: "<<p->ficko.gyilkossag<<endl;
    if(p->ficko.nemi_eroszak!=0)
        cout<<"Nemi eroszak: "<<p->ficko.nemi_eroszak<<endl;
    if(p->ficko.csempeszet!=0)
        cout<<"Csempeszet: "<<p->ficko.csempeszet<<endl;
    if(p->ficko.drogkereskedelem!=0)
        cout<<"Drogkereskedelem: "<<p->ficko.drogkereskedelem<<endl;
    if(p->ficko.emberkereskedelem!=0)
        cout<<"Emberkereskedelem: "<<p->ficko.emberkereskedelem<<endl;
    if(p->ficko.fizikai_bantalmazas!=0)
        cout<<"Fizikai bantalmazas: "<<p->ficko.fizikai_bantalmazas<<endl;
    cout<<"Veszelyessegi szint: "<<p->info<<endl;
}
elem* PFBK::keres_pf(string nev, elem *gyoker){
    if(gyoker==NULL)
        return NULL;
    if(gyoker->ficko.nev==nev)
    {
        return (gyoker);
    }
    else if(gyoker->ficko.nev<=nev)
    {
        if(gyoker->jobb!=NULL)
            return keres_pf(nev, gyoker->jobb);
        else
            return NULL;
    }
    else
    {
        if(gyoker->bal!=NULL)
            return keres_pf(nev, gyoker->bal);
        else
            return NULL;
    }
}
void PFBK::modosit_lakcim(string nev, string lakcim){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.lakcim=lakcim;
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::modosit_elzarva(string nev, string elzarva){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.elzarva=elzarva;
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::modosit_gyakran_megfordul(string nev, string gyakran_mefordul){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.gyakran_megfordul=gyakran_mefordul;
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::modosit_banda(string nev, string banda){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.banda=banda;
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::modosit_fuggoseg_gyogyszer(string nev, string fuggoseg_gyogyszer){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.fuggoseg_gyogyszer=fuggoseg_gyogyszer;
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::modosit_birtokolt_telkek(string nev, string birtokolt_telkek){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.birtokolt_telkek=birtokolt_telkek;
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::modosit_buntarsak(string nev, string buntarsak){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.buntarsak=buntarsak;
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::modosit_auto_rendszam(string nev, string auto_rendszam){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.auto_rendszam=auto_rendszam;
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_bolti_lopas(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.bolti_lopas++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_nagyobb_lopas(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.nagyobb_lopas++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_bank_rablas(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.bank_rablas++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_nem_szandekos_emberoles(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.nem_szandekos_emberoles++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_gyilkossag(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.gyilkossag++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_nemi_eroszak(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.nemi_eroszak++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_csempeszet(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.csempeszet++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_drogkereskedelem(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.drogkereskedelem++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_emberkereskedelem(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.emberkereskedelem++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::elkovetett_fizikai_bantalmazas(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p==NULL)
    {
        cout<<"Nincs ilyen szemely az adatbazisban."<<endl;
        return;
    }
    else
        p->ficko.fizikai_bantalmazas++;
    veszelyesseg(p);
    cout<<"Sikeres modositas!"<<endl;
}
void PFBK::veszelyesseg(elem *p){
    int rossz=0;
    if(p->ficko.bolti_lopas==1)
        rossz+=p->ficko.bolti_lopas;
    else
        rossz+=p->ficko.bolti_lopas*2;
    if(p->ficko.nagyobb_lopas==1)
        rossz+=2;
    else
        rossz+=p->ficko.nagyobb_lopas*3;
    if(p->ficko.bank_rablas==1)
        rossz+=3;
    else
        rossz+=p->ficko.bank_rablas*4;
    if(p->ficko.nem_szandekos_emberoles==1)
        rossz+=5;
    else{
        rossz+=(p->ficko.nem_szandekos_emberoles*5)*(p->ficko.nem_szandekos_emberoles*5);
    }
    if(p->ficko.gyilkossag==1)
        rossz+=7;
    else{
        rossz+=(p->ficko.gyilkossag*7)*(p->ficko.gyilkossag*7)*(p->ficko.gyilkossag*7);
    }
    if(p->ficko.nemi_eroszak==1)
        rossz+=6;
    else{
        rossz+=(p->ficko.nemi_eroszak*6)*(p->ficko.nemi_eroszak*6);
    }
    if(p->ficko.csempeszet==1)
        rossz+=4;
    else{
        rossz+=(p->ficko.csempeszet*4)*2;
    }
    if(p->ficko.drogkereskedelem==1)
        rossz+=5;
    else{
        rossz+=(p->ficko.drogkereskedelem*5)*2;
    }
    if(p->ficko.emberkereskedelem==1)
        rossz+=6;
    else{
        rossz+=(p->ficko.emberkereskedelem*6)*(p->ficko.emberkereskedelem*6)*(p->ficko.emberkereskedelem*6);
    }
    if(p->ficko.fizikai_bantalmazas==1)
        rossz+=5;
    else{
        rossz+=(p->ficko.fizikai_bantalmazas*5)*3;
    }
    p->info=rossz;
}
void PFBK::Minimum(){
    elem *p=gyoker;
    if(p==NULL)
        cout<<"Az adatbazis ures";
    else{
        while(p->bal!=NULL)
            p=p->bal;
        Kiir_adatok(p);
    }
}
void PFBK::Maximum(){
    elem *p=gyoker;
    if(p==NULL)
        cout<<"Az adatbazis ures";
    else{
        while(p->jobb!=NULL)
            p=p->jobb;
        Kiir_adatok(p);
    }
}
elem* PFBK::Minimum(elem *p){
    if(p==NULL)
    {
        return NULL;
    }
    else{
        while(p->bal!=NULL)
            p=p->bal;
        return p;
    }
}
elem* PFBK::Maximum(elem *p){
    if(p==NULL)
    {
        return NULL;
    }
    else{
        while(p->jobb!=NULL)
            p=p->jobb;
        return p;
    }
}
elem* PFBK::Kovetkezo(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p->jobb!=NULL)
    {
        p=Minimum(p->jobb);
        return p;
    }
    else
    {
        if(Maximum(gyoker)==p)
        {
            cout<<"Maximalis elem.";
            return NULL;
        }
        elem *seged=p->szulo;
        while(seged!=NULL && p==seged->jobb)
        {
            p=seged;
            seged=seged->szulo;
        }
        return seged;
    }
}
elem* PFBK::Kovetkezo(elem *p){
    if(p->jobb!=NULL)
    {
        p=Minimum(p->jobb);
        return p;
    }
    else
    {
        if(Maximum(gyoker)==p)
        {
            cout<<"Maximalis elem.";
            return NULL;
        }
        elem *seged=p->szulo;
        while(seged!=NULL && p==seged->jobb)
        {
            p=seged;
            seged=seged->szulo;
        }
        return seged;
    }
}
elem* PFBK::Elozo(string nev){
    elem *p=keres_pf(nev,gyoker);
    if(p->bal!=NULL)
    {
        p=Maximum(p->jobb);
        return p;
    }
    else
    {
        if(Minimum(gyoker)==p)
        {
            cout<<"Minimum elem.";
            return NULL;
        }
        elem *seged=p->szulo;
        while(seged!=NULL && p==seged->bal)
        {
            p=seged;
            seged=seged->szulo;
        }
        return seged;
    }
}
void PFBK::Masol_adat(elem *p, elem *q){
    p->ficko.nev=q->ficko.nev;
    p->ficko.szul_datum=q->ficko.szul_datum;
    p->ficko.szemelyi_szam=q->ficko.szemelyi_szam;
    p->ficko.bolti_lopas=q->ficko.bolti_lopas;
    p->ficko.nagyobb_lopas=q->ficko.nagyobb_lopas;
    p->ficko.bank_rablas=q->ficko.bank_rablas;
    p->ficko.nem_szandekos_emberoles=q->ficko.nem_szandekos_emberoles;
    p->ficko.gyilkossag=q->ficko.gyilkossag;
    p->ficko.nemi_eroszak=q->ficko.nemi_eroszak;
    p->ficko.csempeszet=q->ficko.csempeszet;
    p->ficko.drogkereskedelem=q->ficko.drogkereskedelem;
    p->ficko.emberkereskedelem=q->ficko.emberkereskedelem;
    p->ficko.fizikai_bantalmazas=q->ficko.fizikai_bantalmazas;
    p->ficko.lakcim=q->ficko.lakcim;
    p->ficko.elzarva=q->ficko.elzarva;
    p->ficko.gyakran_megfordul=q->ficko.gyakran_megfordul;
    p->ficko.banda=q->ficko.banda;
    p->ficko.fuggoseg_gyogyszer=q->ficko.fuggoseg_gyogyszer;
    p->ficko.birtokolt_telkek=q->ficko.birtokolt_telkek;
    p->ficko.buntarsak=q->ficko.buntarsak;
    p->ficko.auto_rendszam=q->ficko.auto_rendszam;
}
void PFBK::Torles(elem* n){
    elem* fiu;
    if(n==NULL)
        return;
    if(n->bal!=NULL && n->jobb!=NULL)
    {
        elem* seged=Maximum(n->bal);
        Masol_adat(n,seged);
        n=seged;
    }
    assert(n->bal==NULL || n->jobb==NULL);
    fiu= n->jobb == NULL ? n->bal : n->jobb;
    if(n->sz==fekete)
    {
        n->sz=elem_szin(fiu);
        Torles_eset1(n);
    }
    Csere(n,fiu);
}
void PFBK::Torles_eset1(elem* n){
    if (n->szulo==NULL)
        return;
    else
        Torles_eset2(n);
}
void PFBK::Torles_eset2(elem* n){
    if (elem_szin(Teso(n))==piros)
    {
        n->szulo->sz=piros;
        Teso(n)->sz=fekete;
        if (n==n->szulo->bal)
            Balraforgat(gyoker,n->szulo);
        else
            Jobbraforgat(gyoker,n->szulo);
    }
    Torles_eset3(n);
}
elem* PFBK::Teso(elem* n){
    assert (n!=NULL);
    assert (n->szulo!=NULL);
    if (n==n->szulo->bal)
        return n->szulo->jobb;
    else
        return n->szulo->bal;
}
void PFBK::Torles_eset3(elem* n){
    if (n->szulo->sz==fekete && elem_szin(Teso(n))==fekete && elem_szin(Teso(n)->bal)==fekete && elem_szin(Teso(n)->jobb)==fekete)
    {
        Teso(n)->sz=piros;
        Torles_eset1(n->szulo);
    }
    else
        Torles_eset4(n);
}
void PFBK::Torles_eset4(elem* n){
    if (n->szulo->sz==piros && elem_szin(Teso(n))==fekete && elem_szin(Teso(n)->bal)==fekete && elem_szin(Teso(n)->jobb)==fekete)
    {
        Teso(n)->sz=piros;
        n->szulo->sz=fekete;
    }
    else
        Torles_eset5(n);
}
void PFBK::Torles_eset5(elem* n){
    if (n==n->szulo->bal && elem_szin(Teso(n))==fekete && elem_szin(Teso(n)->bal)==piros && elem_szin(Teso(n)->jobb)==fekete)
    {
        Teso(n)->sz=piros;
        Teso(n)->bal->sz=fekete;
        elem* tes=Teso(n);
        Jobbraforgat(gyoker,tes);
    }
    else if (n==n->szulo->jobb && elem_szin(Teso(n))==fekete && elem_szin(Teso(n)->jobb)==piros && elem_szin(Teso(n)->bal)==fekete)
    {
        Teso(n)->sz=piros;
        Teso(n)->jobb->sz=fekete;
        elem* tes=Teso(n);
        Balraforgat(gyoker,tes);
    }
    Torles_eset6(n);
}
void PFBK::Torles_eset6(elem* n){
    Teso(n)->sz=elem_szin(n->szulo);
    n->szulo->sz=fekete;
    if(n==n->szulo->bal)
    {
        assert (elem_szin(Teso(n)->jobb)==piros);
        Teso(n)->jobb->sz=fekete;
        Balraforgat(gyoker,n->szulo);
    }
    else
    {
        assert (elem_szin(Teso(n)->bal)==piros);
        Teso(n)->bal->sz=fekete;
        Jobbraforgat(gyoker,n->szulo);
    }
}
void PFBK::Csere(elem* oldn, elem* newn){
    if(oldn->szulo==NULL)
    {
        gyoker = newn;
    }
    else
    {
        if(oldn==oldn->szulo->bal)
            oldn->szulo->bal=newn;
        else
            oldn->szulo->jobb=newn;
    }
    if(newn!=NULL)
    {
        newn->szulo=oldn->szulo;
    }
}
szin PFBK::elem_szin(elem* n){
    return n == NULL ? fekete : n->sz;
}
bunozo Beolvas_bunozo(){
    cout<<"Atlalanos infok: "<<endl;
    string knev,csnev,nev,sz_d,sz_sz,lak,el,gy_m,ban,fugg,bir,bun,aut;
    cout<<"Keresztnev: ";
    cin>>knev;
    cout<<"Csaladnev: ";
    cin>>csnev;
    nev=knev+" "+csnev;
    cout<<"Szuletesi datum: ";
    cin>>sz_d;
    cout<<"Szemelyi szam: ";
    cin>>sz_sz;
    cout<<"Lakcim: ";
    cin>>lak;
    cout<<"Elzarva: ";
    cin>>el;
    cout<<"Gyakran megfordult: ";
    cin>>gy_m;
    cout<<"Banda: ";
    cin>>ban;
    cout<<"Fuggosegek/gyogyszeres kezeles: ";
    cin>>fugg;
    cout<<"Birtokolt telkek: ";
    cin>>bir;
    cout<<"Buntarsak: ";
    cin>>bun;
    cout<<"Auto rendszama: ";
    cin>>aut;
    system("CLS");
    cout<<"Elkovetett buncselekmenyek: "<<endl;
    int b_l,n_l,b_r,n_sz_e,gy,n_e,cs,d_k,e_k,f_b;
    cout<<"Bolti lopast elkovetett (hanyszor): ";
    cin>>b_l;
    cout<<"Nagyobbmeretu lopast elkovetett (hanyszor): ";
    cin>>n_l;
    cout<<"Bankrablast elkovetett (hanyszor): ";
    cin>>b_r;
    cout<<"Nem szandekos emberoles (hanyszor): ";
    cin>>n_sz_e;
    cout<<"Gyilkossag (hanyszor): ";
    cin>>gy;
    cout<<"Nemi eroszak (hanyszor): ";
    cin>>n_e;
    cout<<"Csempeszet (hanyszor): ";
    cin>>cs;
    cout<<"Drogkereskedelem (hanyszor): ";
    cin>>d_k;
    cout<<"Emberkereskedelem (hanyszor): ";
    cin>>e_k;
    cout<<"Fizikai bantalmazas (hanyszor): ";
    cin>>f_b;
    bunozo uj;
    uj.nev=nev;
    uj.szul_datum=sz_d;
    uj.szemelyi_szam=sz_sz;
    uj.bolti_lopas=b_l;
    uj.nagyobb_lopas=n_l;
    uj.bank_rablas=b_r;
    uj.nem_szandekos_emberoles=n_sz_e;
    uj.gyilkossag=gy;
    uj.nemi_eroszak=n_e;
    uj.csempeszet=cs;
    uj.drogkereskedelem=d_k;
    uj.emberkereskedelem=e_k;
    uj.fizikai_bantalmazas=f_b;
    uj.lakcim=lak;
    uj.elzarva=el;
    uj.gyakran_megfordul=gy_m;
    uj.banda=ban;
    uj.fuggoseg_gyogyszer=fugg;
    uj.birtokolt_telkek=bir;
    uj.buntarsak=bun;
    uj.auto_rendszam=aut;
    return uj;
}
void PFBK::Hozzaad_elem(bunozo p){
    elem *uj=new elem(p);
    uj->sz=piros;
    Bovites(gyoker,uj);
    Problema_megoldas(gyoker,uj);
}
void PFBK::Beolvas_fajlbol_bunozo(ifstream &f){
    string knev,csnev,nev,sz_d,sz_sz,lak,el,gy_m,ban,fugg,bir,bun,aut;
    int b_l,n_l,b_r,n_sz_e,gy,n_e,cs,d_k,e_k,f_b;
    while(f>>knev>>csnev>>sz_d>>sz_sz>>b_l>>n_l>>b_r>>n_sz_e>>gy>>n_e>>cs>>d_k>>e_k>>f_b>>lak>>el>>gy_m>>ban>>fugg>>bir>>bun>>aut)
    {
        nev=knev+" "+csnev;
        bunozo uj;
        uj.nev=nev;
        uj.szul_datum=sz_d;
        uj.szemelyi_szam=sz_sz;
        uj.bolti_lopas=b_l;
        uj.nagyobb_lopas=n_l;
        uj.bank_rablas=b_r;
        uj.nem_szandekos_emberoles=n_sz_e;
        uj.gyilkossag=gy;
        uj.nemi_eroszak=n_e;
        uj.csempeszet=cs;
        uj.drogkereskedelem=d_k;
        uj.emberkereskedelem=e_k;
        uj.fizikai_bantalmazas=f_b;
        uj.lakcim=lak;
        uj.elzarva=el;
        uj.gyakran_megfordul=gy_m;
        uj.banda=ban;
        uj.fuggoseg_gyogyszer=fugg;
        uj.birtokolt_telkek=bir;
        uj.buntarsak=bun;
        uj.auto_rendszam=aut;
        Hozzaad_elem(uj);
    }
}

