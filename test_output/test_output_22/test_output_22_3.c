
 #pragma ACCEL kernel

void kernel_seidel_2d(int orig_A[4096],int sol[4096],int filter[9])
{
  int r;
  int c;
  int r0;
  int r1;
  int r2;
  int r3;
  int r4;
  int r5;
  int r6;
  int r7
  int c0;
  int c1;
  int c2;
  int c3
  int c4;
  int c5;
  int c6;
  int c7
  int flnr;
  int flnc;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 32; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_rc0:
    for (rc0 = 4 * r + 0; rc0 < 4 * r + 3; rc0++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_c0:
      for (c0 = 4 * r + 0; c0 < 4 * r + 3; c0 += 8) {
        temp = orig_A[rc0 * 32 + c0];
        loop_flnr:
        for (flnr = 0; flnr < 3; flnr++) {
          loop_flnc:
          for (flnc = 0; flnc < 3; flnc++) {
            temp += filter[flnr * 3 + flnc] * orig_A[(r0 + flnr) * 32 + c0 + flnc];
          }
        }
        sol[rc0 * 32 + c0] = temp;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    loop_rc1:
    for (rc1 = 4 * r + 1; rc1 < 4 * r + 3; rc1++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      loop_c1:
      for (c1 = 4 * r + 1; c1 < 4 * r + 3; c1 += 8) {
        temp = orig_A[rc1 * 32 + c1];
        loop_flnr_1:
        for (flnr = 0; flnr < 3; flnr++) {
          loop_flnc_1:
          for (flnc = 0; flnc < 3; flnc++) {
            temp += filter[flnr * 3 + flnc] * orig_A[(r1 + flnr) * 32 + c1 + flnc];
          }
        }
        sol[rc1 * 32 + c1] = temp;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    loop_rc2:
    for (rc2 = 4 * r + 2; rc2 < 4 * r + 3; rc2++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      loop_c2:
      for (c2 = 4 * r + 2; c2 < 4 * r + 3; c2 += 8) {
        temp = orig_A[rc2 * 32 + c2];
        loop_flnr_2:
        for (flnr = 0; flnr < 3; flnr++) {
          loop_flnc_2:
          for (flnc = 0; flnc < 3; flnc++) {
            temp += filter[flnr * 3 + flnc] * orig_A[(r2 + flnr) * 32 + c2 + flnc];
          }
        }
        sol[rc2 * 32 + c2] = temp;
      }
    }
  }
}
