#pragma ACCEL PIPELINE auto{}
 
#pragma ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{126}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}