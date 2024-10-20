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
        string p4_name, string p4_type) : pack(pack) {

            this->points = points;

            shuffling = shuffle;

            players.push_back(Player_factory(p1_name, p1_type));
            players.push_back(Player_factory(p2_name, p2_type));
            players.push_back(Player_factory(p3_name, p3_type));


        };

        void play() {

            cout << "Play!" << endl;

            cout << points << endl;


            for (size_t i = 0; i < players.size(); ++i) {
                delete players[i];
            }
        }

    private:

        vector<Player*> players;
        Pack pack;
        string shuffling;
        int points;

        void shuffle() {
            if (shuffling == "shuffle") {
                pack.shuffle();
            } else if (shuffling == "noshuffle") {
                pack.reset();
            }
        };

        void deal() {
            
            for (size_t i = 0; i < 4; ++i) {

                int num_cards = 0;

                if (i % 2 == 0) {
                    num_cards = 3;
                } else {
                    num_cards = 2;
                }
                for (size_t j = 0; j < num_cards; ++j) {
                        *players[i].add_card(pack.deal_one());
                }

            }

            for (size_t i = 0; i < 4; ++i) {

                int num_cards = 0;

                if (i % 2 == 0) {
                    num_cards = 2;
                } else {
                    num_cards = 3;
                }
                for (size_t j = 0; j < num_cards; ++j) {
                        *players[i].add_card(pack.deal_one());
                }

            }
        };


        void make_trump() {
            
        };
        void play_hand();

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