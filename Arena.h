#ifndef ARENA_H
#define ARENA_H

/*
Arena size can be specified but the standard arena is 9 long x 6 wide (including home row)
Default constructor creates 9x6 arena. Custom constructor takes in rows x columns.
Maximum size set as 27 long x 12 wide.
*/

class Arena {
public:
    //Default constructor creates 9x6 arena

    //Custom constructor creates specified arena
private:
    int length; //Rows
    int width;  //Columns
};

#endif
