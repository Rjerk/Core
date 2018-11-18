
const MAX_POINTS: u32 = 100_000;

fn main() {

    let mut x = 5;
    println!("The value of x is: {}", x);
    x = 6;

    let spaces = "         ";
    let spaces = spaces.len();

    let guess : u32 = "42".parse().expect("Not a number!");

    let decimal = 98_222;
    let hex = 0xff;
    let octal = 0o77;
    let binary = 0b111_0000;
    let byte = b'a';

    let bool_v : bool = false;

    let quotient = 4 / 3;
    println!("{}", quotient);

    let tup: (i32, f64, u8) = (500, 6.5, 1);

    let tup = (1, 2, 3);

    let (x, y, z) = tup;

    let one = tup.0;

    let arr = [1, 2, 3];

    let one = arr[0];
}
