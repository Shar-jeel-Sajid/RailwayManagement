#include "button.hpp"
#include "pages.hpp"

using namespace sf;

int main()
{
    
    RenderWindow window(VideoMode(800, 600), "Window");
    while(true)
        if(!Login_page(window))
            break;
}
