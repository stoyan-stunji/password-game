#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Windows.h"

#include "Timer.h"

std::string get_captcha()
{
    const char char_set[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int char_set_size = sizeof(char_set) - 1;
    std::string captcha;

    srand(std::time(0));

    for (int i = 0; i < 10; i++) 
    {
        int index = (rand() * std::time(NULL)) % char_set_size;
        captcha += char_set[index];
    }
    return captcha;
}

size_t get_time()
{
    size_t time = std::time(NULL);
    return time;
}

class Container
{
    private:
        std::string input;

        int tries = 1;
        const int LEFT = 1;
        const int RIGHT = 21;

        std::string difficulty = "*";

        bool is_15_long = false;

        bool has_small_letters = false;
        bool has_big_letters = false;
        bool has_digit = false;
        bool has_special_symbol = false;

        bool has_five_letters_lenght = false;
        bool has_digits_up_to_25 = false;
        bool has_month = false;

        bool has_captcha = false;
        std::string current_captcha = get_captcha();
        bool has_smoke_on_the_water = false;
        bool has_the_cat = false;

        bool has_fav_colour = false;
        bool has_random_gibberish = false;

        int random_1 = get_random(LEFT + 1, RIGHT);
        int random_2 = get_random(LEFT, RIGHT - 1);
        int random_3 = get_random(LEFT + 1, RIGHT - 3);

        bool has_the_smallest = false;
        bool has_the_alphabet_backwards = false;
        bool has_another_one_bites_the_dust = false;

        bool has_math = false;
        int increaser = get_random(LEFT + 5, RIGHT + 5);
        std::string math_answer = std::to_string((((random_1 * random_2) - random_3) + increaser));
        const char* math_answer_char = math_answer.c_str();

        bool has_time = false;
        size_t current_time = get_time();
        std::string time_answer = std::to_string(this->current_time);
        const char* time_answer_char = time_answer.c_str();

        bool has_periodic_table_element = false;
        bool has_best_programing_language = false;

        int get_random(int left, int right)
        {
            srand(std::time(0));
            return (left + (rand() % (right - left)));
        }

        void checker()
        {
            check_for_15_symbols();
            check_for_another_bites_the_dust();
            check_for_big_letters();
            check_for_captcha(current_captcha);
            check_for_digit();
            check_for_digits_up_to_25();
            check_for_fav_colour();
            check_for_five_letters_lenght();
            check_for_math();
            check_for_month();
            check_for_periodic_table_element();
            check_for_small_letters();
            check_for_smallest();
            check_for_smoke_on_the_water();
            check_for_special_symbol();
            check_for_the_alphabet_backwards();
            check_for_the_cat();
            check_for_time();
            check_for_best_programing_language();
        }

        const bool is_end(std::string input)
        {
            return (input == "end");
        }

        void increment_difficulty(std::string input)
        {
            if(input.size() % 7 == 0)
            {
                this->difficulty.push_back('*');
                this->difficulty.push_back('*');
            }    
            else if(input.find('&') == true)
            {
                this->difficulty.push_back('*');
                this->difficulty.push_back('*');
                this->difficulty.push_back('*');
            }  
            else
            {
                this->difficulty.push_back('*');
            }
        }

        const bool check_for_character(char start, char end) const
        {
            bool flag = false;
            for (char i = start; i <= end; i++)
            {
                if(this->input.find(i) != std::string::npos)
                {
                    flag = true;
                    break;
                }
            }
            return flag;
        }

        const bool check_for_sequence(const char input[]) const
        {
            bool flag = false;
            if (this->input.find(input) != std::string::npos) 
            {
                flag = true;
            }
            else
            { 
                flag = false;
            }
            return flag;
        }

        void check_for_small_letters()
        {
            if(check_for_character('a', 'z') == true)
            {
                this->has_small_letters = true;
            }
        }

        void check_for_big_letters()
        {
            if(check_for_character('A', 'Z') == true)
            {
                this->has_big_letters = true;
            }
        }

        void check_for_digit()
        {
            if(check_for_character('0', '9') == true)
            {
                this->has_digit = true;
            }
        }

        void check_for_special_symbol()
        {
            if(check_for_character(':', '@') == true 
            || check_for_character('[', '`') == true 
            || check_for_character('{', '~') == true)
            {
                this->has_special_symbol = true;
            }
        }

        void check_for_five_letters_lenght()
        {
            if(this->input.size() >= 50)
            {
                this->has_five_letters_lenght = true;
            }
        }

        void check_for_digits_up_to_25()
        {
            if (check_for_character('0', '9') == true)
            {
                int sum = 0;
                for (char c : this->input)
                {
                    if (std::isdigit(c) == true)
                    {
                        sum += (c - '0');
                    }
                }

                if (sum >= 50)
                {
                    this->has_digits_up_to_25 = true;
                }
            }
        }
    
        void check_for_month()
        {
            static const std::string months[] = 
            {
            "january", "february", "march", "april", "may", "june",
            "july", "august", "september", "october", "november", "december"
            };

            for (const std::string& month : months) 
            {
                if (this->input.find(month) != std::string::npos) 
                {
                    this->has_month = true;
                    break;
                }
            }
        }

        void check_for_captcha(std::string captcha)
        {
            if (this->input.find(captcha) != std::string::npos) 
            {
                this->has_captcha = true;
            }
        }
    
        void check_for_smoke_on_the_water()
        {
            if (check_for_sequence("035036503530") == true) 
            {
                this->has_smoke_on_the_water = true;
            }
        }

        void check_for_the_cat()
        {
            if (check_for_sequence("UwU") == true) 
            {
                this->has_the_cat = true;
            }
        }
    
        void check_for_fav_colour()
        {
            if (check_for_sequence("RGB") == true) 
            {
                this->has_fav_colour = true;
            }
        }
    
        void check_for_smallest()
        {
            if (check_for_sequence("smallest") == true) 
            {
                this->has_the_smallest = true;
            }
        }

        void check_for_the_alphabet_backwards()
        {
            if (check_for_sequence("tebahpla") == true) //alphabet
            {
                this->has_the_alphabet_backwards = true;
            }
        }

        void check_for_another_bites_the_dust()
        {
            if (check_for_sequence("000000305") == true)
            {
                this->has_another_one_bites_the_dust = true;
            }
        }

        void check_for_math()
        {
            if (check_for_sequence(this->math_answer_char) == true)
            {
                this->has_math = true;
            }
        }

        void check_for_15_symbols()
        {
            if(this->input.size() >= 15)
            {
                this->is_15_long = true;
            }
        }

        void check_for_time()
        {
            if (check_for_sequence(this->time_answer_char) == true) 
            {
                this->has_time = true;
            }
        }

        void check_for_periodic_table_element()
        {
            static const std::string elements[] = 
            {
                "HE", "NE", "CL", "AR", "SE", "BR", "KR", "XE", "AT", "RN"
            };

            for (const std::string& singular : elements) 
            {
                if (this->input.find(singular) != std::string::npos) 
                {
                    this->has_periodic_table_element = true;
                    break;
                }
            }
        }
    
        void check_for_best_programing_language()
        {
            if (check_for_sequence("C++") == true)
            {
                this->has_best_programing_language = true;
            }
        }
    
    public:
        Container(std::string input)
        {
            this->input = input;

            checker();
            increment_difficulty(this->input);
        }

        void run()
        {
            bool flag_ended = false;
            bool flag_finished_game = false;
            int random = get_random(LEFT, RIGHT);

            Timer t;
            if(this->input.size() < 15)
            {
                check_for_15_symbols();
                std::cout << "\nYour password must be AT LEAST 15 SYMBOLS LONG!\n";
                std::cout << ">> " << this->input;
                std::string new_input;
                std::cin >> new_input;
                this->input += new_input;
            }
            else if(this->input.size() >= 15 && this->input.size() < 50)
            {
                check_for_five_letters_lenght();
                std::cout << "\nYour password must be AT LEAST 50 SYMBOLS LONG!\n";
                std::cout << ">> " << this->input;
                std::string new_input;
                std::cin >> new_input;
                this->input += new_input;
            }

            t.begin();

            while(flag_ended == false || flag_finished_game == false)
            {
                bool THE_BIG_BOOL = (this->has_small_letters == true && this->has_big_letters == true
                && this->has_digit == true && this->has_special_symbol == true && 
                this->has_five_letters_lenght == true && this->has_digits_up_to_25 == true
                && this->has_month && this->has_captcha && this->has_smoke_on_the_water
                && this->has_the_cat && this->has_fav_colour && this->has_the_smallest
                && this->has_the_alphabet_backwards && this->has_another_one_bites_the_dust
                && this->has_math && this->is_15_long && this->has_time
                && this->has_periodic_table_element && this->has_best_programing_language);

                if(THE_BIG_BOOL == true)
                {
                    flag_finished_game = true;
                    t.finish();
                    if(t.getDiff() >= 60)
                    {
                        increment_difficulty(this->input);
                    }
                    std::cout << "\nPassword Difficulty: " << this->difficulty << '\n';
                    std::cout << "Congrats! You have finished the game in " << t << " with " << tries << " tries!\n";
                    break;
                }

                if(random == 1)
                {
                    check_for_small_letters();
                    if(this->has_small_letters == false)
                    {
                        std::cout << "\nYour password must contain at least one SMALL letter!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;       
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }          
                    }
                }
                else if(random == 2)
                {
                    check_for_big_letters();
                    if(this->has_big_letters == false)
                    {
                        std::cout << "\nYour password must contain at least one BIG letter!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        } 
                    }
                }
                else if(random == 3)
                {
                    check_for_digit();
                    if(this->has_digit == false)
                    {
                        std::cout << "\nYour password must contain at least one DIGIT!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        } 
                    }
                }
                else if(random == 4)
                {
                    check_for_special_symbol();
                    if(this->has_special_symbol == false)
                    {
                        std::cout << "\nYour password must contain at least one SPECIAL SYMBOL!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        } 
                    }
                }
                else if(random == 5)
                {
                    check_for_five_letters_lenght(); // fix name
                    if(this->has_five_letters_lenght == false)
                    {
                        std::cout << "\nYour password must be AT LEAST 50 SYMBOLS LONG!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        } 
                    }
                }
                else if(random == 6)
                {
                    check_for_digits_up_to_25(); //fix name
                    if(this->has_digits_up_to_25 == false)
                    {
                        std::cout << "\nThe digits in your password MUST ADD UP TO 50!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 7)
                {
                    check_for_month();
                    if(this->has_month == false)
                    {
                        std::cout << "\nThe password must contain a MONTH OF THE YEAR!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 8)
                {
                    check_for_captcha(this->current_captcha);
                    if(this->has_captcha == false)
                    {
                        std::cout << "\nThe password must contain the CAPTCHA!\n";
                        std::cout << "[ " << this->current_captcha << " ]" << '\n';
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 9)
                {
                    check_for_smoke_on_the_water();
                    if(this->has_smoke_on_the_water == false)
                    {
                        std::cout << "\nPlay SMOKE ON THE WATER!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 10)
                {
                    check_for_the_cat();
                    if(this->has_the_cat == false)
                    {
                        std::cout << "\nThis is my cat Nasko UwU and he is very cold! I think you should keep him in the password!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 11)
                {
                    check_for_fav_colour();
                    if(this->has_fav_colour == false)
                    {
                        std::cout << "\nThe password must contain MY FAVOURITE COLOUR!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 12)
                {
                    if(this->has_random_gibberish == false)
                    {
                        Sleep(200);
                        std::cout << "\nHere are some RANDOM LETTERS!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input = get_captcha();
                        std::cout << new_input << '\n';
                        this->input += new_input;
                        this->has_random_gibberish = true;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 13)
                {
                    check_for_smallest();
                    if(this->has_the_smallest == false)
                    {
                        std::cout << "\nThe password must include the SMALLEST!\n[ " << this->random_1 
                        << " " << this->random_2 << " " << this->random_3 << " ]\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 14)
                {
                    check_for_the_alphabet_backwards();
                    if(this->has_the_alphabet_backwards == false)
                    {
                        std::cout << "\nThe password must include the ALPHABET BACKWARDS!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 15)
                {
                    check_for_another_bites_the_dust();
                    if(this->has_another_one_bites_the_dust == false)
                    {
                        std::cout << "\nPlay ANOTHER ONE BITES THE DUST!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 16)
                {
                    check_for_math();
                    if(this->has_math == false) //(random_1 + random_2) - random_3) * increaser)
                    {
                        std::cout << "\nThe password must include THE ANSWER to the MATH QUESTION!\n[ " 
                        << "((" << this->random_2 << " * " << this->random_1 << ") - " << this->random_3 << ") + " << this->increaser << " ]\n";
                        std::cout << this->math_answer << ">> " << this->input; //remove answer
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 17)
                {
                    check_for_15_symbols();
                    if(this->is_15_long == false)
                    {
                        std::cout << "\nYour password must be AT LEAST 15 SYMBOLS LONG!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        } 
                    }
                }
                else if(random == 18)
                {
                    check_for_time();
                    if(this->has_time == false)
                    {
                        std::cout << "\nYour password must include THE TIME IN UNIX TIME!\n";
                        std::cout << this->current_time << ">> " << this->input; //remove answer
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        } 
                    }
                }
                else if(random == 19)
                {
                    check_for_periodic_table_element();
                    if(this->has_periodic_table_element == false)
                    {
                        std::cout << "\nThe password must include a TWO LETTER NON-METAL FROM THE PERIODIC TABLE!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
                else if(random == 20)
                {
                    check_for_best_programing_language();
                    if(this->has_best_programing_language == false)
                    {
                        std::cout << "\nThe password must include a THE BEST PROGRAMING LANGUAGE!\n";
                        std::cout << ">> " << this->input;
                        std::string new_input;
                        std::cin >> new_input;
                        this->input += new_input;

                        random = get_random(LEFT, RIGHT);
                        tries++;
                        increment_difficulty(new_input);
                    }
                    else
                    {
                        if(THE_BIG_BOOL == false)
                        {
                            random = get_random(LEFT, RIGHT);
                        }  
                        else
                        {
                            flag_finished_game = true;
                        }
                    }
                }
            }
        }
};

#endif