#pragma once

#include <string>
#include <stdint.h>

#include "lib.h"

namespace person {
namespace detail {

    //! Opaque struct used only in interface with the underlying C API
    struct person;
}

class Person final
{
  public:
    ~Person();

    Person(Person& other) = delete;
    Person(Person&& other);

    Person& operator=(Person& other) = delete;
    Person& operator=(Person&& other);

    static Person New(const std::string& name, const std::string& zip, uint32_t dob);

  private:
    explicit Person(::rust::Box<::prs::Person> inner);

    // detail::person* _inner;

    ::rust::Box<::prs::Person> _inner;
};

}
