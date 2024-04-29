The provided application code is a simple example application used to demonstrate the usage of ACCEL. The provided application code can be compiled and run on various devices. For this code to be executed on a target device, the target device must support all the systems calls used in the application.

 
# pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = ((8192 * (i - 1)) + (j - 1)) * 2;
      for (k = 0; k < 9; k++) {
        result += orig[result + filter[k]] - sol[result + filter[k]];
      }
      sol[result] = result * (-1) + 32768 + (result * 31) / (8192 * 8192);
    }
  }
}