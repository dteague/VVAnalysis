# Setup ScaleFactor objects to be "registered" with ROOT,
# allowing them to be called from TTree.Draw(), for example.
# Currently used for lepton scale factors and pileup weights.
#
# Modified from N. Smith, U. Wisconsin
# 

#!/usr/bin/env python
import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.PyConfig.IgnoreCommandLineOptions = True

def float2double(hist):
    if hist.ClassName() == 'TH1F':
        new = ROOT.TH1D()
        hist.Copy(new)
    elif hist.ClassName() == 'TH2F':
        new = ROOT.TH2D()
        hist.Copy(new)
    else:
        raise Exception("Bad hist, dummy")
    return new

fScales = ROOT.TFile('../data/scaleFactors.root', 'recreate')

#pileupSF = ROOT.ScaleFactor("pileupSF", "ICHEP 12.9/fb Pileup profile Scale Factor, x=NTruePU")
#pileupFile = ROOT.TFile.Open('PileupWeights/PU_Central.root')
#pileupFileUp = ROOT.TFile.Open('PileupWeights/PU_minBiasUP.root')
#pileupFileDown = ROOT.TFile.Open('PileupWeights/PU_minBiasDOWN.root')
#pileupSF.Set1DHist(pileupFile.Get('pileup'), pileupFileUp.Get('pileup'), pileupFileDown.Get('pileup'), ROOT.ScaleFactor.AsInHist)
#fScales.cd()
#pileupSF.Write()

electronMedIdSF = ROOT.ScaleFactor("electronMedIdSF", "ICHEP Electron Medium WP ID SF, x=Eta, y=Pt")
eidFile = ROOT.TFile.Open('../data/ichepElectronMediumSF.root')
electronMedIdSF.Set2DHist(float2double(eidFile.Get('EGamma_SF2D')))
fScales.cd()
electronMedIdSF.Write()

electronTightIdSF = ROOT.ScaleFactor("electronTightIdSF", "ICHEP Electron Medium WP ID SF, x=Eta, y=Pt")
eidFile = ROOT.TFile.Open('../data/ichepElectronTightSF.root')
electronTightIdSF.Set2DHist(float2double(eidFile.Get('EGamma_SF2D')))
fScales.cd()
electronTightIdSF.Write()

electronGsfSF = ROOT.ScaleFactor("electronGsfSF", "ICHEP Electron GSF track reco SF, x=Eta, y=Pt")
eleGsfFile = ROOT.TFile.Open('../data/ichepElectronGsfSF.root')
electronGsfSF.Set2DHist(float2double(eleGsfFile.Get('EGamma_SF2D')))
fScales.cd()
electronGsfSF.Write()

muonTightIdSF = ROOT.ScaleFactor("muonTightIdSF", "ICHEP Muon Tight WP ID SF, x=Eta")
midFile = ROOT.TFile.Open('../data/MuonID_Z_RunBCD_prompt80X_7p65.root')
muonTightIdSF.Set2DHist(float2double(midFile.Get('MC_NUM_TightIDandIPCut_DEN_genTracks_PAR_pt_spliteta_bin1/abseta_pt_ratio')))
fScales.cd()
muonTightIdSF.Write()

muonMedIdSF = ROOT.ScaleFactor("muonMedIdSF", "ICHEP Muon Med WP ID SF, x=Eta")
muonMedIdSF.Set2DHist(float2double(midFile.Get('MC_NUM_MediumID_DEN_genTracks_PAR_pt_spliteta_bin1/abseta_pt_ratio')))
fScales.cd()
muonMedIdSF.Write()

muonTightIsoSF = ROOT.ScaleFactor("muonTightIsoSF", "ICHEP Muon Tight Iso (0.15) WP ID SF, x=abs(Eta), y=Pt")
misoFile = ROOT.TFile.Open('../data/MuonIso_Z_RunBCD_prompt80X_7p65.root')
muonTightIsoSF.Set2DHist(float2double(misoFile.Get('MC_NUM_TightRelIso_DEN_TightID_PAR_pt_spliteta_bin1/abseta_pt_ratio')))
fScales.cd()
muonTightIsoSF.Write()

fakeRateFile = ROOT.TFile.Open('../data/CutBasedFakeRate_fromSvenja.root')
eCBMedFakeRate = ROOT.ScaleFactor("eCBMedFakeRate_Svenja", "Fake rate from dijet control, by Svenja")
eCBMedFakeRate.Set2DHist(float2double(fakeRateFile.Get('e/medium/fakeratePtEta')), 0, 0, ROOT.ScaleFactor.NearestEntry)
eCBTightFakeRate = ROOT.ScaleFactor("eCBTightFakeRate_Svenja", "Fake rate from dijet control, by Svenja")
eCBTightFakeRate.Set2DHist(float2double(fakeRateFile.Get('e/tight/fakeratePtEta')), 0, 0, ROOT.ScaleFactor.NearestEntry)
mCBMedFakeRate = ROOT.ScaleFactor("mCBMedFakeRate_Svenja", "Fake rate from dijet control, by Svenja")
mCBMedFakeRate.Set2DHist(float2double(fakeRateFile.Get('m/medium/fakeratePtEta')), 0, 0, ROOT.ScaleFactor.NearestEntry)
mCBTightFakeRate = ROOT.ScaleFactor("mCBTightFakeRate_Svenja", "Fake rate from dijet control, by Svenja")
mCBTightFakeRate.Set2DHist(float2double(fakeRateFile.Get('m/tight/fakeratePtEta')), 0, 0, ROOT.ScaleFactor.NearestEntry)
fScales.cd()
mCBMedFakeRate.Write()
mCBTightFakeRate.Write()
eCBMedFakeRate.Write()
eCBTightFakeRate.Write()

fakeRateFile = ROOT.TFile.Open('../data/fakeRate23Feb2017-3LooseLeptons.root')
eCBTightFakeRateZjets = ROOT.ScaleFactor("eCBTightFakeRate", "Fake rate from Z+jet")
eCBTightFakeRateZjets.Set2DHist(fakeRateFile.Get('DataEWKCorrected/ratio2D_allE'), 0, 0, ROOT.ScaleFactor.NearestEntry)
mCBTightFakeRateZjets = ROOT.ScaleFactor("mCBTightFakeRate", "Fake rate from Z+jet")
mCBTightFakeRateZjets.Set2DHist(fakeRateFile.Get('DataEWKCorrected/ratio2D_allMu'), 0, 0, ROOT.ScaleFactor.NearestEntry)
fScales.cd()

mCBTightFakeRateZjets.Write()
eCBTightFakeRateZjets.Write()
