
5. Mark the following loop as a parallelized one: 
   
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (j = 16; j < 48; j++) {
      e = beta * y[j];
      v = z[j];
      p = q = e;
      
#pragma ACCEL PIPELINE auto{__PIPE__L8}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (i = 0; i < 40; i++) {
        POLYBENCH_POWER_BRAID_2_MULT(p, q, x[i], y[i])
      }
      y[j] = v + p;
      z[j] = q;
    }

