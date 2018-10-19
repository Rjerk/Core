
int lookup1() { return 0; }

double lookup2() { return 1.1111; }

decltype(auto) look_up_a_string_1() {
    return lookup1();
}
decltype(auto) look_up_a_string_2() {
    return lookup2();
}

int main()
{

}
