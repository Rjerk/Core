extern crate rand;


use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    println!("Guess the number!");

    let secret_num = rand::thread_rng().gen_range(1, 10);

    // println!("The secret_num is: {}", secret_num);

    loop {

        println!("Please input your guess: ");

        // let foo = 5; // immutable
        let mut guess = String::new(); // mutable
        // & reference
        io::stdin().read_line(&mut guess) // return io::Result, enums type, Err/Ok
            .expect("Fail to read_line");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("You guessed: {}", guess);

        match guess.cmp(&secret_num) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            },
        };
    }
}
