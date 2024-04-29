#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    int ellpack_2_size = 10;
    int ellpack_2_limit = i + 10;
    int ellpack_2_col = 0;
    int ellpack_2_stop = 0;
    if (ellpack_2_limit > 494) {
      ellpack_2_stop = 494;
    }
    else {
      ellpack_2_stop = ellpack_2_limit;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = i; j < ellpack_2_stop; j++) {
      while ((((int )*cols) < ((int )0)) && (j < ellpack_2_limit)) {
        cols += 1;
        nzval += 1;
      }
      ellpack_2_col = ((int )*cols);
      if (((int )*cols) == ((int )0)) {
        break;
      }
      sum += ((double )*nzval) * vec[ellpack_2_col];
      nzval += 1;
    }
    out[i] = sum;
  }
}