

fn main() {
    println!("{}", another_func(1, 2));

    let _x = 5;

    let _y = {
        let _x = 3;
        _x + 1
    };
}

fn another_func(x : i32, y : i32) -> i32 {
    println!("x + y: {}", x + y);
    x + y
}
