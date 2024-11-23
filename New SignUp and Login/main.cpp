#include <iostream>
#include <curl/curl.h>
#include <string>
#include "UserManager.h"

int main() {

    UserManager newManger;
    int choice;
    std::cout << "1: Sign Up" << std::endl;
    std::cout << "2: Sign In" << std::endl;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        newManger.signUp();
    }
    else if (choice == 2) {
        newManger.signIn();
    }
    else {
        std::cerr << "Invalid choice!" << std::endl;
    }

    return 0;
}