#include <vector>
#include <algorithm>
#include <cmath>

void trova_devstd(const char* filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Errore nell'apertura del file." << std::endl;
        return;
    }

    // Leggi tutti i dati in un vettore
    std::vector<double> dati ;
    double x;
    
    while (infile >> x) {
        dati.push_back(x);
       
    }
   
    infile.close();
   
    
    if (dati.empty()) {
        std::cerr << "File vuoto." << std::endl;
        return;
    }

    // Calcola min, max e range
    auto [min, max] = std::minmax_element(dati.begin(), dati.end());
    double range = *max - *min;

    // Calcola numero di bin con la regola di Sturges
    int n = dati.size();
    int nBins = std::ceil(1 + std::log2(n));

    // Crea l’istogramma con i parametri calcolati
    TH1F* hist = new TH1F("hist", "Istogramma auto;Valore;Conteggi", nBins, *min, *max);


    hist->SetFillColor(40); 

    // Riempi l’istogramma
    for (double val : dati) {
        hist->Fill(val);
    }

    // Disegna e fitta
    TCanvas* c1 = new TCanvas("c1", "Fit Gaussiana", 800, 600);

    hist->Draw();
   

    TF1* gauss = new TF1("gauss", "gaus", *min, *max);
    hist->Fit(gauss, "R");

    double sigma = gauss->GetParameter(2);
    std::cout << "Deviazione standard (sigma): " << sigma << std::endl;
}
