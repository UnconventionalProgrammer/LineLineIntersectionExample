//
// Created by Dan on 07/11/2020.
//

#ifndef SFUIBASE_H
#define SFUIBASE_H

#include <string>
#include "SFML/Graphics.hpp"

class SFUIBase
{
protected:
    sf::RenderWindow mWindow;
public:
    SFUIBase(size_t width, size_t height, const std::string &title);

    bool processEvents();

private:
    virtual void mouseMoved(const sf::Event::MouseMoveEvent &event);
    virtual void mouseButtonReleased(const sf::Event::MouseButtonEvent &event);
    virtual void joystickButtonPressed(const sf::Event::JoystickButtonEvent &event);
    virtual void joystickButtonReleased(const sf::Event::JoystickButtonEvent &event);
    virtual void joystickConnected(const sf::Event::JoystickConnectEvent &event);
    virtual void resized(const sf::Event::SizeEvent &event);
    virtual void lostFocus();
    virtual void gainedFocus();
    virtual void textEntered(const sf::Event::TextEvent &event);
    virtual void keyPressed(const sf::Event::KeyEvent &event);
    virtual void keyReleased(const sf::Event::KeyEvent &event);
    virtual void mouseWheelMoved(const sf::Event::MouseWheelEvent &event);
    virtual void mouseWheelScrolled(const sf::Event::MouseWheelScrollEvent &event);
    virtual void mouseButtonPressed(const sf::Event::MouseButtonEvent &event);
    virtual void mouseEntered();
    virtual void mouseLeft();
    virtual void joystickMoved(const sf::Event::JoystickMoveEvent &event);
    virtual void joystickDisconnected(const sf::Event::JoystickConnectEvent &event);
    virtual void touchBegan(const sf::Event::TouchEvent &event);
    virtual void touchMoved(const sf::Event::TouchEvent &event);
    virtual void touchEnded(const sf::Event::TouchEvent &event);
    virtual void sensorChanged(const sf::Event::SensorEvent &event);
    virtual void draw(sf::RenderTarget &window);
};


#endif //SFUIBASE_H
