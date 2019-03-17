<img src="Screenshots/Welcome.png" width="512">

# An IDE for Jonathan Cauldwell's Arcade Game Designer

<img src="Screenshots/IDE.png" height=400>

Editors for:
* Images 
  * Sprites
  * Objects
  * Tiles/Blocks)
* Events (Code)
  * Syntax highlighting editor
    * AGD syntax (done)
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
https://github.com/tonyt73/AGDX-Studio/releases

## Build Instructions

* Clone this repo on to your PC
* Download and Install the Embarcardero Rad-Studio C++ Community Edition
  * https://www.embarcadero.com/products/cbuilder/starter
  * Register if you need to (its free)
  * Install the 32 bit and 64 bit Windows compilers (OSX, iOS & Android are optional)
  * I personally use Rad Studio 10.3.1 (latest)
* Download the trial version of LMD Innovative components
  * http://files.lmd.de/downloads/lmd2019vcl/setupvcl19td26.zip
  * Unzip and run the Setup application
  * Click Next to all questions to Install all defaults
  
* Either:
  * Install the latest release
  * This will install all the configuration files and the example project
  
* Or:
  * Install the Application Configuration files
    * Open up the location you cloned this repo to
    * Move the ```Config``` folder to ```%AppData%```
      * Hint: Copy the above uri and paste into Windows Explorer
    * Rename the ```Config``` folder to ```AGDX Studio```
  * Install the test project files
    * Open up the location you cloned this repo to
    * Move the contents of the ```Public Documents``` folder to ```C:\Users\Public\Documents\```

* Launch the Rad-Studio IDE
  * Open up the location you cloned this repo to
  * Open the AGDX Studio.cproj file
* Press F9 to build and run the application

