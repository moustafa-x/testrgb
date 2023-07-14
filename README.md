# Installation RGB
Dans cette situation, nous avons utilisé Arduino Uno et un système d'exploitation en temps réel (RTOS) appelé Trampoline. Nous avons créé des tâches pour contrôler l'allumage des LED afin de créer un jeu de couleurs (RGB).

Linstallation est réalisée sur une Ubuntu 16.04.2 LTS. Il faut ajouter les extensions pour l'USB sur la machine virtuelle (VirtualBox utilisé) [VirtualBox Oracle VM VirtualBox Extension Pack](https://www.virtualbox.org/wiki/Downloads), et faire en sorte que le périphérique soit pris en charge en priorité par la machine virtuelle: `Devices->USB->USB settings…`.

## Préparation Linux

### Les outils de base pour le développement

```sh
sudo bash
export https://github.com/moustafa-x/testrgb.git
apt-get update

```

Le cross-compilateur gcc vers la cible ARM:

```sh
sudo apt-get install avr-libc gcc-avr avrdude
```

Si vous utilisez une Ubuntu 16.04 LTS, il faudra recompiler OpenOCD. Il faut alors installer la bibliothèque hidapi (ce n'est pas nécessaire pour une Ubuntu 18.04 LTS).

```sh
apt-get install libhidapi-dev libhidapi-libusb0
```

Plus besoin d'être super-utilisateur à partir de maintenant:

```sh
exit
```

Installation des **Guest additions**, puis redémarrage.

### OpenOCD
C'est l'outil qui va permettre de faire l'interface entre La carte SAMD21, et le debugger `gdb`.

#### Sur Ubuntu 16.04 LTS
La version proposée sur Ubuntu est la 0.9, mais elle n'a pas le support de l'interface `CMSIS-DAP`. Donc on recompile l'outil à partir des sources. 

On télécharge les sources sur le site [d'openocd](http://openocd.org/).

```sh
tar xvjf openocd-0.10.0.tar.bz2
cd openocd-0.10.0/
 ./configure --enable-cmsis-dap  
make
sudo make install
```

#### Sur Ubuntu 18.04 LTS
Le paquet est suffisamment récent:

```sh
sudo apt-get install openocd
```

## Trampoline
### sources
Récupération des sources

```sh
git clone --depth 1 https://github.com/TrampolineRTOS/trampoline.git
```
### goil

```sh
cd trampoline/goil/makefile-unix
./build+release.py
sudo cp goil /usr/local/bin
```

## Test de compilation d'une application

Exemple de base permettant de faire clignoter la LED0 (`PB30`), avec une tâche périodique.

```sh
cd trampoline/examples/avr/arduinoUno/blink
goil --target=avr/arduinoUno--templates=../../../../../../goil/templates/ blink.oil
./make.py
sudo ./make.py flash
```





Récupérer le contenu du test: 

* soit en téléchargeant l'archive directement. Il y a un bouton avec une flèche vers le bas dans l'interface gitlab, à droite de l'icone `find file`.
* soit, en faisant un clone git directement (beaucoup mieux!):

```sh
git clone  https://github.com/moustafa-x/testrgb.git
```



* le fichier `rgb.oil` qui définit votre architecture fonctionnelle
* un squelette d'application `rgb.cpp`

Dans le fichier `.oil`, Il sera nécessaire de modifier l'attribut `TRAMPOLINE\_BASE\_PATH` pour indiquer le dossier d'installation de Trampoline.

La première fois, il est nécessaire d'exécuter le compilateur `goil` directement:

```sh
goil --target=avr/arduino/uno --templates=../../../../goil/templates/ blink.oil

Le compilateur `goil` génère alors non seulement les structures de données internes utilisées par l'OS, mais aussi les scripts de compilation `make.py`. 

Maintenant il ne sera plus nécessaire d'appeler la commande `goil` directement: si le fichier `.oil` est mis à jour, alors le script de compilation fera le nécessaire pour appeler `goil` et reconstruire l'exécutable.

Les 2 commandes utiles sont alors:

```sh
./make.py
```

pour générer l'exécutable (format.elf), et:

```sh
sudo ./make.py flash
```

pour envoyer l'exécutable sur la carte.
