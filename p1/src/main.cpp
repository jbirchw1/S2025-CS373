#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <unordered_map>

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

std::unordered_map<int, State> states;
State start_state;
//                  p                       x                 q 
std::unordered_map<int, std::unordered_map<char, std::vector<int>>> transitions;
// e.g., transitions[4]['a'] => {6, 7, 8, ...}

void initialize_states() {
    for(int i = 0; i < 1002; i++) {
        states[i].num = i;
    }
}

// for office use only
void print_states(int index) {
    std::cout << "Start state is " << start_state.num << std::endl;
    for(int i = 0; i <= index; i++) {
        std::cout << "State " << states[i].num << " is " << ((states[i].is_accept) ? "" : "not ") << "an accept state" << std::endl;
    }
}

void print_transitions() {
    for (const auto& [state, symbol_map] : transitions) {
        for (const auto& [symbol, next_states] : symbol_map) {
            std::cout << "Transition: " << state << " --(" << symbol << ")--> {";
            
            for (size_t i = 0; i < next_states.size(); i++) {
                std::cout << next_states[i];
                if (i < next_states.size() - 1) std::cout << ", ";
            }
            
            std::cout << "}" << std::endl;
        }
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
        if(tokens.at(0).compare("state") == 0) { // state input
            if(tokens.size() > 3) {
              if((tokens.at(2).find("accept") != std::string::npos) || (tokens.at(3).find("accept") != std::string::npos)) {
                states[std::stoi(tokens.at(1))].is_accept = true;
            }
            if((tokens.at(2).find("start") != std::string::npos) || (tokens.at(3).find("start") != std::string::npos)) {
                start_state = states[std::stoi(tokens.at(1))];
            }  
            }
            else {
                if(tokens.at(2).find("accept") != std::string::npos) {
                    states[std::stoi(tokens.at(1))].is_accept = true;
                }
                if(tokens.at(2).find("start") != std::string::npos) {
                    start_state = states[std::stoi(tokens.at(1))];
                }
            }
            
        }
        if(tokens.at(0).compare("transition") == 0) { // transition input
            // ! NOTE: tokens.at(2).at(0) may only work if there is a char there to begin with
            transitions[std::stoi(tokens.at(1))][tokens.at(2).at(0)].push_back(std::stoi(tokens.at(3)));
        }
        tokens.clear();
    }
}

int main(int argc, char *argv[]) {
    initialize_states();
    parse(argv[1]);
    print_states(7);
    print_transitions();
    return 0;
}