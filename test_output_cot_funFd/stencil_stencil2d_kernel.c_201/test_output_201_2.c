Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8186; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 8; k++) {
        result += filter[k] * orig[i + (-4 + k)](j + (-4 + k));
      }
      sol[i](j) = result;
    }
  }
}