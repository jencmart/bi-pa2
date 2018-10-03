//
// Created by jencmart on 5/27/17.
//

#include "botPlayer.h"

/// Pokud ti nejde vytvorit cesta, vem nahodne nejake mraveniste nepritele a zautoc

Command *BotPlayer::GetCommand() const
{
   usleep(CONSIDER_TIME);

   while (1)
   {
      std::list<AntHill *> myAntHills;
      std::list<AntHill *> enemyAntHills;

      std::list<AntHill *> emptyAntHills;
      std::list<AntHill *> onlyEnemyAntHills;


      myAntHills = m_map->GetAntHillsByOwner(m_typeID);

      ///get all other than mine
      for (int i = 'e'; i < 'z'; ++i)
      {
         if (m_typeID != i)
         {
            std::list<AntHill *> tmp = m_map->GetAntHillsByOwner(i);
            enemyAntHills.insert(enemyAntHills.end(), tmp.begin(), tmp.end());
         }
      }

      ///get empty
      for (int i = 'e'; i < 'z'; ++i)
      {
         if (i == 'n')
         {
            std::list<AntHill *> tmp = m_map->GetAntHillsByOwner(i);
            emptyAntHills.insert(emptyAntHills.end(), tmp.begin(), tmp.end());
         }
      }

      ///get only enemy, not empty
      for (int i = 'e'; i < 'z'; ++i)
      {
         if (m_typeID != i && i != 'n')
         {
            std::list<AntHill *> tmp = m_map->GetAntHillsByOwner(i);
            onlyEnemyAntHills.insert(onlyEnemyAntHills.end(), tmp.begin(), tmp.end());
         }
      }




      /// ULTRA BOGO BOT PLAYER
      if (m_typeID == 'e')
         return UltraBogoAI(myAntHills, enemyAntHills);

         /// BETTER AI PLAYER
      else
         return BetterAI(myAntHills, onlyEnemyAntHills, emptyAntHills);


   }

   return NULL;
}

Command *BotPlayer::BogoAI(std::list<AntHill *> myHills, std::list<AntHill *> otherHills) const
{
   Command *command;

   while (1)
   {
      ///set iterators
      std::list<AntHill *>::iterator randItOther = otherHills.begin();
      std::list<AntHill *>::iterator randItMine = myHills.begin();

      ///get randIterators
      std::advance(randItOther, std::rand() % otherHills.size());
      std::advance(randItMine, std::rand() % myHills.size());

      ///try to create command
      try
      { command = new Command(*randItMine, *randItOther, m_map); }
      catch (...)
      { continue; }

      return command;
   }
}

Command *BotPlayer::UltraBogoAI(std::list<AntHill *> myHills, std::list<AntHill *> otherHills) const
{
   Command *command;

   for (auto myHill : myHills)
   {
      try
      { command = new Command(myHill, *(otherHills.begin()), m_map); }
      catch (...)
      { continue; }

      return command;
   }

   return NULL;
}


std::list<AntHill *> BotPlayer::GetListOfLowestNumOfAntsHills(std::list<AntHill *> myHills) const
{
   int minAnts = (*myHills.begin())->GetNumOfAnts();

   for (auto hill : myHills)
   {
      if (hill->GetNumOfAnts() < minAnts)
         minAnts = hill->GetNumOfAnts();
   }

   for (auto hillIt = myHills.begin(); hillIt != myHills.end();)
   {
      if ((*hillIt)->GetNumOfAnts() != minAnts)
      {
         hillIt = myHills.erase(hillIt);
      } else
         ++hillIt;
   }

   return myHills;
}


std::list<AntHill *> BotPlayer::GetListOfHighestNumOfAntsHills(std::list<AntHill *> myHills) const
{
   int maxAnts = (*myHills.begin())->GetNumOfAnts();

   for (auto hill : myHills)
   {
      if (hill->GetNumOfAnts() > maxAnts)
         maxAnts = hill->GetNumOfAnts();
   }

   for (auto hillIt = myHills.begin(); hillIt != myHills.end();)
   {
      if ((*hillIt)->GetNumOfAnts() != maxAnts)
      {
         hillIt = myHills.erase(hillIt);
      } else
         ++hillIt;
   }

   return myHills;
}


void BotPlayer::EraseAntHillFromList(AntHill *hill, std::list<AntHill *> &myHills) const
{
   for (auto hillIt = myHills.begin(); hillIt != myHills.end();)
   {
      if ((*hillIt) == hill)
      {
         hillIt = myHills.erase(hillIt);
         break;
      } else
         ++hillIt;
   }
   return;
}


std::list<AntHill *>
BotPlayer::GetListOfClosestHills(AntHill *randHill, std::list<AntHill *> myHills) const
{
   int distance = ComputeDistanceBetweenHills(randHill, *myHills.begin());

   for (auto hill : myHills)
   {
      int tmpDistance = ComputeDistanceBetweenHills(randHill, hill);
      if (tmpDistance < distance)
         distance = tmpDistance;
   }

   for (auto hillIt = myHills.begin(); hillIt != myHills.end();)
   {
      if (ComputeDistanceBetweenHills(randHill, *hillIt) != distance)
      {
         hillIt = myHills.erase(hillIt);
      } else
         ++hillIt;
   }

   return myHills;
}


int BotPlayer::ComputeDistanceBetweenHills(AntHill *from, AntHill *to) const
{
   Path *path = new Path(from, to, m_map);

   int distance = path->PathLength();

   delete path;

   return distance;
}


Command *BotPlayer::Support(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                            std::list<AntHill *> emptyHills) const
{
   Command *command;

   ///IF U HAVE MORE THAN 1 ANTHILL
   if (myHills.size() > 1)
   {
      ///AND IF  SOME OF YOUR ANTHILLS HAVE <10 ANTS
      std::list<AntHill *> lowest = GetListOfLowestNumOfAntsHills(myHills);
      if ((*lowest.begin())->GetNumOfAnts() <= 5)
      {
         ///choose randomly one of them
         std::list<AntHill *>::iterator randLowest = lowest.begin();
         std::advance(randLowest, std::rand() % lowest.size());

         /// in rest of your anthills, find those with most of the ants
         EraseAntHillFromList(*randLowest, myHills);
         std::list<AntHill *> highest = GetListOfLowestNumOfAntsHills(myHills);

         ///from them, find the closest one to the choosen random lowest one
         std::list<AntHill *> closest = GetListOfClosestHills(*randLowest, highest);

         /// if more, choose randomly
         std::list<AntHill *>::iterator randClosest = closest.begin();
         std::advance(randClosest, std::rand() % closest.size());

         /// support your anthill
         command = new Command(*randClosest, *randLowest, m_map);
      }
   }
}


Command *BotPlayer::AttackEmpty(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                                std::list<AntHill *> emptyHills) const
{
   Command *command;

   /// IF EMPTY ANTHILL
   if (emptyHills.size())
   {

      ///choose randomly one of them
      std::list<AntHill *>::iterator randEmpty = emptyHills.begin();
      std::advance(randEmpty, std::rand() % emptyHills.size());

      ////// find anthill with most ants
      std::list<AntHill *> highest = GetListOfHighestNumOfAntsHills(myHills);

      ///from them, find the closest one to the choosen random empty one
      std::list<AntHill *> closest = GetListOfClosestHills(*randEmpty, highest);

      /// if more, choose randomly
      std::list<AntHill *>::iterator randClosest = closest.begin();
      std::advance(randClosest, std::rand() % closest.size());


      /// attack that empty anthill
      try
      {
         command = new Command(*randClosest, *randEmpty, m_map);

      }
      catch (...)
      {
         throw 1;
      }
   } else
      throw 1;


   return command;


}


Command *BotPlayer::Attackenemy1(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                                 std::list<AntHill *> emptyHills) const
{
   Command *command;


   if(! enemyHills.size())
      throw 1;


///find enemy hill with lowest number of ants
   std::list<AntHill *> lowest = GetListOfLowestNumOfAntsHills(enemyHills);
///if more, choose randomly...
   std::list<AntHill *>::iterator randLowest = lowest.begin();
   std::advance(randLowest, std::rand() % lowest.size());

///choose highest numbered anthill
   std::list<AntHill *> highest = GetListOfHighestNumOfAntsHills(myHills);

///if more, find the closest one
   std::list<AntHill *> closest = GetListOfClosestHills(*randLowest, highest);

/// if more, choose randomly
   std::list<AntHill *>::iterator randClosest = closest.begin();
   std::advance(randClosest, std::rand() % closest.size());

///attack enemy anthill with lowest num of ants
   try
   {
      command = new Command(*randClosest, *randLowest, m_map);
   }
   catch (...)
   {
      throw 1;
   }

   return command;
}

Command *BotPlayer::Attackenemy2(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                                 std::list<AntHill *> emptyHills) const
{
   Command *command;

   if(! enemyHills.size())
      throw 1;

   ///choose your anthill with highest number of ants (if more choose randomly)
   ///choose highest numbered anthill
   std::list<AntHill *> highest = GetListOfHighestNumOfAntsHills(myHills);
   ///if more, choose randomly...
   std::list<AntHill *>::iterator randHighest = highest.begin();
   std::advance(randHighest, std::rand() % highest.size());

   ///find closest enemy antHill
   std::list<AntHill *> closest = GetListOfClosestHills(*randHighest, enemyHills);

   /// if more, choose randomly
   std::list<AntHill *>::iterator randClosest = closest.begin();
   std::advance(randClosest, std::rand() % closest.size());


   /// attack closest enemy anthill
   try
   {
      command = new Command(*randHighest, *randClosest, m_map);

   }
   catch (...)
   {
      throw 1;
   }

   return command;
}

double rand_value() { return (double)rand() / RAND_MAX; }


Command *BotPlayer::BetterAI(std::list<AntHill *> myHills, std::list<AntHill *> enemyHills,
                             std::list<AntHill *> emptyHills) const
{
   Command *command = NULL;

   while (1)
   {
      try
      {

         double rand = rand_value();
         if ( rand <= 0.25)
         {
            command =   Support(myHills,enemyHills,emptyHills);
            if(command)
               break;
            continue;
         }

         else if (rand <= 0.5)
         {
            command = AttackEmpty(myHills,enemyHills,emptyHills);
            if(command)
               break;
            continue;
         }

         else if (rand < 0.75)
         {
            command =   Attackenemy1(myHills,enemyHills,emptyHills);
            if(command)
               break;
            continue;
         }

        else
         {
            command =  Attackenemy2(myHills,enemyHills,emptyHills);
            if(command)
               break;
            continue;
         }
      }
      catch (...)
      {
         continue;
      }
   }

   return command;

}




