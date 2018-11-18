fn main() {
    let num = 3;
    if num < 5 { 
        println!("true");
    } else {
        println!("false");
    }

    if num != 0 {

    } else if num == 3 {

    } else {

    }

    let condition = true;

    let num = if condition {
        5
    } else {
        6
    };

    loop {
        break;
    }

    let mut num = 4;

    while num != 0 {
        println!("{}!", num);

        num -= 1;
    }

    let arr = [1, 2, 3, 4, 5];

    for elem in arr.iter() {
        println!("value: {}", elem);
    }

    for num in (1..10).rev() {
        println!("{}!", num);
    }
}
