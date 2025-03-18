# Scene Class Interface

## Protected Members

### std::vector\<<sf::Drawable*>\> m_drawables_objects

> Vector that responsible to contain all the target render drawable objects <br/>
> To add new object to render just use **m_drawables_objects.push_back(Drawable_ptr);**


### std::vector\<<SFMLBoost::ObjectsGroup>\> Objects_groups
> Vector that responsible to contain all the target render Objects groups <br/>
> To add new group to render just use **Objects_groups.push_back(Drawable_ptr);**


### <sf::Color> m_Background_Color
> Member of the type sf::Color that responsible to the background color
>> *Default: sf::Color(29, 180, 237) <span style="color:rgb(29, 180, 237)">&#9724;</span>*

### std::vector\<<std::function>\<bool()\>\> animations;
> vector that responsible to contain all the animations that will run <br/>
> **The function must return bool that represent if the animation hasn't finished**
>> **False** - Hasn't finished yet and will run again <br/>
>> **True** - animation has finished and will be deleted from verctor  


## Public Functions

### Scene(); 
> **Constructor** Responsible for the memory allocation

### ~Scene();
> **Destructor**

### virtual void Start(std::shared_ptr\<<sf::RenderWindow>\> Scene_window)
>  Runs **once** when scene loaded <br/>
> **Must be declared**
> * **Scene_window** - Shared_ptr(from lib <memory>) of the main window for graphic placments

### virtual void Frame_update(std::queue\<<sf::Event>\> events_queue) = 0;
> Runs every frame responsible for the logical part of the frame <br/>
> **Must be declared**
> * **events_queue** - queue contains the inputs between frames

### virtual void Graphical_update(std::shared_ptr\<<sf::RenderWindow>\> Scene_window);
> Runs every frame responsible for the graphical part of the frame <br/>
> *Also runs the animations*
> * **Scene_window** - Shared_ptr(from lib <memory>) of the main window for graphic placments

### virtual void Render_objects(std::shared_ptr\<<sf::RenderWindow>\> Scene_window);
>  Runs every frame responsible to render the object into the screen <br/>
> **Attention - Also clearing the window** <br/>
> * **Scene_window** - the main window for rendering