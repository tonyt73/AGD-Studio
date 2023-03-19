# PROJECT DOCUMENT SYSTEM OVERVIEW

AGD Studio's editor system uses documents which can use specific or generic creation editors for the user to edit document content.

The documents are defined from a common `Document` base class, which itself inherits from the `JsonFile` class. By default, all documents are JSON, unless overidden.
Documents usually (I need to fix this) don't include UI references.
Each type of AGD game element, such as the Images, the Map, the Event code, the Jump Table etc as defined as a document.
A document has a `"Type"` and `"Sub Type"`, which as to describe the purpose of the document.
There is also a `"Classification"` value which describes where in the project tree (visual tree view component) a document fits.

| Classification Path | Document Types | Type | Sub Type |
| --- | --- | --- |--- |
| Game\Configuration | Project  | Game | Configuration |
| Game\Configuration | Controls | Controls | List |
| Game\Configuration | Jump Table | Jump | Table |
| Game\Configuration | Window | Window | Definition |
| Game\Images | Character Set | Image | Character Set |
| Game\Images | Sprites | Image | Sprite |
| Game\Images | Objects | Image | Object |
| Game\Images | Tiles | Image | Tile |
| Game\Map | Tile Map / Game Screens | Map | Tiled |
| Game\Events | Game Events Code | Text | Event |
| Game\Files | Messages | Text | Messages |
| Game\Files | Sounds Fx List | Text | SoundFx |
| Game\Output | Various output files | Text | AGD/Asm |

Although `Type/SubType` may seem similar to a documents Classification. The Classification is used to group different `Type/SubType` combinations.
From the `Type/SubType` specification of a document, we can then associate (register) a document creator for that document type.
This done in the `DocumentManager` class, which itself is called from the `ProjectManager` singleton class.
Registration of a document is based on the `Type\SubType` pairing and can use either a derived class (Specialised document) or base class object reference (Generic document).
When the UI treeview opens a document, it needs to create the UI editor for it.
This is done via the IDE UI component (`fIde.cpp`) using the `DocumentEditorFactory`. This sets the UI editors for each specialised and/or generic document types.

* All Image types (`ImageDocument`) use the same generic image editor, there are no specialisation of the image editor.
* Most text documents (`TextDocument`) use the generic text editor, with currently only the `Messages` document sub-type using a specialised editor.

The document base class can be used by the UI (Treeview) to show the properties of the inherited objects and implements the default Json load/save functions and UI property access functions.
Each version of a document can expose additional properties that the base class handles registration with the UI for them.
The `TextDocument` class does not use the Json format and thus their save/load functions are overridden to return nothing.
It is therefore up to the Text Editor to save the contents of a `TextDocument`.
This is handled by the LMD Editor component, with the file name been retrieved from the `Document` base class.

## DOCUMENT CLASS HIERARCHY
```
                          (file content loaded/saved by the JsonFile class)
TPersisent <- JsonFile <- Settings
                       <- Machine Configuration
                       <- MRU List
                       <- File Definitions
                       <- Document <- Project
                                   <- Tiled Map
                                   <- Controls
                                   <- Jump Table
                                   <- Window
                                   <- Image <- Character Set
                                            <- Object
                                            <- Sprite
                                            <- Tile
                                   (file content loaded/saved by the code editor)
                                   <- Text  <- Event
                                            <- Message
                                            <- Sfx
                                            <- AGD
                                            <- Assembly
```

## EDITING A DOCUMENT
Each document type can have a specific editor associated with it.
If a base class has an editor associated with it, then all instances inheriting from the base class, use that editor.
For example the `ImageDocument` is associated with the Image Editor and thus all types of images use the same editor.
The Keyboard/Joystick (`ControlsDocument`) class has its own editor.
As does the `TextDocument` class, with an exception for Messages; which has its own Sub Type editor.

## PROJECT MANAGEMENT OF DOCUMENTS

