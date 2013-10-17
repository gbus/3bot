

/*
 * 3bot player plugin
 * 
 */

// ONLY if you need something that was #define'd as a result of configure 
// (e.g., HAVE_CFMAKERAW), then #include <config.h>, like so:
/*
#include <config.h>
*/

#include <unistd.h>
#include <string.h>
#include "pwmlib.h"
#include "3botdriver.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <libplayercore/playercore.h>



// A factory creation function, declared outside of the class so that it
// can be invoked without any object context (alternatively, you can
// declare it static in the class).  In this function, we create and return
// (as a generic Driver*) a pointer to a new instance of this driver.
Driver* 
3botDriver_Init(ConfigFile* cf, int section)
{
  // Create and return a new instance of this driver
  return((Driver*)(new 3botDriver(cf, section)));
}

// A driver registration function, again declared outside of the class so
// that it can be invoked without object context.  In this function, we add
// the driver into the given driver table, indicating which interface the
// driver can support and how to create a driver instance.
void 3botDriver_Register(DriverTable* table)
{
  table->AddDriver("3botdriver", 3botDriver_Init);
}




////////////////////////////////////////////////////////////////////////////////
// Constructor.  Retrieve options from the configuration file and do any
// pre-Setup() setup.
3botDriver::3botDriver(ConfigFile* cf, int section)
    : ThreadedDriver(cf, section, false, PLAYER_MSGQUEUE_DEFAULT_MAXLEN, 
             PLAYER_POSITION2D_CODE)
{

  // 
/*
  if (cf->ReadDeviceAddr(&laserID, section, "requires", PLAYER_LASER_CODE, -1, NULL) != 0)
  {
    PLAYER_ERROR("Could not find laser interface!");
    SetError(-1);
    return;
  } */

  // Read an option from the configuration file
  this->leftwheel_i2a_ch = cf->ReadInt(section, "leftwheel_i2a_ch", 0);
  this->rightwheel_i2a_ch = cf->ReadInt(section, "rightwheel_i2a_ch", 1);
  this->leftwheelmin = cf->ReadTupleInt(section, "leftwheel_minmax", 0, -1);
  this->leftwheelmax = cf->ReadTupleInt(section, "leftwheel_minmax", 1, -1);
  this->rightwheelmin = cf->ReadTupleInt(section, "rightwheel_minmax", 0, -1);
  this->rightwheelmax = cf->ReadTupleInt(section, "rightwheel_minmax", 1, -1);

  return;
}




////////////////////////////////////////////////////////////////////////////////
// Set up the device.  Return 0 if things go well, and -1 otherwise.
int 3botDriver::MainSetup()
{   
  puts("Initialising the 16channels PWM controller");

  PWM* pwm = new PWM(PWM_I2C_ADDR,true);
  pwm->setPWMFreq(PWM_I2C_FREQ);
  
    
  puts("Driver initialised");

  return(0);
}


////////////////////////////////////////////////////////////////////////////////
// Shutdown the device
void 3botDriver::MainQuit()
{
  puts("Shutting 3bot driver down");

  // Here you would shut the device down by, for example, closing a
  // serial port.

  puts("The driver has been shutdown");
}

int 3botDriver::ProcessMessage(QueuePointer & resp_queue, 
                                  player_msghdr * hdr,
                                  void * data)
{
  // Process messages here.  Send a response if necessary, using Publish().
  // If you handle the message successfully, return 0.  Otherwise,
  // return -1, and a NACK will be sent for you, if a response is required.
  return(0);
}



////////////////////////////////////////////////////////////////////////////////
// Main function for device thread
void 3botDriver::Main() 
{
  // The main loop; interact with the device here
  for(;;)
  {
    // test if we are supposed to cancel
    pthread_testcancel();

    // Process incoming messages.  3botDriver::ProcessMessage() is
    // called on each message.
    ProcessMessages();

    // Interact with the device, and push out the resulting data, using
    // Driver::Publish()

    // Sleep (you might, for example, block on a read() instead)
    usleep(100000);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Extra stuff for building a shared object.

/* need the extern to avoid C++ name-mangling  */
extern "C" {
  int player_driver_init(DriverTable* table)
  {
    puts("Example driver initializing");
    3botDriver_Register(table);
    puts("Example driver done");
    return(0);
  }
}

