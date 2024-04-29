The error(s) detected are: 
	[Stencil] Processing stencil.c - Failed
#pragma ACCEL kernel



 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 8; j < 8184 + 8; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (i = 8; i < 8192 + 8; i++) {
      sol[i] = ((filter[0] * orig[i - 8]) + (filter[1] * orig[i - 8 + 1]) + (filter[2] * orig[i - 8 + 2]) + (filter[3] * orig[i - 1]) + (filter[4] * orig[i]) + (filter[5] * orig[i + 1]) + (filter[6] * orig[i + 2]) + (filter[7] * orig[i + 8]) + (filter[8] * orig[i + 8 + 1]));
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 8; i < 8192 + 8; i++) {
      orig[i] = sol[i];
    }
  }
}