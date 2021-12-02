//gestionarea unui club sportiv
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <list>
#include <map>
#include <set>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");
class Sportiv
{
protected:
    string cnp;
    char* nume_de_familie;
    char* prenume;
    int anul_nasterii;
    char gen;//F-feminin, M-masculin
    string categorie;//copil,cadet,junior,senior,master
    int primul_an_in_care_a_participat_la_concursuri;
    int nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs;
    int nr_competitii_in_fiecare_an;//este acelasi numar pentru fiecare an
    int nr_ani;//pentru care vreau sa vad punctajele
    int ** nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii;//o matrice cu punctaje
    int numar_gustari_primite_la_final_de_antrenament;
    const int numar_legitimatie;

public:
    static int numar_id;
    const static int arie_medie_sportiv;//aria medie pe care o ocupa un sportiv(sau un om intr-o sala sportiva) este de 2 m^2
    Sportiv();
    Sportiv(string cnp,char* nume_de_familie,char* prenume, int anul_nasterii,char gen, string categorie,int primul_an_in_care_a_participat_la_concursuri,int nr_ani,int nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs,int nr_competitii_in_fiecare_an, int** nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii,int numar_gustari_primite_la_final_de_antrenament);
    Sportiv(string cnp,char* nume_de_familie, char* prenume,char gen, int anul_nasterii, string categorie);
    Sportiv(const Sportiv& sporti);
    Sportiv& operator=(const Sportiv& sporti);
    virtual ~Sportiv();

    friend ostream& operator<<(ostream& out, const Sportiv& sportiv);
    friend istream& operator>>(istream& in,Sportiv& sportiv);

    string getCnp();

    void setNumeDeFamilieSportiv(char* nume_de_familie);
    char* getNumeDeFamilieSportiv();

    void setPrenumeSportiv(char* prenume);
    char * getPrenumeSportiv();

    void setAnulNasterii(int anul_nasterii);
    int getAnulNasterii();

    void setGen(char gen);
    char getGen();

    void setCategorie(string categorie);
    string getCategorie();

    void setPrimulAnInCareAParticipatLaConcursuri(int primul_an_in_care_a_participat_la_concursuri);
    int getPrimulAnInCareAParticipatLaConcursuri();


    int getNumarAni();

    int getNumarLegitimatie();

    int getNumarMaximDeProbeLaCarePoateParticipaLaFiecareConcurs();

    int getNumarCompetitiiInFiecareAn();

    void setNumarGustariPrimiteLaFinalDeAntrenament(int numar_gustari_primite_la_final_de_antrenament);
    int getNumarGustariPrimiteLaFinalDeAntrenament();

    void setNumarPunctajObtiuntPeParcursulAnilorPerProbaPerCompetitii(int ** nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii,int nr_ani,int nr_competitii_in_fiecare_an,int nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs);
    int **getNumarPunctajObtiuntPeParcursulAnilorPerProbaPerCompetitii();

    const Sportiv& operator--();//pentru numarul de gustari
    const Sportiv operator--(int);//pentru numarul de gustari
    int operator+(const Sportiv &a);//pentru numarul de gustari
    bool operator >(const Sportiv& a);//pentru primul an competitional
    bool operator ==(const Sportiv& a);//pentru a vedea daca am acelasi cnp

    void rezulate_sportiv();
};
int Sportiv::numar_id=1;
const int Sportiv::arie_medie_sportiv=2;//aria medie pe care o ocupa un sportiv este de 2 m^2

void Sportiv::rezulate_sportiv()//in ce an a avut punctajul cel mai mare si pentru fiecare an sa stiu ce tipuri de medalii am
{
    int s, maxi=0,numarul_anului=0,an,nr_loc1,nr_loc2,nr_loc3,k=0,ok;
    int suma[nr_ani];//sumele de puncte le fac pentru fiecare an in parte
    int loc1[nr_ani];//vad cate medalii de locul 1 are per fiecare an
    int loc2[nr_ani];//vad cate medalii de locul 2 are per fiecare an
    int loc3[nr_ani];//vad cate medalii de locul 3 are per fiecare an
    int anul[nr_ani];//pun anii in vector

    for(int i=0; i<this->nr_ani; i++)
    {
        s=0;//fac suma punctajelor per an
        nr_loc1=0;//fac suma numarului de medalii de locul 1
        nr_loc2=0;//fac suma numarului de medalii de locul 2
        nr_loc3=0;//fac suma numarului de medalii de locul 3
        for (int j=0; j<(this->nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs*this->nr_competitii_in_fiecare_an); j++)
        {
            s=s+this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j];
            if(this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j]==3)
                nr_loc1=nr_loc1+1;
            if(this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j]==2)
                nr_loc2=nr_loc2+1;
            if(this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j]==1)
                nr_loc3=nr_loc3+1;
        }
        loc1[i]=nr_loc1;
        loc2[i]=nr_loc2;
        loc3[i]=nr_loc3;
        suma[i]=s;

    }
    ok=0;
    for(int i=0; i<this->nr_ani; i++)
    {
        if(suma[i]!=0)
            ok=ok+1;
    }
    if (ok==0)//adica in cazul in care nu are niciun premiu
        cout<<"\n"<<this->nume_de_familie<<" "<<this->prenume<<" nu are nicio medalie in acest interval de timp";
    else

    {
        for(int i=0; i<this->nr_ani; i++)
        {
            if (suma[i]>maxi)
            {
                maxi=suma[i];
                numarul_anului=i;//retin indicele anului
                k=0;//indicele pentru vectorul care imi specifica anii in care numarul de puncte este maxim
                anul[k]=i+this->primul_an_in_care_a_participat_la_concursuri;//aici calculez care este acel an
            }
            else
            {
                if(suma[i]==maxi && suma[i]!=0)//se poate intampla sa nu castige nimic
                {
                    k=k+1;
                    anul[k]=i+this->primul_an_in_care_a_participat_la_concursuri;
                }

            }

            cout<<"\nIn anul "<<i+this->primul_an_in_care_a_participat_la_concursuri<<this->getNumeDeFamilieSportiv()<<" "<<this->getPrenumeSportiv()<<" a obtinut un numar de: ";
            if(loc1[i]==1)
                cout<<loc1[i]<<" medalie de locul 1, ";
            else
                cout<<loc1[i]<<" medalii de locul 1, ";
            if(loc2[i]==1)
                cout<<loc2[i]<<" medalie de locul 2, ";
            else
                cout<<loc2[i]<<" medalii de locul 2, ";
            if(loc3[i]==1)
            {
                cout<<loc3[i]<<" medalie de locul 3, ajungand sa acumuleze un numar de "<<suma[i];
                if(suma[i]==1)
                    cout<<" punct.\n";
                else
                    cout<<" puncte.\n";
            }
            else
            {
                cout<<loc3[i]<<" medalii de locul 3,ajungand sa acumuleze un numar de "<<suma[i];
                if(suma[i]==1)
                    cout<<" punct.\n";
                else
                    cout<<" puncte.\n";
            }
        }

        an=numarul_anului+this->primul_an_in_care_a_participat_la_concursuri;
        if(k==0)
        {
            cout<<"Astfel, in anul "<<an<<" "<<this->nume_de_familie<<" "<<this->prenume<<" a acumulat cel mai mare punctaj din cariera sportiva, anume: "<<maxi;
            if(maxi==1)
                cout<<" punct.\n";
            else
                cout<<" puncte.\n";

        }
        else
        {
            if(k>=1)
            {
                cout<<"Astfel, in anii: ";
                for(int i=0; i<k+1; i++)
                    cout<<anul[i]<<", ";
                cout<<this->nume_de_familie<<" "<<this->prenume<<" a acumulat cel mai mare punctaj din cariera sportiva, anume: "<<maxi<<" puncte.\n";
            }
        }
    }

}


bool Sportiv::operator ==(const Sportiv& a)//sportivii au cnp unic
{
    if(this->cnp==a.cnp )
        return true;
    return false;
}
bool Sportiv:: operator >(const Sportiv& a)//compar anii in care participa la primul concursuri
{
    if(this->primul_an_in_care_a_participat_la_concursuri>a.primul_an_in_care_a_participat_la_concursuri)
        return true;
    return false;
}

int Sportiv::operator+(const Sportiv &a)
{
    Sportiv aux(*this);
    aux.numar_gustari_primite_la_final_de_antrenament=aux.numar_gustari_primite_la_final_de_antrenament+a.numar_gustari_primite_la_final_de_antrenament;
    return aux.getNumarGustariPrimiteLaFinalDeAntrenament();
}

const Sportiv& Sportiv :: operator--()//predecrementare
{
    this->numar_gustari_primite_la_final_de_antrenament--;
    return *this;
}

const Sportiv Sportiv::operator--(int)//postdecrementare
{
    Sportiv aux (*this);
    this->numar_gustari_primite_la_final_de_antrenament--;
    return aux;
}

void Sportiv:: setNumeDeFamilieSportiv(char* nume_de_familie)//setter
{
    if(this->nume_de_familie !=NULL)
        delete[] this->nume_de_familie;
    this->nume_de_familie= new char [strlen(nume_de_familie)+1];
    strcpy(this->nume_de_familie,nume_de_familie);
}

char* Sportiv::getNumeDeFamilieSportiv()//getter
{
    return this->nume_de_familie;
}
string Sportiv::getCnp()//getter
{
    return this->cnp;
}
void Sportiv::setPrenumeSportiv(char* prenume)//setter
{
    if(this->prenume !=NULL)
        delete[] this->prenume;
    this->prenume= new char [strlen(prenume)+1];
    strcpy(this->prenume,prenume);
}

char * Sportiv::getPrenumeSportiv()//getter
{
    return this-> prenume;
}

void Sportiv:: setAnulNasterii(int anul_nasterii)//setter
{
    this->anul_nasterii=anul_nasterii;
}

int Sportiv:: getAnulNasterii()//getter
{
    return this->anul_nasterii;
}

void Sportiv:: setGen(char gen)
{
    this -> gen=gen;
}

char Sportiv:: getGen()
{
    return this ->gen;
}

void Sportiv:: setCategorie(string categorie)
{
    this -> categorie=categorie;
}

string Sportiv :: getCategorie()
{
    return this -> categorie;
}

void Sportiv:: setPrimulAnInCareAParticipatLaConcursuri(int primul_an_in_care_a_participat_la_concursuri)
{
    this ->primul_an_in_care_a_participat_la_concursuri=primul_an_in_care_a_participat_la_concursuri;
}

int Sportiv:: getPrimulAnInCareAParticipatLaConcursuri()
{
    return this->primul_an_in_care_a_participat_la_concursuri;
}

int Sportiv:: getNumarAni()
{
    return this->nr_ani;
}

int Sportiv::getNumarLegitimatie() //aici e getter pt const
{
    return this->numar_legitimatie;
}

int Sportiv::getNumarMaximDeProbeLaCarePoateParticipaLaFiecareConcurs()
{
    return this->nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs;
}

int Sportiv:: getNumarCompetitiiInFiecareAn()
{
    return this->nr_competitii_in_fiecare_an;
}

void Sportiv:: setNumarGustariPrimiteLaFinalDeAntrenament(int numar_gustari_primite_la_final_de_antrenament)
{
    this->numar_gustari_primite_la_final_de_antrenament=numar_gustari_primite_la_final_de_antrenament;
}

int Sportiv :: getNumarGustariPrimiteLaFinalDeAntrenament()
{
    return this->numar_gustari_primite_la_final_de_antrenament;
}

void Sportiv :: setNumarPunctajObtiuntPeParcursulAnilorPerProbaPerCompetitii(int ** nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii,int nr_ani,int nr_competitii_in_fiecare_an,int nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs)
{

    if(this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii !=NULL)
    {
        for(int i=0; i<this->nr_ani; i++)
            delete [] this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i];
        delete [] this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii;
    }
    this->nr_competitii_in_fiecare_an=nr_competitii_in_fiecare_an;
    this->nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs=nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs;
    this->nr_ani=nr_ani;
    this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii=new int*[nr_ani];
    for(int i=0; i<nr_ani; i++)
        this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i]=new int[nr_competitii_in_fiecare_an*nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs];

    for (int i=0; i<nr_ani; i++)
        for(int j=0; j<nr_competitii_in_fiecare_an*nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs; j++)
            this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j]=nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j];

}

int ** Sportiv:: getNumarPunctajObtiuntPeParcursulAnilorPerProbaPerCompetitii()
{
    return this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii;
}

ostream& operator<<(ostream& out, const Sportiv& sportiv)
{
    out<<"\nNume de familie sportiv: "<<sportiv.nume_de_familie;
    out<<"\nPrenume sportiv: "<<sportiv.prenume;
    out<<"\nAnul nasterii: "<<sportiv.anul_nasterii;
    out<<"\nGenul: ";
    if (sportiv.gen=='F')
        out<<"Feminin";
    else
        out<<"Masculin";
    out<<"\nCnp: "<<sportiv.cnp;
    out<<"\nCategoria din care face parte: "<<sportiv.categorie;
    out<<"\nNumarul de dulciuri primite la final de antrenament: "<<sportiv.numar_gustari_primite_la_final_de_antrenament;
    if(sportiv.primul_an_in_care_a_participat_la_concursuri!=0)
        out<<"\nPrimul an competitional este: "<<sportiv.primul_an_in_care_a_participat_la_concursuri;
    if(sportiv.nr_ani!=0 && sportiv.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs!=0 && sportiv.nr_competitii_in_fiecare_an!=0)
    {
        out<<"\nNumarul de ani pentru care doresc sa vad rezultatele acestui sportiv: "<<sportiv.nr_ani;
        out<<"\nNumarul maxim de probe la care poate participa la fiecare concurs: "<<sportiv.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs;
        out<<"\nNumarul de competitii care se desfasoara in fiecare an: "<<sportiv.nr_competitii_in_fiecare_an;
        out<<"\nPunctele alocate pentru fiecare proba din competitiile la care a participat(pe prima linie sunt punctajele din primul an, pe a doua - cele din al doilea an, etc. ):\n";

        for(int i=0; i<sportiv.nr_ani; i++)
        {
            for(int j=0; j<(sportiv.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs*sportiv.nr_competitii_in_fiecare_an); j++)

                out<<sportiv.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j]<<" ";
            out<<"\n";
        }
    }
    return out;
}
istream & operator>>(istream& in,Sportiv &sportiv)
{
    in.get();
    cout<<"\nNume de familie sportiv: ";
    char nume_auxiliar[100];
    in.getline(nume_auxiliar,100);

    if(sportiv.nume_de_familie!=NULL)
        delete[] sportiv.nume_de_familie;
    sportiv.nume_de_familie=new char[strlen(nume_auxiliar)+1];
    strcpy(sportiv.nume_de_familie,nume_auxiliar);

    cout<<"\nPrenume sportiv: ";

    char nume_auxiliar1[100];
    in.getline(nume_auxiliar1,100);

    if(sportiv.prenume!=NULL)
        delete[] sportiv.prenume;
    sportiv.prenume=new char[strlen(nume_auxiliar1)+1];
    strcpy(sportiv.prenume,nume_auxiliar1);

    cout<<"\nAnul nasterii: ";
    in>>sportiv.anul_nasterii;

    cout<<"\nGenul [F-feminin, M-masculin]: ";
    in>>sportiv.gen;
    cout<<"\nCnp: ";
    in>>sportiv.cnp;

    cout<<"\nCategorie (copii, cadeti,juniori,seniori,master): ";
    in>>sportiv.categorie;

    cout<<"\nNumarul de dulciuri primite la final de antrenament: ";
    in>>sportiv.numar_gustari_primite_la_final_de_antrenament;

    cout<<"\nPrimul an competitional: ";
    in>>sportiv.primul_an_in_care_a_participat_la_concursuri;

    cout<<"\nNumarul de ani pentru care doresc sa vad rezultatele acestui sportiv: ";
    in>>sportiv.nr_ani;

    cout<<"\nNumarul maxim de probe la care poate participa la fiecare concurs: ";
    in>>sportiv.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs;

    cout<<"\nNumarul de competitii care se desfasoara in fiecare an: ";
    in>>sportiv.nr_competitii_in_fiecare_an;

    cout<<"\nNumarul de puncte obtinut de-a lungul anilor mai sus mentionati(numarul de elemente introduse este egal cu: numarul de ani*numarul maxim de probe*numarul de competitii)\n";
    cout<<"\nDatele care se scriu sunt: 0 (puncte)-niciun loc pe podium; 1 (punct)- pentru locul 3; 2 (puncte) - locul 2; 3 (puncte) - locul 1;\n";

    if(sportiv.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii !=NULL)
    {
        for(int i=0; i<sportiv.nr_ani; i++)
            delete [] sportiv.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i];
        delete [] sportiv.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii;
    }

    sportiv.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii=new int*[sportiv.nr_ani];
    for(int i=0; i<sportiv.nr_ani; i++)
        sportiv.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i]=new int[sportiv.nr_competitii_in_fiecare_an*sportiv.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs];

    for (int i=0; i<sportiv.nr_ani; i++)
        for(int j=0; j<(sportiv.nr_competitii_in_fiecare_an*sportiv.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs); j++)
            in>>sportiv.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j];

    return in;

}

Sportiv& Sportiv::operator=(const Sportiv & sporti)
{
    if(this!=&sporti)
    {
        if(this->prenume!=NULL)
            delete [] this->prenume;

        if(this->nume_de_familie!=NULL)
            delete [] this->nume_de_familie;

        if(this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii !=NULL)
        {
            for(int i=0; i<this->nr_ani; i++)
                delete [] this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i];
            delete [] this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii;
        }


        this->prenume=new char[strlen(sporti.prenume)+1];
        strcpy(this->prenume,sporti.prenume);

        this->nume_de_familie=new char[strlen(sporti.nume_de_familie)+1];
        strcpy(this->nume_de_familie,sporti.nume_de_familie);

        this->anul_nasterii=sporti.anul_nasterii;
        this->gen=sporti.gen;
        this->cnp=sporti.cnp;
        this->categorie=sporti.categorie;
        this->numar_gustari_primite_la_final_de_antrenament=sporti.numar_gustari_primite_la_final_de_antrenament;
        this->primul_an_in_care_a_participat_la_concursuri=sporti.primul_an_in_care_a_participat_la_concursuri;
        this->nr_ani=sporti.nr_ani;
        this->nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs=sporti.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs;
        this->nr_competitii_in_fiecare_an=sporti.nr_competitii_in_fiecare_an;

        this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii=new int*[sporti.nr_ani];
        for(int i=0; i<sporti.nr_ani; i++)
            this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i]=new int[sporti.nr_competitii_in_fiecare_an*sporti.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs];

        for (int i=0; i<sporti.nr_ani; i++)
            for(int j=0; j<sporti.nr_competitii_in_fiecare_an*sporti.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs; j++)
                this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j]=sporti.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j];

    }
    return *this;
}

Sportiv::Sportiv():numar_legitimatie(numar_id++)
{
    nume_de_familie= new char[strlen("Necunoscut")+1];
    strcpy(nume_de_familie,"Necunoscut");

    prenume= new char[strlen("Necunoscut")+1];
    strcpy(prenume,"Necunoscut");
    cnp="Necunoscut";
    anul_nasterii=0;
    gen='0';
    categorie="Necunoscut";
    primul_an_in_care_a_participat_la_concursuri=0;
    nr_ani=0;
    nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs=0;
    nr_competitii_in_fiecare_an=0;
    nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii=NULL;
    numar_gustari_primite_la_final_de_antrenament=0;
}
Sportiv::Sportiv(string cnp,char* nume_de_familie,char* prenume, int anul_nasterii,char gen,string categorie,int primul_an_in_care_a_participat_la_concursuri,int nr_ani,int nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs,int nr_competitii_in_fiecare_an, int** nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii,int numar_gustari_primite_la_final_de_antrenament):numar_legitimatie(numar_id++)
{
    this->prenume=new char[strlen(prenume)+1];
    strcpy(this->prenume,prenume);

    this->nume_de_familie=new char[strlen(nume_de_familie)+1];
    strcpy(this->nume_de_familie,nume_de_familie);

    this->anul_nasterii=anul_nasterii;
    this->gen=gen;
    this->cnp=cnp;
    this->categorie=categorie;
    this->primul_an_in_care_a_participat_la_concursuri=primul_an_in_care_a_participat_la_concursuri;
    this->nr_ani=nr_ani;
    this->nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs=nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs;
    this->nr_competitii_in_fiecare_an=nr_competitii_in_fiecare_an;
    this->numar_gustari_primite_la_final_de_antrenament=numar_gustari_primite_la_final_de_antrenament;

    this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii=new int*[nr_ani];
    for(int i=0; i<nr_ani; i++)
        this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i]=new int[nr_competitii_in_fiecare_an*nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs];

    for (int i=0; i<nr_ani; i++)
        for(int j=0; j<(nr_competitii_in_fiecare_an*nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs); j++)
            this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j]=nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j];
}
Sportiv::Sportiv(string cnp,char* nume_de_familie, char* prenume,char gen, int anul_nasterii, string categorie):numar_legitimatie(numar_id++)
{
    this->nume_de_familie=new char[strlen(nume_de_familie)+1];
    strcpy(this->nume_de_familie,nume_de_familie);

    this->prenume=new char[strlen(prenume)+1];
    strcpy(this->prenume,prenume);

    this->anul_nasterii=anul_nasterii;
    this->categorie=categorie;

    this->gen=gen;
    this->cnp=cnp;
    primul_an_in_care_a_participat_la_concursuri=0;
    nr_ani=0;
    nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs=0;
    nr_competitii_in_fiecare_an=0;
    nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii=NULL;
    numar_gustari_primite_la_final_de_antrenament=0;

}
Sportiv::Sportiv(const Sportiv& sporti):numar_legitimatie(sporti.numar_legitimatie)
{
    this->prenume=new char[strlen(sporti.prenume)+1];
    strcpy(this->prenume,sporti.prenume);

    this->nume_de_familie=new char[strlen(sporti.nume_de_familie)+1];
    strcpy(this->nume_de_familie,sporti.nume_de_familie);
    this->cnp=sporti.cnp;
    this->anul_nasterii=sporti.anul_nasterii;
    this->gen=sporti.gen;
    this->categorie=sporti.categorie;
    this->primul_an_in_care_a_participat_la_concursuri=sporti.primul_an_in_care_a_participat_la_concursuri;
    this->nr_ani=sporti.nr_ani;
    this->nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs=sporti.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs;
    this->nr_competitii_in_fiecare_an=sporti.nr_competitii_in_fiecare_an;

    this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii=new int*[sporti.nr_ani];
    for(int i=0; i<sporti.nr_ani; i++)
        this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i]=new int[sporti.nr_competitii_in_fiecare_an*sporti.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs];

    for (int i=0; i<sporti.nr_ani; i++)
        for(int j=0; j<sporti.nr_competitii_in_fiecare_an*sporti.nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs; j++)
            this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j]=sporti.nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i][j];

    this->numar_gustari_primite_la_final_de_antrenament=sporti.numar_gustari_primite_la_final_de_antrenament;

}

Sportiv::~Sportiv()
{
    if(this->prenume!=NULL)
        delete [] this->prenume;

    if(this->nume_de_familie!=NULL)
        delete [] this->nume_de_familie;

    if(this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii !=NULL)
    {
        for(int i=0; i<this->nr_ani; i++)
            delete [] this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii[i];
        delete [] this->nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii;
    }

}
class SportivLot:public Sportiv
{
private:
    float* indemnizatia_pe_luna;//indemnizatia se primeste cat timp esti in lot (vector de lungimea 12*nr_ani_in_lot)
    int nr_ani_in_lot;//in lot se fac in fiecare an verificari si in functie de rezultat mai ramai sau nu in lot
    int* ani;//se precizeaza anii in care a fost in lot
public:
    SportivLot();//constructor fara parametrii
    SportivLot(string cnp,char* nume_de_familie,char* prenume, int anul_nasterii,char gen, string categorie,int primul_an_in_care_a_participat_la_concursuri,int nr_ani,int nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs,int nr_competitii_in_fiecare_an, int** nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii,int numar_gustari_primite_la_final_de_antrenament,float* indemnizatia_pe_luna,int nr_ani_in_lot,int* ani);//constructor cu toti parametrii
    SportivLot(const SportivLot& sp_lot);//copy constructor
    SportivLot &operator=(const SportivLot& sp_lot);//supraincarcarea operatorului =
    ~SportivLot();//destructor
    friend istream& operator>>(istream& in, SportivLot& sporti_lot);//operator de citire
    friend ostream& operator<<(ostream& out, const SportivLot& sporti_lot);//operator de afisare
    void setIndemnizatiaPeLuna(float* indemnizatia_pe_luna,int nr_ani_in_lot);//setter pentru a putea modifica numarul de ani in lot si a pune mai multe date
    float* getIndemnizatiaPeLuna();//getter

    int getAniInLot();//getter pentru a vedea numarul anilor

    void setAni(int* ani,int nr_ani_in_lot);//daca modifici indemnizatia pe luna trebuie sa modifici si aici cu acelasi numar de ani
    int* getAni();

    const SportivLot& operator--();//pentru numarul de gustari
    const SportivLot operator--(int);//pentru numarul de gustari
    int operator+(const SportivLot &a);//pentru numarul de gustari
    bool operator >(const SportivLot& a);//pentru primul an competitional
    bool operator ==(const SportivLot& a);//pentru a vedea daca am acelasi cnp

    void indemnizatie_primita_pe_fiecare_an();//calculeaza suma primita de sportiv in fiecare an cand era in lot si suma totala

};
void SportivLot::indemnizatie_primita_pe_fiecare_an()
{
    int lungime=0,lmax=12,k=0;//lungime este pentru a vedea daca am ajuns la 12 luni, lmax reprezinta numarul de luni pe care il are un an, cu "suma" calculez sumele de bani per an, k este indice pentru vectorul cu sume_pe_an, iar s imi calculeaza suma totala
    float suma=0,s=0;
    float suma_pe_an[this->nr_ani_in_lot];//vector cu sume pe fiecare an in parte
    for(int i=0; i<(12*this->nr_ani_in_lot); i++)//mergem pe toate lunile
    {
        if(lungime<lmax-1)//daca nu am ajuns la ultima luna din an
        {
            suma=suma+this->indemnizatia_pe_luna[i];//fac suma
            lungime++;//cresc lungimea
        }
        else
        {
            if(lungime==lmax-1)//daca am ajuns la ultima luna din an
            {
                suma_pe_an[k]=suma+this->indemnizatia_pe_luna[i];//pun in vector suma dintre suma primita in primele 11 luni la care se adauga suma primita din ultima luna
                k++;//avansez la urmatoarea pozitie in vector
                suma=0;//suma o restabilesc
                lungime=0;//lungimea o restabilesc
            }
        }
    }
    for(int j=0; j<this->nr_ani_in_lot; j++)//parcurg vectorul cu sumele calculate per an
    {
        s=s+suma_pe_an[j];//fac totalul
        cout<<"\nIn anul: "<<this->ani[j]<<" "<<this->getNumeDeFamilieSportiv()<<" "<<this->getPrenumeSportiv()<<" a primit in total o suma in valoare de "<<suma_pe_an[j]<<" lei.\n";
    }
    cout<<"\nAstfel, suma de bani castigata de "<<this->getNumeDeFamilieSportiv()<<" "<<this->getPrenumeSportiv()<<" cat timp a fost in lot este de: "<<s<<" lei.\n";
}
bool SportivLot::operator ==(const SportivLot& a)//sportivii au cnp unic
{
    if(this->cnp==a.cnp )
        return true;
    return false;
}
bool SportivLot:: operator >(const SportivLot& a)//compar anii in care participa la primul concursuri
{
    if(this->primul_an_in_care_a_participat_la_concursuri>a.primul_an_in_care_a_participat_la_concursuri)
        return true;
    return false;
}

int SportivLot::operator+(const SportivLot &a)
{
    SportivLot aux(*this);
    aux.numar_gustari_primite_la_final_de_antrenament=aux.numar_gustari_primite_la_final_de_antrenament+a.numar_gustari_primite_la_final_de_antrenament;
    return aux.getNumarGustariPrimiteLaFinalDeAntrenament();
}

const SportivLot& SportivLot :: operator--()//predecrementare
{
    this->numar_gustari_primite_la_final_de_antrenament--;
    return *this;
}

const SportivLot SportivLot::operator--(int)//postdecrementare
{
    SportivLot aux (*this);
    this->numar_gustari_primite_la_final_de_antrenament--;
    return aux;
}
void SportivLot::setIndemnizatiaPeLuna(float* indemnizatia_pe_luna,int nr_ani_in_lot)
{
    this->nr_ani_in_lot=nr_ani_in_lot;
    if(this->indemnizatia_pe_luna!=NULL)
        delete [] this->indemnizatia_pe_luna;
    this->indemnizatia_pe_luna=new float[nr_ani_in_lot*12];
    for(int i=0; i<(nr_ani_in_lot*12); i++)
        this->indemnizatia_pe_luna[i]=indemnizatia_pe_luna[i];

}
float* SportivLot:: getIndemnizatiaPeLuna()
{
    return this->indemnizatia_pe_luna;
}
void SportivLot::setAni(int* ani,int nr_ani_in_lot)//numarul de ani o sa aiba aceeasi valoare ca cea data sus
{
    this->nr_ani_in_lot=nr_ani_in_lot;
    if(this->ani!=NULL)
        delete[]this->ani;
    this->ani=new int [nr_ani_in_lot];
    for(int i=0; i<nr_ani_in_lot; i++)
        this->ani[i]=ani[i];
}
int SportivLot::getAniInLot()
{
    return this->nr_ani_in_lot;
}
int*SportivLot:: getAni()
{
    return this->ani;
}
SportivLot::SportivLot():Sportiv()//constructor fara parametrii
{
    this->nr_ani_in_lot=0;
    this->indemnizatia_pe_luna=NULL;
    this->ani=NULL;

}
SportivLot::SportivLot(string cnp, char* nume_de_familie, char* prenume,int anul_nasterii,char gen,string categorie,
                       int primul_an_in_care_a_participat_la_concursuri,
                       int nr_ani,
                       int nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs,
                       int nr_competitii_in_fiecare_an,
                       int** nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii,
                       int numar_gustari_primite_la_final_de_antrenament,
                       float* indemnizatia_pe_luna,
                       int nr_ani_in_lot,
                       int* ani):Sportiv
    ( cnp,
      nume_de_familie,
      prenume,
      anul_nasterii,
      gen,
      categorie,
      primul_an_in_care_a_participat_la_concursuri,
      nr_ani,
      nr_max_de_probe_la_care_poate_participa_la_fiecare_concurs,
      nr_competitii_in_fiecare_an,
      nr_punctaj_obtinut_pe_parcursul_anilor_per_proba_per_competitii,
      numar_gustari_primite_la_final_de_antrenament)//constructor cu toti parametrii
{
    this->nr_ani_in_lot=nr_ani_in_lot;

    this-> indemnizatia_pe_luna=new float[nr_ani_in_lot*12];//aloc dinamic un vector
    for(int i=0; i<(nr_ani_in_lot*12); i++)
        this-> indemnizatia_pe_luna[i]=indemnizatia_pe_luna[i];

    this->ani=new int[nr_ani_in_lot];
    for(int i=0; i<nr_ani_in_lot; i++)
        this->ani[i]=ani[i];

}
SportivLot::SportivLot(const SportivLot& sp_lot):Sportiv(sp_lot)//copy constructor
{
    this->nr_ani_in_lot=sp_lot.nr_ani_in_lot;

    this-> indemnizatia_pe_luna=new float[sp_lot.nr_ani_in_lot*12];//aloc dinamic un vector
    for(int i=0; i<(sp_lot.nr_ani_in_lot*12); i++)
        this-> indemnizatia_pe_luna[i]=sp_lot.indemnizatia_pe_luna[i];

    this->ani=new int[sp_lot.nr_ani_in_lot];
    for(int i=0; i<sp_lot.nr_ani_in_lot; i++)
        this->ani[i]=sp_lot.ani[i];
}
SportivLot&SportivLot::operator =(const SportivLot& sp_lot)
{
    if(this!=&sp_lot)
    {
        Sportiv::operator=(sp_lot);

        if(this->indemnizatia_pe_luna!=NULL)
            delete[]this->indemnizatia_pe_luna;
        if(this->ani!=NULL)
            delete[]this->ani;

        this->nr_ani_in_lot=sp_lot.nr_ani_in_lot;
        this-> indemnizatia_pe_luna=new float[sp_lot.nr_ani_in_lot*12];//aloc dinamic un vector
        for(int i=0; i<(sp_lot.nr_ani_in_lot*12); i++)
            this-> indemnizatia_pe_luna[i]=sp_lot.indemnizatia_pe_luna[i];

        this->ani=new int[sp_lot.nr_ani_in_lot];
        for(int i=0; i<sp_lot.nr_ani_in_lot; i++)
            this->ani[i]=sp_lot.ani[i];

    }
    return *this;
}
istream& operator>>(istream& in, SportivLot& sporti_lot)
{
    in>>(Sportiv&) sporti_lot;
    cout<<"\nNumarul de ani in care a fost in lot: ";
    in>>sporti_lot.nr_ani_in_lot;

    cout<<"\nAnii in care a fost in lot:\n ";
    if(sporti_lot.ani!=NULL)
        delete [] sporti_lot.ani;
    sporti_lot.ani=new int[sporti_lot.nr_ani_in_lot];
    for(int i=0; i<sporti_lot.nr_ani_in_lot; i++)
        in>>sporti_lot.ani[i];

    cout<<"\nIndemnizatia primita per luna in fiecare an cand a fost in lot:\n ";
    if(sporti_lot.indemnizatia_pe_luna !=NULL)
        delete[] sporti_lot.indemnizatia_pe_luna;
    sporti_lot.indemnizatia_pe_luna=new float[sporti_lot.nr_ani_in_lot*12];
    for(int i=0; i<(sporti_lot.nr_ani_in_lot*12); i++)
        in>>sporti_lot.indemnizatia_pe_luna[i];

    return in;
}
ostream& operator<<(ostream& out, const SportivLot& sporti_lot)
{
    out<<(Sportiv&) sporti_lot;
    out<<"\nNumarul de ani in care a fost in lot: "<<sporti_lot.nr_ani_in_lot;
    out<<"\nAnii in care a fost in lot: ";
    for(int i=0; i<(sporti_lot.nr_ani_in_lot); i++)
        out<<sporti_lot.ani[i]<<"  ";
    out<<"\nIndemnizatia primita in fiecare luna pe parcursul anilor in care a fost in lot:\n";
    for(int i=0; i<(sporti_lot.nr_ani_in_lot*12); i++)
    {
        if(i==0 || i%12==0)
            out<<endl<<"In anul "<<sporti_lot.ani[i/12]<<": "<<sporti_lot.indemnizatia_pe_luna[i]<<"lei ";
        else
            out<<sporti_lot.indemnizatia_pe_luna[i]<<"lei ";
    }
    return out;
}
SportivLot::~SportivLot()
{
    if(this->indemnizatia_pe_luna!=NULL)
        delete[]this->indemnizatia_pe_luna;
    if(this->ani!=NULL)
        delete[]this->ani;
}
class Antrenor
{

protected:
    Sportiv* sportivi;
    SportivLot* sportivilot;//am facut un vector de tipul SportivLot si un vector de tipul Sportiv pentru ca vreau ca un antrenor sa poata avea ambele tipuri
    int numar_sportivi_actuali;
    int numar_sportivi_lot;
    string email;
    int varsta;
    int numar_grupe;
    bool este_acreditat;
    char initiala_sectie;
    char* nume;
    float salariu;
    int* numar_sportivi_alocati_pe_an;// cei care au ramas de la inceputul anului pana la sfarsitul anului respectiv
    int numar_ani;//pentru a vedea cati sportivi a avut alocati
    int numar_luni;//pentru a vedea cate cheltuieli am pe luna
    float* cheltuieli_cu_chiria_pe_luna;
    double ani_experienta;
    const int numar_maxim_de_grupe_alocate;
    char * prenume_antrenor;
    string* grupe_sportivi;// initiere,avansati,performanta
public:
    static string nume_club_sportiv;

    Antrenor();//constructor fara parametrii
    Antrenor(SportivLot* sportivilot,int numar_sportivi_lot,Sportiv* sportivi,int numar_sportivi_actuali,int varsta,string email,int numar_grupe,int numar_luni, bool este_acreditat,char initiala_sectie,char* nume,float salariu,int* numar_sportivi_alocati_pe_an,int numar_ani,float* cheltuieli_cu_chiria_pe_luna,double ani_experienta,char * prenume_antrenor, string* grupe_sportivi,int maxi);
    Antrenor(SportivLot* sportivilot,int numar_sportivi_lot,Sportiv* sportivi,int numar_sportivi_actuali,int varsta,char*nume,char * prenume_antrenor,string email,char initiala_sectie,int numar_ani,int numar_grupe, int* numar_sportivi_alocati_pe_an,string* grupe_sportivi,int maxi);
    virtual ~Antrenor();//destructor- este virtual ca atunci cand se apeleaza destructorul pentru clasa derivata mai intai sa dezaloce de acolo si dupa sa dezaloce din baza
    Antrenor(const Antrenor &instructor);//constructor de copiere
    Antrenor &operator=(const Antrenor & instructor);//forma supraincarcata a operatorului egal
    friend ostream& operator<<(ostream& out, const Antrenor& antr);//operator afisare
    friend istream& operator>>(istream& in, Antrenor& antr);//operator citire

    string getEmail();

    int getNumarSportiviActuali();
    int getNumarSportiviLot();

    void setVarsta(int varsta);
    int getVarsta();

    int getNumarGrupe();

    void setEsteAcreditat(bool este_acreditat);
    bool getEsteAcreditat();

    char getInitialaSectie();

    void setNume(char* nume);
    char* getNume();

    void setSalariu(float salariu);
    float getSalariu();

    void setNumarSportiviAlocatiPeAn(int* numar_sportivi_alocati_pe_an, int numar_ani);
    int* getNumarSportiviAlocatiPeAn();


    Sportiv* getSportivi();


    SportivLot* getSportiviLot();

    int getNumarAni();

    int getNumarLuni();

    void setCheltuieliCuChiriaPeluna(float* cheltuieli_cu_chiria_pe_luna, int numar_luni);
    float* getCheltuieliCuChiriaPeluna();

    void setAniExperianta(double ani_experienta);
    double getAniExperianta();

    int getNumarMaximDegrupeAlocate();

    void setPrenumeAntrenor(char* prenume_antrenor);
    char* getPrenumeAntrenor();

    void setGrupeSportivi(string* grupe_sportivi, int numar_grupe);
    string* getGrupeSportivi();

    const Antrenor& operator++(); //ani experienta
    const Antrenor operator++(int);//ani experienta
    float operator+(const Antrenor &a);//adun salariile
    float operator-(float x);//fac diferenta dintre salariu si un numar
    bool operator <(const Antrenor& a);//numar grupe
    bool operator ==(const Antrenor& a);//la email
    float operator [](int index);//cheltuieli_cu_chiria_pe_luna
    explicit operator int();//salariu
    friend Antrenor operator+(const Sportiv&sporti,const Antrenor&antre);//adun un sportiv cu un antrenor
    friend Antrenor operator+(Antrenor antre,const Sportiv&sporti);//adun un antrenor cu un sportiv
    Antrenor operator-(const Sportiv&sporti);//scad din antrenor sportivi

    friend Antrenor operator+(const SportivLot&sportivil,const Antrenor&antre);//adun un sportiv cu un antrenor
    friend Antrenor operator+(Antrenor antre,const SportivLot&sportivil);//adun un antrenor cu un sportiv
    Antrenor operator-(const SportivLot&sportivil);//scad din antrenor sportivi

    void eficienta_antrenor();//calculeaza cresterea procentuala a numarului de sportivi pe care ii are pe un numar de ani (un antrenor trebuie sa aiba cel putin 1 sportiv alocat pe an)

};
void Antrenor::eficienta_antrenor()
{

    float s[this->numar_ani-1];//pentru ca se compara cate doi=> dimensiunea o sa fie cu 1 in minus
    int v1,v2,ok;

    v1=this->numar_sportivi_alocati_pe_an[0];//nuamrul de sportivi din primul an

    if(numar_ani==1)
        cout<<"\nEste primul an de activitate al antrenorului " <<this->getNume()<<" "<<this->getPrenumeAntrenor()<<", deci nu ne putem pronunta in ceea ce priveste cresterea procentuala anuala a numarului de sportivi.";
    else
    {
        for (int i=1; i<this->numar_ani; i++)
        {
            v2=this->numar_sportivi_alocati_pe_an[i];
            s[i-1]=((v2-abs(v1))*100)/(abs(v1));//formula crestere procentuala
            v1=v2;
        }
        cout<<"\n\nCresterea procentuala anuala a numarului de sportivi ai antrenorului "<<this->getNume()<<" "<<this->getPrenumeAntrenor()<<" este de: ";
        for(int i=0; i<this->numar_ani-1; i++)
            cout<<s[i]<<"% ";
        //}
        ok=0;
        for(int i=0; i<this->numar_ani-1; i++)
        {
            if(s[i]<0)//daca o valoarea este negativa inseamna ca a avut loc o scadere a numarului de sportivi
                ok=1;
        }
        if(ok==1)
            cout<<"\nDe la antrenorul "<<this->getNume()<<" "<<this->getPrenumeAntrenor()<<" au plecat sportivi de-a lungul anilor";
        else
            cout<<"\nAntrenorul "<<this->getNume()<<" "<<this->getPrenumeAntrenor()<<" este eficient si vin din ce in ce mai multi sportivi la el";
    }
}
Antrenor operator+(Antrenor antre,const Sportiv&sporti)
{
    Sportiv* lsportivi;
    lsportivi= new Sportiv[antre.numar_sportivi_actuali];
    for(int i=0; i<antre.numar_sportivi_actuali; i++)
        lsportivi[i]=antre.sportivi[i];
    if(antre.sportivi!=NULL)
        delete[]antre.sportivi;

    antre.numar_sportivi_actuali++;
    antre.sportivi=new Sportiv[antre.numar_sportivi_actuali];
    for(int i=0; i<antre.numar_sportivi_actuali-1; i++)
        antre.sportivi[i]=lsportivi[i];
    antre.sportivi[antre.numar_sportivi_actuali-1]=sporti;
    return antre;
}
Antrenor operator+(const Sportiv&sporti,const Antrenor&antre)
{
    Antrenor auxiliar(antre);
    Sportiv* lsportivi;
    lsportivi= new Sportiv[auxiliar.numar_sportivi_actuali];
    for(int i=0; i<auxiliar.numar_sportivi_actuali; i++)
        lsportivi[i]=auxiliar.sportivi[i];
    if(auxiliar.sportivi!=NULL)
        delete[]auxiliar.sportivi;

    auxiliar.numar_sportivi_actuali++;
    auxiliar.sportivi=new Sportiv[auxiliar.numar_sportivi_actuali];
    for(int i=0; i<auxiliar.numar_sportivi_actuali-1; i++)
        auxiliar.sportivi[i]=lsportivi[i];
    auxiliar.sportivi[auxiliar.numar_sportivi_actuali-1]=sporti;
    return auxiliar;
}

Antrenor Antrenor:: operator-(const Sportiv&sporti)
{

    int poz=0;
    Sportiv* listasportivi;
    listasportivi=new Sportiv[this->numar_sportivi_actuali];
    for(int i=0; i<this->numar_sportivi_actuali; i++)
    {

        listasportivi[i]=this->sportivi[i];
        if(this->sportivi[i]==sporti)
            poz++;//poz o sa fie mereu 1 pentru ca doi sportivi sunt egali doar daca au acelasi cnp care este unic
    }
    if(this->sportivi!=NULL)
        delete[] this->sportivi;

    int j=0;
    this->sportivi=new Sportiv[this->numar_sportivi_actuali-poz];
    int i=0;
    while(i<this->numar_sportivi_actuali)
    {
        if(listasportivi[i]==sporti)
            i++;
        else
        {
            this->sportivi[j]=listasportivi[i];
            j++;
            i++;

        }

    }
    this->numar_sportivi_actuali=this->numar_sportivi_actuali-poz;
    return *this;


}
Antrenor operator+(Antrenor antre,const SportivLot&sportivil)
{
    SportivLot* lsportivi;
    lsportivi= new SportivLot[antre.numar_sportivi_lot];
    for(int i=0; i<antre.numar_sportivi_lot; i++)
        lsportivi[i]=antre.sportivilot[i];
    if(antre.sportivilot!=NULL)
        delete[]antre.sportivilot;

    antre.numar_sportivi_lot++;
    antre.sportivilot=new SportivLot[antre.numar_sportivi_lot];
    for(int i=0; i<antre.numar_sportivi_lot-1; i++)
        antre.sportivilot[i]=lsportivi[i];
    antre.sportivilot[antre.numar_sportivi_lot-1]=sportivil;
    return antre;
}
Antrenor operator+(const SportivLot&sportivil,const Antrenor&antre)
{
    Antrenor auxiliar(antre);
    SportivLot* lsportivi;
    lsportivi= new SportivLot[auxiliar.numar_sportivi_lot];
    for(int i=0; i<auxiliar.numar_sportivi_lot; i++)
        lsportivi[i]=auxiliar.sportivilot[i];
    if(auxiliar.sportivilot!=NULL)
        delete[]auxiliar.sportivilot;

    auxiliar.numar_sportivi_lot++;
    auxiliar.sportivilot=new SportivLot[auxiliar.numar_sportivi_lot];
    for(int i=0; i<auxiliar.numar_sportivi_lot-1; i++)
        auxiliar.sportivilot[i]=lsportivi[i];
    auxiliar.sportivilot[auxiliar.numar_sportivi_lot-1]=sportivil;
    return auxiliar;
}

Antrenor Antrenor:: operator-(const SportivLot&sportivil)
{

    int poz=0;
    SportivLot* listasportivi;
    listasportivi=new SportivLot[this->numar_sportivi_lot];
    for(int i=0; i<this->numar_sportivi_lot; i++)
    {

        listasportivi[i]=this->sportivilot[i];
        if(this->sportivilot[i]==sportivil)
            poz++;//poz o sa fie mereu 1 pentru ca doi sportivi sunt egali doar daca au acelasi cnp care este unic
    }
    if(this->sportivilot!=NULL)
        delete[] this->sportivilot;

    int j=0;
    this->sportivilot=new SportivLot[this->numar_sportivi_lot-poz];
    int i=0;
    while(i<this->numar_sportivi_lot)
    {
        if(listasportivi[i]==sportivil)
            i++;
        else
        {
            this->sportivilot[j]=listasportivi[i];
            j++;
            i++;

        }

    }
    this->numar_sportivi_lot=this->numar_sportivi_lot-poz;
    return *this;


}
Antrenor::operator int()
{
    return (int)this->salariu;
}
float Antrenor:: operator [](int index)
{
    if(0<=index && index< this->numar_luni)
        return cheltuieli_cu_chiria_pe_luna[index];
    else
        return -23;//daca nu e introdus indicele corect afisez aceasta valoare
}

bool Antrenor::operator ==(const Antrenor& a)
{
    if(this->email==a.email)//email-ul mereu o sa fie disitinct de la o persoana la alta
        return true;
    return false;
}
bool Antrenor:: operator <(const Antrenor& a)
{
    if(this->numar_grupe<a.numar_grupe)
        return true;
    return false;
}

float Antrenor::operator+(const Antrenor &a) //adun salariile
{
    Antrenor aux(*this);
    aux.salariu=aux.salariu+a.salariu;
    return aux.getSalariu();
}

float Antrenor:: operator-(float x) //fac diferenta dintre salariu si un numar
{
    Antrenor aux(*this);
    aux.salariu=aux.salariu-x;
    return aux.getSalariu();
}

const Antrenor& Antrenor::operator++()
{
    this->ani_experienta++;
    return *this;
}
const Antrenor Antrenor::operator++(int)
{
    Antrenor aux(*this);
    this->ani_experienta++;
    return aux;
}
string Antrenor::nume_club_sportiv="Rechinul Cel Viteaz Bucuresti";


int Antrenor::getNumarSportiviActuali()
{
    return this->numar_sportivi_actuali;
}
int Antrenor::getNumarSportiviLot()
{
    return this->numar_sportivi_lot;
}
string Antrenor::getEmail()
{
    return this->email;
}
void Antrenor::setVarsta(int varsta)
{
    this->varsta=varsta;
}
int Antrenor::getVarsta()
{
    return this->varsta;
}

int Antrenor::getNumarGrupe()
{
    return this->numar_grupe;
}
void Antrenor::setEsteAcreditat(bool este_acreditat)
{
    this->este_acreditat=este_acreditat;
}
bool Antrenor::getEsteAcreditat()
{
    return this->este_acreditat;
}

char Antrenor::getInitialaSectie()
{
    return this->initiala_sectie;
}

void Antrenor::setNume(char* nume)
{
    if(this->nume!=NULL)
        delete [] this-> nume;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}
char* Antrenor::getNume()
{
    return this->nume;
}

void Antrenor::setSalariu(float salariu)
{
    this->salariu=salariu;
}
float Antrenor::getSalariu()
{
    return this->salariu;
}

void Antrenor::setNumarSportiviAlocatiPeAn(int* numar_sportivi_alocati_pe_an,int numar_ani)
{
    this->numar_ani=numar_ani;
    if(this->numar_sportivi_alocati_pe_an!=NULL)
        delete [] this->numar_sportivi_alocati_pe_an;
    this->numar_sportivi_alocati_pe_an=new int[numar_ani];
    for (int i=0; i<numar_ani; i++)
        this->numar_sportivi_alocati_pe_an[i]=numar_sportivi_alocati_pe_an[i];
}
int* Antrenor::getNumarSportiviAlocatiPeAn()
{
    return this->numar_sportivi_alocati_pe_an;
}


Sportiv* Antrenor:: getSportivi()
{
    return this->sportivi;
}

SportivLot* Antrenor:: getSportiviLot()
{
    return this->sportivilot;
}
int Antrenor::getNumarAni()
{
    return this->numar_ani;
}

int Antrenor::getNumarLuni()
{
    return this->numar_luni;
}

void Antrenor::setCheltuieliCuChiriaPeluna(float* cheltuieli_cu_chiria_pe_luna, int numar_luni)
{
    this->numar_luni=numar_luni;
    if(this->cheltuieli_cu_chiria_pe_luna!=NULL)
        delete [] this->cheltuieli_cu_chiria_pe_luna;
    this->cheltuieli_cu_chiria_pe_luna=new float[numar_luni];
    for (int i=0; i<numar_luni; i++)
        this->cheltuieli_cu_chiria_pe_luna[i]=cheltuieli_cu_chiria_pe_luna[i];
}

float* Antrenor::getCheltuieliCuChiriaPeluna()
{
    return this->cheltuieli_cu_chiria_pe_luna;
}

void Antrenor::setAniExperianta(double ani_experienta)
{
    this->ani_experienta=ani_experienta;
}
double Antrenor::getAniExperianta()
{
    return this->ani_experienta;
}

int Antrenor::getNumarMaximDegrupeAlocate()
{
    return this->numar_maxim_de_grupe_alocate;
}

void Antrenor::setPrenumeAntrenor(char* prenume_antrenor)
{
    if(this->prenume_antrenor!=NULL)
        delete [] this-> prenume_antrenor;
    this->prenume_antrenor=new char[strlen(prenume_antrenor)+1];
    strcpy(this->prenume_antrenor,prenume_antrenor);
}
char* Antrenor::getPrenumeAntrenor()
{
    return this->prenume_antrenor;
}

void Antrenor::setGrupeSportivi(string* grupe_sportivi, int numar_grupe)
{
    this->numar_grupe=numar_grupe;
    if(this->grupe_sportivi!=NULL)
        delete [] this->grupe_sportivi;
    this->grupe_sportivi=new string[numar_grupe];
    for(int i=0; i<numar_grupe; i++)
        this->grupe_sportivi[i]=grupe_sportivi[i];
}
string* Antrenor::getGrupeSportivi()
{
    return this->grupe_sportivi;
}
istream& operator>>(istream& in, Antrenor& antr)
{
    in.get();//daca e citit primul nu ia la afisare prima litera
    cout<<"\nNume Antrenor: ";
    char nume_auxiliar[100];
    in.getline(nume_auxiliar,100);

    if(antr.nume!=NULL)
        delete[] antr.nume;
    antr.nume=new char[strlen(nume_auxiliar)+1];
    strcpy(antr.nume,nume_auxiliar);

    cout<<"\nPrenume Antrenor: ";

    char nume_auxiliar1[100];
    in.getline(nume_auxiliar1,100);

    if(antr.prenume_antrenor!=NULL)
        delete[] antr.prenume_antrenor;
    antr.prenume_antrenor=new char[strlen(nume_auxiliar1)+1];
    strcpy(antr.prenume_antrenor,nume_auxiliar1);

    cout<<"\nEmail Antrenor: ";
    in>>antr.email;

    cout<<"\nVarsta: ";
    in>>antr.varsta;

    cout<<"\nInitiala sectiei (A-atletism/C-ciclism/D-dans/I-inot/T-triathlon): ";
    in>>antr.initiala_sectie;

    cout<<"\nAntrenorul este acreditat? (1-true/0-false): ";
    in>>antr.este_acreditat;

    cout<<"\nCati ani de experienta are?: ";
    in>>antr.ani_experienta;

    cout<<"\nSalariu: ";
    in>>antr.salariu;

    cout<<"\nNumarul de luni pentru care doresc sa vad cat a costat chiria: ";
    in>>antr.numar_luni;

    if(antr.cheltuieli_cu_chiria_pe_luna!=NULL)
        delete[] antr.cheltuieli_cu_chiria_pe_luna;
    antr.cheltuieli_cu_chiria_pe_luna=new float [antr.numar_luni];
    cout<<"\nSume platite pe chirie: ";
    for(int i=0; i<antr.numar_luni; i++)
        in>>antr.cheltuieli_cu_chiria_pe_luna[i];

    cout<<"\nNumarul de grupe pregatite este in numar de [acest numar trebuie sa fie mai mic sau egal cu 10] : ";
    in>>antr.numar_grupe;

    if(antr.grupe_sportivi!=NULL)
        delete[] antr.grupe_sportivi;
    antr.grupe_sportivi=new string[antr.numar_grupe];
    cout<<"\nTipuri de grupe (initiere,avansati,performanta,etc): ";
    for(int i=0; i<antr.numar_grupe; i++)
        in>>antr.grupe_sportivi[i];

    cout<<"\nNumarul de ani pentru care doresc sa vad cati sportivi a avut acest antrenor: ";
    in>>antr.numar_ani;

    if(antr.numar_sportivi_alocati_pe_an!=NULL)
        delete[] antr.numar_sportivi_alocati_pe_an;
    antr.numar_sportivi_alocati_pe_an=new int[antr.numar_ani];
    cout<<"\nNumarul de sportivi din ultimii ani mentionati mai sus: ";
    for(int i=0; i<antr.numar_ani; i++)
        in>>antr.numar_sportivi_alocati_pe_an[i];

    return in;

}

ostream& operator<<(ostream& out, const Antrenor& antr)
{
    out<<"\nNume antrenor: "<<antr.nume;
    out<<"\nPrenume antrenor: "<<antr.prenume_antrenor;
    out<<"\nClubul la care este angajat: "<<antr.nume_club_sportiv;
    out<<"\nEmail antrenor: "<<antr.email;
    out<<"\nVarsta: "<<antr.varsta;

    if (antr.initiala_sectie=='D')
    {
        out<<"\nSectia in care profeseaza este Dans";
    }
    else if (antr.initiala_sectie=='I')
    {
        out<<"\nSectia in care profeseaza este Inot";
    }
    else if (antr.initiala_sectie=='T')
    {
        out<<"\nSectia in care profeseaza este Triathlon";
    }
    else if (antr.initiala_sectie=='A')
    {
        out<<"\nSectia in care profeseaza este Atletism";
    }
    else if (antr.initiala_sectie=='C')
    {
        out<<"\nSectia in care profeseaza este Ciclism";
    }
    else
    {
        out<<"\nInitiala sectiei in care profeseaza este: "<<antr.initiala_sectie;
    }
    if (antr.este_acreditat==0)
        out<<"\nAntrenorul nu este acreditat";
    else
        out<<"\nAntrenorul este acreditat";
    if(antr.ani_experienta==0)
        out<<"\nEste un antrenor la inceput de cariera care nu a mai profesat pana acum";
    if (antr.ani_experienta==1)
        out<<"\nEste un antrenor la inceput de cariera, avand "<<antr.ani_experienta<<" an de experienta";
    if (antr.ani_experienta<4 && antr.ani_experienta>1)
        out<<"\nEste un antrenor la inceput de cariera, avand "<<antr.ani_experienta<<" ani de experienta";
    if (antr.ani_experienta>=4 && antr.ani_experienta<=6)
        out<<"\nEste un antrenor aflat in procesul de perfectionare, avand "<<antr.ani_experienta<<" ani de experienta";
    if (antr.ani_experienta>6)
        out<<"\nEste un antrenor experimentat, avand "<<antr.ani_experienta<<" ani de experienta";

    if(antr.salariu!=0)
        out<<"\nSalariu primit: "<<antr.salariu<<" lei";

    if(antr.numar_luni!=0)
    {
        out<<"\nPlata chiriei pe "<<antr.numar_luni;
        if (antr.numar_luni==1)
            out<<" luna: ";
        else
            out<<" luni: ";
        for(int i=0; i<antr.numar_luni; i++)
            out<<antr.cheltuieli_cu_chiria_pe_luna[i]<<" lei ";
    }

    out<<"\nDistributia sportivilor antrenati pe "<<antr.numar_ani;
    if(antr.numar_ani==1)
        out<<" an: ";
    else
        out<<" ani: ";
    for(int i=0; i<antr.numar_ani; i++)
        out<<antr.numar_sportivi_alocati_pe_an[i]<<" sportivi ";

    //out<<"\nNumarul maxim de grupe pe care le-ar putea antrena este de: "<<antr.numar_maxim_de_grupe_alocate;
    out<<"\nNumarul de grupe pe care le pregateste: "<<antr.numar_grupe;

    out<<"\nTipuri de grupe pe care le antreneaza: ";
    for(int i=0; i<antr.numar_grupe; i++)
        out<<antr.grupe_sportivi[i]<<" ";

    out<<"\nNumarul actual de sportivi ai acestui antrenor care nu sunt in lot este de: "<<antr.numar_sportivi_actuali;
    if(antr.numar_sportivi_actuali!=0)
    {
        out<<"\n\nSportivii actuali care nu sunt in lot ai acestui antrenor sunt:\n\n";
        for(int i=0; i<antr.numar_sportivi_actuali; i++)
            out<<"Nume de familie: "<<antr.sportivi[i].getNumeDeFamilieSportiv()<<"   Prenume: "<<antr.sportivi[i].getPrenumeSportiv()<<"   Anul nasterii: "<<antr.sportivi[i].getAnulNasterii()<<" "<<"\n";
    }
    out<<"\nNumarul actual de sportivi ai acestui antrenor care sunt in lot este de: "<<antr.numar_sportivi_lot;
    if(antr.numar_sportivi_lot!=0)
    {
        out<<"\n\nSportivii din lot actuali ai acestui antrenor sunt:\n\n";
        for(int i=0; i<antr.numar_sportivi_lot; i++)
            out<<"Nume de familie: "<<antr.sportivilot[i].getNumeDeFamilieSportiv()<<"   Prenume: "<<antr.sportivilot[i].getPrenumeSportiv()<<"   Anul nasterii: "<<antr.sportivilot[i].getAnulNasterii()<<" "<<"\n";
    }
    return out;
}

Antrenor::Antrenor():numar_maxim_de_grupe_alocate(10) //fixez 10 pentru ca asa este in constructia clubului//E FARA CONST SI STATIC IN INTERIOR
{
    email="necunoscut";
    varsta=0;
    numar_grupe=0;
    este_acreditat=false;
    numar_sportivi_actuali=0;
    sportivi=NULL;
    numar_sportivi_lot=0;
    sportivilot=NULL;

    initiala_sectie='0';

    nume= new char[strlen("necunoscut")+1];
    strcpy(nume,"necunoscut");

    prenume_antrenor= new char[strlen("necunoscut")+1];
    strcpy(prenume_antrenor,"necunoscut");

    salariu=0;
    numar_sportivi_alocati_pe_an=NULL;
    numar_ani=0;
    numar_luni=0;
    cheltuieli_cu_chiria_pe_luna=NULL;
    ani_experienta=-1;

    grupe_sportivi=NULL;

}

Antrenor::Antrenor(SportivLot* sportivilot,int numar_sportivi_lot,Sportiv* sportivi,int numar_sportivi_actuali, int varsta,string email,int numar_grupe,int numar_luni,bool este_acreditat,char initiala_sectie,char* nume,float salariu,int* numar_sportivi_alocati_pe_an,int numar_ani,float* cheltuieli_cu_chiria_pe_luna,double ani_experienta,char * prenume_antrenor, string* grupe_sportivi,int maxi):numar_maxim_de_grupe_alocate(maxi)
{
    this->email=email;
    this->varsta=varsta;
    this->numar_grupe=numar_grupe;
    this->numar_luni=numar_luni;
    this->este_acreditat=este_acreditat;
    this->initiala_sectie=initiala_sectie;
    this->numar_sportivi_actuali=numar_sportivi_actuali;
    this->numar_sportivi_lot=numar_sportivi_lot;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);

    this->prenume_antrenor=new char[strlen(prenume_antrenor)+1];
    strcpy(this->prenume_antrenor,prenume_antrenor);

    this->salariu=salariu;

    this-> numar_sportivi_alocati_pe_an=new int[numar_ani];//aloc dinamic un vector
    for(int i=0; i<numar_ani; i++)
        this-> numar_sportivi_alocati_pe_an[i]=numar_sportivi_alocati_pe_an[i];

    this->sportivi=new Sportiv[numar_sportivi_actuali];
    for(int i=0; i<numar_sportivi_actuali; i++)
        this->sportivi[i]=sportivi[i];

    this->sportivilot=new SportivLot[numar_sportivi_lot];
    for(int i=0; i<numar_sportivi_lot; i++)
        this->sportivilot[i]=sportivilot[i];

    this->numar_ani=numar_ani;

    this-> cheltuieli_cu_chiria_pe_luna=new float[numar_luni];
    for (int i=0; i<numar_luni; i++)
        this-> cheltuieli_cu_chiria_pe_luna[i]=cheltuieli_cu_chiria_pe_luna[i];

    this->ani_experienta=ani_experienta;

    this->grupe_sportivi=new string[numar_grupe];
    for (int i=0; i<numar_grupe; i++)
        this-> grupe_sportivi[i]=grupe_sportivi[i];


}

Antrenor::Antrenor(SportivLot* sportivilot,int numar_sportivi_lot,Sportiv* sportivi,int numar_sportivi_actuali,int varsta,char*nume,char * prenume_antrenor,string email,char initiala_sectie,int numar_ani,int numar_grupe, int* numar_sportivi_alocati_pe_an, string* grupe_sportivi,int maxi):numar_maxim_de_grupe_alocate(maxi)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);

    this->prenume_antrenor=new char[strlen(prenume_antrenor)+1];
    strcpy(this->prenume_antrenor,prenume_antrenor);

    this->varsta=varsta;
    this-> numar_sportivi_alocati_pe_an = new int[numar_ani];
    for(int i=0; i<numar_ani; i++)
        this->numar_sportivi_alocati_pe_an[i]=numar_sportivi_alocati_pe_an[i];

    this->sportivi=new Sportiv[numar_sportivi_actuali];
    for(int i=0; i<numar_sportivi_actuali; i++)
        this->sportivi[i]=sportivi[i];

    this->sportivilot=new SportivLot[numar_sportivi_lot];
    for(int i=0; i<numar_sportivi_lot; i++)
        this->sportivilot[i]=sportivilot[i];

    this-> grupe_sportivi= new string[numar_grupe];
    for(int i=0; i<numar_grupe; i++)
        this->grupe_sportivi[i]= grupe_sportivi[i];
    this->numar_sportivi_actuali=numar_sportivi_actuali;
    this->numar_sportivi_lot=numar_sportivi_lot;
    this->email=email;
    this->initiala_sectie=initiala_sectie;
    this->numar_ani=numar_ani;
    this->numar_grupe=numar_grupe;

    este_acreditat=false;
    salariu=0;
    numar_luni=0;
    cheltuieli_cu_chiria_pe_luna=NULL;
    ani_experienta=-1;


}

Antrenor::Antrenor(const Antrenor &instructor):numar_maxim_de_grupe_alocate(instructor.numar_maxim_de_grupe_alocate)
{
    //copy constructor
    this->nume=new char[strlen(instructor.nume)+1];
    strcpy(this->nume,instructor.nume);

    this->prenume_antrenor=new char[strlen(instructor.prenume_antrenor)+1];
    strcpy(this->prenume_antrenor,instructor.prenume_antrenor);

    this->numar_sportivi_alocati_pe_an=new int[instructor.numar_ani];//aloc dinamic un vector
    for(int i=0; i<instructor.numar_ani; i++)
        this-> numar_sportivi_alocati_pe_an[i]=instructor.numar_sportivi_alocati_pe_an[i];

    this-> cheltuieli_cu_chiria_pe_luna=new float[instructor.numar_luni];
    for (int i=0; i<instructor.numar_luni; i++)
        this-> cheltuieli_cu_chiria_pe_luna[i]=instructor.cheltuieli_cu_chiria_pe_luna[i];

    this->grupe_sportivi=new string[instructor.numar_grupe];
    for (int i=0; i<instructor.numar_grupe; i++)
        this-> grupe_sportivi[i]=instructor.grupe_sportivi[i];

    this->sportivilot =new SportivLot[instructor.numar_sportivi_lot];
    for(int i=0; i<instructor.numar_sportivi_lot; i++)
        this->sportivilot[i]=instructor.sportivilot[i];

    this->numar_sportivi_lot=instructor.numar_sportivi_lot;

    this->sportivi=new Sportiv[instructor.numar_sportivi_actuali];
    for(int i=0; i<instructor.numar_sportivi_actuali; i++)
        this->sportivi[i]=instructor.sportivi[i];

    this->numar_sportivi_actuali=instructor.numar_sportivi_actuali;
    this->email=instructor.email;
    this->varsta=instructor.varsta;
    this->numar_grupe=instructor.numar_grupe;
    this->numar_luni=instructor.numar_luni;
    this->este_acreditat=instructor.este_acreditat;
    this->initiala_sectie=instructor.initiala_sectie;
    this->salariu=instructor.salariu;
    this->ani_experienta=instructor.ani_experienta;
    this->numar_ani=instructor.numar_ani;

}

Antrenor::~Antrenor()//tb sa dezaloc ce e alocat dinamic
{
    if(this->nume!=NULL)
        delete [] this->nume;
    if(this->prenume_antrenor!=NULL)
        delete [] this->prenume_antrenor;
    if(this ->numar_sportivi_alocati_pe_an!=NULL)
        delete [] this->numar_sportivi_alocati_pe_an;
    if(this->cheltuieli_cu_chiria_pe_luna!=NULL)
        delete [] this->cheltuieli_cu_chiria_pe_luna;
    if(this ->grupe_sportivi !=NULL)
        delete [] this-> grupe_sportivi;
    if(this-> sportivi !=NULL)
        delete [] this->sportivi;
    if(this-> sportivilot !=NULL)
        delete [] this->sportivilot;
}
Antrenor& Antrenor::operator=(const Antrenor& instructor)
{
    if(this!=&instructor)
    {
        if(this->nume!=NULL)
            delete [] this->nume;
        if(this->prenume_antrenor!=NULL)
            delete [] this->prenume_antrenor;
        if(this ->numar_sportivi_alocati_pe_an!=NULL)
            delete [] this->numar_sportivi_alocati_pe_an;
        if(this->cheltuieli_cu_chiria_pe_luna!=NULL)
            delete [] this->cheltuieli_cu_chiria_pe_luna;
        if(this ->grupe_sportivi !=NULL)
            delete [] this-> grupe_sportivi;
        if(this-> sportivi !=NULL)
            delete [] this->sportivi;
        if(this-> sportivilot !=NULL)
            delete [] this->sportivilot;

        this->nume=new char[strlen(instructor.nume)+1];
        strcpy(this->nume,instructor.nume);

        this->prenume_antrenor=new char[strlen(instructor.prenume_antrenor)+1];
        strcpy(this->prenume_antrenor,instructor.prenume_antrenor);

        this->numar_sportivi_alocati_pe_an=new int[instructor.numar_ani];//aloc dinamic un vector
        for(int i=0; i<instructor.numar_ani; i++)
            this-> numar_sportivi_alocati_pe_an[i]=instructor.numar_sportivi_alocati_pe_an[i];

        this-> cheltuieli_cu_chiria_pe_luna=new float[instructor.numar_luni];
        for (int i=0; i<instructor.numar_luni; i++)
            this-> cheltuieli_cu_chiria_pe_luna[i]=instructor.cheltuieli_cu_chiria_pe_luna[i];

        this->grupe_sportivi=new string[instructor.numar_grupe];
        for (int i=0; i<instructor.numar_grupe; i++)
            this-> grupe_sportivi[i]=instructor.grupe_sportivi[i];

        this->sportivi=new Sportiv[instructor.numar_sportivi_actuali];
        for(int i=0; i<instructor.numar_sportivi_actuali; i++)
            this->sportivi[i]=instructor.sportivi[i];

        this->sportivilot =new SportivLot[instructor.numar_sportivi_lot];
        for(int i=0; i<instructor.numar_sportivi_lot; i++)
            this->sportivilot[i]=instructor.sportivilot[i];

        this->numar_sportivi_lot=instructor.numar_sportivi_lot;

        this->numar_sportivi_actuali=instructor.numar_sportivi_actuali;
        this->email=instructor.email;
        this->varsta=instructor.varsta;
        this->numar_grupe=instructor.numar_grupe;
        this->numar_luni=instructor.numar_luni;
        this->este_acreditat=instructor.este_acreditat;
        this->initiala_sectie=instructor.initiala_sectie;
        this->salariu=instructor.salariu;
        this->ani_experienta=instructor.ani_experienta;
        this->numar_ani=instructor.numar_ani;

    }
    return *this;
}

class AntrenorOlimpici:public Antrenor
{
private:
    float bonus;//nu se schimba bonusul
    int nr_olimpiade_cu_rezultat;//cele in care sportivii acestui antrenor au obtinut medalie
    int* ani_olimpiade_cu_rezultat;
public:
    AntrenorOlimpici();//constructor fara parametrii
    AntrenorOlimpici(SportivLot* sportivilot,int numar_sportivi_lot,Sportiv* sportivi,int numar_sportivi_actuali,int varsta,string email,int numar_grupe,int numar_luni, bool este_acreditat,char initiala_sectie,char* nume,float salariu,int* numar_sportivi_alocati_pe_an,int numar_ani,float* cheltuieli_cu_chiria_pe_luna,double ani_experienta,char * prenume_antrenor, string* grupe_sportivi,int maxi,float bonus,int nr_olimpiade_cu_rezultat,int* ani_olimpiade_cu_rezultat);
    AntrenorOlimpici(const AntrenorOlimpici &antr_olimp);//copy constructor
    AntrenorOlimpici &operator=(const AntrenorOlimpici &antr_olimp);//supraincarcarea operatorului =
    ~AntrenorOlimpici();//destructor
    friend istream& operator>>(istream & in,AntrenorOlimpici&antren_olimp);//operator de citire
    friend ostream&operator<<(ostream& out, const AntrenorOlimpici &antren_olimp);//operator de afisare

    void setAniOlimpiadeCuRezultat(int* ani_olimpiade_cu_rezultat,int nr_olimpiade_cu_rezultat);//setter pentru anii in care au rezultate la olimpiada
    int* getAniOlimpiadeCuRezultat();//getter

    int getNrOlimpiadeCuRezultat();
    float getBonus();//ca sa pot vedea bonusul, pe el nu vreau sa il schimb

    const AntrenorOlimpici& operator++(); //ani experienta
    const AntrenorOlimpici operator++(int);//ani experienta
    float operator+(const AntrenorOlimpici &a);//adun salariile
    bool operator <(const AntrenorOlimpici& a);//numar grupe
    bool operator ==(const AntrenorOlimpici& a);//la email
    float operator-(float x);

    friend AntrenorOlimpici operator+(const Sportiv&sporti,const AntrenorOlimpici&antre);//adun un sportiv cu un antrenor
    friend AntrenorOlimpici operator+(AntrenorOlimpici antre,const Sportiv&sporti);//adun un antrenor cu un sportiv
    AntrenorOlimpici operator-(const Sportiv&sporti);//scad din antrenor sportivi

    friend AntrenorOlimpici operator+(const SportivLot&sportivil,const AntrenorOlimpici&antre);//adun un sportiv cu un antrenor
    friend AntrenorOlimpici operator+(AntrenorOlimpici antre,const SportivLot&sportivil);//adun un antrenor cu un sportiv
    AntrenorOlimpici operator-(const SportivLot&sportivil);//scad din antrenor sportivi

    float salariu_antrenor_olimpic();//calculez salariul antrenorului care are si bonus
    float marire_salariu();//se face marire de fiecare data cand are un nou numar de rezultate la olimpiade si aceasta marire se face pentru un an
    float anulare_marire_salariu();//il aduc la salariul inainte de marire-- acel salariu marit o sa fie primit doar o perioada de timp(un an)
};
float AntrenorOlimpici:: operator-(float x) //fac diferenta dintre salariu si un numar
{
    AntrenorOlimpici aux(*this);
    aux.salariu=aux.salariu-x;
    return aux.getSalariu();
}
bool AntrenorOlimpici::operator ==(const AntrenorOlimpici& a)
{
    if(this->email==a.email)//email-ul mereu o sa fie disitinct de la o persoana la alta
        return true;
    return false;
}
bool AntrenorOlimpici:: operator <(const AntrenorOlimpici& a)
{
    if(this->numar_grupe<a.numar_grupe)
        return true;
    return false;
}

float AntrenorOlimpici::operator+(const AntrenorOlimpici &a) //adun salariile
{
    AntrenorOlimpici aux(*this);
    aux.salariu=aux.salariu+a.salariu;
    return aux.getSalariu();
}

const AntrenorOlimpici& AntrenorOlimpici::operator++()
{
    this->ani_experienta++;
    return *this;
}
const AntrenorOlimpici AntrenorOlimpici::operator++(int)
{
    AntrenorOlimpici aux(*this);
    this->ani_experienta++;
    return aux;
}
AntrenorOlimpici operator+(AntrenorOlimpici antre,const Sportiv&sporti)
{
    Sportiv* lsportivi;
    lsportivi= new Sportiv[antre.numar_sportivi_actuali];
    for(int i=0; i<antre.numar_sportivi_actuali; i++)
        lsportivi[i]=antre.sportivi[i];
    if(antre.sportivi!=NULL)
        delete[]antre.sportivi;

    antre.numar_sportivi_actuali++;
    antre.sportivi=new Sportiv[antre.numar_sportivi_actuali];
    for(int i=0; i<antre.numar_sportivi_actuali-1; i++)
        antre.sportivi[i]=lsportivi[i];
    antre.sportivi[antre.numar_sportivi_actuali-1]=sporti;
    return antre;
}
AntrenorOlimpici operator+(const Sportiv&sporti,const AntrenorOlimpici&antre)
{
    AntrenorOlimpici auxiliar(antre);
    Sportiv* lsportivi;
    lsportivi= new Sportiv[auxiliar.numar_sportivi_actuali];
    for(int i=0; i<auxiliar.numar_sportivi_actuali; i++)
        lsportivi[i]=auxiliar.sportivi[i];
    if(auxiliar.sportivi!=NULL)
        delete[]auxiliar.sportivi;

    auxiliar.numar_sportivi_actuali++;
    auxiliar.sportivi=new Sportiv[auxiliar.numar_sportivi_actuali];
    for(int i=0; i<auxiliar.numar_sportivi_actuali-1; i++)
        auxiliar.sportivi[i]=lsportivi[i];
    auxiliar.sportivi[auxiliar.numar_sportivi_actuali-1]=sporti;
    return auxiliar;
}

AntrenorOlimpici AntrenorOlimpici:: operator-(const Sportiv&sporti)
{

    int poz=0;
    Sportiv* listasportivi;
    listasportivi=new Sportiv[this->numar_sportivi_actuali];
    for(int i=0; i<this->numar_sportivi_actuali; i++)
    {

        listasportivi[i]=this->sportivi[i];
        if(this->sportivi[i]==sporti)
            poz++;//poz o sa fie mereu 1 pentru ca doi sportivi sunt egali doar daca au acelasi cnp care este unic
    }
    if(this->sportivi!=NULL)
        delete[] this->sportivi;

    int j=0;
    this->sportivi=new Sportiv[this->numar_sportivi_actuali-poz];
    int i=0;
    while(i<this->numar_sportivi_actuali)
    {
        if(listasportivi[i]==sporti)
            i++;
        else
        {
            this->sportivi[j]=listasportivi[i];
            j++;
            i++;

        }

    }
    this->numar_sportivi_actuali=this->numar_sportivi_actuali-poz;
    return *this;


}
AntrenorOlimpici operator+(AntrenorOlimpici antre,const SportivLot&sportivil)
{
    SportivLot* lsportivi;
    lsportivi= new SportivLot[antre.numar_sportivi_lot];
    for(int i=0; i<antre.numar_sportivi_lot; i++)
        lsportivi[i]=antre.sportivilot[i];
    if(antre.sportivilot!=NULL)
        delete[]antre.sportivilot;

    antre.numar_sportivi_lot++;
    antre.sportivilot=new SportivLot[antre.numar_sportivi_lot];
    for(int i=0; i<antre.numar_sportivi_lot-1; i++)
        antre.sportivilot[i]=lsportivi[i];
    antre.sportivilot[antre.numar_sportivi_lot-1]=sportivil;
    return antre;
}
AntrenorOlimpici operator+(const SportivLot&sportivil,const AntrenorOlimpici&antre)
{
    AntrenorOlimpici auxiliar(antre);
    SportivLot* lsportivi;
    lsportivi= new SportivLot[auxiliar.numar_sportivi_lot];
    for(int i=0; i<auxiliar.numar_sportivi_lot; i++)
        lsportivi[i]=auxiliar.sportivilot[i];
    if(auxiliar.sportivilot!=NULL)
        delete[]auxiliar.sportivilot;

    auxiliar.numar_sportivi_lot++;
    auxiliar.sportivilot=new SportivLot[auxiliar.numar_sportivi_lot];
    for(int i=0; i<auxiliar.numar_sportivi_lot-1; i++)
        auxiliar.sportivilot[i]=lsportivi[i];
    auxiliar.sportivilot[auxiliar.numar_sportivi_lot-1]=sportivil;
    return auxiliar;
}

AntrenorOlimpici AntrenorOlimpici:: operator-(const SportivLot&sportivil)
{

    int poz=0;
    SportivLot* listasportivi;
    listasportivi=new SportivLot[this->numar_sportivi_lot];
    for(int i=0; i<this->numar_sportivi_lot; i++)
    {

        listasportivi[i]=this->sportivilot[i];
        if(this->sportivilot[i]==sportivil)
            poz++;//poz o sa fie mereu 1 pentru ca doi sportivi sunt egali doar daca au acelasi cnp care este unic
    }
    if(this->sportivilot!=NULL)
        delete[] this->sportivilot;

    int j=0;
    this->sportivilot=new SportivLot[this->numar_sportivi_lot-poz];
    int i=0;
    while(i<this->numar_sportivi_lot)
    {
        if(listasportivi[i]==sportivil)
            i++;
        else
        {
            this->sportivilot[j]=listasportivi[i];
            j++;
            i++;

        }

    }
    this->numar_sportivi_lot=this->numar_sportivi_lot-poz;
    return *this;


}
float AntrenorOlimpici::anulare_marire_salariu()
{
    salariu=this->salariu/(1+(0.2*this->nr_olimpiade_cu_rezultat));//este matematic calculul

    return salariu;
}
float AntrenorOlimpici::marire_salariu()
{
    salariu=this->salariu+(this->nr_olimpiade_cu_rezultat*20*this->salariu)/100;//aici este marirea
    return salariu;
}
float AntrenorOlimpici::salariu_antrenor_olimpic()
{
    salariu=this->salariu+this->bonus;//aici adaug bonusul-- aceasta functie o sa fie aplicata o singura data
    return salariu;
}
void AntrenorOlimpici::setAniOlimpiadeCuRezultat(int* ani_olimpiade_cu_rezultat,int nr_olimpiade_cu_rezultat)
{
    this->nr_olimpiade_cu_rezultat=nr_olimpiade_cu_rezultat;
    if(this->ani_olimpiade_cu_rezultat!=NULL)
        delete [] this->ani_olimpiade_cu_rezultat;
    this->ani_olimpiade_cu_rezultat=new int[nr_olimpiade_cu_rezultat];
    for(int i=0; i<nr_olimpiade_cu_rezultat; i++)
        this->ani_olimpiade_cu_rezultat[i]=ani_olimpiade_cu_rezultat[i];
}
int* AntrenorOlimpici::getAniOlimpiadeCuRezultat()
{
    return this->ani_olimpiade_cu_rezultat;
}
int AntrenorOlimpici::getNrOlimpiadeCuRezultat()
{
    return this->nr_olimpiade_cu_rezultat;
}
float AntrenorOlimpici::getBonus()
{
    return this->bonus;
}
AntrenorOlimpici::AntrenorOlimpici():Antrenor()//constructor fara parametrii
{
    this->bonus=0.0;
    this->nr_olimpiade_cu_rezultat=0;
    this->ani_olimpiade_cu_rezultat=NULL;
}
AntrenorOlimpici::AntrenorOlimpici(SportivLot* sportivilot,int numar_sportivi_lot,Sportiv* sportivi,int numar_sportivi_actuali,int varsta,string email,int numar_grupe,int numar_luni, bool este_acreditat,char initiala_sectie,char* nume,float salariu,int* numar_sportivi_alocati_pe_an,int numar_ani,float* cheltuieli_cu_chiria_pe_luna,double ani_experienta,char * prenume_antrenor, string* grupe_sportivi,int maxi,float bonus,int nr_olimpiade_cu_rezultat,int* ani_olimpiade_cu_rezultat):Antrenor(sportivilot,numar_sportivi_lot,sportivi,numar_sportivi_actuali,varsta,email,numar_grupe,numar_luni,este_acreditat,initiala_sectie, nume,salariu,numar_sportivi_alocati_pe_an,numar_ani,cheltuieli_cu_chiria_pe_luna,ani_experienta,prenume_antrenor,grupe_sportivi,maxi)
{
    this->bonus=bonus;
    this->nr_olimpiade_cu_rezultat=nr_olimpiade_cu_rezultat;

    this->ani_olimpiade_cu_rezultat=new int[nr_olimpiade_cu_rezultat];//aloc dinamic un vector
    for(int i=0; i<nr_olimpiade_cu_rezultat; i++)
        this->ani_olimpiade_cu_rezultat[i]=ani_olimpiade_cu_rezultat[i];
}
AntrenorOlimpici::AntrenorOlimpici(const AntrenorOlimpici &antr_olimp):Antrenor(antr_olimp)
{
    this->bonus=antr_olimp.bonus;
    this->nr_olimpiade_cu_rezultat=antr_olimp.nr_olimpiade_cu_rezultat;

    this->ani_olimpiade_cu_rezultat=new int[antr_olimp.nr_olimpiade_cu_rezultat];//aloc dinamic un vector
    for(int i=0; i<antr_olimp.nr_olimpiade_cu_rezultat; i++)
        this->ani_olimpiade_cu_rezultat[i]=antr_olimp.ani_olimpiade_cu_rezultat[i];
}
AntrenorOlimpici &AntrenorOlimpici::operator=(const AntrenorOlimpici &antr_olimp)
{
    if(this!=&antr_olimp)
    {
        Antrenor::operator=(antr_olimp);

        if(this->ani_olimpiade_cu_rezultat!=NULL)
            delete []this->ani_olimpiade_cu_rezultat;

        this->ani_olimpiade_cu_rezultat=new int[antr_olimp.nr_olimpiade_cu_rezultat];
        for(int i=0; i<antr_olimp.nr_olimpiade_cu_rezultat; i++)
            this->ani_olimpiade_cu_rezultat[i]=antr_olimp.ani_olimpiade_cu_rezultat[i];

        this->bonus=antr_olimp.bonus;
        this->nr_olimpiade_cu_rezultat=antr_olimp.nr_olimpiade_cu_rezultat;

    }
    return *this;
}
AntrenorOlimpici::~AntrenorOlimpici()
{
    if(this->ani_olimpiade_cu_rezultat!=NULL)
        delete []this->ani_olimpiade_cu_rezultat;
}
istream& operator>>(istream & in,AntrenorOlimpici&antren_olimp)
{
    in>>(Antrenor&) antren_olimp;
    cout<<"\nBonusul primit de antrenor: ";
    in>>antren_olimp.bonus;
    cout<<"\nNumarul de olimpiade la care sportivii acestui antrenor au obtinut rezultate: ";
    in>>antren_olimp.nr_olimpiade_cu_rezultat;
    cout<<"\nAnii in care sportivii acestui antrenor au obtinut rezultate la olimpiada: ";
    if(antren_olimp.ani_olimpiade_cu_rezultat!=NULL)
        delete [] antren_olimp.ani_olimpiade_cu_rezultat;
    antren_olimp.ani_olimpiade_cu_rezultat=new int[antren_olimp.nr_olimpiade_cu_rezultat];
    for(int i=0; i<antren_olimp.nr_olimpiade_cu_rezultat; i++)
        in>>antren_olimp.ani_olimpiade_cu_rezultat[i];

    return in;
}
ostream& operator <<(ostream &out, const AntrenorOlimpici &antren_olimp)
{
    out<<(Antrenor&) antren_olimp;
    out<<"\nPentru ca este antrenor care pregateste sportivii pentru olimpiada, acesta primeste la salariu un bonus de: "<<antren_olimp.bonus<<" lei";
    out<<"\nNumarul de olimpiade la care sportivii acestui antrenor au obtinut rezultate este de: "<<antren_olimp.nr_olimpiade_cu_rezultat;
    out<<"\nAnii in care sportivii acestui antrenor au obtinut rezultate la olimpiada sunt:\n";
    for(int i=0; i<antren_olimp.nr_olimpiade_cu_rezultat; i++)
        out<<"Anul: "<<antren_olimp.ani_olimpiade_cu_rezultat[i]<<endl;
    return out;
}

class Sala
{
private:
    char evaluare;
    Antrenor* antrenor;
    AntrenorOlimpici* antrenorol;//am facut vector de tipul AntrenorOlimpici si un vector de tipul Antrenor pentru ca o sala vreau  sa aiba ambele tipuri
    int nr_antrenori;
    int nr_antrenori_ol;
    char* nume_sala;
    string specific_sala;
    char* locatie;
    float latime_sala_zona_de_sport;
    float lungime_sala_zona_de_sport;
    float latime_sala;
    float lungime_sala;
    float inaltime;
    bool este_renovat;
    int numar_culoare_teren;
    int nr_ore_permise_de_stat;
    const int nr_de_identificare;
public:
    Sala();
    Sala(AntrenorOlimpici* antrenorol,int nr_antrenori_ol,char evaluare,Antrenor * antrenor,int nr_antrenori,char* nume_sala, char* locatie, float latime_sala_zona_de_sport, float lungime_sala_zona_de_sport, float latime_sala, float lungime_sala, float inaltime, string specific_sala, bool este_renovat, int numar_culoare_teren,int nr_ore_permise_de_stat);
    Sala(AntrenorOlimpici* antrenorol,int nr_antrenori_ol,char evaluare,Antrenor * antrenor,int nr_antrenori,char* nume_sala, char* locatie, string specific_sala, bool este_renovat);
    Sala(char* nume_sala,char* locatie,string specific_sala,float latime_sala_zona_de_sport, float lungime_sala_zona_de_sport, float latime_sala, float lungime_sala,float inaltime);
    Sala (const Sala& sala);
    Sala &operator=(const Sala &sala);
    ~Sala();

    static int nr_inregistrare;

    friend ostream& operator<<(ostream& out, const Sala& sala_sport);
    friend istream& operator>>(istream& in, Sala& sala_sport);

    void setEvaluare(char evaluare);
    char getEvaluare();

    int getNrAntrenori();//pentru antrenorii simplii


    Antrenor* getAntrenor();

    int getNrAntrenoriOlimpici();


    AntrenorOlimpici* getAntrenorOlimpici();

    char* getNumeSala();


    string getSpecificSala();


    char* getLocatie();

    void setLatimeSalaZonaDeSport(float latime_sala_zona_de_sport);
    float getLatimeSalaZonaDeSport();

    void setLungimeSalaZonaDeSport(float lungime_sala_zona_de_sport);
    float getLungimeSalaZonaDeSport();

    void setLatimeSala(float latime_sala);
    float getLatimeSala();

    void setLungimeSala(float lungime_sala);
    float getLungimeSala();

    void setInaltime(float inaltime);
    float getInaltime();

    void setRenovat(bool este_renovat);
    bool getRenovat();

    void setNumarCuloare(int numar_culoare_teren);
    int getNumarCuloare();

    void setNumarOrePermiseDeStat(int nr_ore_permise_de_stat);
    int getNumarOrePermiseDeStat();

    int getNumarDeIdentificare();//aici este variabila const

    const Sala& operator++();//cresc numarul de culoare
    const Sala operator++(int);//cresc numarul de culoare
    float operator/(const Sala &a);//impart inaltimile
    bool operator >=(const Sala& a);//compar latimile salilor
    bool operator ==(const Sala& a);//numele salii o sa fie mereu diferit(nu pot sa am doua sali cu acelasi nume)

    friend Sala operator+(const Antrenor&antr,const Sala&sala);
    friend Sala operator+(Sala sala,const Antrenor&antr);
    Sala operator-(const Antrenor&antr);

    friend Sala operator+(const AntrenorOlimpici&antr,const Sala&sala);
    friend Sala operator+(Sala sala,const AntrenorOlimpici&antr);
    Sala operator-(const AntrenorOlimpici&antr);

    void capacitate();//calculez capacitatea de oameni din sala, capacitatea de oameni din zonei dedicata sportului, capacitatea spectatorilor, volumul salii
    //Procentul de oameni aflati in zona de sport din capacitatea maxima de persoane care se pot afla in sala

};
void Sala::capacitate()
{
    float arie_totala_sala, arie_sala_zona_de_sport, volum;
    int capacitate_maxima_de_oameni,capacitate_maxima_zona_de_sport;
    float procent_oameni_zone_sport;

    arie_totala_sala=this->latime_sala*this->lungime_sala;

    arie_sala_zona_de_sport=this->latime_sala_zona_de_sport*this->lungime_sala_zona_de_sport;

    capacitate_maxima_de_oameni=arie_totala_sala/Sportiv::arie_medie_sportiv;
    capacitate_maxima_zona_de_sport=arie_sala_zona_de_sport/Sportiv::arie_medie_sportiv;

    volum=arie_totala_sala*this->inaltime;

    procent_oameni_zone_sport=(float(capacitate_maxima_zona_de_sport)*100)/capacitate_maxima_de_oameni;

    cout<<"\nVolumul salii "<<nume_sala<<" este de: "<<volum<<" m^3";
    cout<<"\nNumarul maxim de oameni care pot intra in sala este de: "<<capacitate_maxima_de_oameni;
    cout<<"\nNumarul maxim de spectatori este de: "<<capacitate_maxima_de_oameni-capacitate_maxima_zona_de_sport;
    cout<<"\nNumarul maxim de persoane care se pot afla in zona destinata actitivatii sportive este de: "<<capacitate_maxima_zona_de_sport;
    //cat reprezinta numarul de persoane care pot intra in zona de sport din nr total de pers din sala
    cout<<"\nProcentul de oameni aflati in zona de sport din capacitatea maxima de persoane care se pot afla in sala este de: "<<procent_oameni_zone_sport<<"%";

}
Sala operator+(Sala sala,const Antrenor&antr)//adun o sala cu un antrenor
{
    Antrenor* lsantrenor;
    lsantrenor= new Antrenor[sala.nr_antrenori];
    for(int i=0; i<sala.nr_antrenori; i++)
        lsantrenor[i]=sala.antrenor[i];
    if(sala.antrenor!=NULL)
        delete[]sala.antrenor;

    sala.nr_antrenori++;
    sala.antrenor=new Antrenor[sala.nr_antrenori];
    for(int i=0; i<sala.nr_antrenori-1; i++)
        sala.antrenor[i]=lsantrenor[i];
    sala.antrenor[sala.nr_antrenori-1]=antr;
    return sala;
}
Sala operator+(const Antrenor&antr,const Sala&sala)//adun un antrenor cu o sala
{
    Sala auxiliar(sala);
    Antrenor* lsantrenor;
    lsantrenor= new Antrenor[auxiliar.nr_antrenori];
    for(int i=0; i<auxiliar.nr_antrenori; i++)
        lsantrenor[i]=auxiliar.antrenor[i];
    if(auxiliar.antrenor!=NULL)
        delete[]auxiliar.antrenor;

    auxiliar.nr_antrenori++;
    auxiliar.antrenor=new Antrenor[auxiliar.nr_antrenori];
    for(int i=0; i<auxiliar.nr_antrenori-1; i++)
        auxiliar.antrenor[i]=lsantrenor[i];
    auxiliar.antrenor[auxiliar.nr_antrenori-1]=antr;
    return auxiliar;
}
Sala Sala::operator-(const Antrenor&antr)//elimin un antrenor dintr-o sala
{
    int poz=0;
    Antrenor* lsantrenori;
    lsantrenori=new Antrenor[this->nr_antrenori];
    for(int i=0; i<this->nr_antrenori; i++)
    {

        lsantrenori[i]=this->antrenor[i];
        if(this->antrenor[i]==antr)
            poz++;
    }
    if(this->antrenor!=NULL)
        delete[] this->antrenor;

    int j=0;
    this->antrenor=new Antrenor[this->nr_antrenori-poz];
    int i=0;
    while(i<this->nr_antrenori)
    {
        if(lsantrenori[i]==antr)
            i++;
        else
        {
            this->antrenor[j]=lsantrenori[i];
            j++;
            i++;

        }

    }
    this->nr_antrenori=this->nr_antrenori-poz;
    return *this;


}
Sala operator+(Sala sala,const AntrenorOlimpici&antr)//adun o sala cu un antrenor
{
    AntrenorOlimpici* lsantrenor;
    lsantrenor= new AntrenorOlimpici[sala.nr_antrenori_ol];
    for(int i=0; i<sala.nr_antrenori_ol; i++)
        lsantrenor[i]=sala.antrenorol[i];
    if(sala.antrenorol!=NULL)
        delete[]sala.antrenorol;

    sala.nr_antrenori_ol++;
    sala.antrenorol=new AntrenorOlimpici[sala.nr_antrenori_ol];
    for(int i=0; i<sala.nr_antrenori_ol-1; i++)
        sala.antrenorol[i]=lsantrenor[i];
    sala.antrenorol[sala.nr_antrenori_ol-1]=antr;
    return sala;
}
Sala operator+(const AntrenorOlimpici&antr,const Sala&sala)//adun un antrenor cu o sala
{
    Sala auxiliar(sala);
    AntrenorOlimpici* lsantrenor;
    lsantrenor= new AntrenorOlimpici[auxiliar.nr_antrenori_ol];
    for(int i=0; i<auxiliar.nr_antrenori_ol; i++)
        lsantrenor[i]=auxiliar.antrenorol[i];
    if(auxiliar.antrenorol!=NULL)
        delete[]auxiliar.antrenorol;

    auxiliar.nr_antrenori_ol++;
    auxiliar.antrenorol=new AntrenorOlimpici[auxiliar.nr_antrenori_ol];
    for(int i=0; i<auxiliar.nr_antrenori_ol-1; i++)
        auxiliar.antrenorol[i]=lsantrenor[i];
    auxiliar.antrenorol[auxiliar.nr_antrenori_ol-1]=antr;
    return auxiliar;
}
Sala Sala::operator-(const AntrenorOlimpici&antr)//elimin un antrenor dintr-o sala
{
    int poz=0;
    AntrenorOlimpici* lsantrenori;
    lsantrenori=new AntrenorOlimpici[this->nr_antrenori_ol];
    for(int i=0; i<this->nr_antrenori_ol; i++)
    {

        lsantrenori[i]=this->antrenorol[i];
        if(this->antrenorol[i]==antr)
            poz++;
    }
    if(this->antrenorol!=NULL)
        delete[] this->antrenorol;

    int j=0;
    this->antrenorol=new AntrenorOlimpici[this->nr_antrenori_ol-poz];
    int i=0;
    while(i<this->nr_antrenori_ol)
    {
        if(lsantrenori[i]==antr)
            i++;
        else
        {
            this->antrenorol[j]=lsantrenori[i];
            j++;
            i++;

        }

    }
    this->nr_antrenori_ol=this->nr_antrenori_ol-poz;
    return *this;


}
bool Sala::operator ==(const Sala& a)
{
    if(strcmp(this->nume_sala,a.nume_sala)==0)//numele salii o sa fie mereu diferit(nu pot sa am doua sali cu acelasi nume)
        return true;
    return false;
}
bool Sala:: operator >=(const Sala& a)
{
    if(this->lungime_sala>=a.lungime_sala && this->latime_sala>=latime_sala)
        return true;
    return false;
}

float Sala:: operator/(const Sala &a) //impart inaltimile
{
    Sala aux(*this);
    aux.inaltime=aux.inaltime/a.inaltime;
    return aux.getInaltime();
}

const Sala& Sala :: operator++()//preincrementare
{
    this->numar_culoare_teren++;
    return *this;
}

const Sala Sala::operator++(int)//postincrementare
{
    Sala aux (*this);
    this->numar_culoare_teren++;
    return aux;
}

int Sala::nr_inregistrare=200;

void Sala::setEvaluare(char evaluare)
{
    this->evaluare=evaluare;
}
char Sala::getEvaluare()
{
    return this->evaluare;
}

int Sala::getNrAntrenori()
{
    return this->nr_antrenori;
}

Antrenor* Sala::getAntrenor()
{
    return this->antrenor;
}
int Sala::getNrAntrenoriOlimpici()
{
    return this->nr_antrenori_ol;
}

AntrenorOlimpici* Sala::getAntrenorOlimpici()
{
    return this->antrenorol;
}
char* Sala::getNumeSala()
{
    return this->nume_sala;
}

string Sala::getSpecificSala()
{
    return this->specific_sala;
}
char* Sala::getLocatie()
{
    return this->locatie;
}

void Sala::setLatimeSalaZonaDeSport(float latime_sala_zona_de_sport)
{
    this->latime_sala_zona_de_sport=latime_sala_zona_de_sport;
}
float Sala::getLatimeSalaZonaDeSport()
{
    return this->latime_sala_zona_de_sport;
}

void Sala::setLungimeSalaZonaDeSport(float lungime_sala_zona_de_sport)
{
    this->lungime_sala_zona_de_sport=lungime_sala_zona_de_sport;
}
float Sala::getLungimeSalaZonaDeSport()
{
    return this->lungime_sala_zona_de_sport;
}

void Sala::setLatimeSala(float latime_sala)
{
    this->latime_sala=latime_sala;
}
float Sala::getLatimeSala()
{
    return this->latime_sala;
}

void Sala::setLungimeSala(float lungime_sala)
{
    this->lungime_sala=lungime_sala;
}
float Sala::getLungimeSala()
{
    return this->lungime_sala;
}
void Sala::setInaltime(float inaltime)
{
    this->inaltime=inaltime;
}
float Sala::getInaltime()
{
    return this->inaltime;
}

void Sala::setRenovat(bool este_renovat)
{
    this->este_renovat=este_renovat;
}
bool Sala::getRenovat()
{
    return this->este_renovat;
}
void Sala::setNumarCuloare(int numar_culoare_teren)
{
    this->numar_culoare_teren=numar_culoare_teren;
}
int Sala::getNumarCuloare()
{
    return this -> numar_culoare_teren;
}
void Sala::setNumarOrePermiseDeStat(int nr_ore_permise_de_stat)
{
    this->nr_ore_permise_de_stat=nr_ore_permise_de_stat;
}
int Sala::getNumarOrePermiseDeStat()
{
    return this -> nr_ore_permise_de_stat;
}
int Sala::getNumarDeIdentificare()
{
    return this ->nr_de_identificare;
}

ostream& operator<<(ostream& out, const Sala& sala_sport)
{
    out<<"\nSala de sport "<<sala_sport.nume_sala<<" are urmatoarea locatie: "<<sala_sport.locatie<<".";

    if(sala_sport.evaluare=='0'|| sala_sport.evaluare=='1'||sala_sport.evaluare=='2')
        out<<"\nAceasta sala de sport are conditii nesatisfacatoare.";
    if(sala_sport.evaluare=='3'|| sala_sport.evaluare=='4'||sala_sport.evaluare=='5')
        out<<"\nAceasta sala de sport are conditii acceptabile.";
    if(sala_sport.evaluare=='6'|| sala_sport.evaluare=='7')
        out<<"\nAceasta sala de sport are conditii bune.";
    if(sala_sport.evaluare=='8'|| sala_sport.evaluare=='9')
        out<<"\nAceasta sala de sport are conditii foarte bune.";

    out<<"\nSpecificul salii de sport este "<<sala_sport.specific_sala<<".";
    if(sala_sport.este_renovat==0)
        out<<"\nAceasta sala nu este renovata.";
    else
        out<<"\nAceasta sala este renovata.";

    if(sala_sport.latime_sala!=0)
        out<<"\nDimensiunile salii sunt urmatoarele: "<<sala_sport.latime_sala<<" m latime, ";
    if(sala_sport.lungime_sala!=0)
        out<<sala_sport.lungime_sala<<" m lungime ";
    if(sala_sport.inaltime!=0)
        out<<"si "<<sala_sport.inaltime<<" m inaltime.";

    if(sala_sport.latime_sala_zona_de_sport!=0)
        out<<"\nDimensiunile zonei in care se practica sportul: "<<sala_sport.latime_sala_zona_de_sport<<" m latime ";
    if(sala_sport.lungime_sala_zona_de_sport!=0)
        out<<"si "<<sala_sport.lungime_sala_zona_de_sport<<" m lungime.";
    if(sala_sport.numar_culoare_teren!=0)
        out<<"\nNumarul de culoare este de "<<sala_sport.numar_culoare_teren<<".";
    if(sala_sport.nr_ore_permise_de_stat!=0)
    {
        out<<"\nNumarul de ore in care poti avea acces la sala este de "<<sala_sport.nr_ore_permise_de_stat;

        if(sala_sport.nr_ore_permise_de_stat==1)
            out<<" ora.";
        else
            out<<" ore.";
    }

    out<<"\nNumarul antrenorilor din aceasta sala care nu au calificarea sa antreneze sportivi pentru olimpiada este in numar de: "<<sala_sport.nr_antrenori;
    if(sala_sport.nr_antrenori!=0)
    {
        out<<"\n\nAntrenorii care antreneaza in aceasta sala, dar care nu au calificarea sa antreneze sportivi pentru olimpiada sunt:\n\n";
        for(int i=0; i<sala_sport.nr_antrenori; i++)
            out<<"Nume de familie: "<<sala_sport.antrenor[i].getNume()<<"   Prenume: "<<sala_sport.antrenor[i].getPrenumeAntrenor()<<"   Adresa de e-mail: "<<sala_sport.antrenor[i].getEmail()<<"   Numarul de grupe: "<<sala_sport.antrenor[i].getNumarGrupe()<<"    Numarul de sportivi antrenati care nu fac parte din lot: "<<sala_sport.antrenor[i].getNumarSportiviActuali()<<"   Numarul de sportivi antrenati care fac parte din lot: "<<sala_sport.antrenor[i].getNumarSportiviLot()<<"\n";
    }

    out<<"\nNumarul antrenorilor din aceasta sala care au calificarea sa antreneze sportivi pentru olimpiada este in numar de: "<<sala_sport.nr_antrenori_ol;
    if(sala_sport.nr_antrenori_ol!=0)
    {
        out<<"\n\nAntrenorii care antreneaza in aceasta sala si care au calificarea sa antreneze sportivi pentru olimpiada sunt:\n\n";
        for(int i=0; i<sala_sport.nr_antrenori_ol; i++)
            out<<"Nume de familie: "<<sala_sport.antrenorol[i].getNume()<<"   Prenume: "<<sala_sport.antrenorol[i].getPrenumeAntrenor()<<"   Adresa de e-mail: "<<sala_sport.antrenorol[i].getEmail()<<"   Numarul de grupe: "<<sala_sport.antrenorol[i].getNumarGrupe()<<"    Numarul de sportivi antrenati care nu fac parte din lot: "<<sala_sport.antrenorol[i].getNumarSportiviActuali()<<"   Numarul de sportivi antrenati care fac parte din lot: "<<sala_sport.antrenorol[i].getNumarSportiviLot()<<"\n";
    }


    return out;
}
istream& operator>>(istream& in, Sala& sala_sport)
{
    in.get();
    cout<<"\nNumele salii: ";

    char nume[100];
    in.getline(nume,100);

    if(sala_sport.nume_sala!=NULL)
        delete[] sala_sport.nume_sala;
    sala_sport.nume_sala=new char[strlen(nume)+1];
    strcpy(sala_sport.nume_sala,nume);


    cout<<"\nLocatia: ";
    char adresa[100];
    in.getline(adresa,100);

    if(sala_sport.locatie!=NULL)
        delete[] sala_sport.locatie;
    sala_sport.locatie=new char[strlen(adresa)+1];
    strcpy(sala_sport.locatie,adresa);

    cout<<"\nSpecificul salii de sport [numele sportului care se practica:Inot/Dans/Triathlon/Atletism/Ciclism]: ";
    in>>sala_sport.specific_sala;

    cout<<"\nCat de satisfacatoare sunt conditiile din aceasta sala? (dati valori de la 0 la 9, unde 0 reprezinta nesatisfacator, iar 9 - foarte satisfacator) :";
    in>>sala_sport.evaluare;

    cout<<"\nEste renovata? [1-true/0-false]: ";
    in>>sala_sport.este_renovat;

    cout<<"\nLatimea salii de sport (m): ";
    in>>sala_sport.latime_sala;

    cout<<"\nLungimea salii de sport (m): ";
    in>>sala_sport.lungime_sala;

    cout<<"\nLatimea zonei dedicata sportului (m): ";
    in>>sala_sport.latime_sala_zona_de_sport;

    cout<<"\nLungimea zonei dedicata sportului (m): ";
    in>>sala_sport.lungime_sala_zona_de_sport;

    cout<<"\nInaltimea salii de sport (m): ";
    in>>sala_sport.inaltime;

    cout<<"\nNumarul de culoare: ";
    in>>sala_sport.numar_culoare_teren;

    cout<<"\nNumarul de ore in care poti avea acces la sala: ";
    in>>sala_sport.nr_ore_permise_de_stat;

    return in;
}

Sala :: Sala():nr_de_identificare(nr_inregistrare++)
{
    nume_sala= new char[strlen("nestiuta")+1];
    strcpy(nume_sala,"nestiuta");

    locatie= new char[strlen("nestiuta")+1];
    strcpy(locatie,"nestiuta");

    latime_sala_zona_de_sport=0;
    lungime_sala_zona_de_sport=0;
    latime_sala=0;
    lungime_sala=0;
    inaltime=0;
    specific_sala="necunoscut";
    este_renovat=false;
    numar_culoare_teren=0;
    nr_ore_permise_de_stat=0;
    nr_antrenori=0;
    antrenor=NULL;
    nr_antrenori_ol=0;
    antrenorol=NULL;
    evaluare='-';

}

Sala::Sala(AntrenorOlimpici*antrenorol,int nr_antrenori_ol,char evaluare,Antrenor* antrenor,int nr_antrenori,char* nume_sala, char* locatie, float latime_sala_zona_de_sport, float lungime_sala_zona_de_sport, float latime_sala, float lungime_sala, float inaltime, string specific_sala, bool este_renovat, int numar_culoare_teren,int nr_ore_permise_de_stat):nr_de_identificare(nr_inregistrare++)
{

    this->nr_antrenori=nr_antrenori;
    this->nr_antrenori_ol=nr_antrenori_ol;

    this->antrenor=new Antrenor[nr_antrenori];
    for(int i=0; i<nr_antrenori; i++)
        this->antrenor[i]=antrenor[i];

    this->antrenorol=new AntrenorOlimpici[nr_antrenori_ol];
    for(int i=0; i<nr_antrenori_ol; i++)
        this->antrenorol[i]=antrenorol[i];

    this-> nume_sala= new char[strlen(nume_sala)+1];
    strcpy(this->nume_sala,nume_sala);

    this-> locatie= new char[strlen(locatie)+1];
    strcpy(this->locatie,locatie);
    this -> evaluare=evaluare;
    this -> latime_sala_zona_de_sport = latime_sala_zona_de_sport;
    this -> lungime_sala_zona_de_sport=lungime_sala_zona_de_sport;
    this -> latime_sala=latime_sala;
    this -> lungime_sala=lungime_sala;
    this -> inaltime=inaltime;
    this -> specific_sala=specific_sala;
    this -> este_renovat=este_renovat;
    this -> numar_culoare_teren=numar_culoare_teren;
    this -> nr_ore_permise_de_stat=nr_ore_permise_de_stat;
}
Sala::Sala(AntrenorOlimpici*antrenorol,int nr_antrenori_ol,char evaluare, Antrenor * antrenor,int nr_antrenori,char* nume_sala, char* locatie, string specific_sala, bool este_renovat):nr_de_identificare(nr_inregistrare++)
{
    this->nr_antrenori=nr_antrenori;
    this->nr_antrenori_ol=nr_antrenori_ol;

    this->antrenor=new Antrenor[nr_antrenori];
    for(int i=0; i<nr_antrenori; i++)
        this->antrenor[i]=antrenor[i];

    this->antrenorol=new AntrenorOlimpici[nr_antrenori_ol];
    for(int i=0; i<nr_antrenori_ol; i++)
        this->antrenorol[i]=antrenorol[i];

    this -> nume_sala= new char[strlen(nume_sala)+1];
    strcpy(this->nume_sala,nume_sala);
    this -> evaluare=evaluare;
    this -> locatie= new char[strlen(locatie)+1];
    strcpy(this->locatie,locatie);
    this -> specific_sala=specific_sala;
    this -> este_renovat=este_renovat;

    latime_sala_zona_de_sport=0;
    lungime_sala_zona_de_sport=0;
    latime_sala=0;
    lungime_sala=0;
    inaltime=0;
    numar_culoare_teren=0;
    nr_ore_permise_de_stat=0;
}
Sala::Sala(char* nume_sala,char* locatie,string specific_sala,float latime_sala_zona_de_sport, float lungime_sala_zona_de_sport, float latime_sala, float lungime_sala,float inaltime):nr_de_identificare(nr_inregistrare++)
{
    this -> nume_sala= new char[strlen(nume_sala)+1];
    strcpy(this->nume_sala,nume_sala);

    this -> locatie= new char[strlen(locatie)+1];
    strcpy(this->locatie,locatie);

    this -> specific_sala=specific_sala;
    this -> latime_sala=latime_sala;
    this -> lungime_sala=lungime_sala;
    this -> latime_sala_zona_de_sport=latime_sala_zona_de_sport;
    this -> lungime_sala_zona_de_sport=lungime_sala_zona_de_sport;
    this -> inaltime=inaltime;

    strcpy(locatie,"nestiuta");
    este_renovat=false;
    numar_culoare_teren=0;
    nr_ore_permise_de_stat=0;
    nr_antrenori=0;
    antrenor=NULL;
    nr_antrenori_ol=0;
    antrenorol=NULL;
    evaluare='-';
}
Sala :: Sala (const Sala& sala):nr_de_identificare(sala.nr_de_identificare)//copy constructor
{
    this -> nume_sala= new char[strlen(sala.nume_sala)+1];
    strcpy(this->nume_sala,sala.nume_sala);

    this -> locatie= new char[strlen(sala.locatie)+1];
    strcpy(this->locatie,sala.locatie);

    this->nr_antrenori=sala.nr_antrenori;
    this->nr_antrenori_ol=sala.nr_antrenori_ol;

    this->antrenor=new Antrenor[sala.nr_antrenori];
    for(int i=0; i<sala.nr_antrenori; i++)
        this->antrenor[i]=sala.antrenor[i];

    this->antrenorol=new AntrenorOlimpici[sala.nr_antrenori_ol];
    for(int i=0; i<sala.nr_antrenori_ol; i++)
        this->antrenorol[i]=sala.antrenorol[i];

    this -> evaluare=sala.evaluare;
    this -> latime_sala = sala.latime_sala;
    this -> lungime_sala = sala.lungime_sala;
    this -> latime_sala_zona_de_sport = sala.latime_sala_zona_de_sport;
    this -> lungime_sala_zona_de_sport=sala.lungime_sala_zona_de_sport;
    this -> inaltime=sala.inaltime;
    this -> specific_sala=sala.specific_sala;
    this -> este_renovat=sala.este_renovat;
    this -> numar_culoare_teren=sala.numar_culoare_teren;
    this -> nr_ore_permise_de_stat=sala.nr_ore_permise_de_stat;
}
Sala& Sala ::operator=(const Sala &sala)//operator =
{
    if(this!=&sala)
    {
        if(this->locatie!=NULL)
            delete[] this->locatie;

        if(this->nume_sala!=NULL)
            delete[] this->nume_sala;

        if(this->antrenor !=NULL)
            delete [] this->antrenor;

        if(this->antrenorol !=NULL)
            delete [] this->antrenorol;

        this-> locatie= new char[strlen(sala.locatie)+1];
        strcpy(this->locatie,sala.locatie);

        this->nr_antrenori=sala.nr_antrenori;
        this->nr_antrenori_ol=sala.nr_antrenori_ol;

        this->antrenor=new Antrenor[sala.nr_antrenori];
        for(int i=0; i<sala.nr_antrenori; i++)
            this->antrenor[i]=sala.antrenor[i];

        this->antrenorol=new AntrenorOlimpici[sala.nr_antrenori_ol];
        for(int i=0; i<sala.nr_antrenori_ol; i++)
            this->antrenorol[i]=sala.antrenorol[i];


        this-> nume_sala= new char[strlen(sala.nume_sala)+1];
        strcpy(this->nume_sala,sala.nume_sala);

        this -> evaluare=sala.evaluare;
        this -> latime_sala = sala.latime_sala;
        this -> lungime_sala = sala.lungime_sala;
        this -> latime_sala_zona_de_sport = sala.latime_sala_zona_de_sport;
        this -> lungime_sala_zona_de_sport=sala.lungime_sala_zona_de_sport;
        this -> inaltime=sala.inaltime;
        this -> specific_sala=sala.specific_sala;
        this -> este_renovat=sala.este_renovat;
        this -> numar_culoare_teren=sala.numar_culoare_teren;
        this -> nr_ore_permise_de_stat=sala.nr_ore_permise_de_stat;
    }
    return *this;
}
Sala::~Sala()//destructor
{
    if(this->locatie!=NULL)
        delete[] this->locatie;

    if(this->nume_sala!=NULL)
        delete[] this->nume_sala;

    if(this->antrenor !=NULL)
        delete [] this->antrenor;

    if(this->antrenorol !=NULL)
        delete [] this->antrenorol;
}
class TipuriSport
{
private:

    Sala* sali;
    int numar_sali;
    string nume_sport;
    bool echipa;
    char dificultate;
    int numarul_anilor;
    int* poz_sporturi_populare_pe_ani;
    int nr_premii_valoroase_ale_clubului;
    int nr_materiale;
    float pret_materiale_de_baza;//cat te costa sa iti cumperi de la orice magazin toate materialele de baza la un loc
    string* materiale_necesare;//daca se intampla sa nu le ai le poti inchiria de la club
public:
    TipuriSport();
    TipuriSport(Sala* sali, int numar_sali,string nume_sport,bool echipa,char dificultate,int numarul_anilor,int* poz_sporturi_populare_pe_ani,int nr_premii_valoroase_ale_clubului,int nr_materiale,float pret_materiale_de_baza,string * materiale_necesare);
    TipuriSport(Sala* sali, int numar_sali,string nume_sport,bool echipa,char dificultate,float pret_materiale_de_baza,int nr_materiale,string* materiale_necesare);
    TipuriSport(const TipuriSport& sport);//cc
    TipuriSport& operator=(const TipuriSport& sport);
    ~TipuriSport();
    friend ostream& operator<<(ostream& out, const TipuriSport& sportul);
    friend istream& operator>>(istream& in,TipuriSport& sportul);

    int getNumarSali();


    Sala* getSala();


    string getNumeSport()const;


    bool getEchipa();

    char getDificultate();

    int getNumarulAnilor();

    void setPozSporturiPopularePeAn(int * poz_sporturi_populare_pe_ani, int numarul_anilor);
    int * getPozSporturiPopularePeAn();

    void setNrPremiiValoroaseAleClubului(int nr_premii_valoroase_ale_clubului);
    int getNrPremiiValoroaseAleClubului();

    int getNrMateriale();

    float getPretMaximMaterialeDeBaza();

    void setMaterialeNecesare(string * materiale_necesare,int nr_materiale);
    string* getMaterialeNecesare();

    int operator+(const TipuriSport &a);//adun nr_premii_valoroase_ale_clubului
    int operator*(const TipuriSport &a);//inmultesc numarul de materiale
    bool operator <=(const TipuriSport& a);//compar numarul de materiale
    bool operator <(const TipuriSport& a)const;
    bool operator ==(const TipuriSport& a);//pentru nume sport
    string operator [](int index);//pentru vectorul de materiale necesare

    friend TipuriSport operator+(const Sala&sala,const TipuriSport&sport);
    friend TipuriSport operator+(TipuriSport sport,const Sala&sala);
    TipuriSport operator-(const Sala&sala);

    void cel_mai_bun_loc_in_clasament();
};

void TipuriSport::cel_mai_bun_loc_in_clasament()//calculez care este cea mai buna pozitie obtinuta in clasamentul celor mai populare sporturi si vad cati ani consecutivi a ramas pe acea pozitie
{
    int mini,lungime_timp_cel_mai_bun_loc,lmax;

    mini=this->poz_sporturi_populare_pe_ani[0];//pozitia minima
    lungime_timp_cel_mai_bun_loc=0;
    lmax=0;//lungimea maxima
    for(int i=1; i<this->numarul_anilor; i++)
    {
        if(this->poz_sporturi_populare_pe_ani[i]<mini)
            mini=this->poz_sporturi_populare_pe_ani[i];//aflu minimul
    }
    for(int i=0; i<this->numarul_anilor; i++)
    {
        if(this->poz_sporturi_populare_pe_ani[i]==mini)
            lungime_timp_cel_mai_bun_loc++;//cresc lungimea cand vad ca e egal cu mini
        else
            lungime_timp_cel_mai_bun_loc=0;//daca nu este egal cu mini atunci lungimea ia valoarea 0
        if(lungime_timp_cel_mai_bun_loc>lmax)
            lmax=lungime_timp_cel_mai_bun_loc;
    }
    cout<<"Cel mai bun loc ocupat de acest sport este: locul "<<mini;
    if(lmax==1)//adica doar un an a stat pe acea pozitie
    {
        cout<<", fiind ocupat doar pentru "<<lmax<<" an.";
    }
    else if(lmax>1)
    {
        cout<<", iar perioada maxima in care a ramas pe acest loc este de "<<lmax<<" ani.";
    }

}

TipuriSport operator+(TipuriSport sport,const Sala&sala)
{
    Sala* lsali;
    lsali= new Sala[sport.numar_sali];
    for(int i=0; i<sport.numar_sali; i++)
        lsali[i]=sport.sali[i];
    if(sport.sali!=NULL)
        delete[]sport.sali;

    sport.numar_sali++;
    sport.sali=new Sala[sport.numar_sali];
    for(int i=0; i<sport.numar_sali-1; i++)
        sport.sali[i]=lsali[i];
    sport.sali[sport.numar_sali-1]=sala;
    return sport;
}
TipuriSport operator+(const Sala&sala,const TipuriSport&sport)
{
    TipuriSport auxiliar(sport);
    Sala* lsali;
    lsali= new Sala[auxiliar.numar_sali];
    for(int i=0; i<auxiliar.numar_sali; i++)
        lsali[i]=auxiliar.sali[i];
    if(auxiliar.sali!=NULL)
        delete[]auxiliar.sali;

    auxiliar.numar_sali++;
    auxiliar.sali=new Sala[auxiliar.numar_sali];
    for(int i=0; i<auxiliar.numar_sali-1; i++)
        auxiliar.sali[i]=lsali[i];
    auxiliar.sali[auxiliar.numar_sali-1]=sala;
    return auxiliar;
}
TipuriSport TipuriSport::operator-(const Sala&sala)
{
    int poz=0;
    Sala* lsali;
    lsali=new Sala[this->numar_sali];
    for(int i=0; i<this->numar_sali; i++)
    {

        lsali[i]=this->sali[i];
        if(this->sali[i]==sala)
            poz++;
    }
    if(this->sali!=NULL)
        delete[] this->sali;

    int j=0;
    this->sali=new Sala[this->numar_sali-poz];
    int i=0;
    while(i<this->numar_sali)
    {
        if(lsali[i]==sala)
            i++;
        else
        {
            this->sali[j]=lsali[i];
            j++;
            i++;

        }

    }
    this->numar_sali=this->numar_sali-poz;
    return *this;


}
string TipuriSport:: operator [](int index)
{
    if(0<=index && index< this->nr_materiale)
        return materiale_necesare[index];
    else
        return "eroare";
}

bool TipuriSport::operator ==(const TipuriSport& a)//doua sporturi sunt egale daca au acelasi nume
{
    if(this->nume_sport==a.nume_sport)
        return true;
    return false;
}
bool TipuriSport:: operator <=(const TipuriSport& a)
{
    if(this->nr_materiale<a.nr_materiale)
        return true;
    return false;
}
bool TipuriSport:: operator <(const TipuriSport& a)const
{
    return pret_materiale_de_baza< a.pret_materiale_de_baza;
}
int TipuriSport::operator*(const TipuriSport &a)
{
    TipuriSport aux(*this);
    aux.nr_materiale=aux.nr_materiale*a.nr_materiale;
    return aux.getNrMateriale();
}

int TipuriSport:: operator+(const TipuriSport &a)
{
    TipuriSport aux(*this);
    aux.nr_premii_valoroase_ale_clubului=aux.nr_premii_valoroase_ale_clubului+a.nr_premii_valoroase_ale_clubului;
    return aux.getNrPremiiValoroaseAleClubului();
}

ostream& operator<<(ostream& out, const TipuriSport& sportul)
{
    out<<"\nNumele sportului este: "<<sportul.nume_sport;

    if(sportul.echipa==1)
        out<<"\nEste sport de echipa.";
    else
        out<<"\nNu este sport de echipa.";

    if(sportul.dificultate=='S')
    {
        out<<"\nGradul de dificultate al acestui sport este scazut.";
    }
    else if(sportul.dificultate=='M')
    {
        out<<"\nGradul de dificultate al acestui sport este mediu.";
    }
    else if(sportul.dificultate=='R')
    {
        out<<"\nGradul de dificultate al acestui sport este ridicat.";
    }

    out<<"\nNumarul de premii valoroase castigate de sportivii clubului la aceasta sectie este de "<<sportul.nr_premii_valoroase_ale_clubului;
    if(sportul.numarul_anilor!=0)
    {
        out<<"\nIn ultimii "<<sportul.numarul_anilor;
        if(sportul.numarul_anilor==1)
        {
            out<<" an acest sport a ocupat: ";
        }
        else
        {
            out<<" ani acest sport a ocupat: ";
        }

        out<<"locul "<<sportul.poz_sporturi_populare_pe_ani[0];
        for(int i=1; i<sportul.numarul_anilor; i++)
            out<<", locul "<<sportul.poz_sporturi_populare_pe_ani[i];
        out<<" in clasamentul celor mai populare sporturi.";
    }

    out<<"\nPentru acest sport sunt necesare "<<sportul.nr_materiale<<" materiale, precum: ";
    if(sportul.nr_materiale!=0)
    {
        out<<sportul.materiale_necesare[0];
        for(int i=1; i<sportul.nr_materiale; i++)
            out<<", "<<sportul.materiale_necesare[i];
        out<<".";
    }

    out<<"\nPretul pentru materialele de baza la un loc este de: "<<sportul.pret_materiale_de_baza;

    out<<"\nNumarul salilor actuale in care se desfasoara acest tip de sport este in numar de: "<<sportul.numar_sali;
    if(sportul.numar_sali!=0)
    {
        out<<"\n\nSalile in care se desfasoara acest tip de sport sunt:\n\n";
        for(int i=0; i<sportul.numar_sali; i++)
        {
            out<<"Nume sala: "<<sportul.sali[i].getNumeSala()<<"   Locatie: "<<sportul.sali[i].getLocatie()<<"   Renovarea: ";
            if(sportul.sali[i].getRenovat()==1)
                {out<<"este renovata"<<endl<<"    Numarul antrenorilor care lucreaza in aceasta sala, dar care nu au calificarea sa antreneze sportivi pentru olimpiada: "<<sportul.sali[i].getNrAntrenori()<<endl<<"    Numarul antrenorilor care lucreaza in aceasta sala, dar care au calificarea sa antreneze sportivi pentru olimpiada: "<<sportul.sali[i].getNrAntrenoriOlimpici()<<"\n";
                }
            else
                {out<<"nu este renovata"<<endl<<"    Numarul antrenorilor care lucreaza in aceasta sala, dar care nu au calificarea sa antreneze sportivi pentru olimpiada: "<<sportul.sali[i].getNrAntrenori()<<endl<<"    Numarul antrenorilor care lucreaza in aceasta sala, dar care au calificarea sa antreneze sportivi pentru olimpiada: "<<sportul.sali[i].getNrAntrenoriOlimpici()<<"\n";
                }
        }
    }

    return out;
}
istream& operator>>(istream& in,TipuriSport& sportul)
{
    cout<<"\nNume sport [Dans/Inot/Triathlon/Atletism/Ciclism]: ";
    in>>sportul.nume_sport;

    cout<<"\nEste sport de echipa [1-true/0-false]: ";
    in>>sportul.echipa;

    cout<<"\nGradul de dificultate ['S'-scazut/'M'-mediu/'R'-ridicat]: ";
    in>>sportul.dificultate;

    cout<<"\nNumarul de premii valoroase castigate de sportivii clubului la aceasta sectie: ";
    in>>sportul.nr_premii_valoroase_ale_clubului;

    cout<<"\nNumarul anilor pentru care vreau sa stiu ce pozitii a ocupat acest sport in clasamentul celor mai populare sporturi: ";
    in>>sportul.numarul_anilor;

    cout<<"\nPozitiile ocupate in clasamentul celor mai populare sporturi pentru numarul de ani mentionat anterior: ";
    if(sportul.poz_sporturi_populare_pe_ani!=NULL)
        delete [] sportul.poz_sporturi_populare_pe_ani;
    sportul.poz_sporturi_populare_pe_ani = new int [sportul.numarul_anilor];
    for (int i=0; i<sportul.numarul_anilor; i++)
        in>>sportul.poz_sporturi_populare_pe_ani[i];

    cout<<"\nNumarul de materiale necesare acestui sport: ";
    in>>sportul.nr_materiale;

    cout<<"\nTipurile de materiale necesare [daca un material are mai multe cuvinte se vor scrie unite prin caracterul _ ]: ";
    if(sportul.materiale_necesare !=NULL )
        delete [] sportul.materiale_necesare;
    sportul.materiale_necesare= new string [sportul.nr_materiale];
    for(int i=0; i<sportul.nr_materiale; i++)
        in>>sportul.materiale_necesare[i];

    cout<<"\nPretul total al materialelor de baza: ";
    in>>sportul.pret_materiale_de_baza;

    return in;
}

TipuriSport::TipuriSport()//constructor fara parametrii
{
    nume_sport="necunoscut";
    echipa=false;
    dificultate='0';
    numarul_anilor=0;
    poz_sporturi_populare_pe_ani=NULL;
    nr_premii_valoroase_ale_clubului=0;
    nr_materiale=0;
    pret_materiale_de_baza=0.0;
    materiale_necesare=NULL;
    numar_sali=0;
    sali=NULL;
}

TipuriSport:: TipuriSport(Sala* sali, int numar_sali,string nume_sport,bool echipa,char dificultate,int numarul_anilor,int* poz_sporturi_populare_pe_ani,int nr_premii_valoroase_ale_clubului,int nr_materiale,float pret_materiale_de_baza,string * materiale_necesare)
{
    this->nume_sport=nume_sport;
    this->echipa=echipa;
    this->dificultate=dificultate;
    this->numarul_anilor=numarul_anilor;

    this->poz_sporturi_populare_pe_ani= new int[numarul_anilor];
    for(int i=0; i<numarul_anilor; i++)
        this->poz_sporturi_populare_pe_ani[i]=poz_sporturi_populare_pe_ani[i];

    this->nr_premii_valoroase_ale_clubului=nr_premii_valoroase_ale_clubului;
    this->nr_materiale=nr_materiale;
    this->pret_materiale_de_baza=pret_materiale_de_baza;

    this->materiale_necesare=new string [nr_materiale];
    for (int i=0; i<nr_materiale; i++)
        this->materiale_necesare[i]=materiale_necesare[i];

    this->numar_sali=numar_sali;

    this->sali=new Sala[numar_sali];
    for(int i=0; i<numar_sali; i++)
        this->sali[i]=sali[i];

}
TipuriSport:: TipuriSport(Sala* sali, int numar_sali,string nume_sport,bool echipa,char dificultate,float pret_materiale_de_baza,int nr_materiale,string* materiale_necesare)
{
    this->nume_sport=nume_sport;
    this->echipa=echipa;
    this->dificultate=dificultate;
    this->nr_materiale=nr_materiale;
    this->pret_materiale_de_baza=pret_materiale_de_baza;

    this->materiale_necesare=new string [nr_materiale];
    for (int i=0; i<nr_materiale; i++)
        this->materiale_necesare[i]=materiale_necesare[i];

    this->numar_sali=numar_sali;

    this->sali=new Sala[numar_sali];
    for(int i=0; i<numar_sali; i++)
        this->sali[i]=sali[i];

    numarul_anilor=0;
    poz_sporturi_populare_pe_ani=NULL;
    nr_premii_valoroase_ale_clubului=0;

}
TipuriSport::TipuriSport(const TipuriSport& sport)//copy constructor
{
    this->nume_sport=sport.nume_sport;
    this->echipa=sport.echipa;
    this->dificultate=sport.dificultate;
    this->numarul_anilor=sport.numarul_anilor;

    this->poz_sporturi_populare_pe_ani= new int[sport.numarul_anilor];
    for(int i=0; i<sport.numarul_anilor; i++)
        this->poz_sporturi_populare_pe_ani[i]=sport.poz_sporturi_populare_pe_ani[i];

    this->nr_premii_valoroase_ale_clubului=sport.nr_premii_valoroase_ale_clubului;
    this->nr_materiale=sport.nr_materiale;
    this->pret_materiale_de_baza=sport.pret_materiale_de_baza;

    this->materiale_necesare=new string [sport.nr_materiale];
    for (int i=0; i<sport.nr_materiale; i++)
        this->materiale_necesare[i]=sport.materiale_necesare[i];

    this->numar_sali=sport.numar_sali;

    this->sali=new Sala[sport.numar_sali];
    for(int i=0; i<sport.numar_sali; i++)
        this->sali[i]=sport.sali[i];

}
TipuriSport& TipuriSport:: operator=(const TipuriSport& sport)//operator = supraincarcat
{
    if(this != &sport)
    {
        if(this->poz_sporturi_populare_pe_ani !=NULL)
            delete [] this->poz_sporturi_populare_pe_ani;
        if(this->materiale_necesare !=NULL)
            delete [] this->materiale_necesare;
        if(this->sali !=NULL)
            delete [] this->sali;

        this->nume_sport=sport.nume_sport;
        this->echipa=sport.echipa;
        this->dificultate=sport.dificultate;
        this->numarul_anilor=sport.numarul_anilor;

        this->poz_sporturi_populare_pe_ani= new int[sport.numarul_anilor];
        for(int i=0; i<sport.numarul_anilor; i++)
            this->poz_sporturi_populare_pe_ani[i]=sport.poz_sporturi_populare_pe_ani[i];

        this->nr_premii_valoroase_ale_clubului=sport.nr_premii_valoroase_ale_clubului;
        this->nr_materiale=sport.nr_materiale;
        this->pret_materiale_de_baza=sport.pret_materiale_de_baza;

        this->materiale_necesare=new string [sport.nr_materiale];
        for (int i=0; i<sport.nr_materiale; i++)
            this->materiale_necesare[i]=sport.materiale_necesare[i];

        this->numar_sali=sport.numar_sali;

        this->sali=new Sala[sport.numar_sali];
        for(int i=0; i<sport.numar_sali; i++)
            this->sali[i]=sport.sali[i];

    }
    return *this;
}
TipuriSport::~TipuriSport()//destructor
{
    if(this->poz_sporturi_populare_pe_ani !=NULL)
        delete [] this->poz_sporturi_populare_pe_ani;
    if(this->materiale_necesare !=NULL)
        delete [] this->materiale_necesare;
    if(this->sali !=NULL)
        delete [] this->sali;
}

int TipuriSport::getNumarSali()
{
    return this->numar_sali;
}

Sala* TipuriSport::getSala()
{
    return this->sali;
}

string TipuriSport:: getNumeSport()const
{
    return this->nume_sport;
}

bool TipuriSport::getEchipa()
{
    return this->echipa;
}

char TipuriSport::getDificultate()
{
    return this->dificultate;
}

int TipuriSport:: getNumarulAnilor()
{
    return this->numarul_anilor;
}

void TipuriSport:: setPozSporturiPopularePeAn(int * poz_sporturi_populare_pe_ani,int numarul_anilor)
{
    this->numarul_anilor=numarul_anilor;
    if(this->poz_sporturi_populare_pe_ani!=NULL)
        delete [] this->poz_sporturi_populare_pe_ani;
    this->poz_sporturi_populare_pe_ani= new int[numarul_anilor];
    for(int i=0; i<numarul_anilor; i++)
        this->poz_sporturi_populare_pe_ani[i]=poz_sporturi_populare_pe_ani[i];
}

int * TipuriSport:: getPozSporturiPopularePeAn()
{
    return this->poz_sporturi_populare_pe_ani;
}


void TipuriSport::setNrPremiiValoroaseAleClubului(int nr_premii_valoroase_ale_clubului)
{
    this ->nr_premii_valoroase_ale_clubului=nr_premii_valoroase_ale_clubului;
}

int TipuriSport:: getNrPremiiValoroaseAleClubului()
{
    return this ->nr_premii_valoroase_ale_clubului;
}

int TipuriSport:: getNrMateriale()
{
    return this->nr_materiale;
}

float TipuriSport::getPretMaximMaterialeDeBaza()
{
    return this->pret_materiale_de_baza;
}

void TipuriSport::setMaterialeNecesare(string * materiale_necesare,int nr_materiale)
{
    this->nr_materiale=nr_materiale;
    if (this->materiale_necesare!=NULL)
        delete[] this->materiale_necesare;
    this->materiale_necesare=new string [nr_materiale];
    for (int i=0; i<nr_materiale; i++)
        this->materiale_necesare[i]=materiale_necesare[i];

}

string * TipuriSport:: getMaterialeNecesare()
{
    return this->materiale_necesare;
}

class Incasari//interfata
{
public:
    virtual void consum()=0;
};
class Abonament:public Incasari
{
protected:
    string nume_sport;
    int durata_abonament;
    float pret_o_sedinta;
public:
    Abonament();//constructor fara parametrii
    Abonament(string nume_sport,int durata_abonament,float pret_o_sedinta);//constructor cu toti parametrii
    Abonament (const Abonament&abon);//copy constructor
    Abonament& operator=(const Abonament& abon);//supraincarcarea operatorului egal
    virtual ~Abonament();
    virtual float preturi()=0;

    virtual ostream& Afisare(ostream& out)const;//facem citirea virtuala
    virtual istream& Citire(istream& in);//facem afisarea virtuala

    friend istream& operator>>(istream&in, Abonament& abonam);
    friend ostream& operator<<(ostream&out,const Abonament&abonam);

    string getNumeSport();
    int getDurataAbonament();

};
int Abonament::getDurataAbonament()
{
    return this->durata_abonament;
}
string Abonament::getNumeSport()
{
    return this->nume_sport;
}
Abonament::Abonament()
{
    this->nume_sport="Nestiut";
    this->durata_abonament=0;
    this->pret_o_sedinta=0.0;
}
Abonament::Abonament(string nume_sport,int durata_abonament,float pret_o_sedinta)
{
    this->nume_sport=nume_sport;
    this->durata_abonament=durata_abonament;
    this->pret_o_sedinta=pret_o_sedinta;
}
Abonament&Abonament::operator=(const Abonament&abon)
{
    if(this!=&abon)
    {
        this->nume_sport=abon.nume_sport;
        this->durata_abonament=abon.durata_abonament;
        this->pret_o_sedinta=abon.pret_o_sedinta;
    }
    return *this;
}
Abonament::Abonament(const Abonament&abon)
{
    this->nume_sport=abon.nume_sport;
    this->durata_abonament=abon.durata_abonament;
    this->pret_o_sedinta=abon.pret_o_sedinta;
}
ostream& Abonament::Afisare(ostream& out)const
{
    out<<"\nAcest abonament este dedicat sportului: "<<nume_sport;
    out<<"\nDurata abonamentului este de: "<<durata_abonament<<" zile";
    out<<"\nPretul pe o sedinta este de: "<<pret_o_sedinta<<" lei";
    return out;
}
istream& Abonament:: Citire(istream& in)
{
    cout<<"\nSportul dedicat acestui abonament este [Dans/Inot/Ciclism/Atletism/Triathlon]: ";
    in>>this->nume_sport;
    cout<<"\nDurata abonamentului este de [in zile]: ";
    in>>this->durata_abonament;
    cout<<"\nPretul pe o sedinta este de[in lei]: ";
    in>>this->pret_o_sedinta;
    return in;
}
istream& operator>>(istream&in, Abonament& abonam)
{
    return abonam.Citire(in);
}
ostream& operator<<(ostream&out,const Abonament&abonam)
{
    return abonam.Afisare(out);
}
Abonament::~Abonament()
{}
class AbonamentInot:public Abonament
{
private:
    float pret_inchiriere_prosop;
    float pret_inchiriere_halat;
    float pret_inchiriere_elemente_auxiliare;//toate aceste preturi nu se vor modifica, din momentul in care sunt introduse raman asa
public:
    AbonamentInot();//constructor fara parametrii
    AbonamentInot(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_inchiriere_prosop,float pret_inchiriere_halat,float pret_inchiriere_elemente_auxiliare);
    AbonamentInot(const AbonamentInot&aboninot);//copy constructor
    AbonamentInot& operator=(const AbonamentInot&aboninot);//supraincarcarea operatorului egal
    ~AbonamentInot();//destructor
    virtual ostream& Afisare(ostream&out)const;
    virtual istream&Citire(istream& in);
    virtual void consum();
    virtual float preturi();

};
void AbonamentInot::consum()//acest consum este afisat pentru a vedea persoana respectiva cat are de dat daca vrea sa inchirieza aceste produse
{
    float consum_inot_total;
    consum_inot_total=this->pret_inchiriere_elemente_auxiliare+this->pret_inchiriere_halat+this->pret_inchiriere_prosop;
    cout<<"\nDaca alegeti sa inchiriati un halat veti avea de platit: "<<this->pret_inchiriere_halat<<" lei";
    cout<<"\nDaca alegeti sa inchiriati un prosop veti avea de platit: "<<this->pret_inchiriere_prosop<<" lei";
    cout<<"\nDaca alegeti sa inchiriati elemente auxiliare veti avea de platit: "<<this->pret_inchiriere_elemente_auxiliare<<" lei";
    cout<<"\nDaca alegeti sa inchiriati un halat si un prosop veti avea de platit: "<<this->pret_inchiriere_halat+this->pret_inchiriere_prosop<<" lei";
    cout<<"\nDaca alegeti sa inchiriati un halat si elemente auxiliare veti avea de platit: "<<this->pret_inchiriere_halat+this->pret_inchiriere_elemente_auxiliare<<" lei";
    cout<<"\nDaca alegeti sa inchiriati un prosop si elemente auxiliare veti avea de platit: "<<this->pret_inchiriere_prosop+this->pret_inchiriere_elemente_auxiliare<<" lei";
    cout<<"\nDaca alegeti sa inchiriati un halat, un prosop si elemente auxiliare veti avea de platit: "<<consum_inot_total<<" lei";

}
float AbonamentInot::preturi()
{
    float pret_abonament_inot;
    pret_abonament_inot=(this->pret_o_sedinta-0.3*this->pret_o_sedinta)*this->durata_abonament;
    return pret_abonament_inot;
}
AbonamentInot::AbonamentInot():Abonament()
{
    this->pret_inchiriere_elemente_auxiliare=0.0;
    this->pret_inchiriere_halat=0.0;
    this->pret_inchiriere_prosop=0.0;
}
AbonamentInot::AbonamentInot(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_inchiriere_prosop,float pret_inchiriere_halat,float pret_inchiriere_elemente_auxiliare):Abonament(nume_sport,durata_abonament,pret_o_sedinta)
{
    this->pret_inchiriere_elemente_auxiliare=pret_inchiriere_elemente_auxiliare;
    this->pret_inchiriere_halat=pret_inchiriere_halat;
    this->pret_inchiriere_prosop=pret_inchiriere_prosop;
}
AbonamentInot::AbonamentInot(const AbonamentInot&aboninot):Abonament(aboninot)
{
    this->pret_inchiriere_elemente_auxiliare=aboninot.pret_inchiriere_elemente_auxiliare;
    this->pret_inchiriere_halat=aboninot.pret_inchiriere_halat;
    this->pret_inchiriere_prosop=aboninot.pret_inchiriere_prosop;
}
AbonamentInot&AbonamentInot:: operator=(const AbonamentInot&aboninot)
{
    if(this!=&aboninot)
    {
        Abonament::operator=(aboninot);
        this->pret_inchiriere_elemente_auxiliare=aboninot.pret_inchiriere_elemente_auxiliare;
        this->pret_inchiriere_halat=aboninot.pret_inchiriere_halat;
        this->pret_inchiriere_prosop=aboninot.pret_inchiriere_prosop;
    }
    return *this;
}
AbonamentInot::~AbonamentInot()
{

}
ostream& AbonamentInot:: Afisare(ostream&out)const
{
    Abonament::Afisare(out);
    out<<"\nInchirierea unui prosop costa: "<<pret_inchiriere_prosop<< " lei.";
    out<<"\nInchirierea unui halat costa: "<<pret_inchiriere_halat<< " lei.";
    out<<"\nInchirierea unor elemente auxiliare de inot costa: "<<pret_inchiriere_elemente_auxiliare<< " lei.";
    return out;
}
istream& AbonamentInot::Citire(istream& in)
{
    Abonament::Citire(in);
    cout<<"\nInchirierea unui prosop costa[in lei]: ";
    in>>this->pret_inchiriere_prosop;
    cout<<"\nInchirierea unui halat costa[in lei]: ";
    in>>this->pret_inchiriere_halat;
    cout<<"\nInchirierea unor elemente auxiliare de inot costa[in lei]: ";
    in>>this->pret_inchiriere_elemente_auxiliare;
    return in;
}
class AbonamentDans:public Abonament
{
private:
    float pret_inchiriere_incaltari;
    float pret_inchiriere_accesorii;

public:
    AbonamentDans();//constructor fara parametrii
    AbonamentDans(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_inchiriere_incaltari,float pret_inchiriere_accesorii);
    AbonamentDans(const AbonamentDans&abondans);//copy constructor
    AbonamentDans& operator=(const AbonamentDans&abondasn);//supraincarcarea operatorului egal
    ~AbonamentDans();//destructor
    virtual ostream& Afisare(ostream&out)const;
    virtual istream&Citire(istream& in);
    virtual void consum();
    virtual float preturi();

};
void AbonamentDans::consum()//acest consum este afisat pentru a vedea persoana respectiva cat are de dat daca vrea sa inchirieza aceste produse
{
    float consum_dans_total;
    consum_dans_total=this->pret_inchiriere_incaltari+this->pret_inchiriere_accesorii;
    cout<<"\nDaca alegeti sa inchiriati o pereche de incaltari veti avea de platit: "<<this->pret_inchiriere_incaltari<<" lei";
    cout<<"\nDaca alegeti sa inchiriati accesorii veti avea de platit: "<<this->pret_inchiriere_accesorii<<" lei";
    cout<<"\nDaca alegeti sa inchiriati o pereche de incaltari si accesorii veti avea de platit: "<<consum_dans_total<<" lei";

}
float AbonamentDans::preturi()
{
    float pret_abonament_dans;
    pret_abonament_dans=(this->pret_o_sedinta-0.5*this->pret_o_sedinta)*this->durata_abonament;
    return pret_abonament_dans;
}
AbonamentDans::AbonamentDans():Abonament()
{
    this->pret_inchiriere_accesorii=0.0;
    this->pret_inchiriere_incaltari=0.0;
}
AbonamentDans::AbonamentDans(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_inchiriere_accesorii,float pret_inchiriere_incaltari):Abonament(nume_sport,durata_abonament,pret_o_sedinta)
{
    this->pret_inchiriere_accesorii=pret_inchiriere_accesorii;
    this->pret_inchiriere_incaltari=pret_inchiriere_incaltari;
}
AbonamentDans::AbonamentDans(const AbonamentDans&abondans):Abonament(abondans)
{
    this->pret_inchiriere_accesorii=abondans.pret_inchiriere_accesorii;
    this->pret_inchiriere_incaltari=abondans.pret_inchiriere_incaltari;
}
AbonamentDans&AbonamentDans:: operator=(const AbonamentDans&abondans)
{
    if(this!=&abondans)
    {
        Abonament::operator=(abondans);
        this->pret_inchiriere_accesorii=abondans.pret_inchiriere_accesorii;
        this->pret_inchiriere_incaltari=abondans.pret_inchiriere_incaltari;

    }
    return *this;
}
AbonamentDans::~AbonamentDans()//destructor
{

}
ostream& AbonamentDans:: Afisare(ostream&out)const
{
    Abonament::Afisare(out);
    out<<"\nInchirierea unor accesorii costa: "<<pret_inchiriere_accesorii<< " lei.";
    out<<"\nInchirierea unei perechi de incaltaminte costa: "<<pret_inchiriere_incaltari<< " lei.";
    return out;
}
istream& AbonamentDans::Citire(istream& in)
{
    Abonament::Citire(in);
    cout<<"\nInchirierea unor accesorii costa[in lei]: ";
    in>>this->pret_inchiriere_accesorii;
    cout<<"\nInchirierea unei perechi de incaltaminte costa[in lei]: ";
    in>>this->pret_inchiriere_incaltari;
    return in;
}
class AbonamentCiclism:public Abonament
{
private:
    float pret_umflare_roti;
    float pret_serviciu_reparare_pana;
public:
    AbonamentCiclism();//constructor fara paramtrii
    AbonamentCiclism(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_umflare_roti,float pret_serviciu_reparare_pana);//constructor cu toti parametrii
    AbonamentCiclism(const AbonamentCiclism&aboncicl);//copyconstructor
    AbonamentCiclism &operator=(const AbonamentCiclism&aboncicl);//supraincarcarea operatorului =
    ~AbonamentCiclism();//destructor
    virtual ostream& Afisare(ostream&out)const;//afisare virtuala
    virtual istream&Citire(istream& in);//citire virtuala
    virtual void consum();
    virtual float preturi();
};
AbonamentCiclism::AbonamentCiclism():Abonament()
{
    this->pret_umflare_roti=0.0;
    this->pret_serviciu_reparare_pana=0.0;
}
AbonamentCiclism::AbonamentCiclism(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_umflare_roti,float pret_serviciu_reparare_pana):Abonament(nume_sport,durata_abonament,pret_o_sedinta)
{
    this->pret_umflare_roti=pret_umflare_roti;
    this->pret_serviciu_reparare_pana=pret_serviciu_reparare_pana;
}
AbonamentCiclism::AbonamentCiclism(const AbonamentCiclism&aboncicl):Abonament(aboncicl)
{
    this->pret_umflare_roti=aboncicl.pret_umflare_roti;
    this->pret_serviciu_reparare_pana=aboncicl.pret_serviciu_reparare_pana;
}
AbonamentCiclism &AbonamentCiclism::operator=(const AbonamentCiclism&aboncicl)
{
    if(this!=&aboncicl)
    {
        Abonament::operator=(aboncicl);
        this->pret_umflare_roti=aboncicl.pret_umflare_roti;
        this->pret_serviciu_reparare_pana=aboncicl.pret_serviciu_reparare_pana;
    }
    return *this;
}
AbonamentCiclism::~AbonamentCiclism()
{

}
void AbonamentCiclism::consum()//imi afiseaza ce cheltuieli ar putea face
{
    float consum_ciclism_total;
    consum_ciclism_total=this->pret_umflare_roti+this->pret_serviciu_reparare_pana;
    cout<<"\nDaca alegeti sa apelati la serviciul de umflare de roti veti avea de platit: "<<this->pret_umflare_roti<<" lei";
    cout<<"\nDaca alegeti sa va reparati pana de la bicicleta veti avea de platit: "<<this->pret_serviciu_reparare_pana<<" lei";
    cout<<"\nDaca alegeti sa va reparati pana de la bicicleta si sa va umflati si rotile veti avea de platit: "<<consum_ciclism_total<<" lei";
}
float AbonamentCiclism::preturi()//calculeaza pretul abonamentului
{
    float pret_abonament_ciclism;
    pret_abonament_ciclism=(this->pret_o_sedinta-0.2*this->pret_o_sedinta)*this->durata_abonament;
    return pret_abonament_ciclism;
}
ostream& AbonamentCiclism:: Afisare(ostream&out)const
{
    Abonament::Afisare(out);
    out<<"\nServiciul de umflare roti costa: "<<pret_umflare_roti<< " lei.";
    out<<"\nServiciul de reparare pana costa: "<<pret_serviciu_reparare_pana<< " lei.";
    return out;
}
istream& AbonamentCiclism::Citire(istream& in)
{
    Abonament::Citire(in);
    cout<<"\nServiciul de umflare roti costa:[in lei]: ";
    in>>this->pret_umflare_roti;
    cout<<"\nServiciul de reparare pana costa[in lei]: ";
    in>>this->pret_serviciu_reparare_pana;
    return in;
}
class AbonamentTriathlon:public Abonament
{
private:
    float pret_inchiriere_baliza_inot_apelibere;
    float pret_inchiriere_compresoare;
    float pret_inchiriere_centura_puls;
public:
    AbonamentTriathlon();//constructor fara parametrii
    AbonamentTriathlon(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_inchiriere_baliza_inot_apelibere,float pret_inchiriere_centura_puls,float pret_inchiriere_compresoare);
    AbonamentTriathlon(const AbonamentTriathlon& abontri);//copy constructor
    AbonamentTriathlon &operator=(const AbonamentTriathlon& abontri);//supraincarcarea op =
    ~AbonamentTriathlon();//destructor
    virtual ostream& Afisare(ostream&out)const;//afisare virtuala
    virtual istream&Citire(istream& in);//citire virtuala
    virtual void consum();
    virtual float preturi();
};
void AbonamentTriathlon::consum()//acest consum este afisat pentru a vedea persoana respectiva cat are de dat daca vrea sa inchirieza aceste produse
{
    float consum_triathlon_total;
    consum_triathlon_total=this->pret_inchiriere_baliza_inot_apelibere+this->pret_inchiriere_centura_puls+this->pret_inchiriere_compresoare;
    cout<<"\nDaca alegeti sa inchiriati o baliza pentru inotat in ape libere veti avea de platit: "<<this->pret_inchiriere_baliza_inot_apelibere<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o centura de puls veti avea de platit: "<<this->pret_inchiriere_centura_puls<<" lei";

    cout<<"\nDaca alegeti sa inchiriati compresoare pentru brate sau picioare veti avea de platit: "<<this->pret_inchiriere_compresoare<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o baliza pentru inotat in ape libere si o centura de puls veti avea de platit: "<<this->pret_inchiriere_baliza_inot_apelibere+this->pret_inchiriere_centura_puls<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o baliza pentru inotat in ape libere si compresoare pentru brate sau picioare veti avea de platit: "<<this->pret_inchiriere_baliza_inot_apelibere+this->pret_inchiriere_compresoare<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o centura de puls si compresoare pentru brate sau picioare veti avea de platit: "<<this->pret_inchiriere_centura_puls+this->pret_inchiriere_compresoare<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o baliza pentru inotat in ape libere, compresoare pentru brate sau picioare si o centura de puls veti avea de platit: "<<consum_triathlon_total<<" lei";

}
float AbonamentTriathlon::preturi()//calculeaza pretul abonamentului
{
    float pret_abonament_triathlon;
    pret_abonament_triathlon=(this->pret_o_sedinta-0.1*this->pret_o_sedinta)*this->durata_abonament;
    return pret_abonament_triathlon;
}
AbonamentTriathlon::AbonamentTriathlon():Abonament()
{
    this-> pret_inchiriere_baliza_inot_apelibere=0.0;
    this-> pret_inchiriere_compresoare=0.0;
    this->pret_inchiriere_centura_puls=0.0;
}
AbonamentTriathlon::AbonamentTriathlon(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_inchiriere_baliza_inot_apelibere,float pret_inchiriere_centura_puls,float pret_inchiriere_compresoare):Abonament(nume_sport,durata_abonament,pret_o_sedinta)
{
    this-> pret_inchiriere_baliza_inot_apelibere=pret_inchiriere_baliza_inot_apelibere;
    this-> pret_inchiriere_compresoare=pret_inchiriere_compresoare;
    this->pret_inchiriere_centura_puls=pret_inchiriere_centura_puls;
}
AbonamentTriathlon::AbonamentTriathlon(const AbonamentTriathlon& abontri):Abonament(abontri)
{
    this-> pret_inchiriere_baliza_inot_apelibere=abontri.pret_inchiriere_baliza_inot_apelibere;
    this-> pret_inchiriere_compresoare=abontri.pret_inchiriere_compresoare;
    this->pret_inchiriere_centura_puls=abontri.pret_inchiriere_centura_puls;
}
AbonamentTriathlon&AbonamentTriathlon:: operator=(const AbonamentTriathlon& abontri)
{
    if(this!=&abontri)
    {
        Abonament::operator=(abontri);
        this-> pret_inchiriere_baliza_inot_apelibere=abontri.pret_inchiriere_baliza_inot_apelibere;
        this-> pret_inchiriere_compresoare=abontri.pret_inchiriere_compresoare;
        this->pret_inchiriere_centura_puls=abontri.pret_inchiriere_centura_puls;

    }
    return *this;
}
AbonamentTriathlon::~AbonamentTriathlon()
{

}
ostream& AbonamentTriathlon:: Afisare(ostream&out)const
{
    Abonament::Afisare(out);
    out<<"\nInchirierea unei balize de inot pentru ape libere costa: "<<pret_inchiriere_baliza_inot_apelibere<< " lei.";
    out<<"\nInchirierea unei centuri de puls costa: "<<pret_inchiriere_centura_puls<< " lei.";
    out<<"\nInchirierea unor compresoare pentru brate sau picioare costa: "<<pret_inchiriere_compresoare<< " lei.";
    return out;
}
istream& AbonamentTriathlon::Citire(istream& in)
{
    Abonament::Citire(in);
    cout<<"\nInchirierea unei balize de inot pentru ape libere costa[in lei]: ";
    in>>this->pret_inchiriere_baliza_inot_apelibere;
    cout<<"\nInchirierea unei centuri de puls costa[in lei]: ";
    in>>this->pret_inchiriere_centura_puls;
    cout<<"\nInchirierea unor compresoare pentru brate sau picioare costa[in lei]: ";
    in>>this->pret_inchiriere_compresoare;
    return in;
}
class AbonamentAtletism:public Abonament
{
private:
    float pret_inchiriere_greutati_incheieturaSAUglezna;
    float pret_inchiriere_coarda;
    float pret_inchiriere_trx;
public:
    AbonamentAtletism();//constructor fara parametrii
    AbonamentAtletism(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_inchiriere_coarda,float pret_inchiriere_greutati_incheieturaSAUglezna,float pret_inchiriere_trx);
    AbonamentAtletism(const AbonamentAtletism& abonatle);//copy constructor
    AbonamentAtletism &operator=(const AbonamentAtletism& abonatle);//supraincarcare operator =
    ~AbonamentAtletism();//destructor
    virtual ostream& Afisare(ostream&out)const;//afisare virtuala
    virtual istream&Citire(istream& in);//citire virtuala
    virtual void consum();
    virtual float preturi();
};
void AbonamentAtletism::consum()//acest consum este afisat pentru a vedea persoana respectiva cat are de dat daca vrea sa inchirieza aceste produse
{
    float consum_atletism_total;
    consum_atletism_total=this->pret_inchiriere_coarda+this->pret_inchiriere_greutati_incheieturaSAUglezna+this->pret_inchiriere_trx;
    cout<<"\nDaca alegeti sa inchiriati o coarda veti avea de platit: "<<this->pret_inchiriere_coarda<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o pereche de greutati pentru incheietura sau glezna veti avea de platit: "<<this->pret_inchiriere_greutati_incheieturaSAUglezna<<" lei";

    cout<<"\nDaca alegeti sa inchiriati un trx veti avea de platit: "<<this->pret_inchiriere_trx<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o coarda si o pereche de greutati pentru incheietura sau glezna veti avea de platit: "<<this->pret_inchiriere_coarda+this->pret_inchiriere_greutati_incheieturaSAUglezna<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o coarda si un trx veti avea de platit: "<<this->pret_inchiriere_coarda+this->pret_inchiriere_trx<<" lei";

    cout<<"\nDaca alegeti sa inchiriati un trx si o pereche de greutati pentru incheietura sau glezna veti avea de platit: "<<this->pret_inchiriere_trx+this->pret_inchiriere_greutati_incheieturaSAUglezna<<" lei";

    cout<<"\nDaca alegeti sa inchiriati o coarda, un trx si o pereche de greutati pentru incheietura sau glezna veti avea de platit: "<<consum_atletism_total<<" lei";

}
float AbonamentAtletism::preturi()//calculeaza pretul abonamentului
{
    float pret_abonament_atletism;
    pret_abonament_atletism=(this->pret_o_sedinta-0.4*this->pret_o_sedinta)*this->durata_abonament;
    return pret_abonament_atletism;
}
AbonamentAtletism::AbonamentAtletism():Abonament()
{
    this-> pret_inchiriere_coarda=0.0;
    this-> pret_inchiriere_greutati_incheieturaSAUglezna=0.0;
    this->pret_inchiriere_trx=0.0;
}
AbonamentAtletism::AbonamentAtletism(string nume_sport,int durata_abonament,float pret_o_sedinta,float pret_inchiriere_coarda,float pret_inchiriere_greutati_incheieturaSAUglezna,float pret_inchiriere_trx):Abonament(nume_sport,durata_abonament,pret_o_sedinta)
{
    this-> pret_inchiriere_coarda=pret_inchiriere_coarda;
    this-> pret_inchiriere_greutati_incheieturaSAUglezna=pret_inchiriere_greutati_incheieturaSAUglezna;
    this->pret_inchiriere_trx=pret_inchiriere_trx;
}
AbonamentAtletism::AbonamentAtletism(const AbonamentAtletism& abonatle):Abonament(abonatle)
{
    this-> pret_inchiriere_coarda=abonatle.pret_inchiriere_coarda;
    this-> pret_inchiriere_greutati_incheieturaSAUglezna=abonatle.pret_inchiriere_greutati_incheieturaSAUglezna;
    this->pret_inchiriere_trx=abonatle.pret_inchiriere_trx;

}
AbonamentAtletism&AbonamentAtletism:: operator=(const AbonamentAtletism& abonatle)
{
    if(this!=&abonatle)
    {
        Abonament::operator=(abonatle);
        this-> pret_inchiriere_coarda=abonatle.pret_inchiriere_coarda;
        this-> pret_inchiriere_greutati_incheieturaSAUglezna=abonatle.pret_inchiriere_greutati_incheieturaSAUglezna;
        this->pret_inchiriere_trx=abonatle.pret_inchiriere_trx;

    }
    return *this;
}
AbonamentAtletism::~AbonamentAtletism()
{

}
ostream& AbonamentAtletism:: Afisare(ostream&out)const
{
    Abonament::Afisare(out);
    out<<"\nInchirierea unei corzi costa: "<<pret_inchiriere_coarda<< " lei.";
    out<<"\nInchirierea unei perechi de greutati pentru incheietura sau glezna costa: "<<pret_inchiriere_greutati_incheieturaSAUglezna<< " lei.";
    out<<"\nInchirierea unui trx costa: "<<pret_inchiriere_trx<< " lei.";
    return out;
}
istream& AbonamentAtletism::Citire(istream& in)
{
    Abonament::Citire(in);
    cout<<"\nInchirierea unei corzi costa[in lei]: ";
    in>>this->pret_inchiriere_coarda;
    cout<<"\nInchirierea unei perechi de greutati pentru incheietura sau glezna costa[in lei]: ";
    in>>this->pret_inchiriere_greutati_incheieturaSAUglezna;
    cout<<"\nInchirierea unui trx costa[in lei]: ";
    in>>this->pret_inchiriere_trx;
    return in;
}
int main()
{
    //meniu interactiv
    set <TipuriSport> multimeSport;
    list <Sala> listaSala;
    list <Sportiv> listaSportivi;
    list <SportivLot> listaSportivilot;
    list <Antrenor> listaAntrenor;
    list <AntrenorOlimpici> listaAntrenorOl;
    map <string, vector <Abonament*>> mapAbonamente;
    int k=1;
    while (k==1)
    {
        cout<<"\n1 Sportiv\n";
        cout<<"\n2 Antrenor\n";
        cout<<"\n3 Sala in care se practica sport\n";
        cout<<"\n4 Tipuri de sport\n";
        cout<<"\n5 Abonament\n";
        cout<<"\n100 Iesiti din meniu\n";
        int comanda;
        cin>>comanda;
        switch(comanda)
        {
        case 1:
        {
            int k1;
            k1=1;
            while (k1==1)
            {//daca se modifica un sportiv se scoate din antrenor, se modifica si se pune la loc

                cout<<"\n4 Afiseaza un sportiv dat\n";
                cout<<"\n5 Introduceti un sportiv care nu face parte din lot\n";
                cout<<"\n6 Introduceti un sportiv care face parte din lot\n";

                cout<<"\n7 Schimba numele de familie al sportivului\n";
                cout<<"\n8 Schimba prenumele sportivului\n";
                cout<<"\n9 Daca s-a introdus gresit anul nasterii puteti modifica\n";
                cout<<"\n10 Schimba categoria din care face parte sportivul\n";
                cout<<"\n11 Daca s-a introdus gresit primul an in care a participat la concursuri puteti modifica\n";
                cout<<"\n12 Daca s-a introdus gresit genul sportivului puteti modifica\n";
                cout<<"\n13 Modificarea numarului de gustari (cand diferenta dintre ce primea si ce va primi esta mai mare sau ai mica decat 1)\n";
                cout<<"\n14 Modificarea rezultatelor obtinute\n";

                cout<<"\n15 Scade numarul de gustari primite la final de antrenament\n";
                cout<<"\n16 Scade numarul de gustari (la a doua afisare se observa modificarile)\n";
                cout<<"\n17 Numarul de gustari primite la final de antrenament pentru doi sportivi\n";
                cout<<"\n18 Sportivul care participa de cel mai putin timp la competitii dintre doi sportivi care fie sunt amandoi in lot, fie amandoi nu sunt in lot\n";

                cout<<"\n19 Afisare si export sportivi care nu fac parte din lot\n";
                cout<<"\n20 Afisare si export sportivi care fac parte din lot\n";
                cout<<"\n21 Rezultatele unui sportiv\n";
                cout<<"\n22 Rezultatele sportivilor care nu sunt in lot\n";
                cout<<"\n23 Rezultatele sportivilor care sunt in lot\n";

                cout<<"\n24 Actualizare indemnizatie primita pe luna pentru sportivii din lot cat si actualizarea anilor in care au fost in lot\n";//se modifica la finalul anului
                cout<<"\n25 Calcularea indemnizatiei primite pe fiecare an in parte pentru sportivii din lot\n";
                cout<<"\n26 Iesiti din sportiv\n";

                int comanda1;
                cin>>comanda1;
                switch(comanda1)
                {

                case 4:
                {
                    bool tip_sportiv;
                    string cnp;
                    cout<<" Sportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"Pentru a afisa sportivul trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;
                    if(tip_sportiv==0)
                    {
                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                            if(cnp==(*it).getCnp())//cnp-ul e unic
                                cout<<(*it)<<endl;
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                            if(cnp==(*it).getCnp())
                                cout<<(*it)<<endl;
                    }
                    break;

                }
                case 5://introduce sportiv simplu nou
                {
                    Sportiv sp1;
                    cin>>sp1;
                    listaSportivi.push_back(sp1);


                    break;
                }
                case 6://introduce sportiv din lot
                {
                    SportivLot sp2;
                    cin>>sp2;
                    listaSportivilot.push_back(sp2);

                    break;
                }
                case 7://schimba numele de familie
                {
                    bool tip_sportiv;
                    string cnp;
                    cout<<" Sportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"Pentru a schimba numele de familie trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;
                    if(tip_sportiv==0)
                    {
                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                char *nume_fam=new char[100];
                                cout<<"Numele nou de familie: ";
                                cin.get();
                                cin.getline(nume_fam,100);
                                (*it).setNumeDeFamilieSportiv(nume_fam);
                                if(nume_fam!=NULL)
                                    delete [] nume_fam;

                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                char *nume_fam=new char[100];
                                cout<<"Numele nou de familie: ";
                                cin.get();
                                cin.getline(nume_fam,100);
                                (*it).setNumeDeFamilieSportiv(nume_fam);
                                if(nume_fam!=NULL)
                                    delete [] nume_fam;
                            }
                        }
                    }
                    break;
                }

                case 8://schimba prenumele
                {
                    bool tip_sportiv;
                    string cnp;
                    cout<<" Sportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"Pentru a schimba prenumele trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;
                    if(tip_sportiv==0)
                    {
                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                char *prenu=new char[100];
                                cout<<"Prenumele nou: ";
                                cin.get();
                                cin.getline(prenu,100);
                                (*it).setPrenumeSportiv(prenu);
                                if(prenu!=NULL)
                                    delete [] prenu;
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                char *prenu=new char[100];
                                cout<<"Prenumele nou: ";
                                cin.get();
                                cin.getline(prenu,100);
                                (*it).setPrenumeSportiv(prenu);
                                delete [] prenu;
                            }
                        }
                    }
                    break;
                }
                case 9://schimba anul nasterii daca s-a introdus gresit
                {
                    bool tip_sportiv;
                    string cnp;
                    int an_nastere;

                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a schimba anul nasterii trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;

                    if(tip_sportiv==0)
                    {

                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Anul nasterii corect: ";
                                cin>>an_nastere;
                                (*it).setAnulNasterii(an_nastere);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Anul nasterii corect: ";
                                cin>>an_nastere;
                                (*it).setAnulNasterii(an_nastere);
                            }
                        }
                    }
                    break;
                }
                case 10://schimba categoria
                {
                    bool tip_sportiv;
                    string cnp;
                    string categorie;
                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a schimba categoria trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;

                    if(tip_sportiv==0)
                    {

                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Categoria noua din care face parte este: ";
                                cin>>categorie;
                                (*it).setCategorie(categorie);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Categoria noua din care face parte este: ";
                                cin>>categorie;
                                (*it).setCategorie(categorie);
                            }
                        }
                    }
                    break;

                }

                case 11://schimba anul in care a participat la prima competitie daca a fost introdus gresit
                {
                    bool tip_sportiv;
                    string cnp;
                    int an_concurs;

                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a schimba primul an in care a participat la concursuri trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;

                    if(tip_sportiv==0)
                    {

                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Anul in care a participat la primul concurs corect: ";
                                cin>>an_concurs;
                                (*it).setPrimulAnInCareAParticipatLaConcursuri(an_concurs);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Anul in care a participat la primul concurs corect: ";
                                cin>>an_concurs;
                                (*it).setPrimulAnInCareAParticipatLaConcursuri(an_concurs);
                            }
                        }
                    }
                    break;
                }
                case 12://daca s-a introdus gresit genul unui sportiv
                {
                    bool tip_sportiv;
                    string cnp;
                    char gen;

                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a schimba genul trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;

                    if(tip_sportiv==0)
                    {

                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Genul corect['M'/'F']: ";
                                cin>>gen;
                                (*it).setGen(gen);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Genul corect['M'/'F']: ";
                                cin>>gen;
                                (*it).setGen(gen);
                            }
                        }
                    }
                    break;
                }

                case 13://Modificare numarului de gustari
                {
                    bool tip_sportiv;
                    string cnp;
                    int gustari;

                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a schimba numarul de gustari trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;

                    if(tip_sportiv==0)
                    {

                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Numarul corect de gustari: ";
                                cin>>gustari;
                                (*it).setNumarGustariPrimiteLaFinalDeAntrenament(gustari);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Numarul corect de gustari: ";
                                cin>>gustari;
                                (*it).setNumarGustariPrimiteLaFinalDeAntrenament(gustari);
                            }
                        }
                    }
                    break;
                }

                case 14://Modificarea rezultatelor obtinute
                {
                    bool tip_sportiv;
                    string cnp;
                    int nr_ani;

                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a adauga rezultate trebuie sa introduceti CNP-ul sportivului (la introducerea rezultatelor se vor introduce si cele care erau inainte): ";
                    cin>>cnp;

                    if(tip_sportiv==0)
                    {

                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Numarul nou de ani: ";
                                cin>>nr_ani;
                                cout<<"\nNumarul de puncte obtinut de-a lungul anilor mai sus mentionati(numarul de elemente introduse este egal cu: numarul de ani*numarul maxim de probe*numarul de competitii)\n";
                                cout<<"\nDatele care se scriu sunt: 0 (puncte)-niciun loc pe podium; 1 (punct)- pentru locul 3; 2 (puncte) - locul 2; 3 (puncte) - locul 1;\n";
                                int**punctajul=new int *[nr_ani];
                                for(int i=0; i<nr_ani; i++)
                                    punctajul[i]=new int[(*it).getNumarCompetitiiInFiecareAn()*(*it).getNumarMaximDeProbeLaCarePoateParticipaLaFiecareConcurs()];
                                for(int i=0; i<nr_ani; i++)
                                    for(int j=0; j<(*it).getNumarCompetitiiInFiecareAn()*(*it).getNumarMaximDeProbeLaCarePoateParticipaLaFiecareConcurs(); j++)
                                        cin>>punctajul[i][j];

                                (*it).setNumarPunctajObtiuntPeParcursulAnilorPerProbaPerCompetitii(punctajul,nr_ani,(*it).getNumarCompetitiiInFiecareAn(),(*it).getNumarMaximDeProbeLaCarePoateParticipaLaFiecareConcurs());
                                if(punctajul!=NULL){
                                for (int i=0; i<nr_ani; i++)
                                    {
                                    delete[] punctajul[i];
                                    }
                                delete [] punctajul;}

                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                cout<<"Numarul nou de ani: ";
                                cin>>nr_ani;
                                cout<<"\nNumarul de puncte obtinut de-a lungul anilor mai sus mentionati(numarul de elemente introduse este egal cu: numarul de ani*numarul maxim de probe*numarul de competitii)\n";
                                cout<<"\nDatele care se scriu sunt: 0 (puncte)-niciun loc pe podium; 1 (punct)- pentru locul 3; 2 (puncte) - locul 2; 3 (puncte) - locul 1;\n";
                                int**punctajul=new int *[nr_ani];
                                for(int i=0; i<nr_ani; i++)
                                    punctajul[i]=new int[(*it).getNumarCompetitiiInFiecareAn()*(*it).getNumarMaximDeProbeLaCarePoateParticipaLaFiecareConcurs()];
                                for(int i=0; i<nr_ani; i++)
                                    for(int j=0; j<(*it).getNumarCompetitiiInFiecareAn()*(*it).getNumarMaximDeProbeLaCarePoateParticipaLaFiecareConcurs(); j++)
                                        cin>>punctajul[i][j];

                                (*it).setNumarPunctajObtiuntPeParcursulAnilorPerProbaPerCompetitii(punctajul,nr_ani,(*it).getNumarCompetitiiInFiecareAn(),(*it).getNumarMaximDeProbeLaCarePoateParticipaLaFiecareConcurs());
                                if(punctajul!=NULL)
                                {for (int i=0; i<nr_ani; i++)
                                    {
                                    delete[] punctajul[i];
                                    }
                                delete [] punctajul;}

                            }
                        }
                    }
                    break;

                }

                case 15://Scade numarul de gustari primite la final de antrenament pentru un anumit sportiv
                {
                    bool tip_sportiv;
                    string cnp;

                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a scadea cu o unitate numarul de gustari trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;

                    if(tip_sportiv==0)
                    {

                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp() && (*it).getNumarGustariPrimiteLaFinalDeAntrenament()!=0)
                            {
                                (*it)=--(*it);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp() && (*it).getNumarGustariPrimiteLaFinalDeAntrenament()!=0)
                            {
                                (*it)=--(*it);
                            }
                        }
                    }

                    break;
                }

                case 16://Scade numarul de gustari (la a doua afisare se observa modificarile)
                {
                    bool tip_sportiv;
                    string cnp;

                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a scadea cu o unitate numarul de gustari trebuie sa introduceti CNP-ul sportivului: ";
                    cin>>cnp;

                    if(tip_sportiv==0)
                    {

                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp() && (*it).getNumarGustariPrimiteLaFinalDeAntrenament()!=0)

                                (*it)--;
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp() && (*it).getNumarGustariPrimiteLaFinalDeAntrenament()!=0)
                                (*it)--;
                        }
                    }
                    break;
                }
                case 17:
                {
                    bool tip_sportiv1;
                    string cnp1;
                    bool tip_sportiv2;
                    string cnp2;
                    cout<<"\nSe aduna numarul de dulciuri a doi sportivi care sunt din acelasi tip (ambii din lot sau ambii care nu sunt din lot)\n";
                    cout<<"\nPrimul sportiv face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv1;
                    cout<<"\nIntroduceti CNP-ul primului sportiv: ";
                    cin>>cnp1;
                    cout<<"\nAl doilea sportiv face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv2;
                    cout<<"\nIntroduceti CNP-ul celui de-al doilea sportiv: ";
                    cin>>cnp2;


                    if(tip_sportiv1==0 && tip_sportiv2==0)
                    {
                        Sportiv aux1;
                        Sportiv aux2;
                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp1==(*it).getCnp())
                            {
                                aux1=(*it);
                            }
                            if(cnp2==(*it).getCnp())
                            {
                                aux2=(*it);
                            }
                        }
                        cout<<"Numarul de dulciuri primite de sportivii: "<<aux1.getNumeDeFamilieSportiv()<<" "<<aux1.getPrenumeSportiv()<< " si "<<aux2.getNumeDeFamilieSportiv()<<" "<<aux2.getPrenumeSportiv()<<" este: "<<aux1+aux2;
                    }

                    if(tip_sportiv1==1 && tip_sportiv2==1)
                    {
                        SportivLot aux5;
                        SportivLot aux6;
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp1==(*it).getCnp())
                            {
                                aux5=(*it);
                            }
                            if(cnp2==(*it).getCnp())
                            {
                                aux6=(*it);
                            }
                        }
                        cout<<"\nNumarul de dulciuri primite de sportivii: "<<aux5.getNumeDeFamilieSportiv()<<" "<<aux5.getPrenumeSportiv()<< " si "<<aux6.getNumeDeFamilieSportiv()<<" "<<aux6.getPrenumeSportiv()<<" este: "<<aux5+aux6;
                    }

                    break;
                }
                case 18:// Sportivul care participa de cel mai putin timp la competitii
                {
                    bool tip_sportiv1;
                    string cnp1;
                    bool tip_sportiv2;
                    string cnp2;
                    cout<<"\nSportivii alesi trebuie sa faca parte din acelasi tip (ambii din lot sau ambii care nu sunt din lot)\n";
                    cout<<"\nPrimul sportiv face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv1;
                    cout<<"\nIntroduceti CNP-ul primului sportiv: ";
                    cin>>cnp1;
                    cout<<"\nAl doilea sportiv face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv2;
                    cout<<"\nIntroduceti CNP-ul celui de-al doilea sportiv: ";
                    cin>>cnp2;


                    if(tip_sportiv1==0 && tip_sportiv2==0)
                    {
                        Sportiv aux1;
                        Sportiv aux2;
                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp1==(*it).getCnp())
                            {
                                aux1=(*it);
                            }
                            if(cnp2==(*it).getCnp())
                            {
                                aux2=(*it);
                            }
                        }
                        if(aux1>aux2)
                        {
                            cout<<"Sportivul: "<<aux1.getNumeDeFamilieSportiv()<<" "<<aux1.getPrenumeSportiv()<< " care nu este din lot participa de mai putin timp la competitii decat "<<aux2.getNumeDeFamilieSportiv()<<" "<<aux2.getPrenumeSportiv()<<" care nu este in lot";
                            cout<<", mai precis din anul "<<aux1.getPrimulAnInCareAParticipatLaConcursuri();
                        }
                        else
                        {
                            cout<<"Sportivul: "<<aux2.getNumeDeFamilieSportiv()<<" "<<aux2.getPrenumeSportiv()<< " care nu este din lot participa de mai putin timp la competitii decat "<<aux1.getNumeDeFamilieSportiv()<<" "<<aux1.getPrenumeSportiv()<<" care nu este in lot";
                            cout<<", mai precis din anul "<<aux2.getPrimulAnInCareAParticipatLaConcursuri();
                        }
                    }

                    if(tip_sportiv1==1 && tip_sportiv2==1)
                    {
                        SportivLot aux5;
                        SportivLot aux6;
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp1==(*it).getCnp())
                            {
                                aux5=(*it);
                            }
                            if(cnp2==(*it).getCnp())
                            {
                                aux6=(*it);
                            }
                        }
                        if(aux5>aux6)
                        {
                            cout<<"Sportivul: "<<aux5.getNumeDeFamilieSportiv()<<" "<<aux5.getPrenumeSportiv()<< " care este din lot participa de mai putin timp la competitii decat "<<aux6.getNumeDeFamilieSportiv()<<" "<<aux6.getPrenumeSportiv()<<" care nu este in lot";
                            cout<<", mai precis din anul "<<aux5.getPrimulAnInCareAParticipatLaConcursuri();
                        }
                        else
                        {
                            cout<<"Sportivul: "<<aux6.getNumeDeFamilieSportiv()<<" "<<aux6.getPrenumeSportiv()<< " care este din lot participa de mai putin timp la competitii decat "<<aux5.getNumeDeFamilieSportiv()<<" "<<aux5.getPrenumeSportiv()<<" care nu este in lot";
                            cout<<", mai precis din anul "<<aux6.getPrimulAnInCareAParticipatLaConcursuri();
                        }
                    }
                    break;
                }


                case 19:
                {
                    for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {cout<<(*it)<<endl;
                        fout<<(*it)<<endl;}
                    break;
                }
                case 20:
                {
                    for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {cout<<(*it)<<endl;
                        fout<<(*it)<<endl;}
                    break;
                }
                case 21:
                {
                    bool tip_sportiv;
                    string cnp;

                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nIntroduceti CNP-ul sportivului: ";
                    cin>>cnp;

                    if(tip_sportiv==0 )
                    {
                        for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                                (*it).rezulate_sportiv();
                        }
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                                (*it).rezulate_sportiv();
                        }
                    }
                    break;
                }

                case 22:
                {
                    for(auto it=listaSportivi.begin(); it!=listaSportivi.end(); it++)
                        (*it).rezulate_sportiv();
                    break;
                }
                case 23:
                {
                    for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        (*it).rezulate_sportiv();
                    break;

                }

                case 24:
                {
                    string cnp;
                    int nr_ani;
                    bool tip_sportiv;
                    cout<<"\nSportivul face parte din lot? !TREBUIE SA FACA PARTE DIN LOT! (daca face parte tastati 1, altfel 0): ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a modifica indemnizatia primita de sportivul dorit introduceti CNP-ul: ";
                    cin>>cnp;

                    if(tip_sportiv==0 )
                    {
                        cout<<"\nAcest sportiv nu primeste indemnizatie pentru ca nu face parte din lot\n";
                    }
                    else
                    {
                        cout<<"Numarul de ani in care a fost in lot actualizat la acest sfarsit de an este: ";
                        cin>>nr_ani;
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())
                            {
                                float* indemnizatie= new float[nr_ani*12];
                                cout<<"\nPentru a adauga sumele noi trebuie sa le introduceti si pe cele vechi\n";
                                for(int i=0; i<(nr_ani*12); i++)
                                    cin>>indemnizatie[i];
                                (*it).setIndemnizatiaPeLuna(indemnizatie,nr_ani*12);

                                int* ani_in_lot = new int[nr_ani];
                                cout<<"\nPentru a adauga anii/anul nou in care sportivul este in lot trebuie sa ii introduceti si pe cei vechi\n";
                                for(int i=0; i<nr_ani; i++)
                                    cin>>ani_in_lot[i];
                                (*it).setAni(ani_in_lot,nr_ani);

                                if(indemnizatie!=NULL)
                                    delete[]indemnizatie;
                                if(ani_in_lot!=NULL)
                                    delete[]ani_in_lot;

                            }
                        }
                    }
                    break;
                }
                case 25:
                {
                    string cnp;
                    bool tip_sportiv;
                    cout<<"\nSportivul face parte din lot? (daca face parte tastati 1, altfel 0) ! ACEST SPORTIV TREBUIE SA FACA PARTE DIN LOT !: ";
                    cin>>tip_sportiv;
                    cout<<"\nPentru a calcula indemnizatia primita de sportivul dorit introduceti CNP-ul: ";
                    cin>>cnp;

                    if(tip_sportiv==0 )
                    {
                        cout<<"\nAcest sportiv nu primeste indemnizatie pentru ca nu face parte din lot\n";
                    }
                    else
                    {
                        for(auto it=listaSportivilot.begin(); it!=listaSportivilot.end(); it++)
                        {
                            if(cnp==(*it).getCnp())

                                (*it).indemnizatie_primita_pe_fiecare_an();

                        }
                    }
                    break;
                }

                case 26:
                {
                    k1=0;
                    break;
                }
                }

            }
            break;
        }

        case 2:
        {
            int k2;
            k2=1;
            while (k2==1)
            {//daca se modifica un antrenor mai intai se scoate din sala si dupa se modifica si se pune la loc
                cout<<"\n1 Introduceti un antrenor care nu are calificarea sa antreneze sportivi pentru olimpiada\n";
                cout<<"\n2 Introduceti un antrenor care are calificarea sa antreneze sportivi pentru olimpiada\n";

                cout<<"\n3 Afiseaza sportivii care nu sunt din lot antrenati de un antrenor\n";
                cout<<"\n4 Afiseaza sportivii care sunt din lot si antrenati de un antrenor\n";

                cout<<"\n5 Modifica varsta\n";
                cout<<"\n6 Modifica acreditarea\n";
                cout<<"\n7 Modifica numele de familie\n";
                cout<<"\n8 Modifica prenumele\n";
                cout<<"\n9 Modifica salariul\n";
                cout<<"\n10 Actualizeaza numarul de sportivi alocati pe an\n";
                cout<<"\n11 Actualizeaza cheltuiele cu chiria pe luna\n";
                cout<<"\n12 Actualizeaza anii de experienta\n";
                cout<<"\n13 Actualizeaza grupele pe care le antreneaza\n";

                cout<<"\n14 Actualizarea olimpiadelor in care sportivii sai au avut rezultate\n";
                cout<<"\n15 Bonusul primit de un antrenor olimpic\n";

                cout<<"\n16 Creste anii de experienta la toti antrenorii -- cu o unitate -- dupa fiecare an de activitate se va folosi aceasta functie-\n";
                cout<<"\n17 Creste anii de experienta la toti antrenorii - cu o unitate--\n";
                cout<<"\n18 Aduna salariile a doi antrenori de acelasi tip\n";
                cout<<"\n19 Diferenta dintre salariu si un numar dat\n";
                cout<<"\n20 Antrenorul care are mai putine grupe dintre doi antrenori de acelasi tip(ambii antrenori simpli sau ambii antrenori calificati sa antreneze olimpici)\n";
                cout<<"\n21 Pentru a vedea chiria dintr-o anumita luna\n";
                cout<<"\n22 Transformarea salariului intr-o suma exacta(fara virgula)\n";

                cout<<"\n23 Adaugarea unor sportivi care nu sunt din lot la un antrenor\n";//intai scot antrenorul din sala si dupa mdific si dupa il pun la loc in sala
                cout<<"\n24 Adaugarea unor sportivi care sunt din lot la un antrenor\n";//intai scot antrenorul din sala si dupa mdific si dupa il pun la loc in sala
                cout<<"\n25 Scot din antrenor sportivi care nu fac parte din lot\n";//intai scot antrenorul din sala si dupa mdific si dupa il pun la loc in sala
                cout<<"\n26 Scot din antrenor sportivi care fac parte din lot\n";//intai scot antrenorul din sala si dupa mdific si dupa il pun la loc in sala

                cout<<"\n27 Cresterea procentuala a numarului de sportivi pe care ii are un antrenor\n";

                cout<<"\n28 Pentu un antrenor de olimpici calculati salariul cu bonusul - O singura data la inceput -\n";//aceasta se va face doar la inceput
                cout<<"\n29 Marire de salariu pentru antrenorul de olimpici -- aceasta marire va fi valabila un an--\n";
                cout<<"\n30 Anulare marire de salariu pentru antrenorul de olimpici\n";

                cout<<"\n31 Afisare si export antrenori care nu sunt specializati sa antreneze olimpici\n";
                cout<<"\n32 Afisare si export antrenori care sunt specializati sa antreneze olimpici\n";

                cout<<"\n33 Afisarea unui antrenor dat\n";

                cout<<"\n34 Iesiti din antrenor\n";
                cout<<"\n35 Stergeti definitiv un sportiv care nu face parte din lot(acesta pleaca de la club)\n";
                cout<<"\n36 Stergeti definitiv un sportiv care face parte din lot(acesta pleaca de la club)\n";

                int comanda2;
                cin>>comanda2;
                switch(comanda2)
                {
                case 1:
                {
                    Antrenor a1;
                    cin>>a1;
                    listaAntrenor.push_back(a1);
                    break;

                }
                case 2:
                {
                    AntrenorOlimpici a2;
                    cin>>a2;
                    listaAntrenorOl.push_back(a2);
                    break;
                }

                case 3:
                {
                    string email;
                    bool tip;
                    cout<<"Pentru a afisa sportivii care nu sunt din lot introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                for(int i=0; i<(*it).getNumarSportiviActuali(); i++)
                                    cout<<*((*it).getSportivi()+i)<<endl;
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                for(int i=0; i<(*it).getNumarSportiviActuali(); i++)
                                    cout<<*((*it).getSportivi()+i)<<endl;
                            }
                        }
                    }
                    break;
                }
                case 4:
                {
                    string email;
                    bool tip;
                    cout<<"Pentru a afisa sportivii care sunt din lot introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                for(int i=0; i<(*it).getNumarSportiviLot(); i++)
                                    cout<<*((*it).getSportiviLot()+i)<<endl;
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                for(int i=0; i<(*it).getNumarSportiviLot(); i++)
                                    cout<<*((*it).getSportiviLot()+i)<<endl;
                            }
                        }
                    }
                    break;
                }

                case 5:
                {
                    string email;
                    int varsta;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a modifica varsta introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"Varsta corecta: ";
                                cin>>varsta;
                                (*it).setVarsta(varsta);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"Varsta corecta: ";
                                cin>>varsta;
                                (*it).setVarsta(varsta);
                            }
                        }
                    }
                    break;

                }
                case 6:
                {
                    string email;
                    bool acreditare;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a modifica acreditarea introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"A obtinut acreditarea ?[1-da/0-nu] : ";
                                cin>>acreditare;
                                (*it).setEsteAcreditat(acreditare);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"A obtinut acreditarea ? [1-da/0-nu]: ";
                                cin>>acreditare;
                                (*it).setEsteAcreditat(acreditare);
                            }
                        }
                    }
                    break;
                }

                case 7:
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a modifica numele de familie introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                char *nume_fam=new char[100];
                                cout<<"Numele nou de familie: ";
                                cin.get();
                                cin.getline(nume_fam,100);
                                (*it).setNume(nume_fam);
                                if(nume_fam!=NULL)
                                    delete[]nume_fam;
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                char *nume_fam=new char[100];
                                cout<<"Numele nou de familie: ";
                                cin.get();
                                cin.getline(nume_fam,100);
                                (*it).setNume(nume_fam);
                                if(nume_fam!=NULL)
                                    delete[]nume_fam;
                            }
                        }
                    }
                    break;
                }
                case 8:
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a modifica prenumele introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                char *prenume=new char[100];
                                cout<<"Prenume nou: ";
                                cin.get();
                                cin.getline(prenume,100);
                                (*it).setPrenumeAntrenor(prenume);
                                if(prenume!=NULL)
                                    delete[]prenume;
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                char *prenume=new char[100];
                                cout<<"Prenume nou: ";
                                cin.get();
                                cin.getline(prenume,100);
                                (*it).setPrenumeAntrenor(prenume);
                                if(prenume!=NULL)
                                    delete[]prenume;
                            }
                        }
                    }
                    break;
                }
                case  9:
                {
                    string email;
                    float salariu;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a modifica salariul introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)//email-ul e unic
                            {
                                cout<<"Salariu nou: ";
                                cin>>salariu;
                                (*it).setSalariu(salariu);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"Salariu nou: ";
                                cin>>salariu;
                                (*it).setSalariu(salariu);
                            }
                        }
                    }
                    break;
                }
                case 10:
                {
                    string email;
                    bool tip;
                    int nr_ani;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a actualiza numarul de sportivi alocati pe an introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Numarul nou de ani: ";
                    cin>>nr_ani;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                int* nr_sportivi= new int[nr_ani];
                                cout<<"\nPentru a adauga numarul nou de sportivi trebuie introduse si valorile vechi\n";
                                for(int i=0; i<(nr_ani); i++)
                                    cin>>nr_sportivi[i];
                                (*it).setNumarSportiviAlocatiPeAn(nr_sportivi,nr_ani);
                                if(nr_sportivi!=NULL)
                                    delete[]nr_sportivi;

                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                int* nr_sportivi= new int[nr_ani];
                                cout<<"\nPentru a adauga numarul nou de sportivi trebuie introduse si valorile vechi\n";
                                for(int i=0; i<(nr_ani); i++)
                                    cin>>nr_sportivi[i];
                                (*it).setNumarSportiviAlocatiPeAn(nr_sportivi,nr_ani);
                                if(nr_sportivi!=NULL)
                                    delete[]nr_sportivi;
                            }
                        }
                    }
                    break;
                }

                case 11:
                {
                    string email;
                    bool tip;
                    int nr_luni;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a actualiza cheltuielilie cu chiria introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Numarul nou de luni: ";
                    cin>>nr_luni;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                float* cheltuieli= new float[nr_luni];
                                cout<<"\nPentru a adauga numarul nou de bani platiti pe noua luna/noile luni trebuie introduse si valorile vechi\n";
                                for(int i=0; i<(nr_luni); i++)
                                    cin>>cheltuieli[i];
                                (*it).setCheltuieliCuChiriaPeluna(cheltuieli,nr_luni);
                                if(cheltuieli!=NULL)
                                    delete[]cheltuieli;

                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                float* cheltuieli= new float[nr_luni];
                                cout<<"\nPentru a adauga numarul nou de bani platiti pe noua luna/noile luni trebuie introduse si valorile vechi\n";
                                for(int i=0; i<(nr_luni); i++)
                                    cin>>cheltuieli[i];
                                (*it).setCheltuieliCuChiriaPeluna(cheltuieli,nr_luni);
                                if(cheltuieli!=NULL)
                                    delete[]cheltuieli;

                            }
                        }
                    }
                    break;
                }
                case 12:
                {
                    string email;
                    double ani_exp;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a modifica anii de experineta introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"Anii de experienta noi: ";
                                cin>>ani_exp;
                                (*it).setAniExperianta(ani_exp);
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"Anii de experienta noi: ";
                                cin>>ani_exp;
                                (*it).setAniExperianta(ani_exp);
                            }
                        }
                    }
                    break;
                }
                case 13:
                {
                    string email;
                    bool tip;
                    int numar_grupe;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a actualiza grupele antrenate introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Numarul nou de grupe [numar mai mic sau egal cu 10]: ";
                    cin>>numar_grupe;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                string* grupe= new string[numar_grupe];
                                cout<<"\nPentru a adauga grupele noi trebuie introduse si valorile vechi\n";
                                for(int i=0; i<(numar_grupe); i++)
                                    cin>>grupe[i];
                                (*it).setGrupeSportivi(grupe,numar_grupe);
                                if(grupe!=NULL)
                                    delete[] grupe;

                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                string* grupe= new string[numar_grupe];
                                cout<<"\nPentru a adauga grupele noi trebuie introduse si valorile vechi\n";
                                for(int i=0; i<(numar_grupe); i++)
                                    cin>>grupe[i];
                                (*it).setGrupeSportivi(grupe,numar_grupe);
                                if(grupe!=NULL)
                                    delete[] grupe;
                            }
                        }
                    }
                    break;
                }

                case 14:
                {
                    string email;
                    bool tip;
                    int nr_olimpiade;
                    cout<<"Este antrenor pentru olimpici? !Trebuie sa fie olimpic! [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a actualiza olimpiadele cu rezultate introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Numarul total de olimpiade in care a avut rezultate: ";
                    cin>>nr_olimpiade;
                    if(tip==0)
                    {
                        cout<<"\nNu este antrenor pentru olimpici\n";
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                int* ani_olimpiade= new int[nr_olimpiade];
                                cout<<"\nPentru a adauga anul nou/ anii noi in care au avut rezultate la olimpiade trebuie introduse si valorile vechi\n";
                                for(int i=0; i<(nr_olimpiade); i++)
                                    cin>>ani_olimpiade[i];
                                (*it).setAniOlimpiadeCuRezultat(ani_olimpiade,nr_olimpiade);
                                if(ani_olimpiade!=NULL)
                                    delete[]ani_olimpiade;
                            }
                        }
                    }
                    break;
                }
                case 15:
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? !Trebuie sa fie olimpic! [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a vedea bonusul primit introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        cout<<"\nNu este antrenor pentru olimpici\n";
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {

                                cout<<"\nBonusul primit de antrenorul: "<<(*it).getNume()<<" "<<(*it).getPrenumeAntrenor()<<" este de: "<<(*it).getBonus()<< " lei.\n";

                            }
                        }
                    }
                    break;
                }
                case 16:
                {
                    for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        (*it)++;
                    for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        (*it)++;
                    break;

                }
                case 17:

                {
                    for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        ++(*it);
                    for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        ++(*it);
                    break;

                }
                case 18:
                {
                    bool tip_antr1;
                    string email1;
                    bool tip_antr2;
                    string email2;
                    cout<<"\nSe aduna salariile a doi antrenori care sunt din acelasi tip (ambii nu pot antrena olimpici/ ambii pot antrena olimpici )\n";
                    cout<<"\nPrimul antrenor poate antrena olimpici? (daca da tastati 1, altfel 0): ";
                    cin>>tip_antr1;
                    cout<<"\nIntroduceti email-ul primului antrenor: ";
                    cin>>email1;
                    cout<<"\nAl doilea antrenor poate antrena olimpici? (daca da tastati 1, altfel 0): ";
                    cin>>tip_antr2;
                    cout<<"\nIntroduceti email-ul celui de-al doilea antrenor: ";
                    cin>>email2;


                    if(tip_antr1==0 && tip_antr2==0)
                    {
                        Antrenor aux1;
                        Antrenor aux2;
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if(email1==(*it).getEmail())
                            {
                                aux1=(*it);
                            }
                            if(email2==(*it).getEmail())
                            {
                                aux2=(*it);
                            }
                        }
                        cout<<"Suma salariilor celor doi antrenori: "<<aux1.getNume()<<" "<<aux1.getPrenumeAntrenor()<< " si "<<aux2.getNume()<<" "<<aux2.getPrenumeAntrenor()<<" este: "<<aux1+aux2;
                    }

                    if(tip_antr1==1 && tip_antr2==1)
                    {
                        AntrenorOlimpici aux5;
                        AntrenorOlimpici aux6;
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if(email1==(*it).getEmail())
                            {
                                aux5=(*it);
                            }
                            if(email2==(*it).getEmail())
                            {
                                aux6=(*it);
                            }
                        }
                        cout<<"Suma salariilor celor doi antrenori: "<<aux5.getNume()<<" "<<aux5.getPrenumeAntrenor()<< " si "<<aux6.getNume()<<" "<<aux6.getPrenumeAntrenor()<<" este: "<<aux5+aux6;
                    }

                    break;

                }
                case 19:
                {
                    string email;
                    bool tip;
                    float suma;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a vedea la ce salariu ar ajunge antrenorul ales in urma scaderii unei valori introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"\nValoare pe care doriti sa o scadeti: ";
                    cin>>suma;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(*it)-suma;
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(*it)-suma;
                            }
                        }
                    }
                    break;
                }
                case 20:
                {
                    bool tip_antr1;
                    string email1;
                    bool tip_antr2;
                    string email2;
                    cout<<"\nSe compara doi antrenori care sunt din acelasi tip (ambii nu pot antrena olimpici/ ambii pot antrena olimpici) in functie de numarul de grupe\n";
                    cout<<"\nPrimul antrenor poate antrena olimpici? (daca da tastati 1, altfel 0): ";
                    cin>>tip_antr1;
                    cout<<"\nIntroduceti email-ul primului antrenor: ";
                    cin>>email1;
                    cout<<"\nAl doilea antrenor poate antrena olimpici? (daca da tastati 1, altfel 0): ";
                    cin>>tip_antr2;
                    cout<<"\nIntroduceti email-ul celui de-al doilea antrenor: ";
                    cin>>email2;


                    if(tip_antr1==0 && tip_antr2==0)
                    {
                        Antrenor aux1;
                        Antrenor aux2;
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if(email1==(*it).getEmail())
                            {
                                aux1=(*it);
                            }
                            if(email2==(*it).getEmail())
                            {
                                aux2=(*it);
                            }
                        }
                        if(aux1<aux2)
                            cout<<aux1.getNume()<<" "<<aux1.getPrenumeAntrenor()<<" are mai putine grupe si anume "<<aux1.getNumarGrupe()<<" grupe.\n";
                        else
                            cout<<aux2.getNume()<<" "<<aux2.getPrenumeAntrenor()<<" are mai putine grupe si anume "<<aux2.getNumarGrupe()<<" grupe.\n";
                    }

                    if(tip_antr1==1 && tip_antr2==1)
                    {
                        AntrenorOlimpici aux5;
                        AntrenorOlimpici aux6;
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if(email1==(*it).getEmail())
                            {
                                aux5=(*it);
                            }
                            if(email2==(*it).getEmail())
                            {
                                aux6=(*it);
                            }
                        }
                        if(aux5<aux6)
                            cout<<aux5.getNume()<<" "<<aux5.getPrenumeAntrenor()<<" are mai putine grupe si anume "<<aux5.getNumarGrupe()<<" grupe.\n";
                        else
                            cout<<aux6.getNume()<<" "<<aux6.getPrenumeAntrenor()<<" are mai putine grupe si anume "<<aux6.getNumarGrupe()<<" grupe.\n";
                    }

                    break;
                }
                case 21://chiria din luna data
                {
                    string email;
                    int numar_luna;//lunile 0-11 sunt din primul an, lunile 12-23 din al doilea an...
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a vedea chiria dintr-o anumita luna introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Numarul lunii pentru care se doreste aflarea sumei este [numerotarea incepe de la 0]: ";
                    cin>>numar_luna;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(*it)[numar_luna];
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(*it)[numar_luna];
                            }
                        }
                    }
                    break;
                }
                case 22:
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(int)(*it).getSalariu();
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(int)(*it).getSalariu();
                            }
                        }
                    }
                    break;
                }

                case 23://adaugarea sportivilor care nu sunt din lot
                {
                    string email;
                    string cnp;
                    int nr_sportivi;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a adauga sportiv care nu este din lot introduceti adresa de e-mail a antrenorului:\n";
                    cin>>email;
                    cout<<"Numarul de sportivi care vreti sa fie introdusi la acest antrenor: ";
                    cin>>nr_sportivi;

                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"\nIntroduceti cnp-urile sportivilor: ";//caut in lista de sportivi aceste cnp-uri
                                for(int i=0; i<nr_sportivi; i++)
                                {
                                    cin>>cnp;
                                    {
                                        for(auto iter=listaSportivi.begin(); iter!=listaSportivi.end(); iter++)//parcurg lista sportivilor care nu sunt din lot
                                        {
                                            if((*iter).getCnp()==cnp)
                                                (*it)=(*it)+(*iter);

                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"\nIntroduceti cnp-urile sportivilor: ";
                                for(int i=0; i<nr_sportivi; i++)
                                {
                                    cin>>cnp;
                                    {
                                        for(auto iter=listaSportivi.begin(); iter!=listaSportivi.end(); iter++)
                                        {
                                            if((*iter).getCnp()==cnp)
                                                (*it)=(*it)+(*iter);

                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                case 24://adaugarea sportivilor care sunt din lot
                {
                    string email;
                    string cnp;
                    int nr_sportivi;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a adauga sportiv care este din lot introduceti adresa de e-mail a antrenorului (eficienta antrenorului)\n";
                    cin>>email;
                    cout<<"Numarul de sportivi care vreti sa fie introdusi la acest antrenor: ";
                    cin>>nr_sportivi;

                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"\nIntroduceti cnp-urile sportivilor: ";//caut in lista de sportivi aceste cnp-uri
                                for(int i=0; i<nr_sportivi; i++)
                                {
                                    cin>>cnp;
                                    {
                                        for(auto iter=listaSportivilot.begin(); iter!=listaSportivilot.end(); iter++)
                                        {
                                            if((*iter).getCnp()==cnp)
                                                (*it)=(*it)+(*iter);

                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"\nIntroduceti cnp-urile sportivilor: ";
                                for(int i=0; i<nr_sportivi; i++)
                                {
                                    cin>>cnp;
                                    {
                                        for(auto iter=listaSportivilot.begin(); iter!=listaSportivilot.end(); iter++)
                                        {
                                            if((*iter).getCnp()==cnp)
                                                (*it)=(*it)+(*iter);

                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                }

                case 25://stergem sportiv care nu face parte din lot de la un antrenor
                {
                    string email;
                    string cnp;
                    int nr_sportivi;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a sterge sportiv care nu este din lot introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Numarul de sportivi pe care vreti sa ii stergeti de la acest antrenor: ";
                    cin>>nr_sportivi;

                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"\nIntroduceti cnp-urile sportivilor: ";//caut in lista de sportivi aceste cnp-uri
                                for(int i=0; i<nr_sportivi; i++)
                                {
                                    cin>>cnp;
                                    {
                                        for(auto iter=listaSportivi.begin(); iter!=listaSportivi.end(); iter++)
                                        {
                                            if((*iter).getCnp()==cnp)
                                                (*it)=(*it)-(*iter);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"\nIntroduceti cnp-urile sportivilor: ";
                                for(int i=0; i<nr_sportivi; i++)
                                {
                                    cin>>cnp;
                                    {
                                        for(auto iter=listaSportivi.begin(); iter!=listaSportivi.end(); iter++)
                                        {
                                            if((*iter).getCnp()==cnp)
                                                (*it)=(*it)-(*iter);

                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                case 26://scot sportivi care fac parte din lot
                {
                    string email;
                    string cnp;
                    int nr_sportivi;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a sterge sportiv care este din lot introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Numarul de sportivi pe care vreti sa ii stergeti de la acest antrenor: ";
                    cin>>nr_sportivi;

                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"\nIntroduceti cnp-urile sportivilor: ";//caut in lista de sportivi aceste cnp-uri
                                for(int i=0; i<nr_sportivi; i++)
                                {
                                    cin>>cnp;
                                    {
                                        for(auto iter=listaSportivilot.begin(); iter!=listaSportivilot.end(); iter++)
                                        {
                                            if((*iter).getCnp()==cnp)
                                                (*it)=(*it)-(*iter);

                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<"\nIntroduceti cnp-urile sportivilor: ";
                                for(int i=0; i<nr_sportivi; i++)
                                {
                                    cin>>cnp;
                                    {
                                        for(auto iter=listaSportivilot.begin(); iter!=listaSportivilot.end(); iter++)
                                        {
                                            if((*iter).getCnp()==cnp)
                                                (*it)=(*it)-(*iter);

                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                }

                case 27://eficienta antrenorului
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a vedea cresterea procentuala (eficienta antrenorului) introduceti adresa de e-mail a antrenorului \n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                (*it).eficienta_antrenor();
                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                (*it).eficienta_antrenor();
                            }
                        }
                    }
                    break;
                }
                case 28:
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? !TREBUIE sa fie de olimpici! [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a calcula salariul cu bonusul introduceti adresa de e-mail a antrenorului\n";//se face o singura data la inceput
                    cin>>email;
                    if(tip==0)
                    {
                        cout<<"\nNu este antrenor pentru olimpici\n";
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(*it).salariu_antrenor_olimpic();
                            }
                        }
                    }
                    break;
                }

                case 29:
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? !TREBUIE sa fie de olimpici! [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a face marirea de salariu introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        cout<<"\nNu este antrenor pentru olimpici\n";
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(*it).marire_salariu();
                            }
                        }
                    }
                    break;
                }
                case 30:
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? !TREBUIE sa fie de olimpici! [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a anula marirea de salariu introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        cout<<"\nNu este antrenor pentru olimpici\n";
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                cout<<(*it).anulare_marire_salariu();
                            }
                        }
                    }
                    break;

                }
                case 31://afisare si export antrenori care nu sunt specializati in antrenarea olimpicilor
                {
                    for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {cout<<(*it)<<endl;
                        fout<<(*it)<<endl;}
                    break;

                }
                case 32:
                {
                    for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {cout<<(*it)<<endl;
                        fout<<(*it)<<endl;}
                    break;
                }
                case 33:
                {
                    string email;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a afisa antrenorul introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                                cout<<(*it)<<endl;
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                                cout<<(*it)<<endl;
                        }
                    }
                    break;
                }
                case 34:
                {
                    k2=0;
                    break;
                }
                case 35:
                {
                    string email;
                    string cnp;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a sterge definitiv sportiv care nu este din lot introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Cnp sportiv: ";
                    cin>>cnp;

                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                for(auto iter=listaSportivi.begin(); iter!=listaSportivi.end(); iter++)
                                {
                                    if((*iter).getCnp()==cnp)
                                    {
                                        (*it)=(*it)-(*iter);
                                        listaSportivi.erase(iter);
                                        break;
                                    }
                                }

                            }
                        }
                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                for(auto iter=listaSportivi.begin(); iter!=listaSportivi.end(); iter++)
                                {
                                    if((*iter).getCnp()==cnp)
                                    {
                                        (*it)=(*it)-(*iter);
                                        listaSportivi.erase(iter);
                                        break;
                                    }

                                }
                            }
                        }
                    }


                    break;

                }
                case 36:
                {
                    string email;
                    string cnp;
                    bool tip;
                    cout<<"Este antrenor pentru olimpici? [1- da/0-nu]\n";
                    cin>>tip;
                    cout<<"Pentru a sterge definitiv sportiv care este din lot introduceti adresa de e-mail a antrenorului\n";
                    cin>>email;
                    cout<<"Cnp sportiv: ";
                    cin>>cnp;

                    if(tip==0)
                    {
                        for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                for(auto iter=listaSportivilot.begin(); iter!=listaSportivilot.end(); iter++)
                                {
                                    if((*iter).getCnp()==cnp)
                                    {
                                        (*it)=(*it)-(*iter);
                                        listaSportivilot.erase(iter);
                                        break;
                                    }
                                }
                            }
                        }

                    }
                    else
                    {
                        for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                        {
                            if((*it).getEmail()==email)
                            {
                                for(auto iter=listaSportivilot.begin(); iter!=listaSportivilot.end(); iter++)
                                {
                                    if((*iter).getCnp()==cnp)
                                    {
                                        (*it)=(*it)-(*iter);
                                        listaSportivilot.erase(iter);
                                        break;
                                    }

                                }
                            }
                        }
                    }


                    break;

                }

                }
            }
            break;
        }


        case 3:
        {
            int k3;
            k3=1;
            while (k3==1)
            {//cand se face o modificare la o sala mai intai se scoate din tipuri sport si dupa se modifica si se pune la loc

                cout<<"\n1 Introduceti o sala\n";

                cout<<"\n2 Schimbati evaluarea salii\n";
                cout<<"\n3 Afisati antrenorii din sala dorita care nu au calificarea sa antreneze olimpici\n";
                cout<<"\n4 Afisati antrenorii din sala dorita care au calificarea sa antreneze olimpici\n";

                cout<<"\n5 Schimbati latimea zonei destinata sportului din sala\n";
                cout<<"\n6 Schimbati lungimea zonei destinata sportului din sala\n";
                cout<<"\n7 Schimbati latimea salii de sport\n";
                cout<<"\n8 Schimbati lungimea salii de sport\n";
                cout<<"\n9 Schimbati inaltimea salii de sport\n";

                cout<<"\n10 Daca s-a renovat sala puteti sa actualizati\n";
                cout<<"\n11 Schimbarea numarului de culoare dintr-o sala\n";
                cout<<"\n12 Schimbarea numarului orelor permise de stat in sala\n";

                cout<<"\n13 Afiseaza sala data\n";
                cout<<"\n14 Afiseaza si exporta toate salile\n";


                cout<<"\n15 Creste numarul de culoare-- cu o unitate\n";
                cout<<"\n16 Imparte inaltimile a doua sali\n";
                cout<<"\n17 Compara latimea si lungimea a doua sali\n";

                cout<<"\n18 Adauga antrenori care nu au calificarea sa antreneze olimpici la o sala\n";
                cout<<"\n19 Adauga antrenori care au calificarea sa antreneze olimpici la o sala\n";
                cout<<"\n20 Scoate antrenori care nu au calificarea sa antreneze olimpici de la o sala\n";
                cout<<"\n21 Scoate antrenori care au calificarea sa antreneze olimpici de la o sala\n";

                cout<<"\n22 Scoate un antrenor care nu are calificarea sa antreneze olimpici definitiv din club\n";
                cout<<"\n23 Scoate un antrenor care are calificarea sa antreneze olimpici definitiv din club\n";
                cout<<"\n24 Capacitatea unei sali\n";
                cout<<"\n25 Capacitatea tuturor salilor\n";
                cout<<"\n26 Iesi din sala\n";

                int comanda1;
                cin>>comanda1;
                switch(comanda1)
                {
                case 1:
                {
                    Sala s1;
                    cin>>s1;
                    listaSala.push_back(s1);
                    break;

                }
                case 2:
                {
                    char* numesala= new char[100];
                    char eval;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti noua evaluare [valori de la 0-nesatisfacator la 9-foarte bun]: ";
                    cin>>eval;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setEvaluare(eval);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;

                }

                case 3:
                {
                    char* numesala= new char[100];
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            for(int i=0; i<(*iter).getNrAntrenori(); i++)
                                cout<<*((*iter).getAntrenor()+i)<<endl;
                        }
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 4:
                {
                    char* numesala= new char[100];
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            for(int i=0; i<(*iter).getNrAntrenoriOlimpici(); i++)
                                cout<<*((*iter).getAntrenorOlimpici()+i)<<endl;
                        }
                    }
                    if(numesala!=NULL)//unde am pus asa e daca se intamlpa sa nu scrie nimic, ca mereu o sa fie ceva scis acolo
                        delete [] numesala;
                    break;
                }
                case 5:
                {
                    char* numesala= new char[100];
                    float latimezonasport;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti noua latime a zonei de sport[m]: ";
                    cin>>latimezonasport;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setLatimeSalaZonaDeSport(latimezonasport);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 6:
                {
                    char* numesala= new char[100];
                    float lungimezonasport;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti noua lungime a zonei de sport[m]: ";
                    cin>>lungimezonasport;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setLungimeSalaZonaDeSport(lungimezonasport);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 7:
                {
                    char* numesala= new char[100];
                    float latime;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti noua latime a salii de sport[m]: ";
                    cin>>latime;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setLatimeSala(latime);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 8:
                {
                    char* numesala= new char[100];
                    float lungime;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti noua lungime a salii de sport[m]: ";
                    cin>>lungime;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setLungimeSala(lungime);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 9:
                {
                    char* numesala= new char[100];
                    float inaltime;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti noua inaltime a salii de sport[m]: ";
                    cin>>inaltime;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setInaltime(inaltime);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 10://sala renovata
                {
                    char* numesala= new char[100];
                    cout<<"Introduceti numele salii care s-a renovat: ";
                    cin.get();
                    cin.getline(numesala,100);
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setRenovat(1);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 11://numar culoare
                {
                    int numar_culoare;
                    char* numesala= new char[100];
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti numarul nou de culoare: ";
                    cin>>numar_culoare;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setNumarCuloare(numar_culoare);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 12://numar culoare
                {
                    int numar_ore;
                    char* numesala= new char[100];
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti numarul nou de ore permise de stat in sala: ";
                    cin>>numar_ore;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter).setNumarOrePermiseDeStat(numar_ore);
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 13://afisez o sala data
                {
                    char* numesala= new char[100];
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            cout<<(*iter)<<endl;
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;

                }
                case 14://afisez toate salile
                {
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                        {cout<<(*iter)<<endl;
                        fout<<(*iter)<<endl;
                        }
                    break;

                }
                case 15://creste numarul de culoare pentru o sala
                {
                    char* numesala= new char[100];

                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                            (*iter)++;
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 16://de cate ori intra o sala in alta sala dupa inaltime
                {
                    Sala aux1;
                    Sala aux2;
                    char* numesala1= new char[100];
                    char* numesala2= new char[100];
                    cout<<"Introduceti numele primei sali: ";
                    cin.get();
                    cin.getline(numesala1,100);
                    cout<<"Introduceti numele celei de-a doua sali: ";

                    cin.getline(numesala2,100);
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala1)==0)
                            aux1=(*iter);
                        if(strcmp((*iter).getNumeSala(),numesala2)==0)
                            aux2=(*iter);
                    }
                    if(aux1.getInaltime()>aux2.getInaltime())
                        cout<<aux2.getNumeSala()<<" intra de: "<<aux1/aux2<<" ori ca inaltime in sala "<<aux1.getNumeSala();
                    else
                        cout<<aux1.getNumeSala()<<" intra de: "<<aux2/aux1<<" ori ca inaltime in sala "<<aux2.getNumeSala();
                    if(numesala1!=NULL)
                        delete [] numesala1;
                    if(numesala2!=NULL)
                        delete [] numesala2;
                    break;
                }
                case 17://compara latimile si lungimea salilor
                {
                    Sala aux1;
                    Sala aux2;
                    char* numesala1= new char[100];
                    char* numesala2= new char[100];
                    cout<<"Introduceti numele primei sali: ";
                    cin.get();
                    cin.getline(numesala1,100);
                    cout<<"Introduceti numele celei de-a doua sali: ";

                    cin.getline(numesala2,100);
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala1)==0)
                            aux1=(*iter);
                        if(strcmp((*iter).getNumeSala(),numesala2)==0)
                            aux2=(*iter);
                    }
                    if(aux1>=aux2)
                        cout<<aux1.getNumeSala()<<" are latimea si latimea salii mai mari sau egale cu cele ale salii "<<aux2.getNumeSala();
                    else
                        cout<<aux2.getNumeSala()<<" are latimea si latimea salii mai mari sau egale cu cele ale salii "<<aux1.getNumeSala();
                    if(numesala1!=NULL)
                        delete [] numesala1;
                    if(numesala2!=NULL)
                        delete [] numesala2;
                    break;
                }
                case 18://adauga antrenori la o sala
                {
                    char* numesala= new char[100];
                    int nr_antr;
                    string email;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Numarul de antrenori care nu au calificarea sa antreneze olimpici care vreti sa fie introdusi la acest antrenor: ";
                    cin>>nr_antr;

                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            cout<<"\nIntroduceti email-urile antrenorilor:\n";
                            for(int i=0; i<nr_antr; i++)
                            {
                                cin>>email;
                                for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                                {
                                    if((*it).getEmail()==email)
                                        (*iter)=(*iter)+(*it);
                                }
                            }
                        }

                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 19://adauga antrenori calificati pe antrenat olimpici la o sala
                {
                    char* numesala= new char[100];
                    int nr_antr;
                    string email;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Numarul de antrenori care au calificarea sa antreneze olimpici care vreti sa fie introdusi la acest antrenor: ";
                    cin>>nr_antr;

                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            cout<<"\nIntroduceti email-urile antrenorilor:\n";
                            for(int i=0; i<nr_antr; i++)
                            {
                                cin>>email;
                                for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                                {
                                    if((*it).getEmail()==email)
                                        (*iter)=(*iter)+(*it);
                                }
                            }
                        }

                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 20:
                {
                    char* numesala= new char[100];
                    int nr_antr;
                    string email;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Numarul de antrenori care nu au calificarea sa antreneze olimpici care vreti sa fie scosi de la aceasta sala: ";
                    cin>>nr_antr;

                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            cout<<"\nIntroduceti email-urile antrenorilor:\n";
                            for(int i=0; i<nr_antr; i++)
                            {
                                cin>>email;
                                for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                                {
                                    if((*it).getEmail()==email)
                                        (*iter)=(*iter)-(*it);
                                }
                            }
                        }

                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 21:
                {
                    char* numesala= new char[100];
                    int nr_antr;
                    string email;
                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Numarul de antrenori care au calificarea sa antreneze olimpici care vreti sa fie scosi de la aceasta sala: ";
                    cin>>nr_antr;

                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            cout<<"\nIntroduceti email-urile antrenorilor:\n";
                            for(int i=0; i<nr_antr; i++)
                            {
                                cin>>email;
                                for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                                {
                                    if((*it).getEmail()==email)
                                        (*iter)=(*iter)-(*it);
                                }
                            }
                        }

                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }

                case 22://Scoate un antrenor care nu are calificarea sa antreneze olimpici definitiv din club
                {
                    char* numesala= new char[100];
                    string email;
                    cout<<"Pentru a sterge definitiv un antrenor care nu are calificarea sa antreneze olimpici introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti email-ul antrenorului: ";
                    cin>>email;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            for(auto it=listaAntrenor.begin(); it!=listaAntrenor.end(); it++)
                            {
                                if((*it).getEmail()==email)
                                {
                                    (*iter)=(*iter)-(*it);
                                    listaAntrenor.erase(it);
                                    break;
                                }
                            }
                        }

                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }

                case 23://Scoate un antrenor care are calificarea sa antreneze olimpici definitiv din club

                {
                    char* numesala= new char[100];
                    string email;
                    cout<<"Pentru a sterge definitiv un antrenor care are calificarea sa antreneze olimpici introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    cout<<"Introduceti email-ul antrenorului: ";
                    cin>>email;
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            for(auto it=listaAntrenorOl.begin(); it!=listaAntrenorOl.end(); it++)
                            {
                                if((*it).getEmail()==email)
                                {
                                    (*iter)=(*iter)-(*it);
                                    listaAntrenorOl.erase(it);
                                    break;
                                }
                            }
                        }

                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }


                case 24://capacitatea unei sali date
                {
                    char* numesala= new char[100];

                    cout<<"Introduceti numele salii: ";
                    cin.get();
                    cin.getline(numesala,100);
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        if(strcmp((*iter).getNumeSala(),numesala)==0)
                        {
                            cout<<endl;
                            (*iter).capacitate();
                            cout<<endl;
                        }
                    }
                    if(numesala!=NULL)
                        delete [] numesala;
                    break;
                }
                case 25://capacitatea pentru toate salile
                {
                    for(auto iter=listaSala.begin(); iter!=listaSala.end(); iter++)
                    {
                        (*iter).capacitate();
                        cout<<endl;
                    }
                }
                case 26:
                {
                    k3=0;
                    break;
                }
                }
            }
            break;
        }
        case 4:
        {
            int k4;
            k4=1;
            while (k4==1)
            {
                cout<<"\n2 Importati sporturile existente -- SE FACE DIN FISIER O SINGURA DATA LA INCEPUT--\n";

                cout<<"\n3 Actualizati pozitiile pe care se afla tipul de sport in clasamentul celor mai populare sporturi\n";
                cout<<"\n4 Actualizati numarul premiilor valoroase obtinute la acest tip de sport\n";
                cout<<"\n5 Actualizati materialele necesare pentru un sport\n";

                cout<<"\n6 Adunati premiile valoroase pentru doua tipuri de sport\n";
                cout<<"\n7 Inmultirea numarului de materiale pentru doua sporturi\n";
                cout<<"\n8 Comparati numarul de materiale pentru doua sporturi\n";
                cout<<"\n9 Afisati materialele necesare pentru un sport\n";

                cout<<"\n10 Afisare si export pentru toate tipurile de sport\n";
                cout<<"\n11 Afisati un sport dat\n";

                cout<<"\n12 Adauga o sala\n";
                cout<<"\n13 Scoate o sala\n";
                cout<<"\n14 Scoate o sala definitiv\n";

                cout<<"\n15 Cel mai bun loc obtinut de un sport in clasament\n";
                cout<<"\n16 Iesi din tipuri sport\n";
                int comanda1;
                cin>>comanda1;
                switch(comanda1)
                {
                case 2://se face o singura data -- pentru dansuri se plateste cel mai putin, pentru atletism mai mult, apoi vine inotul, ciclismul si cel mai costisitor este triathlonul
                {
                    TipuriSport t1;
                    fin>>t1;
                    fout<<"Tipul sportului: "<<t1.getNumeSport()<<endl;
                    TipuriSport t2;
                    fin>>t2;
                    fout<<"Tipul sportului: "<<t2.getNumeSport()<<endl;
                    TipuriSport t3;
                    fin>>t3;
                    fout<<"Tipul sportului: "<<t3.getNumeSport()<<endl;
                    TipuriSport t4;
                    fin>>t4;
                    fout<<"Tipul sportului: "<<t4.getNumeSport()<<endl;
                    TipuriSport t5;
                    fin>>t5;
                    fout<<"Tipul sportului: "<<t5.getNumeSport()<<endl;
                    multimeSport.insert(t1);
                    multimeSport.insert(t2);
                    multimeSport.insert(t3);
                    multimeSport.insert(t4);
                    multimeSport.insert(t5);
                    break;
                }
                case 3:
                {
                    string nume_sport;
                    int ani;
                    cout<<"\nIntroduceti numele sportului[Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport;
                    cout<<"\nPentru a actualiza locul ocupat in clasament introduceti noul numar de ani: ";
                    cin>>ani;
                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport)
                        {
                            TipuriSport t1;
                            t1=(*iteratorul);
                            multimeSport.erase(iteratorul);
                            int* pozitii= new int[ani];
                            cout<<"\nPentru a adauga pozitia nou ocupata trebuie introduse si valorile vechi\n";
                            for(int i=0; i<ani; i++)
                                cin>>pozitii[i];
                            (t1).setPozSporturiPopularePeAn(pozitii,ani);
                            multimeSport.insert(t1);
                            if(pozitii!=NULL)
                                delete [] pozitii;
                            break;
                        }

                    }
                    break;
                }
                case 4:
                {
                    string nume_sport;
                    int nr_premii;
                    cout<<"\nIntroduceti numele sportului[Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport;
                    cout<<"\nIntroduceti noul numar de premii valoroase obtinute: ";
                    cin>>nr_premii;
                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport)
                        {
                            TipuriSport t1;
                            t1=(*iteratorul);
                            multimeSport.erase(iteratorul);
                            (t1).setNrPremiiValoroaseAleClubului(nr_premii);
                            multimeSport.insert(t1);
                            break;
                        }

                    }
                    break;
                }
                case 5:
                {
                    string nume_sport;
                    int nr_materiale;
                    cout<<"\nIntroduceti numele sportului [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport;
                    cout<<"\nIntroduceti noul numar de materiale necesare: ";
                    cin>>nr_materiale;
                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport)
                        {
                            TipuriSport t1;
                            t1=(*iteratorul);
                            multimeSport.erase(iteratorul);
                            string* materiale= new string[nr_materiale];
                            cout<<"\nPentru a adauga materiale noi trebuie introduse si cele vechi\n";
                            for(int i=0; i<nr_materiale; i++)
                                cin>>materiale[i];
                            (t1).setMaterialeNecesare(materiale,nr_materiale);
                            multimeSport.insert(t1);
                            if(materiale!=NULL)
                                delete[]materiale;
                            break;
                        }

                    }
                    break;
                }
                // Adunati premiile valoroase pentru doua tipuri de sport
                case 6:
                {
                    string nume_sport1;
                    TipuriSport t1;
                    TipuriSport t2;
                    string nume_sport2;
                    cout<<"\nIntroduceti numele primului sport [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport1;
                    cout<<"\nIntroduceti numele celui de-al doilea sport [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport2;

                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport1)
                        {
                            t1=(*iteratorul);
                        }
                        if((*iteratorul).getNumeSport()==nume_sport2)
                        {
                            t2=(*iteratorul);
                        }
                    }

                    cout<<"\n\nNumarul de premii valoroase acumulate de club de la "<<nume_sport1<<" si "<<nume_sport2<<" este "<< t1+t2<<"\n" ;

                    break;
                }
                //Inmultirea numarului de materiale pentru doua sporturi
                case 7:
                {
                    string nume_sport1;
                    TipuriSport t1;
                    TipuriSport t2;
                    string nume_sport2;
                    cout<<"\nIntroduceti numele primului sport [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport1;
                    cout<<"\nIntroduceti numele celui de-al doilea sport [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport2;

                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport1)
                        {
                            t1=(*iteratorul);
                        }
                        if((*iteratorul).getNumeSport()==nume_sport2)
                        {
                            t2=(*iteratorul);
                        }
                    }

                    cout<<"\n\nPrin inmultirea numarului de materiale al celor doua tipuri de sport se obtine "<< t1*t2<<"\n" ;

                    break;
                }
                //Comparati numarul de materiale pentru doua sporturi
                case 8:
                {
                    string nume_sport1;
                    TipuriSport t1;
                    TipuriSport t2;
                    string nume_sport2;
                    cout<<"\nIntroduceti numele primului sport [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport1;
                    cout<<"\nIntroduceti numele celui de-al doilea sport [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport2;

                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport1)
                        {
                            t1=(*iteratorul);
                        }
                        if((*iteratorul).getNumeSport()==nume_sport2)
                        {
                            t2=(*iteratorul);
                        }
                    }
                    if(t1<=t2)

                        cout<<"\n"<<t1.getNumeSport()<< " are un numar mai mic sau egal de materiale necesare fata de "<<t2.getNumeSport()<<"\n";
                    else
                        cout<<"\n"<<t2.getNumeSport()<< " are un numar mai mic sau egal de materiale necesare fata de "<<t1.getNumeSport()<<"\n";
                    break;
                }
                //Afisati un material necesar de la o pozitie data pentru un sport
                case 9:
                {
                    string nume_sport1;
                    TipuriSport t1;
                    cout<<"\nIntroduceti numele sportului [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport1;
                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport1)
                        {
                            t1=(*iteratorul);
                        }

                    }
                    cout<<"\nMateriale necesare pentru "<<t1.getNumeSport()<< " sunt: \n";
                    for(int i=0; i<t1.getNrMateriale(); i++)
                        cout<<" "<<t1[i]<<endl;
                    break;
                }
                case 10:
                {
                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                        {cout<<(*iteratorul)<<"\n\n";
                        fout<<(*iteratorul)<<"\n\n";}
                    break;
                }
                //Afisati un sport dat
                case 11:
                {
                    string nume_sport1;
                    TipuriSport t1;
                    cout<<"\nIntroduceti numele sportului [Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport1;
                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport1)
                        {
                            cout<<(*iteratorul)<<endl;
                            break;
                        }

                    }
                    break;
                }
                //Adauga o sala
                case 12:
                {
                    string nume_sport;
                    cout<<"\nIntroduceti numele sportului[Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport;

                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport)
                        {
                            TipuriSport t1;
                            t1=(*iteratorul);

                            char* numesala= new char[100];
                            cout<<"\nPentru a adauga o sala introduceti numele acesteia\n";
                            cin.get();
                            cin.getline(numesala,100);
                            for(auto it=listaSala.begin(); it!=listaSala.end(); it++)
                            {
                                if(strcmp((*it).getNumeSala(),numesala)==0)
                                {multimeSport.erase(iteratorul);
                                    t1=t1+(*it);
                                }
                            }
                            multimeSport.insert(t1);
                            if(numesala!=NULL)
                                delete[]numesala;
                            break;
                        }

                    }
                    break;
                }
                //Elimina o sala de la un sport
                case 13:
                {
                    string nume_sport;
                    cout<<"\nIntroduceti numele sportului[Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport;

                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport)
                        {
                            TipuriSport t1;
                            t1=(*iteratorul);

                            char* numesala= new char[100];
                            cout<<"\nPentru a sterge o sala introduceti numele acesteia\n";
                            cin.get();
                            cin.getline(numesala,100);
                            for(auto it=listaSala.begin(); it!=listaSala.end(); it++)
                            {
                                if(strcmp((*it).getNumeSala(),numesala)==0)
                                {multimeSport.erase(iteratorul);
                                    t1=t1-(*it);
                                }
                            }
                            multimeSport.insert(t1);
                            if(numesala!=NULL)
                                delete[]numesala;
                            break;
                        }

                    }
                    break;
                }
                case 14:
                {
                    string nume_sport;
                    cout<<"\nIntroduceti numele sportului[Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport;

                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport)
                        {
                            TipuriSport t1;
                            t1=(*iteratorul);

                            char* numesala= new char[100];
                            cout<<"\nPentru a sterge definitiv o sala introduceti numele acesteia\n";
                            cin.get();
                            cin.getline(numesala,100);
                            for(auto it=listaSala.begin(); it!=listaSala.end(); it++)
                            {
                                if(strcmp((*it).getNumeSala(),numesala)==0)
                                {   multimeSport.erase(iteratorul);
                                    t1=t1-(*it);
                                    listaSala.erase(it);
                                    multimeSport.insert(t1);
                                    if(numesala!=NULL)
                                        delete[]numesala;
                                    break;
                                }
                            }

                            break;
                        }

                    }
                    break;
                }
                // Cel mai bun loc obtinut de un sport in clasament
                case 15:
                {
                    string nume_sport;
                    TipuriSport t1;
                    cout<<"\nIntroduceti numele sportului[Dans/Inot/Triathlon/Atletism/Ciclism]\n";
                    cin>>nume_sport;

                    for(auto iteratorul=multimeSport.begin(); iteratorul!=multimeSport.end(); iteratorul++)
                    {
                        if((*iteratorul).getNumeSport()==nume_sport)
                        {
                            t1=(*iteratorul);
                            cout<<endl;
                            t1.cel_mai_bun_loc_in_clasament();
                            cout<<endl;
                        }

                    }
                    break;
                }
                case 16:
                {
                    k4=0;
                    break;
                }

                }
            }
            break;
        }

        case 5:
        {
            int k4;
            k4=1;
            while (k4==1)
            {
                cout<<"\n1 Adauga un abonamet pentru dansuri [la numele sportului se scrie Dans]\n";
                cout<<"\n2 Adauga un abonament pentru inot [la numele sportului se scrie Inot]\n";
                cout<<"\n3 Adauga un abonament pentru atletism [la numele sportului se scrie Atletism]\n";
                cout<<"\n4 Adauga un abonament pentru ciclism [la numele sportului se scrie Ciclism]\n";
                cout<<"\n5 Adauga un abonament pentru triathlon [la numele sportului se scrie Triathlon]\n";
                cout<<"\n6 Afisati consumul pentru abonamentele de la un sport dat\n";
                cout<<"\n7 Afisati preturile pentru abonamentele de la un sport dat\n";
                cout<<"\n8 Afisati abonamentele pentru tipul de sport dorit\n";
                cout<<"\n9 Iesiti din abonamente\n";

                int comanda1;
                cin>>comanda1;
                switch(comanda1)
                {
                case 1:
                {
                    AbonamentDans* ad=new AbonamentDans;
                    cin>>*ad;
                    int ok=0;
                    for(auto &el1:mapAbonamente)
                    {
                        if(el1.first==(ad)->getNumeSport())
                        {
                            mapAbonamente[el1.first].push_back(ad);
                            ok=1;
                        }
                    }
                    if(ok==0)
                    {
                        mapAbonamente[ad->getNumeSport()].push_back(ad);
                    }

                    break;
                }
                case 2:
                 {
                    AbonamentInot* ai=new AbonamentInot;
                    cin>>*ai;
                    int ok=0;
                    for(auto &el1:mapAbonamente)
                    {
                        if(el1.first==(ai)->getNumeSport())
                        {
                            mapAbonamente[el1.first].push_back(ai);
                            ok=1;
                        }
                    }
                    if(ok==0)
                    {
                        mapAbonamente[ai->getNumeSport()].push_back(ai);
                    }
                    break;
                }
                case 3:
                 {
                    AbonamentAtletism* aa=new AbonamentAtletism;
                    cin>>*aa;
                    int ok=0;
                    for(auto &el1:mapAbonamente)
                    {
                        if(el1.first==(aa)->getNumeSport())
                        {
                            mapAbonamente[el1.first].push_back(aa);
                            ok=1;
                        }
                    }
                    if(ok==0)
                    {
                        mapAbonamente[aa->getNumeSport()].push_back(aa);
                    }
                    break;
                }
                case 4:
                 {
                    AbonamentCiclism* ac=new AbonamentCiclism;
                    cin>>*ac;
                    int ok=0;
                    for(auto &el1:mapAbonamente)
                    {
                        if(el1.first==(ac)->getNumeSport())
                        {
                            mapAbonamente[el1.first].push_back(ac);
                            ok=1;
                        }
                    }
                    if(ok==0)
                    {
                        mapAbonamente[ac->getNumeSport()].push_back(ac);
                    }
                    break;
                }
                case 5:
                 {
                    AbonamentTriathlon* atr=new AbonamentTriathlon;
                    cin>>*atr;
                    int ok=0;
                    for(auto &el1:mapAbonamente)
                    {
                        if(el1.first==(atr)->getNumeSport())
                        {
                            mapAbonamente[el1.first].push_back(atr);
                            ok=1;
                        }
                    }
                    if(ok==0)
                    {
                        mapAbonamente[atr->getNumeSport()].push_back(atr);
                    }
                    break;
                }
                //Afisati consumul pentru un tip de abonament
                case 6:
                    {
                    cout<<"\nScrieti sportul pentru care doriti sa vedeti consumul pentru toate abonamentele sale: ";
                    string nume_sp;
                    cin>>nume_sp;
                     int ok=0;
                     int i=1;
                     for(auto &abonament:mapAbonamente[nume_sp])
                     {   cout<<"\nPentru abonamentul "<<i<<":";
                         (*abonament).consum();
                         cout<<endl;
                         i++;
                        ok=1;

                     }
                     if(ok==0)
                      {cout<<"\nNu exista abonamente din aceasta categorie\n";}
                     break;
                    }
                case 7:
                    {
                    cout<<"\nScrieti sportul pentru care doriti sa vedeti pretul pentru toate abonametele sale: ";
                    string nume_sp;
                    cin>>nume_sp;
                     int ok=0;
                     int i=1;
                     for(auto &abonament:mapAbonamente[nume_sp])
                     {
                         cout<<"\nPretul abonamentului cu numarul "<<i<<" este: "<< (*abonament).preturi()<<" lei.";
                        i++;
                        ok=1;

                     }
                     if(ok==0)
                      {cout<<"\nNu exista abonamente din aceasta categorie\n";}
                     break;
                    }
                case 8:
                    {cout<<"\nScrieti sportul pentru care doriti sa vedeti abonamentele: ";
                    string nume_sp;
                    cin>>nume_sp;
                     int ok=0;
                     for(auto &abonament:mapAbonamente[nume_sp])
                     {   cout<<*abonament<<endl;
                        ok=1;

                     }
                     if(ok==0)
                      {cout<<"\nNu exista abonamente din aceasta categorie\n";}
                     break;
                   }

                case 9:
                {
                    k4=0;
                    break;
                }

                }
            }
            break;
        }

        case 100:
        {
            k=0;
            break;
        }
        }

    }
    for(auto &abonamentul:mapAbonamente)
{
    for(auto &abonament:abonamentul.second)
    {
        delete abonament;
    }
}
fin.close();
fout.close();
    return 0;
}
