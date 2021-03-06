#!/usr/bin/env python

import sys
import os
import os.path
import optparse
import time
import math
import glob

import ROOT

sys.path.append('%s/CrossSectionReader/' % os.environ['BASE_WORK_DIR'])
import CrossSectionReader

sys.path.append('%s/RunHelpers/' % os.environ['BASE_WORK_DIR'])
import RunHelpers

# ==============================================================================
# ntuple tree name
input_tree_name = 'TNT'
lep_pt_cut = 40.e3
jet_pt_cut = 40.e3

# 90% working point
# btag_working_point = 0.0617
# 80% working point
btag_working_point = 0.3511
# 70% working point
# btag_working_point = 0.7892

# ==============================================================================
print 'loading packages'
ROOT.gROOT.ProcessLine(".x ${ROOTCOREDIR}/scripts/load_packages.C")
print 'loading libraries'
ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libProgressBar.so')
ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libCutFlowTracker.so')
ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libHistogramHandlers.so')
ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libPennSusyFrameCore.so')
ROOT.gSystem.Load('${BASE_WORK_DIR}/lib/libBMinusLAnalysis.so')
print 'done loading libraries'

# ------------------------------------------------------------------------------
def runBMinusLDRStudiesFun(data_set_dict):
    print '================================================================================'
    print 'label: %s'       % data_set_dict['label']
    # print 'file_list: %s'   % data_set_dict['file_list']
    print 'dsid: %s'        % data_set_dict['dsid']

    print 'is data: %s'     % data_set_dict['is_data']

    if data_set_dict['is_data']:
        print 'is egamma stream: %s' % data_set_dict['is_egamma_stream']
    else:
        print 'is full sim: %s' % data_set_dict['is_full_sim']

    print 'total number jobs: %s' % data_set_dict['total_num_jobs']
    print 'this job number: %s' % data_set_dict['job_num']

    print 'total num events: %s' % data_set_dict['total_num_events']
    print 'total num entries: %s' % data_set_dict['total_num_entries']
    print 'sum of event weights: %s' % data_set_dict['sum_mc_event_weights']

    print 'About to run BMinusLDRStudies'
    runBMinusLDRStudies( file_list             = data_set_dict['file_list']
                       , is_data               = data_set_dict['is_data']
                       , is_egamma_stream      = data_set_dict['is_egamma_stream']
                       , is_full_sim           = data_set_dict['is_full_sim']
                       , tree_name             = input_tree_name
                       # , tree_name             = 'TNT'
                       # , tree_name             = 'BMinusLTTNT'
                       , dsid                  = data_set_dict['dsid']
                       , out_file_special_name = data_set_dict['label']
                       , is_tnt                = True
                       , fancy_progress_bar    = False
                       , job_num               = data_set_dict['job_num']
                       , total_num_jobs        = data_set_dict['total_num_jobs']
                       , total_num_events      = data_set_dict['total_num_events']
                       , total_num_entries     = data_set_dict['total_num_entries']
                       , sum_mc_event_weights  = data_set_dict['sum_mc_event_weights']
                       , out_dir               = data_set_dict['out_dir']
                       )

# ------------------------------------------------------------------------------
def runBMinusLDRStudies( file_list
                       , is_data
                       , is_egamma_stream
                       , is_full_sim
                       , tree_name             = 'susy'
                       , dsid                  = 1
                       , out_file_special_name = None
                       , is_tnt                = False
                       , fancy_progress_bar    = True
                       , job_num               = 0
                       , total_num_jobs        = 1
                       , total_num_events      = 0
                       , total_num_entries     = 0
                       , sum_mc_event_weights  = 0
                       , out_dir               = './'
                       ):
    # ==============================================================================
    # If the num events are not set and we are running over TNTs, get the total NumEvents
    print 'total num events: %s' % total_num_events
    if total_num_events == 0 and is_tnt:
        print 'Getting total num unskimmed events'
        print '  -- this is slow. you should do this once per data set - not for each stream!'
        total_num_events = getTotalNumEvents(file_list, is_tnt)

    print "Adding files to TChain"
    print '  Tree name: ' , tree_name
    t = RunHelpers.getTChain(file_list, tree_name)
    print t
    print t.GetEntries()

    # ==============================================================================
    print 'Creating BMinusLDRStudies object'
    bmldrs = ROOT.PennSusyFrame.BMinusLDRStudies(t)

    print 'configuring BMinusLDRStudies object'
    if out_file_special_name is not None:
        bmldrs.setProcessLabel(out_file_special_name + '__%d_of_%d' % (job_num, total_num_jobs) )
    bmldrs.setFancyProgressBar(False)

    # set is data or MC
    if is_data:
        bmldrs.setIsData()

        if is_egamma_stream:
            bmldrs.setIsEgammaStream()
        else:
            bmldrs.setIsMuonStream()
    else:
        bmldrs.setIsMC()

        xsec_dict = CrossSectionReader.getCrossSection(dsid)
        if xsec_dict is None:
            return
        bmldrs.setCrossSection(xsec_dict['xsec'])
        bmldrs.setKFactor(     xsec_dict['kfac'])
        bmldrs.setFilterEff(   xsec_dict['eff'])

        bmldrs.setTotalNumEntries(    total_num_entries    )
        bmldrs.setNumGeneratedEvents( total_num_events     )
        bmldrs.setSumMCEventWeights(  sum_mc_event_weights )

    # set is full sim/fast sim
    if is_full_sim:
        bmldrs.setFullSim()

    # set start entry and max number events
    if total_num_jobs > 1:
        print 'total num jobs (%s) > 1' % total_num_jobs
        this_job_events = int(math.ceil( float(total_num_entries) / total_num_jobs ))
        this_job_start = job_num*this_job_events

        print 'total num entries; %s' % total_num_entries
        print 'setting max num events: %s' % this_job_events
        print type(this_job_events)
        bmldrs.setMaxNumEvents(this_job_events)
        print 'setting start entry: %s' % this_job_start
        bmldrs.setStartEntry(this_job_start)

    # set out histogram file name
    print 'setting histogram names'
    out_hist_file_name = '%s/BMinusLDRStudies.' % out_dir
    if out_file_special_name is not None:
        out_hist_file_name += '%s.' % out_file_special_name
    out_hist_file_name += 'hists'
    if total_num_jobs > 1:
        out_hist_file_name += '.%d_of_%d' % (job_num, total_num_jobs)
    out_hist_file_name += '.root'
    bmldrs.setOutHistFileName(out_hist_file_name)

    # Set critical cuts
    # print 'setting critical cuts'
    bmldrs.setCritCutGrl(            1)
    bmldrs.setCritCutIncompleteEvent(1)
    bmldrs.setCritCutLarError(       1)
    bmldrs.setCritCutTileError(      1)
    bmldrs.setCritCutTileHotSpot(    1)
    bmldrs.setCritCutTileTrip(       1)
    bmldrs.setCritCutBadJetVeto(     1)
    bmldrs.setCritCutCaloProblemJet( 1)
    bmldrs.setCritCutPrimaryVertex(  1)
    bmldrs.setCritCutBadMuonVeto(    1)
    bmldrs.setCritCutCosmicMuonVeto( 1)
    bmldrs.setCritCutHFOR(           1)
    bmldrs.setCritCutMcOverlap(      1)
    bmldrs.setCritCutGe2Lepton(      1)
    bmldrs.setCritCut2Lepton(        0)
    bmldrs.setCritCut2SignalLepton(  0)
    bmldrs.setCritCut2BJets(         0)
    bmldrs.setCritCutBadJetVeto(     1)
    bmldrs.setCritCutBLPairing(      0)

    # Set cut values
    # print 'set cuts'
    bmldrs.setElPtCut(  lep_pt_cut, -1     )
    bmldrs.setMuPtCut(  lep_pt_cut, -1     )
    bmldrs.setBJetPtCut(jet_pt_cut, -1     )
    bmldrs.setMV1Cut(btag_working_point)

    # Turn off detailed B-L histograms
    bmldrs.setDoDetailedBLHists(False)

    # prepare tools and run analysis loop
    print 'preparing tools'
    bmldrs.prepareTools()
    print 'looping -- %s' % out_file_special_name
    bmldrs.Loop()
    print 'done looping -- %s' % out_file_special_name

    # ==============================================================================
    print ''
    print ''
