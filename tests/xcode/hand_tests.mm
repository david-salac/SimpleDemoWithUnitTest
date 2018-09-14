// Includes
#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>

#import "../../source/hand.h"

// Test namespaces
using namespace ingg::poker;

//
// Card test interface
//
@interface Hand_Tests : XCTestCase

@end

//
// Card test implementation
//
@implementation Hand_Tests

    // Checks the rank order of our hands
    - (void)test_HandOrder_Ordered
    {
        XCTAssertLessThan(Hand::Type::HighCard, Hand::Type::Pair);
        XCTAssertLessThan(Hand::Type::Pair, Hand::Type::TwoPairs);
        XCTAssertLessThan(Hand::Type::TwoPairs, Hand::Type::ThreeOfAKind);
        XCTAssertLessThan(Hand::Type::ThreeOfAKind, Hand::Type::Straight);
        XCTAssertLessThan(Hand::Type::Straight, Hand::Type::Flush);
        XCTAssertLessThan(Hand::Type::Flush, Hand::Type::FullHouse);
        XCTAssertLessThan(Hand::Type::FullHouse, Hand::Type::FourOfAKind);
        XCTAssertLessThan(Hand::Type::FourOfAKind, Hand::Type::StraightFlush);
    }

    // Checks the hand is created correctly
    - (void)test_HandCreated_CardsHeldInOrder
    {
        // Create an unordered hand
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Four, Card::Suit::Clubs),
            Card(Card::Rank::Eight, Card::Suit::Clubs),
            Card(Card::Rank::Ten, Card::Suit::Clubs),
            Card(Card::Rank::Eight, Card::Suit::Diamonds),
            Card(Card::Rank::Ace, Card::Suit::Clubs),
        }});
        
        // Pull out the hand, it should be in order
        std::array<Card, Hand::Size> const& heldCards = newHand.GetCards();
        
        // Cards should be in a specific order
        XCTAssertEqual(heldCards[0].GetRank(), Card::Rank::Ace);
        XCTAssertEqual(heldCards[1].GetRank(), Card::Rank::Four);
        XCTAssertEqual(heldCards[2].GetRank(), Card::Rank::Eight);
        XCTAssertEqual(heldCards[3].GetRank(), Card::Rank::Eight);
        XCTAssertEqual(heldCards[4].GetRank(), Card::Rank::Ten);
        
        // Suits order equal ranks
        XCTAssertEqual(heldCards[2].GetSuit(), Card::Suit::Clubs);
        XCTAssertEqual(heldCards[3].GetSuit(), Card::Suit::Diamonds);
    }

    // Hand check - high card
    - (void)test_HandHeld_HighCard
    {
        // Create a hand without a win
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Clubs),
            Card(Card::Rank::Four, Card::Suit::Clubs),
            Card(Card::Rank::Six, Card::Suit::Clubs),
            Card(Card::Rank::Eight, Card::Suit::Clubs),
            Card(Card::Rank::Ten, Card::Suit::Diamonds),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::HighCard);
    }

    // Hand check - Flush
    - (void)test_HandHeld_Flush
    {
        // Create a hand with a flush
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Clubs),
            Card(Card::Rank::Four, Card::Suit::Clubs),
            Card(Card::Rank::Six, Card::Suit::Clubs),
            Card(Card::Rank::Eight, Card::Suit::Clubs),
            Card(Card::Rank::Ten, Card::Suit::Clubs),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::Flush);
    }

    // Hand check - Straight
    - (void)test_HandHeld_Straight
    {
        // Create a hand with a straight
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Clubs),
            Card(Card::Rank::Three, Card::Suit::Clubs),
            Card(Card::Rank::Four, Card::Suit::Clubs),
            Card(Card::Rank::Five, Card::Suit::Clubs),
            Card(Card::Rank::Six, Card::Suit::Diamonds),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::Straight);
    }

    // Hand check - Straight (Broadway)
    - (void)test_HandHeld_StraightAcesHigh
    {
        // Create a hand with a straight (aces low - a wheel)
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Ten, Card::Suit::Clubs),
            Card(Card::Rank::Jack, Card::Suit::Clubs),
            Card(Card::Rank::Queen, Card::Suit::Clubs),
            Card(Card::Rank::King, Card::Suit::Clubs),
            Card(Card::Rank::Ace, Card::Suit::Diamonds),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::Straight);
    }

    // Hand check - Straight flush
    - (void)test_HandHeld_StraightFlush
    {
        // Create a hand with a straight flush
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Clubs),
            Card(Card::Rank::Three, Card::Suit::Clubs),
            Card(Card::Rank::Four, Card::Suit::Clubs),
            Card(Card::Rank::Five, Card::Suit::Clubs),
            Card(Card::Rank::Six, Card::Suit::Clubs),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::StraightFlush);
    }

    // Hand check - Four of a kind
    - (void)test_HandHeld_FourOfAKind
    {
        // Create a hand with four of a kind
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Two, Card::Suit::Clubs),
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Six, Card::Suit::Clubs),
            Card(Card::Rank::Two, Card::Suit::Diamonds),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::FourOfAKind);
    }

    // Hand check - Full house
    - (void)test_HandHeld_FullHouse
    {
        // Create a hand with a full house
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Six, Card::Suit::Clubs),
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Six, Card::Suit::Clubs),
            Card(Card::Rank::Two, Card::Suit::Diamonds),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::FullHouse);
    }

    // Hand check - Three of a kind
    - (void)test_HandHeld_ThreeOfAKind
    {
        // Create a hand with three of a kind
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Six, Card::Suit::Clubs),
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Seven, Card::Suit::Clubs),
            Card(Card::Rank::Two, Card::Suit::Diamonds),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::ThreeOfAKind);
    }

    // Hand check - Two pairs
    - (void)test_HandHeld_TwoPairs
    {
        // Create a hand with two pairs
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Six, Card::Suit::Clubs),
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Seven, Card::Suit::Clubs),
            Card(Card::Rank::Six, Card::Suit::Diamonds),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::TwoPairs);
    }

    // Hand check - Two pairs
    - (void)test_HandHeld_Pair
    {
        // Create a hand with a pair
        Hand newHand(std::array<Card, Hand::Size> {{
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Six, Card::Suit::Clubs),
            Card(Card::Rank::Two, Card::Suit::Diamonds),
            Card(Card::Rank::Seven, Card::Suit::Clubs),
            Card(Card::Rank::King, Card::Suit::Diamonds),
        }});
        
        // A high hand
        XCTAssertEqual(newHand.GetType(), Hand::Type::Pair);
    }

@end
