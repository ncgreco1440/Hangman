#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <random>
#include <algorithm>

const int WORD_BANK_LENGTH = 26;
const std::string wordbank[WORD_BANK_LENGTH] =
{
    "apiary", "beetle", "cereal", "danger", "ensign", "florid", "garage", "health", "insult",
    "jackal", "keeper", "loaner", "manage", "nonce", "onset", "plaid", "quilt", "remote", "stolid",
    "train", "useful", "valid", "whence", "xenon", "yearn", "zippy"
};

/* ===================================================================================
    PROTOTYPE RANDOM GENERATOR CLASS

    Remember that random generators always return from a range that includes the
    minimum value but excludes the maximum value.
=================================================================================== */
template<class T>
class RandomGen
{
public:
// Constructor
    RandomGen(T min, T max): _min(min), _max(max) {};
// Change range
    void setRange(T min, T max)
    {
        _min = min;
        _max = max;
    };
// Return a random value
    T getRandom()
    {
        std::random_device random_device;
        std::mt19937 mt(random_device());
        std::uniform_int_distribution<T> dist(_min, _max);
        return dist(mt);
    };
private:
    T _min, _max;
};

/* ===================================================================================
    MAIN FUNCTION
=================================================================================== */
int main()
{
    using std::string;
    using std::cout;
    using std::cin;
    using std::endl;

    // Set up RandomGen
    RandomGen<int> rand(0, WORD_BANK_LENGTH);

    char play;
    cout << "Will you play a word game? <y/n>";
    cin >> play;
    play = tolower(play);

    // GAME LOOP
    while(play == 'y')
    {
        // INTRODUCTION
        string target = wordbank[rand.getRandom()];
        int length = target.length();
        string attempt(length, '-');
        string badguesses;
        int guesses = 6;

        cout << "Guess my secret word. It has " << length << " letters, and you guess\n"
            << "one letter at a time. You get " << guesses << " guesses.\n"
            << "Your word: " << attempt << endl;

        // GUESSING LOOP
        while(guesses > 0 && attempt != target)
        {
            // Guess a letter
            char letter;
            cout << "Guess a letter:_\b";
            cin >> letter;

            // Letter was already guessed
            if(badguesses.find(letter) != string::npos || attempt.find(letter) != string::npos)
            {
                cout << "You've already guessed that letter! Try Again!\n";
                continue;
            }

            // Letter was not guessed
            int loc = target.find(letter);
            if(loc == string::npos)
            {
                // You chose wisely!
                cout << "You chose...poorly.\n\n";
                --guesses;
                badguesses += letter;
            }
            else
            {
                // You chose wisely!
                cout << "You chose...wisely!\n\n";
                attempt[loc] = letter;
                loc = target.find(letter, loc + 1);
                while(loc != string::npos)
                {
                    attempt[loc] = letter;
                    loc = target.find(letter, loc + 1);
                }
            }

            cout << "Your word: " << attempt << endl;
            if(attempt != target)
            {
                if(badguesses.length() > 0)
                    cout << "Poor guesses: " << badguesses << endl;
                cout << guesses << " guesses remaining" << endl;
            }
        }

        // HAVE YOU WON OR LOST?
        if(guesses > 0)
            cout << "You've done it!\n";
        else
            cout << "Sorry, the word is " << target << ".\n";
        cout << "Will you play again? <y/n>";
        cin >> play;
        play = tolower(play);
    }
    cout << "Fare thee well!" << endl;

    return 0;
}