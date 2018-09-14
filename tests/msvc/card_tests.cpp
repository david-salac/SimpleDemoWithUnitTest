#include <SDKDDKVer.h>
#include "CppUnitTest.h"

#include "../../source/card.h"

// Test namespaces
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ingg::poker;

namespace PokerHandAlgorithmTests
{		
	TEST_CLASS(Card_Tests)
	{
	public:
		
		// Checks the suits are ranked correctly based on standard poker rules
		TEST_METHOD(SuitRank_OrderedCorrectly)
		{
			Assert::IsTrue(Card::Suit::Clubs < Card::Suit::Diamonds);
			Assert::IsTrue(Card::Suit::Diamonds < Card::Suit::Hearts);
			Assert::IsTrue(Card::Suit::Hearts < Card::Suit::Spades);
		}

		// Checks our ranks are in order
		TEST_METHOD(ValueRank_OrderedCorrectly)
		{
			Assert::IsTrue(Card::Rank::Two < Card::Rank::Three);
			Assert::IsTrue(Card::Rank::Three < Card::Rank::Four);
			Assert::IsTrue(Card::Rank::Four < Card::Rank::Five);
			Assert::IsTrue(Card::Rank::Five < Card::Rank::Six);
			Assert::IsTrue(Card::Rank::Six < Card::Rank::Seven);
			Assert::IsTrue(Card::Rank::Seven < Card::Rank::Eight);
			Assert::IsTrue(Card::Rank::Eight < Card::Rank::Nine);
			Assert::IsTrue(Card::Rank::Nine < Card::Rank::Ten);
			Assert::IsTrue(Card::Rank::Ten < Card::Rank::Jack);
			Assert::IsTrue(Card::Rank::Jack < Card::Rank::Queen);
			Assert::IsTrue(Card::Rank::Queen < Card::Rank::King);
		}

		// Checks we play with aces low
		TEST_METHOD(AceRank_OrderedLowest)
		{
			Assert::IsTrue(Card::Rank::Ace < Card::Rank::Two);
		}

		// Cards are default constructed
		TEST_METHOD(CardConstructed_DefaultValue)
		{
			Card newCard;

			// Default values
			Assert::IsTrue(newCard.GetRank() == Card::Rank::Ace);
			Assert::IsTrue(newCard.GetSuit() == Card::Suit::Clubs);
		}

		// Cards are constructed correctly
		TEST_METHOD(CardConstructed_UserValue)
		{
			Card newCard(Card::Rank::Ten, Card::Suit::Hearts);

			// Default values
			Assert::IsTrue(newCard.GetRank() == Card::Rank::Ten);
			Assert::IsTrue(newCard.GetSuit() == Card::Suit::Hearts);
		}

		// Equality is checked corrected
		TEST_METHOD(CardEqualityCompared_OnlyRankUsed)
		{
			Card cardTenOfHearts(Card::Rank::Ten, Card::Suit::Hearts);
			Card cardTenOfDiamonds(Card::Rank::Ten, Card::Suit::Diamonds);
			Card cardEightOfDiamonds(Card::Rank::Eight, Card::Suit::Diamonds);

			// Ranks are equal
			Assert::IsTrue(cardTenOfHearts == cardTenOfDiamonds);

			// Suits are not
			Assert::IsFalse(cardTenOfDiamonds == cardEightOfDiamonds);
		}

		// Comparision is checked corrected
		TEST_METHOD(CardComparison_RankOverSuit)
		{
			Card cardTenOfHearts(Card::Rank::Ten, Card::Suit::Hearts);
			Card cardTenOfDiamonds(Card::Rank::Ten, Card::Suit::Diamonds);
			Card cardEightOfSpades(Card::Rank::Eight, Card::Suit::Spades);

			// Ranks are compared
			Assert::IsTrue(cardEightOfSpades < cardTenOfHearts);

			// Suits are compared after
			Assert::IsTrue(cardTenOfDiamonds < cardTenOfHearts);
		}

	};
}