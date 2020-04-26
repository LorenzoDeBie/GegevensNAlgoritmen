#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H

#include <string>

unsigned int worst_hash(const std::string &word)
{
    return 0;
}

unsigned int bad_hash(const std::string &word)
{
    return word.size();
}

unsigned int other_bad_hash(const std::string &word)
{
    unsigned int result = 0;

    for (const auto &c : word)
    {
        result += c;
    }

    return result;
}

unsigned int horner_hash(const std::string &word)
{
    unsigned int horner = 0;

    for (const auto &c : word)
    {
        horner = (horner * 256 + c);
    }

    return horner;
}

unsigned int good_hash(const std::string &word)
{
    unsigned int horner = 0;

    for (const char c : word)
    {
        horner = (horner * 131 + c);
    }

    return horner;
}

unsigned int djb2(const std::string &str)
{
    unsigned int hash = 5381;

    for(char c : str)
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

unsigned int sdbm(const std::string &str)
{
    unsigned int hash = 0;

    for(char c : str)
        hash = c + (hash << 6u) + (hash << 16u) - hash;

    return hash;
}

unsigned int lose_lose(const std::string &str)
{
    unsigned int hash = 0;

    for(char c : str)
        hash += c;

    return hash;
}

unsigned int stl_hash(const std::string &str) {
    return std::hash<std::string>{}(str);
}

unsigned int jenkins_one_at_a_time_hash(const std::string &str) {
    size_t i = 0;
    unsigned int hash = 0;

    while (i != str.length()) {
        hash += str[i++];
        hash += hash << 10u;
        hash ^= hash >> 6u;
    }
    hash += hash << 3u;
    hash ^= hash >> 11u;
    hash += hash << 15u;
    return hash;
}

#endif