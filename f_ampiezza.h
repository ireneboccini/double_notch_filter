
#ifndef F_AMP_HEADER
#define F_AMP_HEADER

#include <cmath>

// Funzione teorica da fittare: solo R è variabile
double f_ampiezza(double *x, double *par) {
    double f = x[0];
    double w = 2 * M_PI * f;

    // Parametri fissi (metti i valori reali!)
    double C1 =  101.2 * 1e-9;
    double C2 = 22 * 1e-9 ;
    double L1 = 10 * 1e-3 ;
    double L2 = 4.7 * 1e-3;
    double RL1 = 42;
    double RL2 = 78;

    // Parametro libero: R
    double R = par[0];

    double x_re = R * (1 - w*w*L2*C2 - w*w*L1*C1 + pow(w,4)*L1*C1*L2*C2 - w*w*C1*C2*RL1*RL2);
    double x_im = R * (w*C2*RL2 + w*C1*RL1 - pow(w,3)*L1*C1*C2*RL2 - pow(w,3)*L2*C2*C1*RL1);
    double z_re = -w*w*L1*C2*RL2 + RL1 - w*w*L2*C2*RL1 - w*w*L2*C1*RL1 + RL2 - w*w*L1*C1*RL2 + x_re;
    double z_im = w*L1 - pow(w,3)*L1*L2*C2 + w*C2*RL2*RL1 + w*L2 - pow(w,3)*L2*L1*C1 + w*C1*RL1 + RL2 + x_im;
// H = (x_re + i x_im )/(z_re + z_im)
    double num_re = x_re * z_re + x_im * z_im;
    double num_im = x_im * z_re - x_re * z_im;
    double den = z_re*z_re + z_im*z_im;

    return ( 2.5 * sqrt((num_re*num_re + num_im*num_im) / (den*den))) ; // 2.5 voltaggio, solo un picco ( 5V era il voltaggio picco-picco)
}

#endif
