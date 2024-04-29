#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{13}
 void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      if (((cols[i * 64 + j]) < 494) && (((cols[i * 64 + j]) >= 0) && (nzval[i * 64 + j] != 0.0))) {
        out[i] += nzval[i * 64 + j] * vec[cols[i * 64 + j]];
      }
    }
  }
}