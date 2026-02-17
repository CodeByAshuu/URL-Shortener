#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include "URL.h"
#include <string>
#include <unordered_map>
#include <vector>

class StorageManager {
private:
    std::string filePath;
    std::vector<std::string> split(const std::string &str, char delimiter);

public:
    StorageManager(std::string filePath);
    std::unordered_map<std::string, URL> loadFromFile();
    void saveToFile(const std::unordered_map<std::string, URL>& urls);
};

#endif // STORAGEMANAGER_H
