use chrono::Datelike;

#[cxx::bridge(namespace = "prs")] // todo scoping? #[cxx::bridge(namespace = "org::blobstore")]
mod ffi {

    extern "Rust" {

        type Person;
        fn new_person(name: &str, zip: &str, dob: u32) -> Box<Person>;
        fn get_age(&self) -> u32;
        fn get_zip(&self) -> &str;
        fn update_zip(&mut self, zip: &str);

    }
}

pub struct Person {
    name: String,
    zip: String,
    dob: u32, //todo use chrono::NaiveDate
    id: u32,  // in future may be hash of above
}

fn new_person(name: &str, zip: &str, dob: u32) -> Box<Person> {
    Box::new(Person::new(name, zip, dob))
}
impl Person {
    pub fn new(name: &str, zip: &str, dob: u32) -> Person {
        Person {
            name: name.to_string(),
            zip: zip.to_string(),
            dob,
            id: 0,
        }
    }

    pub fn get_age(&self) -> u32 {
        let current_year = chrono::Utc::now().naive_utc().year_ce().1 as u32;
        current_year - self.dob
    }

    pub fn get_zip(&self) -> &str {
        &self.zip.as_str()
    }

    pub fn update_zip(&mut self, zip: &str) {
        self.zip = zip.to_string();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn new_person() {
        let p = Person::new("John Doe", "12345", 1980);
        assert_eq!(p.name, "John Doe");
        assert_eq!(p.zip, "12345");
        assert_eq!(p.id, 0);
        assert_eq!(p.dob, 1980);
    }

    #[test]
    fn get_person_age() {
        let p = Person::new("John Doe", "12345", 1980);
        assert_eq!(p.get_age(), 45);
    }

    #[test]
    fn get_person_zip() {
        let p = Person::new("John Doe", "12345", 1980);
        assert_eq!(p.get_zip(), "12345");
    }

    #[test]
    fn update_person_zip() {
        let mut p = Person::new("John Doe", "12345", 1980);
        p.update_zip("54321");
        assert_eq!(p.get_zip(), "54321");
    }
}
