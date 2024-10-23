#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}
TEST(test_card)
{
    Card c(TWO, SPADES);
    ASSERT_EQUAL(Card(), c);
    Card c2(THREE, DIAMONDS);
    ASSERT_EQUAL(c2.get_rank(), THREE);
    ASSERT_EQUAL(c2.get_suit(), DIAMONDS);
}
TEST(test_card_trump)
{
    Card c3(JACK, CLUBS);
    
    Card c4(JACK, SPADES);
    ASSERT_EQUAL(c3.get_suit(SPADES), SPADES);
    ASSERT_EQUAL(c3.is_trump(CLUBS), true);
    ASSERT_EQUAL(c4.is_trump(CLUBS), true);
    ASSERT_EQUAL(c3.is_trump(SPADES), true);
    

}
TEST(test_ace_face)
{
    Card c(TEN, CLUBS);
    Card c2(JACK, DIAMONDS);
    Card c3(ACE, HEARTS);
    ASSERT_EQUAL(c.is_face_or_ace(), false);
    ASSERT_EQUAL(c2.is_face_or_ace(), true);
    ASSERT_EQUAL(c3.is_face_or_ace(), true);
}
TEST(test_right)
{
    Card c3(JACK, CLUBS);
    ASSERT_EQUAL(c3.is_right_bower(CLUBS), true);
}
TEST(test_left)
{
    Card c3(JACK, CLUBS);
    ASSERT_EQUAL(c3.is_left_bower(SPADES), true);
}
//Below is taken from public tests
TEST(test_card_insertion) {
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(test_card_extraction) {
    istringstream iss("Three of Spades");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(THREE, SPADES));
}

TEST(operator_greater_than) {
    Card less = Card(TWO, SPADES);
    Card More = Card(ACE, SPADES);
    ASSERT_EQUAL(More > less, true);

    less = Card(THREE, DIAMONDS);
    More = Card(FOUR, DIAMONDS);
    ASSERT_EQUAL(More > less, true);
}

TEST(operator_less_than) {
    Card less = Card(TWO, SPADES);
    Card More = Card(ACE, SPADES);
    ASSERT_EQUAL(less < More, true);

    less = Card(THREE, DIAMONDS);
    More = Card(FOUR, DIAMONDS);
    ASSERT_EQUAL(less > More, false);
}

TEST(operator_less_equal) {
    Card less = Card(TWO, SPADES);
    Card More = Card(ACE, HEARTS);
    ASSERT_EQUAL(less <= More, true);

    less = Card(THREE, DIAMONDS);
    More = Card(THREE, DIAMONDS);
    ASSERT_EQUAL(less <= More, true);
}


TEST(operator_greater_equal) {
    Card less = Card(TWO, SPADES);
    Card More = Card(ACE, HEARTS);
    ASSERT_EQUAL(less >= More, false);

    less = Card(THREE, DIAMONDS);
    More = Card(THREE, DIAMONDS);
    ASSERT_EQUAL(More >= less, true);
}


TEST(operator_equal) {
    Card less = Card(TWO, SPADES);
    Card More = Card(ACE, HEARTS);
    ASSERT_EQUAL(less == More, false);

    less = Card(THREE, DIAMONDS);
    More = Card(THREE, DIAMONDS);
    ASSERT_EQUAL(More == less, true);
}

TEST(operator_not_equal) {
    Card less = Card(FOUR, SPADES);
    Card More = Card(FOUR, SPADES);
    ASSERT_EQUAL(less != More, false);

    less = Card(TWO, DIAMONDS);
    More = Card(THREE, DIAMONDS);
    ASSERT_EQUAL(More != less, true);

}
TEST(next_suit) {
    Card c = Card(THREE, SPADES);
    ASSERT_EQUAL(Suit_next(CLUBS), c.get_suit());
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
}
TEST(Cardless) {
    Card c1 = Card(JACK, SPADES);
    Card c2 = Card(JACK, CLUBS);
    Card c3 = Card(ACE, SPADES);
    Card c4 = Card(ACE, DIAMONDS);
    Card c5 = Card(NINE, SPADES);
    ASSERT_TRUE(Card_less(c1, c2, CLUBS));
    ASSERT_TRUE(Card_less(c3, c1, CLUBS));
    ASSERT_TRUE(Card_less(c3, c4, CLUBS));
    ASSERT_TRUE(Card_less(c4, c5, SPADES));
}
TEST(Cardless2) {
    Card c1 = Card(JACK, SPADES);
    Card c2 = Card(JACK, CLUBS);
    Card c3 = Card(ACE, SPADES);
    Card c4 = Card(ACE, DIAMONDS);
    Card c5 = Card(NINE, SPADES);
    Card c6 = Card(TEN, HEARTS);
    ASSERT_TRUE(Card_less(c4, c3, Card(QUEEN, SPADES), CLUBS));
    ASSERT_TRUE(Card_less(c2, c1, Card(QUEEN, SPADES), SPADES));
    ASSERT_TRUE(Card_less(c4, c5, c3, HEARTS));
    ASSERT_TRUE(Card_less(c3, c6, c1, HEARTS));
}
TEST(test_card_suit_and_rank) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), TWO);
    ASSERT_EQUAL(two_spades.get_suit(), SPADES);

    Card three_spades = Card(THREE, SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), THREE);
    ASSERT_EQUAL(three_spades.get_suit(), SPADES);
    ASSERT_EQUAL(three_spades.get_suit(CLUBS), SPADES);
}


TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
}

TEST(test_card_type) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());
    ASSERT_FALSE(three_spades.is_right_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_trump(CLUBS));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           CLUBS));
}

// Add more test cases here

TEST_MAIN()
