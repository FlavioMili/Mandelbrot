#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main(){
  sf::RenderWindow window(sf::VideoMode(800, 600), "Mandelbrot Visualiser");
  sf::Shader mandelbrotShader;

  if(!mandelbrotShader.loadFromFile("../shaders/mandelbrot.frag", sf::Shader::Fragment)) return -1;

  float zoom = 1.01f;
  sf::Vector2f offset(-1.0f, 0.0f);

  sf::RectangleShape screen(sf::Vector2f(800, 600));
    screen.setPosition(0, 0);

  while(window.isOpen()){
    int maxIter = (500 + 500 * log(zoom));
    sf::Event event;
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed) 
        window.close();
    if(event.type == sf::Event::KeyPressed) {
                float moveSpeed = 0.1f / zoom;
                
                switch(event.key.code) {
                    case sf::Keyboard::Left:  
                        offset.x -= moveSpeed; 
                        break;
                    case sf::Keyboard::Right: 
                        offset.x += moveSpeed; 
                        break;
                    case sf::Keyboard::Down:    
                        offset.y -= moveSpeed; 
                        break;
                    case sf::Keyboard::Up:  
                        offset.y += moveSpeed; 
                        break;
                    case sf::Keyboard::Z:     
                        zoom *= 2.1f; 
                        break;
                    case sf::Keyboard::X:     
                        zoom *= 0.9f; 
                        break;
                    case sf::Keyboard::R:     
                        zoom = 0.5f;
                        offset = sf::Vector2f(-0.5f, 0.0f);
                        break;
                    default:
                        break;
                }
            }    
      }
    mandelbrotShader.setUniform("zoom", zoom);
    mandelbrotShader.setUniform("offset", offset);
    mandelbrotShader.setUniform("maxIter", maxIter);

    window.clear();
    sf::RenderStates states;
    states.shader = (&mandelbrotShader);
    window.draw(screen, states);
    window.display();
  }

  return 0;
}
