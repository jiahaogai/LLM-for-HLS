

5.  Don't automatically distribute this loop, i.e., don't automatically partition the original problem into smaller regions to be handled by each of the compute nodes.
```c
#pragma ACCEL DISTRIBUTE FACTOR=1
  for (t = 0; t < 40; t++) {
    dt = (t * 5.0) / 4.0;
    dpc = 1.0 / (pow(2.0,dt));
    mul1 = dpc * dpc;
    mul2 = mul1 * dpc;
    expt1 = 2.0 * M_PI * mul1;
    expt2 = 2.0 * M_PI * mul2;
    clear = 0.0;
    qclean = 0.0;
    qg = 0.0;
    qle = 0.0;
    qne = 0.0;
    
#pragma ACCEL PIPELINE auto{off}
    for (j = 0; j < 120; j++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      for (i = 0; i < 120; i++) {
        temp = _in[i * 120 + j];
        ix = dpc * (i - 60.0);
        iy = dpc * (j - 60.0);
        dist = sqrt(ix * ix + iy * iy);
        e_dot_j = e[0] * ix + e[1] * iy;
        e_cross_j_dot_j = e[0] * iy - e[1] * ix;
        b_dot_j = b[0] * ix + b[1] * iy;
        b_cross_j_dot_j = b[0] * iy - b[1] * ix;
        leaky_req = mul1 * temp - dpc * (qlean[i * 120 + j] + qne[i * 120 + j] - qn[i * 120 + j]);
        gain = mul2 * (qclean[i * 120 + j] - qle[i * 120 + j]);
        dqclean_dqle = (qclean[i * 120 + j] * qle[i * 120 + j]) - 1.0;
        dqne_dqn = (qne[i * 120 + j] * qn[i * 120 + j]) - 1.0;
        dqne_dclean = qne[i * 120 + j] - qclean[i * 120 + j];
        dqne_dle = qne[i * 120 + j] - qle[i * 120 + j];
        dqn_dqne = (qn[i * 120 + j] * qne[i * 120 + j]) - 1.0;
        dqn_dclean = qn[i * 120 + j] - qclean[i * 120 + j];
        dqn_dle = qn[i * 120 + j] - qle[i * 120 + j];
        dqle_dqne = qle[i * 120 + j] - qne[i * 120 + j];
        dqle_dclean = qle[i * 120 + j] - qclean[i * 120 + j];
        dqle_dqn = qle[i * 120 + j] - qn[i * 120 + j];
        dqn_dqclean = qn[i * 120 + j] - qclean[i * 120 + j];
        dqn_db = b_cross_j_dot_j * qn[i * 120 + j];
        dqne_db = b_cross_j_dot_j * qne[i * 120 + j];
        dqle_db = b_cross_j_dot_j * qle[i * 120 + j];
        dqclean_dqle = qclean[i * 120 + j] * qle[i * 120 + j];
        dqclean_db = b_dot_j * qclean[i * 120 + j];
        dqne_dqclean = qne[i * 120 + j] * qclean[i * 120 + j];
        dqne_db = (b_dot_j * qne[i * 120 + j] + b_cross_j_dot_j * qne[i * 120 + j]) - mul2 * dqne_dqn;
        dqle_dqne = qle[i * 120 + j] * qne[i * 120 + j];
        dqle_dqclean = qle[i * 120 + j] * qclean[i * 120 + j];
        dqle_db = (b_dot_j * qle[i * 120 + j] + b_cross_j_dot_j * qle[i * 120 + j]) - mul2 * dqle_dqn;
        dqn_db = (b_dot_j * qn[i * 120 + j] + b_cross_j_dot_j * qn[i * 120 + j]) - mul1 * dqn_dqne;
        dqne_dqn = qne[i * 120 + j] * qn[i * 120 + j];
        dqne_dqclean = qne[i * 120 + j] * qclean[i * 120 + j];
        dqne_dclean = qne[i * 120 + j] * dqclean_dqle;
        dqle_dqle = qle[i * 120 + j] * qle[i * 120 + j];
        dqle_dclean = qle[i * 120 + j] * dqclean_dqne;
        dqle_db = (b_dot_j * qle[i * 120 + j] + b_cross_j_dot_j * qle[i * 120 + j]) - mul2 * dqle_dqclean;
        dqn_dqn = qn[i * 120 + j] * qn[i * 120 + j];
        dqn_dqclean = qn[i * 120 + j] * qclean[i * 120 + j];
        dqn_dclean = qn[i * 120 + j] * dqclean_dqne;
        dqne_dclean = qne[i * 120 + j] * dqclean_dqle;
        dqne_db = (b_dot_j * qne[i * 120 + j] + b_cross_j_dot_j * qne[i * 120 + j]) - mul2 * dqne_dqclean;
        dqclean_db = (b_dot_j * qclean[i * 120 + j] + b_cross_j_dot_j * qclean[i * 120 + j]) - mul1 * dqclean_dqne;
        qclean[i * 120 + j] = qclean[i * 120 + j] + leaky_req - gain;
        qne[i * 120 + j] = qne[i * 120 + j] + e_dot_j * (leaky_req - gain) - mul2 * (dqne_dqn + dqne_dclean);
        qle[i * 120 + j] = qle[i * 120 + j] + mul2 * (dqle_dqne + dqle_dclean) - mul2 * (dqle_dqclean + dqle_db);
        qn