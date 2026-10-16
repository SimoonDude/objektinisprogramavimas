# objektinisprogramavimas

## v0.3 konteinerių testavimas

### Sistema

- CPU: Intel Xeon Platinum 8370C, 2 branduoliai, 2,80 GHz
- RAM: 7,8 GiB
- Diskas: virtualus SSD (darbo disko `ROTA=0`)
- Kompiliatorius: `g++`, `-std=c++17 -O2`

Matuota su  `studentai10000.txt`, `studentai100000.txt` ir
`studentai1000000.txt` failais. Skirstymas atliktas į `islaike` ir
`neislaike` grupes, rezultatai įrašyti į du failus. Kiekvienas testas kartotas
5 kartus, lentelėje pateikti vidurkiai sekundėmis. Rikiavimas išjungtas.

### Rezultatai

#### `std::vector`
| Įrašų skaičius | Skaitymas | Skirstymas | Įrašymas į failus |
|---:|:---:|---:|---:|
| 10 000 | 0.020024 | 0.002376 | 0.017435 |
| 100 000 | 0.289048 | 0.021513 | 0.146705 |
| 1 000 000 | 1.100530 | 0.178681 | 1.534361 |
#### `std::list`
| Įrašų skaičius | Skaitymas | Skirstymas | Įrašymas į failus |
|---:|:---:|:---:|---:|
| 10 000 | 0.027613 | 0.007547 | 0.012833 |
| 100 000 | 0.288874 | 0.069823 | 0.125358 |
| 1 000 000 | 1.074310 | 0.319281 | 1.670242 |
### Išvada

`std::vector` skirstymą atliko greičiau. `std::list` įrašymas į failus buvo
šiek tiek greitesnis su 10 000 ir 100 000 įrašų, tačiau su 1 000 000 įrašų
greitesnis buvo `std::vector`. Bendras `std::vector` rezultatas buvo geresnis.