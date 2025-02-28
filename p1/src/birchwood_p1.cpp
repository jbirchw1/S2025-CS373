#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <unordered_set>

bool accept_states[1001];
int start_state;
std::unordered_map<int, std::unordered_map<char, std::vector<int>>> transitions;
//                  p                       x                 q 
// e.g., transitions[4]['a'] => {6, 7, 8, ...}

/**
 * Reads states and transitions from stdin
 */
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
            if(tokens.size() > 3) { // if there is a "state accept" separated by a tab
              if((tokens.at(2).find("accept") != std::string::npos) || (tokens.at(3).find("accept") != std::string::npos)) {
                accept_states[std::stoi(tokens.at(1))] = true;
            }
            if((tokens.at(2).find("start") != std::string::npos) || (tokens.at(3).find("start") != std::string::npos)) {
                start_state = std::stoi(tokens.at(1));
            }  
            }
            else { // if there is only "accept", "start", or "acceptstart"
                   // note that .find() allows it to work in any case
                if(tokens.at(2).find("accept") != std::string::npos) {
                    accept_states[std::stoi(tokens.at(1))] = true;
                }
                if(tokens.at(2).find("start") != std::string::npos) {
                    start_state = std::stoi(tokens.at(1));
                }
            }
            
        }
        if(tokens.at(0).compare("transition") == 0) { // transition input
            //! NOTE: tokens.at(2).at(0) may only work if there is a char there to begin with
            transitions[std::stoi(tokens.at(1))][tokens.at(2).at(0)].push_back(std::stoi(tokens.at(3)));
        }
        tokens.clear();
    }
}

/**
 * Helper function to remove duplicate states from list of states after each transition
 */
void condense(std::vector<int>& vec) {
    std::unordered_set<int> seen;
    std::vector<int> result;

    for (int num : vec) {
        if (seen.insert(num).second) { // Insert returns {iterator, bool}, bool is true if inserted
            result.push_back(num);
        }
    }

    vec = std::move(result); // Replace the original vector with the condensed one
}

/**
 * Adds each accessible state given an input character for the
 * list of currently available states 
 */
std::vector<int> transition(std::vector<int> current_states, char symbol) {
    std::vector<int> next_states;

    while(!current_states.empty()) {
        int curr = current_states.back();
        current_states.pop_back();

        auto stateIt = transitions.find(curr);
        if (stateIt != transitions.end()) {
            auto symbolIt = stateIt->second.find(symbol);
            if (symbolIt != stateIt->second.end()) {
                const std::vector<int>& nextStates = symbolIt->second;
                for (int s : nextStates) {
                    next_states.push_back(s); // add reachable states to vector
                }
            }
            // else doNothing()
        }
    }
    return next_states;
}

/**
 * Wrapper function that calculates all transitions for a 
 * given input string beginning at the start state
 */
std::vector<int> begin_automata(char* input) {
    int size_of_input = std::strlen(input);

    std::vector<int> accessible_states;
    accessible_states.push_back(start_state);

    for(int i = 0; i < size_of_input; i++) {
        accessible_states = transition(accessible_states, input[i]);
        condense(accessible_states);
    }

    return accessible_states;
}
/**
 * Prints required output and list of states
 */
void print_end_status(std::vector<int> end_states) {
    bool accept = false;
    for(int state : end_states) {
        if(accept_states[state]) {
            accept = true;
        }
    }

    if(accept) { // print all accept states
        std::cout << "accept ";
        for(int state : end_states) {
            if(accept_states[state]) {
                std::cout << state << " ";
            }
        }
    } else { // print all accessible states
        std::cout << "reject ";
        for(int state : end_states) {
            std::cout << state << " ";
        }
    }
    
    std::cout << std::endl;
}

// Driver
int main(int argc, char *argv[]) {
    if(argc < 3) {
        std::cout << "Please provide the required command line input." << std::endl;
        return 1;
    }
    
    // get states + transition
    parse(argv[1]);

    // run the automata
    std::vector<int> accessible_states = begin_automata(argv[2]);

    // print accept/reject
    print_end_status(accessible_states);

    return 0;
}