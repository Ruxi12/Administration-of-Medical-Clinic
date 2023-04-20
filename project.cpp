#include <iostream>
#include <cstring>
#include <string.h>
#include <vector>
#include <set>
#include <stdexcept>
#include <map>
#include <list>
#include <fstream>
using namespace std;
using std::runtime_error;
// Creating template class
template <class T>

class Vector {
private:
    T* elements;
    long long capacity;
    long long length;
public:
     Vector(long long n = 100);
    long long pushBack (T);
    T popBack();
    long long size () const;
    T& operator [] (long long index);
    class Iterator{
    private:
        //pointer
        T* ptr;
    public:
        Iterator():ptr(nullptr){}
        Iterator(T* p):ptr(p){}
        bool operator==(const Iterator& pointer) const{
            return ptr == pointer.ptr;
        }
        bool operator!=(const Iterator& x) const{
            return !(*this == x);
        }
        T operator*() const{
            return *ptr;
        }
        Iterator& operator++(){
            ptr++;
            return *this;
        }
        Iterator operator++(int){
            Iterator aux(*this);
            ++*this;
            return aux;
        }

    };
    // Begin iterator
    Iterator begin() const;

    // End iterator
    Iterator end() const;
};

template <typename T>
Vector<T>::Vector(long long n): capacity(n), elements(new T[n]), length(0){}
// Template class to insert the element in vector
template <typename T>
long long Vector<T>::pushBack(T info){
    if (length == capacity) {
        T* oldElements = elements;
        elements = new T[capacity = capacity * 2];
        copy(oldElements, oldElements + length, elements);
        delete[] oldElements;
    }
    elements[length++] = info;
    return length;
}
// Template class to return the popped element
template <typename T>
T Vector<T>::popBack(){
    return elements[length-- - 1];
}
// Template class to return the size of
template <typename T>
long long Vector<T>::size() const{
    return length;
}
// Template class to return the element of
// vector at given index
template <typename T>
T& Vector<T>::operator[](long long index)
{
    // if given index is greater than the
    // size of vector print Error
    if (index >= length) {
        cout << "Eroare:indexul nu se gaseste in Vector ";
        exit(0);
    }

    // else return value at that index
    return *(elements + index);
}
//return begin iterator
template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() const{
    return Iterator(elements);
}
//return end iterator
template <typename T>
typename Vector<T>::Iterator
Vector<T>::end() const{
    return Iterator(elements + length);
}
// Template class to display element in
// vector
template <typename V>
void displayVector(V& v, bool dereferenceValues  = false) {

    typename V::Iterator itr;
    for(itr = v.begin(); itr != v.end();itr++) {
        if(dereferenceValues) { cout << **itr; }
        else {cout << *itr; }
        cout << "\n";
    }

}

class IOInterface {
public:
    // virtualizarea citirii
    virtual istream& citire (istream& is) = 0;
    virtual ostream& afisare (ostream& os) const = 0;
};
class CNPexception:public exception{
    const char* what(){
        return "CNP invalid";
    }
};
class dataNasterii_exception:public exception{
    const char* what (){
        return "Data nasterii invalida";
    }
};
class DoctorException:public exception{
    const char* what (){
        return "numar ore invalid";
    }
};
class genderException:public exception{
    const char* what (){
        return "invalid gender";
    }
};
class salariuException:public exception{
    const char* what (){
        return "salariu invalid";
    }
};
class specException: public exception {
    const char* what (){
        return "numar invalid";
    }
};
class memException: public exception{
    const char* what (){
        return "pointer nu poate fi sters";
    }
};
class Persoana:public IOInterface{
protected:
    char* nume;
    char* prenume;
    string dataNasterii;
    string CNP;
    char gen;
public:
    //constructorul cu toti parametrii
    Persoana (char* Nume, char* Prenume, string dataNasterii, string CNP, char Gen);
    //constructor fara parametrii
    Persoana ();
    //copy-constructor
    Persoana (const Persoana& pers);
    istream& citire(istream& in) ;
    ostream& afisare (ostream& os ) const;
    //supraincarcare
    Persoana& operator = (const Persoana& p);
    //supraincarcare citire afisare
    friend istream& operator >> (istream& in, Persoana& p);
    friend ostream& operator << (ostream& out, const Persoana& p);
    //calcul varsta
    int varsta () const;
    ~Persoana();
};
int Persoana:: varsta () const{
    int n = this->dataNasterii.length();
    int numar = (this->dataNasterii[(n-4)]-48)*1000+ (this->dataNasterii[(n-3)]-48)*100 +
                (this->dataNasterii[(n-2)]-48)*10 + (this->dataNasterii[(n-1)]-48) ;
    return 2022-numar;
}
Persoana& Persoana::operator = (const Persoana& p){
    if (this != &p){
        if (this->nume != NULL)
            delete []this->nume;
        if (this->prenume != NULL)
            delete []this->prenume;
        this->nume = new char[100];
        this->prenume= new char[100];
        strcpy(this->nume, p.nume);
        strcpy(this->prenume, p.prenume);
        this->dataNasterii = p.dataNasterii;
        this->gen = p.gen;
        this->CNP = p.CNP;
    }
    return *this;
}
istream& Persoana::citire(istream &in){
    cout << "\nIntroduceti numele persoanei: ";
    char aux[100];
    in >> aux;
    this->nume = new char [strlen(aux)+1];
    strcpy (this->nume, aux);
    cout << "\nIntroduceti prenumele persoanei: ";
    in >> aux;
    this->prenume = new char [strlen(aux)+1];
    strcpy(this->prenume, aux);
    while (this->dataNasterii == ""){
        cout << "\nData nasterii: ";
        in >> this->dataNasterii;
        try{
            if (this->varsta()<0 || this->varsta()>99)
                throw dataNasterii_exception();
        }
        catch (exception& e){
            cout << e.what() << endl;
            cout << "Data nasterii invalida\n";
            this->dataNasterii = "";
        }
    }
    while (this->CNP ==""){
        cout << "\nIntroduceti CNP-ul persoanei: ";
        in >> this->CNP;
        try{
            if (this->CNP.length() != 13)
                throw CNPexception();
        }
        catch (exception& e){
            cout << e.what() << endl;
            cout << "CNP-ul are 13 cifre\n";
            this->CNP = "";
        }
    }
    while (this->gen == ' '){
        cout << "\nBarbat/Femeie[B/F]: ";
        in >> this->gen;
        try{
            if (this->gen != 'B' && this->gen != 'F')
                throw genderException();
        }
        catch (exception& e){
            cout << e.what() << endl;
            cout << "Invalid gender \n";
            this->gen = ' ';
        }
    }

    return in;

}
ostream& Persoana::afisare (ostream& os ) const{
    os << this->nume << " " << this->prenume;
    if (this->gen == 'F') {
        os << " este nascuta pe data de " ;
    }
    else {
        os << " este nascut pe data de ";
    }
    os << this->dataNasterii << endl;
    os << "Are CNP-ul " << this->CNP << endl;
    return os;
}
Persoana::Persoana (char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen){
    this->nume = new char [strlen(Nume)+1];
    strcpy(this->nume, Nume);
    this->prenume = new char [strlen(Prenume)+1];
    strcpy(this->prenume, Prenume);
    this->dataNasterii = DataNasterii;
    this->CNP = CNP;
    this->gen = Gen;
}
Persoana::Persoana (const Persoana& p){
    this->nume = new char [strlen(p.nume)+1];
    strcpy(this->nume, p.nume);
    prenume = new char [strlen(p.prenume)+1];
    strcpy(this->prenume, p.prenume);
    this->dataNasterii = p.dataNasterii;
    this->CNP = p.CNP;
    this->gen = p.gen;
}

istream& operator >> (istream& in, Persoana& p){
    return p.citire(in);
}
ostream& operator << (ostream& os, const Persoana& p){
    return p.afisare(os);
}
Persoana::Persoana(){
    this->nume = new char;
    this->prenume = new char;
    this->CNP = "";
    this->dataNasterii = "";
    this->gen = ' ';
}
Persoana::~Persoana() {
    //char*
    try {
        delete []this->nume;
        delete []this->prenume;
    }
    catch (...) {
        throw memException();
    }
    /*if (this->nume != NULL)
        delete []this->nume;
    if (this->prenume != NULL)
        delete []this->prenume;*/
}
class Angajat:public Persoana{
protected:
    float salariuNet;
public:
    //constructori
    Angajat();
    Angajat (char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen, float salariuNet);
    Angajat (const Angajat& a);
    Angajat& operator = (const Angajat& a);
    //citire + afisare
    istream& citire (istream& is);
    ostream& afisare (ostream& os) const;
    // virtual
    virtual void afisareSalariuBrut () = 0;
    virtual void afisareAngajat() ;
    //template
    template<typename t1, typename t2>
    bool comparareSalarii (t1 a, t2 b);
    ~Angajat();
    float getSalariu ();
    void setSalariu (float s);
};
void Angajat::setSalariu (float s){
    this->salariuNet = s;
}
float Angajat::getSalariu (){
    return this->salariuNet;
}
template<typename t1, typename t2>
bool comparareSalarii (t1 a, t2 b){
    if (a < b)
        return true;
    return false ;
}
void Angajat::afisareAngajat() {
    cout << "Sunt ANGAJAT la cea mai buna clinica !\n";
}
Angajat& Angajat::operator=(const Angajat &a) {
    if (this != &a) {
        // call explicit la operatorul = al clasei Persoana
        Persoana::operator=(a);
        this->salariuNet = a.salariuNet;
    }
    return *this;
}
istream& Angajat::citire (istream& is){
    Persoana::citire(is);
    while (this->salariuNet == 0){
        cout << "Introduceti salariul net al angajatului " << this->nume << " ";
        is >> this->salariuNet;
        try{
            if (this->salariuNet<0)
                throw salariuException();
        }
        catch (exception& e) {
            cout << e.what() << endl;
            cout << "Salariul nu poate fi invalid \n";
            this->salariuNet = 0;
        }
    }
    return is;
}
ostream& Angajat::afisare (ostream& os) const{
    Persoana::afisare(os);
    os << "Salariul net : " << this->salariuNet << endl;
    return os;
}
Angajat::Angajat(const Angajat& a): Persoana(a){
    this->salariuNet = a.salariuNet;
}
Angajat::~Angajat() {
    // cout << "Destructor angajat\n";
}
Angajat::Angajat (char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen, float salariuNet)
        : Persoana(Nume, Prenume, DataNasterii, CNP, Gen){
    this->salariuNet = salariuNet;
}
//constructor chaining
Angajat::Angajat(): Persoana () {
    this->salariuNet = 0;
}
class Asistenta:public Angajat {
private:
    int numarSpecializari;
    set<string> specializari;
public:
    //constructori
    Asistenta(char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen,
              float salariuNet,
              int numarSpecializari, set<string> Specializari);
    Asistenta ();
    Asistenta (const Asistenta& a);
    //operator =
    Asistenta& operator = (const Asistenta& a);
    //operator []
    string operator [] (int index);
    //citire+afisare
    istream& citire(istream& is);
    ostream& afisare(ostream &os) const;
    //
    void afisareSalariuBrut ();

    //destructor
    ~Asistenta();
};

string Asistenta:: operator [] (int index){
    set<string>::iterator itr;
    int i = 0;
    for (itr = this->specializari.begin(); itr != this->specializari.end(); itr++) {
        if (i == index )
            return ( *itr ) ;
        i++;
    }
    return "index introdus gresit";
}

Asistenta::~Asistenta() {
    //cout << "Destructor Asistenta\n";
}
Asistenta& Asistenta::operator=(const Asistenta &a) {
    if (this != &a){
        // call explicit la operatorul = al clasei Produs
        Angajat::operator =(a);
        this->numarSpecializari = a.specializari.size();
        this->specializari = a.specializari;
    }
    return *this;
}
Asistenta::Asistenta(const Asistenta& a): Angajat(a){
    //this->numarSpecializari = a.numarSpecializari;
    this->specializari = a.specializari;
    this->numarSpecializari = a.specializari.size();
}
void Asistenta::afisareSalariuBrut (){
    cout << "Salariul Brut al asistentei " << this->nume
         << " este: " << this->salariuNet*10 << endl;
}
Asistenta::Asistenta(char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen,
                     float salariuNet, int numarSpecializari,set<string> Specializare):
        Angajat(Nume, Prenume, DataNasterii, CNP, Gen, salariuNet){
    this->numarSpecializari = numarSpecializari;
    this->specializari = Specializare;
}
istream& Asistenta::citire(istream &is) {
    Angajat::citire(is);
    string s;
    int numar;
    while (this->numarSpecializari == 0){
        cout << "\nIntroduceti numarul specializarilor: /n";
        is >> s;
        try{
            try {
                numar = stoi(s);
            } catch(exception& e) {
                throw specException();
            }
            if (numar < 0)
                throw specException();
            if(numar == 0) {
                this->numarSpecializari = 0;
                break;
            }

            this->numarSpecializari = numar;
        }
        catch (exception& e) {
            cout << e.what() << endl;
            cout << "/nNUMARUL de specilizari\n";
            this->numarSpecializari = 0;
        }
    }

    int i;
    for (i=0; i<this->numarSpecializari; i++) {
        is >> s;
        this->specializari.insert(s);
    }
    this->numarSpecializari = this->specializari.size();
    return is;
}
ostream& Asistenta::afisare(ostream &os) const {
    Angajat::afisare(os);
    if (this->numarSpecializari){
        cout << "Asistent cu specializari in ";
        set<string>::iterator itr;
        for (itr = this->specializari.begin(); itr != this->specializari.end(); itr++) {
            cout << *itr << " ";
        }
        cout << endl;
    }
    return os;
}
Asistenta::Asistenta():Angajat(){
    this->numarSpecializari = 0;
}
class Pacient:public Persoana{
protected:
    bool clientFidel;
    float sumaAchitata;
public:
    //constructori
    Pacient();
    Pacient(char* Nume, char* Prenume, string DataNasterii, string CNP,
            char Gen, bool ClientFidel, float SumaAchitata);
    Pacient (const Pacient& p);
    //operator =
    Pacient& operator = (const Pacient& p);
    //citire-afisare
    ostream& afisare(ostream& os) const;
    istream& citire (istream& is);
    void setterSumaAchitata (float suma);
    bool getterClientFidel() const;
    float getterSumaAchitata () const;
    Pacient operator-=(int x) ;
    //destructor
    ~Pacient();
};
float Pacient::getterSumaAchitata() const {
    return this->sumaAchitata;
}
Pacient Pacient::operator-=(int x) {
    this->sumaAchitata -= x;
    return *this;
}
bool Pacient::getterClientFidel() const{
    return this->clientFidel;
}
void Pacient::setterSumaAchitata(float suma) {
    this->sumaAchitata = suma;
}
Pacient::~Pacient() {
    //cout << "Destructor Pacient\n";
}
Pacient& Pacient::operator = (const Pacient& p){
    if (this != &p){
        // call explicit la operatorul = al clasei Persoana
        Persoana::operator=(p);
        this->clientFidel = p.clientFidel;
        this->sumaAchitata = p.sumaAchitata;
    }
    return *this;
}
istream& Pacient::citire(istream& is){
    Persoana::citire (is);
    cout << "Este client fidel ?[1/0] ";
    is >> this->clientFidel;
    cout << "Cat are de achitat ";
    is >> this->sumaAchitata;



    return is;
}
ostream& Pacient::afisare(ostream& os) const {
    Persoana::afisare(os);
    if (this->clientFidel == true)
        os <<this->nume << " este client fidel, a platit " << this->sumaAchitata << endl;
    else
        os << this->nume << " nu este client fidel, a platit " << this->sumaAchitata << endl;
    return os;
}
Pacient::Pacient(const Pacient& p):Persoana(p){
    this->clientFidel = p.clientFidel;
    this->sumaAchitata = p.sumaAchitata;
}
Pacient::Pacient():Persoana(){
    this->clientFidel = true;
    this->sumaAchitata = 0;
}
Pacient::Pacient(char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen, bool ClientFidel, float SumaAchitata)
        :Persoana(Nume, Prenume, DataNasterii, CNP, Gen){
    this->clientFidel = ClientFidel;
    this->sumaAchitata = SumaAchitata;
}

class Doctor:public Angajat {
protected:
    int numarOre;
public:
    //constructori
    Doctor ();
    Doctor (char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen, float salariuNet, int numarOre);
    Doctor (const Doctor& d);
    //supraincarcare =
    Doctor& operator = (const Doctor& d);
    //afisare + citire
    istream& citire (istream& is);
    ostream& afisare (ostream& os) const;
    void afisareSalariuBrut ();
    // destructor
    ~Doctor();
    void afisareAngajat (){
        cout << this->nume << endl;
        cout << "Sunt doctor la cea mai buna clinica din lume\n";
    }

};

void Doctor::afisareSalariuBrut (){
    cout << "Salariul Brut al doctorului "
         <<this->nume
         << " este: " << this->salariuNet*2 << endl;
}
istream& Doctor:: citire(istream& is){
    Angajat::citire(is);

    string s;
    int numar;
    while (this->numarOre == 0){
        cout << "Cate ore lucrate are Doctorul " << this->nume << " ?";
        is >> s;
        try{
            try {
                numar = stoi(s);
            } catch(exception& e) {
                throw DoctorException();
            }
            if (numar < 0)
                throw specException();
            if(numar == 0) {
                this->numarOre = 0;
                break;
            }

            this->numarOre = numar;
        }
        catch (exception& e) {
            cout << e.what() << endl;
            cout << "/nNUMARUL de ore este numar natural! Try again\n";
            this->numarOre = 0;
        }
    }

    return is;
}
ostream& Doctor:: afisare(ostream& os) const{
    Angajat::afisare(os);
    os << "Doctorul " << this->nume << " are "<< this->numarOre << " ore lucrate \n";
    return os;
}
Doctor& Doctor::operator=(const Doctor &d) {
    if (this != &d){
        Angajat::operator=(d);
        this->numarOre = d.numarOre;
    }
    return *this;
}
Doctor::Doctor(const Doctor& d):Angajat(d){
    this->numarOre = d.numarOre;
}
Doctor::Doctor (char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen,
                float salariuNet, int NumarOre): Angajat(Nume, Prenume, DataNasterii, CNP, Gen, salariuNet){
    this->numarOre = NumarOre;
}

Doctor::Doctor():Angajat() {
    this->numarOre = 0;
}
Doctor::~Doctor() {
    //cout << "Destructor Doctor\n";
}
class Pediatru:public Doctor{
public:
    //constructori
    Pediatru(char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen,
             float salariuNet, int NumarOre);
    Pediatru();
    Pediatru(const Pediatru& p);

    void afisareVarsta()const;
    void afisareSalariuBrut ();
    virtual void afisarePediatru (){
        cout << this->nume << endl;
        cout << "Sunt pediatru \n";
    }
    ~Pediatru();
};
void Pediatru::afisareVarsta() const {
    cout << "Pediatrul " << this->nume << " are "
         <<  this->varsta() << " ani.\n";
}
void Pediatru::afisareSalariuBrut (){
    cout << "Salariul Brut este: " << this->salariuNet*3 << endl;
}

Pediatru::~Pediatru(){
    //cout << "Destructor Pediatru\n";
}
Pediatru::Pediatru(char *Nume, char *Prenume, string DataNasterii, string CNP, char Gen,
                   float salariuNet, int NumarOre):
        Doctor(Nume, Prenume, DataNasterii, CNP, Gen, salariuNet, NumarOre){}
Pediatru::Pediatru():Doctor() {}
Pediatru::Pediatru (const Pediatru& p): Doctor(p){}

class Chirurg:public Doctor{
protected:
    string pregatire;
public:
    //constructori
    Chirurg(char* Nume, char* Prenume, string DataNasterii, string CNP, char Gen,
            float salariuNet, int NumarOre, string pregatire);
    Chirurg();
    Chirurg(const Chirurg& p);
    //operatori
    Chirurg& operator = (const Chirurg& c);
    Chirurg operator += (int x);
    //void afisareSalariuBrut ();
    bool operator >(int x);
    void afisareChirurg (){
        cout << this->nume << endl;
        cout << "Sunt chirurg \n";
    }
    //citire + afisare
    istream& citire (istream& is );
    ostream& afisare (ostream& os) const;
    ~Chirurg();
};
/*
void Chirurg::afisareSalariuBrut (){
    cout << "Salariul Brut este: " << this->salariuNet*4 << endl;
}
 */
istream& Chirurg:: citire (istream& is){
    Doctor::citire(is);
    cout << "Ce pregatire are chirurgul ? ";
    is >> this->pregatire;
    return is;
}
ostream& Chirurg::afisare(ostream& os)const{
    Doctor::afisare (os);
    os << this->pregatire << endl;
    return os;
}
bool Chirurg:: operator > (int x){
    if (this->numarOre > x)
        return true;
    return false;
}
Chirurg Chirurg::operator+=(int x) {
    this->salariuNet += x;
    return *this;
}
Chirurg::~Chirurg(){
    //cout << "Destructor Chirurg\n";
}
Chirurg& Chirurg::operator=(const Chirurg& c) {
    if (this != &c){
        Doctor::operator=(c);
        this->pregatire = c.pregatire;
    }
    return *this;
}
Chirurg::Chirurg(char *Nume, char *Prenume, string DataNasterii, string CNP, char Gen,
                 float salariuNet, int NumarOre, string Pregatire):
        Doctor(Nume, Prenume, DataNasterii, CNP, Gen, salariuNet, NumarOre){
    this->pregatire = Pregatire;
}
Chirurg::Chirurg():Doctor() {
    this->pregatire = "undefined";
}
Chirurg::Chirurg (const Chirurg& p): Doctor(p){
    this->pregatire = p.pregatire;
}
class Medicament {
private:
    string categorie;
    int nr;
    map<string, float> map1;
public:
    //constructori
    Medicament();
    Medicament(string categorie,int nr,map<string, float> m);
    Medicament (const Medicament& m);
    //supraincarcare =
    Medicament& operator = (const Medicament& m);
    //citire-afisare
    friend ostream& operator << (ostream& out, const Medicament& m);
    friend istream& operator >> (istream& out,  Medicament& m);
    //reducere de pret
    Medicament operator-=(int numar);
    //destructor
    ~Medicament();
};
Medicament Medicament::operator-=(int numar) {
    map<string, float> ::iterator itr;
    for (itr = this->map1.begin(); itr != this->map1.end(); ++itr) {
        itr->second -= numar;
    }
    return *this;
}
istream& operator >> (istream& is,  Medicament& m){
    cout << "\nCategorie: ";
    is >> m.categorie;
    cout << "\nNumar produse: ";
    is >> m.nr;
    string num;
    float price;
    int i;
    for (i=0; i<m.nr; i++){
        is >> num >> price;
        m.map1.insert({num, price});
    }
    return is;
}
Medicament& Medicament::operator=(const Medicament& m){
    if (this != &m){
        this->categorie = m.categorie;
        this->nr = m.nr;
        this->map1 = m.map1;
    }
    return *this;
}
ostream& operator << (ostream& out, const Medicament& m){
    out << "Medicamente din categoria " << m.categorie <<endl;
    for(auto x: m.map1)
    {
        out << x.first << " costa " <<
            x.second <<endl;
    }
    return out;
}

Medicament::~Medicament() {
    //cout << "Destructor medicament\n"
}
Medicament::Medicament() {
    this->categorie = " ";
    this->nr = 0;
}
Medicament::Medicament(string categorie,int nr, map<string, float> m) {
    this->categorie = categorie;
    this->nr = nr;
    this->map1 = m;
}
Medicament::Medicament(const Medicament &m) {
    this->categorie = m.categorie;
    this->nr = m.nr;
    this->map1 = m.map1;
}
class Meniu {
private:
    static Meniu* INSTANCE;
    Meniu(){}
    Meniu (const Meniu& meniu){}
public:
    static Meniu* getInstance (){
        if (INSTANCE == NULL){
            INSTANCE = new Meniu();
        }
    }
    void launch (){
        Vector<int> v;
        Vector<Medicament*> listaMedicamente = Vector<Medicament*>();
        //declarare date
        Medicament* m = new Medicament("stomac",2, {{"a", 1}, {"b", 2} });
        Medicament* m1 = new Medicament();
        listaMedicamente.pushBack(m);
        listaMedicamente.pushBack(m1);

        vector<Angajat *> listaAngajati = vector<Angajat*>();
        list<Pacient *> listaPacienti = list <Pacient*>();
        Angajat *d = new Doctor();
        Angajat *a = new Asistenta();
        Angajat *p = new Pediatru();
        Angajat *c = new Chirurg();
        Pacient *pac = new Pacient();
        int option, i;
        string categorie;
        Angajat *doc = new Doctor("Ioana", "Hadid", "12.12.2002", "123456",
                                  'B', 10, 20);
        listaAngajati.push_back(doc);
        Angajat *d1 = new Doctor("eugen", "scarlatescu", "12.12.2002", "7", 'B', 70, 90);
        listaAngajati.push_back(d1);
        Pacient *pac1 = new Pacient("Ioana", "Hadid", "12.12.2002", "123456", 'B', false, 1276);
        Pacient *pac3 = new Pacient("Telefonica", "Hadid", "12.12.2002", "123456", 'B', true, 1276);

        listaPacienti.push_back(pac1);
        listaPacienti.push_back(pac3);

        Angajat *ass = new Asistenta("Ioana", "Hadid", "12.12.2002", "123456", 'B', 12000, 1, {"chirurgie"});
        Angajat *ass1 = new Asistenta("Marinica", "NAmol", "12.12.2002", "123456", 'B', 12000,1, {"chirurgie"});

        listaAngajati.push_back(ass);
        listaAngajati.push_back(ass1);
        ass = ass1;
        Angajat *ass3(ass1);
        Angajat *chi = new Chirurg("Ioana", "Hadid", "12.12.2002",
                                   "123456", 'B', 10, 11, "avanasat");
        listaAngajati.push_back(chi);
        Angajat *ped = new Pediatru("eugen", "scarlatescu", "12.12.2000", "7", 'B', 70, 90);
        listaAngajati.push_back(ped);
        ifstream f;
        f.open ("informatii.txt");
        ofstream fout ("afisarePacienti.out");
        ofstream foutAng ("afisareAngajati.out");
        while (true){
            cout << "\nACESTA ESTE MENIUL PRINCIPAL\n"
                 << "1.Introduceti date despre persoana\n"
                 << "2.Afisare pentru o anumita categorie\n"
                 << "3.In cazul Angajatilor, afisati salariul brut pe care acestia il incaseaza\n"
                 << "4.In cazul chirurgilor cu peste 10 ore lucrate, se face "
                 << "marire de salariu\n"
                 << "5.Varsta medie a Angajatilor\n"
                 << "6.Reducere pentru pacientii fideli\n"
                 << "7.Reducere pentru clientii care au achitat mai mult de 1000 ron\n"
                 << "8.Introducere medicament nou\n"
                 << "9.Afisare Medicamente\n"
                 << "10.Reducere a pretului medicamentelor\n"
                 << "11.Exit\n"
                 <<"*************************************************\n";
            cin >> option;
            switch (option) {
                case 1:
                    cout << "Din ce categorie face parte ? \n";
                    cout << "Chirurg,\nAsistenta, \nDoctor,\nPediatru,\nPacient\n";
                    cin >> categorie;
                    if (categorie == "Asistenta") {
                        a = new Asistenta();
                        f >> *a;
                        //adaugare la vector
                        listaAngajati.push_back(a);
                    }
                    if (categorie == "Doctor") {
                        d = new Doctor();
                        cin >> *d;
                        //adaugare la vector
                        listaAngajati.push_back(d);
                    }
                    if (categorie == "Pediatru") {
                        p = new Pediatru();
                        cin >> *p;
                        //adaugare la vector
                        listaAngajati.push_back(p);

                    }

                    if (categorie == "Pacient") {
                        pac = new Pacient();
                        cin >> *pac;
                        //adaugare la vector
                        listaPacienti.push_back(pac);

                    }
                    if (categorie == "Chirurg") {
                        c = new Chirurg();
                        cin >> *c;
                        //adaugare la vector
                        listaAngajati.push_back(c);
                    }
                    break;
                case 2:
                    cout << "Pentru ce categorie ? \n";
                    cout << "Angajati\n,\nPacienti\n";
                    cin >> categorie;
                    if (categorie == "Angajati") {
                        for (i = 0; i < listaAngajati.size(); i++)
                            foutAng << *listaAngajati[i] << endl;
                    }

                    if (categorie == "Pacienti") {
                        for (auto x: listaPacienti){
                            fout << *x << endl;
                        }

                    }
                    break;
                case 3:
                    if (listaAngajati.size()) {
                        cout << "Angajati ai clinicii\n";
                        for (i = 0; i < listaAngajati.size(); i++)
                            listaAngajati[i]->afisareSalariuBrut();
                    }
                    break;
                case 4:
                    if (listaAngajati.size()) {
                        cout << "Chirurgi cu peste 10 ore au primit marire de 100 ron\n";
                        for (i = 0; i < listaAngajati.size(); i++) {
                            if (dynamic_cast<Chirurg *>(listaAngajati[i]))
                                //cout << "Ana";
                                listaAngajati[i]->setSalariu(listaAngajati[i]->getSalariu() * 1.20);
                            //if (*listaChirurgi[i] > 10)
                            //*listaChirurgi[i]+=100;
                        }
                    }
                    break;
                case 5: {
                    float medieVarsta = 0;
                    if (listaAngajati.size()) {
                        cout << "Angajatii au media de varsta: ";
                        for (i = 0; i < listaAngajati.size(); i++)
                            medieVarsta += listaAngajati[i]->varsta();
                        cout << medieVarsta * 1.0 / listaAngajati.size() << endl;
                    }
                    break;
                }

                case 6: {
                    for (auto x:listaPacienti){
                        if (x->getterClientFidel() == 1)
                            x->setterSumaAchitata(x->getterSumaAchitata() - 0.1*x->getterSumaAchitata());

                    }
                    break;
                }
                case 7:{
                    for (auto x: listaPacienti){
                        if (x->getterSumaAchitata() >= 1000)
                            *x-=150;
                    }

                    break;
                }
                case 8:{
                    m1 = new Medicament();
                    cin >> *m1;
                    listaMedicamente.pushBack(m1);
                    break;
                }

                case 9:{
                    displayVector(listaMedicamente, true);
                    break;
                }
                case 10:{
                    for (i=0; i<listaMedicamente.size (); i++)
                        listaMedicamente[i]-=10;
                }
            }
            if (option == 11) {
                f.close ();
                fout.close();
                foutAng.close();
                break;
            }
        }
    }
    Meniu& operator=(const Meniu& meniu){
        return *INSTANCE;
    }
};
Meniu* Meniu::INSTANCE=0;
int main() {
    Meniu::getInstance()->launch();

    return 0;
}
