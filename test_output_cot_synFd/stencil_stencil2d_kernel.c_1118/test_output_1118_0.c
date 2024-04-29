#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 398; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 398; j++) {
      t = 0;
      k = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      while (k < 9) {
        t += ((int )filter[k]) * orig[i + ((k / 3) - 1)][j + ((k % 3) - 1)];
        k++;
      }
      sol[i][j] = t;
    }
  }
}