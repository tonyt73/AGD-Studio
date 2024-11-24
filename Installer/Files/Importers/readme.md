## AGD file importing
This section explains the matching language to parse each machines AGD file.

Each AGD file for different machines is slightly different.
Usually differing from the following properites:
- Window
  - different size due to graphics modes
- Controls
  - different number of fire and option keys
- JumpTable 
  - different size due to graphics modes
- Sprites/Objects/Blocks/Font 
  - different size due to graphics modes
- Screens
  - different widths due to graphics modes

The match language allows a user to configure AGD file parsing for different AGD formats for different machine platforms, without the need for AGD Studio to hard code each machine type.

### Match language
Used to capture sections of the AGD file format.

#### Basic format
**JSON**<br>
- `"Match"`: The pattern to match.

**Section Matching**<br>
Sections start with single word capture tag and then all value match elements separated by a single '**[space]**' character.
```
"{section name} <values>..."
```

**Value Matching**<br>
The match pattern after the initial section name, is a set of value matches defined within a set or angle brackets '**`< >`**'.
```
"{section name} <value match 1> <value match 2> ... <value match n>"
```

**Value Match Format**<br>
'**`<type>:<variable name>[<array dimensions>]`**'<br>
- **`<type>`**: is the type of variable to capture
  - **Is Required**
  - `number`: a simple integer value (0-65535) in decimal or hex ($)
  - `word__`: a string containing a single alphanumeric word.
  - `ascii_`: a single ascii character enclosed in single quotes. eg. `'A'`
  - `string`: text enclosed in double quotes `"some text"`
  - `line__`: the entire line of text
- **`<variable name>`**: is the variable name to hold the captured value in.
  - **Is Required**
  - Variables can be used in other sections.
  - Any variable used in a different section must have been parsed before its use. 
  - The AGD file must include the section before any variable used.
- **`[<array dimensions>]`**: is an optional array element.
  - *Is Optional*
  - Arrays can be 1 or 2 dimensions.
  - Arrays can use fixed numbering. ie. `[4,16]` or `[64]` These are the same size array
  - Arrays can use variable substitution. ie. `[window.width,window.height]`
     - The variable must of being assigned earlier within the file.
	 - ie. You can use the `window.width/height` variables if the `DEFINEWINDOW` section has not been parsed.
  - Arrays can reference a special count value for sections those names end in an `'s'`. Such as `Screens`.
	 - Format is `{Importer section name}`.
	   - works for 
	      - `"Objects": = {objects}`
		  - `"Sprites": = {sprites}`
		  - `"Blocks": = {blocks}`
		  - `"Events": = {events}`
		  - `"Screens": = {screens}`
     - Retrieves the count of sections captured with the name so far.
  - Arrays can use `-1` to indicate that size is unknown and all data of the array type is to be added to the array.
- **Matching is case-insensitive**

### Explanation of some patterns
 - `definemessages <string:message[-1]>`
	- `definemessages` captures the `DEFINEMESSAGES` word at the start of the line.
	- `<string:message[-1]>` reads all lines containing strings where a single quote (")is present) and adds them to the internal `message` variable.
    - Parsing is complete.
 - `map width <number:map.width> startscreen <number:map.startscreen> <number:map.data[map.width,-1]> endmap`
    - `map` captures the `MAP` word at the start of the line.
    - `width` captures the `WIDTH` word next.
    - `<number:map.width>` assigns a single number value to the internal variable `map.width`.
    - `startscreen` captures the `STARTSCREEN` word next.
    - `<number:map.startscreen>` assigns a single number value to the internal variable `map.startscreen`.
    - `<number:map.data[map.width,-1]>` assigns an array of numbers with the first dimension as the value in the variable `window.width`.
       - Captures all other number values in a group of `window.width`.
    - `endmap` captures the `ENDMAP` word last.
    - Parsing is complete.
- `spriteposition <number:screen{screens}.spriteposition.type[1]> <number:screen{screens}.spriteposition.index[1]> <number:screen{screens}.spriteposition.y[1]> <number:screen{screens}.spritepositions.x[1]>`
	- This one is special in that it uses a value from a previous section capture to assign names for internal variables, using the `{screen}` attribute.
	- `{screen}` references the count of `DEFINESCREENS` captured so far.
	  - `{screens}` actually references the import matcher name **"Screens":**
	- `spriteposition` captures the `SPRITEPOSITION` word at the start of the line.
	- `<number:screen{screens}.spriteposition.type[1]>` captures a single number value and adds it to an internal variable of type array.
	   - `{screens}` makes the variable name `screen1.spriteposition.type`
	   - `[1]` is used to trick the parser to think it is processing arrays, since they capture multiple values as a list of values and not a single value. 
	   - This is important because with the `[1]` the parser would only store a single value for `screen1.spriteposition.type` and so each new line of `SPRITEPOSITION` would overwrite the previous lines value.
	   - So each new line of `SPRITEPOSITION` will add each new value to each of the variable names defined as such as `screen1.spriteposition.type`.
	   - This is repeated for all the `SPRITEPOSITION` parameters, `index`, `y` and `x`.
   

## How do I define AGD importing for a new machine.
- Copy the `"ZX Spectrum 256x192 16 Colour"` json file in the `importers/` folder and rename it to your machine.
   - The machine name MUST match the one used in the `machines/` folder.
- Change `"Name"` to match your machine.
- Change any of the following if the different.
   - `JumpTable` 
      - Set table size to the number of elements required for your jump table.
   - `ControlSet` 
	  - Remove any keys not required. ie. The Amstrad CPC does not have a 3rd fire button (key.fire3)
   - `Objects` 
	 - Remove `<number:object.colour>` if your machine is not attribute based.
	 - Change `<number:object.imagedata[32]>` to the number of bytes that define an object bitmap.
   - `Sprites`
     - Change `<number:sprite.image[32,sprite.frames]>` to the number of bytes that define a sprite bitmap.
   - `Blocks`
	 - Change `<number:block.image[9]>` to the number of bytes that define a block bitmap.
   - `Font`
     - Change `<number:font.images[8,96]>` to the number of bytes that define a full character set.
	 - Most likely you'll only need to change the `8` to the width of your character bitmap.
   - `Palette`
     - Change `<number:palette.table[4,16]>` to size of your graphics palette.
	 - Delete this object entry if your machines agd engine does not allow for palette changes.
- There shouldn't be any need to change the following:
   - `Window`, `Events`, `MessageList`, `Screens`, `SpritePosition` or `Map`.