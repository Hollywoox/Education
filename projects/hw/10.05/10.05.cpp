////////////////////////////////////////////////////////

// chapter : Data Structures

////////////////////////////////////////////////////////

// section : Hashing Containers

////////////////////////////////////////////////////////

// content : Biassociative Containers
//
// content : Library Boost.Bimap

////////////////////////////////////////////////////////

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <random>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

////////////////////////////////////////////////////////

namespace
{

constexpr std::size_t StringLength = 10;
constexpr std::size_t MinStrings   = 1000;
constexpr std::size_t MaxStrings   = 1000000;
constexpr std::size_t StepCount    = 20;

////////////////////////////////////////////////////////


unsigned int RSHash(const char* str, unsigned int length)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}


unsigned int JSHash(const char* str, unsigned int length)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}


unsigned int PJWHash(const char* str, unsigned int length)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          =
                      (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash = 0;
   unsigned int test = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << OneEighth) + (*str);

      if ((test = hash & HighBits) != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}


unsigned int ELFHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << 4) + (*str);

      if ((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }

      hash &= ~x;
   }

   return hash;
}


unsigned int BKDRHash(const char* str, unsigned int length)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}


unsigned int SDBMHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}


unsigned int DJBHash(const char* str, unsigned int length)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}


unsigned int DEKHash(const char* str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
       hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }
 
    return hash;
 }


unsigned int APHash(const char* str, unsigned int length)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}


using HashFunction = unsigned int (*)(char const *, unsigned int);

struct HashInfo
{
    char const *    name;
    HashFunction    func;
};

HashInfo const HashFunctions[] = {
    {"RSHash",  RSHash },
    {"JSHash",  JSHash },
    {"PJWHash", PJWHash},
    {"ELFHash", ELFHash},
    {"BKDRHash", BKDRHash},
    {"SDBMHash", SDBMHash},
    {"DJBHash", DJBHash},
    {"DEKHash", DEKHash},
    {"APHash",  APHash },
};

constexpr std::size_t HashFunctionCount =
    sizeof(HashFunctions) / sizeof(HashFunctions[0]);


std::vector<std::string> make_strings(std::size_t count)
{
    std::set<std::string> unique;
    std::string buffer(StringLength, '_');
    std::mt19937 engine(42);
    std::uniform_int_distribution<int> dist(97, 122);

    while (unique.size() < count)
    {
        for (char & ch : buffer)
        {
            ch = static_cast<char>(dist(engine));
        }
        unique.insert(buffer);
    }

    return std::vector<std::string>(unique.begin(), unique.end());
}


std::size_t count_collisions(HashFunction func, const std::vector<std::string> & strings)
{
    std::unordered_set<unsigned int> hashes;
    std::size_t collisions = 0;

    for (const std::string & s : strings)
    {
        unsigned int const h = func(s.data(), static_cast<unsigned int>(s.size()));
        if (!hashes.insert(h).second)
        {
            ++collisions;
        }
    }

    return collisions;
}

void run_analysis(std::size_t hash_index, std::ostream & csv_out)
{
    HashInfo const & info = HashFunctions[hash_index];


    std::cout << "\n   " << info.name << "\n";
    
    csv_out << "N,collisions\n";

    for (std::size_t step = 0; step <= StepCount; ++step)
    {
        std::size_t const n = MinStrings + (MaxStrings - MinStrings) * step / StepCount;

        std::vector<std::string> strings = make_strings(n);
        std::size_t const collisions = count_collisions(info.func, strings);

        std::cout << "  N = " << std::setw(5) << n << "  collisions = " << collisions << '\n';
        csv_out << n << ',' << collisions << '\n';
    }
}


void generate_data()
{
    std::cout << "\n  Generating collision data for given functionsn \n";

    for (std::size_t i = 0; i < HashFunctionCount; ++i)
    {
        std::string const fname =
            std::string("10.05_") + HashFunctions[i].name + ".csv";
        std::ofstream csv(fname);
        run_analysis(i, csv);
        std::cout << "  " << HashFunctions[i].name << " -> " << fname << '\n';
    }
}

} // namespace


int main()
{
    generate_data();
}

