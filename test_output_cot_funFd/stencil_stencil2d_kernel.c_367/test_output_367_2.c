#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int tid;
  int row;
  int col;
  int flatten_col;
  int flatten_row;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (tid = 0; tid < 8192; tid++) {
    i = tid / 64 + 1;
    j = tid % 64 + 1;
    row = tid;
    col = 0;
    int flatten_i = i - 1;
    int flatten_j = j - 1;
    int flatten_tid = flatten_i * 64 + flatten_j;
    inner:
    for (col = 1; col <= 8; col++) {
      int _in = ((flatten_i * 64) + (flatten_j * 1)) + col;
      
#pragma ACCEL PARALLEL reduction = sol{sol[_in]}
      int _out = ((i * 64) + (j * 1)) + col;
      sol[_out] = 0;
      
#pragma ACCEL PARALLEL reduction = sol{sol[_in]}
      for (row = 1; row <= 8; row++) {
        int _in_1 = ((flatten_i * 64) + (row * 8)) + flatten_j;
        sol[_out] += filter[row] * orig[_in_1];
      }
    }
  }
}