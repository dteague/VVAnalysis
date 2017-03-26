// The class definition in WZSelectorBase.h has been generated automatically
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

#include "Analysis/WZAnalysis/interface/WZSelectorBase.h"
#include <TStyle.h>

void WZSelectorBase::Begin(TTree * /*tree*/)
{
    TString option = GetOption();
}

void WZSelectorBase::SlaveBegin(TTree * /*tree*/)
{
}
void WZSelectorBase::Init(TTree *tree)
{
    if (!tree) return;
    fChain = tree;
    
    TString option = GetOption();

    if (GetInputList() != nullptr) {
        TNamed* name = (TNamed *) GetInputList()->FindObject("name");
        TNamed* chan = (TNamed *) GetInputList()->FindObject("channel");
        if (name != nullptr) {
            name_ = name->GetTitle();
        }
        if (chan != nullptr) {
            channelName_ = chan->GetTitle();
        }
    }
    std::cout << "Processing " << name_ << std::endl;
    
    currentHistDir_ = dynamic_cast<TList*>(fOutput->FindObject(name_.c_str()));
    if ( currentHistDir_ == nullptr ) {
        currentHistDir_ = new TList();
        currentHistDir_->SetName(name_.c_str());
        fOutput->Add(currentHistDir_);
        // Watch for something that I hope never happens,
        size_t existingObjectPtrsSize = allObjects_.size();
        SetupNewDirectory();
        if ( existingObjectPtrsSize > 0 && allObjects_.size() != existingObjectPtrsSize ) {
            Abort(Form("WZSelectorBase: Size of allObjects has changed!: %lu to %lu", existingObjectPtrsSize, allObjects_.size()));
        }
    }
    UpdateDirectory();

    isMC_ = false;
    if (name_.find("data") == std::string::npos){
        isMC_ = true;
        fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
    }

    if (channelName_ == "eee") {
        channel_ = eee;
        fChain->SetBranchAddress("e1IsCBVIDTight", &l1IsTight, &b_l1IsTight);
        fChain->SetBranchAddress("e2IsCBVIDTight", &l2IsTight, &b_l2IsTight);
        fChain->SetBranchAddress("e3IsCBVIDTight", &l3IsTight, &b_l3IsTight);
    }
    else if (channelName_ == "eem") { 
        channel_ = eem;
        fChain->SetBranchAddress("e1IsCBVIDTight", &l1IsTight, &b_l1IsTight);
        fChain->SetBranchAddress("e2IsCBVIDTight", &l2IsTight, &b_l2IsTight);
        fChain->SetBranchAddress("mIsMedium", &l3IsTight, &b_l3IsTight);
        fChain->SetBranchAddress("mRelPFIsoDBR04", &m3RelPFIsoDBR04, &b_m3RelPFIsoDBR04);
    }
    else if (channelName_ == "emm") { 
        channel_ = emm;
        fChain->SetBranchAddress("eIsCBVIDTight", &l3IsTight, &b_l3IsTight);
        fChain->SetBranchAddress("m1IsMedium", &l1IsTight, &b_l1IsTight);
        fChain->SetBranchAddress("m1RelPFIsoDBR04", &m1RelPFIsoDBR04, &b_m1RelPFIsoDBR04);
        fChain->SetBranchAddress("m2IsMedium", &l2IsTight, &b_l2IsTight);
        fChain->SetBranchAddress("m2RelPFIsoDBR04", &m2RelPFIsoDBR04, &b_m2RelPFIsoDBR04);
    }
    else if (channelName_ == "mmm") { 
        channel_ = mmm;
        fChain->SetBranchAddress("m1IsMedium", &l1IsTight, &b_l1IsTight);
        fChain->SetBranchAddress("m1RelPFIsoDBR04", &m1RelPFIsoDBR04, &b_m1RelPFIsoDBR04);
        fChain->SetBranchAddress("m2IsMedium", &l2IsTight, &b_l2IsTight);
        fChain->SetBranchAddress("m2RelPFIsoDBR04", &m2RelPFIsoDBR04, &b_m2RelPFIsoDBR04);
        fChain->SetBranchAddress("m3IsMedium", &l3IsTight, &b_l3IsTight);
        fChain->SetBranchAddress("m3RelPFIsoDBR04", &m3RelPFIsoDBR04, &b_m3RelPFIsoDBR04);
    }
    else
        throw std::invalid_argument("Invalid channel choice!");
}

Bool_t WZSelectorBase::Notify()
{
    return kTRUE;
}

Bool_t WZSelectorBase::Process(Long64_t entry)
{
    genWeight = 1;
    if (isMC_)
        b_genWeight->GetEntry(entry);
    b_l1IsTight->GetEntry(entry);
    b_l2IsTight->GetEntry(entry);
    b_l3IsTight->GetEntry(entry);
    
    if (channel_ == eem) {
        b_m3RelPFIsoDBR04->GetEntry(entry);
    }
    else if (channel_ == emm) {
        b_m1RelPFIsoDBR04->GetEntry(entry);
        b_m2RelPFIsoDBR04->GetEntry(entry);
    }
    else if (channel_ == mmm) {
        b_m1RelPFIsoDBR04->GetEntry(entry);
        b_m2RelPFIsoDBR04->GetEntry(entry);
        b_m3RelPFIsoDBR04->GetEntry(entry);
    }

    return kTRUE;
}

bool WZSelectorBase::tightZLeptons() {
    if (channel_ == eem || channel_ == eee) {
        return l1IsTight && l2IsTight; 
    }
    else 
        return m1RelPFIsoDBR04 < 0.15 && m2RelPFIsoDBR04 < 0.15;
}

bool WZSelectorBase::lepton3IsTight() {
    if (channel_ == eee || channel_ == emm) {
        return l3IsTight;
    }
    else if (channel_ == mmm || channel_ == eem) {
        return m3RelPFIsoDBR04 < 0.15;
    }
    else
        return false;
}

void WZSelectorBase::Terminate()
{
}
    
void WZSelectorBase::SlaveTerminate()
{
}
void WZSelectorBase::UpdateDirectory()
{
  for(TNamed** objPtrPtr : allObjects_) {
    if ( *objPtrPtr == nullptr ) Abort("WZSelectorBase: Call to UpdateObject but existing pointer is null");
    *objPtrPtr = (TNamed *) currentHistDir_->FindObject((*objPtrPtr)->GetName());
    if ( *objPtrPtr == nullptr ) Abort("WZSelectorBase: Call to UpdateObject but current directory has no instance");
  }
}

void WZSelectorBase::SetupNewDirectory()
{
}
