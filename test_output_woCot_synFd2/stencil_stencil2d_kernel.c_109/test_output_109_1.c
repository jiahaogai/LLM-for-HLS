#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_row;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp_row = 0;
    
#pragma ACCEL PARALLEL reduction=tmp_row FACTOR=auto{16}
    inner:
    for (j = 0; j < 9; j++) {
      filter_elem = filter[j];
      tmp = orig[i + (j - 4)];
      tmp_row += filter_elem * tmp;
    }
    sol[i] = tmp_row;
  }
}