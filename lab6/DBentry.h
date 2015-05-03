
#ifndef _DBENTRY_H
#define _DBENTRY_H

#include <string>
using namespace std;

class DBentry {
private:
	string name;
	unsigned int IPaddress;
        bool active;

public:
	// the default constructor
	DBentry();
        DBentry (string _name, unsigned int _IPaddress, bool _active);

	// the destructor
 	~DBentry();	

	// sets the domain name, which we will use as a key.
	void setName(string _name);

	// sets the IPaddress data.
	void setIPaddress(unsigned int _IPaddress);
    
        // sets whether or not this entry is active.
        void setActive (bool _active);

        // returns the name.
	string getName() const;

	// returns the IPaddress data.
	unsigned int getIPaddress() const;

        // returns whether or not this entry is active.
        bool getActive() const;

	// prints the entry in the format 
        // name : IPaddress : active  followed by newline
        // active is printed as a string (active or inactive)
        friend ostream& operator<< (ostream& out, const DBentry& rhs);
};

#endif	/* DBENTRY_H */

