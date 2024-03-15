
5. Mark the following loop as a parallelized loop : 
   
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
   for (j = 1; j <= 20; j++) {
      b[j] = b[j] + 1.0;
    }

6. Mark the following loop as a parallelized loop : 
   
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
   for (i = 1; i < 120; i++) {
      s[i] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 20; j++) {
         s[i] = s[i] + a[i][j] * b[j];
      }
    }

