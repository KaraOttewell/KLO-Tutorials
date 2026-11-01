// Kara Ottewell's STL Course
//
// Example 3.2                  © Kara Ottewell 1997-2026
//
// Purpose:
//          Demonstrate deque sequence container with a dumb card game
//          which is a bit like pontoon/blackjack/vingt-et-un
//          Note sneaky use of the shuffle() sequence modifying algorithm
//
// ---- A deque as a deck of cards, for a game of pontoon ("example_3_2.cpp") -

// C++ Standard Library Headers
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <random>

using namespace std;

class Card
{
  public:
    Card() : suit( 0 ), rank( 1 ) {}
    Card( int newSuit, int newRank ) : suit( newSuit ), rank( newRank ) {}
    friend ostream & operator<<( ostream &os, const Card &card );
    int Value() const { return( rank > 10 ? 10 : rank ); } // Picture cards count 10
  private:
    int suit, rank;
};

ostream & operator<<( ostream &os, const Card &card )
{
   static const char *suitNames[] = { "Hearts", "Clubs", "Diamonds", "Spades" };
   static const char *rankNames[] = { "Ace", "2", "3", "4", "5", "6", "7",
                                      "8", "9", "10", "Jack", "Queen", "King" };
   return( os << rankNames[card.rank-1] << " of " << suitNames[card.suit] );
}

class Deck
{
  public:
    Deck() : randomNumbers( random_device()() ) { NewPack(); }
    void NewPack() {
      cards.clear(); // Throw away what is left of the old pack first
      for ( int suit = 0; suit < 4; ++suit ) {
        for ( int rank = 1; rank <= 13; ++rank ) cards.push_back( Card( suit, rank ) );
      }
    }
//  Shuffle() uses the STL sequence modifying algorithm, shuffle()
    void Shuffle() { shuffle( cards.begin(), cards.end(), randomNumbers ); }
    bool Empty() const { return( cards.empty() ); }
    Card Twist() { Card next = cards.front(); cards.pop_front(); return( next ); }
  private:
    deque< Card > cards;
    mt19937 randomNumbers;    // Random number engine for shuffle()
};

// Read a one letter answer, in upper case
char GetResponse()
{
    char response = 'N';
    cin >> response;
    if ( !cin.good() ) {
      cin.clear(); // Catch Ctrl-Z, which leaves cin in an error state
      response = 'N';
    }
    return( (char)toupper( (unsigned char)response ) );
}

int main()
{
    Deck deck;
    Card card;
    int playerTotal, bankTotal;
    char response;
//  End of declarations ...

    while ( true ) {
      cout << "\n\n ---- New deck ----" << endl;
      playerTotal = bankTotal = 0;
      deck.Shuffle();
      response = 'T';

      while ( true ) {
        if ( playerTotal > 0 && playerTotal != 21 ) {
          cout << "Twist or Stick ? ";
          response = GetResponse();
        } else {
          if ( playerTotal == 21 ) response = 'S'; // Stick at 21
        }

        if ( response == 'Y' || response == 'T' ) {
          card = deck.Twist();
          playerTotal += card.Value();
          cout << card << " makes a total of " << playerTotal << endl;
          if ( playerTotal > 21 ) {
            cout << "Bust !" << endl;
            break;
          }
        } else {
          cout << "You stuck at " << playerTotal << "\n"
               << "Bank tries to beat you" << endl;

          while ( bankTotal < playerTotal && !deck.Empty() ) {
            card = deck.Twist();
            bankTotal += card.Value();
            cout << card << " makes bank's total " << bankTotal << endl;
          }
          if ( bankTotal > 21 ) {
            cout << "Bank has bust - You win !" << endl;
          } else if ( bankTotal >= playerTotal ) {
            cout << "Bank has won !" << endl;
          } else {
            cout << "Bank has run out of cards - You win !" << endl;
          }
          break;
        }
      }

      cout << "New game [Y/N] ? ";
      response = GetResponse();
      if ( response != 'Y' && response != 'T' ) break;
      deck.NewPack();
    }

    return( EXIT_SUCCESS );
}
