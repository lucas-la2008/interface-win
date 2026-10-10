#ifndef BASE_OBJECT__
#define BASE_OBJECT__

#include "style/style.hpp"
#include "vectors.hpp"

class BaseObject{
protected:
    friend class Renderer;
    Vec::Vector2 size;
    Vec::Vector2 position;
    
public:
    BaseObject() = default;
    virtual ~BaseObject() = default;

    BaseObject& setPosition(float,float);

    BaseObject& setSize(float,float);

    Vec::Vector2 getPosition();
    
    Vec::Vector2 getSize();

    virtual Style getStyle() const = 0;
    
    virtual void clicked() = 0;
};

#endif