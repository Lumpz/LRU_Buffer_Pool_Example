/*
 * File:   BufferBlock.hpp
 * Author: Professor Terri Sipantzi
 *
 * Created on August 25, 2012, 8:49 AM
 */
 //Blake Bonheim 3/31/21
#ifndef BUFFERBLOCKADT_H
#define    BUFFERBLOCKADT_H

#include <iostream>
#include <string>

using namespace std;

class BufferBlockADT {
private:
    //Instance variables:
    //    int blockID;
    //    char block;

public:

    //sz is the size of the character array data
    //points to.
    BufferBlockADT() {}
    BufferBlockADT(char* data, int sz = 4096) {}
    virtual ~BufferBlockADT() {}

    //read the block from pos to pos + sz-1 (or to the end of the block)
    virtual void getData(int pos, int sz, char* data) = 0;

    //setID
    virtual void setID(int id) = 0;

    //getID
    virtual int getID() const = 0;

    //getBlocksize
    virtual int getBlocksize() const = 0;

    //return the block
    virtual char* getBlock() const = 0;

    //set the block
    virtual void setBlock(char* blk) = 0;
};


#endif    /* BUFFERBLOCKADT_H */