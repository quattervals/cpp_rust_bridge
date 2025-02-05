#include <stdint.h>
#include "person.hpp"

extern "C" {

extern person::detail::person* person_new(const char* name, const char* zip, uint32_t dob);
}

namespace person {

Person Person::New(const std::string& name, const std::string& zip, uint32_t dob) {
    return person_new(name.c_str(), zip.c_str(), dob);
}

Person::Person(struct detail::person* inner) : _inner(inner) {}

}
