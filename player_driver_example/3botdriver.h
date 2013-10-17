#ifndef 3botdriverH
#define 3botdriverH

#include <libplayercore/playercore.h>

#define PWM_I2C_ADDR	0x40
#define PWM_I2C_FREQ	60

////////////////////////////////////////////////////////////////////////////////
// The class for the driver
class 3botDriver : public ThreadedDriver
{
  public:
    
    // Constructor
    3botDriver(ConfigFile* cf, int section);

    // This method will be invoked on each incoming message
    virtual int ProcessMessage(QueuePointer &resp_queue, 
                               player_msghdr * hdr,
                               void * data);

  private:

    // Main function for device thread.
    virtual void Main();
    virtual int MainSetup();
    virtual void MainQuit();

    //player_devaddr_t laserID;
    int leftwheel_i2a_ch
    int rightwheel_i2a_ch
    int leftwheelmin
    int leftwheelmax
    int rightwheelmin
    int rightwheelmax
};


#endif
