#include "URLShortenerService.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

URLShortenerService::URLShortenerService(string storageFile) : storageManager(storageFile) {
    srand(time(0)); 
    urlMap = storageManager.loadFromFile();
}

string URLShortenerService::generateShortCode() {
    string code = "";
    for (int i = 0; i < SHORT_CODE_LENGTH; ++i) {
        code += BASE62[rand() % BASE62.length()];
    }
    return code;
}

string URLShortenerService::shortenURL(string longURL) {
    // Check if URL already exists
    for (const auto& pair : urlMap) {
        if (pair.second.getLongURL() == longURL) {
            return "http://short.ly/" + pair.first;
        }
    }

    string shortCode;
    do {
        shortCode = generateShortCode();
    } while (urlMap.find(shortCode) != urlMap.end());

    time_t now = time(0);
    time_t expiry = now + EXPIRY_DURATION;
    
    URL newURL(longURL, shortCode, expiry);
    urlMap[shortCode] = newURL;
    storageManager.saveToFile(urlMap);
    
    return "http://short.ly/" + shortCode;
}

string URLShortenerService::expandURL(string shortCode) {
    if (urlMap.find(shortCode) == urlMap.end()) {
        return "Error: Short code not found.";
    }

    URL& url = urlMap[shortCode];
    if (url.isExpired()) {
        return "Error: This short URL has expired.";
    }

    url.incrementAccessCount();
    storageManager.saveToFile(urlMap); // Persist updated access count
    return url.getLongURL();
}

bool URLShortenerService::deleteURL(string shortCode) {
    if (urlMap.find(shortCode) != urlMap.end()) {
        urlMap.erase(shortCode);
        storageManager.saveToFile(urlMap);
        return true;
    }
    return false;
}

URL URLShortenerService::getStats(string shortCode) {
    if (urlMap.find(shortCode) != urlMap.end()) {
        return urlMap[shortCode];
    }
    return URL(); // Return empty URL object if not found
}

unordered_map<string, URL> URLShortenerService::getAllURLs() {
    return urlMap;
}
