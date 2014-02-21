#!/usr/bin/env python

import sys
import os.path
import optparse
import time

import glob

import ROOT

import os
sys.path.append('%s/CrossSectionReader/' % os.environ['BASE_WORK_DIR'])
import CrossSectionReader

# ------------------------------------------------------------------------------
def getFileListFromDir(file_path):
    print 'getting files from dir: %s' % file_path
    file_list = glob.glob('%s/*' % file_path)
    return file_list

# ------------------------------------------------------------------------------
def getFileListFromGridInput(grid_input_string):
    file_list = grid_input_string.split(',')
    return file_list

# ------------------------------------------------------------------------------
def runBMinusLAnalysis( file_list
                      , is_data
                      , is_full_sim
                      , tree_name = 'susy'
                      , dsid = 1
                      ):
    # ==============================================================================
    print 'loading packages'
    ROOT.gROOT.ProcessLine(".x ${ROOTCOREDIR}/scripts/load_packages.C")
    print 'loading libraries'
    ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libProgressBar.so')
    ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libCutFlowTracker.so')
    ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libHistogramHandlers.so')
    ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libPennSusyFrameCore.so')
    ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libBMinusLAnalysis.so')

    # ==============================================================================
    print "Adding files to TNT maker"
    t = ROOT.TChain(tree_name)
    # t = ROOT.TChain("TNT")
    for fl in file_list:
        print 'Adding file: %s' % fl
        t.AddFile(fl)

    # ==============================================================================
    bmla = ROOT.PennSusyFrame.BMinusLAnalysis(t)
    if is_data:
        bmla.setIsData()
    else:
        bmla.setIsMC()

        xsec_dict = CrossSectionReader.getCrossSection(dsid)
        if xsec_dict is None:
            return
        bmla.setCrossSection(xsec_dict['xsec'])
        bmla.setKFactor(     xsec_dict['kfac'])
        bmla.setFilterEff(   xsec_dict['eff'])

    if is_full_sim:
        bmla.setFullSim()

    bmla.setCritCutGrl(            1)
    bmla.setCritCutIncompleteEvent(1)
    bmla.setCritCutLarError(       1)
    bmla.setCritCutTileError(      1)
    bmla.setCritCutTileHotSpot(    1)
    bmla.setCritCutTileTrip(       1)
    bmla.setCritCutBadJetVeto(     1)
    bmla.setCritCutCaloProblemJet( 1)
    bmla.setCritCutPrimaryVertex(  1)
    bmla.setCritCutBadMuonVeto(    1)
    bmla.setCritCutCosmicMuonVeto( 1)
    bmla.setCritCutHFOR(           1)
    bmla.setCritCutMcOverlap(      1)
    bmla.setCritCutGe2Lepton(      1)
    bmla.setCritCut2Lepton(        1)
    bmla.setCritCut2SignalLepton(  1)
    bmla.setCritCutBadJetVeto(     1)
    bmla.setCritCutBLPairing(      1)

    bmla.prepareTools()
    bmla.Loop()

    # ==============================================================================
    print ''
    print ''
