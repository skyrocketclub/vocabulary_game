// Vocabulary_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <time.h>


void display_menu();
void quit();
void play_game();
void add_word();
void view_words();
void about_game();
bool check_word(std::string spanish_word);
std::string capitalise(std::string);
void insert_no_highscore();
size_t check_word_count();
double play_default(int,std::string);
double play_main(int,std::string);

//So, after the user has finished the session, there can be an option for him to retry the ones that he missed
//He can keep on playing the ones he misses after this till he decides to quit.
//When he gets the words, they leave the pool of the æmissed words

int option{ 1 };//universal variable...

int main()
{
    std::cout << "\t\t\t*******************VOCABULARY GAME*******************" << std::endl;
    display_menu();

    return 0;
}

void display_menu() {

    if (option == 1) {
        int choice{};
        std::cout << "1 - PLAY GAME\n2 - ADD NEW WORDS\n3 - VIEW ALL WORDS\n4 - ABOUT GAME\n0 - QUIT\n";

        std::string entry{};
        bool done{ false };
        do {
            std::cout << "OPTION: ";
            std::cin >> entry;
            std::istringstream validator{ entry };
            if (validator >> choice) {
                done = true;
            }
            else {
                std::cout << "KINDLY ENTER A VALID INPUT\n";
                std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
            }


        } while (!done);

      

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
    std::string player_name{}, h_score{};
    int word_source{}; 
    size_t num = check_word_count();
    system("CLS");
    std::cout << "WELCOME PLAYER\nEnter your nick_name:" << std::endl;
    std::cin.ignore(1, '\n');
    std::getline(std::cin,player_name);
    player_name = capitalise(player_name);

    system("CLS");
    std::cout << "WELCOME " << player_name << " TO THE VOCABULARY GAME\n\nCHOOSE A WORD SOURCE\n";
    std::cout << "1 - DEFAULT WORD BANK\n";
    std::cout<<"2 - MY WORD BANK ";
    if (num < 50) {
        std::cout << " (NOT CURRENTLY AVAILBLE - YOU NEED " << 50 - num << " MORE WORDS)\n";
    }

    else {
        std::cout << " (AVAILABLE)\n";
    }
   word_source_retry: std::cout << "OPTION: ";

    //DATA VALIDATION
    std::string entry{};
    bool done{ false };
    do {
        std::cout << "OPTION: ";
        std::cin >> entry;
        std::istringstream validator{ entry };
        if (validator >> word_source) {
            done = true;
        }
        else {
            std::cout << "KINDLY ENTER A VALID INPUT\n";
            std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
        }
    } while (!done);



    switch (word_source)
    {
        case 1:
        {
        defaults: int attempts{ 0 };
            double highscore{}, current_score{};

            std::string h_score{}, substr{};
            std::vector<std::string>result;
            double current_highscore{};

           
            std::cout << player_name << " WELCOME\nCurrent Highscore: ";

            std::ifstream in_file;
            in_file.open("default_words.txt");
 
            //first read out the high score...
            std::getline(in_file, h_score);
            std::stringstream s_stream(h_score);

            while (s_stream.good()) {
                std::getline(s_stream, substr, ',');
                result.push_back(substr);
            }
            std::cout << result.at(0) << " with " << result.at(1)<<" %" << std::endl;
            current_highscore = stod(result.at(1));
            
            //Now to the playing of the game..
            std::cout << std::endl;
            std::cout << "HOW MANY WORDS WOULD YOU LIKE TO ATTEMPT?\nOPTION: ";
            std::cin >>attempts ;
            in_file.close();

            current_score = play_default(attempts,player_name);
            if (current_score >= current_highscore) {
                std::cout << "NEW HIGHSCORE!\n"<<player_name<<" : "<<current_score<<" %" << std::endl;
                std::ifstream in_file;
                
                in_file.open("default_words.txt");
                std::vector<std::string> lines;
                std::string line{};
                
                while (std::getline(in_file, line)) {
                    lines.push_back(line);
                }
                in_file.close();

                std::ofstream out_file("temp.txt");
                
                out_file << player_name << "," << current_score << std::endl;
                for (size_t i{ 1 }; i < lines.size(); i++) {
                    out_file << lines.at(i) << std::endl;
                }
                out_file.close();
                remove("default_words.txt");
                rename("temp.txt", "default_words.txt");
            }

            else {
                std::cout << "YOUR SCORE IS: " << current_score <<" %" << std::endl;
            }

            
            
        }
        break;

        case 2:
        {
            size_t number{};
            int attempts{ 0 }, option{};
            double highscore{}, current_score{};

            std::string h_score{}, substr{};
            std::vector<std::string>result;
            double current_highscore{};

            number = check_word_count();
            if (number < 50) {
                std::cout << "YOU NEED 50 WORDS TO PLAY WITH YOUR WORD SOURCE, YOU HAVE: " << number << std::endl;
                std::cout << "1 - PLAY WITH DEFAULT\n2 - RETURN TO HOME MENU\nOPTION: ";
                std::cin >> option;
                switch (option)
                {
                    case 1:
                    {
                        system("CLS");
                        goto defaults;
                    }
                    break;
                    case 2:
                    {
                        system("CLS");
                        display_menu();
                    }
                    break;
                    default:
                    {
                        std::cout << "INVALID OPTION\n";
                    }
                }
            }

            else {
                std::cout << player_name << " WELCOME\nCurrent Highscore: ";

                std::ifstream in_file;
                in_file.open("words.txt");

                //first read out the high score...
                std::getline(in_file, h_score);
                std::stringstream s_stream(h_score);

                while (s_stream.good()) {
                    std::getline(s_stream, substr, ',');
                    result.push_back(substr);
                }
                std::cout << result.at(0) << " with " << result.at(1) << " %" << std::endl;
                current_highscore = stod(result.at(1));

                //Now to the playing of the game..
                std::cout << std::endl;
                std::cout << "HOW MANY WORDS WOULD YOU LIKE TO ATTEMPT?\nOPTION: ";
                std::cin >> attempts;
                in_file.close();

                current_score = play_default(attempts, player_name);
                if (current_score >= current_highscore) {
                    std::cout << "NEW HIGHSCORE!\n" << player_name << " : " << current_score << " %" << std::endl;
                    std::ifstream in_file;

                    in_file.open("default_words.txt");
                    std::vector<std::string> lines;
                    std::string line{};

                    while (std::getline(in_file, line)) {
                        lines.push_back(line);
                    }
                    in_file.close();

                    std::ofstream out_file("temp.txt");

                    out_file << player_name << "," << current_score << std::endl;
                    for (size_t i{ 1 }; i < lines.size(); i++) {
                        out_file << lines.at(i) << std::endl;
                    }
                    out_file.close();
                    remove("default_words.txt");
                    rename("temp.txt", "default_words.txt");
                }

                else {
                    std::cout << "YOUR SCORE IS: " << current_score << " %" << std::endl;
                }
            }
        }
        break;

        default:
        {
            std::cout << "KINDLY ENTER A VALID OPTION" << std::endl;
            goto word_source_retry;
        }
    }

}

double play_default(int attempts,std::string player_name) {
    std::string line{}, h_score{}, current_line{};
    size_t game_size{};
    int trial{ attempts }, pos;
    double score{ 0 }, expected_score{}, percentage{};
    std::vector <std::string> missed;
    std::vector<std::string>missed_temp{};

    expected_score = attempts * 10;

    std::ifstream in_file;
    in_file.open("default_words.txt");

    std::vector<std::string>entry;
    std::vector<std::string>default_failed;

    std::getline(in_file, h_score);
    while (std::getline(in_file, line)) {
        entry.push_back(line);
    }

    game_size = entry.size();
    std::cin.ignore(1, '\n');

    while (trial > 0) {
        srand(time(nullptr));
        pos = rand() % game_size ; 
        current_line = entry.at(pos);

        std::string english{};
        std::stringstream s_stream(current_line);
        std::string substr{};
        std::vector<std::string> result;

        while (s_stream.good()) {
            std::getline(s_stream, substr, ',');
            result.push_back(substr);
        }
      

        std::cout << result.at(0) << ": ";
        std::getline(std::cin, english);
        english = capitalise(english);
        if (english == result.at(1)) {
            score += 10;
            std::cout << "\nCORRECT!\n\n";
        }
        else {
            std::cout << "\nINCORRECT! (ANSWER: "<<result.at(1)<<" ) \n\n";
            missed_temp.push_back(current_line);
        }

        trial--;
    }
    percentage = (score / expected_score) * 100;

    missed = missed_temp;
    size_t misses = missed.size();
    bool retry{ true };
    int retry_opt{};

    if (misses > 0) {

        while (retry == true) {
            do {
                missed = missed_temp;
                missed_temp.clear();

                std::cout << std::endl << std::endl;
                retry_opt_retry: std::cout << " WOULD YOU LIKE TO RETRY THE MISSED ATTEMPTS?\n1 - YES\n2 - NO\nOPTION: ";


                //DATA VALIDATION
                std::string entry{};
                bool done{ false };
                do {
                    std::cout << "OPTION: ";
                    std::cin >> entry;
                    std::istringstream validator{ entry };
                    if (validator >> retry_opt) {
                        done = true;
                    }
                    else {
                        std::cout << "KINDLY ENTER A VALID INPUT\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
                    }
                } while (!done);

             
                std::cin.ignore(1, '\n');

                if (retry_opt == 1) {
                    system("CLS");
                    for (size_t i{ 0 }; i < missed.size(); i++) {
                        std::string english_missed;
                        std::string spanish_missed;
                        std::string substr_missed;
                        std::stringstream s_stream(missed.at(i));
                        std::vector<std::string>result_missed;

                        while (s_stream.good()) {
                            std::getline(s_stream, substr_missed, ',');
                            result_missed.push_back(substr_missed);
                        }

                        std::cout << result_missed.at(0) << ": ";
                        std::getline(std::cin, english_missed);
                        english_missed = capitalise(english_missed);

                        if (english_missed == result_missed.at(1)) {
                            std::cout << "CORRECT! " << std::endl;
                        }

                        else {
                            std::cout << "INCORRECT! (ANSWER: " << result_missed.at(1) << " )" << std::endl;
                            missed_temp.push_back(missed.at(i));
                        }
                        std::cout << std::endl;
                    }
                    retry = true;
                    if (missed_temp.size() == 0) {
                        retry = false;
                    }
                }
                else if (retry_opt == 2) {
                    retry = false;
                }
                else {
                    std::cout << "KINDLY ENTER A VALID INPUT\n";
                    goto retry_opt_retry;
                }
            } while (missed_temp.size() > 0);
        }
    }

    else {

    }

    in_file.close();
    return percentage;
}

double play_main(int attempts,std::string ) {
    std::string line{}, h_score{}, current_line{};
    size_t game_size{};
    int trial{ attempts }, pos;
    double score{ 0 }, expected_score{}, percentage{};
    std::vector <std::string> missed;
    std::vector<std::string>missed_temp{};

    expected_score = attempts * 10;

    std::ifstream in_file;
    in_file.open("words.txt");

    std::vector<std::string>entry;
    std::vector<std::string>default_failed;

    std::getline(in_file, h_score);
    while (std::getline(in_file, line)) {
        entry.push_back(line);
    }

    game_size = entry.size();
    std::cin.ignore(1, '\n');

    while (trial > 0) {
        srand(time(nullptr));
        pos = rand() % game_size;
        current_line = entry.at(pos);

        std::string english{};
        std::stringstream s_stream(current_line);
        std::string substr{};
        std::vector<std::string> result;

        while (s_stream.good()) {
            std::getline(s_stream, substr, ',');
            result.push_back(substr);
        }


        std::cout << result.at(0) << ": ";
        std::getline(std::cin, english);
        english = capitalise(english);
        if (english == result.at(1)) {
            score += 10;
            std::cout << "\nCORRECT!\n\n";
        }
        else {
            std::cout << "\nINCORRECT! (ANSWER: " << result.at(1) << " ) \n\n";
            missed_temp.push_back(current_line);
        }

        trial--;
    }
    percentage = (score / expected_score) * 100;


    missed = missed_temp;
    size_t misses = missed.size();
    bool retry{ true };
    int retry_opt{};

    if (misses > 0) {

        while (retry == true) {
            do {
                missed = missed_temp;
                missed_temp.clear();

                std::cout << std::endl << std::endl;
                retry_again:std::cout << " WOULD YOU LIKE TO RETRY THE MISSED ATTEMPTS?\n1 - YES\n2 - NO\nOPTION: ";

                //DATA VALIDATION
                std::string entry{};
                bool done{ false };
                do {
                    std::cout << "OPTION: ";
                    std::cin >> entry;
                    std::istringstream validator{ entry };
                    if (validator >> retry_opt) {
                        done = true;
                    }
                    else {
                        std::cout << "KINDLY ENTER A VALID INPUT\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
                    }
                } while (!done);

              
                std::cin.ignore(1, '\n');

                if (retry_opt == 1) {
                    system("CLS");
                    for (size_t i{ 0 }; i < missed.size(); i++) {
                        std::string english_missed;
                        std::string spanish_missed;
                        std::string substr_missed;
                        std::stringstream s_stream(missed.at(i));
                        std::vector<std::string>result_missed;

                        while (s_stream.good()) {
                            std::getline(s_stream, substr_missed, ',');
                            result_missed.push_back(substr_missed);
                        }

                        std::cout << result_missed.at(0) << ": ";
                        std::getline(std::cin, english_missed);
                        english_missed = capitalise(english_missed);

                        if (english_missed == result_missed.at(1)) {
                            std::cout << "CORRECT! " << std::endl;
                        }

                        else {
                            std::cout << "INCORRECT! (ANSWER: " << result_missed.at(1) << " )" << std::endl;
                            missed_temp.push_back(missed.at(i));
                        }
                        std::cout << std::endl;
                    }
                    retry = true;
                    if (missed_temp.size() == 0) {
                        retry = false;
                    }
                }
                else if (retry_opt == 2) {
                    retry = false;
                }
                else {
                    std::cout << "KINDLY ENTER A VALID INPUT\n";
                    goto retry_again;
                }
            } while (missed_temp.size() > 0);
        }
    }

    in_file.close();
    return percentage;
}

void insert_no_highscore() {
    size_t count{};
    count = check_word_count();

    if (count == 0) {
        std::ofstream out_file("words.txt", std::ios::app);
        out_file << "NO HIGH SCORE YET,0" << std::endl;
        out_file.close();
    }
}

size_t check_word_count() {
    std::string line{};
    std::vector <std::string> lines;
    size_t value{};

    //This creates the file incase it does not exist...
    std::ofstream out_file("words.txt", std::ios::app);
    out_file.close();

    std::ifstream in_file;
    in_file.open("words.txt");
    while (std::getline(in_file, line)) {
        lines.push_back(line);
    }
  
    value = lines.size();
    in_file.close();
    return value;
}

void add_word() {
    system("CLS");
    bool status{ false };

    std::string spanish{}, english{};
    int number{};

    insert_no_highscore();
    std::ofstream out_file("words.txt", std::ios::app);
   
    
    if (!out_file) {
        std::cerr << "Error Opening File" << std::endl;
    }
    else {

        std::cout << "How many words would you like to add?" << std::endl;  
             

        //DATA VALIDATION

        bool done{ false };
        std::string entry;

        do {
            std::cout << "Option: ";
            std::cin >> entry;
            std::istringstream validator{ entry };
            if(validator >> number) {
                done = true;  
            }
            else {
                std::cout << "KINDLY ENTER A VALID INPUT\n";
                std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
            }
        } while (!done);

        std::cin.ignore(1, '\n');

        if (number > 0) {
            for (int i{ 0 }; i < number; i++) {


                std::cout << std::endl << "Spanish Word: ";
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
       }

        
        out_file.close();
    }
}

void view_words() {
    system("CLS");
    std::string spanish{}, english{}, line{}, temp{}, high_score{};
    std::vector<std::string>entry;
   

    std::ifstream in_file;
    in_file.open("words.txt");

    if (!in_file) {
        std::cerr << "There are no words in you record at the moment" << std::endl;
    }
    else {
        getline(in_file, high_score);

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
    system("CLS");
    std::cout << "	Vocabulary Chase\n1 - Use Default word Bank(The user can use the word bank in the .txt file that accompanies the  application).\n2 - Use Your Word Bank(will not work except you have 50 words available).\n GAME MODES AVAILABLE\n3 - Firstly, the user can choose to use the default word bank, or rather use his own word bank(which must have up to 50 words before this operation can run)\n4 - ANY WORDS ADDED MUST FOLLOW THIS FORMAT --> SPANISH,ENGLISH  <-- \n5 - Each time, the user chooses how many words he wants to attempt.\n6 - The High score is usually stored in percentage.It is usually displayed on attempt of a new game\n7 - Words that are missed are stored…\n8 - So, after the user has finished the session, there can be an option for him to retry the ones that he missed…\n9 - He can keep on playing the ones he misses after this till he decides to quit.\n10 - When he gets the words, they leave the pool of the ‘missed words’.\n11 - Then if the user beats or meets the high score, there is now a new high score…" << std::endl << std::endl;
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
