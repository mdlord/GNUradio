/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "spreading_ff_impl.h"

namespace gr {
  namespace comm {

    spreading_ff::sptr
    spreading_ff::make()
    {
      return gnuradio::get_initial_sptr
        (new spreading_ff_impl());
    }

    /*
     * The private constructor
     */
    spreading_ff_impl::spreading_ff_impl()
      : gr::block("spreading_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    spreading_ff_impl::~spreading_ff_impl()
    {
    }

    void 
    spreading_ff_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
    	//for(int i = 0; i < ninput_items_required.size(); i++)
    	//{
        	ninput_items_required[0] = noutput_items; 
    	//}
    }

    int
    spreading_ff_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        float *out = (float *) output_items[0];
	
	float SL = 10;
	float r_bifurcation = 4;
	float initial = 0.1121;        
	float sp[10];
	sp[0] = r_bifurcation*(1-initial)*initial;
	
	for(int i =1; i < SL; i++)
	{
		sp[i] = r_bifurcation*sp[i-1]*(1-sp[i-1]);
	}
	
	float sp_seq[10];
	float tau = 0.5;
	 
	//noutput_items = SL;
	
	for (int i = 0; i < SL; i++)
	{
	//	out[i]= sp[i];
	
		if(sp[i]< tau)
			sp_seq[i] = -1;
			//out[i] = -1;
		else
			sp_seq[i] = 1;
			//out[i] = 1;
			
	}
	
	int k = 0;
	for(int i = 0; i < noutput_items; i++)
	{
		for(int j = 0; j < SL; j++)
		{
			if(sp_seq[j]==1 && in[i]>0)
				out[k] = 0;
			else if(sp_seq[j]==-1 && in[i]>0)
				out[k] = 1;
			else if(sp_seq[j]==1 && in[i]<0)
				out[k] = 1;
			else if(sp_seq[j]==-1 && in[i]<0)
				out[k] = 0;
				
		k++;
		} 
	}
	
	//out[0] = k;
	
        // Do <+signal processing+>
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we 	 produced.
        return noutput_items;
    }

  } /* namespace comm */
} /* namespace gr */

