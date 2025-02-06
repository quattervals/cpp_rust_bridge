#include "person.hpp"
#include <iostream>


int main() {
    person::Person p = person::Person::New("hugo", "1,2,3", 22);
    std::cout << "we got a person" << std::endl;
    person::Person pepe = std::move(p);
    return 0;
}
