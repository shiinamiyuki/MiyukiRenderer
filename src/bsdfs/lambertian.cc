//
// Created by Shiina Miyuki on 2019/2/9.
//

#include "lambertian.h"
using namespace Miyuki;
Spectrum LambertianBSDF::f(const ScatteringEvent &event) const {

    return Spectrum(evalAlbedo(event) * INVPI);

}
