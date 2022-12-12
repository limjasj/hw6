#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int num_k[k.size()];
        for(unsigned int i=0; i<k.size(); i++) //go through string k, change to numbers
        {
            if(k[i]>='A' && k[i]<='Z')
            {
                num_k[i]=letterDigitToNumber(k[i]+32);
            }
            else
            {
                num_k[i]=letterDigitToNumber(k[i]);
            }
        }

        int size_k= k.size();

        unsigned long long w[5]={0,0,0,0,0};
        for(int i=0; i<5; i++)
        {   
            w[4-i]=0;
            for(int j=0; j<6; j++)
            {
                if(size_k-(j+(6*i))-1 >=0)
                {
                    w[4-i] += pow(36,j) * num_k[size_k-(j+(6*i))-1];
                }
                else
                {
                    w[4-i] += 0;
                }
            }
        }

        HASH_INDEX_T hashValue=0;
        for(int i=0; i<5; i++)
        {
            hashValue+=(rValues[i] * w[i]);
        }

        return hashValue;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T number;
        if(letter>='a' && letter<='z')
        {
            number=int(letter)-97;
        }
        else if (letter>='0' && letter<='9')
        {
            number=int(letter)-22;
        }
        return number;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
