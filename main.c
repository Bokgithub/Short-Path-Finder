#include "module.h"
# define num 10
int main() {
  MinimumHopPath(7, 1);
  ShortestTimePath(7, 1);

  printf("======================\n");
  MinimumHopPath(5, 2);
  ShortestTimePath(5, 2);

  printf("======================\n");
  MinimumHopPath(2, 5);
  ShortestTimePath(2, 5);

  

  /*
    Printed Output

  Minimum hop path: 7 0 5 1
  # of hops : 3
  Shortest time path: 7 0 5 1
  Total time : 23
  ======================
  Minimum hop path: 5 2
  # of hops : 1
  Shortest time path: 5 4 2
  Total time : 10
  ======================
  Minimum hop path: 2 5
  # of hops : 1
  Shortest time path: 2 4 5
  Total time : 10

  */

  return 0;
}