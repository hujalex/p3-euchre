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
                if ((hand[i].is_face_or_ace() && hand[i].get_suit() == trump_suit)) { //double check
                  face_or_ace_of_trump++;
                }
                if(hand[i].is_left_bower(trump_suit))
                {
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
            

              order_up_suit = same_color_suit;
              return true;
            } else {
              for (size_t i = 0; i < hand.size(); ++i) {
                if (hand[i].is_face_or_ace() && hand[i].get_suit() == same_color_suit) {
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
      // cout << "Add and Discard" << endl;
      // cout << "Added card " << upcard << endl;

      Card lowest = upcard; // Changed upcard from hand[0];
      int lowest_idx = 0;

      for (size_t i = 0; i < hand.size(); ++i) {
        if (Card_less(hand[i], lowest, upcard.get_suit())) {
          lowest = hand[i];
          lowest_idx = i;
        }
      }
      hand.erase(hand.begin() + lowest_idx); //! double check needs to remove lowest card
      add_card(upcard);

    }

    Card lead_card(Suit trump) override {

      assert(hand.size() > 0);

      // print_hand();

      Card leadCard = hand[0]; //switched from default initialization

      // cout << "initalized lead" << leadCard << endl;

      int leadCardidx = 0;

      bool has_non_trump = false;

      for (size_t i = 0; i < hand.size(); ++i) {

        if (!hand[i].is_trump(trump)) {

          has_non_trump = true; 

          if (leadCard.is_trump(trump)) {
            // cout << "TRUE" << endl;
            leadCard = hand[i];
            leadCardidx = i;
          }
          else if (Card_less(leadCard, hand[i], trump)) {
            leadCard = hand[i];
            leadCardidx = i;
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
      if (led_card.is_left_bower(trump)) {
        lead_suit = Suit_next(led_card.get_suit());
      }

      Card cardPlayed = hand[0];
      int cardPlayedIdx = 0;

      for (size_t i = 0; i < hand.size(); ++i) {
        if (Card_less(hand[i], cardPlayed, led_card, trump)) {
          cardPlayed = hand[i];
          cardPlayedIdx = i;
        }


      }

      for (size_t i = 0; i < hand.size(); ++i) {


        if (hand[i].is_left_bower(trump) && lead_suit != Suit_next(hand[i].get_suit())) {
          continue;
        }

        if (hand[i].is_left_bower(trump) && lead_suit == Suit_next(hand[i].get_suit())) {
          if (cardPlayed.get_suit() != lead_suit) {
            cardPlayed = hand[i];
            cardPlayedIdx = i;
          }

          if (Card_less(cardPlayed, hand[i], led_card, trump)) {
            cardPlayed = hand[i];
            cardPlayedIdx = i; //does not consider trump;
          }
        }

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




  private:
    string name;
    vector<Card> hand;

    void print_hand() const {
      for (size_t i = 0; i < hand.size(); ++i) {
        cout << "Human player " << name << "'s hand: "
        << "[" << i << "] " << hand[i] << "\n";
      }
    }

};


class HumanPlayer : public Player {

  public:
  
    HumanPlayer(string name)
    : name(name) {};

    const string & get_name() const {
      return name;
    }

    void add_card(const Card&c) override {

      sort(hand.begin(), hand.end());

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

      // sort(hand.begin(), hand.end());

      print_hand();
      cout << "Discard upcard: [-1]\n";
      cout << "Human player " << name << ", please select a card to discard:\n";
      
      string response;
      cin >> response;

      int card_to_discard = stoi(response);

      if (card_to_discard != -1) {
          hand.erase(hand.begin() + card_to_discard);
          add_card(upcard);
      } 

      
    }

    Card lead_card(Suit trump) override {


      // sort(hand.begin(), hand.end());

      print_hand();
      cout << "Human player " << name << ", please select a card:\n";
      string card_str;
      cin >> card_str;
      int card_idx = stoi(card_str);

      Card leadCard = hand[card_idx];
      hand.erase(hand.begin() + card_idx);

      return leadCard;

    };

    Card play_card(const Card &led_card, Suit trump) override {

      // sort(hand.begin(), hand.end());

      print_hand();
      cout << "Human player " << name << ", please select a card:\n";

      string card_str;
      cin >> card_str;
      int card_idx = stoi(card_str);
      Card playedCard = hand[card_idx];

      hand.erase(hand.begin() + card_idx);

      return playedCard;

    };


  private:
    vector<Card> hand;
    string name;


    void print_hand() const {
      for (size_t i = 0; i < hand.size(); ++i) {
        cout << "Human player " << name << "'s hand: "
        << "[" << i << "] " << hand[i] << "\n";
      }
    }



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

