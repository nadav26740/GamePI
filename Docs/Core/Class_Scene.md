# 🖼️ Scene Class

The **Scene** class is the backbone for rendering, event handling, and animation management in GamePI.

---

## 🔒 Protected Members

- **`std::vector<sf::Drawable*> m_drawables_objects`**  
  *Contains all drawable objects for rendering. Add new objects with `m_drawables_objects.push_back(Drawable_ptr);`*

- **`std::vector<SFMLBoost::ObjectsGroup*> Objects_groups`**  
  *Contains groups of renderable objects for batch operations. Add new groups with `Objects_groups.push_back(Group_ptr);`*

- **`sf::Color m_Background_Color`**  
  *Defines the scene background color. Default: `sf::Color(29, 180, 237)` <span style="color:rgb(29, 180, 237)">&#9724;</span>*

- **`std::shared_ptr<sf::RenderWindow> m_Scene_window`**  
  *Reference to the main render window.*

- **`std::vector<std::function<bool()>> animations`**  
  *Stores animation functions. Each function returns `true` if finished (removed from vector), `false` if still running.*

---

## 🚀 Public Member Functions

- **`Scene()`**  
  *Constructor. Responsible for memory allocation and outputs creation log.*

- **`~Scene()`**  
  *Destructor. Outputs destruction log.*

- **`virtual void Start(std::shared_ptr<sf::RenderWindow> Scene_window)`**  
  *Runs once when the scene loads. Sets up the scene window and clears object groups.*

- **`virtual void Frame_update(std::queue<sf::Event> events_queue) = 0;`**  
  *Runs every frame, responsible for logic and input events. The queue contains input events.*

- **`virtual void Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window)`**  
  *Runs every frame for graphical updates and animations. Iterates and removes finished animations.*

- **`virtual void Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)`**  
  *Renders all objects and groups to the window, and clears the window with the background color.*

---

## 💡 Usage Example (from code)

```cpp
void Scene::Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    auto itr = this->animations.begin();
    while (itr != animations.end()) {
        if ((*itr)())
            animations.erase(itr);
        else
            itr++;
    }
}

void Scene::Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    Scene_window->clear(m_Background_Color);
    for (auto obj_itr : Objects_groups)
        obj_itr->DrawGroup(*Scene_window);
    for (auto drawable : m_drawables_objects)
        Scene_window->draw(*drawable);
}
```

---