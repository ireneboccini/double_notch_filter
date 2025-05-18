
#ifndef F_PHASE_HEADER
#define F_PHASE_HEADER

#include <cmath>

// Funzione teorica da fittare: solo R è variabile
double f_fase(double *x, double *par) {
    double f = x[0];
    double w = 2 * M_PI * f;
    
double R = par[0]; 
 double C1 = par[1];
     double C2 = par[2];
      double L1 = par[3];
      double L2 = par [4];
      double RL1 = par [5];
      double RL2 = par[6];
 

    double x_re = R * (1 - w*w*L2*C2 - w*w*L1*C1 + pow(w,4)*L1*C1*L2*C2 - w*w*C1*C2*RL1*RL2);
    double x_im = R * (w*C2*RL2 + w*C1*RL1 - pow(w,3)*L1*C1*C2*RL2 - pow(w,3)*L2*C2*C1*RL1);
    double z_re = -w*w*L1*C2*RL2 + RL1 - w*w*L2*C2*RL1 - w*w*L2*C1*RL1 + RL2 - w*w*L1*C1*RL2 + x_re;
    double z_im = w*L1 - pow(w,3)*L1*L2*C2 + w*C2*RL2*RL1 + w*L2 - pow(w,3)*L2*L1*C1 + w*C1*RL1 + RL2 + x_im;

    double num = x_im * z_re - x_re * z_im;
    double den = x_re * z_re + x_im * z_im;


    return atan2(num, den) * 180.0 / M_PI; //

}

#endif
