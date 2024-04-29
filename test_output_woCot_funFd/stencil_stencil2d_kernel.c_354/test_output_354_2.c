#pragma ACCEL kernel stencil

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        row = ((4 + i) + k);
        col = ((4 + j) + k);
        if ((((row < 0) || (row >= 8192))) || (((col < 0) || (col >= 8192)))) {
          continue;
        }
        t += ((filter[((k + 4) + 4)] * orig[row * 256 + col]));
      }
      sol[i * 256 + j] = t;
    }
  }
}