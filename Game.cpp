#include "Game.hpp"

void Game::initBoard()
{
    char c = '0';
    // Initialize the board with sequential characters starting from '0'
    for (size_t i = 0; i < board.size(); ++i)
    {
        board.at(i) = c + i;
    }
}

/* ************************************************** */
void Game::printBoard() const
{
    // Print each row of the board
    for (size_t i = 0; i < dim; ++i)
    {
        std::cout << "\t";
        for (size_t j = 0; j < dim; ++j)
        {
            std::cout << board.at(i * dim + j) << "\t";
        }
        std::cout << std::endl;
    }
}

/* ************************************************** */
bool Game::checkRowsWinner() const
{
    // Iterate through each row to check if all elements are the same
    for (size_t i = 0; i < board.size(); i += dim)
    {
        bool isWinner = true;
        for (size_t j = 1; j < dim; ++j)
        {
            if (board.at(i) != board.at(i + j))
            {
                isWinner = false;
                break;
            }
        }
        if (isWinner == true)
        {
            return true;
        }
    }
    return false;
}

/* ************************************************** */
bool Game::checkColumnsWinner() const
{
    // Iterate through each column to check if all elements are the same
    for (size_t i = 0; i < dim; ++i)
    {
        bool isWinner = true;
        for (size_t j = i + dim; j < board.size(); j += dim)
        {
            if (board.at(i) != board.at(j))
            {
                isWinner = false;
                break;
            }
        }
        if (isWinner == true)
        {
            return true;
        }
    }
    return false;
}

/* ************************************************** */
bool Game::checkFirstDiagonalWinner() const
{
    size_t firstPos = 0;
    // Check the main diagonal (top-left to bottom-right)
    for (size_t j = dim + 1; j < board.size(); j += dim + 1)
    {
        if (board.at(firstPos) != board.at(j))
        {
            return false;
        }
    }
    return true;
}

bool Game::checkSecondDiagonalWinner() const
{
    size_t firstPos = dim - 1;
    // Check the secondary diagonal (top-right to bottom-left)
    for (size_t j = firstPos + dim - 1; j < board.size() - dim + 1; j += dim - 1)
    {
        if (board.at(firstPos) != board.at(j))
        {
            return false;
        }
    }
    return true;
}

bool Game::checkDiagonalsWinner() const
{
    // Return true if either diagonal has a winning condition
    return checkFirstDiagonalWinner() || checkSecondDiagonalWinner();
}

bool Game::checkWinner() const
{
    // Return true if any row, column, or diagonal has a winning condition
    return checkRowsWinner() || checkColumnsWinner() || checkDiagonalsWinner();
}

/* ************************************************** */
Round Game::generateFirstRound()
{
    // Generate a random number to decide which player starts first.
    std::random_device rd;
    std::uniform_int_distribution<int> dist(static_cast<int>(Round::ROUND_PLAYER1), static_cast<int>(Round::ROUND_PLAYER2));
    int randomValue = dist(rd);
    return static_cast<Round>(randomValue);
}

/* ************************************************** */
bool Game::checkPosition(const size_t &pos, Round &curr_round) const
{
    bool valid = false;
    char curr_sign = (curr_round == Round::ROUND_PLAYER1 ? player1.getSign() : player2.getSign());
    char other_sign = (curr_round == Round::ROUND_PLAYER1 ? player2.getSign() : player1.getSign());

    // Check if the position is within the valid range
    if (pos < board.size())
    {
        // Check if the position is free and not occupied by the other player
        if (board.at(pos) == '0' + pos && board.at(pos) != other_sign)
        {
            valid = true;
        }
        else if (board.at(pos) == other_sign) // The position is occupied by the opponent
        {
            std::cout << "The current cell is already occupied by your opponent!" << std::endl;
        }
        else // The position is occupied by the current player (board.at(pos) != '0' + pos)
        {
            std::cout << "The current cell is already occupied by you!" << std::endl;
        }
    }
    else // The range is not correct
    {
        std::cout << "The position is not valid" << std::endl;
    }
    return valid;
}

/* ************************************************** */
void Game::askPosition(size_t &pos, Round &curr_round)
{
    bool valid = false;
    do
    {
        // Prompt the current player to input a position (0 - 8)
        std::cout << (curr_round == Round::ROUND_PLAYER1
                          ? "Player1(X): "
                          : "Player2(O): ")
                  << "Insert Position(0 - 8) >>";
        if (std::cin >> pos)
        {
            valid = checkPosition(pos, curr_round);
            if (!valid)
            {
                // If the input is invalid, reprint the board for clarity
                printBoard();
            }
        }
        else
        {
            // Clear the error state
            std::cin.clear();
            // Ignore invalid input and flush the input buffer to prevent infinite loops
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number between 0 and 8.\n";
            continue;
        }
    } while (valid == false);
}

/* ************************************************** */
void Game::updateBoard(const size_t &pos, Round &curr_round)
{
    // Update the board at the given position with the current player's sign.
    board[pos] = (curr_round == Round::ROUND_PLAYER1 ? player1.getSign() : player2.getSign());
}

/* ************************************************** */
void Game::updateRound(Round &curr_round)
{
    // Switch the current round to the other player.
    curr_round = (curr_round == Round::ROUND_PLAYER1 ? Round::ROUND_PLAYER2 : Round::ROUND_PLAYER1);
}

/* ************************************************** */
void Game::play()
{
    bool gameOver = false;
    // Randomly determine which player starts first.
    Round curr_round = generateFirstRound();
    size_t moves = 0;

    // Main game loop: continue until the game is over or all board positions are filled.
    while (gameOver == false && moves < board.size())
    {
        std::size_t position;
        // Ask the current player for a move.
        askPosition(position, curr_round);
        // Update the board with the player's move.
        updateBoard(position, curr_round);
        // Print the updated board.
        printBoard();

        // Check if this move resulted in a win.
        if (checkWinner())
        {
            std::cout << "Player "
                      << (curr_round == Round::ROUND_PLAYER1 ? "1" : "2")
                      << " has won!" << std::endl;
            gameOver = true;
            break;
        }
        // Switch to the other player.
        updateRound(curr_round);
        moves++;
    }

    // If no winning condition was met, declare a draw.
    if (gameOver == false)
    {
        std::cout << "Draw!" << std::endl;
    }
}