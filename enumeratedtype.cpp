#include <iostream>

using namespace std;

enum Suit {
    SPADES = 0,
    HEARTS = 1,
    CLUBS = 2,
    DIAMONDS = 3,
};


ostream & operator<<(ostream &os, Suit suit) {
    if (suit == 0) {
        os << "Spades";
    } else if (suit == 1) {
        os << "Hearts";
    } else if (suit == 2) {
        os << "Clubs";
    } else if (suit == 3) {
        os << "Diamonds";
    }
    return os;
}

int main() {
    Suit trump = HEARTS;
    cout << trump << endl;

    


}