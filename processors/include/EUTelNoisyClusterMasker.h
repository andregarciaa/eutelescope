/*
 *   This source code is part of the Eutelescope package of Marlin.
 *   You are free to use this source files for your own development as
 *   long as it stays in a public research context. You are not
 *   allowed to use it for commercial purpose. You must put this
 *   header with author names in all development based on this file.
 *
 */
#ifndef EUTELNOISYCLUSTERMASKER_H
#define EUTELNOISYCLUSTERMASKER_H

// eutelescope includes ".h"
#include "EUTelEventImpl.h"
#include "EUTelGenericSparsePixel.h"

// marlin includes ".h"
#include "marlin/Processor.h"

// lcio includes <.h>
#include <IMPL/LCCollectionVec.h>
#include <LCIOTypes.h>

// system includes <>
#include <map>
#include <string>

namespace eutelescope {

  //! Processor to convert data to be compliant with EUTelGenericSparsePixel
  /*! EUTelescope stores data either in EUTelGenericSparsePixel with
   *  information (X,Y,signal) per hit or EUTelAPIXSparsePixel with
   *  (X,Y,signal, chip, time).
   *  New processors should not have to deal with those different types,
   *  therefore there is the EUTelGenericSparsePixel which stores information
   *  (X,Y,signal,time).
   *  This processor takes zsdata in either of the above pixels and
   *  stores them compliant to be interfaced with EUTelGenericSparsePixel
   *  in a TrackerDataImpl collection.
   *  If the original collection should be dumped, specify so in the
   *  EUTelOutputProcessor ("Save")
   */
  class EUTelNoisyClusterMasker : public marlin::Processor {

  public:
    //! Returns a new instance of EUTelNoisyClusterMasker
    /*! This method returns an new instance of the this processor.  It
     *  is called by Marlin execution framework and it shouldn't be
     *  called/used by the final user.
     */
    virtual Processor *newProcessor() {
      return new EUTelNoisyClusterMasker;
    }

    //! Default constructor
    EUTelNoisyClusterMasker();

    //! Called at the job beginning.
    /*! This is executed only once in the whole execution. It prints
     *  out the processor parameters and performs some asserts about
     *  the value of the provided parameters
     */
    virtual void init();

    //! Called for every run.
    /*! It is called for every run, and consequently the run counter
     *  is incremented.
     *
     *  @param run LCRunHeader of the current run
     *
     *  @throw InvalidParameterException if a parameter is wrongly set
     */
    virtual void processRunHeader(LCRunHeader *run);

    //! Called every event
    /*! This is called for each event in the file. If the current 
     *  @evt is flagged to be used for update, then the selected
     *  algorithm wrapper is called
     *
     *  @param evt the current LCEvent event as passed by the
     *  ProcessMgr
     *
     *  @throw InvalidParameterException if information in the cellID
     *  is inconsistent
     */
    virtual void processEvent(LCEvent *evt);

    //! Called after data processing.
    /*! This method is called when the loop on events is
     *  finished. Just printing a good bye message
     */
    virtual void end();

  protected:
    //! Input collection name for data
    std::string _inputCollectionName;

    //! Name of the hot pixel collection
    std::string _noisyPixelCollectionName;

    //! Current run number.
    /*! This number is used to store the current run number */
    int _iRun;

    //! Current event number.
    /*! This number is used to store the current event number NOTE that
     * events are counted from 0 and on a run base
     */
    int _iEvt;

  private:
    //! Bool set to false after first event is processed
    bool _firstEvent;

    //! Flag to check if the data format has been checked already
    bool _dataFormatChecked;

    //! Result of the data format check
    /*! False is everything is OK, true otherwise */
    bool _wrongDataFormat;

    //! Map linking the noise vectors of each plane to the plane ID
    std::map<int, std::vector<int>> _noisyPixelMap;

    //! Map counting the removed hot pixels per plane
    std::map<int, int> _maskedNoisyClusters;

    //! Static bool flag to mark if any instance of this processor has printed
    //! out general info
    static bool _staticPrintedSummary;
  };

  //! A global instance of the processor
  EUTelNoisyClusterMasker gEUTelNoisyClusterMasker;
}
#endif
