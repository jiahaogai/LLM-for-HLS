ACCEL PIPELINE, ACCEL TILE, and ACCEL PARALLEL directives are used for this purpose.

4. Array Declarations:
   //#pragma ACCEL PIPELINE auto{off}
   
   //#pragma ACCEL TILE FACTOR=auto{126}
   
   //#pragma ACCEL PARALLEL FACTOR=auto{1}
   int orig[8192];
   
   //#pragma ACCEL PIPELINE auto{off}
   
   //#pragma ACCEL TILE FACTOR=auto{126}
   
   //#pragma ACCEL PARALLEL FACTOR=auto{1}
   int sol[8192];
   
   //#pragma ACCEL PIPELINE auto{flatten}
   
   //#pragma ACCEL TILE FACTOR=auto{1}
   
   //#pragma ACCEL PARALLEL FACTOR=auto{8}
   int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};