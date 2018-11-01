#ifndef EUTelFitTuple_h
#define EUTelFitTuple_h 1

#include "marlin/Processor.h"

// system includes <>
#include <string>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TVectorT.h>

namespace eutelescope {
  class EUTelGBLOutput : public marlin::Processor {

  public:
    virtual Processor *newProcessor() { return new EUTelGBLOutput; }

    EUTelGBLOutput();
    virtual void init();
    virtual void processRunHeader(LCRunHeader *run);
    virtual void processEvent(LCEvent *evt);
    virtual void check(LCEvent * /*evt*/) { ; };
    virtual void end();

  protected:
    void clear();

    std::vector<std::string> _inputHitCollections;
    std::vector<std::string> _inputZsCollections;
    std::string _path2file;

    bool _onlyWithTracks;
    bool _tracksLocalSystem;
    bool _dumpHeader;
    std::vector<int> _SelectedPlanes;

    // Internal processor variables
    // ----------------------------
    int _nRun;
    int _nEvt;
    int _runNr;
    int _evtNr;

    bool _isFirstEvent;

    TFile *_file;

    TTree *_eutracks;
    int _nTrackParams;
    std::vector<int> *_IDtrack;
    std::vector<int> *_trackID;
    std::vector<int> *_triggerID;
    std::vector<double> *_xPos;
    std::vector<double> *_yPos;
    std::vector<double> *_omega;
    std::vector<double> *_phi;
    std::vector<double> *_kinkx;
    std::vector<double> *_kinky;
    std::vector<double> *_chi2;
    std::vector<int> *_ndof;
    TTree *_euhits;
    std::vector<int> *_hitSensorId;
    std::vector<double> *_hitXPos;
    std::vector<double> *_hitYPos;
    std::vector<double> *_hitZPos;
    
    TTree *_zstree;
    std::vector<int> *zs_id;
    std::vector<int> *zs_x;
    std::vector<int> *zs_y;
    std::vector<double> *zs_signal;
    std::vector<int> *zs_time;
  };

  //! A global instance of the processor.
  EUTelGBLOutput gEUTelGBLOutput;
}
#endif
