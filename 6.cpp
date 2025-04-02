#include <iostream>
#include <string>

using namespace std;

class RecursiveDescentParser {
public:
    RecursiveDescentParser(const string& input) : input_string(input), index(0) {}

    string parse() {
        if (parse_S()) {
            if (index == input_string.size()) {
                return "Valid string";  
            }
        }
        return "Invalid string"; 
    }

private:
    string input_string;  
    size_t index;         

    bool parse_S() {
        if (index < input_string.size()) {
            if (input_string[index] == 'a') {
              
                index++;
                return true;
            }
            else if (input_string[index] == '(') {
               
                index++;
                if (parse_L()) {
                    if (index < input_string.size() && input_string[index] == ')') {
                        
                        index++;
                        return true;
                    }
                }
            }
        }
        return false; 
    }

    bool parse_L() {
        if (!parse_S()) return false; 
        return parse_L_prime();         
    }

   
    bool parse_L_prime() {
        if (index < input_string.size() && input_string[index] == ',') {
            
            index++;
            if (!parse_S()) return false;
            return parse_L_prime();
        }
   
        return true;
    }
};

int main() {
    string input_string;
    while (true) {
        cout << "Enter the string to be validated (-1 to terminate): ";
        getline(cin, input_string);       
        if (input_string == "-1") {
            break;
        }
        RecursiveDescentParser parser(input_string);      
        cout << parser.parse() << endl;
    }
    cout << "Program terminated." << endl;
    return 0;
}
