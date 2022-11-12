#pragma once

#include <string_view>

class CowString;

class StringData {
public:
    StringData(std::string_view);
    ~StringData();
    void Inc();
    void Dec();
    char* GetStr() const;
    size_t GetCount() const;
    size_t GetSize() const;

private:
    char* str_;
    size_t count_;
    size_t size_;
};

class ProxyChar {
public:
    ProxyChar(CowString* ptr, int val);
    ProxyChar& operator=(const char& x);
    ProxyChar& operator=(const ProxyChar& other);
    operator char() const;

private:
    size_t pos_;
    CowString* ptr_;
};

class CowString {
public:
    class Iterator {
    public:
        Iterator(CowString* ptr, size_t pos);
        Iterator& operator++();
        bool operator!=(const Iterator& other);
        ProxyChar operator*();

    private:
        size_t pos_ = 0;
        CowString* ptr_;
    };

    class ConstIterator {
    public:
        ConstIterator(const CowString* ptr, size_t pos);
        ConstIterator& operator++();
        bool operator!=(const ConstIterator& other);
        char operator*() const;

    private:
        size_t pos_ = 0;
        const CowString* ptr_;
    };

    CowString(std::string_view str);
    CowString(const CowString& other);
    CowString(CowString&& other);
    ~CowString();

    CowString& operator=(std::string_view str);
    CowString& operator=(const CowString& other);
    CowString operator=(CowString&& other);

    const char* GetData() const;
    Iterator begin();             // NOLINT
    ConstIterator begin() const;  // NOLINT
    Iterator end();               // NOLINT
    ConstIterator end() const;    // NOLINT
    ProxyChar operator[](size_t pos);
    char At(size_t pos) const;

    CowString operator+(std::string_view str);
    CowString operator+(const CowString& other);
    CowString& operator+=(std::string_view str);
    CowString& operator+=(const CowString& other);

    bool operator==(std::string_view str) const;
    bool operator==(const CowString& other) const;

    bool operator!=(std::string_view str) const;
    bool operator!=(const CowString& other) const;

    operator std::string_view() const;
    friend class ProxyChar;

private:
    StringData* data_;
};

bool operator==(std::string_view str, const CowString& other);
bool operator!=(std::string_view str, const CowString& other);
