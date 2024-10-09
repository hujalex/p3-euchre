#include "Player.hpp"
#include <vector>
#include <string>

using namespace std;

void Player::add_card(const Card&c) {
    if ()
}



std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

class SimplePlayer : public Player {
  public:
    SimplePlayer(string name)
      : (name(name)) {};

    string & get_name() const{
      return this->name;
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
            for (int i = 0; i < hand.size(); ++i) {
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
            } else if {
              for (int i = 0; i < hand.size(); ++i) {
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
      assert(hand.size() > 0);
      hand.erase(hand.begin()); //! double check
      hand.push_back(upcard);
    }

    Card lead_card(suit trump) {
      assert(hand.size() > 0);

    }

    Card play_card(const Card &led_card, Suit trump) {
      assert(hand.size() > 0);
    }
    


  private:
    string name;
    vector<Card> hand;

}




Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  ...
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}
