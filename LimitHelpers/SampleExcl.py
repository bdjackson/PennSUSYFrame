################################################################
## In principle all you have to setup is defined in this file ##
################################################################
from configManager import configMgr
from ROOT import kBlack,kWhite,kGray,kRed,kPink,kMagenta,kViolet,kBlue,kAzure,kCyan,kTeal,kGreen,kSpring,kYellow,kOrange,kDashed,kSolid,kDotted
from configWriter import fitConfig,Measurement,Channel,Sample
from systematic import Systematic
from math import sqrt

# Setup for ATLAS plotting
from ROOT import gROOT, TLegend, TLegendEntry, TCanvas
gROOT.LoadMacro("./macros/AtlasStyle.C")
import ROOT
ROOT.SetAtlasStyle()

# ------------------------------------------------------------------------------
# import functions to do scaling
import sys
sys.path.append('%s/LimitHelpers/' % os.environ['BASE_WORK_DIR'])
import FlavorChannelScaling as scaling

# ----------------------------------------------------------------------------------------------
# - Some flags for overridding normal execution and telling ROOT to shut up... use with caution!
# ----------------------------------------------------------------------------------------------
#gROOT.ProcessLine("gErrorIgnoreLevel=10001;")
#configMgr.plotHistos = True
configMgr.blindSR = True

# ----------------------------------------
# - Flags to control which fit is executed
# ----------------------------------------
use_stat = True
do_validation = True

single_bin_regions = True
single_bin_signal  = True

print 'Analysis configurations:'
if myFitType == FitType.Exclusion:
    print '  fit type: Exclusion'
elif myFitType == FitType.Discovery:
    print '  fit type: Discovery'
elif myFitType == FitType.Background:
    print '  fit type: Background'
else:
    print '  fit type: Undefined :('

# -----------------------------------------------------------------------
# - cannot do validation and exclusion/discovery at the same time for now
# -----------------------------------------------------------------------
if myFitType == FitType.Discovery or myFitType == FitType.Exclusion:
    print 'turning off validation for discovery or exclusion'
    do_validation = False

# --------------------------------
# - Parameters for hypothesis test
# --------------------------------
#configMgr.doHypoTest=False
configMgr.nTOYs=10000
configMgr.calculatorType=2 # use 2 for asymptotic, 0 for toys
configMgr.testStatType=3
configMgr.nPoints=10

# ---------------------------------
# - Now we start to build the model
# ---------------------------------

# First define HistFactory attributes
configMgr.analysisName = "SampleExcl"
configMgr.histCacheFile = "data/"+configMgr.analysisName+".root"
configMgr.outputFileName = "results/"+configMgr.analysisName+"_Output.root"

# Scaling calculated by outputLumi / inputLumi
configMgr.inputLumi = 0.001    # Luminosity of input TTree after weighting
# configMgr.outputLumi = 13.0    # Luminosity required for output histograms
configMgr.outputLumi = 21.0    # Luminosity required for output histograms
configMgr.setLumiUnits("fb-1")


# Set the files to read from
bkg_files = []
sig_files = []
if configMgr.readFromTree:
    print 'reading from trees!'
    bkg_files.append("${BASE_WORK_DIR}/HistFitterNtuples/BackgroundHistFitterTrees.root")
    if myFitType==FitType.Exclusion:
        # 1-step simplified model
        sig_files.append("${BASE_WORK_DIR}/HistFitterNtuples/SignalHistFitterTrees.root")
else:
    print 'not reading from trees -- getting input from cache!'
    bkg_files = ["data/"+configMgr.analysisName+".root"]

# ------------------------------------
# - Dictionnary of cuts for Tree->hist
# ------------------------------------
# SR
base_sr_str = "is_sr"
configMgr.cutsDict["SR_ee"] = '(%s && is_ee)' % base_sr_str
configMgr.cutsDict["SR_mm"] = '(%s && is_mm)' % base_sr_str
configMgr.cutsDict["SR_em"] = '(%s && is_em)' % base_sr_str

# CR_top
base_cr_top_str = "is_cr_top"
configMgr.cutsDict["CR_top_all"] = base_cr_top_str
configMgr.cutsDict["CR_top_ee"] = '(%s && is_ee)' % base_cr_top_str
configMgr.cutsDict["CR_top_mm"] = '(%s && is_mm)' % base_cr_top_str
configMgr.cutsDict["CR_top_em"] = '(%s && is_em)' % base_cr_top_str

# CR_Z
base_cr_z_str = "is_cr_z"
configMgr.cutsDict["CR_Z_all"] = base_cr_z_str
configMgr.cutsDict["CR_Z_ee"] = '(%s && is_ee)' % base_cr_z_str
configMgr.cutsDict["CR_Z_mm"] = '(%s && is_mm)' % base_cr_z_str

# VR 3
base_vr_3_str = "is_vr_3"
configMgr.cutsDict["VR_3_all"] = base_vr_3_str
configMgr.cutsDict["VR_3_ee"] = '(%s && is_ee)' % base_vr_3_str
configMgr.cutsDict["VR_3_mm"] = '(%s && is_mm)' % base_vr_3_str
configMgr.cutsDict["VR_3_em"] = '(%s && is_em)' % base_vr_3_str

# VR 5
base_vr_5_str = "is_vr_5"
configMgr.cutsDict["VR_5_all"] = base_vr_5_str
configMgr.cutsDict["VR_5_ee"] = '(%s && is_ee)' % base_vr_5_str
configMgr.cutsDict["VR_5_mm"] = '(%s && is_mm)' % base_vr_5_str

# --------------------------
# - lists of nominal weights
# --------------------------
flavor_scale_factors = scaling.getFlavorScaleFactorsFromBR( br_e=0.1
                                                          , br_m=0.9
                                                          , br_t=0.
                                                          )
# TODO figure out how to only apply this weight for signal samples
# configMgr.weights = ["weight*( (is_ee*%f) + (is_mm*%f) + (is_em*%f) )" % ( flavor_scale_factors['ee']
#                                                                          , flavor_scale_factors['mm']
#                                                                          , flavor_scale_factors['em']
#                                                                          )
#                     ]
configMgr.weights = ["weight"]

# name of nominal histogram for systematics
configMgr.nomName = "_NoSys"

# ---------------------
# - List of systematics
# ---------------------
# TODO replace general systematic with real systematics

# generic systematic -- placeholder for now
gen_syst = Systematic( "gen_syst" , configMgr.weights , 1.0 + 0.30 , 1.0 - 0.30 , "user" , "userOverallSys" )

# JES uncertainty as shapeSys - one systematic per region (combine WR and TR), merge samples
# jes = Systematic("JER","_JESup","_JESdown","tree","overallNormHistoSys")
jes_uncert = Systematic("JES", '_NoSys', "_JES_UP", "_JES_DOWN", "tree", "overallSys")
jer_uncert = Systematic('JER', '_NoSys', '_JER'   , '_JER'     , 'tree', 'histoSysOneSide')

btag_sf_uncert = Systematic('btag_sf', configMgr.weights, ('weight', 'btag_sf_down_frac'), ('weight', 'btag_sf_up_frac'), 'weight', 'overallSys')

# --------------------------------------------
# - List of samples and their plotting colours
# --------------------------------------------
sample_list = []

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ttbar
ttbar_sample = Sample( "ttbar" , kGreen+2 )

ttbar_sample.setNormFactor("mu_ttbar",1.,0.,5.)
ttbar_sample.setStatConfig(use_stat)
sample_list.append(ttbar_sample)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# single top
single_top_sample = Sample( "SingleTop" , kGreen-1 )

single_top_sample.setStatConfig(   use_stat)
single_top_sample.setNormByTheory()
sample_list.append(single_top_sample)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Z/gamma*
z_sample = Sample( "ZGamma" , kRed+1 )

z_sample.setNormFactor("mu_z",1.,0.,5.)
z_sample.setStatConfig(use_stat)
sample_list.append(z_sample)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# ttV
ttv_sample = Sample( "ttV" , kAzure+8 )

ttv_sample.setStatConfig(use_stat)
ttv_sample.setNormByTheory()
sample_list.append(ttv_sample)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# diboson
diboson_sample = Sample( "Diboson" , kSpring-4 )

diboson_sample.setStatConfig(use_stat)
diboson_sample.setNormByTheory()
sample_list.append(diboson_sample)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# higgs
higgs_sample = Sample( "Higgs" , kOrange-5 )

higgs_sample.setStatConfig(use_stat)
higgs_sample.setNormByTheory()
sample_list.append(higgs_sample)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# data
data_sample = Sample("data",kBlack)
data_sample.setData()
sample_list.append(data_sample)

# set the file from which the samples should be taken
for sl in sample_list:
    sl.setFileList(bkg_files)

# ----------
# - Binnings
# ----------
# TODO reset the binning and add more histograms

# flavor channel binning
flavor_channel_bin = 5
flavor_channel_min = -0.5
flavor_channel_max = flavor_channel_min + flavor_channel_bin

# pt binning
pt_bin = 10 if not single_bin_regions else 1
pt_min = 0
pt_max = 500

# mbbll binning
mbbll_bin = 6 if not single_bin_regions else 1
mbbll_min = 0
mbbll_max = 1200

# mbl binning
mbl_bin = 6 if not single_bin_regions else 1
mbl_min = 0
mbl_max = 1200

# ptbl binning
ptbl_bin = 6 if not single_bin_regions else 1
ptbl_min = 0
ptbl_max = 600

# ptll binning
ptll_bin = 6 if not single_bin_regions else 1
ptll_min = 0
ptll_max = 600

# ptbbll binning
ptbbll_bin = 6 if not single_bin_regions else 1
ptbbll_min = 0
ptbbll_max = 600

# mll binning
mll_bin = 10 if not single_bin_regions else 1
mll_min = 0
mll_max = 500

mll_inz_bin = 6 if not single_bin_regions else 1
mll_inz_min = 75
mll_inz_max = 105

# ht binning
ht_bin = 11 if not single_bin_regions else 1
ht_min = 0
ht_max = 1100

ht_sr_bin = 19 if not single_bin_regions else 1
ht_sr_min = 1100
ht_sr_max = 3000

# mbl asym binning
mbl_asym_bin = 5 if not single_bin_regions else 1
mbl_asym_min = 0
mbl_asym_max = 1.

# met significance binning
met_sig_bin = 10 if not single_bin_regions else 1
met_sig_min = 0
met_sig_max = 500

# met et binning
met_et_bin = 5 if not single_bin_regions else 1
met_et_min = 0
met_et_max = 100

# dphi binning
dphi_bin = 8 if not single_bin_regions else 1
dphi_min = 0
dphi_max = 3.2

# deta binning
deta_bin = 4 if not single_bin_regions else 1
deta_min = 0
deta_max = 4

# dr binning
dr_bin = 4 if not single_bin_regions else 1
dr_min = 0
dr_max = 4

# SR binning (this is just a single bin cut and count binning)
srNBins = 1
srBinLow = 0.5
srBinHigh = 1.5

# **************
# * Bkg only fit
# **************
background_config = configMgr.addFitConfig("BkgOnly")
if use_stat:
    background_config.statErrThreshold = 0.05
else:
    background_config.statErrThreshold = None
background_config.addSamples(sample_list)

# Systematics to be applied globally within this topLevel
background_config.addSystematic(btag_sf_uncert)
background_config.addSystematic(jes_uncert)
background_config.addSystematic(jer_uncert)

meas = background_config.addMeasurement(name = "NormalMeasurement", lumi = 1.0, lumiErr = 0.039 )
meas.addPOI("mu_SIG")

# --------------------------------------------------
# - Constraining regions - statistically independent
# --------------------------------------------------
cr_list = []
# Add Top CR for background
for cr_name in ['CR_top_', 'CR_Z_']:
    # for flavor_channel in ['ee', 'mm', 'em']:
    for flavor_channel in ['all']:
        if cr_name  == 'CR_Z_' and flavor_channel == 'em': continue

        # cr_list.append( background_config.addChannel( "flavor_channel", ['%s%s' % (cr_name, flavor_channel)], flavor_channel_bin, flavor_channel_min, flavor_channel_max) )
        cr_list.append( background_config.addChannel( "mbl_0"         , ['%s%s' % (cr_name, flavor_channel)], mbl_bin           , mbl_min           , mbl_max           ) )
        ## cr_list.append( background_config.addChannel( "mbl_1"         , ['%s%s' % (cr_name, flavor_channel)], mbl_bin           , mbl_min           , mbl_max           ) )
        ## if cr_name == 'CR_Z_':
        ##     cr_list.append( background_config.addChannel( "mll"       , ['%s%s' % (cr_name, flavor_channel)], mll_inz_bin       , mll_inz_min       , mll_inz_max       ) )
        ## else:
        ##     cr_list.append( background_config.addChannel( "mll"       , ['%s%s' % (cr_name, flavor_channel)], mll_bin           , mll_min           , mll_max           ) )
        ## cr_list.append( background_config.addChannel( "ht_signal"     , ['%s%s' % (cr_name, flavor_channel)], ht_bin            , ht_min            , ht_max            ) )
        ## cr_list.append( background_config.addChannel( 'mbl_asym'      , ['%s%s' % (cr_name, flavor_channel)], mbl_asym_bin      , mbl_asym_min      , mbl_asym_max      ) )
        ## cr_list.append( background_config.addChannel( 'met_sig_signal', ['%s%s' % (cr_name, flavor_channel)], met_sig_bin       , met_sig_min       , met_sig_max       ) )

background_config.setBkgConstrainChannels(cr_list)

###############################
#                             #
#    Example new cosmetics    #
#                             #
###############################
# Set global plotting colors/styles
background_config.dataColor      = data_sample.color
background_config.totalPdfColor  = kBlue
background_config.errorFillColor = kBlue-5
background_config.errorFillStyle = 3004
background_config.errorLineStyle = kDashed
background_config.errorLineColor = kBlue-5

for crl in cr_list:
    crl.useOverflowBin = True
    crl.titleY = "Entries"
    crl.logY = True
    crl.ATLASLabelX = 0.25
    crl.ATLASLabelY = 0.85
    crl.ATLASLabelText = "Work in progress"

# ---------------------------------------------------------------
# - Validation regions - not necessarily statistically independent
# ---------------------------------------------------------------
vr_list = []
if do_validation:
    print 'Setting up validation regions!'
    for vr_name in ['VR_3' , 'VR_5']:
        for flavor_channel in ['_all', '_ee', '_mm', '_em']:
            if not vr_name == 'VR_llbb' and flavor_channel == '': continue
            if vr_name  == 'VR_5' and flavor_channel == '_em': continue

            if flavor_channel == '_all':
                vr_list.append( background_config.addChannel( "flavor_channel", ['%s%s' % (vr_name, flavor_channel)], flavor_channel_bin, flavor_channel_min, flavor_channel_max) )

            vr_list.append( background_config.addChannel( 'mbl_0'    , ['%s%s' % (vr_name, flavor_channel)], mbl_bin   , mbl_min   , mbl_max    ) )
            vr_list.append( background_config.addChannel( 'mbl_1'    , ['%s%s' % (vr_name, flavor_channel)], mbl_bin   , mbl_min   , mbl_max    ) )
            ## # vr_list.append( background_config.addChannel( 'mbbll'    , ['%s%s' % (vr_name, flavor_channel)], mbbll_bin , mbbll_min , mbbll_max  ) )
            ## # vr_list.append( background_config.addChannel( 'ptbl_0'   , ['%s%s' % (vr_name, flavor_channel)], ptbl_bin  , ptbl_min  , ptbl_max   ) )
            ## # vr_list.append( background_config.addChannel( 'ptbl_1'   , ['%s%s' % (vr_name, flavor_channel)], ptbl_bin  , ptbl_min  , ptbl_max   ) )
            ## # vr_list.append( background_config.addChannel( 'ptbbll'   , ['%s%s' % (vr_name, flavor_channel)], ptbbll_bin, ptbbll_min, ptbbll_max ) )
            ## if vr_name == 'VR_5':
            ##     vr_list.append( background_config.addChannel( 'mll'      , ['%s%s' % (vr_name, flavor_channel)], mll_inz_bin , mll_inz_min, mll_inz_max ) )
            ## else:
            ##     vr_list.append( background_config.addChannel( 'mll'      , ['%s%s' % (vr_name, flavor_channel)], mll_bin     , mll_min    , mll_max     ) )
            ## # vr_list.append( background_config.addChannel( 'ptll'     , ['%s%s' % (vr_name, flavor_channel)], ptll_bin  , ptll_min  , ptll_max   ) )
            ## vr_list.append( background_config.addChannel( 'met_et'        , ['%s%s' % (vr_name, flavor_channel)], met_et_bin , met_et_min , met_et_max  ) )
            ## vr_list.append( background_config.addChannel( 'met_sig_signal', ['%s%s' % (vr_name, flavor_channel)], met_sig_bin, met_sig_min, met_sig_max ) )
            vr_list.append( background_config.addChannel( 'ht_signal'     , ['%s%s' % (vr_name, flavor_channel)], ht_bin     , ht_min     , ht_max      ) )
            ## vr_list.append( background_config.addChannel( 'pt_l_0'        , ['%s%s' % (vr_name, flavor_channel)], pt_bin     , pt_min     , pt_max      ) )
            ## vr_list.append( background_config.addChannel( 'pt_l_1'        , ['%s%s' % (vr_name, flavor_channel)], pt_bin     , pt_min     , pt_max      ) )
            ## vr_list.append( background_config.addChannel( 'pt_b_0'        , ['%s%s' % (vr_name, flavor_channel)], pt_bin     , pt_min     , pt_max      ) )
            ## vr_list.append( background_config.addChannel( 'pt_b_1'        , ['%s%s' % (vr_name, flavor_channel)], pt_bin     , pt_min     , pt_max      ) )
            ## ## # vr_list.append( background_config.addChannel( 'dphi_bl_0', ['%s%s' % (vr_name, flavor_channel)], dphi_bin  , dphi_min  , dphi_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'dphi_bl_1', ['%s%s' % (vr_name, flavor_channel)], dphi_bin  , dphi_min  , dphi_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'deta_bl_0', ['%s%s' % (vr_name, flavor_channel)], deta_bin  , deta_min  , deta_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'deta_bl_1', ['%s%s' % (vr_name, flavor_channel)], deta_bin  , deta_min  , deta_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'dr_bl_0'  , ['%s%s' % (vr_name, flavor_channel)], dr_bin    , dr_min    , dr_max     ) )
            ## ## # vr_list.append( background_config.addChannel( 'dr_bl_1'  , ['%s%s' % (vr_name, flavor_channel)], dr_bin    , dr_min    , dr_max     ) )
            ## ## # vr_list.append( background_config.addChannel( 'dphi_ll'  , ['%s%s' % (vr_name, flavor_channel)], dphi_bin  , dphi_min  , dphi_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'deta_ll'  , ['%s%s' % (vr_name, flavor_channel)], deta_bin  , deta_min  , deta_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'dr_ll'    , ['%s%s' % (vr_name, flavor_channel)], dr_bin    , dr_min    , dr_max     ) )
            ## ## # vr_list.append( background_config.addChannel( 'dphi_bb'  , ['%s%s' % (vr_name, flavor_channel)], dphi_bin  , dphi_min  , dphi_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'deta_bb'  , ['%s%s' % (vr_name, flavor_channel)], deta_bin  , deta_min  , deta_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'dr_bb'    , ['%s%s' % (vr_name, flavor_channel)], dr_bin    , dr_min    , dr_max     ) )

    for vr_name in ['CR_top_', 'CR_Z_']:
        for flavor_channel in ['all', 'ee', 'mm', 'em']:
            if vr_name  == 'CR_Z_' and flavor_channel == 'em': continue
            if flavor_channel == 'all':
                vr_list.append( background_config.addChannel( "flavor_channel", ['%s%s' % (vr_name, flavor_channel)], flavor_channel_bin, flavor_channel_min, flavor_channel_max) )

            if not flavor_channel == 'all':
                vr_list.append( background_config.addChannel( 'mbl_0'    , ['%s%s' % (vr_name, flavor_channel)], mbl_bin   , mbl_min   , mbl_max    ) )
            vr_list.append( background_config.addChannel( 'mbl_1'    , ['%s%s' % (vr_name, flavor_channel)], mbl_bin   , mbl_min   , mbl_max    ) )
            ## # vr_list.append( background_config.addChannel( 'mbbll'    , ['%s%s' % (vr_name, flavor_channel)], mbbll_bin , mbbll_min , mbbll_max  ) )
            ## # vr_list.append( background_config.addChannel( 'ptbl_0'   , ['%s%s' % (vr_name, flavor_channel)], ptbl_bin  , ptbl_min  , ptbl_max   ) )
            ## # vr_list.append( background_config.addChannel( 'ptbl_1'   , ['%s%s' % (vr_name, flavor_channel)], ptbl_bin  , ptbl_min  , ptbl_max   ) )
            ## # vr_list.append( background_config.addChannel( 'ptbbll'   , ['%s%s' % (vr_name, flavor_channel)], ptbbll_bin, ptbbll_min, ptbbll_max ) )
            ## if vr_name == 'VR_5':
            ##     vr_list.append( background_config.addChannel( 'mll'      , ['%s%s' % (vr_name, flavor_channel)], mll_inz_bin , mll_inz_min, mll_inz_max ) )
            ## else:
            ##     vr_list.append( background_config.addChannel( 'mll'      , ['%s%s' % (vr_name, flavor_channel)], mll_bin     , mll_min    , mll_max     ) )
            ## # vr_list.append( background_config.addChannel( 'ptll'     , ['%s%s' % (vr_name, flavor_channel)], ptll_bin  , ptll_min  , ptll_max   ) )
            ## vr_list.append( background_config.addChannel( 'met_et'        , ['%s%s' % (vr_name, flavor_channel)], met_et_bin , met_et_min , met_et_max  ) )
            ## vr_list.append( background_config.addChannel( 'met_sig_signal', ['%s%s' % (vr_name, flavor_channel)], met_sig_bin, met_sig_min, met_sig_max ) )
            vr_list.append( background_config.addChannel( 'ht_signal'     , ['%s%s' % (vr_name, flavor_channel)], ht_bin     , ht_min     , ht_max      ) )
            ## vr_list.append( background_config.addChannel( 'pt_l_0'        , ['%s%s' % (vr_name, flavor_channel)], pt_bin     , pt_min     , pt_max      ) )
            ## vr_list.append( background_config.addChannel( 'pt_l_1'        , ['%s%s' % (vr_name, flavor_channel)], pt_bin     , pt_min     , pt_max      ) )
            ## vr_list.append( background_config.addChannel( 'pt_b_0'        , ['%s%s' % (vr_name, flavor_channel)], pt_bin     , pt_min     , pt_max      ) )
            ## vr_list.append( background_config.addChannel( 'pt_b_1'        , ['%s%s' % (vr_name, flavor_channel)], pt_bin     , pt_min     , pt_max      ) )
            ## ## # vr_list.append( background_config.addChannel( 'dphi_bl_0', ['%s%s' % (vr_name, flavor_channel)], dphi_bin  , dphi_min  , dphi_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'dphi_bl_1', ['%s%s' % (vr_name, flavor_channel)], dphi_bin  , dphi_min  , dphi_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'deta_bl_0', ['%s%s' % (vr_name, flavor_channel)], deta_bin  , deta_min  , deta_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'deta_bl_1', ['%s%s' % (vr_name, flavor_channel)], deta_bin  , deta_min  , deta_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'dr_bl_0'  , ['%s%s' % (vr_name, flavor_channel)], dr_bin    , dr_min    , dr_max     ) )
            ## ## # vr_list.append( background_config.addChannel( 'dr_bl_1'  , ['%s%s' % (vr_name, flavor_channel)], dr_bin    , dr_min    , dr_max     ) )
            ## ## # vr_list.append( background_config.addChannel( 'dphi_ll'  , ['%s%s' % (vr_name, flavor_channel)], dphi_bin  , dphi_min  , dphi_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'deta_ll'  , ['%s%s' % (vr_name, flavor_channel)], deta_bin  , deta_min  , deta_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'dr_ll'    , ['%s%s' % (vr_name, flavor_channel)], dr_bin    , dr_min    , dr_max     ) )
            ## ## # vr_list.append( background_config.addChannel( 'dphi_bb'  , ['%s%s' % (vr_name, flavor_channel)], dphi_bin  , dphi_min  , dphi_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'deta_bb'  , ['%s%s' % (vr_name, flavor_channel)], deta_bin  , deta_min  , deta_max   ) )
            ## ## # vr_list.append( background_config.addChannel( 'dr_bb'    , ['%s%s' % (vr_name, flavor_channel)], dr_bin    , dr_min    , dr_max     ) )

    for vr in vr_list:
        vr.useOverflowBin = True

    background_config.setValidationChannels( vr_list )

# ------------------------------------------------------------------------------
# - set up SRs
# ------------------------------------------------------------------------------
if not myFitType == FitType.Discovery:
# if myFitType == FitType.Exclusion:
    sr_list = []
    for flavor_channel in ['ee', 'mm', 'em']:
        this_sr_name = "SR_%s" % flavor_channel
        this_mbl_bin = mbl_bin if not single_bin_signal and not single_bin_regions else 1
        sr_list.append( background_config.addChannel( "mbl_0"
                                                    , [ this_sr_name]
                                                    , this_mbl_bin
                                                    , mbl_min
                                                    , mbl_max
                                                    )
                      )
        # sr_list.append( background_config.addChannel( "mbl_1"
        #                                             , [ this_sr_name]
        #                                             , this_mbl_bin
        #                                             , mbl_min
        #                                             , mbl_max
        #                                             )
        #               )

    for sr in sr_list:
        sr.useUnderflowBin = True
        sr.useOverflowBin  = True
        sr.titleY = "Entries"
        sr.logY = True
        sr.ATLASLabelX = 0.25
        sr.ATLASLabelY = 0.85
        sr.ATLASLabelText = "Work in progress"

    background_config.setSignalChannels(sr_list)

# ---------------
# - Discovery fit
# ---------------
if myFitType == FitType.Discovery:
    print 'ERROR!!! DISCOVERY FIT IS NOT YET CONFIGURED!!!'

# -------------------------------------------------------
# - Exclusion fits (1-step simplified model in this case)
# -------------------------------------------------------
if myFitType == FitType.Exclusion:
    print 'Setting up exclusion fit!'
    sig_sample_list=['sig_500', 'sig_600', 'sig_700', 'sig_800', 'sig_900', 'sig_1000']
    # sig_sample_list=['sig_1000']
    # sig_sample_list=['sig_500']
    sig_samples = []
    for sig in sig_sample_list:
        print 'setting up signal sample: ' , sig
        exclusion_sr_config = configMgr.addFitConfigClone( background_config , "Sig_excl_%s" % sig )

        sig_sample = Sample(sig, kViolet+5)
        sig_sample.setStatConfig(use_stat)
        sig_sample.setFileList(sig_files)
        sig_sample.setNormByTheory()
        sig_sample.setNormFactor("mu_SIG", 1., 0., 5.)

        exclusion_sr_config.addSamples(sig_sample)
        exclusion_sr_config.setSignalSample(sig_sample)
        exclusion_sr_config.setSignalChannels(sr_list)

# ----------------
# - Create TLegend
# ----------------
# TCanvas is needed for that, but it gets deleted afterwards
c = TCanvas()
compFillStyle = 1001 # see ROOT for Fill styles
leg = TLegend(0.6, 0.475, 0.9, 0.925, "")
leg.SetFillStyle(0)
leg.SetFillColor(0)
leg.SetBorderSize(0)

# Data entry
entry = TLegendEntry()
entry = leg.AddEntry("", "Data 2012 (#sqrt{s}=8 TeV)", "p")
entry.SetMarkerColor(background_config.dataColor)
entry.SetMarkerStyle(20)

# Total PDF
entry = leg.AddEntry("", "Total pdf", "lf")
entry.SetLineColor(background_config.totalPdfColor)
entry.SetLineWidth(2)
entry.SetFillColor(background_config.errorFillColor)
entry.SetFillStyle(background_config.errorFillStyle)

# ttbar entry
entry = leg.AddEntry("", "t#bar{t}", "lf")
entry.SetLineColor(ttbar_sample.color)
entry.SetFillColor(ttbar_sample.color)
entry.SetFillStyle(compFillStyle)

# Z/gamma* entry
entry = leg.AddEntry("", "Z/#gamma*", "lf")
entry.SetLineColor(z_sample.color)
entry.SetFillColor(z_sample.color)
entry.SetFillStyle(compFillStyle)

# Single top entry
entry = leg.AddEntry("", "Single top", "lf")
entry.SetLineColor(single_top_sample.color)
entry.SetFillColor(single_top_sample.color)
entry.SetFillStyle(compFillStyle)

# ttV entry
entry = leg.AddEntry("", "ttV", "lf")
entry.SetLineColor(ttv_sample.color)
entry.SetFillColor(ttv_sample.color)
entry.SetFillStyle(compFillStyle)

# Diboson entry
entry = leg.AddEntry("", "Diboson", "lf")
entry.SetLineColor(diboson_sample.color)
entry.SetFillColor(diboson_sample.color)
entry.SetFillStyle(compFillStyle)

# Higgs entry
entry = leg.AddEntry("", "Higgs", "lf")
entry.SetLineColor(higgs_sample.color)
entry.SetFillColor(higgs_sample.color)
entry.SetFillStyle(compFillStyle)

# If exclusion mode, add signal entry
if myFitType==FitType.Exclusion:
    entry = leg.AddEntry("", "signal", "lf")
    entry.SetLineColor(kViolet+5)
    entry.SetFillColor(kViolet+5)
    entry.SetFillStyle(compFillStyle)

# Set legend for fitConfig
background_config.tLegend = leg
if myFitType==FitType.Exclusion:
    exclusion_sr_config.tLegend = leg
c.Close()

print 'done with my stuff'
print '--------------------------------------------------------------------------------'
print ''