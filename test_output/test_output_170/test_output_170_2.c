
  #pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  for (i = 16; i < 24; i++) {
    tmp = 1.0;
    sum = e[i];
    for (j = 0; j < 20; j++) {
      tmp = tmp * r[j];
      sum = sum + offset[i] * v[j] * tmp;
    }
    e[i] = sum;
  }
}
