# PROJECT DOCUMENT SYSTEM OVERVIEW

AGD Studio's editor system uses documents which can use specific or generic creation editors for the user to edit document content.

The documents are defined from a common `Document` base class, which itself inherits from the `JsonFile` class. By default, all documents are JSON, unless overidden (ie. The `TextDocument` class).
Documents usually (I need to fix this) don't include UI references.
Each type of AGD game element, such as the Images, the Map, the Event code, the Jump Table etc is defined as a document.
A document has a `"Type"` and `"Sub Type"`, which is used to describe the purpose of the document.
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

## USING AND EDITING DOCUMENTS
Although `Type/SubType` may seem similar to a documents Classification. The Classification is used to group different `Type/SubType` combinations.
From the `Type/SubType` specification of a document, we can then associate (register) a document creator for that document type.
This is done in the `DocumentManager` class, which itself is called from the `ProjectManager` singleton class.
Registration of a document is based on the `Type\SubType` pairing and can use either a derived class (Specialised document) or base class object reference (Generic document).
When the UI treeview opens a document, it needs to create the UI editor for it.
This is done via the IDE UI component (`fIde.cpp`) using the `DocumentEditorFactory`. This sets up the UI editors for each specialised and/or generic document types.

* All Image types (`ImageDocument`) use the same generic image editor, there are no specialisation of the image editor.
* Most text documents (`TextDocument`) use the generic text editor, with currently only the `Messages` document sub-type using a specialised editor.

The document base class can be used by the UI (Treeview) to show the properties of the inherited objects and implements the default Json load/save functions and UI property access functions.
Each version of a document can expose additional properties; the base class will handle registration with the UI for them.
The `TextDocument` class does not use the Json format and thus their save/load functions are overridden to return nothing.
It is therefore up to the Text Editor to save the contents of a `TextDocument`.
This is handled by the LMD Editor component, with the file name been retrieved from the `Document` base class.

## DOCUMENT CLASS HIERARCHY
```
(UI property editing)      (file content loaded/saved by the JsonFile class)                                      (UI Editor)
TPersisent              <- JsonFile     <- Settings                                                                UI Settings Dialog
                                        <- Machine Configuration                                                   None
                                        <- MRU List                                                                MRU File menu
                                        <- File Definitions                                                        None
                                        <- Document <- Project Document                                            IDE Tree View
                                                    <- Tiled Map Document                                          Map editor
                                                    <- Controls Document                                           Controls editor
                                                    <- Jump Table Document                                         Jump Table editor
                                                    <- Window Document                                             Window editor
                                                    <- Image <- Character Set Document                             Image Editor
                                                             <- Object Document                                    Image Editor
                                                             <- Sprite Document                                    Image Editor
                                                             <- Tile Document                                      Image Editor
                                                                (file content loaded/saved by the code editor)
                                                             <- Text Document  <- Event Document                   Text editor
                                                                               <- Sfx Document                     Text editor
                                                                               <- AGD Document                     Text editor
                                                                               <- Assembly Document                Text editor
                                                                               <- Messages Document                Messages editor
```

## PROJECT MANAGEMENT OF DOCUMENTS
The `ProjectManager` class is responsible for creating a new project, loading an existing project and saving a project.
It manages all documents associated with the project and it's supporting setting/configuration files.
It is also the link between the IDE UI and the documents, responsible for managing the UI tree view, MRU list. (project view)
TODO: I should move the registration of UI editors (fIDE) to here as well. As the IDE should be editor agnostic.

