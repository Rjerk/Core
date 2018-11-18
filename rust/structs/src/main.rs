
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }

    fn square(size: u32) -> Rectangle {
        Rectangle { width: size, height: size }
    }
}

fn main() {
    let mut user1 = User {
        email: String::from("aaa@email.com"),
        username: "11".to_string(),
        active: true,
        sign_in_count: 1,
    };

    user1.username = String::from("aaa");

    let user2 = build_user(String::from("aa"), String::from("bnbb"));

    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);

    let rect1 = Rectangle{ width: 30, height : 50 };
    println!("area: {}", area(&rect1));
    println!("area: {}", rect1.area());

    println!("rect1: {:#?}", rect1);

    let rect2 = Rectangle{ width: 20, height: 10};
    println!("can hold? {}", rect1.can_hold(&rect2));

    println!("{:#?}", Rectangle::square(1));
}

fn area(rect : &Rectangle) -> u32 {
    rect.width * rect.height
}

fn build_user(email: String, username: String) -> User {
    User {
        email,
        username,
        sign_in_count: 1,
        active: true,
    }
}
