# Objektinis programavimas — Studentų galutinių balų skaičiavimas

## Projekto aprašymas

Programa skirta studentų namų darbų ir egzamino rezultatams apdoroti bei galutiniam balui apskaičiuoti.

Projekto metu realizuojamas studentų duomenų įvedimas, apdorojimas, grupavimas į dvi kategorijas ir skirtingų konteinerių bei algoritmų veikimo spartos tyrimas.

## Versijos ir jų pakeitimai

### `v.pradinė`

- Sukurta pradinė studentų duomenų apdorojimo programa. (su `std::vector`)
- Realizuotas studento duomenų saugojimas naudojant `struct`.
- Realizuotas namų darbų vidurkio ir medianos skaičiavimas.
- Pridėtas kintamas namų darbų skaičius, atsitiktinių pažymių generavimas ir pasirinkimų meniu.
- Pridėtas duomenų nuskaitymas iš failo.

### `v0.1`


- Studentai generuojami pagal geresnį algoritmą.
- Studentai surūšiuojami pagal pasirinktą kriterijų.
- Stulpeliai išlygiuojami, galutiniai balai pateikiami dviejų skaičių po kablelio tikslumu.

### `v0.2`

- Studentai skirstomi į išlaikiusius ir neišlaikiusius (pirmoji strategija).
- Simplifikuota struktūra, iškeltas funkcionalumas į header'ius
- Funkcionalumas algoritmų spartos matavimui
- Studentų vardų, pavardžių generavimas, randominiam režime

### `v0.3`

- Realizuota antroji bei trečioji veikimo strategija.
- Ištirtas `vector` ir `list` konteinerių veikimo efektyvumas; jų skirtumai.
- Išbandyti skirtingi C++ algoritmai studentų skirstymo procedūrai optimizuoti.


### `v1.0`

- Pasirinkta naudoti trečiąją strategiją.
- Ištaisyti galutinės klaidos, galutinai testuota.
- Parengtos programos kompiliavimo ir paleidimo instrukcijos.

---

## Programos reikalavimai

- C++ kompiliatorius, palaikantis C++17.
- `make` įrankis (jei naudojamas Makefile).
- Git – pasirinktinai, jei norima atsisiųsti ir valdyti projekto šaltinio kodą.

## Įdiegimas ir kompiliavimas

### 1. Projekto atsisiuntimas

```bash
git clone <REPOSITORY_URL>
cd objektinisprogramavimas
```

### 2. Programos kompiliavimas

Projekto šakniniame kataloge vykdyti:

```bash
make
```

Kompiliavimo metu sukuriamas vykdomasis failas `studentai`.

### 3. Programos paleidimas

Linux arba „GitHub Codespaces“ aplinkoje:

```bash
./studentai
```

Jeigu `make` nėra įdiegtas, programą galima kompiliuoti tiesiogiai:

```bash
g++ -std=c++17 -Wall -Wextra -O2 1uzd.cpp -o studentai
```

## Naudojimosi instrukcija

1. Paleisti programą pagal aukščiau pateiktas instrukcijas.
2. Pasirinkti norimą operaciją programos meniu:
    1) Įvesti studentų duomenis pačiam.
    2) Apdoroti turimus duomenis.
    3) Sugeneruoti pažymius turimems studentams
    4) Sugeneruoti ne tik pažymius bet ir studentus
4. Pasirinkti kur išvesti, ir prireikus, suvesti failo pavadinimą.
5. Pasirinkti galutinio balo rūšiavimo būdą.
6. Peržiūrėti apskaičiuotus rezultatus ir studentų suskirstymą į kategorijas.
7. Jeigu norima, ištestuoti programos veikimo spartą su "Debug" pasirinkimu ir failais `benchmark-data/`.

## Studentų skirstymo strategijos

Studentai suskirstomi į dvi grupes pagal galutinio balo kriterijų:

- **Vargšiukai** – studentai, kurių galutinis balas mažesnis už nustatytą ribą.
- **Kietiakai** – studentai, kurių galutinis balas yra lygus ribai arba ją viršija.

Skirstymo riba. Laikoma išlaikyta, jeigu

$ vidurkis_{nd} * 0,4 + egzaminas * 0,6 \geq 5 $

### 1 strategija – du nauji konteineriai

Sukuriami nauji `vargsiukai` ir `kietiakai` konteineriai. Studentai nukopijuojami į atitinkamą grupę, o pradinis `studentai` konteineris lieka išsaugotas. 

### 2 strategija – vienas naujas konteineris

Sukuriamas tik `vargsiukai` konteineris. Silpnesni studentai perkeliami į jį, o iš pradinio konteinerio pašalinami. Po skirstymo pradiniame konteineryje lieka tik kietiakai. Tai išbandyta su `std::remove_copy_if` ir `vector::erase`.

### 3 strategija – optimizuotas skirstymas

Taikomi efektyvesni algoritmai arba konteinerių metodai, atsižvelgiant į ankstesnių strategijų rezultatus bei `vector` ir `list` ypatybes.
Pasirinkta naudoti `std::partition`.

## Eksperimentų metodika

Eksperimentų tikslas – palyginti skirtingų programos įgyvendinimų strategijų veikimo spartą ir įvertinti, kokią įtaką daro įvariūs algoritmai bei konteineriai.

### Testavimo aplinka

- CPU: Intel Xeon Platinum 8370C, 2 branduoliai, 2,80 GHz
- RAM: 7,8 GiB
- Diskas: virtualus SSD (darbo disko `ROTA=0`)
- Kompiliatorius: `g++`, `-std=c++17 -O2`

### Naudoti duomenų rinkiniai

Eksperimentams naudojami iš anksto sugeneruoti failai:

| Studentų skaičius | Failo pavadinimas | Paskirtis |
|---:|---|---|
| 10 000 | `studentai10000.txt` | Mažesnio rinkinio testas |
| 100 000 | `studentai100000.txt` | Vidutinio rinkinio testas |
| 1 000 000 | `studentai1000000.txt` | Didelio rinkinio testas |

Kiekviena strategija testuojama su tais pačiais duomenų rinkiniais. Kiekvienas bandymas atliekamas iš naujo paruošus pradinį konteinerį. Skaičiuojamas kelių bandymų laiko vidurkis.

Matavimo metu į laiką neįtraukiama įvairi informacijos manipuliacija (pvz.apskaičiavimas vidurkių) ar kitos operacijos, kurios nėra tiesiogiai susijusios su failais ar nėra intensyvios resursų ar laiko sąnaudos atžvilgiu.

### Rezultatai

Projekto eigos metu buvo keletą kartų testuota įvairūs konteineriai ir strategijos (pvz. pirmoji) ir, kartu, rezultatai išsaugoti. Galima pamatyti juos čia:

Laikas visur milisekundėmis (ms).

| Įrašų skaičius | Skaitymas | Skirstymas | Įrašymas į failus |
|---:|:---:|---:|---:|
`std::vector`
| 10 000 | 0.020024 | 0.002376 | 0.017435 |
| 100 000 | 0.289048 | 0.021513 | 0.146705 |
| 1 000 000 | 1.100530 | 0.178681 | 1.534361 |
`std::list`
| 10 000 | 0.027613 | 0.007547 | 0.012833 |
| 100 000 | 0.288874 | 0.069823 | 0.125358 |
| 1 000 000 | 1.074310 | 0.319281 | 1.670242 |

#### Galutinių ezultatų palyginimas: `std::vector`

| Įrašų skaičius | Skaitymas | Skirstymas | Įrašymas į failus |
|---:|---:|---:|---:|
| 10,000 | 0.017334 | 0.000008 | 0.013997 |
| 100,000 | 0.192781 | 0.000515 | 0.119963 |
| 1,000,000 | 1.243102 | 0.005943 | 1.348206 |

#### Galutinių rezultatų palyginimas: `std::list`

| Įrašų skaičius | Skaitymas | Skirstymas | Įrašymas į failus |
|---:|---:|---:|---:|
| 10,000 | 0.023973 | 0.000119 | 0.011529 |
| 100,000 | 0.250550 | 0.011444 | 0.129109 |
| 1,000,000 | 1.226978 | 0.181761 | 1.566027 |

## Galutinės išvados

Visų pirma, galima pastebėti, kad `std::vector` konteineris yra geriausias pasižymintis savo greičiu ir paprastumu. Antra, kad labai svarbi yra naudojama duomenų manipuliacijos strategija – nuo jos priklauso iki 20x efektyvumo pokytis.
Galų gale galima paminėti šis projektas yra geras apšilimas vėlesniam darbui su C++.

### TODO

Norėčiau netolimoje ateityje pereiti prie `template`'u. Šiuo metu egzistuoja skirtingos struktūros su `std::list` ir `std::vector`.

### Papildomi komentarai

<img width="656" height="50" alt="{009B9741-B639-469F-80A3-92D4BEF856D2}" src="https://github.com/user-attachments/assets/6561230b-3892-4733-98d2-fe40ba4f4ff4" />