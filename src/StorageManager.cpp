#include "StorageManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

StorageManager::StorageManager(string filePath) : filePath(filePath) {}

vector<string> StorageManager::split(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

unordered_map<string, URL> StorageManager::loadFromFile() {
    unordered_map<string, URL> urls;
    ifstream file(filePath);
    
    if (!file.is_open()) {
        // If file doesn't exist, just return empty map
        return urls; 
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        vector<string> parts = split(line, '|');
        if (parts.size() == 5) {
            string shortCode = parts[0];
            string longURL = parts[1];
            time_t createdAt = stoll(parts[2]);
            time_t expiryAt = stoll(parts[3]);
            int accessCount = stoi(parts[4]);

            URL url(longURL, shortCode, createdAt, expiryAt, accessCount);
            urls[shortCode] = url;
        }
    }
    file.close();
    return urls;
}

void StorageManager::saveToFile(const unordered_map<string, URL>& urls) {
    ofstream file(filePath);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing: " << filePath << endl;
        return;
    }

    for (const auto& pair : urls) {
        URL url = pair.second;
        file << url.getShortCode() << "|" 
             << url.getLongURL() << "|" 
             << url.getCreatedAt() << "|" 
             << url.getExpiryAt() << "|" 
             << url.getAccessCount() << "\n";
    }
    file.close();
}
