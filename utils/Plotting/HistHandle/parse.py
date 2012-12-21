#!/usr/bin/env python

import sys
import inspect
import os.path
import optparse
import time

import yaml

import metaroot
import ROOT

import HistHandle as hh

# ==============================================================================
class InputContainer(object):
    # --------------------------------------------------------------------------
    def __init__(self, input_dict):
        self.name = input_dict['name']
        self.color = input_dict['color']
        self.marker_style = input_dict['marker_style']
        self.entries = []
        for e in input_dict['entries']:
            self.entries.append(EntryContainer(e))

        self.hist_info = hh.Objects.HistInfo( self.name
                                            , self.color
                                            , self.color
                                            , self.marker_style
                                            )

    # ------------------------------------------------------------------------------
    def getInputFileList(self):
        # input_file_list = {}
        input_file_list = []
        for e in self.entries:
            input_file_list.append(e.file_list)
            # input_file_list[e.label] = e.file_list
        # return input_file_list
        return hh.Helper.flatten(input_file_list)

    # --------------------------------------------------------------------------
    def genHistMerger( self
                     , dir_name
                     , hist_name
                     ):
        hist_handle_dict = {}
        for e in self.entries:
            hist_handle_dict[e.label] = e.genHistHandle(dir_name, hist_name)
        tmp =  hh.Merger.HistMerger( dir_name
                                   , hist_name
                                   , hist_handle_dict
                                   , self.hist_info
                                   )
        tmp.genMergedHist()
        return tmp

# ==============================================================================
class EntryContainer(object):
    # --------------------------------------------------------------------------
    def __init__( self
                , entry_dict
                ):
        self.label =        entry_dict['label']
        self.fill_color =   entry_dict['fill_color']
        self.fill_color =   entry_dict['fill_color']
        self.line_color =   entry_dict['line_color']
        self.marker_style = entry_dict['marker_style']
        self.inputs =       entry_dict['inputs']

        self.lumi_modeled_in_file = 1.
        self.target_lumi = 1.
        if 'lumi_modeled_in_file' in entry_dict and 'target_lumi' in entry_dict:
            self.lumi_modeled_in_file = entry_dict['lumi_modeled_in_file']
            self.target_lumi = entry_dict['target_lumi']

        self.file_list = [ ROOT.TFile(f) for f in self.inputs ]

        self.hist_info = hh.Objects.HistInfo( self.label
                                            , self.line_color
                                            , self.fill_color
                                            , self.marker_style
                                            )

    # --------------------------------------------------------------------------
    def genHistHandle( self
                     , dir_name
                     , hist_name
                     ):
        return hh.Handle.HistHandle( dir_name
                                   , hist_name
                                   , self.hist_info
                                   , self.file_list
                                   , self.lumi_modeled_in_file
                                   , self.target_lumi
                                   )

# ==============================================================================
class OptimizeContainer(object):
    # --------------------------------------------------------------------------
    def __init__(self, input_dict):
        self.cut_dir =      input_dict['cut_dir']
        self.optimize_dir = self.cut_dir
        if 'optimize_dir' in input_dict:
            self.optimize_dir = input_dict['optimize_dir']
        self.to_optimize =  input_dict['to_optimize']
        self.direction =    input_dict['direction']
        self.fixed_points = input_dict['fixed_points']
        self.scan = bool(input_dict['scan'])

        if   self.direction == 'right': self.direction = hh.right
        elif self.direction == 'left':  self.direction = hh.left
        else: assert False

# ------------------------------------------------------------------------------
def parseInputs():
    # TODO do proper parsing so we aren't sensitive to order of inputs
    global_config_file = sys.argv[1]
    config_dict = processConfigFile(global_config_file)

    outfile = sys.argv[2]

    return { 'config':config_dict['config']
           , 'files':config_dict['files']
           , 'optimize':config_dict['optimize']
           , 'outfile':outfile
           }

# ------------------------------------------------------------------------------
def interpretEnvVariables(string):
    if type(string) == str:
        while not string.find("$") == -1:
            search_begin = string.find("${") + 2
            search_end = string.find("}")
            search_key = string[search_begin:search_end]
            string = string.replace( "${%s}" % search_key
                                   , os.environ.get(search_key)
                                   )
    return string

# ------------------------------------------------------------------------------
def processConfigFile(config_file_name):
    print 'config_file_name: %s ' % config_file_name
    config_file = open(config_file_name)
    config_dict = yaml.load(config_file)

    input_block = processInputBlock(config_dict['Inputs'])
    input_containers = input_block['config']
    input_files      = input_block['files']

    optimize_block = None
    if 'Optimize' in config_dict:
        optimize_block = processOptimizeBlock(config_dict['Optimize'])

    return { 'config':input_containers
           , 'files':input_files
           , 'optimize':optimize_block
           }

# ------------------------------------------------------------------------------
def processInputBlock(input_dict):
    input_containers = {}
    input_files = []
    for inp in input_dict:
        key = inp['class']
        input_containers[key] = InputContainer(inp)

        input_files.append(input_containers[key].getInputFileList())

    input_files = hh.Helper.flatten(input_files)

    return {'config':input_containers, 'files':input_files}

# ------------------------------------------------------------------------------
def processOptimizeBlock(input_dict):
    optimizations = {}
    for inp in input_dict:
        optimizations[inp['cut_dir']] = OptimizeContainer(inp)

    return optimizations
