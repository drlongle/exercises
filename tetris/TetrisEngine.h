#pragma once

#include <set>
#include <string>
#include <vector>

/**
 * y-coordinate and height of a vertical block
 */
struct Block {
    Block() = default;
    Block(size_t y_coordinate, size_t block_height)
        : y{y_coordinate}, height{block_height} {}
    size_t y, height;
};

/**
 * A tetris piece that contains multiple contiguous vertical blocks
 */
struct Piece {
    std::vector<Block> blocks;
};

/**
 * Tetris game engine
 */
class TetrisEngine {
  public:
    TetrisEngine(size_t nr_columns) : columns(nr_columns) {}
    void process_line(const std::string &line);
    size_t get_height() const;
    std::set<size_t> get_full_rows() const;

  private:
    void process_entry(const std::string &entry);
    void cross_rows(const std::set<size_t> &rows);
    std::vector<std::vector<size_t>>
        columns; // An array of columns. Each column contains an array of
                 // occupied cells.
};
