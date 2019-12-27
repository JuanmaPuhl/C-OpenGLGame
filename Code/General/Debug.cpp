#include "Debug.h"

Debug::Debug()
{

}

Debug::~Debug()
{

}

int Debug::getFpsCount(float current,float* lastTime)
{
  this->fps++;
  if((current - *lastTime) >= 1.0f)
  {
    double fpsCount = 1000.0/double(fps);
    // this->print("FPS:",&(this->fps),1);
    // this->print("MS:",&fpsCount,1);
    this->fpsConstantes = this->fps;
    this->fps = 0;
    (*lastTime)++;
  }
  return fpsConstantes;
}
