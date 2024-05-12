#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student
{
    std::string ime;
    std::string prezime;
    double prosjek;

    bool operator<(const Student &s) const
    {
        return prosjek > s.prosjek;
    }
};

int main()
{
    std::vector<Student> ucenici;
    int n;
    std::string ime, prezime;
    double prosjek;
    std::ifstream ulaz("ucenici.bin", std::ios::binary);
    while (ulaz.read((char *)&ime, sizeof(ime)))
    {
        ulaz.read((char *)&prezime, sizeof(prezime));
        ulaz.read((char *)&prosjek, sizeof(prosjek));
        ucenici.push_back({ime, prezime, prosjek});
    }
    ulaz.close();
    std::cout << "Unesite broj novih ucenika: ";
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cout << "Unesite ime, prezime i prosjek " << i + 1 << ". ucenika: ";
        std::cin >> ime >> prezime >> prosjek;
        ucenici.push_back({ime, prezime, prosjek});
    }
    std::sort(ucenici.begin(), ucenici.end());
    std::ofstream izlaz("ucenici.bin", std::ios::binary | std::ios::trunc);
    for (const auto &ucenik : ucenici)
    {
        izlaz.write((char *)&ucenik.ime, sizeof(ucenik.ime));
        izlaz.write((char *)&ucenik.prezime, sizeof(ucenik.prezime));
        izlaz.write((char *)&ucenik.prosjek, sizeof(ucenik.prosjek));
    }
    izlaz.close();

    return 0;
}
