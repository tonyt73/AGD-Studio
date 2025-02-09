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
* Produces AGD compiler output very quickly

Themes:
* Multiple user selectable UI themes
* Dockable content editors and helper panel
  * Future improvements:
    * Save layout per project

Coming Soon! (In no particular order)
* Build system improvements with lessons from MPAGD build (Kees Van Oss)
* Better Machine support
  * More machines (with testing once the above build process is finished)
  * Possibly a Machine configuration UI feature
    * Allow you to define your own new machines
    * Graphics
    * Build process
    * etc     
* Finish the Image editor toolset
* Custom sounds support
* Nameable Objects/Sprites
  * Names can be used in source code
* MPAGD Generate code feature

**Getting very close to a v1.0 release.**

## Releases
https://github.com/tonyt73/AGD-Studio/releases

## Build Instructions

* Clone this repo on to your PC
* Download and Install the Embarcardero Rad-Studio C++ Community Edition
  * https://www.embarcadero.com/products/cbuilder/starter/free-download
  * Register if you need to (its free)
  * I personally use Rad Studio 12.0
* Download the trial version of LMD Innovative components
  * http://files.lmd.de/downloads/
  * Unzip and run the Setup application
  * Click Next to all questions to Install all defaults

* Install the latest release
  * This will install all the configuration files and the example project

* Launch the Rad-Studio IDE
  * Open the AGD Studio.cproj file from File > Open Project
  * Press F9 to build and run the application

