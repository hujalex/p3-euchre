#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"
#include <string>
#include <vector>
#include <sstream>
#include "Card.hpp"

using namespace std;

Pack::Pack() {
    int card_index = 0;
    for(int suit = SPADES; suit <= DIAMONDS; suit++)
    {
        for(int rank = NINE; rank <= ACE; rank++)
        {
            cards[card_index] = Card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            card_index++;
        }
    }
}
Pack::Pack(std::istream& pack_input) {
    string rank;
    string suit;
    string of;
    int index = 0;
    
    while (pack_input >> rank >> of >> suit) {
        cards[index] = Card(string_to_rank(rank), string_to_suit(suit));
        ++index;
    }
}
 Card Pack::deal_one()
 {
    assert(next < PACK_SIZE);
    return(cards[next]);
    next++;
 }
 void Pack::reset()
 {
    next = 0;
 }

void Pack::shuffle()
{
    std::array<Card, PACK_SIZE> temp;
    int half = PACK_SIZE/2;
    for(int i = 0; i < 7; i++)
    {
        int j = 0;
        for(int k = 0; k < half; k++)
        {
            temp[j] = cards[k+half];
            j++;
            temp[j] = cards[k];
            j++;
        }
    }
    cards = temp;
    reset();
}
bool Pack::empty() const
{
    assert(next >= PACK_SIZE);
}

 

