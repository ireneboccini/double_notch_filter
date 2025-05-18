
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "f_ampiezza.h"

void grafico_ampiezza() {
  const char* filenames[4] = {
      "330R analisi in frequenza.txt", "390R analisi in frequenza.txt",
      "470R analisi in frequenza.txt", "560R analisi in frequenza.txt"};

  int colori[4] = {kRed, kBlue, kGreen + 2, kMagenta};

  TCanvas* c1 = new TCanvas("c1", "Ampiezza", 800, 600);
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
    
    gr->SetPointError(j, 0.001226217,  0.000104863); // errore piccolissimoo, va bene?
    }

    gr->SetMarkerStyle(1);
    gr->SetMarkerColor(colori[i]);
    gr->SetLineColor(colori[i]);

   /* 

    double xmin = vx.front();
    double xmax = vx.back();
    */
 TF1* f = new TF1(Form("fit_%d", i), "f_ampiezza", 200, 10000, 8);
      // due parametri: A e R
    f->SetParameter(0, 2.5);  // A
    f->SetParLimits(0, 0.5, 5);
    double R_nominali[4] = {333.33, 389.9, 473.96, 561.53};
    f->SetParameter(1, R_nominali[i]);// R
    f->SetParLimits(1, 330, 562);
f->SetParameter(2, 101.2 * 1e-9 );
f->SetParameter(3, 20.98 * 1e-9 );
f->SetParameter(4, 10.23 * 1e-3);
f->SetParameter(5, 4.651 * 1e-3 );

f->SetParameter(6, 42 );
f->SetParameter(7, 78 );
 f->SetNpx(2000); // per fluidità
  
   
    f->SetLineColor(colori[i]);
    gr->Fit(f, "R");
    f->SetLineWidth(2);
    f->Draw("same");
   
    mg->Add(gr);
    std::cout << "chi quadro ridotto " << i << " :" << f->GetChisquare()/f->GetNDF() << std::endl;
    std::cout << "fit probability " << i << " :" << f->GetProb() << std::endl;
  }
  mg->GetXaxis()->SetRangeUser(200, 10000); 
  mg->Draw("AP");  //"AP"
  mg->SetTitle("Fit ampiezza ; Frequenza [Hz]; Ampiezza [V]");
}
