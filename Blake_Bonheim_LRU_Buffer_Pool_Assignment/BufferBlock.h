//
//Blake Bonheim 3/31/21
//
#ifndef BUFFERBLOCK_H
#define BUFFERBLOCK_H

#include <iostream>
#include <string>
#include "BufferBlockADT.h"

using namespace std;

class BufferBlock : BufferBlockADT
{
private:
    int blockID;
    char* block;
    int size;

public:
    BufferBlock(char* data, int sz) //create buffer block and point it to the data and define its size
    {
        block = data;
        size = sz;
    }

    ~BufferBlock() {}
    void BufferBlockADT::getData(int pos, int sz, char* data)
    {
        int dataCount = 0;
        //   v Grab desired amount        v current grabing pos    v end of block pos
        while (dataCount < sz      &&   (pos + dataCount) < (size + (size * blockID)))
        {
            data[dataCount] = block[pos - (size * blockID)+ dataCount];              //write the desired position and length of data to data*      
            dataCount++;
        }

    }


    void setID(int id) //set block id
    {
        blockID = id;
    }

    int getID() const //return block id
    {
        return blockID;
    }

    int getBlocksize() const //return block size
    {
        return size;
    }

    char* getBlock() const //return block pointer
    {
        return block;
    }

    void setBlock(char* blk) //change the block pointer
    {
        block = blk;
    }

};


#endif
