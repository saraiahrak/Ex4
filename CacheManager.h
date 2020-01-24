//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

#include <functional>


using namespace std;


class CacheManager {
public:

    //apply a lambada function to all objects in cache
    virtual void foreach(const function<void(string &)> f) = 0;

    //get the solution given a problem
    virtual string getSolution(string key) = 0;

    //insert a new problem and solution to the cache
    virtual void insert(string problem, string obj) = 0;

    //check if problem exists in cache
    virtual bool existsInCache(string key) = 0;

    //check if problem exists in files
    virtual bool existsInFiles(string key) = 0;

    //get solution from files
    virtual string getFromFiles(string key) = 0;

    //get solution from cache
    virtual string getFromCache(string key) = 0;

    //insert to cache
    virtual void insertToCache(string key, string obj) = 0;

    //write the problem and solution in files
    virtual void writeToFile(string key, string obj) = 0;

    //check if the cache is in full capacity
    virtual bool fullCapacity() = 0;

    //move an object in cache to the front
    virtual void moveToFront(string key) = 0;

    //remove an object from cache
    virtual void removeFromCache() = 0;

};


#endif //EX4_CACHEMANAGER_H
