#pragma once

#include <string>
#include <stdint.h>

#include "personbridge.h"

namespace person {

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
    explicit Person(::rust::Box<::rstperson::Person> inner);

    ::rust::Box<::rstperson::Person> _inner;
};

}
