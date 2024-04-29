Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
==> //#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 64 + 1 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 128 + 1 - 1; j++) {
      idx = i * 128 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + 1)) + (filter[2] * (center + 128))) + ((filter[3] * (center - 1)) + (filter[4] * (center - 128)) + (filter[5] * (center - 1 + 128)));
    }
  }
//#pragma endscop
}