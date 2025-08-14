# 🎮 GamePI

Game Boy Emulator for Raspberry Pi 4 🕹️🍓

---

## 🚀 Getting Started

How to install on your Raspberry Pi:

### 1️⃣ Clone the repository
```bash
git clone https://github.com/nadav26740/GamePI.git
```

### 2️⃣ For automatic installation 🤖
Run the installation shell:
```bash
cd ./GamePI
./install.sh
```

### 3️⃣ Manual Installation 🛠️

#### Install all the requirements 📦
See 👉 [Requirements](#requirements)

#### Compile the system using build.sh ⚒️
```bash
cd ./GamePI/src
./build.sh --release
```

#### Make required folders 📁
```bash
cd
mkdir .GAMEPI
cd .GAMEPI
mkdir EMULATOR_GAMES   # Here all the games will be saved 🎲
```

---

## 📋 Requirements

- SFML 2.6.2 🖼️
- C++17 💻

---

## 📝 License

This project is licensed under the [Apache License](./License) 📄

---

## 🖼️ Concept Image

![concept image](Docs/Concept_image.jpeg)

---

Have fun playing Game Boy games on your Raspberry Pi! 🌟
