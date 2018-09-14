// Includes
#include "card.h"

// Top level namespace
namespace ingg
{
    namespace poker
    {
        //
        // Constructor
        //
        Card::Card(Card::Rank::Enum rank, Card::Suit::Enum suit)
            : m_suit(suit)
            , m_rank(rank)
        {
        }
        
		Card::Card() {
			m_suit = Card::Suit::Enum::Clubs;
			m_rank = Card::Rank::Enum::Ace;
		}

        //
        // Returns the suit of this card
        //
        Card::Suit::Enum Card::GetSuit() const
        {
            return m_suit;
        }
        
        //
        // Returns the rank of this card
        //
        Card::Rank::Enum Card::GetRank() const
        {
            return m_rank;
        }
    }
}