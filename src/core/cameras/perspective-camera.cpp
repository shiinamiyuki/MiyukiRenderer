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

#include "perspective-camera.h"

namespace miyuki::core {
    void PerspectiveCamera::initialize(const json &params) {
        fov = DegreesToRadians(params.at("fov").get<Float>());
        if (params.contains("eye")) {
            auto viewpoint = params.at("eye").get<Vec3f>();
            auto at = params.at("at").get<Vec3f>();
            transform = Transform(Matrix4::lookAt(viewpoint, at));
        } else if (params.contains("translate")) {
            auto translate = params.at("translate").get<Vec3f>();
            auto rotation = DegreesToRadians(params.at("rotate").get<Vec3f>());
            Matrix4 m = Matrix4::identity();
            m *= Matrix4::rotate(Vec3f(0, 0, 1), rotation.z);
            m *= Matrix4::rotate(Vec3f(1, 0, 0), rotation.y);
            m *= Matrix4::rotate(Vec3f(0, 1, 0), rotation.x);
            m *= Matrix4::translate(translate);
            transform = Transform(m);
        } else {
            MIYUKI_THROW(std::runtime_error, "Unknown input format to PerspectiveCamera");
        }
        invTransform = transform.inverse();
    }

    void PerspectiveCamera::generateRay(const Point2f &u1,
                                        const Point2f &u2,
                                        const Point2i &raster,
                                        Point2i filmDimension,
                                        CameraSample &sample) const {
        float x = float(raster.x) / filmDimension.x;
        float y = float(raster.y) / filmDimension.y;

        Point2f pixelWidth(1.0 / filmDimension.x, 1.0 / filmDimension.y);
        sample.pFilm = Point2f(x, y);
        sample.pFilm += u1 * pixelWidth - 0.5f * pixelWidth;
        sample.pLens = {0, 0};
        x = sample.pFilm[0];
        y = sample.pFilm[1];
        y = 1 - y;
        x = -(2 * x - 1);
        y = 2 * y - 1;
        y *= float(filmDimension.y) / filmDimension.x;
        float z = 1.0f / std::atan(fov / 2);
        Vec3f d = Vec3f(x, y, 0) - Vec3f(0, 0, -z);
        d.normalize();
        Point3f o = Vec3f(sample.pLens.x, sample.pLens.y, 0);
        o = transform(o);
        d = transform(d);
        sample.ray = Ray(o, d, RayBias);
    }

}