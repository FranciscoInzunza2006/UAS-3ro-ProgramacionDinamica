
#include <iostream>

void drawRectangle(const int width, const int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
            {
                std::cout << "* ";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}

void drawSquare(const int width)
{
    drawRectangle(width, width);
}

int main()
{
    std::cout << "Cuadrado 5x5:\n";
    drawSquare(5);

    std::cout << "Cuadrado 8x5:\n";
    drawRectangle(8, 5);

    std::cout << "\nHaz tu propio cuadrado: \n";

    int width;
    std::cout << "Ancho: ";
    std::cin >> width;

    int height;
    std::cout << "Alto: ";
    std::cin >> height;
    drawRectangle(width, height);

    return 0;
}