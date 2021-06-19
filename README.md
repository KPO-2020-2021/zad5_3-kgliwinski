# Dragonfly 5.3


## Class diagram

![Class diagram](/readme_pics/class_diagram.png)

To see more indepth diagrams and documentation go to /documentation dir.

## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Example:

``` bash
> mkdir build && cd build
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make
> ./main         # Runs program
> make test      # Makes and runs the tests.
> make coverage  # Generate a coverage report.
> make doc       # Generate html documentation.
```

## Running
Program does everything that the task obliged it to do. It is fully functional, has the modification implemented (see in menu), everything is tested and seems to work fine.

## Documentation
To see documentation go to /documentation dir and search for index.html. You can generate your own documentation in doxygen using:
```
make doc
```
in the build dir.

## Tests

Tests are made using doctests.
There are two different ways to initiate tests:
``` bash
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make
> ./unit_tests
```
OR:
``` bash
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make fulltest
```

Results of tests on my local machine: (using *./unit_tests*)
```
===============================================================================
[doctest] test cases: 411 | 411 passed | 0 failed | 0 skipped
[doctest] assertions: 929 | 929 passed | 0 failed |
[doctest] Status: SUCCESS!
```
There are tests included for counting Vectors, class inheritence, all algebraic operations on vectors and matrices,
cuboid and prism contruction assertion and more.

**Important note:** there are problems while using *make fulltest* command. Tests that write data to *.dat* files will be shown as failed while using this command.
In case *./unit_tests* is used, all tests have success status. The problematic tests have also been done manually and everything seems to work good.

## datasets directory
It is important for the program to work that there is a datasets directory (that also includes main dircetory which contains final and sample dirs) for the file to operate. Here is a simple diagram:
```
|----zad5_3-kgliwinski
|    |----datasets
|         |----main
|              |---final
|              |---sample
```

# Informacje w kontekście zadania dron 5.3
Zawarte informacje o zrealizowanych rozszerzeniach i ogólnej funkcjonalności programu w kontekście zadania projektowego.

## Program realizuje podstawowe założenia zadania
         1. Zachowana funkcjonalność z fazy 5.2 (włącznie z rozszerzeniami z tego zadania)
         2. Dron nie wyladuje na zadnej z przeszkod.
         3. Obrys rzutu drona na XY jest okręgiem,
            figur pochodnych z prostopadloscianu prostokatem,
            natomiast pochodnych z graniastoslupa szesciokatnego - okregiem.
         4. Drony sa alokowane dynamicznie na std::vector
         5. Zastosowane sa metoody wirtualne pochodzace z klasy Block (klasy bazowej figur)
         6. Obiekty znajduja sie na liscie, na tej samej liscie sa rowniez umieszczone drony

## Zrealizowane rozszerzenia
         1. Dron autonomicznie wybiera najblizsze miejsce ladowania jesli nie moze wyladowac tam gdzie sie znajduje.
         2. Procesowi wybierania towarzyszy rysowanie w Gnuplocie stozka szesciokatnego - reprezentuje on pole widzenia drona
            i rzeczywiście nim jest.

## Komentarze
         1. Wybieranie miejsca do ladowania przebiega nastepujaco: najmniejszy promien obszaru ktory dron rozwaza to 10
            co kazda iteracje (jesli dron nie znajdzie miejca) promien zwieksza sie o 1.
         2. Drony sa jednoczesnie na liscie obiektow oraz na ich wlasnym std::vector
         3. Drony czasem nie laduja mimo ze w teorii jest na to miejsce. Jest to spowodowane dodaniem marginesu bledu 
            (ktory w prawdziwym dronie by sie pojawil) i przez to raczej nie uswiadczymy drona ladujacego na styk przy przeszkodzie

## Przykładowa sciezka w programie aby pokazac funkcjonalnosc programu
         1. Włącz program ( ./main )
         2. p ---> 45 (kierunek lotu) ---> 121 (dlugosc lotu)
         3. Dron nie moze wyladowac w tym miejscu. Rysowany jest stozek kamery drona i wybierane jest miejsce ladowania. Dron laduje.
         4. p ---> 180 (kierunek lotu) ---> 35 (dlugosc lotu)
         5. Dron nie jest bezposrednio nad figura, lecz wciaz program wykrywa ze dron nie moze ladowac. Powtorka z pt. 3
         6. a ---> 2 (wybor drugiego drona)
         7. p ---> 315 (kierunek lotu) ---> 242 (dlugosc lotu) 
         8. Dron jest miedzy dwoma przeszkodami. Powtorka z pt. 3
         9. d (dodaj element) ---> 6 (Wulkan) ---> 150 150 70 (ogromna skala taka ze obiekt prawie wychodzi poza plansze) ---> 150 150 (polozenie na srodku planszy)
         10. p ---> 180 (kierunek) ---> 180 (dlugosc) 
         11. Dron nad jedna, bardzo duza przeszkoda, rysowany jest duzy obszar szukajacy miejsca do ladowania, w koncu dron laduje tam gdzie moze.
         12. u ---> 7 (usuniecie duzego wulkanu ktory stworzylismy)
         13. p ---> 180 (kierunek) ---> 150 (dlugosc)
         14. Dron laduje bez problemu

## Druga ścieżka, aby pokazać że drony nie lądują na sobie
         1. Włącz program ( ./main )
         2. p --- > 75 ---> 180
         3. Dron jest nad plaskowyzem, jednak nie laduje na dronie (mimo ze jesli by go nie widzial to tak by raczej zrobil)
         4. p --- > 180 ---> 65
         5. Dron znajduje sie nad innym dronem, omija go i laduje w odpowiednim miejscu
