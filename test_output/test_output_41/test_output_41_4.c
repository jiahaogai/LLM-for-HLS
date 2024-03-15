
 #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
  for (tile_i = 0; tile_i < 8; tile_i++) {
    L1 = 0.0;
    L2 = 0.0;
    L3 = 0.0;
    L4 = 0.0;
    prefetch_array_q_2(tile_i,q_2);

#pragma ACCEL PIPELINE auto{__PIPE__L2}

#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 0; i < 400; i++) {
      L1 += (q_2[i] - p_2[i]) * (q_2[i] - p_2[i]);
      L2 += (q_2[i] - p_1[i]) * (q_2[i] - p_1[i]);
      L3 += (q_2[i] - p_0[i]) * (q_2[i] - p_0[i]);
      L4 += (q_2[i] - p_1[i]) * (q_2[i] - p_0[i]);
    }
  }

  E_2 = L1 + L2;
  SSE = L3 + L4;
//SSE_original = fabs(SSE_original);

  *E = E_2;
  *SSE_in = SSE;
  return;
}
