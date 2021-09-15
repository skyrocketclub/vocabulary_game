// Vocabulary_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <iomanip>


void display_menu();
void quit();
void play_game();
void add_word();
void view_words();
void about_game();
bool check_word(std::string spanish_word);
std::string capitalise(std::string);
bool verify(std::string, std::string);
bool default_verify(std::string, std::string);


int option{ 1 };

int main()
{
    std::cout << "\t\t\t*******************VOCABULARY GAME*******************" << std::endl;
    display_menu();

    return 0;
}

void display_menu() {

    if (option == 1) {
        int choice{};
        std::cout << "1 - PLAY GAME\n2 - ADD NEW WORDS\n3 - VIEW ALL WORDS\n4 - ABOUT GAME\n0 - QUIT\nOPTION: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                play_game();
                display_menu();
            }
            break;

            case 2:
            {
                add_word();
                display_menu();
            }
            break;
            case 3:
            {
                view_words();
                display_menu();
            }
            break;
            case 4:
            {
                about_game();
                display_menu();
            }
            break;
            
            case 0:
            {
                quit();
            }
            break;

            default:
            {
                std::cout << "Kindly enter a valid option" << std::endl;
                display_menu();
            }
        }
    }
}

void play_game() {
    std::string player_name{};
    int high_score{ 0 }, word_source{};

    system("CLS");
    std::cout << "WELCOME PLAYER\nEnter your nick_name:" << std::endl;
    std::getline(std::cin,player_name);
    player_name = capitalise(player_name);

    system("CLS");
    std::cout << "WELCOME " << player_name << " TO THE VOCABULARY GAME\n\nCHOOSE A WORD SOURCE\n";
    std::cout << "1 - DEFAULT WORD BANK\n2 - MY WORD BANK (must have minimum of 50 words)\nOPTION: ";
    std::cin >> word_source;

    switch (word_source)
    {
        case 1:
        {

        }
        break;

        case 2:
        {

        }
        break;
    }

}

bool verify(std::string spanish, std::string english) {

}

bool default_verify(std::string spanish, std::string english) {

}

void add_word() {
    system("CLS");
    bool status{ false };

    std::string spanish{}, english{};
    int number{};
    std::ofstream out_file("words.txt", std::ios::app);
    
    if (!out_file) {
        std::cerr << "Error Opening File" << std::endl;
    }
    else {
        std::cout << "How many words would you like to add?" << std::endl<<"Option: ";
        std::cin >> number;             
        std::cin.ignore(1, '\n');

        for (int i{ 0 }; i < number; i++) {
           
          
            std::cout <<std::endl<< "Spanish Word: ";
            std::getline(std::cin, spanish);
            spanish = capitalise(spanish);

            out_file.close();
            status = check_word(spanish);
            out_file.open("words.txt", std::ios::app);

            //meaning the word is not already available
            if (status == false) {
                std::cout << "English word: ";
                std::getline(std::cin, english);
                english = capitalise(english);

                out_file << spanish << "," << english << std::endl;
            }
            else {
                std::cout << spanish << " is already in your collection" << std::endl;
            }
             
        }
        std::cout << "Words Successfully added!" << std::endl;
        out_file.close();
    }
}

void view_words() {
    system("CLS");
    std::string spanish{}, english{}, line{}, temp{};
    std::vector<std::string>entry;
   

    std::ifstream in_file;
    in_file.open("words.txt");

    if (!in_file) {
        std::cerr << "There are no words in you record at the moment" << std::endl;
    }
    else {
        std::cout << std::setw(20)<<std::left<<"SPANISH" <<"ENGLISH"<< std::endl<<std::endl;
        while (std::getline(in_file, line)) {

            entry.push_back(line);
        }
        in_file.close();
    }

    for (size_t i{ 0 };i < entry.size();i++) {
        for (size_t j{ i + 1 };j < entry.size(); j++) {
            if (entry.at(i) > entry.at(j)) {
                temp = entry.at(i);
                entry.at(i) = entry.at(j);
                entry.at(j) = temp;
            }
        }
    }

    for (size_t k{ 0 };k < entry.size();k++) {
        std::stringstream s_stream(entry.at(k));
        std::string substr;
        std::vector<std::string> result;


        while (s_stream.good()) {
            std::getline(s_stream, substr, ',');
            result.push_back(substr);
        }
        spanish = result.at(0);
        english = result.at(1);
        std::cout << std::setw(20) << std::left << spanish << std::setw(20) << english << std::endl;
    }
}

void about_game() {
    std::cout<<"	Vocabulary Chase\nUse Default word Bank(The user can use the word bank in the.txt file that accompanies the application).\nUse Your Word Bank(will not work except you have 50 words available).\nGAME MODES AVAILABLE\nFirstly, the user can choose to use the default word bank, or rather use his own word bank(which must have up to 50 words before this operation can run)\nEach correct try is 10 points.\nEach wrong try is - 10 points\nEach time, the user chooses how many words he wants to attempt today.\nThe High score is usually stored but in terms of percentage accuracy.It is usually displayed on attempt of a new game\nWords that are missed are movedand stored in a.txt file…\nSo, after the user has finished the session, there can be an option for him to retry the ones that he missed…\nHe can keep on playing the ones he misses after this till he decides to quit.\nWhen he gets the words, they leave the pool of the ‘missed words’.\nThen if the user beats the high score, there is now a new high score…\nIt is officially Game Over…(I think this should happen when he misses 50 % of his planned attempts)"<<std::endl<<std::endl;
}

bool check_word(std::string spanish_word) {
    std::string spanish{}, english{}, line{};
    bool status{false};
    
    std::ifstream in_file;
    in_file.open("words.txt");

    if (!in_file) {
        std::cerr << "Error opening file" << std::endl;
    }
    else {
      /*  in_file.seekg(0, std::ios::beg);*/
        while (std::getline(in_file, line)) {
            std::stringstream s_stream(line);
            std::string substr;
            std::vector<std::string> result;

            while (s_stream.good()) {
                std::getline(s_stream, substr, ',');
                result.push_back(substr);
            }
             spanish = result.at(0);
             english = result.at(1);

            if (spanish == spanish_word) {
                status = true;
                break;
            }
        }
        in_file.close();
    }
    return status;
}

std::string capitalise(std::string word) {
    std::string reform{};
    for (auto letters : word) {
        letters = toupper(letters);
        reform += letters;
    }
    return reform;
}

void quit() {
    std::cout << "GOODBYE PLAYER" << std::endl;
    option = 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
