//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_GAMEWRAPPER_H
#define ANTWARS_GAMEWRAPPER_H

#include <unistd.h>
#include "game.h"
#include "menu.h"

static std::string INTRO_TEXT = "A N T   W A R S !";
const std::string MAPS_DIR = "../examples/maps";
const std::string SAVES_DIR = "../examples/saves";

class GameWrapper
{
private:
   eGameState m_gameState;
   InputOutput *m_IN_OUT;
   Menu m_menu;
   Game *m_game;

public:
   GameWrapper() : m_IN_OUT(new InputOutput()),
                   m_gameState(GAME_INIT),
                   m_menu(m_IN_OUT, &m_gameState, MAPS_DIR, SAVES_DIR),
                   m_game(NULL)
   {
      m_IN_OUT->ClearAll();
      m_IN_OUT->Animate(Coords(5, 5), INTRO_TEXT, 50000);
      m_IN_OUT->Refresh();
      usleep(500000);
   }

   /*!  Main game cycle. Starting by 'MENU' state.
    */
   void run();
};

#endif //ANTWARS_GAMEWRAPPER_H
