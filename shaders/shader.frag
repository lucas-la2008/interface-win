#version 330 core

flat in vec4 vertexColor;
flat in vec4 borderColor;
flat in float borderSize;
in vec2 localPos;
flat in vec2 elementSize;


out vec4 fragColor;

void main() {
    vec2 edgeDistance =
        min(localPos, vec2(1.0) - localPos) * elementSize;

    if (edgeDistance.x < borderSize ||
        edgeDistance.y < borderSize) {
        fragColor = vec4(borderColor.x/255.0,borderColor.y/255.0,borderColor.z/255.0,borderColor.w);
    } else {
        fragColor = vec4(vertexColor.x/255.0,vertexColor.y/255.0,vertexColor.z/255.0,vertexColor.w);
    }   
}
