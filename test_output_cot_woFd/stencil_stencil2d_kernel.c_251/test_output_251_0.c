#pragma ACCEL kernel

int orig[8192];
int sol[8192];
int filter[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        int i_tmp;
        int j_tmp;
        i_tmp = i + (-1 + k);
        j_tmp = j + (-1 + k);
        sum += ((orig[i_tmp * 256 + j_tmp] * filter[k]));
      }
      sol[i * 256 + j] = sum;
    }
  }
}