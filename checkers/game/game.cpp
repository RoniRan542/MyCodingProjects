#include "game.hpp"

Game::Game(std::string p_name1, std::string p_name2)
{
    Player p1(m_board, BLACK, p_name1, PlayerId::ONE);
    Player p2(m_board, LIGHTGRAY, p_name2, PlayerId::TWO);
    m_players.push_back(p1);
    m_players.push_back(p2);
}

void Game::PlayTurns()
{
    bool move_finished = false;
    int retval_start = 0;
    Vector2 src_pos;
    Vector2 dest_pos;
    while (move_finished == false)
    {
        if (retval_start == false)
        {
            if (IsMouseButtonPressed(0))
            {
                src_pos = GetMousePosition();
                if (m_players[!!m_curr_player].ChoosePawn(m_board.GetBoard()[src_pos.x / 120][src_pos.y / 120]) > 0)
                {
                    std::cout << "player " << !!m_curr_player << "chose source successfully. " << std::endl;
                    retval_start = true;
                }
            }
        }
        else
        {
            if (IsMouseButtonPressed(0))
            {
                dest_pos = GetMousePosition();
                if (m_players[!!m_curr_player].MovePlayer(m_board.GetBoard()[src_pos.x / 120][src_pos.y / 120], m_board.GetBoard()[dest_pos.x / 120][dest_pos.y / 120]) > 0)
                {
                    std::cout << "player " << !!m_curr_player << "chose dest " << dest_pos.x / 120 << " and " << dest_pos.y / 120 << std::endl;
                    m_curr_player = !m_curr_player;

                    return;
                }
            }
        }
    }
}
/* void PlayerMove(Player plyr, Pawn &pawn, enum Direction dir, int steps);
void PlayerCapture(Player plyr, Pawn &pawn, enum Direction dir, int steps); */
bool Game::IsValidMove(Pawn pawn, std::pair<u_int32_t, u_int32_t>)
{
    return false;
}
Board &Game::GetBoard()
{
    return m_board;
}
std::vector<Player> Game::GetPlayers() const
{
    return m_players;
}
