/*****************************************************************************\

Name:   simple_frontend.cxx
Author: Matthias W. Smith
Email:  mwsmith2@uw.edu

About:  A simple example frontend that generates a random point.
        
\*****************************************************************************/


//--- std includes ----------------------------------------------------------//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <random>
#include <sys/time.h>
using std::string;

//--- other includes --------------------------------------------------------//
#include "midas.h"

//--- project includes ------------------------------------------------------//
#include "frontend_utils.hh"
#include "field_structs.hh"

//--- globals ---------------------------------------------------------------//

#define FRONTEND_NAME @BLANK // Prefer capitalize with spaces
const char * const bank_name = @BLANK; // 4 letters, try to make sensible

// Any structs need to be defined.
BANK_LIST trigger_bank_list[] = {
  {bank_name, @TYPE(TID_WORD, etc), @BANK_LENGTH, NULL},
  {""}
};
// @EXAMPLE END

extern "C" {
  
  // The frontend name (client name) as seen by other MIDAS clients
  char *frontend_name = (char*)FRONTEND_NAME;

  // The frontend file name, don't change it.
  char *frontend_file_name = (char*)__FILE__;
  
  // frontend_loop is called periodically if this variable is TRUE
  BOOL frontend_call_loop = FALSE;
  
  // A frontend status page is displayed with this frequency in ms.
  INT display_period = 1000;
  
  // maximum event size produced by this frontend
  INT max_event_size = 0x8000; // 32 kB @EXAMPLE - adjust if neeeded

  // maximum event size for fragmented events (EQ_FRAGMENTED)
  INT max_event_size_frag = 0x800000; // DEPRECATED
  
  // buffer size to hold events
  INT event_buffer_size = 0x800000;
  
  // Function declarations
  INT frontend_init();
  INT frontend_exit();
  INT begin_of_run(INT run_number, char *error);
  INT end_of_run(INT run_number, char *error);
  INT pause_run(INT run_number, char *error);
  INT resume_run(INT run_number, char *error);

  INT frontend_loop();
  INT read_trigger_event(char *pevent, INT off);
  INT poll_event(INT source, INT count, BOOL test);
  INT interrupt_configure(INT cmd, INT source, PTYPE adr);

  // Equipment list @EXAMPLE BEGIN

  EQUIPMENT equipment[] = 
    {
      {FRONTEND_NAME,   // equipment name 
       { 10, 0,         // event ID, trigger mask 
         "SYSTEM",      // event buffer
         @EQ_TYPE,      // equipment type (EQ_POLLED, EQ_PERIODIC)
         0,             // not used 
         "MIDAS",       // format 
         TRUE,          // enabled 
         RO_RUNNING,    // read only when running 
         10,            // poll for 10 ms 
         0,             // stop run after this event limit 
         0,             // number of sub events 
         0,             // don't log history 
         "", "", "",
       },
       read_trigger_event,      // readout routine 
       NULL,
       NULL,
       NULL, 
      },

      {""}
    };

} //extern C

// @USER - Put necessary globals in an anonomous namespace here.
namespace {
boost::property_tree::ptree conf;
boost::property_tree::ptree global_conf;
} 

//--- Frontend Init ---------------------------------------------------------//
INT frontend_init() 
{
  return SUCCESS;
}

//--- Frontend Exit ---------------------------------------------------------//
INT frontend_exit()
{
  return SUCCESS;
}

//--- Begin of Run ----------------------------------------------------------//
INT begin_of_run(INT run_number, char *error)
{

  int rc = load_global_settings(global_conf);
  if (rc != 0) {
    cm_msg(MERROR, "begin_of_run", "could not load global settings");
    return rc;
  }
 
  rc = load_settings(frontend_name, conf);
  if (rc != 0) {
    cm_msg(MERROR, "begin_of_run", "could not load equipment settings");
    return rc;
  }

  // @USER - retrieve ODB params here
  // local_example = conf.get<double>("local_example", [optional default])

  return SUCCESS;
}

//--- End of Run ------------------------------------------------------------//
INT end_of_run(INT run_number, char *error)
{
  return SUCCESS;
}

//--- Pause Run -------------------------------------------------------------//
INT pause_run(INT run_number, char *error)
{
  return SUCCESS;
}

//--- Resume Run ------------------------------------------------------------//
INT resume_run(INT run_number, char *error)
{
  return SUCCESS;
}

//--- Frontend Loop ---------------------------------------------------------//

INT frontend_loop()
{
  // If frontend_call_loop is true, this routine gets called when
  // the frontend is idle or once between every event
  return SUCCESS;
}

//---------------------------------------------------------------------------//

/****************************************************************************\
  
  Readout routines for different events

\*****************************************************************************/

//--- Trigger event routines ------------------------------------------------//

INT poll_event(INT source, INT count, BOOL test) {

  static unsigned int i;

  // fake calibration
  if (test) {
    for (i = 0; i < count; i++) {
      usleep(10);
    }
    return 0;
  }

  // Check hardware for events, just random here.
  if (@CHECK_FOR_EVENT)
    return 1;
  } else {
    return 0;
  }
}

//--- Interrupt configuration ---------------------------------------*/

INT interrupt_configure(INT cmd, INT source, PTYPE adr)
{
  switch (cmd) {
  case CMD_INTERRUPT_ENABLE:
    break;
  case CMD_INTERRUPT_DISABLE:
    break;
  case CMD_INTERRUPT_ATTACH:
    break;
  case CMD_INTERRUPT_DETACH:
    break;
  }
  return SUCCESS;
}

//--- Event readout -------------------------------------------------*/

INT read_trigger_event(char *pevent, INT off)
{
  @BANK_MIDAS_TYPE (DWORD) *pdata;

  // And MIDAS output.
  bk_init32(pevent);

  // Let MIDAS allocate the struct.
  bk_create(pevent, bank_name, @TID_TYPE, &pdata);

  // Copy data to pdata
  // memcpy(pdata, &@USER_DATA, sizeof(point));
  //  pdata += sizeof(@USER_DATA);

  // Need to increment pointer and close.
  bk_close(pevent, pdata);

  return bk_size(pevent);
}
