
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "f_fase.h"

void grafico_fase() {
    const char* filenames[4] = {"330R fase corretto.txt", "390R fase corretto.txt", "470R fase corretto.txt", "560R fase corretto.txt"};

    double R_values[4] = {333.33, 389.9, 473.96, 561.53};
    int colori[4] = {kRed, kBlue, kGreen+2, kMagenta};

    TCanvas* c1 = new TCanvas("c1", "Fase", 800, 600);
    TMultiGraph* mg = new TMultiGraph();

    for (int i = 0; i < 4; i++) {
        // Carica dati
        std::ifstream file(filenames[i]);
        std::vector<double> vx, vy;
        
        double x, y;
        while (file >> x >> y) {
            vx.push_back(x);
            vy.push_back(y);
        }
        file.close();
        
        int n = vx.size();
        TGraphErrors* gr = new TGraphErrors(n);
        for (int j = 0; j < n; ++j) {
            gr->SetPoint(j, vx[j], vy[j]);
            gr->SetPointError(j, 0.001226217, 2.264 );  // per ora come errore su y ho messo st dev trovata da fit gaus
        }
        
        gr->SetMarkerStyle(1);
        gr->SetMarkerColor(colori[i]);
        gr->SetLineColor(colori[i]);

       // Funzione con parametro R fisso
        TF1* f = new TF1(Form("f%d", i), f_fase, 1000, 100000, 7);
        f->SetParameter(0, R_values[i]);  // blocca R
       f->SetParameter(1, 101.2 * 1e-9 );
f->SetParameter(2, 20.98 * 1e-9 );
f->SetParameter(3, 10.23 * 1e-3);
f->SetParameter(4, 4.651 * 1e-3 );

f->SetParameter(5, 42 );
f->SetParameter(6, 78 );
        f->SetNpx(2000); // per fluidità
 f->SetLineColor(colori[i]);
    gr->Fit(f, "R");
    f->SetLineWidth(2);
    f->Draw("same");

    mg->Add(gr);
    

    }
    mg->Draw("AP"); 
    mg->SetTitle("Fit fase ; Frequenza [Hz]; Fase [gradi °]");
}
