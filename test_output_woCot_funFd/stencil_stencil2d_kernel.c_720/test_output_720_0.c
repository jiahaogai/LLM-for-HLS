#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        buf += filter[k] * orig[i + ((k - 4) > 0 ? (k - 4) : 0) + ((k - 4) < 0 ? -(k - 4) : 0) * 8192 + j + ((k - 4) > 0 ? (k - 4) : 0) + ((k - 4) < 0 ? -(k - 4) : 0)];
      }
      sol[i * 8192 + j] = buf;
    }
  }
}