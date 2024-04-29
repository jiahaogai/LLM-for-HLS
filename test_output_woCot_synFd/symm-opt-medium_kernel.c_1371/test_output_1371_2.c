- The inner loop is tiled with a tile size of 1 for the `B` array.
- The inner loop is tiled with a tile size of 2 for the `A` array.
- The `A` array is iterated over by a thread team with a team size of 32 and an auto-scheduled task index.
- The `B` array is iterated over by a thread team with a team size of 32 and a static scheduling of 4.
- The `C` array is iterated over by a thread team with a team size of 32 and an auto-scheduled task index.

#pragma ACCEL kernel