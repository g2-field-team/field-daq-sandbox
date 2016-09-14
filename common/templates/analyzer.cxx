/**************************************************************************** \

  file:    @ANALYZER_NAME.cxx
  author:  @USER
  email:   @USER_EMAIL

  about:   A template front-end

\*****************************************************************************/

//--- std includes ----------------------------------------------------------//
#include <string>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <iomanip>
using std::string;
using std::cout;
using std::endl;

//--- other includes --------------------------------------------------------//
#include "midas.h"

//--- project includes ------------------------------------------------------//

//--- global variables ------------------------------------------------------//

// The analyzer name (client name) as seen by other MIDAS clients
char *analyzer_name = (char *)@ANALYZER_NAME;

// analyzer_loop is called with this interval in ms (0 to disable)  
INT analyzer_loop_period = 0;

// default ODB size 
INT odb_size = DEFAULT_ODB_SIZE;

//--- module declaration ----------------------------------------------------//

BANK_LIST analyzer_bank_list[] = {
  {@BANK_NAME, @TID_TYPE, @BANK_LENGTH, NULL},
  {""}
};

//-- event request list -----------------------------------------------------//
INT ana_trigger_event(EVENT_HEADER *pheader, void *pevent);
INT ana_begin_of_run(INT run_number, char *error);
INT ana_end_of_run(INT run_number, char *error);

ANALYZE_REQUEST analyze_request[] = {
  {@ANALYZER_NAME,     // equipment name 
    {@BANK_EVENT_ID,                     // event ID 
     TRIGGER_ALL,           // trigger mask 
     GET_NONBLOCKING,       // get events without blocking producer 
     "SYSTEM",                // event buffer 
     TRUE,                  // enabled 
     "", "",}
    ,
    ana_trigger_event,      // analyzer routine 
    NULL,                   // module list 
    analyzer_bank_list,     // bank list  
   },
   {""}
};



//--- init routine ----------------------------------------------------------//

INT analyzer_init()
{
  return SUCCESS;
}


//--- exit routine ----------------------------------------------------------//

INT analyzer_exit(void)
{
   return SUCCESS;
}

//--- BOR routine -----------------------------------------------------------//

INT ana_begin_of_run(INT run_number, char *error)
{
   return SUCCESS;
}

//--- EOR routine -----------------------------------------------------------//

INT ana_end_of_run(INT run_number, char *error)
{
   return SUCCESS;
}

//--- pause run -------------------------------------------------------------//

INT ana_pause_run(INT run_number, char *error)
{
   return CM_SUCCESS;
}
 
//--- resume run ------------------------------------------------------------//

INT ana_resume_run(INT run_number, char *error)
{
   return CM_SUCCESS;
}

//--- analyzer loop ---------------------------------------------------------//

INT analyzer_loop()
{
   return CM_SUCCESS;
}

//--- event routine ---------------------------------------------------------//

INT ana_trigger_event(EVENT_HEADER *pheader, void *pevent)
{
   INT end, start, n;
   @MIDAS_DATA_TYPE *pdata;

   // Look for shim platform data bank
   n = bk_locate(pevent, @BANK_NAME, &pdata);

   // @USER algos.

   return SUCCESS;
}
