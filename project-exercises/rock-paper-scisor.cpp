#include<iostream>
#include<ctime>

char getUserChoice();
void show_choice(char &choice);
char getComputerChoice();
void chooseWinner(char &player, char &computer);

int main(){
    char player;
    char computer;

    player = getUserChoice();
    computer = getComputerChoice();
    std::cout << "Your choice : ";
    show_choice(player); 
    std::cout << "Computer choice : ";
    show_choice(computer);
    chooseWinner(player, computer);
    return 0;
}

char getUserChoice()
{
    char player;
    std::cout << "Rock-Paper-Scissors"<< std::endl;
    do{
        std::cout << "Choose one from this three."<< std::endl;
        std::cout << "-----------*----------" << std::endl;
        std::cout << "r for Rock." << std::endl;
        std::cout << "p for Paper." << std::endl;
        std::cout << "s for scissors." << std::endl;
        std::cin >> player;
    } while (player != 'r' && player != 'p' && player != 's');
    
    return player;
}

void show_choice(char &choice){
    switch (choice){
        case 'r':
            std::cout << "Rock\n";
            break;
        case 'p':
            std::cout << "Paper\n";
            break;
        case 's':
            std::cout << "Scissors\n";
            break;
        default: 
            std::cout << "Try again.";
            break;

    }
}

char getComputerChoice(){
    srand(time(0));
    int num = rand() % 3 + 1;
    switch(num){
        case 1: return 'r';
        case 2: return 'p';
        case 3: return 's';
    }
    return 0;
}

void chooseWinner(char &player, char &computer){
    switch (player){
        case 'r':   if (computer == 'r'){
                        std::cout << "It's tie.\n";
                    }
                    else if (computer == 'p') {
                        std::cout << "You Loose.\n";
                    }
                    else {
                        std::cout << "You Win.\n";
                    }
                    break;
        case 'p':   if (computer == 'r'){
                        std::cout << "You Win.\n";
                    }
                    else if (computer == 'p') {
                        std::cout << "It's tie.\n";
                    }
                    else {
                        std::cout << "You Loose.\n";
                    }
                    break;
        case 's':   if (computer == 'r'){
                        std::cout << "You Loose.\n";
                    }
                    else if (computer == 'p') {
                        std::cout << "You Win.\n";
                    }
                    else {
                        std::cout << "It's tie.\n";
                    }
                    break;
    }
}