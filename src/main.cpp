#include "URLShortenerService.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

void printHeader() {
    cout << "\n====== URL Shortener Service ======\n";
    cout << "1. Shorten a URL\n";
    cout << "2. Expand a short URL\n";
    cout << "3. View URL statistics\n";
    cout << "4. Delete a URL\n";
    cout << "5. List all URLs\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";
}

string formatTime(time_t t) {
    if (t == 0) return "N/A";
    char buffer[20];
    struct tm* tm_info = localtime(&t);
    strftime(buffer, 20, "%Y-%m-%d %H:%M", tm_info);
    return string(buffer);
}

int main() {
    URLShortenerService service("data/urls.txt");
    int choice;
    string longURL, shortCode;

    while (true) {
        printHeader();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(); // Consume newline

        switch (choice) {
            case 1:
                cout << "Enter long URL: ";
                getline(cin, longURL);
                if (longURL.empty()) {
                    cout << "Error: URL cannot be empty.\n";
                } else {
                    cout << "Short URL created: " << service.shortenURL(longURL) << "\n";
                }
                break;

            case 2:
                cout << "Enter short code: ";
                cin >> shortCode;
                cout << "Original URL: " << service.expandURL(shortCode) << "\n";
                break;

            case 3:
                cout << "Enter short code: ";
                cin >> shortCode;
                {
                    URL url = service.getStats(shortCode);
                    if (url.getShortCode().empty()) {
                        cout << "Error: Short code not found.\n";
                    } else {
                        cout << "\n--- URL Statistics ---\n";
                        cout << "Short Code:   " << url.getShortCode() << "\n";
                        cout << "Original URL: " << url.getLongURL() << "\n";
                        cout << "Access Count: " << url.getAccessCount() << "\n";
                        cout << "Created On:   " << formatTime(url.getCreatedAt()) << "\n";
                        cout << "Expires On:   " << formatTime(url.getExpiryAt()) << "\n";
                    }
                }
                break;

            case 4:
                cout << "Enter short code to delete: ";
                cin >> shortCode;
                if (service.deleteURL(shortCode)) {
                    cout << "Deleted short code: " << shortCode << "\n";
                } else {
                    cout << "Error: Short code not found.\n";
                }
                break;

            case 5:
                {
                    cout << "\n" << left << setw(10) << "CODE" 
                              << setw(40) << "LONG URL" 
                              << setw(10) << "CLICKS" 
                              << "EXPIRY" << "\n";
                    cout << "---------------------------------------------------------------------\n";
                    auto allUrls = service.getAllURLs();
                    if (allUrls.empty()) {
                        cout << "No URLs found.\n";
                    }
                    for (const auto& pair : allUrls) {
                        URL u = pair.second;
                        cout << left << setw(10) << u.getShortCode() 
                                  << setw(40) << (u.getLongURL().length() > 37 ? u.getLongURL().substr(0, 34) + "..." : u.getLongURL()) 
                                  << setw(10) << u.getAccessCount() 
                                  << formatTime(u.getExpiryAt()) << "\n";
                    }
                }
                break;

            case 6:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
