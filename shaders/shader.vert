#version 330 core

uniform mat4 projection;

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aSize;
layout(location = 2) in vec2 aPosition;
layout(location = 3) in vec4 aColor;
layout(location = 4) in vec4 aBorderColor;
layout(location = 5) in float aBorderSize;

out vec4 vertexColor;
out vec4 borderColor;
out float borderSize;
out vec2 localPos;
out vec2 elementSize;

void main(){
    
  vec2 aFinal = aPos * aSize + aPosition;
  
  gl_Position = projection * vec4(aFinal,0.0,1.0); 
  vertexColor = aColor;

  borderColor = aBorderColor;
  borderSize = aBorderSize;
  localPos = aPos;
  elementSize = aSize;
}