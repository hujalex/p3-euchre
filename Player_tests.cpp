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
TEST(test_add_discard)
{
    Player* bob = Player_factory("Bob", "Simple");
    Card upcard = Card(JACK,SPADES);
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));
    bob->add_and_discard(upcard);
    delete bob;

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

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

TEST(test_player_get_name2) {
  // Create a player and verify that get_name() returns the player's name
  Player * alice = Player_factory("Alice", "Simple");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;
}
//ACTUAL TEST CASES

TEST(Human_name) { 
    Player* player = Player_factory("Toby", "Human");
    ASSERT_NOT_EQUAL(player->get_name(), "Alex");
    ASSERT_EQUAL(player->get_name(), "Toby");
    delete player;
}
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
TEST(test_make_trump)
{
    Player* player = Player_factory("Bot", "Simple");
    player->add_card(Card(NINE, HEARTS));
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(ACE, SPADES));
    player->add_card(Card(KING, SPADES));
    player->add_card(Card(QUEEN, SPADES));
    Card upcard(JACK, HEARTS);
    Suit trump;
    bool order_suit = player->make_trump(upcard, false, 1, trump);
    ASSERT_NOT_EQUAL(HEARTS, trump);
    ASSERT_FALSE(order_suit);
    Card upcard2(JACK,SPADES);
    bool order_suit2 = player->make_trump(upcard2, true, 1, trump);
    ASSERT_EQUAL(trump, SPADES);
    ASSERT_TRUE(order_suit2);
    
    delete player;
}

TEST(test_make_trump_r2)
{
    Player* player = Player_factory("Bot", "Simple");
    player->add_card(Card(QUEEN, SPADES)); //first one to appear 
    player->add_card(Card(JACK, DIAMONDS));
    player->add_card(Card(NINE, HEARTS));
    player->add_card(Card(NINE,CLUBS));
    player->add_card(Card(TEN,SPADES));
    Card upcard(TEN, CLUBS);
    Suit trump;
    bool order_suit = player->make_trump(upcard, false, 2, trump);
    ASSERT_EQUAL(SPADES,trump);
    ASSERT_TRUE(order_suit);

    Card upcard2(KING, SPADES);
    bool order_suit2 = player->make_trump(upcard2, true, 2, trump);
    ASSERT_EQUAL(trump, CLUBS);
    ASSERT_TRUE(order_suit2);

    Card upcard3(NINE,SPADES);
    bool order_suit3 = player->make_trump(upcard3, false, 2, trump);
    ASSERT_FALSE(order_suit3);

    delete player;
}
TEST(test_make_trump_r1_2)
{
    Player* player = Player_factory("Bot", "Simple");
    player->add_card(Card(JACK, DIAMONDS)); //first
    player->add_card(Card(QUEEN, SPADES)); 
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(NINE,CLUBS));
    player->add_card(Card(TEN,SPADES));
    Card upcard(KING, HEARTS);
    Suit trump;
    bool order_suit = player->make_trump(upcard, true, 1, trump);
    ASSERT_EQUAL(trump, HEARTS);
    ASSERT_TRUE(order_suit);
    delete player;
}

TEST(test_lead)
{
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    Card c1(JACK,HEARTS);
    bob->add_and_discard(c1);

    Card card_led = bob->lead_card(HEARTS);
    ASSERT_EQUAL(c1, card_led);
    delete bob;
}
TEST(test_lead2)
{
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(ACE, SPADES));
    bob->add_card(Card(ACE, CLUBS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(ACE, DIAMONDS));
    bob->add_card(Card(KING, HEARTS));
    Card c1(JACK,CLUBS);
    bob->add_and_discard(c1);

    Card card_led = bob->lead_card(CLUBS);
    ASSERT_EQUAL(Card(ACE, DIAMONDS), card_led);
    delete bob;
}
TEST(test_lead3)
{
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(JACK, DIAMONDS));
    bob->add_card(Card(KING, HEARTS));
    Card c1(JACK,CLUBS);
    bob->add_and_discard(c1);

    Card card_led = bob->lead_card(CLUBS);
    ASSERT_EQUAL(Card(KING, HEARTS), card_led);
    delete bob;
}
TEST(test_lead4)
{
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    Card c1(NINE,HEARTS);
    bob->add_and_discard(c1);

    Card card_led = bob->lead_card(HEARTS);
    ASSERT_EQUAL(Card(JACK,HEARTS), card_led);
    delete bob;
}
TEST(test_lead5)
{
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(JACK, DIAMONDS));
    bob->add_and_discard(Card(TEN,HEARTS));

    Card c(JACK,HEARTS);
    Card card_led = bob->lead_card(HEARTS);
    ASSERT_EQUAL(c, card_led);
    delete bob;
}
TEST(test_lead6)
{
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(ACE, SPADES));
    bob->add_and_discard(Card(NINE, HEARTS));

    Card c(JACK,HEARTS);
    Card card_led = bob->lead_card(HEARTS);
    ASSERT_EQUAL(c, card_led);
    delete bob;
}
TEST(lead_card_7) {

 Player * bob = Player_factory("bob", "Simple");
   bob->add_card(Card(NINE, DIAMONDS));
   bob->add_card(Card(TEN, DIAMONDS));
   bob->add_card(Card(QUEEN, DIAMONDS));
   bob->add_card(Card(KING, DIAMONDS));
   bob->add_card(Card(ACE, DIAMONDS));

 bob->add_and_discard(
   Card(QUEEN, DIAMONDS) // upcard
 );

 Card card_lead = bob->lead_card(DIAMONDS);

 Card ace_diamonds(ACE, DIAMONDS);
 ASSERT_EQUAL(card_lead, ace_diamonds);
 delete bob;
}

TEST(test_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));
  // Bob plays a card
  Card c(JACK,SPADES);
  Card card_played = bob->play_card(
    c,  
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(ACE,SPADES));
  delete bob;
}
TEST(test_play_card2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card c(JACK,SPADES);
  Card card_played = bob->play_card(
    c,  
    SPADES   // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(ACE,SPADES));
  delete bob;
}
TEST(test_play_card3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card c(KING,DIAMONDS);
  Card card_played = bob->play_card(
    c,  
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(QUEEN,DIAMONDS));
  delete bob;
}
TEST(test_play_card4) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));
  // Bob plays a card
  Card upcard(JACK,SPADES);
  bob->add_and_discard(upcard);
  Card card_played = bob->play_card(
    upcard,
    SPADES    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, upcard);
  delete bob;
}
TEST(test_play_card5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, CLUBS));
  // Bob plays a card
  Card led_card = Card(NINE,SPADES);
  Card card_played = bob->play_card(
    led_card,
    SPADES    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, CLUBS));
  delete bob;
}
TEST(test_os)
{
    Player * bob = Player_factory("Bob", "Simple");
    ostringstream os;
    os << * bob;
    ASSERT_NOT_EQUAL(os.str(), "Simple");
    delete bob;
}

TEST_MAIN()
