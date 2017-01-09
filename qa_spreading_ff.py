#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2016 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import comm_swig as comm
import subprocess

class qa_spreading_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_spreading_ff (self):
    	src_data = (-1,1) 	
        
        xr = (0,1,1,0,0,0,0,
              1,0,1,1,
       	      )
       	      
        expected_result = tuple([float(x) for x in xr])
 
# 	expected_result = 20
 		
 	src = blocks.vector_source_f(src_data)
        sprd = comm.spreading_ff()
        dst = blocks.vector_sink_f()
        
        self.tb.connect(src, sprd)
        self.tb.connect(sprd, dst)
        self.tb.run()
        
        result_data = dst.data()
        
        L = min(len(result_data), len(expected_result))
      	
      	self.assertEqual(expected_result[0:L], result_data[0:L])
        
#        self.assertEqual(expected_result,result_data)	
        print "Working"

#    def test_002_spreading_ff (self):
#    	src_data = (1,-1)
#        expected_result = (1,-1)
#        src = blocks.vector_source_f(src_data)
#        sprd = comm.spreading_ff()
#        dst = blocks.vector_sink_f()
#        self.tb.connect(src, sprd)
#        self.tb.connect(sprd, dst)
#        self.tb.run()
#        result_data = dst.data()
        
      #  for i in range(len(result_data)):
 #       self.assertFloatTuplesAlmostEqual(expected_result, result_data, 2)
 #       print "test 002 - END "
        
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_spreading_ff, "qa_spreading_ff.xml")
