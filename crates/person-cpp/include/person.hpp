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
    //todo: delete unwanted constructors
    // ~Person();

    static Person New(const std::string& name, const std::string& zip, uint32_t dob);

  private:
    Person(detail::person* inner);

    detail::person* _inner;
};

}
