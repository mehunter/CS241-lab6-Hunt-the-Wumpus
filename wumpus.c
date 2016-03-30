/* Given map, current room, and exit choice, return the room # of the next 
 * room. 
 */
int nextRoom(struct Map* map, int room, int exit)
{
  return room;
}


/* Tests if test room is reachable from the current room in the given map. 
 */
int neighbor(int current, int test, struct Map* map)
{
  return 0;
}


/* Is given path traversable in the given map?
 * Verify that path[i+1] is reachable from path[i]
 */
int validPath(int pathlength, int path[], struct Map* map)
{
  return 0;
}



/* Create a map from an input stream.
 * Input will be in text format, consisting of lines of numbers.
 *   First line has two numbers:
 *   ROOMS: The number of rooms in the map
 *   EXITS: The number of exits per room
 * The next ROOMS lines give the connection information for rooms
 *   outgoing connections.
 *
 * The map is a directed multigraph.
 *   It is possible that room A has an exit to room B
 *     without room B having an exit to room A.
 *   It is possible for a room to connect to itself.
 *   It is possible for multiple exits to connect to the same room.
 */
struct Map* loadMap(FILE* in)
{
  return;
}


/* Free the memory used by the map. */
void freeMap(struct Map* map)
{
  return;
}
