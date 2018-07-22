# AGDX-Studio
An integrated development environment for AGD

Editors for:
* Images (Sprites, Objects, Tiles/Blocks)
* Map
* Messages
* Events (Code)
  * Syntax highlighting editor
  * Code folding

Automated build system:
* Produces AGD compiler output on the fly
* Automatic compiled output

Themes:
* Multiple user selectable UI themes
* Dockable content editors and helper panel


## Build Instructions

* Clone this repo on to your PC
* Download and Install the Embarcardero Rad-Studio C++ Community Edition
  * https://www.embarcadero.com/products/cbuilder/starter
  * Register if you need to (its free)
  * Install the 32 bit and 64 bit Windows compilers (OSX, iOS & Android are optional)
* Download the trial version of LMD Innovative components
  * http://files.lmd.de/downloads/lmd2018vcl/setupvcl18td25.zip
  * Unzip and run the Setup application
  * Click Next to all questions to Install all defaults
* Install the Application Configuration files
  * Open up the location you cloned this repo to
  * Move the ```Config``` folder to ```%AppData%```
    * Hint: Copy the above uri and paste into Windows Explorer
  * Rename the ```Config``` folder to ```AGDX Studio```
* Launch the Rad-Studio IDE
  * Open up the location you cloned this repo to
  * Open the AGDX Studio.cproj file
* Press F9 to build and run the application

