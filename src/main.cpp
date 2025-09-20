#include <iostream>
#include <string>
#include "parser.h"

int main() {
    // Faster i/o (harmless here, different style)
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string lineName;
    std::string lineEmail;

    // Expect two lines: full name, then email
    std::getline(std::cin, lineName);
    std::getline(std::cin, lineEmail);

    // Heap-allocate per assignment requirement
    std::string* fName = new std::string();
    std::string* lName = new std::string();

    // Derive parts
    StringUtils::parseName(lineName, fName, lName);
    const std::string handle = StringUtils::getUsername(lineEmail);

    // EXACT labels
    std::cout << "First Name: " << *fName << '\n';
    std::cout << "Last Name: "  << *lName  << '\n';
    std::cout << "Username: "   << handle  << '\n';

    // Clean up
    delete fName;
    delete lName;

    return 0;
}