# 🎨 Theme Configuration

Themes in GamePI enable flexible customization of the launcher’s look & feel. Each theme is defined in a `Theme.json` configuration file at the root of its folder.

---

## 🗄️ Theme.json Structure

The `Theme.json` file must specify:
- 📦 Paths and names of all assets used in the theme.
- 🏷️ Theme metadata (name and version).

**Tip:**  
If multiple assets share the same path, the asset loads only once, with all names referencing the same instance.

---

### 🌈 Example: Theme.json

```json
{
    "Metadata": {
        "Theme_name": "Default_Theme",
        "Theme_Version": 0.1
    },
    "Textures": [
        { "name": "Error_texture", "path": "Textures/Error.png" },
        { "name": "GamePI_Icon", "path": "Textures/GamePIicon.png" }
    ],
    "Sounds": [
        { "name": "Beep", "path": "Sounds/Beep.mp3" }
    ],
    "Fonts": [
        { "name": "GameFont", "path": "Fonts/GameFont.ttf" },
        { "name": "Default_Font", "path": "Fonts/GameFont.ttf" }
    ]
}
```

---

## 🛡️ Default Assets

GamePI defines fallback assets, loaded when a requested asset fails:

- 🖼️ **Texture:** `"Error_texture"`
- 🔔 **Sound:** `"Error_Sound"`
- 🅰️ **Font:** `"Default_Font"`

---

## 🔖 Theme.json Required Structure

The configuration file **must** contain:

- **Metadata**  
  - `Theme_name` *(string)*  
  - `Theme_Version` *(decimal number)*

- **Textures**  
  Array of objects:  
  - `name` *(string)*
  - `path` *(string)*

- **Sounds**  
  Array of objects:  
  - `name` *(string)*
  - `path` *(string)*

- **Fonts**  
  Array of objects:  
  - `name` *(string)*
  - `path` *(string)*

> 📌 **Asset paths must be relative to the Theme.json file location.**

---

## 🌟 Best Practices

- Confirm all assets are included and referenced properly.
- Use unique names for clarity.
- Always provide fallback assets for a seamless experience.

---

> 📝 **See [AssetsCacheManager.md](Core/AssetsCacheManager.md) for asset caching details.**