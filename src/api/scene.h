// MIT License
//
// Copyright (c) 2019 椎名深雪
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MIYUKIRENDERER_SCENE_H
#define MIYUKIRENDERER_SCENE_H

#include <api/accelerator.h>
#include <api/entity.hpp>
#include <api/light.h>
#include <api/ray.h>
#include <api/shape.h>
#include <atomic>

#include <core/accelerators/embree-backend.h>
#include <core/accelerators/sahbvh.h>
namespace miyuki::core {

    class Scene {
#ifdef MYK_USE_EMBREE
        std::shared_ptr<EmbreeAccelerator> accelerator;
#else
        std::shared_ptr<Accelerator> accelerator;
#endif

        std::atomic<size_t> rayCounter = 0;

      public:
        std::vector<std::shared_ptr<Light>> lights;
        std::vector<std::shared_ptr<Mesh>> meshes;
        std::vector<std::shared_ptr<MeshInstance>> instances;

        bool intersect(const Ray &ray, Intersection &isct);

        void preprocess();

        size_t getRayCounter() const { return rayCounter; }

        void resetRayCounter() { rayCounter = 0; }
    };
} // namespace miyuki::core
#endif // MIYUKIRENDERER_SCENE_H