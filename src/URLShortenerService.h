#ifndef URLSHORTENERSERVICE_H
#define URLSHORTENERSERVICE_H

#include "StorageManager.h"
#include "URL.h"
#include <string>
#include <unordered_map>

class URLShortenerService {
private:
    std::unordered_map<std::string, URL> urlMap;
    StorageManager storageManager;
    const std::string BASE62 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int SHORT_CODE_LENGTH = 6;
    const long EXPIRY_DURATION = 30 * 24 * 60 * 60; // 30 days in seconds

    std::string generateShortCode();

public:
    URLShortenerService(std::string storageFile);
    std::string shortenURL(std::string longURL);
    std::string expandURL(std::string shortCode);
    bool deleteURL(std::string shortCode);
    URL getStats(std::string shortCode);
    std::unordered_map<std::string, URL> getAllURLs();
};

#endif // URLSHORTENERSERVICE_H
