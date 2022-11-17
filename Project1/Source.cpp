#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
bool mousePressed = false;
bool wasMousePressed = false;


sf::Color red = { 255,0,0,255 };
void drawText(const char* text, float posX, float posY, float fontSize, sf::Color color, sf::Font font, sf::RenderWindow& window);
sf::Font font;

bool isMouseKeyDown(sf::Mouse::Button);
int main()
{
   
    sf::SoundBuffer buffer;
    sf::Sound example;
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    if (!font.loadFromFile("H:/Facultad/Image Tecnicatura Primer Año/10.Practica Profesional 1 - Desarrollo de Videojuegos 1/SFML/Project1/Tomatoes-O8L8.ttf"))
    {
    }
    if (buffer.loadFromFile("H:/Facultad/Image Tecnicatura Primer Año/10.Practica Profesional 1 - Desarrollo de Videojuegos 1/SFML/SFMLTEST/res/bullet1.wav"))
    {
        example.setBuffer(buffer);
    }
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        if  (isMouseKeyDown(sf::Mouse::Left))
        {
        drawText("Prueba", 10, 10, 40, red, font,window);
        if (example.getStatus() == sf::SoundSource::Stopped)
        {
            example.play();
            
        }
        }
        window.display();
    }

    return 0;
}
void drawText(const char* text, float posX, float posY, float fontSize, sf::Color color, sf::Font font, sf::RenderWindow& window)
{
	sf::Text drawableText = sf::Text(text, font, fontSize);
    drawableText.setPosition(posX, posY);
    window.draw(drawableText);
}
bool isMouseKeyDown(sf::Mouse::Button button)
{
   
    if (sf::Mouse::isButtonPressed(button))
    {
        return true;
    }
    else return false;
}
void  mouseStatus()
{
    wasMousePressed = mousePressed;
}
