#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include "SFMLBoost.hpp"

// interface
class Scene
{
protected:
    /* data */
    std::vector<SFMLBoost::ObjectsGroup> Objects_groups;


public:
    Scene();

    /// @brief 
    virtual void Awake() = 0;

    /// @brief 
    virtual void Start() = 0;

    /// @brief Update phase in the native system loop
    virtual void Frame_update() = 0;

    virtual ~Scene() = 0;
};