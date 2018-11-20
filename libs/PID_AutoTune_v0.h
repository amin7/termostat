#ifndef PID_AutoTune_v0
#define PID_AutoTune_v0
#define LIBRARY_VERSION	0.0.1

class PID_ATune
{

  public:
  typedef enum {
    mode_off = 0,
    mode_starting,
    mode_run,
    mode_done,
    mode_err
  } mode_t;

  //commonly used functions **************************************************************************
  /***
   * in_max_error - if reach - stop tune
   */
  PID_ATune(double*, double*, double in_max_error = 40);            // * Constructor.  links the Autotune to a given PID
  int Runtime();						   			   	// * Similar to the PID Compue function, returns non 0 when done
  void Start(double setpoint);
	void Cancel();									   	// * Stops the AutoTune	
	
	void SetOutputRange(double min, double max);	// * how far above and below the starting value will the output step?

	void SetControlType(int); 						   	// * Determies if the tuning parameters returned will be PI (D=0)
	int GetControlType();							   	//   or PID.  (0=PI, 1=PID)			
	
	void SetLookbackSec(int);							// * how far back are we looking to identify peaks
	int GetLookbackSec();								//
	
	void SetNoiseBand(double);							// * the autotune will ignore signal chatter smaller than this value
	double GetNoiseBand();								//   this should be acurately set
  int getPeakCount() {
    return peakCount;
  }
	
	double GetKp();										// * once autotune is complete, these functions contain the
	double GetKi();										//   computed tuning parameters.  
	double GetKd();										//
	
  private:
    void FinishUp();
  mode_t mode_ = mode_off;
	bool isMax, isMin;
	double *input, *output;
	double setpoint_;
	double noiseBand;
	int controlType;
	bool running;
	unsigned long peak1, peak2, lastTime;
	int sampleTime;
	int nLookBack;
	int peakType;
	double lastInputs[101];
    double peaks[10];
	int peakCount;
  bool justchanged;
	double absMax, absMin;
  double out_min_ = 0;
  double out_max_ = 0;
	double Ku, Pu;
  const double in_max_error_;

};
#endif

