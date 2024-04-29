#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8176; j++) {
      result = ((8192 * (filter[0] - 1)) / 2) + filter[0] - 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 8192; k++) {
        if ((((8192 * (filter[0] - 1)) / 2) + k) < 0) {
          result += filter[0] - 1;
        }
         else {
          if ((((8192 * (filter[0] - 1)) / 2) + k) > 8191) {
            result += 8192 - filter[0];
          }
           else {
            result += orig[((8192 * (filter[0] - 1)) / 2) + k];
          }
        }
      }
      sol[((8192 * (filter[0] - 1)) / 2) + j] = result;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8176; j++) {
      result = ((8192 * (filter[0] - 1)) / 2) + filter[0] - 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 8192; k++) {
        if ((((8192 * (filter[0] - 1)) / 2) + k) < 0) {
          result += filter[0] - 1;
        }
         else {
          if ((((8192 * (filter[0] - 1)) / 2) + k) > 8191) {
            result += 8192 - filter[0];
          }
           else {
            result += sol[((8192 * (filter[0] - 1)) / 2) + k];
          }
        }
      }
      orig[((8192 * (filter[0] - 1)) / 2) + j] = result;
    }
  }
}