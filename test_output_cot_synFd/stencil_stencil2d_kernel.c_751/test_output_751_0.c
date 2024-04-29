#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4 * 8192;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      for (k = -4; k < 5; k++) {
        t += filter[k + 4] * orig[i + k * 64];
      }
      sol[pt + i + j] = t;
    }
  }
}