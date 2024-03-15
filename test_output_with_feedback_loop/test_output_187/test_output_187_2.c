5. Mark the following loop as a parallelized one: 
   
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
   
#pragma ACCEL PIPELINE auto{__PIPE__L4}
   for (j = 16; j < 40; j++) {
      e = b[j] - sum;
      d = e * f;
      c = g * d;
      h = a[j] + c;
      b[j] = b[j] + e;
      a[j - 16] = a[j - 16] + f * d;
      a[j] = h;
      sum = a[j];
   }