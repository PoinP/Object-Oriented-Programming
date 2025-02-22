#include <iostream>

const char* const SUITS[] = { "Hearts", "Spades", "Diamonds", "Clubs" };
enum class Suit
{
    Hearts,
    Spades,
    Diamonds,
    Clubs
};

const char* const RANKS[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
enum class Rank
{
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

int main()
{
    int userInput;

    std::cout << "Enter rank: [Ace - 1 ... King - 13]";
    std::cin >> userInput;
    Rank rank = (Rank)(userInput - 1);

    std::cout << "Enter suit: [0 - Hearts, 1 - Spades, 2 - Diamonds, 3 - Clubs]";
    std::cin >> input;
    suit = (Suit)userInput;

    if ((int)rank < 1 || (int)rank > 12 || (int)suit < 0 (int)suit > 3)
    {
        std::cout << "Error";
        return -1;
    }

    std::cout << RANKS[(int)rank] << " of " << SUITS[(int)suit];
}