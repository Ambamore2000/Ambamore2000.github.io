//////////////////////////////////////////////////
/// Group Members: Andrew Kim, Ethan Rodriguez ///
//////////////////////////////////////////////////
#include <iostream>

using namespace std;

class State {
public:

    State();

    void printSize() const;

    void setName(string name) {
        this->name = name;
    }
    void setPopulation(int population) {
        this->population = population;
    }

    string getName() const {
        return name;
    }
    int getPopulation() const {
        return population;
    }

private:

    string name;            // Name of State.
    int population;         // Population size of State.

    string size() const;
};

State::State() {
    setName("N/A");
    setPopulation(0);
}

string State::size() const {
    if (getPopulation() < 1000000) {
        return "small";
    } else if (getPopulation() > 1000000 && getPopulation() < 5000000) {
        return "medium";
    } else if (getPopulation() > 5000000) {
        return "large";
    }
}

void State::printSize() const {
    cout << getName() << ": " << size() << endl;
}

int main() {

    State state1;

    state1.printSize();

    state1.setName("California");
    state1.setPopulation(40000000);

    state1.printSize();
    return 0;
}
