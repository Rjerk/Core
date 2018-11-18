fn main() {
    let mut s = String::from("hello");

    s.push_str(", world");

    println!("{}", s);

    let s1 = String::from("SSSSSSSSSSS");

    let s2 = s1.clone();

    println!("{}, world", s1);


    let str = String::from("ownership");

    takes_ownership(str);

    let x = 54;

    makes_copy(x);

    let s1 = gives_ownership();

    let s2 = String::from("hello");

    let s3 = takes_and_gives_back(s2);

    let (s4, len) = calculate_length(s3);

    let len = calculate_length_2(&s4);

    let mut s5 = s4;

    change(&mut s5); 

    {

        let s6 = &mut s5;
    }

    let s7 = &mut s5;

    let s8 = &s7;
    let s9 = &s7;

    let s9 = String::from("helloworld");
    let word = first_word(&s9);
    println!("{}", word);


    let sa = String::from("12100");

    let twelve = &sa[..2];
    let onehundred = &sa[2..];

    println!("{}, {}, {}", twelve, onehundred, &sa[..]);

    let sb = "111 11";

    // string literal is string slice
    let word = first_word(sb);
}

fn takes_ownership(some_string: String) {
    println!("{}", some_string);
}

fn makes_copy(some_integer: i32) { 
    println!("{}", some_integer);
}

fn gives_ownership() -> String {
    let some_string = String::from("hello");

    some_string
}

fn takes_and_gives_back(a: String) -> String {
    a
}

fn calculate_length(s: String) -> (String, usize) {
    let len = s.len();

    (s, len)
}

fn calculate_length_2(s: &String) -> usize {
    s.len()
}

fn change(s: &mut String) {
    s.push_str(", world");
}


// slice type declaration: &str
fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    &s[..]
}
