#include "app.hpp"
#include "elements/button.hpp"
#include <iostream>

void foo(){
    std::cout << "hello\n";
}

int main(){
    App main(200,200,"Hello World");
    
    Button button;
    button
        .setColor(213.f,190.f,212.f,1.f)
        .setBorderSize(2.f)
        .setBorderColor(113.f,90.f,112.f,1.f)
        .setPosition(60.0f,70.0f)
        .setSize(80.0f,50.0f);

    button.connect(foo);
    
    main.addButton(button);
    main.run();
}