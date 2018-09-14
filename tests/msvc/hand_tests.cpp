#include <SDKDDKVer.h>
#include "CppUnitTest.h"

#include "../../source/hand.h"

// Test namespaces
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ingg::poker;

namespace PokerHandAlgorithmTests
{		
	TEST_CLASS(Hand_Tests)
	{
	public:
		
		// Checks the rank order of our hands
		TEST_METHOD(HandOrder_Ordered)
		{
			Assert::IsTrue(Hand::Type::HighCard < Hand::Type::Pair);
			Assert::IsTrue(Hand::Type::Pair < Hand::Type::TwoPairs);
			Assert::IsTrue(Hand::Type::TwoPairs < Hand::Type::ThreeOfAKind);
			Assert::IsTrue(Hand::Type::ThreeOfAKind < Hand::Type::Straight);
			Assert::IsTrue(Hand::Type::Straight < Hand::Type::Flush);
			Assert::IsTrue(Hand::Type::Flush < Hand::Type::FullHouse);
			Assert::IsTrue(Hand::Type::FullHouse < Hand::Type::FourOfAKind);
			Assert::IsTrue(Hand::Type::FourOfAKind < Hand::Type::StraightFlush);
		}

		// Checks the hand is created correctly
		TEST_METHOD(HandCreated_CardsHeldInOrder)
		{
			// Create an unordered hand
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Four, Card::Suit::Clubs),
				Card(Card::Rank::Eight, Card::Suit::Clubs),
				Card(Card::Rank::Ten, Card::Suit::Clubs),
				Card(Card::Rank::Eight, Card::Suit::Diamonds),
				Card(Card::Rank::Ace, Card::Suit::Clubs),
			}});

			// Pull out the hand, it should be in order
			std::array<Card, Hand::Size> const& heldCards = newHand.GetCards();

			// Cards should be in a specific order
			Assert::IsTrue(heldCards[0].GetRank() == Card::Rank::Ace);
			Assert::IsTrue(heldCards[1].GetRank() == Card::Rank::Four);
			Assert::IsTrue(heldCards[2].GetRank() == Card::Rank::Eight);
			Assert::IsTrue(heldCards[3].GetRank() == Card::Rank::Eight);
			Assert::IsTrue(heldCards[4].GetRank() == Card::Rank::Ten);

			// Suits order equal ranks
			Assert::IsTrue(heldCards[2].GetSuit() == Card::Suit::Clubs);
			Assert::IsTrue(heldCards[3].GetSuit() == Card::Suit::Diamonds);
		}

		// Hand check - high card
		TEST_METHOD(HandHeld_HighCard)
		{
			// Create a hand without a win
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Two, Card::Suit::Clubs),
				Card(Card::Rank::Four, Card::Suit::Clubs),
				Card(Card::Rank::Six, Card::Suit::Clubs),
				Card(Card::Rank::Eight, Card::Suit::Clubs),
				Card(Card::Rank::Ten, Card::Suit::Diamonds),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::HighCard);
		}

		// Hand check - Flush
		TEST_METHOD(HandHeld_Flush)
		{
			// Create a hand with a flush
			Hand newHand(std::array < Card, Hand::Size > {{
					Card(Card::Rank::Two, Card::Suit::Clubs),
					Card(Card::Rank::Four, Card::Suit::Clubs),
					Card(Card::Rank::Six, Card::Suit::Clubs),
					Card(Card::Rank::Eight, Card::Suit::Clubs),
					Card(Card::Rank::Ten, Card::Suit::Clubs),
				}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::Flush);
		}

		// Hand check - Straight
		TEST_METHOD(HandHeld_Straight)
		{
			// Create a hand with a straight
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Two, Card::Suit::Clubs),
				Card(Card::Rank::Three, Card::Suit::Clubs),
				Card(Card::Rank::Four, Card::Suit::Clubs),
				Card(Card::Rank::Five, Card::Suit::Clubs),
				Card(Card::Rank::Six, Card::Suit::Diamonds),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::Straight);
		}

		// Hand check - Straight (Broadway)
		TEST_METHOD(HandHeld_StraightAcesHigh)
		{
			// Create a hand with a straight (aces low - a wheel)
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Ten, Card::Suit::Clubs),
				Card(Card::Rank::Jack, Card::Suit::Clubs),
				Card(Card::Rank::Queen, Card::Suit::Clubs),
				Card(Card::Rank::King, Card::Suit::Clubs),
				Card(Card::Rank::Ace, Card::Suit::Diamonds),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::Straight);
		}

		// Hand check - Straight flush
		TEST_METHOD(HandHeld_StraightFlush)
		{
			// Create a hand with a straight flush
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Two, Card::Suit::Clubs),
				Card(Card::Rank::Three, Card::Suit::Clubs),
				Card(Card::Rank::Four, Card::Suit::Clubs),
				Card(Card::Rank::Five, Card::Suit::Clubs),
				Card(Card::Rank::Six, Card::Suit::Clubs),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::StraightFlush);
		}

		// Hand check - Four of a kind
		TEST_METHOD(HandHeld_FourOfAKind)
		{
			// Create a hand with four of a kind
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Two, Card::Suit::Clubs),
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Six, Card::Suit::Clubs),
				Card(Card::Rank::Two, Card::Suit::Diamonds),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::FourOfAKind);
		}

		// Hand check - Full house
		TEST_METHOD(HandHeld_FullHouse)
		{
			// Create a hand with a full house
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Six, Card::Suit::Clubs),
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Six, Card::Suit::Clubs),
				Card(Card::Rank::Two, Card::Suit::Diamonds),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::FullHouse);
		}

		// Hand check - Three of a kind
		TEST_METHOD(HandHeld_ThreeOfAKind)
		{
			// Create a hand with three of a kind
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Six, Card::Suit::Clubs),
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Seven, Card::Suit::Clubs),
				Card(Card::Rank::Two, Card::Suit::Diamonds),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::ThreeOfAKind);
		}

		// Hand check - Two pairs
		TEST_METHOD(HandHeld_TwoPairs)
		{
			// Create a hand with two pairs
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Six, Card::Suit::Clubs),
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Seven, Card::Suit::Clubs),
				Card(Card::Rank::Six, Card::Suit::Diamonds),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::TwoPairs);
		}

		// Hand check - Two pairs
		TEST_METHOD(HandHeld_Pair)
		{
			// Create a hand with a pair
			Hand newHand(std::array < Card, Hand::Size > {{
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Six, Card::Suit::Clubs),
				Card(Card::Rank::Two, Card::Suit::Diamonds),
				Card(Card::Rank::Seven, Card::Suit::Clubs),
				Card(Card::Rank::King, Card::Suit::Diamonds),
			}});

			// A high hand
			Assert::IsTrue(newHand.GetType() == Hand::Type::Pair);
		}

	};
}