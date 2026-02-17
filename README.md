# URL Shortener System in C++

A robust, file-based URL Shortener service written in C++. This project demonstrates backend engineering concepts, data persistence, and clean system design.

## Features

- **URL Shortening**: Converts long URLs into 6-character unique short codes using Base62 encoding.
- **URL Redirection**: Retrieves original URLs from short codes.
- **Persistent Storage**: Saves data to `data/urls.txt`, ensuring data survives application restarts.
- **Expiry Support**: URLs automatically expire after a default of 30 days.
- **Analytics**: Tracks access counts for each short URL.
- **Collision Handling**: Handles hash collisions by regenerating codes.
- **CLI Interface**: Interactive menu for managing URLs.

## Project Structure

```
URL-Shortener/
│── src/
│   ├── main.cpp
│   ├── URL.cpp
│   ├── URLShortenerService.cpp
│   ├── StorageManager.cpp
│   ├── URL.h
│   ├── URLShortenerService.h
│   ├── StorageManager.h
│── data/
│   ├── urls.txt
│── README.md
```

## How to Run

1.  **Compile the code**:
    ```bash
    g++ src/*.cpp -o url_shortener
    ```

2.  **Run the executable**:
    ```bash
    ./url_shortener
    ```

3.  **Follow the on-screen menu** to shorten, expand, and manage URLs.

## Future Improvements

-   **SQLite Integration**: Replace file-based storage with SQLite for better scalability.
-   **REST API**: Expose functionality via a REST API using a C++ framework like Crow.
-   **Custom Short Codes**: Allow users to define their own custom aliases.
-   **Rate Limiting**: Prevent abuse by limiting requests per user.

## Author

Amazon SDE Intern Candidate
