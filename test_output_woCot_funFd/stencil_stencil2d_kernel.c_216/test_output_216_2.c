#pragma ACCEL kernel

void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 39; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop:
      for (k = 0; k < 9; k++) {
        idx = i - 4 + ((k >> 6) & 3);
        idy = j - 4 + (k & 3);
        fl = filter[k];
        sol[i][j] += fl * orig[idx][idy];
      }
    }
  }
}