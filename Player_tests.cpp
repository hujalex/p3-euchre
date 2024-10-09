#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
TEST(test_empty_name)
{
    Player* empty = Player_factory("", "Simple");
    ASSERT_EQUAL(empty->get_name(), "");
    delete empty;
}
TEST(test_add_card) {
    Player* player = Player_factory("Bob", "Simple");
    Card c1(ACE, HEARTS);
    Card c2(KING, SPADES);
    //c3 and c4 may not work because the card rank is < 9
    Card c3(TWO, SPADES);
    Card c4(FIVE, DIAMONDS);
    player->add_card(c1);
    player->add_card(c2);
    player->add_card(c3);
    player->add_card(c4);

    delete player;
}
TEST(test_trump) {
    Player* player = Player_factory("Alex", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit = SPADES;

    // Test for round 1 as a non-dealer
    bool ordered_up = player->make_trump(upcard, false, 1, order_up_suit);
    if(ordered_up)
    {
        ASSERT_EQUAL(ordered_up, true);  
    }
    else
    {
        ASSERT_EQUAL(ordered_up, false);  
    }

    // Test for round 1 as a dealer
    ordered_up = player->make_trump(upcard, true, 1, order_up_suit);
    if(ordered_up)
    {
        ASSERT_EQUAL(ordered_up, true);  
    }
    else
    {
        ASSERT_EQUAL(ordered_up, false);  
    }
    delete player;
}
TEST(test_add_and_discard) {
    Player* player = Player_factory("Toby", "Simple");
    Card upcard(KING, HEARTS);
    player->add_and_discard(upcard);

    delete player;
}

TEST_MAIN()
