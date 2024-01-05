#include "studentas.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <chrono>

void wtf(const std::vector<Studentas>& s, int num) {
    std::string name = "out" ;
    name.append(std::to_string(num));
    std::cout << name << std::endl;
    std::ofstream f(name);

    for (const Studentas& stud : s) {
        f << stud.getVardas() << " " << stud.getPavarde() << " " << stud.skaiciuotiGalutiniBala("Vid") << std::endl;
    }

    f.close();
}

void dalinimoBudas1(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsai, std::vector<Studentas>& balleriai, const std::string& skBudas) {
    auto pirmasKietas = std::find_if(studentai.begin(), studentai.end(), [&](const Studentas& s){
         return s.skaiciuotiGalutiniBala(skBudas) >= 5;
    });

    vargsai.assign(studentai.begin(), pirmasKietas);
    balleriai.assign(pirmasKietas, studentai.end());

    wtf(vargsai, 1);
    wtf(balleriai, 2);
}

void dalinimoBudas2(std::vector<Studentas>& studentai, std::vector<Studentas>& balleriai, const std::string& skBudas) {
    auto pirmasKietas = std::find_if(studentai.begin(), studentai.end(), [&](const Studentas& s){
        return s.skaiciuotiGalutiniBala(skBudas) >= 5;
    });

    balleriai.assign(pirmasKietas, studentai.end());
    studentai.resize(studentai.size() - balleriai.size());
    studentai.shrink_to_fit();

    wtf(studentai, 3);
    wtf(balleriai, 4);
}

double Studentas::skaiciuotiGalutiniBala(const std::string& tipas) const {
    if (tipas == "Vid") {
        double tarpiniuVidurkis = std::accumulate(tarpiniai_rezultatai.begin(), tarpiniai_rezultatai.end(), 0.0) / tarpiniai_rezultatai.size();
        return tarpiniuVidurkis;
    } else if (tipas == "Med") {
        std::vector<int> visiPazymiai = tarpiniai_rezultatai;
        visiPazymiai.push_back(egzamino_rezultatas);
        std::sort(visiPazymiai.begin(), visiPazymiai.end());

        int dydis = visiPazymiai.size();
        if (dydis % 2 == 0) {
            int vidurioIndeksas = dydis / 2;
            return (visiPazymiai[vidurioIndeksas - 1] + visiPazymiai[vidurioIndeksas]) / 2.0;
        } else {
            return visiPazymiai[dydis / 2];
        }
    } else {
        std::cout << "Netinkamas tipo, naudojamas vidurkis." << std::endl;
        double tarpiniuVidurkis = std::accumulate(tarpiniai_rezultatai.begin(), tarpiniai_rezultatai.end(), 0.0) / tarpiniai_rezultatai.size();
        return tarpiniuVidurkis;
    }
}

void ivestiDuomenisRanka(std::vector<Studentas>& studentai) {
    int studentuSkaicius;
    std::cout << "Iveskite studentu skaiciu: ";
    std::cin >> studentuSkaicius;

    studentai.resize(studentuSkaicius);

    for (int i = 0; i < studentuSkaicius; ++i) {
        std::string vardas, pavarde;
        int tarpinis;

        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::cin >> vardas;

        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::cin >> pavarde;

        std::vector<int> tarpiniai_rezultatai;

        std::cout << "Iveskite " << i + 1 << "-ojo studento tarpinius rezultatus (baigti su -1): ";
        while (true) {
            std::cin >> tarpinis;
            if (tarpinis == -1) {
                break;
            }
            tarpiniai_rezultatai.push_back(tarpinis);
        }

        int egzamino_rezultatas;
        std::cout << "Iveskite " << i + 1 << "-ojo studento egzamino rezultata: ";
        std::cin >> egzamino_rezultatas;

        studentai[i] = Studentas(vardas, pavarde, tarpiniai_rezultatai, egzamino_rezultatas);
    }
}


void skaitytiDuomenisIsFailo(std::vector<Studentas>& studentai, const std::string& failoPavadinimas) {
    std::ifstream failas(failoPavadinimas);

    if (!failas) {
        std::cout << "Nepavyko atidaryti failo." << std::endl;
        return;
    }

    std::string vardas, pavarde;
    std::vector<int> tarpiniai_rezultatai;
    int egzamino_rezultatas;

    while (failas >> vardas >> pavarde) {
        tarpiniai_rezultatai.clear();
        int pazymys;

        while (failas >> pazymys) {
            if (pazymys == -1) {
                break;
            }
            tarpiniai_rezultatai.push_back(pazymys);
        }

        failas >> egzamino_rezultatas;

        studentai.push_back(Studentas(vardas, pavarde, tarpiniai_rezultatai, egzamino_rezultatas));
    }

    failas.close();
}


void generuotiDuomenis(std::vector<Studentas>& studentai) {
    int studentuSkaicius;
    std::cout << "Iveskite studentu skaiciu: ";
    std::cin >> studentuSkaicius;

    studentai.resize(studentuSkaicius);

    for (int i = 0; i < studentuSkaicius; ++i) {
        std::string vardas, pavarde;
        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::cin >> vardas;

        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::cin >> pavarde;

        studentai[i] = Studentas(vardas, pavarde, {}, 0);

        for (int j = 0; j < 5; ++j) {
            int pazymys = rand() % 10 + 1;
            studentai[i].getTarpiniaiRezultatai().push_back(pazymys);
        }

        studentai[i].setEgzaminoRezultatas(rand() % 10 + 1);
    }
}







void generuotiFailus() {
    const std::vector<int> irasuSkaiciai = {1000, 10000, 100000, 1000000, 10000000};
    const std::string sabloninisVardas = "Vardas";
    const std::string sabloninePavarde = "Pavarde";

    for (int irasuSkaicius : irasuSkaiciai) {
        auto start = std::chrono::high_resolution_clock::now();

        std::string failoPavadinimas = "failas_" + std::to_string(irasuSkaicius) + ".txt";
        std::ofstream failas(failoPavadinimas);

        if (!failas) {
            std::cout << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
            return;
        }

        for (int i = 1; i <= irasuSkaicius; ++i) {
            failas << sabloninisVardas << i << " " << sabloninePavarde << i;

            for (int j = 0; j < 5; ++j) {
                int pazymys = rand() % 10 + 1;
                failas << " " << pazymys;
            }

            int egzaminoBalas = rand() % 10 + 1;
            failas << " " << egzaminoBalas << std::endl;
        }

        failas.close();
        auto end = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        std::cout << "Sukurtas failas: " << failoPavadinimas  << ", uztruko " << diff << "ms" << std::endl;
    }
}
void Studentas::padalintiStudentusIFailus(const std::vector<Studentas>& studentai, const std::string& failasVargsiukai, const std::string& failasLyderiai) {
    std::ofstream vargsiukaiFailas(failasVargsiukai);
    std::ofstream lyderiaiFailas(failasLyderiai);

    if (!vargsiukaiFailas || !lyderiaiFailas) {
        std::cout << "Nepavyko sukurti failu." << std::endl;
        return;
    }

    for (const auto& studentas : studentai) {
        double galutinis = studentas.skaiciuotiGalutiniBala("Vid");
        if (galutinis < 5.0) {
            vargsiukaiFailas << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        } else {
            lyderiaiFailas << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }
    }

    vargsiukaiFailas.close();
    lyderiaiFailas.close();
}
