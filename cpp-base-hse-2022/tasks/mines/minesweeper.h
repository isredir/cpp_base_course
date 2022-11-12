#pragma once

#include <string>
#include <vector>
#include <ctime>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    struct SmartCell {
        bool is_revealed = false;
        bool is_marked = false;
        char value;
    };
    size_t CountNeighboursMines(size_t i, size_t j);
    void InitGame(size_t width, size_t height, size_t mines_count);
    void Click();
    bool IsPointOnTable(size_t i, size_t j, size_t x, size_t y);
    void Fill();
    void FillStartTable(size_t mines_count, const std::vector<Cell>& cells_with_mines);
    GameStatus status_ = GameStatus::NOT_STARTED;
    size_t width_;
    size_t height_;
    size_t mines_ = 0;
    size_t revealed_ = 0;
    std::vector<std::vector<SmartCell>> table_;
    bool first_click_ = false;
    std::time_t start_time_;
};
