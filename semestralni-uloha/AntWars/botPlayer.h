//
// Created by jencmart on 5/27/17.
//

#ifndef ANTWARS_BOTPLAYER_H
#define ANTWARS_BOTPLAYER_H

#include "abstractPlayer.h"
#define CONSIDER_TIME  200000

class BotPlayer : public AbstractPlayer
{
private:
public:
   BotPlayer(Map *map, int playerType) : AbstractPlayer(map, playerType)
   {}

   /*! Collect command from BOT player
    * Bsed on ownerID ( 'e' 'f'  [g,z]\{p} ) different AI strategies are promoted
    * @return
    */
   Command *GetCommand() const override;

   /*! Constantly select first enemy in the enemy list
    * @param myHills
    * @param otherHills
    * @return
    */
   Command *UltraBogoAI(std::list<AntHill *> myHills,std::list<AntHill *> otherHills) const;

   /*! Randomly select my hill, Randomly select other hill. Try create command
    * @param myHills
    * @param otherHills
    * @return
    */
   Command *BogoAI(std::list<AntHill *> myHills,std::list<AntHill *> otherHills) const;

   Command *BetterAI(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                     std::list<AntHill *> emptyHills) const;

   std::list<AntHill *> GetListOfLowestNumOfAntsHills(std::list<AntHill *> myHills) const;

   std::list<AntHill *> GetListOfHighestNumOfAntsHills(std::list<AntHill *> myHills) const;

   void EraseAntHillFromList(AntHill *hill, std::list<AntHill *> &myHills) const;

   std::list<AntHill *> GetListOfClosestHills(AntHill *randHill, std::list<AntHill *> myHills) const;

   int ComputeDistanceBetweenHills(AntHill *randHill, AntHill *other) const;

   Command *Support(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                    std::list<AntHill *> emptyHills) const;

   Command *AttackEmpty(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                        std::list<AntHill *> emptyHills) const;

   Command *Attackenemy1(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                         std::list<AntHill *> emptyHills) const;

   Command *Attackenemy2(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                         std::list<AntHill *> emptyHills) const;
};

#endif //ANTWARS_BOTPLAYER_H
