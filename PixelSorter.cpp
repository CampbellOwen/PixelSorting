#include "PixelSorter.h"
#include <cstdlib>
#include <ctime>
#include "utility.h"
#include <iostream>

PixelSorter::PixelSorter(const std::string& path, int sampleSize, unsigned int /*seed*/)
{
	std::random_device rd;  // for seed for the random number engine
    this->sampleSize = sampleSize;
    this->randEng = std::mt19937(rd());
    index = 0;
    img.loadFromFile(path); 
}

bool PixelSorter::Update(sf::Texture& texture)
{
    // static uint64_t iter = 0;
    const sf::Vector2u size = img.getSize();
    uint64_t maxIndex = (size.x * size.y) - 1;
        // std::cout << "Iter: " << iter++ << std::endl;
        uint64_t start = index;
        sf::Vector2u pos = Utility::indexToPosition(start, size);

        if (start >= maxIndex) {
            return false;
        }

        // img.setPixel(pos.x, pos.y, sf::Color::White);

        std::uniform_int_distribution<> distr(start+1, maxIndex);

        sf::Color currColour = img.getPixel(pos.x, pos.y);

        std::vector< std::pair<sf::Color, sf::Vector2u> > points;
        for (int i = 0; i < sampleSize; i++) {
            uint64_t index = distr(randEng);
            sf::Vector2u nextPos = Utility::indexToPosition(index, size);
            std::pair<sf::Color, sf::Vector2u> info(img.getPixel(nextPos.x, nextPos.y), nextPos);
            points.push_back(info);
        }

        std::sort(points.begin(), points.end(), [this, &pos](auto &left, auto &right) {
            size_t leftX = left.second.x;
            size_t leftY = left.second.y;

            size_t rightX = right.second.x;
            size_t rightY = right.second.y;

            std::vector<sf::Vector2i> comparisons = { {-1,-1}, {0,-1}, {1,-1}, 
                                                    {-1,0}, {0,0}, {1, 0},
                                                    {-1,1}, {0,1}, {1, 1}};

            double leftScore = 0;
            double rightScore = 0;
            int count = 0;

            for (auto comparison : comparisons) {
                size_t x = pos.x + comparison.x;
                size_t y = pos.y + comparison.y;
                if (x >= 0 && x < img.getSize().x && y >= 0 && y < img.getSize().y) {
                    leftScore += Utility::colourDist(img.getPixel(x, y), img.getPixel(leftX, leftY));
                    rightScore += Utility::colourDist(img.getPixel(x, y), img.getPixel(rightX, rightY));
                    count++;
                }
            }

            leftScore /= count;
            rightScore /= count;

            return leftScore < rightScore;
        });

        auto bestPos = points[0];

        //  std::cout << (int)bestPos.first.r << " " << (int)bestPos.first.g << " " << (int)bestPos.first.b << std::endl;

        img.setPixel(pos.x, pos.y, bestPos.first);
        img.setPixel(bestPos.second.x, bestPos.second.y, currColour);

    index++;
    texture.update(img);

    return true;
}