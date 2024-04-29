#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int temp;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (r = 2; r < 128 - 2; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 2; c < 64 - 2; c++) {
      temp = 0;
      mul = 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k2 = 0; k2 < 9; k2++) {
        
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{4}
	for (k1 = 0; k1 < 9; k1++) {
          mul = mul * filter[k1 * 9 + k2];
        }
        temp = temp + orig[r * 64 + c] * mul;
      }
      sol[r * 64 + c] = temp;
    }
  }
}