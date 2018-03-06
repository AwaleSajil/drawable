#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;

class Process : public sf::Drawable
{
private:
    sf::Vector2f Position = sf::Vector2f(0,0); //initial
    sf::Vector2f Scale = sf::Vector2f(1,1);
    sf::Color text_outline_color = sf::Color::Black;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // You can draw other high-level objects
            target.draw(r, states);
            target.draw(text, states);
        }

public:

    sf::RectangleShape r;
    sf::Font font;
    sf::Text text;

    Process()
    {
       // void sf::Transformable::setOrigin	(	const Vector2f & 	origin	)

        //cout << "rect: " << r.getSize().x << " , " << r.getSize().y << endl;
        r.setSize(sf::Vector2f(150, 50)); //hve to update on  setstring
        r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
        r.setScale(Scale);
        //cout << "rect: " << r.getSize().x << " , " << r.getSize().y << endl;
        //r.setOrigin(r.getGlobalBounds().width/2, r.getGlobalBounds().height/2);
        cout << "rect: " << r.getGlobalBounds().width << " , " << r.getGlobalBounds().height << endl;
        r.setPosition(Position);               //mouse
        r.setOutlineThickness(4/(Scale.x+Scale.y));
        r.setOutlineColor(text_outline_color);    //depends on selection state
        r.setFillColor(sf::Color::White);



        if (!font.loadFromFile("Roboto-Regular.ttf"))
        {
            // error...
            std::cout << "Error loading font" << std::endl;
        }

        text.setFont(font); // font is a sf::Font

        text.setString("Hello world");      // have to be user selectable

        text.setCharacterSize(14*pow((Scale.x+Scale.y)/2, 0.7)); // in pixels, not points! // depends on scale
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+3*Scale.y);
        // set the color
        text.setFillColor(text_outline_color);
        text.setPosition(Position);
        // set the text style
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    }

    void setPosition(const sf::Vector2f &pos)
    {
         Position = pos;
         r.setPosition(Position);
         text.setPosition(Position);
    }
    void setScale(const sf::Vector2f &sc)
    {
        Scale = sc;
        r.setScale(Scale);
        r.setOutlineThickness(4/(Scale.x+Scale.y));
        text.setCharacterSize(14*pow((Scale.x+Scale.y)/2, 0.7));
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2+3*Scale.y);
    }
    void setColor(const sf::Color color)
    {
        text_outline_color = color;
        r.setOutlineColor(text_outline_color);
        text.setFillColor(text_outline_color);
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");



    Process shape;
    cout << "width: " << shape.text.getGlobalBounds().width << " height: " << shape.text.getGlobalBounds().height << endl;
    //shape.setColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(500,400));
    shape.setScale(sf::Vector2f(2,2));
    while (window.isOpen())
    {
        //window.clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(shape);
        window.display();
    }

    return 0;
}
