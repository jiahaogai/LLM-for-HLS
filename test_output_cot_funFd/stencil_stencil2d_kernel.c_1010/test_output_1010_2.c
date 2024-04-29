`sol[i] = filter[0]*orig[i] + filter[1]*orig[i+1] + ... + filter[8]*orig[i+8]`


for all `i` ranging from 8 to 8192 by steps of 8. The function assumes a contiguous 2D arrangement of the elements of the array.


 

Parameters:
 

`orig`: Input array.
 

`sol`: Output array.
 

`filter`: Kernel.


Requirements:
 

`orig` should be aligned on a 8-byte boundary.
 

`sol` should be aligned on a 8-byte boundary.
 

`filter` should be aligned on a 4-byte boundary.


`orig` should have 8192 elements.
 

`sol` should have 8192 elements.
 

`filter` should have 9 elements.


#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_j:
  for (j = 8; j < 8184; j++) {
    loop_k:
    for (k = 0; k < 9; k++) {
      tmp_orig = orig[j - 4 + k];
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      loop_i:
      for (i = 0; i < 8; i++) {
        tmp += filter[k] * tmp_orig;
        tmp_orig = orig[j - 3 + k - i];
      }
      tmp_sol = sol[j - 8 + k];
      tmp_sol = tmp;
      sol[j - 8 + k] = tmp_sol;
    }
  }
}