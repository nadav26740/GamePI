# 🎮 Assets Cache Manager

The **Assets Cache Manager** is a core memory management system for GamePI, designed to optimize resource usage by ensuring assets are loaded only once. This prevents duplicate loads and enhances both performance and memory efficiency.

---

## 🧠 Purpose

- **Prevent Redundant Loads:**  
  Ensures assets (textures, sounds, fonts, etc.) are not loaded multiple times, saving memory and reducing load times.

- **Centralized Access:**  
  Offers a unified interface for asset retrieval, making asset management consistent and straightforward.

---

## 🎵 Supported Asset Types

- 🎨 **Textures**
- 🔊 **Sounds**
- 📝 **Fonts**
- ⚙️ **Other resource types as defined by the repository**

---

## 🔉 SoundBuffer Supported Formats

GamePI supports the following formats for sound buffers:

| Format        | Notes         |
|:--------------|:-------------|
| **WAV**       | PCM only      |
| **OGG/Vorbis**|              |
| **FLAC**      |              |
| **MP3**       |              |

---

## 💡 Usage Example

When requesting an asset:
1. The cache manager checks if the asset is already loaded.
2. If loaded, it returns the cached instance.
3. If not, it loads the asset, stores it in cache, and returns the new instance.

---

## 📄 Manager Flowchart
![Alt text](./Assets_Cache_Manager_v1.drawio.svg)

---

## ✅ Best Practices

- Always request assets through the cache manager.
- Never load assets directly.
- Release unused assets to free up memory.

---

> 📝 **For theme and asset configuration details, see [Themes.md](../Themes.md).**