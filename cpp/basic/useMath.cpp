// C++ code to demonstrate the round( ), lround( ), llround( ) functions
#include <cmath>
#include <iostream>

using namespace std;
// test function round()
void testRound();
void testFloor();
void testCeil();
// Driver program
int main() {
    // 四舍五入（最接近的）
    // testRound();
    // 向下取整
    testFloor();
    // 向上取整
    testCeil();
    return 0;
}

void testRound() {
    // initializing value
    double x = 32.14, y = 12.552, z = 91.78;
    cout << "Nearest value of " << x << " : " << round(x) << "\n";
    cout << "Nearest value of " << y << " : " << round(y) << "\n";
    cout << "Nearest value of " << z << " : " << round(z) << "\n\n";

    /**** Positive Floating Number of decimal value less than 0.5 *****/
    x = 0.14, y = 21.48, z = 0.075;
    cout << "round(" << x << ") = " << round(x);
    cout << "\t\t"
         << "round(" << y << ") = " << round(y);
    cout << "\t\t"
         << "round(" << z << ") = " << round(z) << endl;

    cout << "lround(" << x << ") = " << lround(x);
    cout << "\t"
         << "lround(" << y << ") = " << lround(y);
    cout << "\t\t"
         << "lround(" << z << ") = " << lround(z) << endl;

    cout << "llround(" << x << ") = " << llround(x);
    cout << "\t"
         << "llround(" << y << ") = " << llround(y);
    cout << "\t\t"
         << "llround(" << z << ") = " << llround(z) << endl
         << endl;

    /**** Positive Floating Number of decimal value greater than 0.5 ****/
    x = 0.85, y = 25.73, z = 91.553;
    cout << "round(" << x << ") = " << round(x);
    cout << "\t\t"
         << "round(" << y << ") = " << round(y);
    cout << "\t\t"
         << "round(" << z << ") = " << round(z) << endl;

    cout << "lround(" << x << ") = " << lround(x);
    cout << "\t"
         << "lround(" << y << ") = " << lround(y);
    cout << "\t\t"
         << "lround(" << z << ") = " << lround(z) << endl;

    cout << "llround(" << x << ") = " << llround(x);
    cout << "\t"
         << "llround(" << y << ") = " << llround(y);
    cout << "\t\t"
         << "llround(" << z << ") = " << llround(z) << endl
         << endl;

    /**** Positive Floating Number of decimal value 0.5 ****/
    x = 0.50, y = 25.5, z = 91.500;
    cout << "round(" << x << ") = " << round(x);
    cout << "\t\t"
         << "round(" << y << ") = " << round(y);
    cout << "\t\t"
         << "round(" << z << ") = " << round(z) << endl;

    cout << "lround(" << x << ") = " << lround(x);
    cout << "\t\t"
         << "lround(" << y << ") = " << lround(y);
    cout << "\t\t"
         << "lround(" << z << ") = " << lround(z) << endl;

    cout << "llround(" << x << ") = " << llround(x);
    cout << "\t"
         << "llround(" << y << ") = " << llround(y);
    cout << "\t\t"
         << "llround(" << z << ") = " << llround(z) << endl
         << endl;

    /**** Negative Floating Number of decimal value less than 0.5 ****/
    x = -0.14, y = -0.002, z = -23.39;
    cout << "round(" << x << ") = " << round(x);
    cout << "\t"
         << "round(" << y << ") = " << round(y);
    cout << "\t\t"
         << "round(" << z << ") = " << round(z) << endl;

    cout << "lround(" << x << ") = " << lround(x);
    cout << "\t"
         << "lround(" << y << ") = " << lround(y);
    cout << "\t\t"
         << "lround(" << z << ") = " << lround(z) << endl;

    cout << "llround(" << x << ") = " << llround(x);
    cout << "\t"
         << "llround(" << y << ") = " << llround(y);
    cout << "\t\t"
         << "llround(" << z << ") = " << llround(z) << endl
         << endl;

    /**** Negative Floating Number of decimal value greater than 0.5 ****/
    x = -0.72, y = -21.864, z = -57.62;
    cout << "round(" << x << ") = " << round(x);
    cout << "\t"
         << "round(" << y << ") = " << round(y);
    cout << "\t"
         << "round(" << z << ") = " << round(z) << endl;

    cout << "lround(" << x << ") = " << lround(x);
    cout << "\t"
         << "lround(" << y << ") = " << lround(y);
    cout << "\t"
         << "lround(" << z << ") = " << lround(z) << endl;

    cout << "llround(" << x << ") = " << llround(x);
    cout << "\t"
         << "llround(" << y << ") = " << llround(y);
    cout << "\t"
         << "llround(" << z << ") = " << llround(z) << endl
         << endl;

    /**** Negative Floating Number of decimal value of 0.5 ****/
    x = -0.5, y = -6.50, z = -56.500;
    cout << "round(" << x << ") = " << round(x);
    cout << "\t"
         << "round(" << y << ") = " << round(y);
    cout << "\t\t"
         << "round(" << z << ") = " << round(z) << endl;

    cout << "lround(" << x << ") = " << lround(x);
    cout << "\t"
         << "lround(" << y << ") = " << lround(y);
    cout << "\t\t"
         << "lround(" << z << ") = " << lround(z) << endl;

    cout << "llround(" << x << ") = " << llround(x);
    cout << "\t"
         << "llround(" << y << ") = " << llround(y);
    cout << "\t\t"
         << "llround(" << z << ") = " << llround(z) << endl;
}

void testFloor() {
    float a = 1.2345;
    float m = -1.2345;
    std::cout << "positive 1: " << a << " floor " << floor(a) << std::endl;
    std::cout << "negative 1: " << m << " floor " << floor(m) << std::endl;
    std::cout << "chu fa: " << 5 / 2 << std::endl;  // 向下取整
}

void testCeil() {
    float a = 1.2345;
    float m = -1.2345;
    std::cout << "positive 1: " << a << " floor " << ceil(a) << std::endl;
    std::cout << "negative 1: " << m << " floor " << ceil(m) << std::endl;
}