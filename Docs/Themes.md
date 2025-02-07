# TODO!

## Theme config 
At the root folder of each theme there should be a json file called Theme.json
the file will contain the path and name of each asset in the theme, The file must be also conatin Theme_name and Theme_version

```json
{
    "Theme_name": "Default_Theme",
    "Theme_Version": 0.1,
    
    "Textures": [
        {
            "name": "Error_texture",
            "path": "Textures/Error.png"
        },
        {
            "name": "GamePI_Icon",
            "path": "Textures/GamePIicon.png"
        }
    ],

    "Sounds":[

    ],

    "Fonts":[
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