#pragma once
#include <reflection.h>
#include <core/mesh.h>

namespace Miyuki {
	namespace Core {
		struct Accelerator : Component{
			MYK_INTERFACE(Accelerator);
			virtual void addMesh(std::shared_ptr<Mesh> mesh, uint32_t id) = 0;

			virtual bool intersect(const Ray& ray, Intersection* isct) = 0;

			//virtual void detachGeometry(int geomId) = 0;
		};
	}
}