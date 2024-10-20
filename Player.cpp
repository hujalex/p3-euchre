#include "Player.hpp"
#include <vector>
#include <string>
#include <cassert>
// #include "Card.cpp"
// #include "Pack.cpp"

using namespace std;



std::ostream & operator<<(std::ostream &os, const Player &p) {

  os << p.get_name();
  return os;
}

class SimplePlayer : public Player {
  public:
    SimplePlayer(string name)
      : name(name) {};

    const string & get_name() const{
      return name;
    }

    void add_card(const Card&c) {
      if (hand.size() < MAX_HAND_SIZE) {
        hand.push_back(c);
      }
    }

    bool make_trump(const Card & upcard, bool is_dealer,
          int round, Suit &order_up_suit) const {
          
          assert(round == 1 || round == 2);
          Suit trump_suit = upcard.get_suit();
          Suit same_color_suit = Suit_next(trump_suit);

          if (round == 1) {

            int face_or_ace_of_trump = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                if (hand[i].is_face_or_ace()) {
                  face_or_ace_of_trump++;
                }
            }
            if (face_or_ace_of_trump >= 2) {
              order_up_suit = trump_suit;
              return true;
            }
          }
          else if (round == 2) {

            if (is_dealer) {
              order_up_suit = trump_suit;
              return true;
            } else {
              for (size_t i = 0; i < hand.size(); ++i) {
                if (hand[i].get_suit() == same_color_suit) {
                  order_up_suit = same_color_suit ;
                  return true;
                }
              }
            }
          }
          return false;

    }

    void add_and_discard(const Card & upcard) {

      cout << hand.size() << endl;
      // assert(hand.size() > 0);
      hand.push_back(upcard);
      hand.erase(hand.begin()); //! double check

    }

    Card lead_card(Suit trump) {

      assert(hand.size() > 0);

      Card leadCard = hand[0];

      int leadCardidx = 0;

      for (size_t i = 0; i < hand.size(); ++i) {
        if (!hand[i].is_trump(trump)) {
          if (hand[i] > leadCard) {
            leadCard = hand[i];
            leadCardidx = i;
          }
        }
      }

      hand.erase(hand.begin() + leadCardidx);

      return leadCard;
    }

    Card play_card(const Card &led_card, Suit trump) {
      assert(hand.size() > 0);

      Suit lead_suit = led_card.get_suit();

      Card cardPlayed = hand[0];
      int cardPlayedIdx = 0;

      for (size_t i = 0; i < hand.size(); ++i) {
        if (Card_less(hand[i], cardPlayed, led_card, trump)) {
          cardPlayed = hand[i];
          cardPlayedIdx = i;
        }
      }

      for (size_t i = 0; i < hand.size(); ++i) {
        if (hand[i].get_suit() == lead_suit) {
          if (hand[i] > cardPlayed) {
            cardPlayed = hand[i];
            cardPlayedIdx = i;
          }
        }
      }

      hand.erase(hand.begin() + cardPlayedIdx);

      return cardPlayed;

      
    }
    
  private:
    string name;
    vector<Card> hand;

};


class Human : public Player {

  public:
  
    Human(string name)
    : name(name) {};

    const string & get_name() const{
      return name;
    }

    void add_card(const Card&c) {
      if (hand.size() < MAX_HAND_SIZE) {
        hand.push_back(c);
      }
    }

    bool make_trump(const Card & upcard, bool is_dealer,
          int round, Suit &order_up_suit) const {
          
          assert(round == 1 || round == 2);
          Suit trump_suit = upcard.get_suit();
          Suit same_color_suit = Suit_next(trump_suit);

          if (round == 1) {

            int face_or_ace_of_trump = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                if (hand[i].is_face_or_ace()) {
                  face_or_ace_of_trump++;
                }
            }
            if (face_or_ace_of_trump >= 2) {
              order_up_suit = trump_suit;
              return true;
            }
          }
          else if (round == 2) {

            if (is_dealer) {
              order_up_suit = trump_suit;
              return true;
            } else {
              for (size_t i = 0; i < hand.size(); ++i) {
                if (hand[i].get_suit() == same_color_suit) {
                  order_up_suit = same_color_suit ;
                  return true;
                }
              }
            }
          }
          return false;

    }

    void add_and_discard(const Card & upcard) {

      cout << hand.size() << endl;

      // assert(hand.size() > 0);
      hand.erase(hand.begin()); //! double check
      hand.push_back(upcard);
    }

    Card lead_card(Suit trump) {

      assert(hand.size() > 0);

      Card leadCard = hand[0];

      int leadCardidx = 0;

      for (size_t i = 0; i < hand.size(); ++i) {
        if (!hand[i].is_trump(trump)) {
          if (hand[i] > leadCard) {
            leadCard = hand[i];
            leadCardidx = i;
          }
        }
      }


      hand.erase(hand.begin() + leadCardidx);

      return leadCard;
    }

    Card play_card(const Card &led_card, Suit trump) {
      assert(hand.size() > 0);
      Suit lead_suit = led_card.get_suit();

      Card cardPlayed = hand[0];
      int cardPlayedIdx = 0;

      for (size_t i = 0; i < hand.size(); ++i) {
        if (Card_less(hand[i], cardPlayed, led_card, trump)) {
          cardPlayed = hand[i];
          cardPlayedIdx = i;
        }
      }

      for (size_t i = 0; i < hand.size(); ++i) {
        if (hand[i].get_suit() == lead_suit) {
          if (hand[i] > cardPlayed) {
            cardPlayed = hand[i];
            cardPlayedIdx = i;
          }
        }
      }
      hand.erase(hand.begin() + cardPlayedIdx);
      return cardPlayed;
    }

  private:
    vector<Card> hand;
    string name;
};



Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }

  else if (strategy == "Human") {
    return new Human(name);
  }
  // Repeat for each other type of Player
  //...
  // Invalid strategy if we get here
  return nullptr;
}

// int main() {
//   Player* player = Player_factory("Toby", "Simple");


//     Card upcard(KING, HEARTS);

    
//     player->add_and_discard(upcard);

//     delete player;
// }