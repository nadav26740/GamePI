# 🚀 SFMLBoost Library Classes

The **SFMLBoost** library provides utility classes and functions for enhancing SFML usage in GamePI, especially for positioning and grouping graphical objects.

---

## 📦 Key Classes & Functions

### SFMLBoost::Object_wrapper

- **Fields**
  - `const sf::Drawable* object_drawable`  
    *Pointer to drawable form of the object.*
  - `std::shared_ptr<sf::Transformable> object_ptr`  
    *Shared pointer to the transformable object.*
  - `sf::Vector2f position`  
    *Position, relative to group origin.*
  - `int z_position`  
    *Z position relative to group.*

- **Methods**
  - `Object_wrapper(std::shared_ptr<sf::Transformable> object_ptr, const sf::Drawable* Object_draw)`
  - `Object_wrapper()`
  - `static bool CompareByZAxis(const Object_wrapper &obj1, const Object_wrapper &obj2)`
  - `void Draw(sf::RenderWindow&)`

### SFMLBoost::ObjectsGroup

- **Fields**
  - `sf::Vector2f OriginPosition`  
    *Origin position of the group.*
  - `sf::Vector2f Position`  
    *Current position of the group.*
  - `std::vector<std::shared_ptr<SFMLBoost::Object_wrapper>> Objects_in_group`  
    *Objects contained in the group.*
  - `int last_draw_group_count`  
    *Last count of drawn objects.*

- **Methods**
  - `sf::Vector2f GetPosition()`  
    *Returns current position.*
  - `sf::Vector2f GetOrigin()`  
    *Returns group origin.*
  - `void SetPosition(sf::Vector2f)`  
    *Sets position.*
  - `void move(sf::Vector2f)`  
    *Moves group by a given vector.*
  - `void SetOrigin(sf::Vector2f)`  
    *Sets origin position.*
  - `void DrawGroup(sf::RenderWindow&)`  
    *Draws all objects in the group.*
  - `ObjectsGroup()`  
    *Constructor.*
  - `~ObjectsGroup()`  
    *Destructor.*

---

## 💡 SFMLBoost Utility Functions

- `void CenterASprite(sf::Sprite*, const sf::Window*)`  
  *Centers a sprite in the window.*

- `void CenterATransformable(sf::Transformable*, const sf::Window*, sf::FloatRect, sf::Vector2f)`  
  *Centers a transformable object.*

- `void SetTransformablePosition(sf::Transformable*, const sf::Window*, SFMLBoost::POSITION, sf::FloatRect, sf::Vector2f)`  
  *Sets object position based on window and desired position (TOP_LEFT, CENTER, etc).*

- `_SetTransformablePosition_*`  
  *Functions for positioning objects at specific window locations (TOPLEFT, TOPRIGHT, BOTTOMCENTER, etc).*

---

## 💡 Usage Example

```cpp
objects_group.SetPosition({100, 200});
objects_group.move({10, 0});
objects_group.DrawGroup(window);
```

---