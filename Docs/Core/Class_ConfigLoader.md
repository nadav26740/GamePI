# ⚙️ ConfigLoader Class

The **ConfigLoader** class manages configuration loading and saving for GamePI, using a singleton pattern.

---

## 🔒 Protected Members

- `std::filesystem::path m_Theme_path`  
  *Path to the current theme.*

- `std::filesystem::path m_Default_assets_path`  
  *Path to default assets.*

- `std::string m_Emulator_Flags`  
  *Flags for emulator configuration.*

- `std::string m_Emulator_name`  
  *Name of the emulator.*

- `std::filesystem::path m_games_directory`  
  *Directory containing game files.*

- `std::string m_Games_Extension`  
  *File extension for game files.*

- `bool m_Config_Changed`  
  *Indicates if configuration has changed since last save.*

---

## 🚀 Public Member Functions

- **Singleton/Basic**
  - `ConfigLoader()`  
    *Constructor. Sets up config loader.*

  - `static ConfigLoader* GetIntance()`  
    *Returns the singleton instance.*

  - `void ResetToDefault()`  
    *Resets configuration to default values.*

- **Config I/O**
  - `bool LoadConfig(const std::filesystem::path& config_path = DEFAULT_CONFIG_LOADER_PATH, bool Set_missings_to_default = true)`  
    *Loads configuration from JSON file.*

  - `bool SaveConfig(const std::filesystem::path& config_path = DEFAULT_CONFIG_LOADER_PATH)`  
    *Saves configuration to JSON file.*

- **Getters**
  - `std::filesystem::path GetThemePath()`
  - `std::filesystem::path GetAssetsPath()`
  - `std::string GetEmulatorFlags()`
  - `std::string GetEmulatorName()`
  - `std::filesystem::path GetGamesDirectory()`
  - `std::string GetGamesExtension()`

- **Setters**
  - `void SetThemePath(std::filesystem::path value)`
  - `void SetAssetsPath(std::filesystem::path value)`
  - `void SetEmulatorFlags(std::string value)`
  - `void SetEmulatorName(std::string value)`
  - `void SetGamesDirectory(std::filesystem::path value)`
  - `void SetGamesExtension(std::string value)`

---

## 📝 Internal Utility

- `template<typename T> void JsonIntoField(nlohmann::json& js, T& field, std::string name)`  
  *Copies a field from JSON into the config field.*

---

## 💡 Usage Notes

- Always retrieve configuration via the ConfigLoader singleton.
- Update configuration files for new features or extension changes.

---