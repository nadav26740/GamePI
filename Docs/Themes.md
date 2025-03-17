## Theme config 
At the root folder of each theme there should be a json file called Theme.json
the file will contain the path and name of each asset in the theme, The file must be also conatin Theme_name and Theme_version
> If two assets have the same path it will only load it once and both the names will point to the same loaded asset

```json
{
    "Metadata":
    {
        "Theme_name": "Default_Theme",
        "Theme_Version": 0.1
    },
    
    "Textures": 
    [
        {
            "name": "Error_texture",
            "path": "Textures/Error.png"
        },
        {
            "name": "GamePI_Icon",
            "path": "Textures/GamePIicon.png"
        }
    ],

    "Sounds":
    [
        {
            "name": "Beep",
            "path": "Sounds/Beep.mp3"
        }
    ],

    "Fonts":
    [
        {
            "name": "GameFont",
            "path": "Fonts/GameFont.ttf"
        },
        {
            "name": "Default_Font",
            "path": "Fonts/GameFont.ttf"
        }
    ]
}
 ```

## Default Assets
There are three default assets name defines that their purpose is that if the asset unable to be load it will load it instead

### The Default Defines name:
* **Texture - "Error_texture"**
* **Sound - "Error_Sound"**
* **Font - "Default_Font"**

## Struct of the config json file
The Struct of the json config file must contain 4 things: <br/>
* **Metadata** - Object that will contain the fields:
    * Theme_name \<string\>
    * Theme_Version \<Decimal Number\>

* **Textures** - Array that will contain an objects of texture path and name:
    * name \<string\>
    * path \<string\>

* **Sounds** - Array that will contain an objects of sound path and name:
    * name \<string\>
    * path \<string\>

* **Fonts** - Array that will contain an objects of fonts path and name:
    * name \<string\>
    * path \<string\>

> `The Paths must be related to the folder of the json config file` 
