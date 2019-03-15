#ifndef __NAGYEGESZ_H_INCLUDED__
#define __NAGYEGESZ_H_INCLUDED__
class NagyEgesz{
int n;
int elojel;
int *a;
public:
    NagyEgesz();
    ///~NagyEgesz();
    NagyEgesz(int e, int m, const int* szamjegyek);
    NagyEgesz(const NagyEgesz&b);
    void kiir() const;
    NagyEgesz osszead(const NagyEgesz& b);
    NagyEgesz kivon(const NagyEgesz& b);
    bool osszehasonlit(const NagyEgesz& b);
    bool egyenlo(const NagyEgesz& b);
    bool egyenlo(const NagyEgesz& b, const NagyEgesz& c);
    NagyEgesz szoroz(const NagyEgesz& b);
    NagyEgesz oszt(const NagyEgesz& b);
    NagyEgesz nullakat_kiszed();
    bool osszehasonlit(const NagyEgesz& a, const NagyEgesz& b);
    NagyEgesz nullakat_kiszed(NagyEgesz& b);
    class NullavalValoOsztas{};
};
#endif
