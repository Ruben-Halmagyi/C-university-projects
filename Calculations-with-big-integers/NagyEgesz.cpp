#include <iostream>
#include "NagyEgesz.h"
using namespace std;

NagyEgesz::NagyEgesz(){
        n=1;
        elojel=1;
        a=new int[1];
        a[0]=0;
}
///NagyEgesz::~NagyEgesz(){delete []a;}
NagyEgesz::NagyEgesz(int e, int m, const int* szamjegyek){
        if(szamjegyek[0]==0 && m!=1)
            throw "Nem szabad 0 val kezdodjon a szam";
        elojel=e;
        n=m;
        a=new int[n];
        for(int i=0; i<n; i++)
            a[i]=szamjegyek[i];
    }
NagyEgesz::NagyEgesz(const NagyEgesz& b){
        elojel=b.elojel;
        n=b.n;
        a=new int[n];
        for(int i=0; i<n; i++)
            a[i]=b.a[i];
}
void NagyEgesz::kiir()const{
        if(elojel==-1)
            cout<<"-";
        for(int i=0; i<n; i++)
            cout<<a[i];
        cout<<endl;
}
bool NagyEgesz::egyenlo(const NagyEgesz& b){
    if(n!=b.n)
        return false;
    for(int i=0; i<n; i++)
        if(a[i]!=b.a[i])
            return false;
    return true;
}
bool NagyEgesz::egyenlo(const NagyEgesz& b, const NagyEgesz& c){
    if(c.n!=b.n)
        return false;
    for(int i=0; i<c.n; i++)
        if(c.a[i]!=b.a[i])
            return false;
    return true;
}
NagyEgesz NagyEgesz::osszead(const NagyEgesz& b){
    if(!osszehasonlit(b) && !egyenlo(b))
    {
        NagyEgesz c(b);
        c.osszead((*this));
        elojel=c.elojel;
        n=c.n;
        a=new int[n];
        for(int i=0; i<n; i++)
            a[i]=c.a[i];
    }
    else if(elojel==b.elojel){
        int r=n-1, t=b.n-1;
        while(r>=0 && t>=0){
            if(b.a[t]+a[r]<10)
                a[r]+=b.a[t];
            else{
                a[r-1]+=1;
                a[r]=(a[r]+b.a[t])%10;
            }

            r--;
            t--;
            if(r==0 && t==0)
                break;
        }
        if(r==0 && t==0){
            a[r]+=b.a[t];
            if(a[r]>10){
                n++;
                for(int i=n; i>0; i--){
                    a[i]=a[i-1];
                }
                a[0]=a[1]/10;
                a[1]=a[1]%10;
            }
        }
    }
    else if(elojel==1 && b.elojel==-1){
        if(egyenlo(b))
        {
            a[0]=0;
            n=1;
            elojel=1;
            return (*this);
        }
        else if(osszehasonlit(b)){
            elojel=-1;
            (*this).kivon(b);
            elojel=1;
        }
        else{
            elojel=-1;
            (*this).kivon(b);
            elojel=-1;
        }
    }
    else if(elojel==-1 && b.elojel==1){
        if(egyenlo(b))
        {
            a[0]=0;
            n=1;
            elojel=1;
            return (*this);
        }
        else if(osszehasonlit(b)){
            elojel=1;
            (*this).kivon(b);
            elojel=-1;
        }
        else{
            elojel=1;
            (*this).kivon(b);
            elojel=1;
        }
    }
    nullakat_kiszed();
    NagyEgesz eredmeny((*this));
    return eredmeny;
}
bool NagyEgesz::osszehasonlit(const NagyEgesz& b){
    int i=0;
    if(n>b.n)
        return true;
    else if(b.n>n)
        return false;
    else{
        while(a[i]==b.a[i] && i<n)
            i++;
        if(a[i]>b.a[i])
            return true;
        else
            return false;
    }
}
bool NagyEgesz::osszehasonlit(const NagyEgesz& a, const NagyEgesz& b){
    int i=0;
    if(a.n>b.n)
        return true;
    else if(b.n>a.n)
        return false;
    else{
        while(a.a[i]==b.a[i] && i<a.n)
            i++;
        if(a.a[i]>b.a[i])
            return true;
        else
            return false;
    }
}
NagyEgesz NagyEgesz::kivon(const NagyEgesz& b){
    if(egyenlo(b) && elojel==b.elojel)
    {
        a[0]=0;
        n=1;
        elojel=1;
        return (*this);
    }
    else if(elojel==b.elojel){
        if(osszehasonlit(b)){
            int r=n-1, t=b.n-1;
            while(r>=0 && t>=0){
                if(a[r]-b.a[t]>=0)
                {
                    a[r]-=b.a[t];
                }

                else{
                    a[r-1]--;
                    a[r]=(a[r]+10-b.a[t]);
                }
                r--;
                t--;
            }
        }
        else{
            if(!egyenlo(b))
            {
                NagyEgesz c(b);
                c.kivon((*this));
                elojel=c.elojel*(-1);
                n=c.n;
                a=new int[n];
                for(int i=0; i<n; i++)
                    a[i]=c.a[i];
            }
        }
    }
    else if(elojel==1 && b.elojel==-1){
            elojel=-1;
            (*this).osszead(b);
            elojel=1;
    }
    else if(elojel==-1 && b.elojel==1){
            elojel=1;
            (*this).osszead(b);
            elojel=-1;
    }
    nullakat_kiszed();
    NagyEgesz eredmeny((*this));
    return eredmeny;
}
NagyEgesz NagyEgesz::szoroz(const NagyEgesz& b){
    if((n==1 && a[0]==0) || (b.n==1 && b.a[0]==0))
    {
        n=1;
        a[0]=0;
        return (*this);
    }
    int c[n+b.n]={0};
    int k=(n+b.n);
    int l=(n+b.n);
    for(int i=(b.n)-1; i>=0; i--)
    {
        l--;
        k=l;
        for(int j=n-1; j>=0; j--)
        {
            c[k-1]=(c[k]+(a[j]*b.a[i]))/10+c[k-1];
            c[k]=(c[k]+(a[j]*b.a[i]))%10;
            /**cout<<c[k]<<" "<<a[j]<<" "<<b.a[i]<<" ";
            for(int g=0; g<n+b.n; g++)
                cout<<c[g];
            cout<<endl;**/
            k--;
        }
    }
    for(int i=0; i<n+b.n; i++)
        a[i]=c[i];
    n=n+b.n;
    if(elojel==1 && b.elojel==-1)
        elojel=-1;
    else if(elojel==-1 && b.elojel==-1)
        elojel=1;
    nullakat_kiszed();
    NagyEgesz eredmeny((*this));
    return eredmeny;
}
NagyEgesz NagyEgesz::nullakat_kiszed(){
    while(a[0]==0)
    {
        for(int i=0; i<n-1; i++)
            a[i]=a[i+1];
        n--;
    }
    return (*this);
}
NagyEgesz NagyEgesz::nullakat_kiszed(NagyEgesz& b){
    while(b.a[0]==0)
    {
        for(int i=0; i<b.n-1; i++)
            b.a[i]=b.a[i+1];
        b.n--;
    }
    return b;
}
NagyEgesz NagyEgesz::oszt(const NagyEgesz& b){
    int minusz=0;
    if(b.a[0]==0)
    {
        throw NullavalValoOsztas();
    }
    else if(!osszehasonlit(b)){
        a[0]=0;
        n=1;
    }
    else{
        if(b.elojel==-1)
        {
            minusz=1;
            //b.elojel=1;
        }
        NagyEgesz h(b);
        h.elojel=1;
        int c[n+b.n]={0};
        int k=0;
        int d[n+b.n];
        int szam=0;
        for(int i=0; i<n; i++)
        {
            d[i]=a[i];
        }
        NagyEgesz osztas(1,b.n,d);
        int l=n;
        while(l>=b.n){
            szam=0;
            while(osszehasonlit(osztas,h) || egyenlo(osztas,h))
            {
                osztas.kivon(h);
                szam++;
            }
            if(osztas.a[0]==0 && osztas.n!=1)
                nullakat_kiszed(osztas);
            c[k]=szam;
            k++;
            for(int i=0; i<l; i++)
                d[i]=d[i+1];
            l--;
                osztas.a[osztas.n]=d[b.n-1];
                osztas.n++;
        }
        for(int i=0; i<k; i++)
            a[i]=c[i];
        n=k;
        if(minusz==1)
            elojel*=-1;
        nullakat_kiszed();
    }
    NagyEgesz eredmeny((*this));
    return eredmeny;
}
