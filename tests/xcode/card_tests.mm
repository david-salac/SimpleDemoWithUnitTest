// Includes
#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>

#import "../../source/card.h"

// Test namespaces
using namespace ingg::poker;

//
// Card test interface
//
@interface Card_Tests : XCTestCase

@end

//
// Card test implementation
//
@implementation Card_Tests

    // Checks the suits are ranked correctly based on standard poker rules
    - (void)test_SuitRank_OrderedCorrectly
    {
        XCTAssertLessThan(Card::Suit::Clubs, Card::Suit::Diamonds);
        XCTAssertLessThan(Card::Suit::Diamonds, Card::Suit::Hearts);
        XCTAssertLessThan(Card::Suit::Hearts, Card::Suit::Spades);
    }

    // Checks our ranks are in order
    - (void)test_ValueRank_OrderedCorrectly
    {
        XCTAssertLessThan(Card::Rank::Two, Card::Rank::Three);
        XCTAssertLessThan(Card::Rank::Three, Card::Rank::Four);
        XCTAssertLessThan(Card::Rank::Four, Card::Rank::Five);
        XCTAssertLessThan(Card::Rank::Five, Card::Rank::Six);
        XCTAssertLessThan(Card::Rank::Six, Card::Rank::Seven);
        XCTAssertLessThan(Card::Rank::Seven, Card::Rank::Eight);
        XCTAssertLessThan(Card::Rank::Eight, Card::Rank::Nine);
        XCTAssertLessThan(Card::Rank::Nine, Card::Rank::Ten);
        XCTAssertLessThan(Card::Rank::Ten, Card::Rank::Jack);
        XCTAssertLessThan(Card::Rank::Jack, Card::Rank::Queen);
        XCTAssertLessThan(Card::Rank::Queen, Card::Rank::King);
    }

    // Checks we play with aces low
    - (void)test_AceRank_OrderedLowest
    {
        XCTAssertLessThan(Card::Rank::Ace, Card::Rank::Two);
    }

    // Cards are default constructed
    - (void)test_CardConstructed_DefaultValue
    {
        Card newCard;
        
        // Default values
        XCTAssertEqual(newCard.GetRank(), Card::Rank::Ace);
        XCTAssertEqual(newCard.GetSuit(), Card::Suit::Clubs);
    }

    // Cards are constructed correctly
    - (void)test_CardConstructed_UserValue
    {
        Card newCard(Card::Rank::Ten, Card::Suit::Hearts);
        
        // Default values
        XCTAssertEqual(newCard.GetRank(), Card::Rank::Ten);
        XCTAssertEqual(newCard.GetSuit(), Card::Suit::Hearts);
    }

    // Equality is checked corrected
    - (void)test_CardEqualityCompared_OnlyRankUsed
    {
        Card cardTenOfHearts(Card::Rank::Ten, Card::Suit::Hearts);
        Card cardTenOfDiamonds(Card::Rank::Ten, Card::Suit::Diamonds);
        Card cardEightOfDiamonds(Card::Rank::Eight, Card::Suit::Diamonds);
        
        // Ranks are equal
        XCTAssertTrue(cardTenOfHearts == cardTenOfDiamonds);
        
        // Suits are not
        XCTAssertFalse(cardTenOfDiamonds == cardEightOfDiamonds);
    }

    // Comparision is checked corrected
    - (void)test_CardComparison_RankOverSuit
    {
        Card cardTenOfHearts(Card::Rank::Ten, Card::Suit::Hearts);
        Card cardTenOfDiamonds(Card::Rank::Ten, Card::Suit::Diamonds);
        Card cardEightOfSpades(Card::Rank::Eight, Card::Suit::Spades);
        
        // Ranks are compared
        XCTAssertTrue(cardEightOfSpades < cardTenOfHearts);
        
        // Suits are compared after
        XCTAssertTrue(cardTenOfDiamonds < cardTenOfHearts);
    }

@end
