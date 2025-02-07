#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>

// Custom State class
class State{
    public:
        State() { // default constructor (required for making an array)
            num = 0;
            is_accept = false;
        }
        State(int x) { // constructor with number
            num = x;
        }
        int num;
        bool is_accept;
};

State states[1001];
int start_state;

void initialize_states() {
    for(int i = 0; i < 1002; i++) {
        states[i].num = i;
    }
}

void print_states(int index) {
    for(int i = 0; i <= index; i++) {
        std::cout << "State " << states[i].num << " is " << ((states[i].is_accept) ? "" : "not ") << "an accept state" << std::endl;
    }
}

void parse(char* filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> tokens;

    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        while(std::getline(iss, token, '\t'))
            tokens.push_back(token);
        // update state in array of states with this information
        if(tokens.at(0).compare("state") == 0) {
            if(tokens.at(2).find("accept") != std::string::npos) {
                states[std::stoi(tokens.at(1))].is_accept = true;
            }
            if(tokens.at(2).find("start") != std::string::npos) {
                start_state = std::stoi(tokens.at(1));
            }
        }
        tokens.clear();
    }
}

int main(int argc, char *argv[]) {
    initialize_states();
    parse(argv[1]);
    print_states(7);
    return 0;
}