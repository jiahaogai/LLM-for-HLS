#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int q;
  int p;
  int pad;
  int pad2;
  int r_col;
  int r_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  pad = 1;
  pad2 = ((pad << 1) + 2);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  r_col = 33;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  r_row = pad2;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (r_row < 65 - pad2) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    r = r_row * 32 + r_col;
    
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{2}
    sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (q = 0; q < 9; q++) {
      p = r + ((q / 3) - 1) * 32 + pad + ((q % 3) - 1);
      sum += filter[q] * orig[p];
    }
    sol[r] = sum;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    r_col++;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    if (r_col == 32) {
      r_col = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      r_row++;
    }
  }
}