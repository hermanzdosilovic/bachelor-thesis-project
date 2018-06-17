# Demonstracija sustava za određivanje strukture teksta na temelju položaja pojedinih znakova

## 1. Prevođenje izvornog kôda
Da biste uspješno preveli izvorni kôd trebate imati prevoditelj GCC verzije 8 ili više.

1. Pozicionirajte se u vršni direktorij projekta.
2. Napravite `build` direktorij koji će se nalaziti u vršnom dikretoriju projekta:
  ```bash
  mkdir build
  ```
3. Pozicionirajte se u direktorij `build` i pokrenite `cmake`:
  ```bash
    cmake -DCMAKE_BUILD_TYPE=Release .. # ili -DCMAKE_BUILD_TYPE=Debug
    ```
4. Pokrenite `make`:
  ```
    make
    ```

## 2. Pokretanje sustava
Nakon prevođenja, pokrenite `LayouterDemo` program sa zastavicom `--help` kako biste vidjeli popis svih dostupnih zastavica i njihove zadane vrijednosti:
```bash
./LayouterDemo --help
```

Pokretanje programa `LayouterDemo`, bez zastavica, pokreće demonstraciju rada sustava koji koristi *maxoverlap* algoritam za određivanje linija i *avgcenterdist* algoritam za rastavljanje riječi s optimalnim parametrima navedenima u radu:
```bash
$ ./LayouterDemo
-----------------------------------------------------------------------
|         |    min    |    avg    |    med    |    max    |    top    |
-----------------------------------------------------------------------
| aligner |  0.821555 |  0.985377 |  1.000000 |  1.000000 |  0.570000 |
| spacer  |  0.826709 |  0.985173 |  1.000000 |  1.000000 |  0.540000 |
-----------------------------------------------------------------------
```

Korištenjem zastavice `--show-output` dobit ćete ispis OCR-rezultata u formatu opisanom u pododjeljku 4.2.3 završnog rada.

## 3. Pokretanje ispitivanja sustava
Nakon prevođenja, možete pokrenuti ispitivanje sustava:
```bash
./LayouterTest
```

Ispitivanje provjerava jesu li zadovoljene dobivene točnosti za definirane parametre.

## 4. Dobivanje grafa točnosti
Za dobivanje grafa točnosti u formatu PNG koristi se biblioteka [matplotlib-cpp](https://github.com/lava/matplotlib-cpp) koja koristi Python biblioteke [matplotlib](https://matplotlib.org/index.html) i [numpy](http://www.numpy.org/). Prije prevođenja kôda trebate instalirati te dvije biblioteke. Pratite upute biblioteke *matplotlib-cpp* za detaljnije informacije o instalaciji Python biblioteka o kojima biblioteka *matplotlib-cpp* ovisi.

Nakon uspješne instalacije potrebnih biblioteka, morate ponovo prevesti izvorni kôd koristeći dodatnu zastavicu `-DLayouterDemo_USE_MATPLOTLIB=ON`:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DLayouterDemo_USE_MATPLOTLIB=ON ..
make
```

Sada će se pokretanjem programa `LayouterDemo` automatski stvoriti slika s grafom točnosti. Ime datoteke ovisi koje ste algoritme pokrenuli i za koju primjenu (engl. *use-case*).

Ako pokrenete `LayouterDemo` program bez zastavica, stvorit će se datoteka imena
`Receipt-annotated-maxoverlap-avgcenterdist.png`:

![Imgur](https://i.imgur.com/gBjwMWz.png)
