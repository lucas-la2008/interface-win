#ifndef BUTTON__
#define BUTTON__

#include "elements/baseObject.hpp"
#include "style/style.hpp"
#include <vector>

class Button : public BaseObject{
    void clicked() override;
    std::vector<void(*)()> callbacks;
    Style style;
public:
    Button();
    void connect(void (*func)());
    
    Button& setColor(float,float,float,float);

    Button& setBorderSize(float);

    Button& setBorderColor(float,float,float,float);

    Style getStyle() const override;
};

#endif