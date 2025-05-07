#include <stdint.h>
#include <iostream>
#include "person.hpp"
#include "personbridge.h"

namespace person {

Person Person::New(const std::string& name, const std::string& zip, uint32_t dob) {
    return Person(rstperson::new_person(rust::Str(name), rust::Str(zip), dob));
}

Person::Person(::rust::Box<::rstperson::Person> inner) : _inner(std::move(inner)) {}

Person::Person(Person&& other) : _inner(std::move(other._inner)) {}

Person& Person::operator=(Person&& other) {
    _inner = std::move(other._inner);
    return *this;
}

Person::~Person() {
    std::cout << "Destroying Person" << std::endl;
}

}
