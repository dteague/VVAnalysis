#define FakeRateEEMTest_cxx
// The class definition in FakeRateEEMTest.h has been generated automatically
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
// To use this file, try the following se                                              FakeRateEEMTest.C")
// root> T->Process("FakeRateEEMTest.C","some options")
// root> T->Process("FakeRateEEMTest.C+")
//


#include "Analysis/WZAnalysis/interface/FakeRateEEMTest.h"
#include <TStyle.h>

void FakeRateEEMTest::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void FakeRateEEMTest::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    const char* dataset = "Unnamed";
    const char* channel = "eem";
    if (GetInputList() != nullptr) {
        TNamed* name = (TNamed *) GetInputList()->FindObject("name");
        TNamed* chan = (TNamed *) GetInputList()->FindObject("channel");
        if (name != nullptr)
            dataset = name->GetTitle();
        if (chan != nullptr)
            channel = chan->GetTitle();
    }
    histDir_ = new TList();
    histDir_->SetName(dataset);
    fOutput->Add(histDir_);
    passingTight2D_= new TH2D((std::string("passingTight2D_")+channel).c_str(),
        "Tight leptons; p_{T} [GeV]; Eta", 8, 10, 50, 5, -2.5, 2.5);
    passingTight2D_->SetDirectory(0);
    histDir_->Add(passingTight2D_);
    passingTight1DPt_= new TH1D((std::string("passingTight1DPt_")+channel).c_str(),
        "Tight leptons; p_{T} [GeV]", 8, 10, 50);
    passingTight1DPt_->SetDirectory(0);
    histDir_->Add(passingTight1DPt_);
    passingTight1DEta_ = new TH1D( (std::string("passingTight1DEta_")+channel).c_str(), 
        "Tight leptons; #eta; Events", 5, -2.5, 2.5);
    passingTight1DEta_->SetDirectory(0);
    histDir_->Add(passingTight1DEta_);
    passingLoose2D_ = new TH2D((std::string("passingLoose2D_")+channel).c_str(), 
        "Leptons passing tight failing loose; p_{T} [GeV]; Eta", 8, 10, 50, 5, -2.5, 2.5);
    passingLoose2D_->SetDirectory(0);
    histDir_->Add(passingLoose2D_);
    passingLoose1DPt_ = new TH1D((std::string("passingLoose1DPt_")+channel).c_str(), 
        "Loose leptons; p_{T} [GeV]; Events", 8, 10, 50);
    passingLoose1DPt_->SetDirectory(0);
    histDir_->Add(passingLoose1DPt_);
    passingLoose1DEta_ = new TH1D((std::string("passingLoose1DEta_")+channel).c_str(), 
        "Loose leptons; #eta; Events", 5, -2.5, 2.5);
    passingLoose1DEta_->SetDirectory(0);
    histDir_->Add(passingLoose1DEta_);
    TString option = GetOption();

}

Bool_t FakeRateEEMTest::Process(Long64_t entry)
{
    // The Process() function is called for each entry in the tree (or possibly
    // keyed object in the case of PROOF) to be processed. The entry argument
    // specifies which entry in the currently loaded tree is to be processed.
    // When processing keyed objects with PROOF, the object is already loaded
    // and is available via the fObject pointer.
    //
    // This function should contain the \"body\" of the analysis. It can contain
    // simple or elaborate selection criteria, run algorithms on the data
    // of the event and typically fill histograms.
    //
    // The processing can be stopped by calling Abort().
    //
    // Use fStatus to set the return value of TTree::Process().
    //
    // The return value is currently not used.

    b_type1_pfMETEt->GetEntry(entry);
    b_nWWLooseElec->GetEntry(entry);
    b_nWZLooseMuon->GetEntry(entry);
    b_e1IsCBVIDTight->GetEntry(entry);
    b_e2IsCBVIDTight->GetEntry(entry);
    b_e1IsEB->GetEntry(entry);
    b_e2IsEB->GetEntry(entry);
    b_e1PVDXY->GetEntry(entry);
    b_e2PVDXY->GetEntry(entry);
    b_e1PVDZ->GetEntry(entry);
    b_e2PVDZ->GetEntry(entry);
    b_mIsTightMuon->GetEntry(entry);
    b_mRelPFIsoDBR04->GetEntry(entry);
    b_mEta->GetEntry(entry);
    b_mPt->GetEntry(entry);
    if (std::abs(static_cast<int>(nWWLooseElec + nWZLooseMuon) - 3) > 0.1)
        return true;
    if (type1_pfMETEt > 30)
        return true;
    if (!(e1IsCBVIDTight &&
            (e1IsEB ? e1PVDXY < 0.05 : e1PVDXY < 0.1) &&
            (e1IsEB ? e1PVDZ < 0.1 : e1PVDZ < 0.2)) &&
            (e2IsCBVIDTight &&
            (e2IsEB ? e2PVDXY < 0.05 : e2PVDXY < 0.1) &&
            (e2IsEB ? e2PVDZ < 0.1 : e2PVDZ < 0.2)))
        return true;
    passingLoose2D_->Fill(mPt, mEta);
    passingLoose1DPt_->Fill(mPt);
    passingLoose1DEta_->Fill(mEta);
    if (mIsTightMuon && mRelPFIsoDBR04 < 0.15) {
        passingTight2D_->Fill(mPt, mEta);
        passingTight1DPt_->Fill(mPt);
        passingTight1DEta_->Fill(mEta);
    }

    return kTRUE;
}

void FakeRateEEMTest::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.

}

void FakeRateEEMTest::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.

}
