void test1(Int_t time = 10,Double_t g_x = 1.0, Double_t g_y = -1.0, Double_t k_xy = 1.0,Double_t k_yx = 1.0) {

  gRandom->SetSeed(0);
  Long64_t N[2] = { gRandom->Uniform(50,100),gRandom->Uniform(50,100) };

//Double_t g_x = 1.0;
//Double_t g_y = -1.0;
//Double_t k_xy = 1.0;
//Double_t k_yx = 1.0;

  Double_t matrixT[2][2];
  matrixT[0][0] = g_x - k_xy;
  matrixT[1][0] = k_yx;
  matrixT[0][1] = k_xy;
  matrixT[1][1] = g_y - k_yx;

  
  Printf("gx=%f gy=%f kxy=%f kyx=%f",g_x, g_y, k_xy, k_yx);

  Printf("|%f %f|",matrixT[0][0],matrixT[1][0]);
  Printf("|%f %f|",matrixT[1][0],matrixT[1][1]);

  TGraph *gNx = new TGraph();
  gNx->SetLineColor(kGreen);
  TGraph *gNy = new TGraph();
  gNy->SetLineColor(kRed);


  Printf("N_x=%d N_y=%d",N[0],N[1]);
  Double_t diff_Nx, diff_Ny;
  for (Int_t iTime = 1; iTime <= time;iTime++) {
     
    //Printf("->>>>>[%d] %d N_y=%d",iTime, N[0], N[1]);
    diff_Nx = matrixT[0][0]*N[0] + matrixT[1][0]*N[1];    
    diff_Ny = matrixT[0][1]*N[0] + matrixT[1][1]*N[1];

    //Printf("[%d] diff_Nx=%f diff_Ny=%f",iTime, diff_Nx, diff_Ny);

    N[0] += diff_Nx;    
    N[1] += diff_Ny;    
    Printf("[%d] N_x=%d N_y=%d",iTime, N[0], N[1]);
    
    if (N[0]<0) N[0]=0;    
    if (N[1]<0) N[1]=0;    
    gNx->SetPoint(gNx->GetN(),iTime,N[0]);
    gNy->SetPoint(gNy->GetN(),iTime,N[1]);
  }


  TCanvas *c = new TCanvas();
  //c->Divide(2,1);
  c->cd(1);
  gNx->Draw("APL");
  //c->cd(2);
  gNy->Draw("PL SAME");


}
