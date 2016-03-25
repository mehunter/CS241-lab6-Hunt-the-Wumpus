#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wumpus.h"

/* Generates a random integer in the range [0, n-1], inclusive. */
int randomInt(int n)
{ 
  int r = rand(); /* r = [0,RAND_MAX] */
  
  /* x = [0, 1) */
  double x = (double)r / ((double)RAND_MAX + 1.0 );
  /* Without +1.0, there is a 1 in RAND_MAX */
  /* chance of returning n. */

  /* return: [0, n-1] */
  return (int)(x*n); 
}

void printLocation(int player, struct Map* map)
{
  int i;
  printf("\nYou are in room %d\n", player);
  printf("There are exits to rooms ");
  for(i = 0; i < map->exitsPerRoom; i++)
  {
    printf("%d ", nextRoom(map, player, i));
  }
  printf("\n");
}

void warnNearHazard(int player, int hazard, struct Map* map, char* msg)
{
  if(neighbor(player, hazard, map))
  {
    printf("%s\n", msg);
  }
}


int main(int argc, char** argv)
{
  int wumpus;
  int pit;
  int bats;
  int player;
  int arrows = 5;
  int gameOn = 1;

  char* mapfile = argc > 1 ? argv[1] : "dodecahedron.map";
  FILE* in;

  struct Map* map;

  long seed = (long)time(NULL);
  srand(seed);

  printf("Loading map from %s\n", mapfile);
  in = fopen(mapfile, "r");
  map = loadMap(in);
  fclose(in);
  printf("loaded map with %d rooms, %d exits/room\n",
         map->rooms, map->exitsPerRoom);

  wumpus = randomInt(map->rooms);
  pit = randomInt(map->rooms);
  bats = randomInt(map->rooms);
  player = randomInt(map->rooms);

  printf("Welcome to Hunt the Wumpus\n");

  while (gameOn)
  {
    printLocation(player, map);

    warnNearHazard(player, wumpus, map, "You smell the wumpus.");
    warnNearHazard(player, pit, map, "You feel the wind from the pit.");
    warnNearHazard(player, bats, map, "You hear bats screeching.");

    if(player == wumpus)
    {
      printf("The wumpus ate you\n");
      gameOn = 0;
    } 
    else if(player == pit)
    {
      printf("You fell in the pit and died\n");
      gameOn = 0;
    }
    else if (player == bats)
    {
      player = randomInt(map->rooms);
      printf("Bats carried you to room %d\n", player);
      bats = randomInt(map->rooms);
    } 
    else
    {
      int read = -1;
      int choice;
      char c;
      
      while(read < 0)
      {
        printf("Shoot or Move? (S/M)\n");
        do
        {
          read = scanf("%c", &c);
          if(read != 1) printf("I'm confused\n");
        } while(c == ' ' || c == '\n' || c == '\t');
      }

      switch(c)
      {
      case 'S':
      case 's':
        if(arrows > 0)
        {
          int distance = 0;
          int rooms[6];
          int i;

          printf("You have %d arrows\n", arrows);
          do
          { 
            printf("How far will you shoot? (1-5)\n");
            read = scanf("%d", &distance);
            if(read != 1) printf("So confused...");
          } while(distance < 1 || distance > 5);
          
          printf("List the rooms where the arrow will go\n");
          rooms[0] = player;
          for(i = 1; i <= distance; ++i)
          {
            read = scanf("%d", &rooms[i]);
            if(read != 1) printf("I don't understand this");
          }

          --arrows;

          if(validPath(distance+1, rooms, map))
          {
            for(i = 0; i <= distance; ++i)
            {
              if(rooms[i] == wumpus)
              {
                printf("Arrow hit the wumpus in room %d\n", rooms[i]);
                printf("You win!\n");
                gameOn = 0;
              }
            }
          }
          else
          {
            printf("Invalid path!\n");
          }

          if(gameOn)
          {
            int wumpusChoice = randomInt(1+map->exitsPerRoom);
            printf("You missed your shot and startled the wumpus.\n");
            printf("It's possible you scared it into moving to another room. \n");
            
            if(wumpusChoice < map->exitsPerRoom)
            {
              wumpus = nextRoom(map, wumpus, wumpusChoice);
            }
          }
        }
        else 
        {
          printf("Sorry, out of arrows!\n");
        }
        break;
      case 'M':
      case 'm':
        printf("Where will you go?\n");
        read = scanf("%d", &choice);
        if(read != 1)
        {
          printf("I don't understand that\n");
        }
        else if(neighbor(player, choice, map))
        {
          printf("Moving to room %d\n", choice);
          player = choice;
        }
        else
        {
          printf("You can't go there from here\n");
        }
        break;
      default:
        printf("I don't understand \"%c\"\n", c);
      }

    } 
  }

  printf("Game Over\n");

  freeMap(map);

  return 0;
}
