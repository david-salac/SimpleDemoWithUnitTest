// Includes
#include <array>
#include <map>

#include "card.h"

// Top level namespace
namespace ingg
{
    namespace poker
    {
        //
        // A players hand
        //
        class Hand
        {
        public:
            // Size of a hand
            static int const Size = 5;
            
            // The type of hand we have
            struct Type
            {
                // Type of hand in accending order
                enum Enum
                {
                    HighCard,           // Five cards which do not form any of the combinations below
                    Pair,               // A hand with two cards of equal rank and three cards which are different from these and from each other
                    TwoPairs,           // A hand with two pairs of different ranks
                    ThreeOfAKind,       // Three cards of the same rank plus two unequal cards
                    Straight,           // Five cards of mixed suits in sequence
                    Flush,              // Five cards of the same suit
                    FullHouse,          // Three cards of one rank and two cards of another rank
                    FourOfAKind,        // Four cards of the same rank and the fifth card can be anything
                    StraightFlush,      // Five cards of the same suit in sequence
                };
            };
            
            // Object creation
                                                    Hand(std::array<Card, Size> const& cards);
            
            // Hand properties
            inline std::array<Card, Size> const&    GetCards() const
            {
                return m_cards;
            }
            
            inline Type::Enum                       GetType() const
            {
                return m_type;
            }
            
        private:
            std::array<Card, Size>                  m_cards;    // Cards making up this hand
            Type::Enum                              m_type;     // Type of hand this card makes
            
            // Hand calculations
            Type::Enum                              Evaluate();
            
            // Copy protection
                                                    Hand(Hand const& hand);
            Hand&                                   operator=(Hand const& rhs);

			bool CheckThreeOfKind(bool & fullHouse) const;
			bool CheckStraight() const;
			bool CheckPairs(bool & twoPairs) const;
		};
    }
}