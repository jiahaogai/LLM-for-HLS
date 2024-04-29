#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8192; j++) {
      flit = 0;
      
#pragma ACCEL PARALLEL reduction = flit FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        flit += orig[i + ((k - 4) * 8192)] * filter[k];
      }
      sol[j] = flit;
    }
  }
}