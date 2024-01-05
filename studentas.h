#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED
#include <iomanip>
#include <string>
#include <vector>

class Zmogus {
protected:
    std::string vardas, pavarde;

    Zmogus(std::string vardas = "", std::string pavarde = "")
        : vardas(vardas), pavarde(pavarde) {}

public:
    virtual std::string getVardas() const = 0;
    virtual std::string getPavarde() const = 0;
};
class Studentas: public Zmogus {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> tarpiniai_rezultatai;
    int egzamino_rezultatas;

public:
    // Konstruktorius
    Studentas(std::string v, std::string p, std::vector<int> tr, int er)
        : Zmogus(v, p), tarpiniai_rezultatai(tr), egzamino_rezultatas(er) {}
    ~Studentas(){tarpiniai_rezultatai.clear();}
    Studentas(const Studentas& s):Zmogus(s.vardas, s.pavarde), tarpiniai_rezultatai(s.tarpiniai_rezultatai), egzamino_rezultatas(s.egzamino_rezultatas){}
    Studentas& operator=(const Studentas& s) {
        if (&s == this) return *this;

        vardas = s.vardas;
        pavarde = s.pavarde;
        tarpiniai_rezultatai = s.tarpiniai_rezultatai;
        egzamino_rezultatas = s.egzamino_rezultatas;


        return *this;
    }
    // Get metodai
    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    int getEgzaminoRezultatas() const { return egzamino_rezultatas; }
    std::vector<int>& getTarpiniaiRezultatai() { return tarpiniai_rezultatai; }
    Studentas() {}
    // Kitos funkcijos
    double skaiciuotiGalutiniBala(const std::string& tipas) const;
    void setEgzaminoRezultatas(int rez) {this->egzamino_rezultatas= rez;}
    void padalintiStudentusIFailus(const std::vector<Studentas>& studentai, const std::string& failasVargsiukai, const std::string& failasLyderiai);
    double skaiciuotiGalutiniBala(const Studentas& studentas, const char tipas[]);

    friend void operator>>(std::istream& in, Studentas& s) {
        int pazymys;
        in >> s.vardas >> s.pavarde;
    }

    friend std::ostream& operator<<(std::ostream& out, const Studentas& stud) {
        out << std::left << std::setw(20) << stud.getVardas() << std::setw(20) << stud.getPavarde()
        << std::fixed << std::setprecision(2) << stud.skaiciuotiGalutiniBala("Vid");
    return out;
}
};

void dalinimoBudas1(std::vector<Studentas>&, std::vector<Studentas>&, std::vector<Studentas>&, const std::string&);
void dalinimoBudas2(std::vector<Studentas>&, std::vector<Studentas>&, const std::string&);
void ivestiDuomenisRanka(std::vector<Studentas>& studentai);
void skaitytiDuomenisIsFailo(std::vector<Studentas>& studentai, const std::string& failoPavadinimas);
void generuotiDuomenis(std::vector<Studentas>& studentai);
void generuotiFailus();
void padalintiStudentusIFailus(const std::vector<Studentas>& studentai, const std::string& failasVargsiukai, const std::string& failasLyderiai);
double skaiciuotiGalutiniBala(const Studentas& studentas, const std::string& tipas);

#endif
