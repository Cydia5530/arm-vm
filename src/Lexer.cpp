//
//  Lexer.cpp
//  virtualmachine
//
//  Created by Jem Tucker on 18/10/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Lexer.h"

#include <string>

namespace {

std::vector<std::string> split_string(const std::string& str, const std::string& delims) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    size_t last = 0;

    do
    {
        // Find next delimiter
        pos = str.find_first_of(delims, pos);
        if (pos == std::string::npos) {
            tokens.push_back(str.substr(last));
        } else if (pos > last) {
            const auto len = (pos++ - last);
            tokens.push_back(str.substr(last, len));
        } else {
            ++pos;
        }

        last = pos;
    } while (pos != std::string::npos);

    return tokens;
}

}

namespace assembler {

const TokenisedInstruction Lexer::tokenize(std::string line) {
    std::vector<std::string> lexed_tokens = split_string(line, ", ");

    TokenisedInstruction instr;

    instr.operation = tokens_to_operation(lexed_tokens);
    instr.condition = tokens_to_condition(lexed_tokens);
    instr.arg_a     = tokens_to_arg_a(lexed_tokens);
    instr.arg_b     = tokens_to_arg_b(lexed_tokens);
    instr.arg_c     = tokens_to_arg_c(lexed_tokens);
    instr.s         = tokens_to_s(lexed_tokens);

    // arg_c should never be empty when arg_b is not, this handles cases such as mov r1, #10
    if (instr.arg_c.size() == 0 && instr.arg_b.size() != 0) {
        instr.arg_c = instr.arg_b;
        instr.arg_b = "";
    }

    return instr;
}

const std::string Lexer::extract_partial_token(std::vector<std::string> tokens, int token_index, int start, int length) {
    int token_min_len = start + length;

    if (tokens.size() > token_index && tokens[token_index].size() >= token_min_len) {
        return tokens[token_index].substr(start, length);
    }

    return "";
}

const std::string Lexer::extract_single_token(std::vector<std::string> tokens, int token_index) {
    if (tokens.size() > token_index) {
        return tokens[token_index];
    }
    return "";
}

const std::string Lexer::tokens_to_operation(std::vector<std::string> tokens) {
    return extract_partial_token(tokens, 0, 0, 3);
}

const std::string Lexer::tokens_to_condition(std::vector<std::string> tokens) {
    return extract_partial_token(tokens, 0, 3, 2);
}

const std::string Lexer::tokens_to_arg_a(std::vector<std::string> tokens) {
    return extract_single_token(tokens, 1);
}

const std::string Lexer::tokens_to_arg_b(std::vector<std::string> tokens) {
    return extract_single_token(tokens, 2);
}

const std::string Lexer::tokens_to_arg_c(std::vector<std::string> tokens) {
    return extract_single_token(tokens, 3);
}

const std::string Lexer::tokens_to_s(std::vector<std::string> tokens) {
    if (tokens_to_condition(tokens) != "") {
        return extract_partial_token(tokens, 0, 5, 1);
    } else {
        return extract_partial_token(tokens, 0, 3, 1);
    }
}


} // namespace assembler
