
mod person;

use person::{new_person, Person};



#[cxx::bridge(namespace = "rstperson")]
mod ffi {

    extern "Rust" {

        type Person;
        fn new_person(name: &str, zip: &str, dob: u32) -> Box<Person>;
        fn get_age(&self) -> u32;
        fn get_zip(&self) -> &str;
        fn update_zip(&mut self, zip: &str);

    }
}
