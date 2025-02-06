use std::{
    ffi::{c_char, c_double, c_uint, c_ulong, CStr},
    mem,
};

use person::Person;

fn to_str(c_str: *const c_char) -> &'static str {
    unsafe { CStr::from_ptr(c_str).to_str().unwrap() }
}

#[no_mangle]
extern "C" fn person_new(name: *const c_char, zip: *const c_char, dob: c_uint) -> *mut Person {
    let name = to_str(name);
    let zip = to_str(zip);
    let dob = dob as u32;

    Box::into_raw(Box::new(Person::new(name, zip, dob)))
}

#[no_mangle]
#[allow(unused_unsafe)]
extern "C" fn person_free(person: *mut Person) {
    unsafe {
        println!("dropping person");
        drop(Box::from(person));
    }
}
