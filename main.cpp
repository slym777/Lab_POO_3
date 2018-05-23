/// !In atentia utilizatorului:
/// 1: Elementele in obiecte de tip int, float si double vor fi introduse in ordine inversa
/// 2: Pentru obiectele de tip char a fost implementata doar operatia +


#include <iostream>
#include <bits/stdc++.h>

using namespace std;

template <class T> class Nr_Natural_Mare;   /// am declarat clasa aici pentru ca sa o pot folosi in clasa Vector,
template <class T> class Numar_Intreg_mare;

template<class T>
ostream& operator<<(ostream&, const Nr_Natural_Mare<T>&);

template<class T>
istream& operator>>(istream&, Nr_Natural_Mare<T>&);

template < class T >
istream& operator>> (istream&, Numar_Intreg_mare<T>&);

template <class T>
class Vector
{
    T *a;
public:
    Vector (){ a = NULL; }
    ~Vector(){ delete[] a; }
    friend class Nr_Natural_Mare<T>;    /// am declarat clasa prietena pentru a avea acces la membrul a din clasa Vector
    friend class Numar_Intreg_mare<T>;  /// am declarat clasa prietena pentru a avea acces la membrul a din clasa Vector
    friend istream& operator>> <>(istream&, Nr_Natural_Mare<T>&);
    friend ostream& operator<< <>(ostream&, const Nr_Natural_Mare<T>&);
};

template <class T> class Nr_Natural_Mare
{
protected:
    int nrcfr;
    Vector<T> V;
public:
    void eliminare_0();                                                 /// functie ce elimineaza 0 din stanga numarului. Exemplu: 034 = 34
    Nr_Natural_Mare (){ nrcfr = 0;}                                      /// constructor de initializare fara parametri
    Nr_Natural_Mare (int n) { nrcfr = n; V.a = new T [nrcfr]; }        /// constructor de initializare cu 1 parametru
    Nr_Natural_Mare (int, T*a);                                       /// constructor de initializare cu 2 parametri
    virtual ~Nr_Natural_Mare () { nrcfr = 0; V.~Vector(); }              /// destructor declarat virtual, pentru ca facand upcasting sa se apeleze mai intia destructorul clasei derivate
    Nr_Natural_Mare (const Nr_Natural_Mare<T>&);                            /// constr copiere
    Nr_Natural_Mare<T>& operator= (const Nr_Natural_Mare<T>&);                 /// supraincarcarea operaorului =
    friend istream& operator>> <>(istream&, Nr_Natural_Mare<T>&);             /// supraincarcarea operatorului >>
    friend ostream& operator<< <>(ostream&, const Nr_Natural_Mare<T>&);       /// supraincarcarea operatorului <<
    virtual void afisare(ostream& out) const                            /// functie de afisare pe care o folosesc in definirea operatorului <<, am declarato virtuala ca sa pot folosi acceasi definire a operatorului << si pentru clasa derivata
    {
        for(int i = nrcfr-1; i >= 0; i--)
            out << V.a[i];
        out << endl;
    }
    Nr_Natural_Mare<T>& operator+ (const Nr_Natural_Mare<T>&);                /// supraincarcarea operatorului +
    Nr_Natural_Mare<T>& operator- (const Nr_Natural_Mare<T>&);                /// supraincarcarea operatorului -
    Nr_Natural_Mare<T>& operator* (const Nr_Natural_Mare<T>&);                /// supraincarcarea operatorului *
};

template<>
class Nr_Natural_Mare<char>
{
protected:
    int nrcfr;
    Vector<char> V;
public:
    void eliminare_0();
    Nr_Natural_Mare (){ nrcfr = 0;}                                      /// constructor de initializare fara parametri
    Nr_Natural_Mare (int n) { nrcfr = n; V.a = new char [nrcfr]; }        /// constructor de initializare cu 1 parametru
    Nr_Natural_Mare (int, char*a);                                       /// constructor de initializare cu 2 parametri
    virtual ~Nr_Natural_Mare () { nrcfr = 0; V.~Vector(); }              /// destructor declarat virtual, pentru ca facand upcasting sa se apeleze mai intia destructorul clasei derivate
    Nr_Natural_Mare (const Nr_Natural_Mare<char>&);                            /// constr copiere
    Nr_Natural_Mare<char>& operator= (const Nr_Natural_Mare<char>&);                 /// supraincarcarea operaorului =
    friend istream& operator>> <>(istream&, Nr_Natural_Mare<char>&);             /// supraincarcarea operatorului >>
    friend ostream& operator<< <>(ostream&, const Nr_Natural_Mare<char>&);       /// supraincarcarea operatorului <<
    virtual void afisare(ostream& out) const                            /// functie de afisare pe care o folosesc in definirea operatorului <<, am declarato virtuala ca sa pot folosi acceasi definire a operatorului << si pentru clasa derivata
    {
        for(int i = 0; i < nrcfr; i++)
            out << V.a[i];
        out << endl;
    }
    Nr_Natural_Mare<char>& operator+ (const Nr_Natural_Mare<char>&);                /// supraincarcarea operatorului +
};

template < class T >
class Numar_Intreg_mare : public Nr_Natural_Mare<T>
{
    char semn;
public:
    Numar_Intreg_mare () : Nr_Natural_Mare<T>() { semn = 0; }
    Numar_Intreg_mare (int n) : Nr_Natural_Mare<T>(n) { semn = 0; }
    Numar_Intreg_mare (int n, T*a): Nr_Natural_Mare<T>(n,a) { semn = 0;}
    Numar_Intreg_mare (int n, T*a, char c) : Nr_Natural_Mare<T>(n,a) { semn = c; }
    ~Numar_Intreg_mare (){ semn = 0;}
    Numar_Intreg_mare (const Numar_Intreg_mare<T>& x) : Nr_Natural_Mare<T>(x) { semn = x.semn;}
    Numar_Intreg_mare<T>& operator= (const Numar_Intreg_mare<T>& x)
    {
        if (this != &x)
        {
            this->Nr_Natural_Mare<T>::operator=(x);
            semn = x.semn;
        }
        return *this;
    }
    friend istream& operator>> <>(istream&, Numar_Intreg_mare<T>&);
    void afisare (ostream& out) const
    {
        out << semn;
        this->Nr_Natural_Mare<T>::afisare(out);
    }
    Numar_Intreg_mare<T>& operator+ (const Numar_Intreg_mare<T>&);
    Numar_Intreg_mare<T>& operator- (const Numar_Intreg_mare<T>&);
    Numar_Intreg_mare<T>& operator* (const Numar_Intreg_mare<T>&);
};

/// definire pentru toate clasa Nr_Natural_Mare generica
template <class T>
Nr_Natural_Mare<T>::Nr_Natural_Mare(int n, T* x)
{
    nrcfr = n;
    V.a = new T [nrcfr];
    for (int i = 0; i < nrcfr; i++)
        V.a[i] = x[i];
    eliminare_0();
}

template <class T>
Nr_Natural_Mare<T>::Nr_Natural_Mare(const Nr_Natural_Mare<T>& x)
{
    nrcfr = x.nrcfr;
    V.a = new T [nrcfr];
    for (int i = 0; i < nrcfr; i++)
        V.a[i] = x.V.a[i];
}

template <class T>
Nr_Natural_Mare<T>& Nr_Natural_Mare<T>::operator= (const Nr_Natural_Mare<T>& x)
{
    if (this != &x)
    {
        nrcfr = x.nrcfr;
        V.a = new T[nrcfr];
        for (int i = 0; i < nrcfr; i++)
            V.a[i] = x.V.a[i];
    }
    return *this;
}

template <class T>
ostream& operator<< (ostream& out, const Nr_Natural_Mare<T>& x)
{
    x.afisare(out); /// folosesc functia virtuala afisare, astfel aceasta definire a operatorului << va fi valabila si pentru clasele derivate care au ca metode functia de afisare
    return out;
}

int exceptie_1(string s, int flag)
{
    try
    {
        for( int  i = 0 ; i < (int)s.size(); i++)
        {
           // cout << s[i] << endl;
            if (s[i] < '0' or s[i] > '9')
                throw s;
        }
        flag = 0;
    }
    catch(string s){ cout << " Ati introdus o valoare gresita, introduceti din nou"; flag = 1;}
    //cout << flag;
    return flag;
}

template <class T>
istream& operator>> (istream& in, Nr_Natural_Mare<T>& x)
{
    x.nrcfr = 0; //T a;
    int flag = 1;  string s;
    cout << " Dati nr de elemente\n";
    do
    {
        in >> s;
        flag = exceptie_1(s,flag);
    }
    while(flag != 0);

    for (int i = 0; i < (int)s.size(); i++)
        {
            x.nrcfr += (s[i]-48)*pow(10,s.size()-i-1);
            //cout << x.nrcfr << endl;
        }

    cout << x.nrcfr << endl;
    cout << " Dati elemente\n";
    x.V.a = new T [x.nrcfr];
    for (int i = 0; i < x.nrcfr; i++)
    {
        in >> x.V.a[i];
        //cout << " ab" << endl;
        if(typeid(x.V.a[i]) != typeid(flag) )
        {
            x.V.a[i] = (int)x.V.a[i];
        }

    }
    x.eliminare_0();
    return in;
}

template <class T>
void Nr_Natural_Mare<T>::eliminare_0()
{
    while (V.a[nrcfr-1] == 0)
        nrcfr--;
}

/// clasa specializata Nr_Natural_Mare pentru char

Nr_Natural_Mare<char>::Nr_Natural_Mare(int n, char* x)
{
    nrcfr = n;
    V.a = new char [nrcfr];
    for (int i = 0; i < nrcfr; i++)
        V.a[i] = x[i];
    eliminare_0();
}

Nr_Natural_Mare<char>::Nr_Natural_Mare(const Nr_Natural_Mare<char>& x)
{
    nrcfr = x.nrcfr;
    V.a = new char [nrcfr];
    for (int i = 0; i < nrcfr; i++)
        V.a[i] = x.V.a[i];
}

Nr_Natural_Mare<char>& Nr_Natural_Mare<char>::operator= (const Nr_Natural_Mare<char>& x)
{
   if (this != &x)
    {
        nrcfr = x.nrcfr;
        V.a = new char[nrcfr];
        for (int i = 0; i < nrcfr; i++)
            V.a[i] = x.V.a[i];
    }
    return *this;
}

template<>
ostream& operator<< (ostream& out, const Nr_Natural_Mare<char>& x)
{
    x.afisare(out);
    return out;
}

template<>
istream& operator>> (istream& in, Nr_Natural_Mare<char>&x)
{
    x.nrcfr = 0; //T a;
    int flag = 1;  string s;
    cout << " Dati nr de elemente\n";
    do
    {
        in >> s;
        flag = exceptie_1(s,flag);
    }
    while(flag != 0);

    for (int i = 0; i < (int)s.size(); i++)
        {
            x.nrcfr += (s[i]-48)*pow(10,s.size()-i-1);
            //cout << x.nrcfr << endl;
        }

    cout << " Dati elementele\n";
    x.V.a = new char [x.nrcfr];
    for (int i = 0; i < x.nrcfr; i++)
    {
        in >> x.V.a[i];
    }
    x.eliminare_0();
    return in;
}

void Nr_Natural_Mare<char>::eliminare_0()
{
    while (V.a[nrcfr-1] == 0)
        nrcfr--;
}

/// definire clasa Numar_Intreg_mare generica
template <class T>
istream& operator>> (istream& in, Numar_Intreg_mare<T>& x)
{
    int flag=0;
    cout << "Dati semnul" << endl;
    do
    {
        try
        {
            in >> x.semn;
            if (x.semn != '+' && x.semn != '-')
                throw x.semn;
            else flag = 1;
        }
        catch(char b) { cout << " Ati introdus un semn gresit, introduceti din nou" << endl;}
    }
    while(flag == 0);
    in >> ( Nr_Natural_Mare<T>&)x; /// fac conversie practic, pentru a apela automat operatorul>> din clasa de baza
    return in;
}

/// definire operatori Nr_Natural_Mare generica

template <class T>
Nr_Natural_Mare<T>& Nr_Natural_Mare<T>::operator+ (const Nr_Natural_Mare<T>& x)   /// am simulat adunarea in colonita, probabil ca complexitate nu e chiar reusita
{
    int t,r = 0;
    Nr_Natural_Mare<T>* temp = new Nr_Natural_Mare<T>;
    temp->nrcfr = ((nrcfr > x.nrcfr) ? nrcfr : x.nrcfr)+1; /// am observat ca la adunare a 2 nr, suma va avea cu cel mult o cifra in plus, in caz ca e 0 ultima cifra apelez eliminare_0
    temp->V.a = new T [temp->nrcfr];
    for (int i = 0 ; i < temp->nrcfr; i++)
    {
        if(i < nrcfr && i < x.nrcfr)    /// cand cifrele care le adun sunt undeva in mijlocul numerelor
        {
            t = V.a[i] + x.V.a[i] + r;
            if (t/10 != 0)
            {
                temp->V.a[i] = t%10;
                r = t/10;
            }
            else
            {
                temp->V.a[i] = t;
                r = 0;
            }
        }
        if(i >= nrcfr && i < x.nrcfr) /// in caz ca nu mai sunt cifre din nr1 , dar au ramas in nr 2
        {
            t = x.V.a[i] + r;
            if (t/10 != 0)
            {
                temp->V.a[i] = t%10;
                r = t/10;
            }
            else
            {
                temp->V.a[i] = t;
                r = 0;
            }
        }
        if(i < nrcfr && i >= x.nrcfr) ///  in caz ca nu mai sunt cifre din nr 2 , dar au ramas in nr 1
        {
            t = V.a[i] + r;
            if (t/10 != 0)
            {
                temp->V.a[i] = t%10;
                r = t/10;
            }
            else
            {
                temp->V.a[i] = t;
                r = 0;
            }
        }
        if(i >= nrcfr && i >= x.nrcfr) /// in caz ca ambele numere nu mai au cifre de adunat , dar mai am de adunat o cifra care o memorez in caz ca suma cifrelor precedente depaseste 10;
        {
            temp->V.a[i] = r;
            r = 0;
        }
    }
    //for (int i = 0 ; i < temp->nrcfr; i++)
    temp->eliminare_0();
    return *temp;
}

template <class T>
Nr_Natural_Mare<T>& Nr_Natural_Mare<T>::operator- (const Nr_Natural_Mare<T>& x) /// simulez scaderea in colonita, deasemena ca complexitate lasa de dorit
{
    int flag = 0;
    Nr_Natural_Mare<T>* temp = new Nr_Natural_Mare<T>;
    temp->nrcfr = (nrcfr > x.nrcfr) ? nrcfr : x.nrcfr; /// la scadere nr maxim de cifre al numarului nou format este nr de cifre a numarului mai lung
    //cout << endl << endl << temp->nrcfr << endl;
    temp->V.a = new T [temp->nrcfr];
    if( nrcfr == x.nrcfr )  /// caz particular pentru lungimi egale de numere
    {
        for (int i = temp->nrcfr-1; i >= 0; i--)
        {
            //cout << " a : " << V.a[i] << " " << x.V.a[i] << endl;
            if (V.a[i] < x.V.a[i]) /// intrucat cifrele sunt egale verific care din nr este totusi mai mare, comparand cifra cu cifra
                {
                    flag = 1;
                    //cout << V.a[i] <<" " <<x.V.a[i] << endl;
                    break;
                }
            else if (V.a[i] > x.V.a[i])
            {
                //cout << V.a[i] << " " << x.V.a[i] << endl;
                break;
            }
        }
        if (flag == 1) /// daca primul e mai mic
        {
            //cout << endl << " primul mai mic ca a 2 " << endl;
            flag = 0;
            for (int i = 0 ; i < temp->nrcfr; i++)
            {
                    if (x.V.a[i] - flag < V.a[i])
                    {
                        temp->V.a[i] = x.V.a[i] - flag - V.a[i] + 10;
                        //cout << temp->V.a[i] << endl;
                        flag = 1;
                    }
                    else
                    {
                        temp->V.a[i] = x.V.a[i] - V.a[i] -flag;
                       // cout << temp->V.a[i] << endl;
                        flag = 0;
                    }
            }
        }
        else /// daca cel de-al 2 e mai mic
        {
            for (int i = 0 ; i < temp->nrcfr; i++)
            {
                if (V.a[i] - flag < x.V.a[i])
                {
                    temp->V.a[i] = V.a[i] - flag - x.V.a[i] + 10;
                    //cout << temp->V.a[i] << endl;
                    flag = 1;
                }
                else
                {
                    temp->V.a[i] = V.a[i] - x.V.a[i] -flag;
                    //cout << temp->V.a[i] << endl;
                    flag = 0;
                }
            }
        }
        temp->eliminare_0(); /// elminez zerourile care pot aparea
    }
    if ( nrcfr > x.nrcfr ) /// caz in care nr de cifre al primului nr e mai mare decat nr de cifre al celui de-al 2 numar
    {
        for (int i = 0 ; i < temp->nrcfr; i++)
        {
            if ( i < nrcfr && i < x.nrcfr )
            {
                if (V.a[i] - flag < x.V.a[i])
                {
                    temp->V.a[i] = V.a[i] - flag - x.V.a[i] + 10;
                    //cout << temp->V.a[i] << endl;
                    flag = 1;
                }
                else
                {
                    temp->V.a[i] = V.a[i] - x.V.a[i] -flag;
                    //cout << temp->V.a[i] << endl;
                    flag = 0;
                }
            }
            if ( i < nrcfr && i >= x.nrcfr )
            {
                temp->V.a[i] = V.a[i] - flag;
               // cout << temp->V.a[i] << endl;
                flag = 0;
            }
        }
        temp->eliminare_0();

    }
    if( nrcfr < x.nrcfr ) /// cazn in care nr de cifre al primului nr e mai mic decat a celui de-al 2 numar
        {
            for (int i = 0 ; i < temp->nrcfr; i++)
            {
                if ( i < nrcfr && i < x.nrcfr )
                {
                    if (x.V.a[i] - flag < V.a[i])
                    {
                        temp->V.a[i] = x.V.a[i] - flag - V.a[i] + 10;
                        //cout << temp->V.a[i] << endl;
                        flag = 1;
                    }
                    else
                    {
                        temp->V.a[i] = x.V.a[i] - V.a[i] - flag;
                       // cout << temp->V.a[i] << endl;
                        flag = 0;
                    }
                }
                if ( i < x.nrcfr && i >= nrcfr )
                {
                    temp->V.a[i] = x.V.a[i] - flag;
                    //cout << temp->V.a[i] << endl;
                    flag = 0;
                }
            }
            temp->eliminare_0();
        }
    for (int i = 0; i < temp->nrcfr; i++) /// acest for ma scapa de situatia in care am de ex 2000 - 1 , si trebuie sa transform cei 3 de 0 in 9
        if (temp->V.a[i] == -1)
        {
            temp->V.a[i] = 9;
            temp->V.a[i+1] -= 1;
        }

    return *temp;
}

template <class T>
Nr_Natural_Mare<T>& Nr_Natural_Mare<T>::operator*(const Nr_Natural_Mare<T>& x) /// simulez inmultirea
{
    int t,r = 0;
    Nr_Natural_Mare<T> p[x.nrcfr]; /// voi folosi acest vector pentru a simula inmultirea, salvand in fiecare element al vectorului numarul care il obtin la inmultirea primului nr ( primului factor) cu  o cifra din cel de-al doilea nr (al doilea factor), urmand sa adun elementele si sa obtin valoarea finala a inmultirii
    Nr_Natural_Mare<T> *temp = new Nr_Natural_Mare<T>;
    for (int i = 0; i < x.nrcfr; i++)
    {
        //cout << "p[" << i << "] = ";
        p[i].nrcfr = nrcfr + 1 + i;
        p[i].V.a = new T [p[i].nrcfr];
        for ( int j = 0 ; j < p[i].nrcfr-1; j++)
        {
            if ( j < i)
            {
                p[i].V.a[j] = 0; /// practic simuland inmultirea ca pe foaie, aduag zerouri la inceput de nr , daca primul nr se inmulteste cu 2 , a 3, a 4 etc cifra din numarul 2 ( al doilea factor)
            //  cout << p[i].V.a[j] << endl;
            }
            else
            {
            t = V.a[j-i] * x.V.a[i] + r;
            r = t/10;
            p[i].V.a[j] = t%10;
            //cout << t << " " << r << " " << p[i].V.a[j] << endl;
            }
            //cout << p[i].V.a[j];
        }
        p[i].V.a[p[i].nrcfr-1] = r;
        r = 0;
        p[i].eliminare_0();
        //cout << endl;
    }
    for ( int i = 0; i < x.nrcfr; i++)
        *temp = *temp + p[i];  /// adun elementele vectorului p, pentru a obtine rezultatul final
    temp->eliminare_0();
    return *temp;

}


Nr_Natural_Mare<char>& Nr_Natural_Mare<char>::operator+ (const Nr_Natural_Mare<char>& x)
{
    Nr_Natural_Mare<char>* temp = new Nr_Natural_Mare<char>;
    temp->nrcfr = this->nrcfr + x.nrcfr;
    temp->V.a = new char[temp->nrcfr];
    for ( int i = 0; i < temp->nrcfr; i++)
    {
        if (i < this->nrcfr)
            temp->V.a[i] = this->V.a[i];
        else
            temp->V.a[i] = x.V.a[i-x.nrcfr];
    }
    return *temp;
}


template<>
Numar_Intreg_mare<char>& Numar_Intreg_mare<char> :: operator+ (const Numar_Intreg_mare<char>& x)
{
    Numar_Intreg_mare<char>*temp =  new Numar_Intreg_mare<char>;
    if (semn == '+' && x.semn == '+')
    {
        (Nr_Natural_Mare<char>&)(*temp) = (Nr_Natural_Mare<char>&)(*this) + (Nr_Natural_Mare<char>&)x;
        temp->semn = '+';
    }
    return *temp;
}


template <class T>
Numar_Intreg_mare<T>& Numar_Intreg_mare<T>::operator+ (const Numar_Intreg_mare<T>& x) /// folosesc adunarea din clasa de baza, schimband doar semnele cand este necesar
{
    Numar_Intreg_mare<T>*temp =  new Numar_Intreg_mare<T>;
    if (semn == '+' && x.semn == '+')
    {
        (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) + (Nr_Natural_Mare<T>&)x;
        temp->semn = '+';
    }
    else if (semn == '-' && x.semn == '+')
    {
        (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) - (Nr_Natural_Mare<T>&)x;
        if (this->nrcfr < x.nrcfr)
                temp->semn = '+';
        if (this->nrcfr > x.nrcfr)
            temp->semn = '-';
        if (this->nrcfr == x.nrcfr)
        {
            for (int i = temp->nrcfr-1; i >= 0; i--)
            {
                if (this->V.a[i] < x.V.a[i])
                    {
                        temp->semn = '+';
                        break;
                    }
                else if (this->V.a[i] > x.V.a[i])
                {
                    temp->semn = '-';
                    break;
                }
            }
        }
    }
    else if (semn == '+' && x.semn == '-')
    {
        (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) - (Nr_Natural_Mare<T>&)x;
        if (this->nrcfr < x.nrcfr)
            temp->semn = '-';
        if (this->nrcfr > x.nrcfr)
            temp->semn = '+';
        if (this->nrcfr == x.nrcfr)
        {
            for (int i = temp->nrcfr-1; i >= 0; i--)
            {
                if (this->V.a[i] < x.V.a[i])
                    {
                        temp->semn = '-';
                        break;
                    }
                else if (this->V.a[i] > x.V.a[i])
                {
                    temp->semn = '+';
                    break;
                }
            }
        }
    }
    else if ( semn == '-' && x.semn == '-')
    {
        (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) + (Nr_Natural_Mare<T>&)x;
        temp->semn = '-';
    }
    return *temp;
}

template <class T>
Numar_Intreg_mare<T>& Numar_Intreg_mare<T>::operator- (const Numar_Intreg_mare<T>& x) /// folosesc scaderea din clasa de baza, schimband doar semnele cand este necesar
{

    Numar_Intreg_mare *temp =  new Numar_Intreg_mare;
    if (semn == '+' && x.semn == '+')
    {
        (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) - (Nr_Natural_Mare<T>&)x;
        if (this->nrcfr < x.nrcfr)
                temp->semn = '-';
        if (this->nrcfr > x.nrcfr)
            temp->semn = '+';
        if (this->nrcfr == x.nrcfr)
        {
            for (int i = temp->nrcfr-1; i >= 0; i--)
            {
                if (this->V.a[i] < x.V.a[i])
                    {
                        temp->semn = '-';
                        break;
                    }
                else if (this->V.a[i] > x.V.a[i])
                {
                    temp->semn = '+';
                    break;
                }
            }
            temp->semn = 0;
        }
    }
    else if (semn == '-' && x.semn == '+')
    {
        (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) + (Nr_Natural_Mare<T>&)x;
        temp->semn = '-';
    }
    else if (semn == '+' && x.semn == '-')
    {
        (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) + (Nr_Natural_Mare<T>&)x;
        temp->semn = '+';
    }
    else if ( semn == '-' && x.semn == '-')
    {
        (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) - (Nr_Natural_Mare<T>&)x;
        if (this->nrcfr < x.nrcfr)
                temp->semn = '+';
        if (this->nrcfr > x.nrcfr)
            temp->semn = '-';
        if (this->nrcfr == x.nrcfr)
        {
            for (int i = temp->nrcfr-1; i >= 0; i--)
            {
                if (this->V.a[i] < x.V.a[i])
                    {
                        temp->semn = '+';
                        break;
                    }
                else if (this->V.a[i] > x.V.a[i])
                {
                    temp->semn = '-';
                    break;
                }
            }
            temp->semn = 0;
        }
    }
    return *temp;
}

template <class T>
Numar_Intreg_mare<T>& Numar_Intreg_mare<T>::operator* (const Numar_Intreg_mare<T>& x) /// folosesc iinmultirea din clasa de baza, schimband doar semnele cand este necesar
{
    Numar_Intreg_mare *temp =  new Numar_Intreg_mare;
    (Nr_Natural_Mare<T>&)(*temp) = (Nr_Natural_Mare<T>&)(*this) * (Nr_Natural_Mare<T>&)x;
    if (( semn == '+' && x.semn == '+')||(semn == '-' && x.semn == '-'))
        temp->semn = '+';
    else temp->semn = '-';
    return *temp;
}

int main()
{
    int flag1 = 0, flag2 = 0, flag3 = 0, op1, op11, op2, op3, n, nr_ob; /// flagurile le folosesc pentru a esi din submeniuri si op-urile pentru a alege optiuni in submeniuri diferite
cout << " !In atentia utilizatorului: " << endl;
cout << " 1: Elementele in obiecte de tip int, float si double vor fi introduse in ordine inversa " << endl;
cout << " 2: Deasemenea, pentru tipurile float si double se va face conversia in int la memorarea " << endl;
cout << " 3: Pentru obiectele de tip char a fost implementata doar operatia + " << endl << endl;


    while(!flag1)
    {
        cout << "\t\t" << " Meniu: " << endl ;
        cout << "\t\t" << " 1) Citire, memorare si afisare a n obiecte (folosind conceptul upcasting / downcasting)" << endl;
        cout << "\t\t" << " 2) Operatii cu diferite tipuri de date, implimentate prin supraincarcare de operatori " << endl;
        cout << "\t\t" << " 3) Iesire din program" << endl;
        cout << endl;
        cout << " Alegeti optiunea dorita : " << endl;
        cin >> op1;
        cout << endl;
        switch(op1)
        {
            case 1:
                {
                    flag2 = 0;
                    cout << " Ati ales optiunea 1) Citire, memorare si afisare a n obiecte \n Alegeti tipul obiectelor" << endl;
                    while (!flag2)
                    {
                    cout << "\t 1 - Integer \n\t 2 - Float \n\t 3 - Double \n\t 4 - Char \n\t 5 - Iesire meniul principal" << endl;
                    cin >> op11;
                    switch (op11){
                        case 1:
                            {
                                cout << " Citirea obiectelor de tip Integer: Introduceti numarul de obiecte : " << endl;
                                Nr_Natural_Mare<int> **p;
                                cin >> nr_ob;
                                p = new Nr_Natural_Mare<int>*[nr_ob];
                                for  (int i = 0 ; i < nr_ob; i++)
                                {
                                    cout << "\t Obiect din clasa : \n\t 1 - Nr_Natural_Mare \n\t 2 - Numar_Intreg_mare" << endl;
                                    cin >> op2;
                                    switch (op2){
                                        case 1:
                                        {
                                            p[i] = new Nr_Natural_Mare<int>;
                                            cin >> *p[i];
                                            break;
                                        }
                                        case 2:
                                        {
                                            p[i] = new Numar_Intreg_mare<int>;
                                            cin >> *(Numar_Intreg_mare<int>*)p[i];
                                            break;
                                        }
                                    }
                                }
                                cout << endl << " Afisare obiecte:" << endl;
                                for ( int i = 0 ; i < nr_ob; i++)
                                {
                                    cout << " Obiectul " << i+1 << " este :" << endl;
                                    cout << *p[i];
                                }
                                delete[] p;
                                cout << endl << " Ati revenit in meniul principal" << endl;
                                break;
                            }
                        case 2:
                            {
                                cout << " Citirea obiectelor de tip Float: Introduceti numarul de obiecte : " << endl;
                                Nr_Natural_Mare<float> **p;
                                cin >> nr_ob;
                                p = new Nr_Natural_Mare<float>*[nr_ob];
                                for  (int i = 0 ; i < nr_ob; i++)
                                {
                                    cout << "\t Obiect din clasa : \n\t 1 - Nr_Natural_Mare \n\t 2 - Numar_Intreg_mare" << endl;
                                    cin >> op2;
                                    switch (op2){
                                        case 1:
                                        {
                                            p[i] = new Nr_Natural_Mare<float>;
                                            cin >> *p[i];
                                            break;
                                        }
                                        case 2:
                                        {
                                            p[i] = new Numar_Intreg_mare<float>;
                                            cin >> *(Numar_Intreg_mare<float>*)p[i];
                                            break;
                                        }
                                    }
                                }
                                cout << endl << " Afisare obiecte:" << endl;
                                for ( int i = 0 ; i < nr_ob; i++)
                                {
                                    cout << " Obiectul " << i+1 << " este :" << endl;
                                    cout << *p[i];
                                }
                                delete[] p;
                                cout << endl << " Ati revenit in meniul principal" << endl;
                                break;
                            }
                        case 3:
                            {
                                cout << " Citirea obiectelor de tip Double: Introduceti numarul de obiecte : " << endl;
                                Nr_Natural_Mare<double> **p;
                                cin >> nr_ob;
                                p = new Nr_Natural_Mare<double>*[nr_ob];
                                for  (int i = 0 ; i < nr_ob; i++)
                                {
                                    cout << "\t Obiect din clasa : \n\t 1 - Nr_Natural_Mare \n\t 2 - Numar_Intreg_mare" << endl;
                                    cin >> op2;
                                    switch (op2){
                                        case 1:
                                        {
                                            p[i] = new Nr_Natural_Mare<double>;
                                            cin >> *p[i];
                                            break;
                                        }
                                        case 2:
                                        {
                                            p[i] = new Numar_Intreg_mare<double>;
                                            cin >> *(Numar_Intreg_mare<double>*)p[i];
                                            break;
                                        }
                                    }
                                }
                                cout << endl << " Afisare obiecte:" << endl;
                                for ( int i = 0 ; i < nr_ob; i++)
                                {
                                    cout << " Obiectul " << i+1 << " este :" << endl;
                                    cout << *p[i];
                                }
                                delete[] p;
                                cout << endl << " Ati revenit in meniul principal" << endl;
                                break;
                            }
                        case 4:
                            {
                                cout << " Citirea obiectelor de tip Char: Introduceti numarul de obiecte : " << endl;
                                Nr_Natural_Mare<char> **p;
                                cin >> nr_ob;
                                p = new Nr_Natural_Mare<char>*[nr_ob];
                                for  (int i = 0 ; i < nr_ob; i++)
                                {
                                    cout << "\t Obiect din clasa : \n\t 1 - Nr_Natural_Mare \n\t 2 - Numar_Intreg_mare" << endl;
                                    cin >> op2;
                                    switch (op2){
                                        case 1:
                                        {
                                            p[i] = new Nr_Natural_Mare<char>;
                                            cin >> *p[i];
                                            break;
                                        }
                                        case 2:
                                        {
                                            p[i] = new Numar_Intreg_mare<char>;
                                            cin >> *(Numar_Intreg_mare<char>*)p[i];
                                            break;
                                        }
                                    }
                                }
                                cout << endl << " Afisare obiecte:" << endl;
                                for ( int i = 0 ; i < nr_ob; i++)
                                {
                                    cout << " Obiectul " << i+1 << " este :" << endl;
                                    cout << *p[i];
                                }
                                delete[] p;
                                cout << endl << " Ati revenit in meniul principal" << endl;
                                break;
                            }
                        case 5:
                            {
                                flag2 = 1;
                                cout << "Ati revenit in meniul principal" << endl;
                                break;
                            }
                        default:
                        {
                            cout << " Ati introdus o optiune gresita" << endl;
                            cout << " Ati revenit in meniul optiunii 1) Citire, memorare si afisare a n obiecte " << endl;
                            cout << " Acum alegeti tipul obiectelor" << endl;
                            break;
                        }
                    }
                    }
                    break;
                }
            case 2:
                {
                    flag2 = 0;
                    cout << " Ati ales optiunea 2) Operatii cu diferite tipuri de date " << endl;
                    cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                    while (!flag2)
                    {
                        cout << "\t 1 - Nr_Natural_Mare <int>  \n\t 2 - Numar_Intreg_mare <int> \n\t 3 - Nr_Natural_Mare <float> \n\t 4 - Numar_Intreg_mare <float> \n\t 5 -  Nr_Natural_Mare <double> \n\t 6 -  Numar_Intreg_mare <double> \n\t 7 -  Nr_Natural_Mare <char> \n\t 8 -  Numar_Intreg_mare <char> \n\t 9 - Iesire meniu principal" << endl;
                        cin >> op2;
                        switch(op2)
                        {
                        case 1:
                            {
                                flag3 = 0;
                                cout << " Ati ales optiunea 2.1) Operatii cu  Nr_Natural_Mare<int>. Alegeti operatia dorita : " << endl;
                                while (!flag3)
                                {
                                    cout << "\t" << " 1. Adunare, implementata prin supraincarcarea operatorului '+' " << endl;
                                    cout << "\t" << " 2. Scadere, implementata prin supraincarcarea operatorului '-' " << endl;
                                    cout << "\t" << " 3. Produs, implementata prin supraincarcarea operatorului '*' " << endl;
                                    cout << "\t" << " 4. Copiere, implementata prin supraincarcarea a operatorului '=' " << endl;
                                    cout << "\t" << " 5. Iesire in submeniul 2) Operatii cu diferite tipuri de date " << endl << endl;
                                    cin >> op3;
                                    switch (op3)
                                    {
                                    case 1:
                                        {
                                            cout << " Ati ales optiunea 2.1.1) Adunare. Introduceti numarul de obiecte participante la adunare" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare<int> *v = new Nr_Natural_Mare<int>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare<int> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp + v[i];
                                            cout << " Suma a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare<int> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 2:
                                        {
                                            cout << " Ati ales optiunea 2.1.2) Scadere. Introduceti numarul de obiecte participante la scadere" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare<int> *v = new Nr_Natural_Mare<int>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare<int> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp - v[i];
                                            cout << " Rezultatul scaderii a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare<int> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 3:
                                        {
                                            cout << " Ati ales optiunea 2.1.3) Produs. Introduceti numarul de obiecte participante la inmultire" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare<int> *v = new Nr_Natural_Mare<int>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare<int> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp * v[i];
                                            cout << " Produsul a celor " << n << " numere este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare<int> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 4 :
                                        {
                                            cout << " Ati ales optiunea 2.1.4) Copierea. Dati obiectul din care se copiaza " << endl;
                                            Nr_Natural_Mare<int> C,X,Y;
                                            cin >> C;
                                            X = Y = C;
                                            cout << " Pentru a va convinge de faptul ca copierea a avut loc cu succes, voi afisa pe rand obiectele C, X, Y, in urma expresiei 'X = Y = C', unde C e oiectul din care se copiaza " << endl;
                                            cout << " Aceasta este obiectul C:";
                                            cout << C << endl;
                                            cout << " Aceasta este obicetul X:";
                                            cout << X << endl;
                                            cout << " Aceasta este obiectul Y:";
                                            cout << Y << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Operatii cu Nr_Natural_Mare<int> . Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    case 5 :
                                        {
                                            flag3 = 1;
                                            cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date" << endl;
                                            cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                                            break;
                                        }
                                    default :
                                        {
                                            cout << " Ati introdus o optiune gresita" << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numere Naturale. Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                        case 2:
                            {
                                flag3 = 0;
                                cout << " Ati ales optiunea 2.1) Operatii cu  Numar_Intreg_mare <int>. Alegeti operatia dorita : " << endl;
                                while (!flag3)
                                {
                                    cout << "\t" << " 1. Adunare, implementata prin supraincarcarea operatorului '+' " << endl;
                                    cout << "\t" << " 2. Scadere, implementata prin supraincarcarea operatorului '-' " << endl;
                                    cout << "\t" << " 3. Produs, implementata prin supraincarcarea operatorului '*' " << endl;
                                    cout << "\t" << " 4. Copiere, implementata prin supraincarcarea a operatorului '=' " << endl;
                                    cout << "\t" << " 5. Iesire in submeniul 2)  Operatii cu diferite tipuri de date " << endl << endl;
                                    cin >> op3;
                                    switch (op3)
                                    {
                                    case 1:
                                        {
                                            cout << " Ati ales optiunea 2.1.1) Adunare. Introduceti numarul de obiecte participante la adunare" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <int> *v = new Numar_Intreg_mare <int>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <int> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp + v[i];
                                            cout << " Suma a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <int> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 2:
                                        {
                                            cout << " Ati ales optiunea 2.1.2) Scadere. Introduceti numarul de obiecte participante la scadere" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <int> *v = new Numar_Intreg_mare <int>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <int> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp - v[i];
                                            cout << " Rezultatul scaderii a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <int> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 3:
                                        {
                                            cout << " Ati ales optiunea 2.1.3) Produs. Introduceti numarul de obiecte participante la inmultire" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <int> *v = new Numar_Intreg_mare <int>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <int> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp * v[i];
                                            cout << " Produsul a celor " << n << " numere este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <int> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 4 :
                                        {
                                            cout << " Ati ales optiunea 2.1.4) Copierea. Dati numarul din care se copiaza " << endl;
                                            Numar_Intreg_mare <int> C,X,Y;
                                            cin >> C;
                                            X = Y = C;
                                            cout << " Pentru a va convinge de faptul ca copierea a avut loc cu succes, voi afisa pe rand obiectele C, X, Y, in urma expresiei 'X = Y = C', unde C e oiectul din care se copiaza " << endl;
                                            cout << " Aceasta este obiectul C:";
                                            cout << C << endl;
                                            cout << " Aceasta este obicetul X:";
                                            cout << X << endl;
                                            cout << " Aceasta este obiectul Y:";
                                            cout << Y << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Operatii cu Numar_Intreg_mare <int> . Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    case 5 :
                                        {
                                            flag3 = 1;
                                            cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date" << endl;
                                            cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                                            break;
                                        }
                                    default :
                                        {
                                            cout << " Ati introdus o optiune gresita" << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numere Naturale. Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                        case 3:
                            {
                                flag3 = 0;
                                cout << " Ati ales optiunea 2.1) Operatii cu  Nr_Natural_Mare <float>. Alegeti operatia dorita : " << endl;
                                while (!flag3)
                                {
                                    cout << "\t" << " 1. Adunare, implementata prin supraincarcarea operatorului '+' " << endl;
                                    cout << "\t" << " 2. Scadere, implementata prin supraincarcarea operatorului '-' " << endl;
                                    cout << "\t" << " 3. Produs, implementata prin supraincarcarea operatorului '*' " << endl;
                                    cout << "\t" << " 4. Copiere, implementata prin supraincarcarea a operatorului '=' " << endl;
                                    cout << "\t" << " 5. Iesire in submeniul 2)  Operatii cu diferite tipuri de date " << endl << endl;
                                    cin >> op3;
                                    switch (op3)
                                    {
                                    case 1:
                                        {
                                            cout << " Ati ales optiunea 2.1.1) Adunare. Introduceti numarul de obiecte participante la adunare" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare <float> *v = new Nr_Natural_Mare <float>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare <float> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp + v[i];
                                            cout << " Suma a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare <float> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 2:
                                        {
                                            cout << " Ati ales optiunea 2.1.2) Scadere. Introduceti numarul de obiecte participante la scadere" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare <float> *v = new Nr_Natural_Mare <float>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare <float> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp - v[i];
                                            cout << " Rezultatul scaderii a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare <float> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 3:
                                        {
                                            cout << " Ati ales optiunea 2.1.3) Produs. Introduceti numarul de obiecte participante la inmultire" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare <float> *v = new Nr_Natural_Mare <float>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare <float> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp * v[i];
                                            cout << " Produsul a celor " << n << " numere este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare <float> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 4 :
                                        {
                                            cout << " Ati ales optiunea 2.1.4) Copierea. Dati numarul din care se copiaza " << endl;
                                            Nr_Natural_Mare <float> C,X,Y;
                                            cin >> C;
                                            X = Y = C;
                                            cout << " Pentru a va convinge de faptul ca copierea a avut loc cu succes, voi afisa pe rand obiectele C, X, Y, in urma expresiei 'X = Y = C', unde C e oiectul din care se copiaza " << endl;
                                            cout << " Aceasta este obiectul C:";
                                            cout << C << endl;
                                            cout << " Aceasta este obicetul X:";
                                            cout << X << endl;
                                            cout << " Aceasta este obiectul Y:";
                                            cout << Y << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Operatii cu Nr_Natural_Mare <float> . Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    case 5 :
                                        {
                                            flag3 = 1;
                                            cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date" << endl;
                                            cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                                            break;
                                        }
                                    default :
                                        {
                                            cout << " Ati introdus o optiune gresita" << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numere Naturale. Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                        case 4:
                            {
                                flag3 = 0;
                                cout << " Ati ales optiunea 2.1) Operatii cu  Numar_Intreg_mare <float>. Alegeti operatia dorita : " << endl;
                                while (!flag3)
                                {
                                    cout << "\t" << " 1. Adunare, implementata prin supraincarcarea operatorului '+' " << endl;
                                    cout << "\t" << " 2. Scadere, implementata prin supraincarcarea operatorului '-' " << endl;
                                    cout << "\t" << " 3. Produs, implementata prin supraincarcarea operatorului '*' " << endl;
                                    cout << "\t" << " 4. Copiere, implementata prin supraincarcarea a operatorului '=' " << endl;
                                    cout << "\t" << " 5. Iesire in submeniul 2)  Operatii cu diferite tipuri de date " << endl << endl;
                                    cin >> op3;
                                    switch (op3)
                                    {
                                    case 1:
                                        {
                                            cout << " Ati ales optiunea 2.1.1) Adunare. Introduceti numarul de obiecte participante la adunare" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <float> *v = new Numar_Intreg_mare <float>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <float> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp + v[i];
                                            cout << " Suma a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <float> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 2:
                                        {
                                            cout << " Ati ales optiunea 2.1.2) Scadere. Introduceti numarul de obiecte participante la scadere" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <float> *v = new Numar_Intreg_mare <float>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <float> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp - v[i];
                                            cout << " Rezultatul scaderii a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <float> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 3:
                                        {
                                            cout << " Ati ales optiunea 2.1.3) Produs. Introduceti numarul de obiecte participante la inmultire" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <float> *v = new Numar_Intreg_mare <float>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <float> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp * v[i];
                                            cout << " Produsul a celor " << n << " numere este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <float> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 4 :
                                        {
                                            cout << " Ati ales optiunea 2.1.4) Copierea. Dati numarul din care se copiaza " << endl;
                                            Numar_Intreg_mare <float> C,X,Y;
                                            cin >> C;
                                            X = Y = C;
                                            cout << " Pentru a va convinge de faptul ca copierea a avut loc cu succes, voi afisa pe rand obiectele C, X, Y, in urma expresiei 'X = Y = C', unde C e oiectul din care se copiaza " << endl;
                                            cout << " Aceasta este obiectul C:";
                                            cout << C << endl;
                                            cout << " Aceasta este obicetul X:";
                                            cout << X << endl;
                                            cout << " Aceasta este obiectul Y:";
                                            cout << Y << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Operatii cu Nr_Natural_Mare<int> . Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    case 5 :
                                        {
                                            flag3 = 1;
                                            cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date" << endl;
                                            cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                                            break;
                                        }
                                    default :
                                        {
                                            cout << " Ati introdus o optiune gresita" << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numere Naturale. Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                         case 5:
                            {
                                flag3 = 0;
                                cout << " Ati ales optiunea 2.1) Operatii cu  Nr_Natural_Mare <double>. Alegeti operatia dorita : " << endl;
                                while (!flag3)
                                {
                                    cout << "\t" << " 1. Adunare, implementata prin supraincarcarea operatorului '+' " << endl;
                                    cout << "\t" << " 2. Scadere, implementata prin supraincarcarea operatorului '-' " << endl;
                                    cout << "\t" << " 3. Produs, implementata prin supraincarcarea operatorului '*' " << endl;
                                    cout << "\t" << " 4. Copiere, implementata prin supraincarcarea a operatorului '=' " << endl;
                                    cout << "\t" << " 5. Iesire in submeniul 2)  Operatii cu diferite tipuri de date " << endl << endl;
                                    cin >> op3;
                                    switch (op3)
                                    {
                                    case 1:
                                        {
                                            cout << " Ati ales optiunea 2.1.1) Adunare. Introduceti numarul de obiecte participante la adunare" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare <double> *v = new Nr_Natural_Mare <double>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                           Nr_Natural_Mare <double> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp + v[i];
                                            cout << " Suma a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare <double> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 2:
                                        {
                                            cout << " Ati ales optiunea 2.1.2) Scadere. Introduceti numarul de obiecte participante la scadere" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare <double> *v = new Nr_Natural_Mare <double>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare <double> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp - v[i];
                                            cout << " Rezultatul scaderii a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare <double> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 3:
                                        {
                                            cout << " Ati ales optiunea 2.1.3) Produs. Introduceti numarul de obiecte participante la inmultire" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare <double> *v = new Nr_Natural_Mare <double>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare <double> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp * v[i];
                                            cout << " Produsul a celor " << n << " numere este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare <double> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 4 :
                                        {
                                            cout << " Ati ales optiunea 2.1.4) Copierea. Dati numarul din care se copiaza " << endl;
                                            Nr_Natural_Mare <double> C,X,Y;
                                            cin >> C;
                                            X = Y = C;
                                            cout << " Pentru a va convinge de faptul ca copierea a avut loc cu succes, voi afisa pe rand obiectele C, X, Y, in urma expresiei 'X = Y = C', unde C e oiectul din care se copiaza " << endl;
                                            cout << " Aceasta este obiectul C:";
                                            cout << C << endl;
                                            cout << " Aceasta este obicetul X:";
                                            cout << X << endl;
                                            cout << " Aceasta este obiectul Y:";
                                            cout << Y << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Operatii cu Nr_Natural_Mare <double> . Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    case 5 :
                                        {
                                            flag3 = 1;
                                            cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date" << endl;
                                            cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                                            break;
                                        }
                                    default :
                                        {
                                            cout << " Ati introdus o optiune gresita" << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numere Naturale. Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                         case 6:
                            {
                                flag3 = 0;
                                cout << " Ati ales optiunea 2.1) Operatii cu  Numar_Intreg_mare <double>. Alegeti operatia dorita : " << endl;
                                while (!flag3)
                                {
                                    cout << "\t" << " 1. Adunare, implementata prin supraincarcarea operatorului '+' " << endl;
                                    cout << "\t" << " 2. Scadere, implementata prin supraincarcarea operatorului '-' " << endl;
                                    cout << "\t" << " 3. Produs, implementata prin supraincarcarea operatorului '*' " << endl;
                                    cout << "\t" << " 4. Copiere, implementata prin supraincarcarea a operatorului '=' " << endl;
                                    cout << "\t" << " 5. Iesire in submeniul 2)  Operatii cu diferite tipuri de date " << endl << endl;
                                    cin >> op3;
                                    switch (op3)
                                    {
                                    case 1:
                                        {
                                            cout << " Ati ales optiunea 2.1.1) Adunare. Introduceti numarul de obiecte participante la adunare" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <double> *v = new Numar_Intreg_mare <double>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <double> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp + v[i];
                                            cout << " Suma a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <double> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 2:
                                        {
                                            cout << " Ati ales optiunea 2.1.2) Scadere. Introduceti numarul de obiecte participante la scadere" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <double> *v = new Numar_Intreg_mare <double>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <double> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp - v[i];
                                            cout << " Rezultatul scaderii a celor " << n << " obiecte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <double> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 3:
                                        {
                                            cout << " Ati ales optiunea 2.1.3) Produs. Introduceti numarul de obiecte participante la inmultire" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare <double> *v = new Numar_Intreg_mare <double>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                             for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Numarul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare <double> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp * v[i];
                                            cout << " Produsul a celor " << n << " numere este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare <double> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 4 :
                                        {
                                            cout << " Ati ales optiunea 2.1.4) Copierea. Dati numarul din care se copiaza " << endl;
                                            Numar_Intreg_mare <double> C,X,Y;
                                            cin >> C;
                                            X = Y = C;
                                            cout << " Pentru a va convinge de faptul ca copierea a avut loc cu succes, voi afisa pe rand obiectele C, X, Y, in urma expresiei 'X = Y = C', unde C e oiectul din care se copiaza " << endl;
                                            cout << " Aceasta este obiectul C:";
                                            cout << C << endl;
                                            cout << " Aceasta este obicetul X:";
                                            cout << X << endl;
                                            cout << " Aceasta este obiectul Y:";
                                            cout << Y << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Operatii cu Numar_Intreg_mare <double> . Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    case 5 :
                                        {
                                            flag3 = 1;
                                            cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date" << endl;
                                            cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                                            break;
                                        }
                                    default :
                                        {
                                            cout << " Ati introdus o optiune gresita" << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numere Naturale. Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                         case 7:
                            {
                                flag3 = 0;
                                cout << " Ati ales optiunea 2.1) Operatii cu  Nr_Natural_Mare<char>. Alegeti operatia dorita : " << endl;
                                while (!flag3)
                                {
                                    cout << "\t" << " 1. Concatenare(adunare), implementata prin supraincarcarea operatorului '+' " << endl;
                                    cout << "\t" << " 2. Copiere, implementata prin supraincarcarea a operatorului '=' " << endl;
                                    cout << "\t" << " 3. Iesire in submeniul 2)  Operatii cu diferite tipuri de date " << endl << endl;
                                    cin >> op3;
                                    switch (op3)
                                    {
                                    case 1:
                                        {
                                            cout << " Ati ales optiunea 2.1.1) Adunare. Introduceti numarul de cuvante participante la concatenare" << endl;
                                            cin >> n;
                                            Nr_Natural_Mare<char> *v = new Nr_Natural_Mare<char>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Cuvantul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Cuvantul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Nr_Natural_Mare<char> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp + v[i];
                                            cout << " Concatenarea a celor " << n << " cuvinte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Nr_Natural_Mare<char> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }
                                    case 2 :
                                        {
                                            cout << " Ati ales optiunea 2.1.4) Copierea. Dati cuvantul din care se copiaza " << endl;
                                            Nr_Natural_Mare<char> C,X,Y;
                                            cin >> C;
                                            X = Y = C;
                                            cout << " Pentru a va convinge de faptul ca copierea a avut loc cu succes, voi afisa pe rand obiectele C, X, Y, in urma expresiei 'X = Y = C', unde C e oiectul din care se copiaza " << endl;
                                            cout << " Aceasta este cuvantul C:";
                                            cout << C << endl;
                                            cout << " Aceasta este cuvantul X:";
                                            cout << X << endl;
                                            cout << " Aceasta este cuvantul Y:";
                                            cout << Y << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Operatii cu Nr_Natural_Mare<char> . Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    case 3 :
                                        {
                                            flag3 = 1;
                                            cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date" << endl;
                                            cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                                            break;
                                        }
                                    default :
                                        {
                                            cout << " Ati introdus o optiune gresita" << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numere Naturale. Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                         case 8:
                            {
                                flag3 = 0;
                                cout << " Ati ales optiunea 2.8) Operatii cu  Numar_Intreg_mare<char>. Alegeti operatia dorita : " << endl;
                                while (!flag3)
                                {
                                    cout << "\t" << " 1. Concatenare(adunare), implementata prin supraincarcarea operatorului '+' " << endl;
                                    cout << "\t" << " 2. Copiere, implementata prin supraincarcarea a operatorului '=' " << endl;
                                    cout << "\t" << " 3. Iesire in submeniul 2)  Operatii cu diferite tipuri de date " << endl << endl;
                                    cin >> op3;
                                    switch (op3)
                                    {
                                    case 1:
                                        {
                                            cout << " Ati ales optiunea 2.1.1) Adunare. Introduceti numarul de cuvantul participante la concatenare" << endl;
                                            cin >> n;
                                            Numar_Intreg_mare<char> *v = new Numar_Intreg_mare<char>[n];
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Cuvantul " << i+1 << " : " << endl;
                                                cin >> v[i];
                                            }
                                            for ( int  i = 0; i < n; i++)
                                            {
                                                cout << " Cuvantul " << i+1 << " este : " << endl;
                                                cout << v[i];
                                            }
                                            Numar_Intreg_mare<char> temp = v[0];
                                            for ( int i = 1; i < n; i++)
                                                temp = temp + v[i];
                                            cout << " Concatenarea a celor " << n << " cuvinte este :" << endl;
                                            cout << temp << endl;
                                            delete[] v;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu Numar_Intreg_mare<char> . Alegeti operatia dorita : " << endl;
                                            break;
                                        }

                                    case 2 :
                                        {
                                            cout << " Ati ales optiunea 2.1.4) Copierea. Dati cuvantul din care se copiaza " << endl;
                                            Numar_Intreg_mare<char> C,X,Y;
                                            cin >> C;
                                            X = Y = C;
                                            cout << " Pentru a va convinge de faptul ca copierea a avut loc cu succes, voi afisa pe rand obiectele C, X, Y, in urma expresiei 'X = Y = C', unde C e oiectul din care se copiaza " << endl;
                                            cout << " Aceasta este cuvantul C:";
                                            cout << C << endl;
                                            cout << " Aceasta este cuvantul X:";
                                            cout << X << endl;
                                            cout << " Aceasta este cuvantul Y:";
                                            cout << Y << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu  Numar_Intreg_mare<char> . Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    case 3 :
                                        {
                                            flag3 = 1;
                                            cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date" << endl;
                                            cout << " Acum alegeti intre ce tipuri si clasa de obiecte doriti sa efectuati operatiile : " << endl;
                                            break;
                                        }
                                    default :
                                        {
                                            cout << " Ati introdus o optiune gresita" << endl;
                                            cout << " Ati revenit in meniul optiunii 2.1) Operatii cu  Numa_Intreg_mare<char>. Alegeti operatia dorita: " << endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                        case 9:
                            {
                                flag2 = 1;
                                cout << "Ati revenit in meniul principal" << endl;
                                break;
                            }
                        default :
                            {
                                cout << "Ati introdus o optiune gresita" << endl;
                                cout << " Ati revenit in meniul optiunii 2) Operatii cu diferite tipuri de date " << endl;
                                cout << " Acum alegeti intre ce tipuri si clasa de biecte doriti sa efectuati operatiile : " << endl;
                                break;
                            }
                        }
                    }
                    break;
                }
            case 3:
                {
                    flag1 = 1;
                    break;
                }
            default :
                {
                    cout << "Ati introdus o optiune gresita" << endl;
                    cout << "Ati revenit in meniul principal" << endl;
                    break;
                }
        }
    }
    return 0;
}
