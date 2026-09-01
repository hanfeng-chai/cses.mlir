fn main() {
    var exponent = read();
    let modulus = 1_000_000_007;
    var result = 1;
    var base = 2;

    while exponent > 0 {
        if (exponent & 1) != 0 {
            result = result * base % modulus;
        }
        base = base * base % modulus;
        exponent >>= 1;
    }
    println(result);
}