/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include <cmath>
#include "testing/SimpleTest.h"
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to int sqrt(n), testing for a
 * zero remainder from the division.
 */
long smarterSum(long n) {
    long total = 0;
    long square_root = sqrt(n);
    for (long divisor = 1; divisor <= square_root; divisor++) {
        if (n % divisor == 0) {
            total += divisor + n / divisor;
        }
    }
    total -= n;
    if (n == square_root*square_root) {
        total -= square_root;
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function calculates the Nth perfect number based on the Euclid???Euler theorem.
 */
//long findNthPerfectEuclid(long n) {
//    long num = 0;
//    long m, k;
//    for (k = 1; k > 0; k++) {
//        m = pow(2,k) - 1;
//        if (smarterSum(m) == 1) num += 1;
//        if (num == n) break;
//    }
//    return pow(2,k-1) * (pow(2,k)-1);
//}

// This function is intended to determine whether it is a prime
bool isPrime(long m) {
    return (smarterSum(m) == 1);
}

// the above implementation is not good because k value will overflow
// so here we refine it by using while loop
long findNthPerfectEuclid(long n) {
    long num = 0;
    long k = 1;
    while (true) {
        long m = pow(2,k) - 1;
        if (isPrime(m)) num += 1; // define a bool function, see above
        if (num == n) break;
        k++;
    }

    return pow(2,k-1) * (pow(2,k)-1);
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

// TODO: add your student test cases here


//STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
//    TIME_OPERATION(35000, findPerfects(35000));
//    TIME_OPERATION(70000, findPerfects(70000));
//    TIME_OPERATION(140000, findPerfects(140000));
//    TIME_OPERATION(280000, findPerfects(280000));
//}


STUDENT_TEST("negative value for isPerfect") {
    EXPECT(!isPerfect(-3));
}

STUDENT_TEST("Confirm smarterSum of small inputs") {
    EXPECT_EQUAL(smarterSum(1), 0);
    EXPECT_EQUAL(smarterSum(12), 16);
    EXPECT_EQUAL(smarterSum(25), 6);
}

STUDENT_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfectSmarter(33550336));
}

//STUDENT_TEST("Time trials of find PerfectsSmarter on doubling input sizes") {
//    TIME_OPERATION(1875000, findPerfectsSmarter(1875000));
//    TIME_OPERATION(3750000, findPerfectsSmarter(3750000));
//    TIME_OPERATION(7500000, findPerfectsSmarter(7500000));
//    TIME_OPERATION(15000000, findPerfectsSmarter(15000000));
//}


STUDENT_TEST("Confirm findNthPerfectEuclid") {
    EXPECT_EQUAL(findNthPerfectEuclid(2),28);
    EXPECT(isPerfect(findNthPerfectEuclid(3))); // we should use EXPECT_EQUAL, which is more accurate
    EXPECT_EQUAL(findNthPerfectEuclid(4),8128);
    EXPECT(isPerfect(findNthPerfectEuclid(5)));
}
