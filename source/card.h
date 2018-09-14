// Top level namespace
namespace ingg
{
    namespace poker
    {
        //
        // Individual card properties
        //
        class Card
        {
        public:
            
            // Card suits
            struct Suit
            {
                // Suits in order
                enum Enum
                {
                    Clubs,
                    Diamonds,
                    Hearts,
                    Spades,
                };
            };
            
            // Card rank
            struct Rank
            {
                // Ranks with aces low
                enum Enum
                {
					Ace,
                    Two,
                    Three,
                    Four,
                    Five,
                    Six,
                    Seven,
                    Eight,
                    Nine,
                    Ten,
                    Jack,
                    Queen,
                    King,
					
                };
            };
            
            // Construction
                            Card(Rank::Enum rank, Suit::Enum suit);
							Card();
            
            // Card properties
            Suit::Enum      GetSuit() const;
            Rank::Enum      GetRank() const;
            
            // Comparision operators
            friend bool operator==(Card const& lhs, Card const& rhs)
            {
                // We only care about rank during equality
                return lhs.m_rank == rhs.m_rank;
            }
            
            friend bool operator<(const Card& lhs, const Card& rhs)
            {
                // If the ranks are equal, check the suit
                // Check the rank
				if (lhs.m_rank == rhs.m_rank) {
					return (lhs.m_suit < rhs.m_suit) ;
				}
				return (lhs.m_rank < rhs.m_rank);
            }
            
        private:
            Suit::Enum                  m_suit = Suit::Diamonds;   // Suit of this card
            Rank::Enum                  m_rank = Rank::Ace;     // Rank of this card
        };
    }
}