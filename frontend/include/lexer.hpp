#ifndef FRONTEND_INCLUDE_LEXER_HPP
#define FRONTEND_INCLUDE_LEXER_HPP

#include <vector>
#include <memory>
#include <string>
#include "token.hpp"
#include "common.hpp"
#include <fstream>
#include <iostream>

namespace language {

class Lexer {
private:
    std::vector<std::unique_ptr<Token>> tokens_{};
    std::string source_{};
    std::size_t i_{0};

public:

    explicit Lexer(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        source_ = std::string(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );
    }

    explicit Lexer(std::string&& source) : source_(std::move(source)) {}

    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;

    Lexer(Lexer&&) noexcept = default;
    Lexer& operator=(Lexer&&) noexcept = default;

    ~Lexer() = default;

    [[nodiscard]] const std::vector<std::unique_ptr<Token>>& 
    get_tokens() const noexcept { return tokens_; }

    void print_source() const {              // for debug
        std::cout << source_ << std::endl;
    }

    void tokenize();
 
private:

    void skip_spaces();
    void check_primitive_tokens();
    void inc() noexcept {++i_;}

};

/*—————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*                                                                                                                 */
/*——————————————————————————————————————————| implementation of methods |——————————————————————————————————————————*/
/*                                                                                                                 */
/*—————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/

inline void Lexer::skip_spaces() {
    char c = source_[i_];
    while (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
        inc();
        c = source_[i_];
    }
}

inline void Lexer::check_primitive_tokens() {
    char c = source_[i_];
    switch (c)
    {
    case '+': {
        tokens_.push_back(std::make_unique<Token_binary_operator>(Binary_operators::operator_add));
        inc();
        break;
    }
    default:
        break;
    }
}


inline void Lexer::tokenize() {
    const std::size_t n = tokens_.size();

    while(i_ < n) {
        skip_spaces();


    }
}

} // namespace language

#endif // FRONTEND_INCLUDE_LEXER_HPP