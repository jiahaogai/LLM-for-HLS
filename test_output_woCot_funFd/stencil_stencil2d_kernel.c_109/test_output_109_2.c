#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
      for (k = -pad; k <= 8 - pad; k++) {
        t += filter[k + pad] * orig[i * 64 + (j * 8 + k)];
      }
      sol[i * 64 + j * 8] = t;
    }
  }
}