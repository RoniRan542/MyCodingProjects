#include "game.hpp"

Game::Game(std::string p_name1, std::string p_name2)
{
    Player p1(m_board, BLACK, p_name1, PlayerId::ONE);
    Player p2(m_board, LIGHTGRAY, p_name2, PlayerId::TWO);
    m_players.push_back(p1);
    m_players.push_back(p2);
}
void Game::PlayTurn(int x, int y)
{
    std::cout << "player is: " << m_curr_player << std::endl;
    m_players[!!m_curr_player].MovePlayer(m_board.GetBoard()[x][y], m_board.GetBoard()[x][y]);

    m_curr_player = !m_curr_player;
}
/* void PlayerMove(Player plyr, Pawn &pawn, enum Direction dir, int steps);
void PlayerCapture(Player plyr, Pawn &pawn, enum Direction dir, int steps); */
bool Game::IsValidMove(Pawn pawn, std::pair<u_int32_t, u_int32_t>)
{
    return false;
}
Board Game::GetBoard() const
{
    return m_board;
}
std::vector<Player> Game::GetPlayers() const
{
    return m_players;
}
