#include <stdint.h>
#include "person.hpp"

extern "C" {
extern person::detail::person* person_new(const char* name, const char* zip, uint32_t dob);
extern void person_free(person::detail::person* person);
}

namespace person {

Person Person::New(const std::string& name, const std::string& zip, uint32_t dob) {
    return Person(person_new(name.c_str(), zip.c_str(), dob));
}

Person::Person(struct detail::person* inner) : _inner(inner) {}

Person::Person(Person&& other) : _inner(std::move(other._inner)) {
    other._inner = nullptr;
}

Person& Person::operator=(Person&& other) {
    _inner = std::move(other._inner);
    other._inner = nullptr;
    return *this;
}

Person::~Person() {
    if (_inner != nullptr) {
        person_free(_inner);
    }
}

}
