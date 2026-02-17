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
        // The format is: shortCode|longURL|createdAt|expiryAt|accessCount
        // parts[0] is shortCode
        // parts[parts.size()-3] is createdAt
        // parts[parts.size()-2] is expiryAt
        // parts[parts.size()-1] is accessCount
        // Everything in between is the longURL
        if (parts.size() >= 5) {
            string shortCode = parts[0];
            
            // Reconstruct longURL in case it contains '|'
            string longURL = "";
            for (size_t i = 1; i <= parts.size() - 4; ++i) {
                longURL += parts[i];
                if (i < parts.size() - 4) longURL += "|";
            }

            time_t createdAt = stoll(parts[parts.size() - 3]);
            time_t expiryAt = stoll(parts[parts.size() - 2]);
            int accessCount = stoi(parts[parts.size() - 1]);

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
