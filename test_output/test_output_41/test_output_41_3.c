
 #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  for (j = 1; j <= 32; j++) {
/* Standardize from: for(k = 1...
     Standardize to: for(k = 1...
     #pragma ACCEL PIPELINE auto{__PIPE__L1}
     for (k = 1; k <= 32; k++) {
      e = a[j] - b[k];
      d = c[j] - d[k];
      product = e * d;
      f[k] += product;
      g[j] += e * f[k];
      h[k] += d * f[k];
     }
     */
#pragma ACCEL PIPELINE auto{__PIPE__L2}
     for (k = 1; k <= 32; k++) {
      e = a[j] - b[k];
      d = c[j] - d[k];
      product = e * d;
      f[k] += product;
      g[j] += e * f[k];
      h[k] += d * f[k];
     }
    }
   }
  }
  ttmp = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (k = 1; k <= 32; k++) {
    ttmp += ((double )h[k]);
  }
  
#pragma ACCEL ENDASSEMBLY
}
