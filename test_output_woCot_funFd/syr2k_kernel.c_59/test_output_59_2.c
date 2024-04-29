Code: k += alpha * ajk;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{80}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      C[k][j] *= beta;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (k = 0; k < 60; k++) {
      C[k][j] += ajk;
    }
  }
}