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

#ifndef MIYUKIRENDERER_GRAPH_H
#define MIYUKIRENDERER_GRAPH_H

#include <miyuki.renderer/bsdf.h>
#include <miyuki.renderer/camera.h>
#include <miyuki.renderer/integrator.h>
#include <miyuki.renderer/sampler.h>
#include <miyuki.renderer/scene.h>
#include <miyuki.serialize/serialize.hpp>
#include <miyuki.renderer/shape.h>

namespace miyuki::core {

    class SceneGraph final : public serialize::Serializable {
    public:
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Integrator> integrator;
        std::shared_ptr<Sampler> sampler;
        std::vector<std::shared_ptr<MeshBase>> shapes;
        std::shared_ptr<Shader> background;
        std::vector<std::shared_ptr<Light>> lights;
        Point2i filmDimension = Vec2i(100, 100);
        Float rayBias = 1e-5f;

        SceneGraph() = default;

        MYK_SER(camera, sampler, integrator, shapes, filmDimension, rayBias, lights, background)

        MYK_DECL_CLASS(SceneGraph, "SceneGraph")

        void render(const std::shared_ptr<serialize::Context> &ctx, const std::string &outImageFile);

        Task<RenderOutput>
        createRenderTask(const std::shared_ptr<serialize::Context> &ctx, const mpsc::Sender<std::shared_ptr<Film>> &tx);
    };
} // namespace miyuki::core
#endif // MIYUKIRENDERER_GRAPH_H
