// Zoe Dauphinee, rec 10, inheritance and polymorphism with instruments

#include <iostream>
#include <vector>
using namespace std;


class Instrument {
    public:
        Instrument() {}
        virtual void makeSound() const = 0;
        virtual const string getType() const { return "Instrument"; }
        virtual unsigned getInfo() const = 0;
        virtual void play() = 0;
    friend ostream& operator<<(ostream& os, const Instrument& instrument);
};

void Instrument::makeSound() const { cout << "To make a sound... "; }

class Brass : public Instrument {
    public:
        Brass(unsigned mouthpiece_size) : Instrument(), mouthpiece_size(mouthpiece_size) {}
        void makeSound() const {
            Instrument::makeSound();
            cout << "blow on a mouthpiece of size " << mouthpiece_size << endl;
        }
        const string getType() const { return "Brass"; }
        unsigned getInfo() const {
            return mouthpiece_size;
        }
    private:
        unsigned mouthpiece_size;
};

class String : public Instrument {
    public:
        String(unsigned pitch) : Instrument(), pitch(pitch) {}
        void makeSound() const {
            Instrument::makeSound();
            cout << "bow a string with pitch " << pitch << endl;
        }
        const string getType() const { return "String"; }
        unsigned getInfo() const {
            return pitch;
        }
    private:
        unsigned pitch;
};

class Percussion : public Instrument {
    public:
        Percussion() : Instrument() {}
        void makeSound() const {
            Instrument::makeSound();
            cout << "hit me!\n";
        }
        const string getType() const { return "Percussion"; }
        unsigned getInfo() const {
            return 0;
        }
};

class Trumpet : public Brass {
    public:
        Trumpet(unsigned mouthpiece_size) : Brass(mouthpiece_size) {}
        const string getType() const { return "Trumpet"; }
        void play() { cout << "Toot"; }
};

class Trombone : public Brass {
    public:
        Trombone(unsigned mouthpiece_size) : Brass(mouthpiece_size) {}
        const string getType() const { return "Trombone"; }
        void play() { cout << "Blat"; }
};

class Violin : public String {
    public:
        Violin(unsigned pitch) : String(pitch) {}
        const string getType() const { return "Violin"; }
        void play() { cout << "Screech"; }
};

class Cello : public String {
    public:
        Cello(unsigned pitch) : String(pitch) {}
        const string getType() const { return "Cello"; }
        void play() { cout << "Squawk"; }
};

class Drum : public Percussion {
    public:
        Drum() : Percussion() {}
        const string getType() const { return "Drum"; }
        void play() { cout << "Boom"; }
};

class Cymbal : public Percussion {
    public:
        Cymbal() : Percussion() {}
        const string getType() const { return "Cymbal"; }
        void play() { cout << "Crash"; }
};


class MILL {
    public:
        MILL() : inventory() {}

        void receiveInstr(Instrument& new_instrument) {
            Instrument* instrptr = &new_instrument;
            instrptr->makeSound();
            for (size_t index = 0; index < inventory.size(); ++index) {
                if (inventory[index] == nullptr) {
                    inventory[index] = instrptr;
                    return;
                }
            }
            inventory.push_back(instrptr);
        }

        Instrument* loanOut() {
            if (inventory.size() == 0) {
                return nullptr;
            }
            for (size_t index = 0; index < inventory.size(); ++index) {
                if (inventory[index]) {
                    Instrument* instrument = inventory[index];
                    inventory[index] = nullptr;
                    return instrument;
                }
            }
            cout << "FLAG";
            return nullptr;
        }

        void dailyTestPlay() {
            for (size_t index = 0; index < inventory.size(); ++index) {
                if (inventory[index]) {
                    inventory[index]->makeSound();
                }
            }
        }

    private:
        vector<Instrument*> inventory;

    friend ostream& operator<<(ostream& os, const MILL& instrument_library);
};


class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }

private:
    Instrument* instr;
    string name;
};


class Orchestra {
    public: 
        Orchestra() : members() {}

        void addPlayer(Musician& new_member) {
            Musician* musicianptr = &new_member;
            members.push_back(musicianptr);
        }

        void play() {
            for (size_t index = 0; index < members.size(); ++index) {
                members[index]->play();
            }
            cout << endl;
        }

    private:
        vector<Musician*> members;
};


int main() {
    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);
  
    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    groucho.testPlay();	
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
       mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orchestra orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;
}



ostream& operator<<(ostream& os, const MILL& instrument_library) {
    os << "The MILL has the following instruments:";
    if (instrument_library.inventory.size() == 0) {
        os << " None";
    }
    int empty_spots = 0;
    for (size_t index = 0; index < instrument_library.inventory.size(); ++index) {
        if (instrument_library.inventory[index]) {
            os << endl << *instrument_library.inventory[index];
        }
        else { empty_spots += 1; }
    }
    if (empty_spots == instrument_library.inventory.size()) {
        os << " None";
    }
    return os;
}

ostream& operator<<(ostream& os, const Instrument& instrument) {
    os << "    " << instrument.getType();
    if (instrument.getInfo() != 0) {
        os << ": " << instrument.getInfo();
    }
    return os;
}