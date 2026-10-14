#!/usr/bin/env python3
"""Self-contained fastio.hpp tests; all generated/build files live in a tempdir.

Usage: python3 verify/tests/test_fastio.py [--cxx g++] [--sanitize]
Only run this after verify/fastio.hpp is ready. No third-party Python packages
are needed. Standard integer expectations are computed with Python integers.
The fixture includes template.cpp and checks contracts in strict and GNU C++20.
"""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import random
import subprocess
import sys
import tempfile


CPP = r'''
#include "template.cpp"
#include "fastio.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

// GNU mode recognizes extended integers as integral; size must still exclude them.
static_assert(!FastInteger<__int128_t>);
static_assert(!FastInteger<__uint128_t>);

template<class T>
std::string decimal(T value) {
    return std::to_string(value);
}

template<std::size_t N>
constexpr bool contracts() {
    using In = FastIn<N>;
    using Out = FastOut<N>;
    static_assert(!std::is_copy_constructible_v<In>);
    static_assert(!std::is_copy_assignable_v<In>);
    static_assert(!std::is_move_constructible_v<In>);
    static_assert(!std::is_move_assignable_v<In>);
    static_assert(!std::is_copy_constructible_v<Out>);
    static_assert(!std::is_copy_assignable_v<Out>);
    static_assert(!std::is_move_constructible_v<Out>);
    static_assert(!std::is_move_assignable_v<Out>);
    static_assert(!std::is_convertible_v<In, bool>);
    static_assert(!std::is_convertible_v<Out, bool>);
    static_assert(std::is_default_constructible_v<In>);
    static_assert(std::is_default_constructible_v<Out>);
    static_assert(!std::is_constructible_v<In, std::FILE*>);
    static_assert(!std::is_constructible_v<Out, std::FILE*>);
    static_assert(std::is_same_v<decltype(std::declval<In&>().read(
        std::declval<int&>())), bool>);
    static_assert(std::is_same_v<decltype(std::declval<Out&>().write(0)), void>);
    static_assert(std::is_same_v<decltype(std::declval<Out&>().flush()), bool>);
    return true;
}
static_assert(contracts<65536>() && contracts<7>() && contracts<1>()
              && contracts<20>() && contracts<21>());
static_assert(std::is_same_v<FastIn<>, FastIn<65536>>);
static_assert(std::is_same_v<FastOut<>, FastOut<65536>>);

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

template<std::size_t N, class Action>
void with_input(const std::string& transport, const char* path, Action action) {
    if (transport == "file") {
        // Reopen before construction: stdin is a regular file, not a pipe.
        // This also exercises any future regular-file/mmap implementation.
        require(std::freopen(path, "rb", stdin) != nullptr, "cannot redirect stdin");
    }
    FastIn<N> input;
    action(input);
}

template<class T, std::size_t N>
bool next(FastIn<N>& input, T& value, bool extraction) {
    if (extraction) {
        input >> value;
        return static_cast<bool>(input);
    }
    return input.read(value);
}

template<class T, std::size_t N>
void numbers(FastIn<N>& input, bool extraction) {
    T value{};
    while (next(input, value, extraction)) {
        require(static_cast<bool>(input), "input false after successful read");
        std::cout << decimal(value) << '\n';
    }
    require(!static_cast<bool>(input), "input true after failed EOF read");
    require(!input.read(value), "repeated EOF read succeeded");
    input >> value;
    require(!static_cast<bool>(input), "EOF extraction reset input state");
}

template<std::size_t N>
void dispatch_numbers(FastIn<N>& input, const std::string& type, bool extraction) {
    if (type == "schar") numbers<signed char>(input, extraction);
    else if (type == "uchar") numbers<unsigned char>(input, extraction);
    else if (type == "short") numbers<short>(input, extraction);
    else if (type == "ushort") numbers<unsigned short>(input, extraction);
    else if (type == "int") numbers<int>(input, extraction);
    else if (type == "uint") numbers<unsigned int>(input, extraction);
    else if (type == "long") numbers<long>(input, extraction);
    else if (type == "ulong") numbers<unsigned long>(input, extraction);
    else if (type == "ll") numbers<long long>(input, extraction);
    else if (type == "ull") numbers<unsigned long long>(input, extraction);

    else throw std::runtime_error("unknown integer type");
}

template<class T, std::size_t N>
void text(FastIn<N>& input, bool extraction) {
    T value{};
    while (next(input, value, extraction)) {
        require(static_cast<bool>(input), "input false after successful text read");
        if constexpr (std::is_same_v<T, char>) {
            std::cout << static_cast<unsigned int>(static_cast<unsigned char>(value)) << '\n';
        } else {
            std::cout << value.size() << ':' << value << '\n';
        }
    }
    require(!static_cast<bool>(input), "text input true at EOF");
    require(!input.read(value), "repeated text EOF read succeeded");
    require(!static_cast<bool>(input), "text EOF read reset input state");
}

template<std::size_t N>
void mixed(FastIn<N>& input, bool extraction) {
    int first = 0, second = 0;
    char a = '\0', b = '\0';
    std::string word;
    long long minimum = 0;
    if (extraction) {
        input >> first >> a >> b >> word >> second >> minimum;
        require(static_cast<bool>(input), "mixed extraction failed");
    } else {
        require(input.read(first), "mixed integer failed");
        require(input.read(a), "mixed first character failed");
        require(input.read(b), "mixed second character failed");
        require(input.read(word), "mixed string failed");
        require(input.read(second), "mixed second integer failed");
        require(input.read(minimum), "mixed final integer failed");
        require(static_cast<bool>(input), "mixed input false on final token");
    }
    std::cout << first << '\n' << a << '\n' << b << '\n' << word << '\n'
              << second << '\n' << decimal(minimum) << '\n';
    require(!input.read(word), "mixed EOF read succeeded");
    require(!static_cast<bool>(input), "mixed input true after EOF");
}

template<bool Insertion, class T, std::size_t N>
void emit(FastOut<N>& output, const T& value) {
    if constexpr (Insertion) output << value;
    else output.write(value);
}

template<bool Insertion, class T, std::size_t N>
void emit_bounds(FastOut<N>& output) {
    emit<Insertion>(output, std::numeric_limits<T>::min());
    output.put(',');
    emit<Insertion>(output, std::numeric_limits<T>::max());
    output.put('\n');
}

std::string long_token() {
    const std::string pattern = "Ab9_-XYZ0123456789";
    std::string result(2 * 1024 * 1024, ' ');
    for (std::size_t i = 0; i < result.size(); ++i) result[i] = pattern[i % pattern.size()];
    return result;
}

template<bool Insertion, std::size_t N>
void output_body(FastOut<N>& output, bool explicit_flush) {
    require(static_cast<bool>(output), "new output has failed state");
    if (explicit_flush) require(output.flush(), "initial empty flush failed");
    // Both 64-bit endpoints need 20 characters. Start at controlled offsets
    // to cover exactly 20 free bytes, 19 free bytes, and full/empty buffers.
    const std::size_t paddings[] = {0, 1, N > 20 ? N - 20 : 0,
                                   N > 19 ? N - 19 : 0, N - 1, N};
    for (std::size_t padding : paddings) {
        for (bool unsigned_value : {false, true}) {
            require(output.flush(), "alignment reset flush failed");
            emit<Insertion>(output, std::string(padding, '~'));
            if (unsigned_value) emit<Insertion>(output, std::numeric_limits<unsigned long long>::max());
            else emit<Insertion>(output, std::numeric_limits<long long>::min());
            output.put('\n');
            require(output.flush(), "aligned integer flush failed");
        }
    }
    emit<Insertion>(output, std::string_view{}); // data() is null.
    emit<Insertion>(output, 'X');
    output.put(':');
    emit<Insertion>(output, std::string("string"));
    emit<Insertion>(output, "|cstr|");
    emit<Insertion>(output, std::string_view("xxVIEWyy").substr(2, 4));
    emit<Insertion>(output, std::string_view{});
    output.put('|');
    emit<Insertion>(output, false);
    emit<Insertion>(output, true);
    output.put('\n');
    emit<Insertion>(output, std::string("A\0B", 3));
    emit<Insertion>(output, std::string_view("C\0D", 3));
    emit<Insertion>(output, "");
    output.put('\n');
    emit_bounds<Insertion, signed char>(output);
    emit_bounds<Insertion, unsigned char>(output);
    emit_bounds<Insertion, short>(output);
    emit_bounds<Insertion, unsigned short>(output);
    emit_bounds<Insertion, int>(output);
    emit_bounds<Insertion, unsigned int>(output);
    emit_bounds<Insertion, long>(output);
    emit_bounds<Insertion, unsigned long>(output);
    emit_bounds<Insertion, long long>(output);
    emit_bounds<Insertion, unsigned long long>(output);

    emit<Insertion>(output, -0);
    output.put(',');
    emit<Insertion>(output, -1);
    output.put(',');
    emit<Insertion>(output, 42u);
    output.put('\n');
    emit<Insertion>(output, long_token());
    output.put('\n');
    if constexpr (Insertion) output << 'c' << std::string("hain") << '!' << '\n';
    else emit<Insertion>(output, "chain!\n");
    require(static_cast<bool>(output), "output failed while writing");
    if (explicit_flush) {
        require(output.flush(), "flush failed");
        require(output.flush(), "second empty flush failed");
        emit<Insertion>(output, "|after-flush|\n");
        require(output.flush(), "flush after additional write failed");
        require(static_cast<bool>(output), "output false after successful flush");
    } else {
        emit<Insertion>(output, "|destructor|\n");
    }
    emit<Insertion>(output, std::string_view{});
}

template<std::size_t N>
void output(const std::string& api, bool explicit_flush,
            const std::string& transport, const char* path) {
    if (transport == "file") {
        require(std::freopen(path, "wb", stdout) != nullptr, "cannot redirect stdout");
    }
    {
        FastOut<N> out;
        if (api == "stream") output_body<true>(out, explicit_flush);
        else output_body<false>(out, explicit_flush);
        if (explicit_flush && transport == "file") {
            // Observe through a separate stream before out's destructor or
            // process exit can hide a missing flush of stdout's stdio buffer.
            std::ifstream observed(path, std::ios::binary);
            require(observed.is_open(), "cannot observe redirected stdout");
            const std::string bytes((std::istreambuf_iterator<char>(observed)),
                                    std::istreambuf_iterator<char>());
            require(bytes.ends_with("|after-flush|\n"),
                    "explicit flush not visible before destructor");
        }
    }
    // Python checks the complete stdout/file after destruction and process exit.
}

template<class T>
void layout_line(const char* name) {
    std::cout << name << ' ' << std::numeric_limits<T>::digits << ' '
              << std::numeric_limits<T>::is_signed << '\n';
}

void layout() {
    layout_line<signed char>("schar");
    layout_line<unsigned char>("uchar");
    layout_line<short>("short");
    layout_line<unsigned short>("ushort");
    layout_line<int>("int");
    layout_line<unsigned int>("uint");
    layout_line<long>("long");
    layout_line<unsigned long>("ulong");
    layout_line<long long>("ll");
    layout_line<unsigned long long>("ull");

}

template<std::size_t N>
void run(char** argv) {
    const std::string mode = argv[1];
    const std::string kind = argv[3];
    const bool stream_api = std::string(argv[4]) == "stream";
    const std::string transport = argv[5];
    const char* path = argv[6];
    if (mode == "output") {
        output<N>(kind, std::string(argv[4]) == "flush", transport, path);
    } else {
        with_input<N>(transport, path, [&](FastIn<N>& input) {
            if (mode == "numbers") dispatch_numbers(input, kind, stream_api);
            else if (mode == "mixed") mixed(input, stream_api);
            else if (mode == "text" && kind == "char") text<char>(input, stream_api);
            else if (mode == "text" && kind == "string") text<std::string>(input, stream_api);
            else throw std::runtime_error("unknown input mode");
        });
    }
}

int main(int argc, char** argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "layout") {
            layout();
            return 0;
        }
        require(argc == 7, "incorrect fixture argument count");
        const std::string buffer = argv[2];
        if (buffer == "default") run<65536>(argv);
        else if (buffer == "7") run<7>(argv);
        else if (buffer == "1") run<1>(argv);
        else if (buffer == "20") run<20>(argv);
        else if (buffer == "21") run<21>(argv);
        else throw std::runtime_error("unknown buffer size");
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "fixture: " << error.what() << '\n';
        return 1;
    }
}
'''


TYPE_NAMES = (
    "schar", "uchar", "short", "ushort", "int", "uint", "long", "ulong",
    "ll", "ull",
)
BUFFERS = ("default", "7", "1", "20", "21")
WHITESPACE = b" \t\r\n\v\f"
LONG_PATTERN = b"Ab9_-XYZ0123456789"
LONG_SIZE = 2 * 1024 * 1024
LONG_TOKEN = (LONG_PATTERN * (LONG_SIZE // len(LONG_PATTERN) + 1))[:LONG_SIZE]


def excerpt(data: bytes, limit: int = 3000) -> str:
    text = data[:limit].decode("utf-8", errors="backslashreplace")
    if len(data) > limit:
        text += f"\n... ({len(data) - limit} more bytes)"
    return text


def difference(expected: bytes, actual: bytes) -> str:
    position = next((i for i, (a, b) in enumerate(zip(expected, actual)) if a != b),
                    min(len(expected), len(actual)))
    begin, end = max(0, position - 40), position + 100
    return (f"first difference at byte {position}; lengths: expected={len(expected)}, "
            f"actual={len(actual)}\n"
            f"  expected[{begin}:{end}]: {expected[begin:end]!r}\n"
            f"  actual  [{begin}:{end}]: {actual[begin:end]!r}")


class Runner:
    def __init__(self, binary: Path, temp: Path, timeout: float, sanitize: bool):
        self.binary = binary
        self.temp = temp
        self.timeout = timeout
        self.total = 0
        self.failed = 0
        self.env = os.environ.copy()
        if sanitize:
            # Do not let recoverable UBSan reports count as passing tests.
            self.env["ASAN_OPTIONS"] = "detect_leaks=1:halt_on_error=1"
            self.env["UBSAN_OPTIONS"] = "halt_on_error=1:print_stacktrace=1"

    def failure(self, name: str, detail: str) -> None:
        self.failed += 1
        if self.failed <= 20:
            print(f"FAIL: {name}\n{detail}", file=sys.stderr)
        elif self.failed == 21:
            print("Further failure details suppressed (20 already shown).", file=sys.stderr)

    def invoke(self, name: str, arguments: list[str], data: bytes = b"") -> bytes | None:
        self.total += 1
        try:
            result = subprocess.run(
                [str(self.binary), *arguments], input=data, capture_output=True,
                timeout=self.timeout, env=self.env, check=False,
            )
        except subprocess.TimeoutExpired as error:
            self.failure(name, f"timeout after {self.timeout:g}s\n{excerpt(error.stderr or b'')}")
            return None
        except OSError as error:
            self.failure(name, str(error))
            return None
        if result.returncode or result.stderr:
            self.failure(name, f"exit={result.returncode}\nstderr:\n{excerpt(result.stderr)}"
                         f"\nstdout:\n{excerpt(result.stdout)}")
            return None
        return result.stdout

    def input_case(self, name: str, mode: str, buffer: str, kind: str,
                   api: str, transport: str, data: bytes, expected: bytes) -> None:
        path = self.temp / "input.bin"
        if transport == "file":
            path.write_bytes(data)
        actual = self.invoke(name, [mode, buffer, kind, api, transport, str(path)],
                             data if transport == "stdio" else b"")
        if actual is not None and actual != expected:
            self.failure(name, difference(expected, actual))

    def output_case(self, name: str, buffer: str, api: str, flushing: str,
                    transport: str, expected: bytes) -> None:
        path = self.temp / "output.bin"
        if path.exists():
            path.unlink()
        stdout = self.invoke(name, ["output", buffer, api, flushing, transport, str(path)])
        if stdout is None:
            return
        if transport == "file":
            if stdout:
                self.failure(name, "redirected stdout unexpectedly wrote to the capture pipe")
                return
            try:
                actual = path.read_bytes()
            except OSError as error:
                self.failure(name, str(error))
                return
        else:
            actual = stdout
        if actual != expected:
            self.failure(name, difference(expected, actual))


def integer_corpus(minimum: int, maximum: int, seed: int) -> tuple[bytes, bytes]:
    values = [minimum, maximum, 0, 1, maximum - 1, minimum + 1]
    if minimum < 0:
        values.extend([-1, -9, -10, -99, -100])
    for power in range(1, len(str(maximum))):
        for value in (10 ** power - 1, 10 ** power, 10 ** power + 1):
            if value <= maximum:
                values.append(value)
            if minimum <= -value and minimum < 0:
                values.append(-value)
    rng = random.Random(seed)
    values.extend(rng.randint(minimum, maximum) for _ in range(80))
    tokens = [str(value) for value in values]
    # Zero with either sign is in range even for unsigned target types.
    tokens.extend(["0", "-0", "+0", "000000", "-000", "+000", "+00001"])
    for index, value in enumerate(values[:40]):
        if value >= 0:
            tokens.append("+" + "0" * (index % 9) + str(value))
        else:
            tokens.append("-" + "0" * (index % 9) + str(-value))
    separators = (b" ", b"\r\n", b"\t", b"\v", b"\f", WHITESPACE)
    parts = [WHITESPACE]
    for index, token in enumerate(tokens):
        if index:
            parts.append(separators[index % len(separators)])
        parts.append(token.encode("ascii"))
    # Deliberately no trailing whitespace: the final token must succeed at EOF.
    data = b"".join(parts)
    expected = b"".join(f"{int(token)}\n".encode("ascii") for token in tokens)
    return data, expected


def text_expected(tokens: list[bytes]) -> bytes:
    return b"".join(str(len(token)).encode("ascii") + b":" + token + b"\n"
                    for token in tokens)


def output_expected(bounds: dict[str, tuple[int, int]], flushing: str,
                    buffer: str) -> bytes:
    width = 65536 if buffer == "default" else int(buffer)
    paddings = (0, 1, max(0, width - 20), max(0, width - 19), width - 1, width)
    result = []
    for padding in paddings:
        for value in (bounds["ll"][0], bounds["ull"][1]):
            result.append(b"~" * padding + f"{value}\n".encode("ascii"))
    result.extend([b"X:string|cstr|VIEW|01\n", b"A\0BC\0D\n"])
    for name in TYPE_NAMES:
        minimum, maximum = bounds[name]
        result.append(f"{minimum},{maximum}\n".encode("ascii"))
    result.extend([b"0,-1,42\n", LONG_TOKEN, b"\nchain!\n"])
    result.append(b"|after-flush|\n" if flushing == "flush" else b"|destructor|\n")
    return b"".join(result)


def run_tests(runner: Runner) -> None:
    layout = runner.invoke("standard integer layout", ["layout"])
    if layout is None:
        return
    try:
        bounds = {}
        for line in layout.decode("ascii").splitlines():
            name, digits_text, signed_text = line.split()
            digits, signed = int(digits_text), int(signed_text)
            if name in bounds or digits < 1 or signed not in (0, 1):
                raise ValueError("invalid or duplicate integer layout")
            bounds[name] = (-(1 << digits) if signed else 0, (1 << digits) - 1)
        if tuple(bounds) != TYPE_NAMES:
            raise ValueError("unexpected integer layout names/order")
    except (ValueError, UnicodeError) as error:
        runner.failure("standard integer layout", f"{error}\n{excerpt(layout)}")
        return

    short_tokens = [b"a", b"bcdefgh", b"0123456789abcdef", b"Z" * 65539,
                    b"last-token"]
    short_data = WHITESPACE + WHITESPACE.join(short_tokens)
    long_tokens = [b"prefix", LONG_TOKEN, b"suffix"]
    long_data = b"\r\n" + b"\r\n\t".join(long_tokens)
    # Each char read consumes one non-whitespace byte, not an entire token.
    char_data = WHITESPACE + b"abcdefg HIJKLMNOP\r\n\t09!?xyz"
    char_expected = b"".join(f"{byte}\n".encode("ascii") for byte in char_data
                             if byte not in WHITESPACE)
    ll_min = bounds["ll"][0]
    mixed_data = b" \r\n+00042\tabcdefghijk\r\n-0\v" + str(ll_min).encode("ascii")
    mixed_expected = f"42\na\nb\ncdefghijk\n0\n{ll_min}\n".encode("ascii")

    for buffer in BUFFERS:
        for api in ("direct", "stream"):
            for transport in ("stdio", "file"):
                label = f"buffer={buffer} api={api} transport={transport}"
                for index, name in enumerate(TYPE_NAMES):
                    data, expected = integer_corpus(*bounds[name], seed=20261014 + index)
                    runner.input_case(f"integers/{name} {label}", "numbers", buffer,
                                      name, api, transport, data, expected)
                runner.input_case(f"characters {label}", "text", buffer, "char", api,
                                  transport, char_data, char_expected)
                runner.input_case(f"string/boundaries {label}", "text", buffer, "string",
                                  api, transport, short_data, text_expected(short_tokens))
                runner.input_case(f"string/2MiB {label}", "text", buffer, "string", api,
                                  transport, long_data, text_expected(long_tokens))
                runner.input_case(f"mixed/chaining {label}", "mixed", buffer, "unused",
                                  api, transport, mixed_data, mixed_expected)
                for data, eof_name in ((b"", "empty"), (WHITESPACE * 3, "whitespace")):
                    for mode, kind in (("numbers", "int"), ("text", "char"),
                                       ("text", "string")):
                        runner.input_case(f"EOF/{eof_name}/{kind} {label}", mode, buffer,
                                          kind, api, transport, data, b"")
                width = 65536 if buffer == "default" else int(buffer)
                zeros = b"0" * 131073
                for kind, values in (("ll", (0, 1, bounds["ll"][0])),
                                     ("ull", (0, 1, bounds["ull"][1]))):
                    tokens = [b"-" + zeros, b"+" + zeros + b"1"]
                    value = values[-1]
                    tokens.append((b"-" if value < 0 else b"+") + zeros
                                  + str(abs(value)).encode("ascii"))
                    runner.input_case(f"integers/long-leading-zero/{kind} {label}",
                                      "numbers", buffer, kind, api, transport,
                                      b"\r\n".join(tokens),
                                      b"".join(f"{v}\n".encode("ascii") for v in values))
                    # Place every possible internal digit split at a refill
                    # boundary, independently of preceding token lengths.
                    token = str(value).encode("ascii")
                    data = bytearray()
                    for split in range(1, len(token)):
                        padding = (width - split - len(data) % width) % width
                        data.extend(b" " * (padding or width))
                        data.extend(token + b"\r\n")
                    runner.input_case(f"integers/all-chunk-splits/{kind} {label}",
                                      "numbers", buffer, kind, api, transport,
                                      bytes(data),
                                      f"{value}\n".encode("ascii") * (len(token) - 1))
                # Number, character, and string ending exactly at a refill boundary.
                for data, mode, kind, expected in (
                    (b" " * (width - 1) + b"7", "numbers", "int", b"7\n"),
                    (b" " * (width - 1) + b"x", "text", "string", b"1:x\n"),
                    (b" " * (width - 1) + b"x", "text", "char", b"120\n"),
                ):
                    runner.input_case(f"EOF/exact-buffer/{kind} {label}", mode, buffer,
                                      kind, api, transport, data, expected)
        for api in ("direct", "stream"):
            for flushing in ("flush", "destructor"):
                for transport in ("stdio", "file"):
                    label = (f"output buffer={buffer} api={api} "
                             f"{flushing} transport={transport}")
                    runner.output_case(label, buffer, api, flushing, transport,
                                       output_expected(bounds, flushing, buffer))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cxx", default="g++", help="C++ compiler executable (default: g++)")
    parser.add_argument("--sanitize", action="store_true",
                        help="build with AddressSanitizer and UndefinedBehaviorSanitizer")
    parser.add_argument("--timeout", type=float, default=60,
                        help="timeout per fixture process in seconds (default: 60)")
    parser.add_argument("--compile-timeout", type=float, default=180,
                        help="compiler timeout in seconds (default: 180)")
    args = parser.parse_args()
    if args.timeout <= 0 or args.compile_timeout <= 0:
        parser.error("timeouts must be positive")
    header = Path(__file__).resolve().parent.parent / "fastio.hpp"
    if not header.is_file():
        print(f"FAIL: compilation\nHeader not found: {header}", file=sys.stderr)
        print("FAIL: 0 runtime cases; 1 compilation failure")
        return 1

    with tempfile.TemporaryDirectory(prefix="fastio-tests-") as directory:
        temp = Path(directory)
        source, binary = temp / "fixture.cpp", temp / "fixture"
        source.write_text(CPP, encoding="utf-8")
        flags = ["-Wall", "-Wextra"]
        if args.sanitize:
            flags += ["-O1", "-g", "-fsanitize=address,undefined",
                      "-fno-sanitize-recover=all", "-fno-omit-frame-pointer"]
        else:
            flags += ["-O2"]
        compilations = 0
        # Compile both dialects so the concept checks also cover GNU's extended
        # integral traits. Runtime cases use the strict C++20 executable.
        for standard in ("c++20", "gnu++20"):
            target = binary if standard == "c++20" else temp / "fixture-gnu"
            command = [args.cxx, f"-std={standard}", *flags,
                       "-I", str(header.parent.parent), "-I", str(header.parent),
                       str(source), "-o", str(target)]
            try:
                build = subprocess.run(command, capture_output=True, check=False,
                                       timeout=args.compile_timeout)
            except (OSError, subprocess.TimeoutExpired) as error:
                detail = str(error)
                if isinstance(error, subprocess.TimeoutExpired):
                    detail += "\n" + excerpt(error.stderr or b"")
                print(f"FAIL: compilation ({standard})\n{detail}", file=sys.stderr)
                print(f"FAIL: 0 runtime cases; {compilations} successful compilations; "
                      "1 compilation failure")
                return 1
            if build.returncode:
                print(f"FAIL: compilation ({standard}, exit={build.returncode})\n"
                      f"{excerpt(build.stdout + build.stderr, 12000)}", file=sys.stderr)
                print(f"FAIL: 0 runtime cases; {compilations} successful compilations; "
                      "1 compilation failure")
                return 1
            compilations += 1

        runner = Runner(binary, temp, args.timeout, args.sanitize)
        run_tests(runner)
        passed = runner.total - runner.failed
        status = "FAIL" if runner.failed else "PASS"
        print(f"{status}: {runner.total} cases; {passed} passed, {runner.failed} failed; "
              f"{compilations} successful compilations")
        return 1 if runner.failed else 0


if __name__ == "__main__":
    sys.exit(main())
