#ifndef FUNCTION_TOGGLE_KEY_H
#define FUNCTION_TOGGLE_KEY_H

#include <functional>
#include <SFML/Graphics.hpp>

class Function_Toggle_Key
{
    public:
        Function_Toggle_Key(std::function<void(void)> f, sf::Keyboard::Key k, sf::Time seconds);

        bool checkInput();

    private:
        std::function<void(void)>   m_func;
        sf::Keyboard::Key   m_key;
        sf::Time            m_toggleTime;
        sf::Clock           m_toggleClock;
};

#endif // FUNCTION_TOGGLE_KEY_H
