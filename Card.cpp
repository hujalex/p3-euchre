#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"
#include <string>
#include <vector>
#include <sstream>
#include "unit_test_framework.hpp"



using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////




constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank corresponding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit corresponding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
//Function stubs



// istream & operator>>(istream &is, Suit &suit) {
//   string input;
//   is >> input;
//   suit = string_to_suit(input);
//   return is;
// }

Card::Card() 
  : rank(TWO), suit(SPADES){};

Card::Card(Rank rank_in, Suit suit_in) 
  : rank(rank_in), suit(suit_in) {}

Rank Card::get_rank() const {
  return rank;
}

Suit Card::get_suit() const {
  return suit;
}

Suit Card::get_suit(Suit trump) const {
  return suit; // ! Double Check this
}

bool Card::is_face_or_ace() const {
  Rank r = get_rank();
  if (r >= 9 && r <= 12) {
    return true;
  }
  return false;
}

bool Card::is_right_bower(Suit trump) const {
  if (get_rank() == 9 && get_suit() == trump) {
    return true;
  }
  return false;
}

bool Card::is_left_bower(Suit trump) const {
  if (get_rank() == 9) {
    if (trump == 0 && get_suit() == 2) {
      return true;
    }
    else if (trump == 1 && get_suit() == 3) {
      return true;
    }
    else if (trump == 2 && get_suit() == 0) {
      return true;
    }
    else if (trump == 3 && get_suit() == 1) {
      return true;
    }
  }
  return false;
}

bool Card::is_trump(Suit trump) const {
  return suit == trump;
}

ostream & operator<<(ostream &os, const Card &card) {
  vector<string> ranks = {
    "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  };

  vector<string> suits = {
    "Spades", "Hearts", "Clubs", "Diamonds"
  };

  Rank card_rank = card.get_rank();
  Suit card_suit = card.get_suit();
  os << ranks[card_rank] << " of " << suits[card_suit];
  return os;
}

istream & operator>>(istream & is, Card &card) {
  string str_rank;
  is >> str_rank;
  card.rank = string_to_rank(str_rank);

  string str_ignore;
  is >> str_ignore;

  string str_suit;
  is >> str_suit;
  card.suit = string_to_suit(str_suit);
  return is;
} 

bool operator<(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() < rhs.get_rank()) {
    return true;
  } 

  else if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() < rhs.get_suit()) {
      return true;
    }
  }

  return false;
}

bool operator<=(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() <= rhs.get_rank()) {
    return true;
  }
   else if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() <= rhs.get_suit()) {
      return true;
    }
  }
  return false;
}

bool operator>(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() > rhs.get_rank()) {
    return true;
  }

  else if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() > rhs.get_suit()) {
      return true;
    }
  }

  return false;
}

bool operator>=(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() >= rhs.get_rank()) {
    return true;
  }

  else if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() >= rhs.get_suit()) {
      return true;
    }
  }

  return false;
}

bool operator==(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() == rhs.get_suit()) {
      return true;
    }
  }
  return false;
}

bool operator!=(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() == rhs.get_suit()) {
      return false;
    }
  }
  return true;
}

Suit Suit_next(Suit suit) {

  if (suit == 0) {
    return CLUBS;
  }
  else if (suit == 1) {
    return DIAMONDS;
  }
  else if (suit == 2) {
    return SPADES;
  }
  else if (suit == 3) {
    return HEARTS;
  }
  else {
    assert(false);
  }

}

bool Card_less(const Card &a, const Card &b, Suit trump) {

  if (a.get_suit() == trump && b.get_suit() == trump) {
    return a < b;
  } else if (b.get_suit() == trump) {
    return true;
  } else if (a.get_suit() == trump) {
    return false;
  }
  return a < b;
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) {

  Suit led_suit = led_card.get_suit();

  if (a.get_suit() != led_suit && b.get_suit() != led_suit) {
    return Card_less(a, b, trump);
  } else if (a.get_suit() == led_suit && b.get_suit() == led_suit) {
    return Card_less(a, b, trump);
  } else if (b.get_suit() == led_suit) {
    return true;
  } else if (a.get_suit() == led_suit) {
    return false;
  }
  else {
    assert(false);
  }

}


// int main() {
//     Card two_spades = Card();

//     cout << two_spades.get_rank() << endl;
//     // ASSERT_EQUAL(two_spades.get_rank(), TWO);
//     // ASSERT_EQUAL(two_spades.get_suit(), SPADES);

//     // Card three_spades = Card(THREE, SPADES);
//     // ASSERT_EQUAL(three_spades.get_rank(), THREE);
//     // ASSERT_EQUAL(three_spades.get_suit(), SPADES);
//     // ASSERT_EQUAL(three_spades.get_suit(CLUBS), SPADES);

// }