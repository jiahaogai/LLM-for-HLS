#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  stencil_label1:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    stencil_label2:
    for (j = 8; j < 8184; j += 8) {
      flit = ((i - 8) * 8192) + (j - 8);
      row = i - 4;
      col = j - 4;
      sol[flit] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      stencil_label3:
      for (k = 0; k < 9; k++) {
        if ((((row + k) >= 0) && ((row + k) < 8192)) && (((col + (((k + 1) / 3) * 3)) >= 0) && ((col + (((k + 1) / 3) * 3)) < 8192))) {
          sol[flit] += orig[(((row + k) * 8192)) + (col + (((k + 1) / 3) * 3))] * filter[k];
        }
      }
    }
  }
}