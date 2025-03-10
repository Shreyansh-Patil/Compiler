#include <iostream>
#include <string>

// will be used to categorize a given string literal
// into tokens
enum {
    // token returned when lexer reachers End Of File (EOF)
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
    tok_datatype = -6
};

// Each token returned by the lexer will either be one of the enum values
// or it will be between [0-255] (ASCII) for a unknown character

// If the current token is an identifier, store it in global variable
static std::string IdentifierStr;

// If the current token is a number, store it in global variable
static double NumVal;

// To generate a token, gettok function will be called

static int gettok() {
    // first we need to skip any white spaces

    // for example, consider the following inputs:
    // "  hello" -> 2 spaces then string 'hello'

    // thus, we first skip whitespaces, \n, \t, etc
    static int lastChar = ' ';
    while (isspace(lastChar)) {
        lastChar = getchar();
    }

    // getchar() function keeps eating input characters
    // isspace() function return true if character is ' ',  '\n', etc.

    // first check if it is number or alhpanumeric character (not alphanumeric number)
    if (isdigit(lastChar) || lastChar == '.') {
        NumVal = 0; // reset old constant's value
        std::string numberString = "";
        int countDecimal = 0;
        while (isdigit(lastChar) || lastChar == '.') {
            if (lastChar == '.') {
                countDecimal += 1;
                if (countDecimal >= 2) { std::cout << "Not a number\n"; return tok_eof; }
            }
            numberString += lastChar;
            lastChar = getchar();
        }

        // check if user inputs just a single dot
        if (numberString == ".") { std::cout << "Not a number twice\n"; return tok_eof; }

        NumVal = strtod(numberString.c_str(), 0);

        return tok_number;
    }

    // now to build the string (if identifier)
    if (isalnum(lastChar) || lastChar == '_') {
        // isalnum returns TRUE if character is A-Z, or a-z, or 0-9
        IdentifierStr = lastChar; // reset IdentifierStr from previous lexing

        // build new IdentifierStr
        lastChar = getchar(); // get next character because the first character is assigned earlier
        while (isalnum(lastChar) || lastChar == '_') {
            IdentifierStr += lastChar;
            lastChar = getchar(); // get next character
        }

        // std::cout << IdentifierStr << '\n';

        if (IdentifierStr == "def") return tok_def;
        else if (IdentifierStr == "extern") return tok_extern;
        else if (IdentifierStr == "int" || IdentifierStr == "string" || IdentifierStr == "bool") return tok_datatype;
        return tok_identifier;
    }

    return tok_eof;
}

int main() {

    std::string input = "  Test";

    while (true) {
        int tok = gettok();

        if (tok == tok_def) std::cout << "Function definition\n";
        else if (tok == tok_extern) std::cout << "Extern thingy\n";
        else if (tok == tok_identifier) std::cout << "Identifier\n";
        else if (tok == tok_number) std::cout << "Number\n";
        else if (tok == tok_datatype) std::cout << "Data Type\n";
        else std::cout << "EOF\n";

        if (tok == tok_eof) break;
    }

    return 0;
}
