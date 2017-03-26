// The class definition in FakeRateSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following se                                              FakeRateSelector.C")
// root> T->Process("FakeRateSelector.C","some options")
// root> T->Process("FakeRateSelector.C+")
//


#include "Analysis/WZAnalysis/interface/FakeRateSelector.h"
#include <TStyle.h>

void FakeRateSelector::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void FakeRateSelector::SlaveBegin(TTree * /*tree*/)
{
    TString option = GetOption();

}

Bool_t FakeRateSelector::Process(Long64_t entry)
{
    WZSelectorBase::Process(entry);

    b_Zmass->GetEntry(entry);
    b_type1_pfMETEt->GetEntry(entry);
    b_nCBVIDVetoElec->GetEntry(entry);
    b_nWZLooseMuon->GetEntry(entry);
    
    b_l1Pt->GetEntry(entry);
    b_l2Pt->GetEntry(entry);
    b_l3Pt->GetEntry(entry);
    b_l3Eta->GetEntry(entry);
    b_l3MtToMET->GetEntry(entry);
    
    if (l1Pt < 25 || l2Pt < 15)
        return true;
    if (Zmass > 111.1876 || Zmass < 81.1876)
        return true;
    if (type1_pfMETEt > 30)
        return true;
    if (l3MtToMET > 30)
        return true;
    if (!tightZLeptons())
        return true;
    passingLoose2D_->Fill(l3Pt, std::abs(l3Eta), genWeight);
    passingLoose1DPt_->Fill(l3Pt, genWeight);
    passingLoose1DEta_->Fill(std::abs(l3Eta), genWeight);
    if (lepton3IsTight()) {
        passingTight2D_->Fill(l3Pt, std::abs(l3Eta), genWeight);
        passingTight1DPt_->Fill(l3Pt, genWeight);
        passingTight1DEta_->Fill(std::abs(l3Eta), genWeight);
    }
    return kTRUE;
}

void FakeRateSelector::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.

}

void FakeRateSelector::Terminate()
{
    //// The Terminate() function is the last function to be called during
    //// a query. It always runs on the client, it can be used to present
    //// the results graphically or save the results to file.
    //ratio2D_ = dynamic_cast<TH2D*>(passingTight2D_->Clone());
    //ratio2D_->Divide(passingLoose2D_);
    //ratio2D_->SetName((std::string("ratio2D_") + channelName_).c_str());
    //ratio2D_->SetTitle("Ratio tight/loose");
    //ratio2D_->SetDirectory(0);
    //histDir_->Add(ratio2D_);

    //ratio1DPt_ = dynamic_cast<TH1D*>(passingTight1DPt_->Clone());
    //ratio1DPt_->Divide(passingLoose1DPt_);
    //ratio1DPt_->SetName((std::string("ratio1DPt_") + channelName_).c_str());
    //ratio1DPt_->SetTitle("Ratio tight/loose");
    //ratio1DPt_->SetDirectory(0);
    //histDir_->Add(ratio1DPt_);

    //ratio1DEta_ = dynamic_cast<TH1D*>(passingTight1DEta_->Clone());
    //ratio1DEta_->Divide(passingLoose1DEta_);
    //ratio1DEta_->SetName((std::string("ratio1DEta_") + channelName_).c_str());
    //ratio1DEta_->SetTitle("Ratio tight/loose");
    //ratio1DEta_->SetDirectory(0);
    //histDir_->Add(ratio1DEta_);
}

void FakeRateSelector::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the reader is initialized.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).
    WZSelectorBase::Init(tree);

    fChain->SetBranchAddress("type1_pfMETEt", &type1_pfMETEt, &b_type1_pfMETEt);
    fChain->SetBranchAddress("nCBVIDVetoElec", &nCBVIDVetoElec, &b_nCBVIDVetoElec);
    fChain->SetBranchAddress("nWZLooseMuon", &nWZLooseMuon, &b_nWZLooseMuon);

    if (channel_ == eee) {
        fChain->SetBranchAddress("e1_e2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("e1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("e2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("e3Pt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("e3Eta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("e3MtToMET", &l3MtToMET, &b_l3MtToMET);
    }
    else if (channel_ == eem) { 
        fChain->SetBranchAddress("e1_e2_Mass", &Zmass, &b_Zmass);
        
        fChain->SetBranchAddress("e1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("e2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("mPt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("mEta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("mMtToMET", &l3MtToMET, &b_l3MtToMET);
    }
    else if (channel_ == emm) { 
        fChain->SetBranchAddress("m1_m2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("m1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("m2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("ePt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("eEta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("eMtToMET", &l3MtToMET, &b_l3MtToMET);
    }
    else if (channel_ == mmm) { 
        fChain->SetBranchAddress("m1_m2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("m1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("m2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("m3Pt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("m3Eta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("m3MtToMET", &l3MtToMET, &b_l3MtToMET);
    }
}

Bool_t FakeRateSelector::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void FakeRateSelector::SetupNewDirectory()
{
    WZSelectorBase::SetupNewDirectory();

    AddObject<TH2D>(passingTight2D_, ("passingTight2D_"+channelName_).c_str(), "#eta; p_{T} [GeV]", 4, 10, 50, 3, 0, 2.5);
    AddObject<TH1D>(passingTight1DPt_, ("passingTight1DPt_"+channelName_).c_str(), "Tight leptons; p_{T} [GeV]", 4, 10, 50);
    AddObject<TH1D>(passingTight1DEta_, ("passingTight1DEta_"+channelName_).c_str(), "Tight leptons; #eta", 3, 0, 2.5);
    
    AddObject<TH2D>(passingLoose2D_, ("passingLoose2D_"+channelName_).c_str(), "#eta; p_{T} [GeV]", 4, 10, 50, 3, 0, 2.5);
    AddObject<TH1D>(passingLoose1DPt_, ("passingLoose1DPt_"+channelName_).c_str(), "Loose leptons; p_{T} [GeV]", 4, 10, 50);
    AddObject<TH1D>(passingLoose1DEta_, ("passingLoose1DEta_"+channelName_).c_str(), "Loose leptons; #eta", 3, 0, 2.5);
}
