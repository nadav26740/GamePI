# 🖼️ Scene Class Interface

The **Scene** class is the backbone for rendering, event handling, and animation management in GamePI.

---

## 🔒 Protected Members

- **`std::vector<sf::Drawable*> m_drawables_objects`**  
  🎨 Contains all drawable objects for rendering.  
  *Add new objects with:*  
  `m_drawables_objects.push_back(Drawable_ptr);`

- **`std::vector<SFMLBoost::ObjectsGroup> Objects_groups`**  
  📦 Holds groups of renderable objects for batch operations.  
  *Add new groups with:*  
  `Objects_groups.push_back(Group_ptr);`

- **`sf::Color m_Background_Color`**  
  🌈 Sets the scene background color.  
  *Default:* `sf::Color(29, 180, 237)` <span style="color:rgb(29, 180, 237)">&#9724;</span>

- **`std::vector<std::function<bool()>> animations`**  
  🎬 Stores animation functions.  
  - `false`: Animation is running  
  - `true`: Animation finished (removed from vector)

---

## 🚀 Public Member Functions

- **`Scene()`**  
  *Constructor:* Initializes scene and allocates memory.

- **`~Scene()`**  
  *Destructor:* Cleans up resources.

- **`virtual void Start(std::shared_ptr<sf::RenderWindow> Scene_window)`**  
  Runs **once** when the scene loads.  
  *Parameter:* `Scene_window` — shared pointer to the main window.

- **`virtual void Frame_update(std::queue<sf::Event> events_queue) = 0;`**  
  Called every frame for logic and event handling.  
  *Parameter:* `events_queue` — queue of input events.

- **`virtual void Graphical_update();`**  
  Called every frame for graphical updates and animations.

- **`virtual void Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window);`**  
  Renders objects to the screen and clears the window each frame.

---

## 💡 Best Practices

- Implement all required virtual functions in derived scenes.
- Manage drawable and animation lifecycles to prevent memory leaks.
- Use background color and group management for consistent scenes.

---

> 📚 **Refer to source code for advanced usage and implementation details.**