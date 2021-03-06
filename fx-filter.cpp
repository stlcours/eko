#include "fx-filter.h"

/*

this code based on Martin Finke's filter tutorial,
where the filter itself based on the resonant filter 
by Paul Kellett http://www.musicdsp.org/showone.php?id=29
*/

float CFilter::process (float sample, size_t channel)
{
  if (channel == 0)
     {
      bufl0 += cutoff * (sample - bufl0 + feedback_amount * (bufl0 - bufl1)); //add reso
      bufl1 += cutoff * (bufl0 - bufl1);
   
      bufl2 += cutoff * (bufl1 - bufl2);
      bufl3 += cutoff * (bufl2 - bufl3);
   
      switch (mode) 
             {
              case FILTER_MODE_LOWPASS:
                    return bufl1;
                    
              case FILTER_MODE_HIGHPASS:
                   return sample - bufl0;
                   
              case FILTER_MODE_BANDPASS:
                   return bufl0 - bufl3;
                   
               default:
                       return 0.0f;
             }
     }  
  else
      {
       bufr0 += cutoff * (sample - bufr0 + feedback_amount * (bufr0 - bufr1)); //add reso
       bufr1 += cutoff * (bufr0 - bufr1);
   
       bufr2 += cutoff * (bufr1 - bufr2);
       bufr3 += cutoff * (bufr2 - bufr3);
   
       switch (mode) 
          {
           case FILTER_MODE_LOWPASS:
                return bufr1;
                
           case FILTER_MODE_HIGHPASS:
                return sample - bufr0;
                
           case FILTER_MODE_BANDPASS:
                return bufr0 - bufr3;
                
           default:
             return 0.0f;
         }
         
       }  
   
   return 0.0f;      
}


CFilter::CFilter()
{
  cutoff = 0.99f;
  resonance = 0.0f;
  mode = FILTER_MODE_LOWPASS;
  
  bufl0 = 0.0f;
  bufl1 = 0.0f;
  bufl2 = 0.0f;
  bufl3 = 0.0f;
  bufr0 = 0.0f;
  bufr1 = 0.0f;
  bufr2 = 0.0f;
  bufr3 = 0.0f;
  
  calc_feedback_amount();
}

void CFilter::reset()
{
  bufl0 = 0.0f;
  bufl1 = 0.0f;
  bufl2 = 0.0f;
  bufl3 = 0.0f;
  bufr0 = 0.0f;
  bufr1 = 0.0f;
  bufr2 = 0.0f;
  bufr3 = 0.0f;
  
  calc_feedback_amount();
} 
