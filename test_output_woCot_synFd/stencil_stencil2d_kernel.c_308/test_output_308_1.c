#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k1;
  int k2;
  int r;
  int c;
  int temp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 0; c < 64; c++) {
      temp = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k1 = 0; k1 < 3; k1++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k2 = 0; k2 < 3; k2++) {
          k = k1 * 3 + k2;
          temp += filter[k] * orig[r * 64 + c * 1 + k2];
        }
      }
      sol[r * 64 + c] = temp;
    }
  }
}