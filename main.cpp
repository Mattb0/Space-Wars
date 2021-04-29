#include "Game.h"

bool allowKBInput = true;
bool allowMouseInput = true;
int main()
{
    sf::Font font;
    if (!font.loadFromFile("resource/all.ttf"))
    {
        std::cout << "Failed to load font file" << "\n";
        system("pause");
    }
    std::cout << "Font file loaded" << "\n";

    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;

    game.Run();

    return 0;
}