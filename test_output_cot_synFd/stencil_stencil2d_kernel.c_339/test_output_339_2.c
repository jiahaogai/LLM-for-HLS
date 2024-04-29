#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  int xmin = 1;
  int xmax = 8190;
  int ymin = 1;
  int ymax = 8190;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 8190; j++) {
      t = ((filter[0] * orig[i - 1,j - 1]) + (filter[1] * orig[i - 1,j]) + (filter[2] * orig[i - 1,j + 1]) + (filter[3] * orig[i,j - 1]) + (filter[4] * orig[i,j]) + (filter[5] * orig[i,j + 1]) + (filter[6] * orig[i + 1,j - 1]) + (filter[7] * orig[i + 1,j]) + (filter[8] * orig[i + 1,j + 1])) / 41;
      sol[i,j] = t;
    }
  }
}