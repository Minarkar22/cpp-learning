#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <algorithm>

class Word
{
    private:
        std::vector<std::string> wordList;
        std::string secretWord;
        std::string hiddenWord;
    public:
        void loadFromFile();
        void chooseRandomWord();
        void setSecretWord();
        bool processGuess(char guess);
        bool solved() const;
        std::string gethiddenWord() { return hiddenWord; }
        std::string getsecretWord() { return secretWord; }

};

class Hangman
{
    private:
        int wrongcount;
        
    public:
        Hangman() : wrongcount(0) {};
        void addWrongCount() { wrongcount++; }
        int getWrongCount() const { return wrongcount; }
        void reset() { wrongcount = 0; }
        void draw();

};

class HangmanGame
{
    private:
        Word word;
        Hangman man;
        const int maxInt = 6;
    public:
        void play();
        bool playagain();
};


int main()
{
    // 1. Seed the random number generator once at the start
    // time(0) provides the number of seconds since Jan 1, 1970
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    HangmanGame game;
    do {
        game.play();
    } while (game.playagain());

    std::cout << "Thanks for playing! Goodbye!\n";
    return 0;
}


void Word::loadFromFile()
{
    std::ifstream randomWord("words.txt");
    if (! randomWord)
    {
        std::cout << "Can not open file!" << std::endl;
        std::exit(1);
    }
    wordList.clear();
    std::string line;
    while (getline(randomWord, line))
    {
        if (!line.empty())
        {
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            wordList.push_back(line);
        }
        
    }

    if (wordList.empty())
    {
        std::cout << "Error! words.txt is empty.\n";
        std::exit(1);
    }

    //for (std::string w:wordList) std::cout << w << ", "; FOR TESTING PURPOSE ONLY
}

void Word::chooseRandomWord()
{
     // Ensure the vector is not empty to avoid division by zero
    if (!wordList.empty()) {
        // 2. Generate a random index from 0 to size-1
        int randomIndex = std::rand() % wordList.size();

        // 3. Print the item at that index
        //std::cout << "Random Index: " << randomIndex << "\n";
        //std::cout << "Random Item:  " << wordList[randomIndex] << std::endl;
        //std::cout << "Word count: " << wordList.size() << std::endl;
        secretWord = wordList[randomIndex];
        //std::cout << word << std::endl;
    }
}

void Word::setSecretWord()
{
    hiddenWord =std::string(secretWord.length(), '*');
    //std::cout << secretWord << std::endl;
    //std::cout << hiddenWord << std::endl;
}

bool Word::processGuess(char guess){
    guess = std::tolower(guess);
    bool found = false;
    for(size_t i = 0; i < secretWord.length(); i++)
    {
        if (secretWord[i] == guess && hiddenWord[i] == '*'){
            hiddenWord[i] = guess;
            found = true;
        }
    }
    return found;
}

bool Word::solved() const {
    return hiddenWord == secretWord;
}

void Hangman::draw()
{
   

    switch (wrongcount)
    {
    case 0:
    {
        std::cout << "___________        "<< std::endl;
        std::cout << "|        }         "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        break;
    }
    case 1:
    {
        std::cout << "___________        "<< std::endl;
        std::cout << "|        }         "<< std::endl;
        std::cout << "|        O         "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        break;
    }
    case 2:
    {
        std::cout << "___________        "<< std::endl;
        std::cout << "|        }         "<< std::endl;
        std::cout << "|        O         "<< std::endl;
        std::cout << "|        |         "<< std::endl;
        std::cout << "|        |         "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        break;
    }
    case 3:
    {
        std::cout << "___________        "<< std::endl;
        std::cout << "|        }         "<< std::endl;
        std::cout << "|        O         "<< std::endl;
        std::cout << "|        |         "<< std::endl;
        std::cout << "|       /|         "<< std::endl;
        std::cout << "|      / |         "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        break;
    }
    case 4:
    {
        std::cout << "___________        "<< std::endl;
        std::cout << "|        }         "<< std::endl;
        std::cout << "|        O         "<< std::endl;
        std::cout << "|        |         "<< std::endl;
        std::cout << "|       /|\\       "<< std::endl;
        std::cout << "|      / | \\      "<< std::endl;
        std::cout << "|                  "<< std::endl;
        std::cout << "|                  "<< std::endl;
        break;
    }
    case 5:
    {
        std::cout << "___________        "<< std::endl;
        std::cout << "|        }         "<< std::endl;
        std::cout << "|        O         "<< std::endl;
        std::cout << "|        |         "<< std::endl;
        std::cout << "|       /|\\       "<< std::endl;
        std::cout << "|      / | \\      "<< std::endl;
        std::cout << "|       /          "<< std::endl;
        std::cout << "|      /           "<< std::endl;
        break;
    }
    case 6:
    {
        std::cout << "___________        "<< std::endl;
        std::cout << "|        }         "<< std::endl;
        std::cout << "|        O         "<< std::endl;
        std::cout << "|        |         "<< std::endl;
        std::cout << "|       /|\\       "<< std::endl;
        std::cout << "|      / | \\      "<< std::endl;
        std::cout << "|       / \\       "<< std::endl;
        std::cout << "|      /   \\      "<< std::endl;
        break;
    }
    default:
        std::cout << "If you are seeing these line, then there is an error.\n";
        break;
    }
    
}

void HangmanGame::play(){
    man.reset();

    word.loadFromFile();
    word.chooseRandomWord();
    word.setSecretWord();

    char guess;
    std::string usedLetters;

    while (man.getWrongCount() < maxInt && !word.solved())
    {
       
        system("clear");
        man.draw();

        std::cout << "Word : " << word.gethiddenWord() << std::endl;
        std::cout << "Wrong guess : "<< man.getWrongCount() << " / "<< maxInt << std:: endl;
        std::cout << "Used letters : " << (usedLetters.empty() ? "NONE" : usedLetters) << "\n";
        
        std::cout << "Enter a letter: ";
        std::cin >> guess;

        if (!isalpha(guess))
        {
            std::cout << "Enter a valid letter.\n";
            std::cin.ignore(10000, '\n');
            std::cin.get();
            continue;
        }

        guess = std::tolower(guess);

        //check if already guessed
        if (usedLetters.find(guess) != std::string::npos)
        {
            std::cout << "You already guessed - " << guess << std::endl;
            std::cin.get();
            continue;
        }

        usedLetters += guess;
        usedLetters += ' ';

        if(!word.processGuess(guess))
        {
            man.addWrongCount();
            std::cout << "Wrong, " << guess << " is not in the Word.\n";
        }
        else{
            std::cout << "Good. " << guess << " is in the Word.\n";
        }
            
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }

    system("clear");
    man.draw();
    if (word.solved())
    {
        std::cout << "===========================" << std::endl;
        std::cout << "Congradulation!You won.\n";
        std::cout << "The word was " << word.getsecretWord() << std::endl;
        std::cout << "===========================" << std::endl;
    }
    else
    {
        std::cout << "===========================" << std::endl;
        std::cout << "!You Lost.\n";
        std::cout << "The word was " << word.getsecretWord() << std::endl;
        std::cout << "===========================" << std::endl;
    }
        
}

bool HangmanGame::playagain(){
    char choice;
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(10000, '\n');
    return std::tolower(choice) == 'y';
}