// $Id: $
// Include files 

void fillrandom() 
{
  
  TCanvas *c1 = new TCanvas("c1","The FillRandom example",200,10,700,900);

  TPad *pad1 = new TPad("pad1","The pad with a function",0.05,0.50,0.95,0.95,21);
  TPad *pad2 = new TPad("pad2","The pad with a histogram",0.05,0.05,0.95,0.45);

  pad1->Draw();
  pad2->Draw();

  pad1->cd();

  //... Programacion funcional desde version 6.00 - lo ultimo
  //TF1 f1("f1","sin(x)",0,10);
  //TF1 f2("f2","cos(x)",0,10);
  //TF1 fsum("fsum","[&](double *x, double *p){ return p[0]*f1(x) + p[1]*f2(x); }",0,10,2);
  //fsum.SetParameters(10,4);  ///Nota: aqui se hace uso del ".", saben por que?

  auto form1 = new TFormula("form1","abs(sin(x)/x)");
  auto sqroot = new TF1("sqroot","x*gaus(0) + [3]*form1",0,10);
  sqroot->SetParameters(10,4,1,30); //Nota: observen como se pasan los parametros
  
  pad1->SetGridx();
  pad1->SetGridy();
  pad1->GetFrame()->SetFillColor(0);
  pad1->GetFrame()->SetBorderMode(-1);
  pad1->GetFrame()->SetBorderSize(5);
  
  sqroot->SetLineColor(4);
  sqroot->SetLineWidth(6);
  sqroot->Draw();

  auto lfunction = new TPaveLabel(5,39,9.8,46,"Nuestra funcion"); /// Nota: que es "auto" ?
  lfunction->SetFillColor(0);
  lfunction->Draw();
  c1->Update();
  
  gBenchmark->Start("fillrandom");
  
  // A function (any dimension) or a formula may reference
  // an already defined formula

  pad2->cd();
  
  pad2->GetFrame()->SetBorderMode(-1);
  
  pad2->GetFrame()->SetBorderSize(5);
  
  TH1F *h1f = new TH1F("h1f","Test random numbers", 100, -5.0, 5.0);
  
  h1f->SetFillColor(5);
  
  h1f->FillRandom("gaus",1000); //Probar con otras distribuciones (landau, expo), no olvidar cambiar los rangos
  
  h1f->Draw();
  
  c1->Update();
  
  //
  // Open a ROOT file and save the formula, function and histogram
  //

  TFile myfile("fillrandom.root","RECREATE"); // Manejo de DATOS - Storage
  
  h1f->Write();
  
  gBenchmark->Show("fillrandom");

  // abrir el archivo .root
  
}
