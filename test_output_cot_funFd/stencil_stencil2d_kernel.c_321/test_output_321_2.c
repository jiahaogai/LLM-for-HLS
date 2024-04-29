Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 128 - 1; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        idx = (i + off[k].i) * 128 + j + off[k].j;
        s += filter[k] * orig[idx];
      }
      sol[i * 128 + j] = s;
    }
  }
//#pragma endscop
}