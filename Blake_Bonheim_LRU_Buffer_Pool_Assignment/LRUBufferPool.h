//
//Blake Bonheim 3/31/21
//

#ifndef LRUBUFFERPOOL_H
#define LRUBUFFERPOOL_H

#include <iostream>
#include <fstream>
#include <string>
#include "BufferPoolADT.h"
#include "BufferBlock.h"
#include <vector>

using namespace std;



class LRUBufferPool : BufferPoolADT
{
private:
    int poolSize;
    int blockSize;
    char* buffer;

    int LRU[5]; //keeps track of least recently used
    int ID[5]; // keeps track of IDs


    vector<BufferBlock> buffers;

public:

    LRUBufferPool(string filename, int poolSizeInt, int blockSizeInt)
    {
        poolSize = poolSizeInt;
        blockSize = blockSizeInt;


        fstream input;
        input.open(filename.c_str(), fstream::in | fstream::binary);


        input.seekg(0, input.end);
        int length = input.tellg(); //determine length of file      http://www.cplusplus.com/reference/istream/istream/seekg/
        input.seekg(0, input.beg);

        buffer = new char[length];

        input.read(buffer, length);

        for (int i = 0; i < poolSizeInt; i++)
        {

            BufferBlock x(buffer, blockSize);
            x.setBlock(buffer + (blockSize * i));

            x.setID(i);

            //we know in this constructor that the blocks will be in LRU order during creation
            LRU[i] = i;
            ID[i] = i;
            buffers.push_back(x);
        }
        input.close();
    }

    void getBytes(char* space, int sz, int pos)
    {
        //search for preexisting block with desired pos
        int count = 0;
        bool blockFound = false;

        int searchCount = 0;
        while (searchCount < poolSize)
        {
            if (ID[searchCount] == (pos / blockSize))
            {
                blockFound = true;
            }
            searchCount++;
        }


        if (blockFound == true) //if a block of the desired ID already exists
        {
            buffers[pos / blockSize].getData(pos, sz, space); //writes desired bytes to char*

            //updates LRU
            int recentlyUsed = LRU[pos / blockSize];
            LRU[pos / blockSize] = -1;

            for (int i = 0; i < poolSize; i++)
            {
                if (LRU[i] < recentlyUsed)
                {
                    LRU[i] = LRU[i] + 1; //increase LRU value because it is being bumped up
                }
            }
        }
        else if (blockFound == false) //create a new block if one of the same ID is not found
        {
            BufferBlock x(buffer, blockSize);
            x.setBlock(buffer + (blockSize * (pos/blockSize)));

            x.setID(pos/blockSize);

            int count = 0;
            while (buffers[count].getID() != getLRUBlockID()) //search for least recently used
            {
                count++;
            }
            buffers.erase(buffers.begin() + count); //remove Least recently used
            buffers.push_back(x);

            //update ID array
            ID[count] = pos / blockSize; 

            //updates LRU
            int recentlyUsed = LRU[count];
            LRU[count] = -1;

            for (int i = 0; i < poolSize; i++)
            {
                if (LRU[i] < recentlyUsed)
                {
                    LRU[i] = LRU[i] + 1; //increase LRU value because it is being bumped up
                }
            }
            buffers[poolSize - 1].getData(pos, sz, space); //writes desired bytes to char*
        }
    }


    void printBufferBlockOrder() //print the block IDs in least recently used order
    {
        cout << "My buffer block order from most recently used to LRU is: " << endl;
        for (int searchInt = 0; searchInt < poolSize; searchInt++) //iterate through 0 - 4
        {
            int count = 0;
            while (LRU[count] != searchInt)
            {
                    count++;
            }
            cout << ID[count] << ", ";
        }
        cout << endl;
    }

    int getLRUBlockID() //return the least recently used block ID
    {
        int count = 0;
        while (LRU[count] != (poolSize - 1))
        {
            count++;
        }

        return ID[count];
    }
};


#endif