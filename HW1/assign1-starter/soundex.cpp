/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */

string removeNonLetters(string s) {
    string result("");
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}


/* This function is intended to encode the letter characters
 * to corresponding numbers.
 */
string encodeLetters(string s) {
    string s_upper = toUpperCase(s);
    vector<string> Soundex_str({"AEIOUHWY","BFPV","CGJKQSXZ","DT","L","MN","R"});
    string Numbers("");
    for (int i = 0; i < s.length(); i++) {
        for (size_t j = 0; j < Soundex_str.size(); j++) {
            if (Soundex_str[j].find(s_upper[i]) != string::npos) {
                Numbers += integerToString(j);
            }
        }
    }
    return Numbers;
}

/* This function is intended to merge the adjacent numbers with the same values.
 */
string mergeNumbers(string s) {
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != result.back()) {
            result += s[i];
        }
    }
    return result;
}

/* This function is intended to remove all zeros in the string.
 */
string removeZero(string s) {
    string result("");
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '0') {
            result += s[i];
        }
    }
    return result;
}

/* This function is intended to pad zero or remove redundant part
 * to make the length of encoded string equal to four.
 */
string fixLength(string s) {
    string result;
    if (s.length() > 4) {
        result = s.substr(0,4);
    } else if (s.length() < 4) {
        string padding(4-s.length(),'0');
        result += s + padding;
    } else {
        result = s;
    }
    return result;
}


/* This function is intended to generate Soundex coding.
 */
string soundex(string s) {
    string removeNonLetters_result = removeNonLetters(s);
    string encodeLetters_result = encodeLetters(removeNonLetters_result);
    string mergeNumbers_result = mergeNumbers(encodeLetters_result);
    mergeNumbers_result[0] = removeNonLetters_result[0];
    mergeNumbers_result = toUpperCase(mergeNumbers_result);
    string removeZero_result = removeZero(mergeNumbers_result);
    string result = fixLength(removeZero_result);

    return result;
}




/* This function is intended to search the names with the same encoding in
 * the database.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;
    cout << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames
    while (true) {
        string surname = getLine("Enter a surname (RETURN to quit): ");
        if (surname.empty()) break;
        string surnameEncoding = soundex(surname);
        cout << "Soundex code is " << surnameEncoding << endl;

        vector<string> matchNames;

        for (size_t i = 0; i < databaseNames.size(); ++i) {
            if (surnameEncoding == soundex(databaseNames[i])) {
                matchNames.push_back(databaseNames[i]);
            }
        }

        // sort the vector and print out the matched names
        sort(matchNames.begin(), matchNames.end());
        cout << "Matches from database: {";
        for (size_t i = 0; i < matchNames.size(); i++) {
                if (i != 0) {
                    cout << ", ";
                }
                cout << '"' << matchNames[i] << '"';
            }
        cout << "}" << endl;
        cout << endl;
    }
    cout << "All done!" << endl;
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here
STUDENT_TEST("Test removing puntuation, digits, and spaces") {
    string s = "3meier";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "meier");
}

STUDENT_TEST("Test encodeLetters") {
    string s = "zhou";
    string number = encodeLetters(s);
    EXPECT_EQUAL(number, "2000");
    s = "Angelou";
    number = encodeLetters(s);
    EXPECT_EQUAL(number, "0520400");
}

STUDENT_TEST("Test mergeNumbers") {
    string s = "200001";
    string number = mergeNumbers(s);
    EXPECT_EQUAL(number, "201");
    s = "2133344";
    number = mergeNumbers(s);
    EXPECT_EQUAL(number, "2134");
}

STUDENT_TEST("Test removeZero") {
    string s = "200001";
    string number = removeZero(s);
    EXPECT_EQUAL(number, "21");
    s = "A103440";
    number = removeZero(s);
    EXPECT_EQUAL(number, "A1344");
}

STUDENT_TEST("Test fixLength") {
    string s = "A12";
    string number = fixLength(s);
    EXPECT_EQUAL(number, "A120");
    s = "A123";
    number = fixLength(s);
    EXPECT_EQUAL(number, "A123");
    s = "A123456";
    number = fixLength(s);
    EXPECT_EQUAL(number, "A123");
}

STUDENT_TEST("Test soundex") {
    string s = "Curie";
    string result = soundex(s);
    EXPECT_EQUAL(result, "C600");
    s = "O'Conner";
    result = soundex(s);
    EXPECT_EQUAL(result, "O256");
    s = "Angelou";
    result = soundex(s);
    EXPECT_EQUAL(result, "A524");
    s = "Zhou";
    result = soundex(s);
    EXPECT_EQUAL(result, "Z000");
}

