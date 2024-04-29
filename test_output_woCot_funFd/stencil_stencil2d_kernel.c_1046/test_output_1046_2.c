#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int idy;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  loop:for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    vloop:for (j = 1; j < 8191; j++) {
      ti = -4 + i;
      tj = -4 + j;
      idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      vvloop:while (idx < 9) {
        idy = 0;
        
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{32}
        vvvloop:while (idy < 9) {
          result += orig[ti + idx] * orig[tj + idy] * filter[idx * 9 + idy];
          idy++;
        }
        idy = -16 + 8;
      }
      sol[i * 8192 + j] = result;
      idx = -16 + 8;
      result = 0;
    }
    j = -16 + 8;
  }
  i = -16 + 8;
}