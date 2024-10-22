#include "Player.hpp"
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
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

    const string & get_name() const override {
      return name;
    }

    void add_card(const Card&c) override {
      if (hand.size() < MAX_HAND_SIZE) {
        hand.push_back(c);
      }
    }

    bool make_trump(const Card & upcard, bool is_dealer,
          int round, Suit &order_up_suit) const override {
          
          assert(round == 1 || round == 2);
          Suit trump_suit = upcard.get_suit();
          Suit same_color_suit = Suit_next(trump_suit);

          if (round == 1) {

            int face_or_ace_of_trump = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                if ((hand[i].is_face_or_ace() && hand[i].get_suit() == trump_suit) || (hand[i].is_left_bower(trump_suit))) { //double check
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
              
              cout << "DEALER ORDERS UP" << endl;

              order_up_suit = same_color_suit;
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

    void add_and_discard(const Card & upcard) override {

      // cout << hand.size() << endl;
      // assert(hand.size() > 0);
      hand.push_back(upcard);
      hand.erase(hand.begin()); //! double check

    }

    Card lead_card(Suit trump) override {

      assert(hand.size() > 0);

      Card leadCard;

      int leadCardidx = 0;

      bool has_non_trump = false;

      for (size_t i = 0; i < hand.size(); ++i) {

        if (!hand[i].is_trump(trump)) {

          has_non_trump = true;

          if (Card_less(leadCard, hand[i], trump)) {
            leadCard = hand[i];
            leadCardidx = i;
          // cout << leadCard << endl;

          }
        }
      }

      if (!has_non_trump) {
        for (size_t i = 0; i < hand.size(); ++i) {

            if (Card_less(leadCard, hand[i], trump)) {
              leadCard = hand[i];
              leadCardidx = i;
            // cout << leadCard << endl;

            }
          
        }
      }

      hand.erase(hand.begin() + leadCardidx);

      return leadCard;
    }

    Card play_card(const Card &led_card, Suit trump) override {
      assert(hand.size() > 0);

      Suit lead_suit = led_card.get_suit();

      Card cardPlayed = hand[0];
      int cardPlayedIdx = 0;

      for (size_t i = 0; i < hand.size(); ++i) {
        if (Card_less(hand[i], cardPlayed, led_card, trump)) {
          cardPlayed = hand[i];
          cardPlayedIdx = i;
          cout << cardPlayed << endl;
        }
      }

      // cout << lead_suit << endl;

      // *
      // cout << endl;
      // print_hand();
      // cout << endl;

      for (size_t i = 0; i < hand.size(); ++i) {
        if (hand[i].get_suit() == lead_suit) {

          if (Card_less(cardPlayed, hand[i], led_card, trump)) {
            cardPlayed = hand[i];
            cardPlayedIdx = i;
          }
        }
      }

      hand.erase(hand.begin() + cardPlayedIdx);


      return cardPlayed;
      
    };

    void print_hand() const override{
      for (size_t i = 0; i < hand.size(); ++i) {
        cout << "Human Player" << name << "'s hand: "
        << "[" << i << "]" << hand[i] << "\n";
      }
    }


  private:
    string name;
    vector<Card> hand;

};


class HumanPlayer : public Player {

  public:
  
    HumanPlayer(string name)
    : name(name) {};

    const string & get_name() const override {
      return name;
    }

    void add_card(const Card&c) override {
      if (hand.size() < MAX_HAND_SIZE) {
        hand.push_back(c);
      }
    }

    bool make_trump(const Card & upcard, bool is_dealer,
          int round, Suit &order_up_suit) const override {
          
          assert(round == 1 || round == 2);

          print_hand();
          cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
          
          string decision;
          cin >> decision;

          if (round == 2 && is_dealer) {

              Suit ordered_up = string_to_suit(decision);
              assert(decision != "pass" && ordered_up != upcard.get_suit());
              order_up_suit = ordered_up;
              return true;
          }

          if (decision != "pass") {
              Suit ordered_up = string_to_suit(decision);
              order_up_suit = ordered_up;


              return true;
          } else {
              return false;
          }

    }

    void add_and_discard(const Card & upcard) override {

      sort(hand.begin(), hand.end());

      print_hand();
      cout << "Discard upcard: [-1]\n";
      cout << "Human player " << name << ", please select a card to discard:\n";

      //TODO 
      
      
    }

    Card lead_card(Suit trump) override {


      sort(hand.begin(), hand.end());

      print_hand();
      cout << "Human player " << name << ", please select a card:\n";
      string card_str;
      cin >> card_str;
      int card = stoi(card_str);

      return hand[card];

    };

    Card play_card(const Card &led_card, Suit trump) override {

      sort(hand.begin(), hand.end());

      print_hand();
      cout << "Human player " << name << ", please select a card:\n";

      string card_str;
      cin >> card_str;
      int card = stoi(card_str);

      return hand[card];


    };

    void print_hand() const {
      for (size_t i = 0; i < hand.size(); ++i) {
        cout << "Human Player" << name << "'s hand: "
        << "[" << i << "]" << hand[i] << "\n";
      }
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
    return new HumanPlayer(name);
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