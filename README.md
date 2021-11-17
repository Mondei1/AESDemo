# AESDemo
**— The following are instructions in german for by research paper about AES. —**

Dieses Programm dient als Eigenanteil für meine Belegarbeit und demonstriert die funktionsweise von AES.

## Bibliotheken
* [tiny-AES-c](https://github.com/kokke/tiny-AES-c) - Eine kleine Bibliothek die, die AES implementiert.
* [bonybrown/tiny-AES128-C](https://github.com/bonybrown/tiny-AES128-C) - Ein Fork von tiny-AES-c woher die
`pkcs7_padding.c` und `pkcs7_padding.h` stammen.

## Kompilieren
Um dieses Programm auszuführen sind folgende Tools notwendig:
* G++
* CMake
* Make

1. Klonen des Repositories
```shell
git clone https://github.com/Mondei1/AESDemo
```

2. Wechsel in den neuen Ordner & generiere Makefile
```shell
cd AESDemo
cmake CMakeLists.txt
```

3. Kompilieren
```shell
make
```

4. Ausführen
```shell
./AESDemo
```

## Entwicklungsumgebung
Das Programm wurde unter folgenden Voraussetzungen programmiert und getestet:

| Name       	| Version 	|
|------------	|---------	|
| Arch Linux 	| -       	|
| `g++`      	| 11.1.0  	|
| `cmake`    	| 3.21.4  	|
| `make`     	| 4.3     	|
| `gtkmm`       | 4.0       | 

Ich habe keine Ahnung ob dieses Programm ohne weiteres auf Windows bauen und ausführen wird.