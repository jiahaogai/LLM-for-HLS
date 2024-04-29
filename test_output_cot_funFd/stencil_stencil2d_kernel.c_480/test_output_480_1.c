Code: 
 #include <math.h>
#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int flatten_filter[9];
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  loop_i:
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_j:
    for (j = 1; j < 4; j++) {
      flatten_filter[idx] = filter[i - 1][j - 1];
      idx++;
    }
    loop_k:
    for (idx = 0; idx < 9; ++idx) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_l:
      for (int _in_j_ = (j - 1); _in_j_ <= (j + 1); _in_j_++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loop_m:
        for (int _in_i_ = (i - 1); _in_i_ <= (i + 1); _in_i_++) {
          sol[i][j] += flatten_filter[idx] * orig[_in_i_][_in_j_];
        }
      }
    }
  }
}
#pragma ACCEL kernel

void stencil_1(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int flatten_filter[9];
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  loop_i:
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_j:
    for (j = 1; j < 4; j++) {
      flatten_filter[idx] = filter[i - 1][j - 1];
      idx++;
    }
    loop_k:
    for (idx = 0; idx < 9; ++idx) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_l:
      for (int _in_j_ = (j - 1); _in_j_ <= (j + 1); _in_j_++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loop_m:
        for (int _in_i_ = (i - 1); _in_i_ <= (i + 1); _in_i_++) {
          sol[i][j] += flatten_filter[idx] * orig[_in_i_][_in_j_];
        }
      }
    }
  }
}
#pragma ACCEL kernel

void stencil_2(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int flatten_filter[9];
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACT