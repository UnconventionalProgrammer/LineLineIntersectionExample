//
// Created by Dan on 07/11/2020.
//

#include "SFUIBase.h"

SFUIBase::SFUIBase(const size_t width, const size_t height, const std::string &title) : mWindow(sf::VideoMode(width, height), title)
{}

bool SFUIBase::processEvents()
{
    sf::Event event{sf::Event::Closed};
    while (this->mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                this->mWindow.close();
                return false;
            case sf::Event::MouseMoved:
                this->mouseMoved(event.mouseMove);
                break;
            case sf::Event::MouseButtonReleased:
                this->mouseButtonReleased(event.mouseButton);
                break;
            case sf::Event::JoystickButtonPressed:
                this->joystickButtonPressed(event.joystickButton);
                break;
            case sf::Event::JoystickButtonReleased:
                this->joystickButtonReleased(event.joystickButton);
                break;
            case sf::Event::JoystickConnected:
                this->joystickConnected(event.joystickConnect);
                break;
            case sf::Event::Resized:
                this->resized(event.size);
                break;
            case sf::Event::LostFocus:
                this->lostFocus();
                break;
            case sf::Event::GainedFocus:
                this->gainedFocus();
                break;
            case sf::Event::TextEntered:
                this->textEntered(event.text);
                break;
            case sf::Event::KeyPressed:
                this->keyPressed(event.key);
                break;
            case sf::Event::KeyReleased:
                this->keyReleased(event.key);
                break;
            case sf::Event::MouseWheelMoved:
                this->mouseWheelMoved(event.mouseWheel);
                break;
            case sf::Event::MouseWheelScrolled:
                this->mouseWheelScrolled(event.mouseWheelScroll);
                break;
            case sf::Event::MouseButtonPressed:
                this->mouseButtonPressed(event.mouseButton);
                break;
            case sf::Event::MouseEntered:
                this->mouseEntered();
                break;
            case sf::Event::MouseLeft:
                this->mouseLeft();
                break;
            case sf::Event::JoystickMoved:
                this->joystickMoved(event.joystickMove);
                break;
            case sf::Event::JoystickDisconnected:
                this->joystickDisconnected(event.joystickConnect);
                break;
            case sf::Event::TouchBegan:
                this->touchBegan(event.touch);
                break;
            case sf::Event::TouchMoved:
                this->touchMoved(event.touch);
                break;
            case sf::Event::TouchEnded:
                this->touchEnded(event.touch);
                break;
            case sf::Event::SensorChanged:
                this->sensorChanged(event.sensor);
                break;
            default:
                break;
        }
    }

    this->draw(this->mWindow);
    this->mWindow.display();

    return true;
}


void SFUIBase::mouseMoved(const sf::Event::MouseMoveEvent &event) {}
void SFUIBase::mouseButtonReleased(const sf::Event::MouseButtonEvent &event) {}
void SFUIBase::joystickButtonPressed(const sf::Event::JoystickButtonEvent &event) {}
void SFUIBase::joystickButtonReleased(const sf::Event::JoystickButtonEvent &event) {}
void SFUIBase::joystickConnected(const sf::Event::JoystickConnectEvent &event) {}
void SFUIBase::resized(const sf::Event::SizeEvent &event) {}
void SFUIBase::lostFocus() {}
void SFUIBase::gainedFocus() {}
void SFUIBase::textEntered(const sf::Event::TextEvent &event) {}
void SFUIBase::keyPressed(const sf::Event::KeyEvent &event) {}
void SFUIBase::keyReleased(const sf::Event::KeyEvent &event) {}
void SFUIBase::mouseWheelMoved(const sf::Event::MouseWheelEvent &event) {}
void SFUIBase::mouseWheelScrolled(const sf::Event::MouseWheelScrollEvent &event) {}
void SFUIBase::mouseButtonPressed(const sf::Event::MouseButtonEvent &event) {}
void SFUIBase::mouseEntered() {}
void SFUIBase::mouseLeft() {}
void SFUIBase::joystickMoved(const sf::Event::JoystickMoveEvent &event) {}
void SFUIBase::joystickDisconnected(const sf::Event::JoystickConnectEvent &event) {}
void SFUIBase::touchBegan(const sf::Event::TouchEvent &event) {}
void SFUIBase::touchMoved(const sf::Event::TouchEvent &event) {}
void SFUIBase::touchEnded(const sf::Event::TouchEvent &event) {}
void SFUIBase::sensorChanged(const sf::Event::SensorEvent &event) {}
void SFUIBase::draw(sf::RenderTarget &window) {}
