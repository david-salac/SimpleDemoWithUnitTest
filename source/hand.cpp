// Includes
#include "hand.h"
#include <algorithm>

// Top level namespace
namespace ingg
{
    namespace poker
    {
        //
        // Constructs the hand
        //
        Hand::Hand(std::array<Card, Size> const& cards)
//            : m_cards{cards}
        {

			m_cards = cards;
			std::sort(m_cards.begin(), m_cards.end(),
				[](const Card & a, const Card & b) -> bool
			{
				return (int)a.GetRank() < (int)b.GetRank();
			});
            // Evaluate this hand
            m_type = Evaluate();
        }


		// Evaluate Three of Kinds, otherIndexX represents the index of others card in set
		bool Hand::CheckThreeOfKind(bool & fullHouse) const {
			fullHouse = false;

			//Check all possibilities:
			if (m_cards[0] == m_cards[1] && m_cards[1] == m_cards[2]) {
				if (m_cards[3] == m_cards[4]) {
					fullHouse = true;
				}
				return true;
			} 
			else if (m_cards[1] == m_cards[2] && m_cards[2] == m_cards[3]) {
				fullHouse = false;
				return true;
			}
			else if (m_cards[2] == m_cards[3] && m_cards[3] == m_cards[4]) {
				if (m_cards[0] == m_cards[1]) {
					fullHouse = true;
				}
				return true;
			}
			return false;
		}

		bool Hand::CheckPairs(bool & twoPairs) const {
			twoPairs = false;

			if (m_cards[0] == m_cards[1]) {
				if (m_cards[2] == m_cards[3]) {
					twoPairs = true;
				}
				else if (m_cards[3] == m_cards[4]) {
					twoPairs = true;
				}
				return true;
			}
			else if (m_cards[1] == m_cards[2]) {
				if (m_cards[3] == m_cards[4]) {
					twoPairs = true;
				}
				return true;
			}
			else if (m_cards[2] == m_cards[3]) {
				if (m_cards[0] == m_cards[1]) {
					twoPairs = true;
				}
				return true;
			}
			else if (m_cards[3] == m_cards[4]) {
				if (m_cards[0] == m_cards[1]) {
					twoPairs = true;
				}
				else if (m_cards[1] == m_cards[2]) {
					twoPairs = true;
				}
				return true;
			}
			return false;
		}

		bool Hand::CheckStraight() const {
			int arrayOfRank[] = { (m_cards[0].GetRank()), (m_cards[1].GetRank()), (m_cards[2].GetRank()), (m_cards[3].GetRank()), (m_cards[4].GetRank()) };
			//Solving Ace position:
			if (arrayOfRank[0] == 0) {
				arrayOfRank[0] += 13;
			}
			std::sort(arrayOfRank, arrayOfRank + 5);
			
			if (arrayOfRank[4] == (arrayOfRank[3] + 1) && arrayOfRank[3] == (arrayOfRank[2] + 1) && arrayOfRank[2] == (arrayOfRank[1] + 1) && arrayOfRank[1] == (arrayOfRank[0] + 1)  ) {
				return true;
			}
			return false;
		}
        
        //
        // Evaluates the current hand
        //
        Hand::Type::Enum Hand::Evaluate()
        {
			//Test four of kind:
			if (
				m_cards[0] == m_cards[1] && m_cards[1] == m_cards[2] && m_cards[2] == m_cards[3] ||
				m_cards[1] == m_cards[2] && m_cards[2] == m_cards[3] && m_cards[3] == m_cards[4]
				) {
				return Hand::Type::FourOfAKind;
			}

			//Test Full House:
			bool fullHouse = false;
			if (CheckThreeOfKind(fullHouse)) {
				if (fullHouse) {
					return Hand::Type::FullHouse;
				}
				else {
					return Hand::Type::ThreeOfAKind;
				}
			}

			//Test flush
			if (m_cards[0].GetSuit() == m_cards[1].GetSuit() && m_cards[1].GetSuit() == m_cards[2].GetSuit() && m_cards[2].GetSuit() == m_cards[3].GetSuit() && m_cards[3].GetSuit() == m_cards[4].GetSuit()) {
				if (CheckStraight()) {
					return Hand::Type::StraightFlush;
				}
				return Hand::Type::Flush;
			}
			if (CheckStraight()) {
				return Hand::Type::Straight;
			}

			//Test pairs:
			bool twoPairs = false;
			if (CheckPairs(twoPairs)) {
				if (twoPairs) {
					return Hand::Type::TwoPairs;
				}
				return Hand::Type::Pair;
			}

            // Return our hand
			return Hand::Type::HighCard;
        }
    }
}