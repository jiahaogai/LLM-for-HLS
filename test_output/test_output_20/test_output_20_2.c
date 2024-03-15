 This option will create 4 computation threads.
 #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
  for (tj = 0;tj < 40;tj++) {
     tmp = 0.0;
     sim = 0.0;
     SUM_SIM: for (jt = 0;jt < 40;jt++) {
        if (tj == jt) {
          continue;
        }
        delta_ij = space[tj] - space[jt];
        SIMM_IJ: for (i = 0;i < 30;i++) {
          SIMM_J = 30 + 0;
          if (i == SIMM_J) {
            goto SIMM_J_END;
          }
          delta_si = li[i] - space[jt];
          simi = 0.0;
          SIMI_IJ: for (j = 0;j < 30;j++) {
            if (i == j) {
              continue;
            }
            delta_sj = lj[j] - space[jt];
            inner_simi = (delta_ij * delta_si) + (delta_sj * delta_sj);
            simi += exp(inner_simi);
          }
//#pragma ACCEL PARALLEL reduction=simi FACTOR=auto{__PARA__L2}
	  for (j = 0; j < 30; j++) {
            delta_sj = lj[j] - space[jt];
            inner_simi = (delta_ij * delta_si) + (delta_sj * delta_sj);
            simi += exp(inner_simi);
          }
        SIMM_J = 30 + 1;
        SIMM_J_END:;
        }
        simj = 0.0;
        SUM_SIMJ: for (j = 0;j < 30;j++) {
          delta_sj = lj[j] - space[tj];
          inner_simj = (delta_ij * delta_sj) + (delta_si * delta_sj);
          simj += exp(inner_simj);
        }
//#pragma ACCEL PARALLEL reduction=simj FACTOR=auto{__PARA__L3}
	for (j = 0; j < 30; j++) {
          delta_sj = lj[j] - space[tj];
          inner_simj = (delta_ij * delta_sj) + (delta_si * delta_sj);
          simj += exp(inner_simj);
        }
        sim = simi * simj;
        tmp += sim;
      }
      lspace[tj] = space[tj] + (a * (log(tmp) - sim));
    }
    tj = 39 + 0;
    tj_end = 39 + 1;
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (tj = 39 + 0;tj < 39 + 1;tj++) {
    space[tj] = lspace[tj];
  }
}
