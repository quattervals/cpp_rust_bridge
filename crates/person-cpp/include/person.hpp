#pragma once

#include <string>
#include <stdint.h>

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
    explicit Person(detail::person* inner);

    detail::person* _inner;
};

}
