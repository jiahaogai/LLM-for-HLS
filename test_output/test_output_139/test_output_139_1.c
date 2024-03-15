
 #pragma ACCEL PIPELINE auto{__PIPE__L0}

#pragma ACCEL TILE FACTOR=auto{__TILE__L0}

#pragma ACCEL PARALLEL FACTOR=auto{2}
   for (i = 1; i <= 250; i++) {
      z[i] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (j = 1; j <= 250; j++) {
         z[i] += a[i] * b[j];
      }
   }
}
