**Optimized For:**
 `latency`

**Input:**
 
 - `orig[8192]`: __global__ int
 - `sol[8192]`: __global__ int
 - `filter[9]`: int

**Output:**
 
 - `sol[8192]`: __global__ int

**Inline:**
 - `void stencil_1(int x,int y,int filter[],int result[])`




#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int x;
  int y;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      x = orig[i * 8192 + j];
      int _in_[9] = {orig[i * 8192 + j - 1],orig[i * 8192 + j],orig[i * 8192 + j + 1],orig[(i - 1) * 8192 + j - 1],orig[(i - 1) * 8192 + j],orig[(i - 1) * 8192 + j + 1],orig[(i + 1) * 8192 + j - 1],orig[(i + 1) * 8192 + j],orig[(i + 1) * 8192 + j + 1]};
      
#pragma ACCEL function
      stencil_1(x,_in_,filter,&result);
      sol[i * 8192 + j] = result;
    }
  }
}
#pragma ACCEL kernel

void stencil_1(int x,int _in_[9],int filter[9],int *result)
{
  int i;
  int j;
  int tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{62}
  for (i = 0; i < 9; i++) {
    tmp += filter[i] * _in_[i];
  }
  *result = tmp;
}