#include "SimpleAdsrComponent.h"
#include "GateConstants.h"
#include "RangeUtils.h"

namespace RtAudioNs
{
  namespace Components
  {

    double AdsrStep::rescalePower(const double signedFromZeroToOne)
    {
      double scaled = rescaleRange(abs(signedFromZeroToOne), 0, 1, 1, maxCurvePower);
      if (signedFromZeroToOne < 0)
      {
        return 1.0 / scaled;
      }
      return scaled;
    }

    double AdsrStep::getPowSignedZerowToOne(const double val)
    {
      return pow((double)position * (1.0 / (double)totalFramesLen), rescalePower(val));
    }

    double AdsrStep::proccess(bool isReset)
    {
      if (isReset)
      {
        position = 0;
        resetRetval();
        simpleAdsrStatus = currentStatus;
      }

      if (position >= totalFramesLen)
      {
        simpleAdsrStatus = beforeNextStatus;
      }

      updateReturnVal();

      position++;
      return returnVal;
    }

    void SimpleAdsrComponent::render(std::vector<double> &vGate, std::vector<double> &vOut)
    {
      stepA.lineCurved = 0.2; //This is zero to one, see in header constant 5 as max power.
      stepD.lineCurved = - 0.2;
      stepR.lineCurved = 0.4;
      stepA.totalFramesLen = 44800; //This is the buffer len(time)
      stepD.totalFramesLen = 44800;
      stepR.totalFramesLen = 44800;


      for (unsigned int i = 0; i < vGate.size(); i++)
      {
        if (vGate[i] > gateThreshold)
        {
          if (simpleAdsrStatus == SimpleAdsrStatus::idle || simpleAdsrStatus == SimpleAdsrStatus::r)
          {
            vOut[i] = stepA.proccess(true);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::a)
          {
            vOut[i] = stepA.proccess(false);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::beforeD)
          {
            vOut[i] = stepD.proccess(true);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::d)
          {
            vOut[i] = stepD.proccess(false);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::s)
          {
            vOut[i] = sustainLevel;
          }
        }
        else
        {
          if (simpleAdsrStatus == SimpleAdsrStatus::a ||
              simpleAdsrStatus == SimpleAdsrStatus::beforeD ||
              simpleAdsrStatus == SimpleAdsrStatus::d ||
              simpleAdsrStatus == SimpleAdsrStatus::s)
          {
            vOut[i] = stepR.proccess(true);
          }
          else if (simpleAdsrStatus == SimpleAdsrStatus::r)
          {
            vOut[i] = stepR.proccess(false);
          }
          else
          {
            simpleAdsrStatus = SimpleAdsrStatus::idle;
            vOut[i] = 0;
          }
        }
      }
    }

  }
}