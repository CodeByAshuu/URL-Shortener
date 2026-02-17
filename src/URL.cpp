#include "URL.h"
#include <ctime>

using namespace std;

URL::URL() : accessCount(0), createdAt(time(0)), expiryAt(0) {}

URL::URL(string longURL, string shortCode, time_t expiryAt)
    : longURL(longURL), shortCode(shortCode), createdAt(time(0)), expiryAt(expiryAt), accessCount(0) {}

URL::URL(string longURL, string shortCode, time_t createdAt, time_t expiryAt, int accessCount)
    : longURL(longURL), shortCode(shortCode), createdAt(createdAt), expiryAt(expiryAt), accessCount(accessCount) {}

string URL::getLongURL() const {
    return longURL;
}

string URL::getShortCode() const {
    return shortCode;
}

time_t URL::getCreatedAt() const {
    return createdAt;
}

time_t URL::getExpiryAt() const {
    return expiryAt;
}

int URL::getAccessCount() const {
    return accessCount;
}

void URL::incrementAccessCount() {
    accessCount++;
}

bool URL::isExpired() const {
    return time(0) > expiryAt;
}
