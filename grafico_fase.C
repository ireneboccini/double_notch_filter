
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "f_fase.h"

void grafico_fase() {
    const char* filenames[4] = {"330R analisi in fase.txt", "390R analisi in fase.txt", "470R analisi in fase.txt", "560R analisi in fase.txt"};

    double R_values[4] = {330, 390, 470, 560};
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
        TF1* f = new TF1(Form("f%d", i), f_fase, 1000, 100000, 1);
        f->FixParameter(0, R_values[i]);  // blocca R
        f->SetNpx(2000); // o anche 2000 per più fluidità
        gr->Fit(f, "R");  // fit con range

        mg->Add(gr);
    

    }
    mg->Draw("AP"); //"AP"
    mg->SetTitle("Fit fase ; Frequenza [Hz]; Fase [gradi °]");
}
