<img src="Screenshots/Welcome.png" width="512">

[![license](https://img.shields.io/github/license/tonyt73/agd-studio?style=for-the-badge)](./LICENSE.txt)
[![release](https://img.shields.io/github/v/release/tonyt73/agd-studio?include_prereleases&style=for-the-badge)](https://github.com/tonyt73/AGD-Studio/releases)
[![downloads](https://img.shields.io/github/downloads/tonyt73/agd-studio/total?style=for-the-badge)](https://github.com/tonyt73/AGD-Studio/releases)
[![latest](https://img.shields.io/github/downloads/tonyt73/agd-studio/latest/total?sort=semver&style=for-the-badge)](https://github.com/tonyt73/AGD-Studio/releases)

![stars](https://img.shields.io/github/stars/tonyt73/agd-studio?style=social)
![forks](https://img.shields.io/github/forks/tonyt73/agd-studio?style=social)
![watchers](https://img.shields.io/github/watchers/tonyt73/agd-studio?style=social)




# An IDE for Jonathan Cauldwell's Arcade Game Designer

<img src="Screenshots/IDE.png" height=400>

Editors for:
* Images 
  * Sprites
  * Objects
  * Tiles/Blocks
* Events (Code)
  * Syntax highlighting editor
    * AGD syntax
    * Asm syntax (TBD)
  * Code folding
* Map
* Messages
* Window size and position
* Keys

Automated build system:
* Produces AGD compiler output on the fly
* Automatic compiled output

Themes:
* Multiple user selectable UI themes
* Dockable content editors and helper panel
  * Future improvements:
    * Save layout per project

## Releases
https://github.com/tonyt73/AGD-Studio/releases

## Build Instructions

* Clone this repo on to your PC
* Download and Install the Embarcardero Rad-Studio C++ Community Edition
  * https://www.embarcadero.com/products/cbuilder/starter/free-download
  * Register if you need to (its free)
  * Install the 32 bit and 64 bit Windows compilers (OSX, iOS & Android are optional)
  * I personally use Rad Studio 11.2
* Download the trial version of LMD Innovative components
  * http://files.lmd.de/downloads/
  * Unzip and run the Setup application
  * Click Next to all questions to Install all defaults

* Install the latest release
  * This will install all the configuration files and the example project

* Launch the Rad-Studio IDE
  * Open the AGD Studio.cproj file from File > Open Project
  * Press F9 to build and run the application

