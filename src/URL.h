#ifndef URL_H
#define URL_H

#include <string>
#include <ctime>

class URL {
private:
    std::string longURL;
    std::string shortCode;
    time_t createdAt;
    time_t expiryAt;
    int accessCount;

public:
    // Constructors
    URL();
    URL(std::string longURL, std::string shortCode, time_t expiryAt);
    URL(std::string longURL, std::string shortCode, time_t createdAt, time_t expiryAt, int accessCount);

    // Getters
    std::string getLongURL() const;
    std::string getShortCode() const;
    time_t getCreatedAt() const;
    time_t getExpiryAt() const;
    int getAccessCount() const;

    // Setters & Modifiers
    void incrementAccessCount();
    bool isExpired() const;

    // Serialization helper (optional, can be done in StorageManager too)
    // std::string toString() const; 
};

#endif // URL_H
