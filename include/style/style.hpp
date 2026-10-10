#ifndef STYLE_STRUCT__
#define STYLE_STRUCT__

#include "vectors.hpp"

struct Style{
    Vec::Vector4 color = {0,0,0,0};
    Vec::Vector4 borderColor = {0,0,0,0};
    float borderSize = 0;
    bool visible = true;
};

#endif