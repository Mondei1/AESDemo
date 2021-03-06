<h1 align="center">AESDemo</h1>
<p align="center">— The following are instructions in german for my research paper about the AES. —</p>

Dieses Programm dient als Eigenanteil für meine Belegarbeit und demonstriert die Funktionsweise von AES.

![Screenshot of AESDemo](https://raw.githubusercontent.com/Mondei1/AESDemo/main/aesdemo/img/screenshot.png)

## Bibliotheken
* [Crypto++](https://cryptopp.com/) - Eine sehr umfassende Kryptografie Bibliothek. Von ihr verwende ich Funktionen
um AES, KDF und Hex Operationen durchzuführen.

## Kompilieren
Um dieses Programm zu bauen und auszuführen sind folgende Tools notwendig:
* G++
* CMake
* Make
* Crypto++ (`pacman -S crypto++` oder `apt install libcrypto++8` | Für andere: [pkgs.org](https://pkgs.org/search/?q=crypto%2B%2B))

1. Klonen des Repositories
```shell
git clone https://github.com/Mondei1/AESDemo
```

2. Wechsel in den neuen Ordner & generiere Makefile
```shell
cd AESDemo
mkdir build && cd build
cmake ..
```

3. Kompilieren
```shell
make
```

4. Ausführen
```shell
./AESDemo
```

## Struktureller Aufbau
| Pfad       	                            | Zweck 	|
|------------	                            |---------	|
|`aesdemo/aesdemo/main.cpp`                 | Beinhaltet die Hauptklasse, welche nur GTK initialisiert.
|`libaesdemo/libaesdemo/`                   | Beinhaltet den eigentlichen Programmcode.
|`libaesdemo/libaesdemo/Crypto.cpp`         | Ist ein kleiner Wrapper um Crypto++ um Operationen einfacher zu machen.
|`libaesdemo/libaesdemo/MainWindows.cpp`    | Beinhaltet den GTK Code und regelt die Logik vom grafischen Fenster.
|`libaesdemo/libaesdemo/Utils.cpp`          | Beinhaltet nur kleine Helferfunktionen.

## Entwicklungsumgebung
Das Programm wurde unter folgenden Voraussetzungen programmiert und getestet:

| Name       	| Version 	|
|------------	|---------	|
| Arch Linux 	| -       	|
| `g++`      	| 11.1.0  	|
| `cmake`    	| 3.21.4  	|
| `make`     	| 4.3     	|
| `gtkmm`       | 4.0       | 
| `crypto++`    | 8.5.0

Ich habe keine Ahnung ob dieses Programm ohne weiteres auf Windows bauen und ausführen wird.
