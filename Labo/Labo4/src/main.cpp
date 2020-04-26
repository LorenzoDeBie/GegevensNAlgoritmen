#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <chrono>
#include <random>
#include <algorithm>
#include <string>
#include <iomanip>

#include "hashfunctions.h"

template <class T>
struct pointer_compare {
    bool operator() (T const * const t1, T const * const t2) const {
        return *t1 < *t2;
    }
};

/*
Reads all the files in "folder". Assumes that they are named 0.py, 1.py, ...
Returns a vector with for each file a set of of tokens in that file. 
Tokens are unique words or bigrams (two sequential words).
*/
std::vector<std::set<std::string>> readDatafiles(const char *folder)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::set<std::string>> contents;

    int i = 0;
    std::ifstream in(folder + std::to_string(i) + ".py");

    while (in)
    {
        std::string word;
        std::string previous = "";
        contents.push_back(std::set<std::string>());

        while (in)
        {
            in >> word;
            contents[i].insert(word);

            previous = previous + " " + word;
            contents[i].insert(previous);

            previous = word;
        }

        i++;
        in = std::ifstream(folder + std::to_string(i) + ".py");
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Reading the data files took " << duration.count() << " ms" << std::endl;

    return contents;
}

// Replaces each unique word with a unique id (0, 1, 2, ...)
std::vector<std::set<int>> replaceWithUniqueId(const std::vector<std::set<std::string>> &input, int &maxId)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::set<int>> contents(input.size());

    //we need a custom comparer to work with a map
    //auto comparer = [](const std::string * const s1, const std::string * const s2) { return *s1 < *s2 ;};
    //this map keeps the links between the unique strings and their number
    //to prevent copying the strings we keep a pointer to them
    std::map<const std::string * const, int, pointer_compare<std::string>> links;

    int counter = 0;
    //all strings in first set will be unique (property of a set), so we don't have to check these
    for(const std::string& word : input[0]) {
        links.insert(std::make_pair(&word, counter));
        contents[0].insert(counter++);
    }

    for(int fileN = 1; fileN < input.size(); fileN++) {
        for(const std::string& word : input[fileN]) {
            auto iterator = links.find(&word);
            //if we don't have a number for this word yet
            //this uses the custom comparer we declared earlier
            if(iterator == links.end()) {
                links.insert(std::make_pair(&word, counter));
                //look in all sets with index smaller than fileN if word
                contents[fileN].insert(counter++);
            }
            else {
                contents[fileN].insert(iterator->second);
            }
        }
    }
    maxId = counter - 1;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Replacing words with IDs took " << duration.count() << " ms" << std::endl;
    return contents;
}

// Replaces each word with its hash code
template <unsigned int (*hashfunction)(const std::string &)>
std::vector<std::set<int>> replaceWithHash(const std::vector<std::set<std::string>> &input, int &maxHash)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::set<int>> contents(input.size());

    maxHash = 0;

    //this function does not check for collisions!
    //loop over all words in all sets
    for(int fileN = 0; fileN < input.size(); fileN++) {
        for(const std::string& word : input[fileN]) {
            int hash = hashfunction(word);
            // add the hash to the corresponding set in contents
            contents[fileN].insert(hash);
            if(hash > maxHash) maxHash = hash;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Replacing words with hash values took " << duration.count() << " ms" << std::endl;
    return contents;
}

template <unsigned int (*hashfunction)(const std::string &)>
void findCollisions(const std::vector<std::set<std::string>> &input)
{
    //this map keeps the links between the hashcodes and a strings that represents it
    //to prevent copying the strings we keep a pointer to them
    std::map<int, std::set<const std::string *, pointer_compare<std::string>>> links;

    //loop over every file
    for(const auto & fileN : input) {
        //loop over all words in a file, prevent copy by using a ref
        for(const std::string& word : fileN) {
            int hash = hashfunction(word);
            //add word to set of strings which hash value is hash
            links[hash].insert(&word);
        }
    }

    int count = 0;
    for (const auto &pair : links) {
        //we have a collision if there is more than one pointer in the set
        if(pair.second.size() > 1) {
            // uncomment the cout lines if you want to know what collides, now it only shows the number of collisions
           // std::cout << "Collisions found for hash " << pair.first << " :";
            for (const auto &wordPtr : pair.second) {
                //std::cout << " " << *wordPtr;
                count++;
            }
            //std::cout << std::endl;
        }
    }
    std::cout << "Total number of collisions: " << count << std::endl;
}

template <typename T>
std::vector<std::priority_queue<std::pair<double, int>>> jaccard(const std::vector<std::set<T>> &contents)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::priority_queue<std::pair<double, int>>> similarities(contents.size());

    //loop over all the input files
    for(int fileN = 0; fileN < contents.size(); fileN++) {
        //check this file against all the other files
        //no need to check all sets with smaller index than this one since we already saved those results
        for(int otherFileN = fileN + 1; otherFileN < contents.size(); otherFileN++) {
            int intersection = 0;
            //for all T in this files: check if other file contains T
            for(const T& t1 : contents[fileN]) {
                //increment intersection when other set also contains t1
                if(contents[otherFileN].find(t1) != contents[otherFileN].end()) intersection++;
            }
            //size of union = sum of both sizes - size of intersection
            int both = contents[fileN].size() + contents[otherFileN].size() - intersection;
            //calculate similarity between fileN and otherFileN
            double similarity = (intersection * 1.0) / both;
            //add data to result vector
            similarities[fileN].push(std::make_pair(similarity, otherFileN));
            //since J(fileN, otherFileN) == J(otherFileN, fileN) we can save both results
            similarities[otherFileN].push(std::make_pair(similarity, fileN));
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Calculating the Jaccard index took " << duration.count() << " ms" << std::endl;
    return similarities;
}

// Show for each document the most similar other documents. Each document only needs to occur once in the list.
// Ignore the document if the similarity score is lower than "threshold" 
void showSummary(std::vector<std::priority_queue<std::pair<double, int>>> &similarities, double threshold)
{
    //array to check whether we already printed a doc
    bool *isPrinted = new bool[similarities.size()]();

    //using iomanip to easily print a table in console
    //header line
    std::cout << std::left << std::setw(8) << std::setfill(' ') << "doc";
    std::cout << "Similar Documents" << std::endl;
    std::cout << std::left << std::setw(26) << std::setfill('-') << "" << std::endl;

    //data
    for(int i = 0; i < similarities.size(); i++) {
        //don't print line if the highest similarity is not above the threshold
        if(similarities[i].top().first < threshold) continue;
        std::stringstream similarDocs("");
        while(similarities[i].top().first >= threshold) {
            int currentSimDoc = similarities[i].top().second;
            double currentSim = similarities[i].top().first;
            double currentSimDocFav = similarities[currentSimDoc].top().first;
            //only print when this doc hasn't been printed yet
            // and only when this is the favorite document or a doc with the same similarity:
            // the similarity has to be greater or equal to the favorite doc
            if(!isPrinted[currentSimDoc] && currentSim >= currentSimDocFav) {
                similarDocs << currentSimDoc << " (" << currentSim << ") ";
                //indicate we printed this doc
                isPrinted[currentSimDoc] = true;
            }
            //advance the queue
            similarities[i].pop();
        }

        if(!similarDocs.str().empty()) {
            //print doc number
            std::cout << std::left << std::setw(8) << std::setfill(' ') << i
                      << similarDocs.str() << std::endl;
        }
    }
    delete[] isPrinted;
}

std::vector<std::priority_queue<std::pair<double, int>>> minhashing(const std::vector<std::set<int>> &contents, int n, int max)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::priority_queue<std::pair<double, int>>> similarities(contents.size());

    //calculation of all the smallest hashes
    int a, b, c = 7177;
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, max - 1);

    //links documents to their smallest id for each hash
    std::vector<std::vector<int>> smallerContents(contents.size(), std::vector<int>(n, c));

    //loop over all hash functions
    for(int k = 0; k < n; k++) {
        //new random a & b
        a = distribution(generator); b = distribution(generator);
        //loop over all the docs
        for (int setN = 0; setN < contents.size(); setN++) {
            int minHash = c;
            //loop over all the words in a doc
            for(const auto &wordId : contents[setN]) {
                //calculate the hash
                int hash = (a * wordId + b) % c;
                if(hash < minHash) {
                    // change the smallest hash if this hash is smaller
                    smallerContents[setN][k] = wordId;
                    minHash = hash;
                }
            }
        }
    }

    //now we can compare all the docs
    for(int docId = 0; docId < smallerContents.size(); docId++) {
        //loop over all following docs
        for(int otherDoc = docId + 1; otherDoc < smallerContents.size(); otherDoc++) {
            double similarity = 0.0;
            //check all hashes
            for(int hash = 0; hash < n; hash++) {
                if(smallerContents[docId][hash] == smallerContents[otherDoc][hash]) {
                    //increase similarity when smallest values are equal
                    similarity++;
                }
            }
            //divide by number of hashes to get the similarity
            similarity /= n;
            //since the similarities are the same for (docA, docB) and (docB, docA) we can add both
            similarities[docId].push(std::make_pair(similarity, otherDoc));
            similarities[otherDoc].push(std::make_pair(similarity, docId));
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "minhashing took " << duration.count() << " ms" << std::endl;
    return similarities;
}

int main()
{
    // Read the source code as sets of strings
    std::vector<std::set<std::string>> contents = readDatafiles("data/quiz/");
    std::cout << contents.size() << " files"<< std::endl;


    // Replace strings with integeres
    int maxId, maxHash;
    std::vector<std::set<int>> contentsId = replaceWithUniqueId(contents, maxId);
    std::vector<std::set<int>> contentsHash = replaceWithHash<stl_hash>(contents, maxHash);

    /*
    //test for hash speeds
    replaceWithHash<good_hash>(contents, maxHash);
    replaceWithHash<djb2>(contents, maxHash);
    replaceWithHash<sdbm>(contents, maxHash);
    replaceWithHash<stl_hash>(contents, maxHash);
    replaceWithHash<jenkins_one_at_a_time_hash>(contents, maxHash);
    */

    // Check if a certain hash function results in collisions
    /*
    findCollisions<worst_hash>(contents);
    findCollisions<bad_hash>(contents);
    findCollisions<other_bad_hash>(contents);
    findCollisions<horner_hash>(contents);
    findCollisions<good_hash>(contents);
    findCollisions<djb2>(contents);
    findCollisions<sdbm>(contents);
    findCollisions<lose_lose>(contents);
    findCollisions<stl_hash>(contents);
    findCollisions<jenkins_one_at_a_time_hash>(contents);
     */


    // Calculate the Jaccard similarity either on sets of strings or on sets of ints
    std::cout << "\nString comparison" << std::endl;
    std::vector<std::priority_queue<std::pair<double, int>>> similarities = jaccard<std::string>(contents);
    std::cout << "\nUnique ids" << std::endl;
    std::vector<std::priority_queue<std::pair<double, int>>> similaritiesId = jaccard<int>(contentsId);
    std::cout << "\nHashes" << std::endl;
    std::vector<std::priority_queue<std::pair<double, int>>> similaritiesHash = jaccard<int>(contentsId);

    int nHashes = 300;
    // Estimate the Jaccard similarity using minhashing
    std::cout << "\nMinhashing with unique ids" << std::endl;
    std::vector<std::priority_queue<std::pair<double, int>>> similaritiesMinHashId = minhashing(contentsId, nHashes, maxId);
    std::cout << "\nMinhashing with hashes" << std::endl;
    std::vector<std::priority_queue<std::pair<double, int>>> similaritiesMinHashHash = minhashing(contentsHash, nHashes, maxHash);

    // Show the results
    std::cout << "\nString comparison" << std::endl;
    showSummary(similarities, 0.75);
    std::cout << "\nMinhashing with unique ids" << std::endl;
    showSummary(similaritiesMinHashId, 0.75);
    std::cout << "\nMinhashing with hashes" << std::endl;
    showSummary(similaritiesMinHashHash, 0.75);



    return 0;
}
