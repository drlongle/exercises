#include <algorithm>
#include <iterator>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "TetrisEngine.h"

using namespace std;

Piece make_piece(const std::string &entry) {
    Piece piece;
    switch (entry[0]) {
    case 'Q':
        piece.blocks.emplace_back(0, 2);
        piece.blocks.emplace_back(0, 2);
        break;
    case 'Z':
        piece.blocks.emplace_back(1, 1);
        piece.blocks.emplace_back(0, 2);
        piece.blocks.emplace_back(0, 1);
        break;
    case 'S':
        piece.blocks.emplace_back(0, 1);
        piece.blocks.emplace_back(0, 2);
        piece.blocks.emplace_back(1, 1);
        break;
    case 'T':
        piece.blocks.emplace_back(1, 1);
        piece.blocks.emplace_back(0, 2);
        piece.blocks.emplace_back(1, 1);
        break;
    case 'I':
        piece.blocks.emplace_back(0, 1);
        piece.blocks.emplace_back(0, 1);
        piece.blocks.emplace_back(0, 1);
        piece.blocks.emplace_back(0, 1);
        break;
    case 'L':
        piece.blocks.emplace_back(0, 3);
        piece.blocks.emplace_back(0, 1);
        break;
    case 'J':
        piece.blocks.emplace_back(0, 1);
        piece.blocks.emplace_back(0, 3);
        break;
    default:
        throw std::invalid_argument("Invalid entry " + entry);
    }

    return piece;
}

void TetrisEngine::process_line(const std::string &line) {
    for (auto &column : columns) {
        column.clear();
    }

    std::istringstream iss{line};
    std::string entry;
    while (std::getline(iss, entry, ',')) {
        process_entry(entry);
    }
}

void TetrisEngine::process_entry(const std::string &entry) {
    const auto piece{make_piece(entry)};
    size_t x_coordinate = entry[1] - '0';
    size_t offset{0};
    for (size_t i{0}; i < piece.blocks.size(); ++i) {
        auto &column = columns[x_coordinate + i];
        if (column.empty()) {
            continue;
        }
        offset = max(offset, column.back() + 1 - piece.blocks[i].y);
    }

    for (size_t i{0}; i < piece.blocks.size(); ++i) {
        auto &column = columns[x_coordinate + i];
        for (size_t hi = 0; hi < piece.blocks[i].height; ++hi) {
            column.push_back(offset + hi + piece.blocks[i].y);
        }
    }

    while (true) {
        const auto full_rows = get_full_rows();
        if (full_rows.empty()) {
            break;
        }
        cross_rows(full_rows);
    }
}

size_t TetrisEngine::get_height() const {
    size_t height{0};
    for (const auto &column : columns) {
        height = max(height, column.empty() ? 0 : column.back() + 1);
    }

    return height;
};

std::set<size_t> TetrisEngine::get_full_rows() const {
    set<size_t> full_rows;

    const auto height{get_height()};
    const auto nr_columns{columns.size()};
    for (size_t hi{0}; hi < height; ++hi) {
        const size_t counter = std::count_if(
            std::begin(columns), std::end(columns), [hi](const auto &column) {
                auto it = lower_bound(column.begin(), column.end(), hi);
                return (it != std::end(column) && *it == hi);
            });
        if (counter == nr_columns) {
            full_rows.emplace(hi);
        }
    }

    return full_rows;
}

void TetrisEngine::cross_rows(const std::set<size_t> &rows) {
    const auto nr_rows = rows.size();
    if (nr_rows == 0) {
        return;
    }

    for (auto &column : columns) {
        const auto column_size = column.size();
        size_t counter = 1;
        auto write_it = std::lower_bound(std::begin(column), std::end(column),
                                         *rows.begin());
        // Copy the undeleted rows but also move them down by the number of
        // deleted rows.
        for (const auto &row : rows) {
            auto read_it =
                std::upper_bound(std::begin(column), std::end(column), row);
            while (read_it != std::end(column) && rows.count(*read_it) == 0) {
                *write_it = *read_it - counter;
                ++read_it, ++write_it;
            }
            ++counter;
        }
        column.resize(column_size - nr_rows);
    }
}