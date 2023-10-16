#include "Container.h"

int main()
{
    std::cout << "[ Register ]\n";
    std::cout << "\nEnter your e-mail address: \n";
    std::cout << ">> ";
    std::string email;
    std::cin >> email;

    std::cout << "\nEnter your password: \n";
    std::string input;
    std::cout << ">> ";
    std::cin >> input;
    Container c(input);

    c.run();
}

//OPTIMIZE

//forfeit as a question
//hints as a question
//repeat the password as last question

//rating

//rename shit
