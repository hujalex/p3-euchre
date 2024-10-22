#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"
#include <fstream>
#include <string>

using namespace std;

class Game {
    public:

        Game();

        Game(Pack pack, string shuffle, int points, 
        string p1_name, string p1_type, 
        string p2_name, string p2_type, 
        string p3_name, string p3_type,
        string p4_name, string p4_type) : pack(pack), shuffling(shuffle), 
        winning_points(points), dealer_idx(0), team_even_points(0), team_odd_points(0) {

            players.push_back(Player_factory(p1_name, p1_type));
            players.push_back(Player_factory(p2_name, p2_type));
            players.push_back(Player_factory(p3_name, p3_type));
            players.push_back(Player_factory(p4_name, p4_type));

        };

        void play() {

            cout << "Play!" << endl;

            cout << winning_points << endl;

            //while < points

            int hand_num = 0;
            cout << team_even_points << endl;

            this->winning_points = 2; //!Only for testing
            cout << winning_points << endl;
            cout << team_odd_points << endl;


            while (team_even_points <= winning_points && team_odd_points <= winning_points) {

                cout << "Hand " << hand_num << endl;

                this->shuffle();

                this->deal();

                
            players[0]->print_hand();
            players[1]->print_hand();
            players[2]->print_hand();
            players[3]->print_hand();

            //? Deal() function is correct
                            

                this->make_trump();

                cout << endl;
                cout << trump_suit << endl;
                cout << ordered_up_idx << endl;

                
                this->play_hand();

                cout << endl;

                this->dealer_idx = (this->dealer_idx + 1) % 4;
                hand_num++;

            }


            for (size_t i = 0; i < players.size(); ++i) {
                delete players[i];
            }
        }

    private:


        Pack pack;
        vector<Player*> players;
        string shuffling;
        int winning_points;
        int dealer_idx;
        int team_even_points;
        int team_odd_points;
        Suit trump_suit;
        int ordered_up_idx;
        

        void shuffle() {
            if (shuffling == "shuffle") {
                pack.shuffle();
            } else if (shuffling == "noshuffle") {
                pack.reset();
            }
        };

        void deal() {
            
            cout << players[dealer_idx]->get_name() << " deals" << endl;


            for (size_t i = 0; i < 4; ++i) {

                int num_cards = 0;

                if (i % 2 == 0) {
                    num_cards = 3;
                } else {
                    num_cards = 2;
                }
                for (int j = 0; j < num_cards; ++j) {
                        int idx = (this->dealer_idx + i + 1) % 4; // first batch left of dealer
                        (*players[idx]).add_card(this->pack.deal_one());
                }
            }

            for (size_t i = 0; i < 4; ++i) {

                int num_cards = 0;

                if (i % 2 == 0) {
                    num_cards = 2;
                } else {
                    num_cards = 3;
                }
                for (int j = 0; j < num_cards; ++j) {
                        int idx = (this->dealer_idx + i + 1) % 4; //second batch left of dealer;
                        (*players[idx]).add_card(this->pack.deal_one());
                }
            
            }
        };


        void make_trump() {

            //round one
            Card upcard = this->pack.deal_one();

            cout << upcard << " turned up" << endl;

            // Suit upcard_suit = upcard.get_suit();
            Suit order_up_suit;
            

            bool round_one_trump = false;

            int i = 0;

            while (i < 4 && !round_one_trump) {

                int player_idx = (this->dealer_idx + i + 1) % 4;

                bool is_dealer = false;

                if (player_idx == this->dealer_idx) {
                    is_dealer = true;
                }

                
                if (players[player_idx]->make_trump(upcard, is_dealer, 1, order_up_suit)) {

                    round_one_trump = true;
                    this->trump_suit = order_up_suit;
                    this->ordered_up_idx = player_idx;
                    cout << players[ordered_up_idx]->get_name() << " orders up " << order_up_suit << endl;
                    cout << "Round One Make Trump" << endl;

                    if (is_dealer) {
                        players[dealer_idx]->add_and_discard(upcard);
                    }
                    
                } else {
                    cout << players[player_idx]->get_name() << " passes 1" << endl;
                }

                ++i;
            }
            
            bool round_two_trump = false;

            int j = 0;

            while (!round_one_trump && j < 4 && !round_two_trump) {

                int player_idx = (this->dealer_idx + j + 1) % 4;

                bool is_dealer = false;

                if (player_idx == this->dealer_idx) {
                    is_dealer = true;

                    cout << players[player_idx]->get_name() << endl;
                }

                if (players[player_idx]->make_trump(upcard, is_dealer, 2, order_up_suit)) {
                    round_two_trump = true;
                    this->trump_suit = order_up_suit;
                    this->ordered_up_idx = player_idx;
                    cout << players[ordered_up_idx]->get_name() << " orders up " << order_up_suit << endl;
                    cout << "Round Two Make Trump" << endl;

                } 
                else {
                    cout << players[player_idx]->get_name() << " passes" << endl;
                }
                ++j;

            }

        };

        
        void play_hand() {

            int leader_idx = (dealer_idx+1) % 4;
            int team_trick_evens = 0;
            int team_trick_odds = 0;

            for (int i = 0; i < 5; ++i) {

                Card ledCard = players[leader_idx]->lead_card(this->trump_suit);
                cout << ledCard << " led by "<< players[leader_idx]->get_name() << endl;
                Card max = ledCard;
                int max_idx = leader_idx;

                for (int j = 0; j < 3; ++j) {

                    int idx = (leader_idx + 1 + j) % 4;
                    // cout << "Lead Card" << ledCard << endl;
                    Card playedCard = players.at(idx)->play_card(ledCard, this->trump_suit);
                    cout << playedCard << " played by " << players[idx]->get_name() << endl;

                    if (Card_less(max, playedCard, ledCard, this->trump_suit)) {
                        // cout << ledCard << endl;
                        // cout << playedCard << endl;
                        // cout << playedCard.get_suit() << endl;
                        // cout << max.get_suit() << endl;

                        max = playedCard;
                        max_idx = idx;
                        
                    
                    }

                }
                // cout << "hello" << endl;
                // cout << max_idx << endl;
                cout << players[max_idx]->get_name() << " takes the trick" << endl;
                leader_idx = max_idx;

                if (max_idx % 2 == 0) {
                    cout << "++team_trick_evens;" << endl;
                    ++team_trick_evens;
                } else if (max_idx % 2 == 1) {
                    cout << "++team_trick_odds;" << endl;
                    ++team_trick_odds;
                }

                cout << endl;
                cout << i << endl;

            }


            string p0_name = players[0]->get_name();
            string p1_name = players[1]->get_name();
            string p2_name = players[2]->get_name();
            string p3_name = players[3]->get_name();

            cout << "ORDERED OUT " << players[ordered_up_idx]->get_name() << endl;
            cout << team_trick_evens << endl;
            cout << team_trick_odds << endl;
            if (ordered_up_idx % 2 == 0) {
                cout << "Evens Ordered" << endl;
                cout << p0_name << " and " << p2_name << " win the hand" << endl;
                if (team_trick_evens == 5) {
                    cout << "march!" << endl;
                    team_even_points += 2;
                } else if (team_trick_odds >= 3) {
                    cout << "euchred!" << endl;
                    team_odd_points += 2;
                } else if (team_trick_evens == 3 || team_trick_evens == 4) {
                    team_even_points++;
                }
            }
            else if (ordered_up_idx % 2 == 1) {
                cout << "Odds Ordered" << endl;
                if (team_trick_odds == 5) {
                    cout << "march!" << endl;
                    team_odd_points += 2;
                } else if (team_trick_evens >= 3) {
                    cout << "euchred!" << endl;
                    cout << "Hello" << endl;
                    team_even_points += 2;
                } else if (team_trick_odds == 3 || team_trick_odds == 4) {
                    team_odd_points++;
                }
            }
            cout << p0_name << " and " << p2_name << " have " << team_even_points << " points" << endl;
            cout << p1_name << " and " << p3_name << " have " << team_odd_points << " points" << endl;
            cout << endl;

        };

};

int main(int argc, char **argv) {

    ifstream fin;
    fin.open(argv[1]);

    if (!fin.is_open()) {
        cout << "Error opening " << argv[1] << endl;
    }

    Pack pack_from_ifstream(fin);

    // cout << shuffle << endl;

    string shuffling = argv[2];
    int points = stoi(argv[3]);
    string player_1_name = argv[4];
    string player_1_type = argv[5];
    string player_2_name = argv[6];
    string player_2_type = argv[7];
    string player_3_name = argv[8];
    string player_3_type = argv[9];
    string player_4_name = argv[10];
    string player_4_type = argv[11];
    
    Game game(pack_from_ifstream, shuffling, points, 
    player_1_name, player_1_type, 
    player_2_name, player_2_type, 
    player_3_name, player_3_type, 
    player_4_name, player_4_type);


    game.play(); 

}

/*./euchre.exe	Name of the executable
pack.in	Filename of the pack
noshuffle	Don’t shuffle the deck, or use shuffle to turn on shuffling
1	Points to win the game
Adi	Name of player 0
Simple	Type of player 0
Barbara	Name of player 1
Simple	Type of player 1
Chi-Chih	Name of player 2
Simple	Type of player 2
Dabbala	Name of player 3
Simple	Type of player 3*/