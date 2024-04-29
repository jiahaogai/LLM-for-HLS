#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int tid;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop:
  for (tid = 0; tid < 8192; tid++) {
    i = tid / 64;
    j = tid % 64;
    row = i - 4;
    col = j - 4;
    sol[tid] = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner1:
    for (flit = 0; flit < 9; flit++) {
      if (((row + flit) >= 0) && ((row + flit) < 64) && ((col) >= 0) && ((col) < 64)) {
        sol[tid] += filter[flit] * orig[((row + flit) * 64) + col];
      }
    }
  }
}