//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

#include <functional>


using namespace std;


class CacheManager {
public:

    virtual void foreach(const function<void(string &)> f) = 0;

    virtual string getSolution(string key) = 0;

    virtual void insert(string problem, string obj) = 0;

    virtual bool existsInCache(string key) = 0;

    virtual bool existsInFiles(string key) = 0;

    virtual string getFromFiles(string key) = 0;

    virtual string getFromCache(string key) = 0;

    virtual void insertToCache(string key, string obj) = 0;

    virtual void writeToFile(string key, string obj) = 0;

    virtual bool fullCapacity() = 0;

    virtual void moveToFront(string key) = 0;

    virtual void removeFromCache() = 0;

};


#endif //EX4_CACHEMANAGER_H
