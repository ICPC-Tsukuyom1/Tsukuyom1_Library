#ifndef TSUKUYOM1_VERIFY_FASTIO_HPP
#define TSUKUYOM1_VERIFY_FASTIO_HPP

// Include template.cpp first.
template <class T>
concept FastInteger = integral<T> && !same_as<T, bool> && sizeof(T) <= sizeof(ll);

template <size_t BufferSize = 1 << 16>
class FastIn {
  static_assert(BufferSize > 0);
  unsigned char buffer_[BufferSize];
  size_t pos_ = 0, end_ = 0;
  bool good_ = true;

  bool refill() {
    if (pos_ < end_) return true;
    end_ = fread(buffer_, 1, BufferSize, stdin);
    pos_ = 0;
    return end_ != 0;
  }
  bool skip_space() {
    while (refill()) {
      while (pos_ < end_ && buffer_[pos_] <= ' ') ++pos_;
      if (pos_ < end_) return true;
    }
    return false;
  }
  bool fail() { good_ = false; return false; }

public:
  FastIn() = default;
  FastIn(const FastIn&) = delete;
  FastIn& operator=(const FastIn&) = delete;
  explicit operator bool() const { return good_; }

  // Numeric tokens must fit T. Accumulate unsigned to handle signed minima.
  template <FastInteger T>
  bool read(T& value) {
    if (!good_ || !skip_space()) return fail();
    bool negative = buffer_[pos_] == '-';
    if (negative || buffer_[pos_] == '+') ++pos_;
    using U = make_unsigned_t<T>;
    U magnitude = 0;
    bool any = false;
    while (refill()) {
      const unsigned char* p = buffer_ + pos_;
      const unsigned char* end = buffer_ + end_;
      if constexpr (endian::native == endian::little) {
        // Cheap probes skip packed conversion for common short tokens.
        while (end - p >= 8 && p[1] >= '0' && p[6] >= '0') {
          uint64_t v;
          memcpy(&v, p, 8);
          if (((v + 0x4646464646464646ULL) | (v - 0x3030303030303030ULL)) & 0x8080808080808080ULL) break;
          v -= 0x3030303030303030ULL;
          v = (v * 10 + (v >> 8)) & 0x00ff00ff00ff00ffULL;
          v = (v * 100 + (v >> 16)) & 0x0000ffff0000ffffULL;
          magnitude = magnitude * 100000000ULL + (uint32_t)(v * 10000 + (v >> 32));
          p += 8;
          any = true;
        }
      }
      while (p != end) {
        unsigned digit = *p - '0';
        if (digit > 9) break;
        magnitude = magnitude * 10 + digit;
        ++p;
        any = true;
      }
      pos_ = p - buffer_;
      if (p != end) break;
    }
    if (!any) return fail();
    if constexpr (is_signed_v<T>) {
      value = negative && magnitude
                  ? -static_cast<T>(magnitude - 1) - 1
                  : static_cast<T>(magnitude);
    } else {
      value = static_cast<T>(negative ? U(0) - magnitude : magnitude);
    }
    return true;
  }
  bool read(char& value) {
    if (!good_ || !skip_space()) return fail();
    value = static_cast<char>(buffer_[pos_++]);
    return true;
  }
  bool read(string& value) {
    if (!good_ || !skip_space()) return fail();
    value.clear();
    do {
      auto start = pos_;
      while (pos_ < end_ && buffer_[pos_] > ' ') ++pos_;
      value.append(reinterpret_cast<const char*>(buffer_ + start), pos_ - start);
      if (pos_ < end_) break;
    } while (refill());
    return true;
  }
  template <class T>
  FastIn& operator>>(T& value) {
    if (good_) read(value);
    return *this;
  }
};

template <size_t BufferSize = 1 << 16>
class FastOut {
  static_assert(BufferSize > 0);
  char buffer_[BufferSize];
  size_t pos_ = 0;
  bool good_ = true;

  bool write_bytes(const char* data, size_t size) {
    while (size) {
      auto written = fwrite(data, 1, size, stdout);
      if (!written) { good_ = false; return false; }
      data += written;
      size -= written;
    }
    return true;
  }
  bool drain() {
    if (!good_) return false;
    bool ok = write_bytes(buffer_, pos_);
    pos_ = 0;
    return ok;
  }

public:
  FastOut() = default;
  FastOut(const FastOut&) = delete;
  FastOut& operator=(const FastOut&) = delete;
  ~FastOut() { flush(); }
  explicit operator bool() const { return good_; }

  bool flush() {
    if (!drain()) return false;
    if (fflush(stdout) != 0) good_ = false;
    return good_;
  }
  void put(char value) {
    if (!good_ || (pos_ == BufferSize && !drain())) return;
    buffer_[pos_++] = value;
  }
  void write(char value) { put(value); }
  void write(bool value) { put(value ? '1' : '0'); }
  void write(string_view value) {
    if (!good_ || value.empty()) return;
    if (value.size() >= BufferSize) {
      if (drain()) write_bytes(value.data(), value.size());
      return;
    }
    if (value.size() > BufferSize - pos_ && !drain()) return;
    memcpy(buffer_ + pos_, value.data(), value.size());
    pos_ += value.size();
  }
  void write(const char* value) { write(string_view(value)); }

  template <FastInteger T>
  void write(T value) {
    if constexpr (BufferSize >= 20) {
      if (!good_ || (BufferSize - pos_ < 20 && !drain())) return;
      auto result = to_chars(buffer_ + pos_, buffer_ + BufferSize, value);
      pos_ = result.ptr - buffer_;
    } else {
      char digits[20];
      auto result = to_chars(digits, digits + sizeof(digits), value);
      write(string_view(digits, result.ptr - digits));
    }
  }
  template <class T>
  FastOut& operator<<(const T& value) {
    write(value);
    return *this;
  }
};

#endif
