#include "cow_string.h"

#include <stdexcept>

StringData::StringData(std::string_view str) : count_(1), size_(str.size()) {
    str_ = new char[size_];
    for (size_t i = 0; i < size_; ++i) {
        str_[i] = str[i];
    }
}

StringData::~StringData() {
    delete[] str_;
}

void StringData::Inc() {
    ++count_;
}

void StringData::Dec() {
    --count_;
    if (count_ == 0) {
        delete this;
    }
}

char* StringData::GetStr() const {
    return str_;
}

size_t StringData::GetCount() const {
    return count_;
}

size_t StringData::GetSize() const {
    return size_;
}

ProxyChar::ProxyChar(CowString* ptr, int val) : pos_(val), ptr_(ptr) {
}

ProxyChar& ProxyChar::operator=(const char& x) {
    if (ptr_->data_->GetCount() == 1) {
        ptr_->data_->GetStr()[pos_] = x;
        return *this;
    }
    if (x != ptr_->data_->GetStr()[pos_]) {
        char* cpy = new char[ptr_->data_->GetSize()];
        for (size_t i = 0; i < ptr_->data_->GetSize(); ++i) {
            cpy[i] = ptr_->data_->GetStr()[i];
        }
        ptr_->data_->Dec();
        cpy[pos_] = x;
        ptr_->data_ = new StringData(std::string_view(cpy, cpy + ptr_->data_->GetSize()));
        delete[] cpy;
    }
    return *this;
}

ProxyChar& ProxyChar::operator=(const ProxyChar& other) {
    if (this != &other) {
        *this = char(other);
    }
    return *this;
}

ProxyChar::operator char() const {
    return ptr_->data_->GetStr()[pos_];
}

CowString::Iterator::Iterator(CowString* ptr, size_t pos) : pos_(pos), ptr_(ptr) {
}

CowString::Iterator& CowString::Iterator::operator++() {
    ++pos_;
    return *this;
}

bool CowString::Iterator::operator!=(const CowString::Iterator& other) {
    return pos_ != other.pos_;
}

ProxyChar CowString::Iterator::operator*() {
    return ProxyChar(ptr_, pos_);
}

CowString::ConstIterator::ConstIterator(const CowString* ptr, size_t pos) : pos_(pos), ptr_(ptr) {
}

CowString::ConstIterator& CowString::ConstIterator::operator++() {
    ++pos_;
    return *this;
}

bool CowString::ConstIterator::operator!=(const CowString::ConstIterator& other) {
    return pos_ != other.pos_;
}

char CowString::ConstIterator::operator*() const {
    return ptr_->At(pos_);
}

CowString::CowString(std::string_view str) : data_(new StringData(str)) {
}

CowString::CowString(const CowString& other) : data_(other.data_) {
    data_->Inc();
}

CowString::CowString(CowString&& other) : data_(other.data_) {
    other.data_ = nullptr;
}

CowString::~CowString() {
    if (data_) {
        data_->Dec();
    }
}

CowString& CowString::operator=(const CowString& other) {
    if (data_ != other.data_) {
        data_->Dec();
        data_ = other.data_;
        data_->Inc();
    }
    return *this;
}

CowString& CowString::operator=(std::string_view str) {
    data_->Dec();
    data_ = new StringData(str);
    return *this;
}

CowString CowString::operator=(CowString&& other) {
    if (data_ != other.data_) {
        data_->Dec();
        data_ = other.data_;
        other.data_ = nullptr;
    }
    return *this;
}

const char* CowString::GetData() const {
    return (data_->GetStr());
}

CowString::Iterator CowString::begin() {
    return {this, 0};
}

CowString::ConstIterator CowString::begin() const {
    return {this, 0};
}

CowString::Iterator CowString::end() {
    return {this, data_->GetSize()};
}

CowString::ConstIterator CowString::end() const {
    return {this, data_->GetSize()};
}

ProxyChar CowString::operator[](size_t pos) {
    return ProxyChar(this, pos);
}

char CowString::At(size_t pos) const {
    if (pos < data_->GetSize()) {
        return data_->GetStr()[pos];
    }
    throw std::out_of_range{"string index is out of range"};
}

CowString CowString::operator+(std::string_view str) {
    size_t s = data_->GetSize();
    char sum[s + str.size()];
    for (size_t i = 0; i < s; ++i) {
        sum[i] = data_->GetStr()[i];
    }
    for (size_t i = 0; i < str.size(); ++i) {
        sum[s + i] = str[i];
    }
    return CowString(std::string_view{sum, sum + s + str.size()});
}

CowString CowString::operator+(const CowString& other) {
    return *this + std::string_view(other);
}

CowString& CowString::operator+=(std::string_view str) {
    *this = *this + str;
    return *this;
}

CowString& CowString::operator+=(const CowString& other) {
    *this = *this + other;
    return *this;
}

bool CowString::operator==(std::string_view str) const {
    return std::string_view{*this} == str;
}

bool CowString::operator==(const CowString& other) const {
    return std::string_view{*this} == std::string_view{other};
}

bool operator==(std::string_view str, const CowString& other) {
    return str == std::string_view{other};
}

bool CowString::operator!=(std::string_view str) const {
    return !(*this == str);
}

bool CowString::operator!=(const CowString& other) const {
    return !(*this == other);
}

bool operator!=(std::string_view str, const CowString& other) {
    return !(str == other);
}

CowString::operator std::string_view() const {
    return std::string_view{data_->GetStr(), data_->GetStr() + data_->GetSize()};
}