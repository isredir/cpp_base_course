#include "minesweeper.h"
#include <set>
#include <tuple>
#include <cstdlib>

static bool operator<(const Minesweeper::Cell &a, const Minesweeper::Cell &b) {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

bool Minesweeper::IsPointOnTable(size_t i, size_t j, size_t y, size_t x) {
    return i + y < height_ && j + x < width_ && i + 1 + y > 0 && j + 1 + x;
}

size_t Minesweeper::CountNeighboursMines(size_t i, size_t j) {
    size_t res = 0;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (IsPointOnTable(i, j, y, x) && table_[i + y][j + x].value == '*') {
                ++res;
            }
        }
    }
    return res;
}

void Minesweeper::Fill() {
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            size_t mines_neighbours = 0;
            if (table_[i][j].value != '*') {
                mines_neighbours = CountNeighboursMines(i, j);
                if (mines_neighbours == 0) {
                    table_[i][j].value = '.';
                } else {
                    table_[i][j].value = mines_neighbours + '0';
                }
            }
        }
    }
}

void Minesweeper::FillStartTable(size_t mines_count, const std::vector<Cell> &cells_with_mines) {
    if (mines_count > width_ * height_) {
        mines_count = width_ * height_;
    }
    std::vector<SmartCell> row = {};
    row.resize(width_, {.value = '-'});
    table_.clear();
    table_.resize(height_, row);
    std::vector<Cell> pairs;
    if (mines_count > 0) {
        for (size_t i = 0; i < height_; ++i) {
            for (size_t j = 0; j < width_; ++j) {
                pairs.push_back({.x = i, .y = j});
            }
        }
    }
    for (size_t i = 0; i < mines_count; ++i) {
        size_t r_num = std::rand() % pairs.size();
        table_[pairs[r_num].y][pairs[r_num].x].value = '*';
        std::swap(pairs[r_num], pairs.back());
        pairs.pop_back();
    }
    if (!cells_with_mines.empty()) {
        for (const Cell &cell : cells_with_mines) {
            table_[cell.y][cell.x].value = '*';
        }
    }
    Fill();
}

void Minesweeper::InitGame(size_t width, size_t height, size_t mines_count) {
    mines_ = mines_count;
    height_ = height;
    width_ = width;
    status_ = GameStatus::NOT_STARTED;
    table_ = {};
    first_click_ = false;
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    InitGame(width, height, mines_count);
    FillStartTable(mines_count, {});
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell> &cells_with_mines) {
    InitGame(width, height, cells_with_mines.size());
    FillStartTable(0, cells_with_mines);
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell> &cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return status_;
}

void Minesweeper::Click() {
    if (!first_click_) {
        status_ = GameStatus::IN_PROGRESS;
        first_click_ = true;
        start_time_ = std::time(nullptr);
    }
}

void Minesweeper::OpenCell(const Cell &cell) {
    Click();
    if (GetGameStatus() != GameStatus::IN_PROGRESS || table_[cell.y][cell.x].is_marked) {
        return;
    }
    if (table_[cell.y][cell.x].value == '*') {
        status_ = GameStatus::DEFEAT;
        for (std::vector<SmartCell> &v : table_) {
            for (SmartCell &c : v) {
                c.is_revealed = true;
            }
        }
        return;
    }

    std::set<Cell> cells;
    cells.insert(cell);
    while (!cells.empty()) {
        std::set<Cell> new_cells = cells;
        for (const Cell &c : new_cells) {
            if (!table_[c.y][c.x].is_marked) {
                table_[c.y][c.x].is_revealed = true;
                ++revealed_;
            }
            cells.erase(c);
            if (table_[c.y][c.x].value == '.') {
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        if (x != y && IsPointOnTable(c.y, c.x, y, x) && !table_[c.y + y][c.x + x].is_revealed) {
                            cells.insert({.x = c.x + x, .y = c.y + y});
                        }
                    }
                }
            }
        }
    }
    if (revealed_ == width_ * height_ - mines_) {
        status_ = GameStatus::VICTORY;
    }
}

void Minesweeper::MarkCell(const Cell &cell) {
    Click();
    if (GetGameStatus() != GameStatus::IN_PROGRESS) {
        return;
    }
    if (table_[cell.y][cell.x].is_marked) {
        table_[cell.y][cell.x].is_marked = false;
    } else if (!table_[cell.y][cell.x].is_revealed) {
        table_[cell.y][cell.x].is_marked = true;
    }
}

time_t Minesweeper::GetGameTime() const {
    std::time_t current_time = std::time(nullptr);
    return current_time - start_time_;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    RenderedField res = {};
    std::string row = {};
    row.resize(width_, '-');
    res.resize(height_, row);
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            if (table_[i][j].is_marked) {
                res[i][j] = '?';
            } else if (table_[i][j].is_revealed) {
                res[i][j] = table_[i][j].value;
            } else {
                res[i][j] = '-';
            }
        }
    }
    return res;
}
