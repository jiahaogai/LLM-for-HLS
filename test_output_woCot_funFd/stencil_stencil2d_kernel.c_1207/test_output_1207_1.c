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
    j = tid - i * 64;
    row = i - 4;
    col = j - 4;
    sol[tid] = 0;
    
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
    flit:
    for (flit = 0; flit < 9; flit++) {
      int cur = filter[flit];
      int r = row + flit - 4;
      int c = col + flit - 4;
      int index = 0;
      if (r >= 0 && r < 64 && c >= 0 && c < 64) {
        index = r * 64 + c;
      }
      sol[tid] += cur * orig[index];
    }
  }
}