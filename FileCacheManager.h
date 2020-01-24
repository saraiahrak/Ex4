//
// Created by sarai on 14/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <list>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <mutex>

using namespace std;

class FileCacheManager : public CacheManager {
public:
    //maps a problem string to a unique sequence of numbers
    hash<string> hashFunc;
    int cap;
    list <string> keyList;
    unordered_map<string, pair<string, list<string>::iterator>> myCache;

    //constructor
    explicit FileCacheManager(int capacity) {
        cap = capacity;
    }

    //destructor
    ~FileCacheManager() = default;

    //apply a lambada function to all objects in cache
    void foreach(const function<void(string &)> f) override {
        for (const string &problem: keyList) {
            string solution = myCache[problem].first;
            f(solution);
        }
    }

    //get the solution from cache/ files given problem
    string getSolution(string problem) override {
        fileLock.lock();
        string solution;
        if (!existsInCache(problem) && !existsInFiles(problem)) {
            fileLock.unlock();
            throw "Object could not be found";
        }
        if (existsInCache(problem)) {
            solution = getFromCache(problem);
        } else if (existsInFiles(problem)) {
            solution = getFromFiles(problem);
        }
        fileLock.unlock();
        return solution;
    }

    //insert a new [problem, solution]
    void insert(string problem, string solution) override {
        cacheLock.lock();
        if (fullCapacity()) {
            removeFromCache();
        }
        insertToCache(problem, solution);
        writeToFile(problem, solution);
        cacheLock.unlock();
    }

    //check if problem exists in cache
    bool existsInCache(string problem) override {
        return myCache.find(problem) != myCache.end();
    }
    //check if problem exists in files
    bool existsInFiles(string problem) override {
        string filename = to_string(hashFunc(problem)) + ".txt";
        fstream file{filename, ios::in};
        if (file.is_open()) {
            file.close();
            return true;
        }
        return false;
    }

    //get solution from files
    string getFromFiles(string problem) override {
        string solution;
        string filename = to_string(hashFunc(problem)) + ".txt";
        fstream in{filename, ios::in};
        if (!in) {
            cerr << "Couldn't open file";
            return "";
        }
        getline(in, solution);
        in.close();

        if (fullCapacity()) {
            removeFromCache();
        }
        if (!existsInCache(problem)) {
            insertToCache(problem, solution);
        } else {
            moveToFront(problem);
        }
        return solution;
    }

    //get solution from cache
    string getFromCache(string problem) override {
        moveToFront(problem);
        return myCache[problem].first;
    }

    //insert a [problem, solution] to cache
    void insertToCache(string problem, string solution) override {
        keyList.push_front(problem);
        myCache[problem] = pair<string, list<string>::iterator>(solution, keyList.begin());
    }

    //write to file
    void writeToFile(string problem, string solution) override {
        string filename = to_string(hashFunc(problem)) + ".txt";
        fstream file{filename, ios::out};
        if (!file) {
            throw "Couldn't open file";
        }
        file << solution;
        file << '\n';
        file.close();
    }

    //check if cache is at full capacity
    bool fullCapacity() override {
        return myCache.size() == (unsigned) cap;
    }


    //move a problem to front of cache
    void moveToFront(string problem) override {
        auto it = myCache.find(problem);
        keyList.remove(problem);
        keyList.push_front(problem);
        if (it != myCache.end()) {
            (myCache[problem]).second = keyList.begin();
        }
    }

    //remove from cache
    void removeFromCache() override {
        string problem = keyList.back();
        myCache.erase(problem);
        keyList.pop_back();
    }

private:

    //mutexes for parallel access to cache and files
    mutex fileLock;

    mutex cacheLock;
};


#endif //EX4_FILECACHEMANAGER_H
