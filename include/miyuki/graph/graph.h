#pragma once

#include <graph/graphnode.h>
#include <graph/materialnode.h>
#include <graph/meshnode.h>
namespace Miyuki {
	namespace Graph {
		class IntegratorNode;
		class Graph : public GraphNode {
		public:
			MYK_CLASS(Graph, GraphNode);
			MYK_INIT(Reflection::Array<MaterialNode> * materials,
				Reflection::Array<MeshNode> * meshes) {
				this->materials = materials;
				this->meshes = meshes;
			}
			MYK_BEGIN_PROPERTY;
			MYK_PROPERTY(Reflection::Array<MaterialNode>, materials);
			MYK_PROPERTY(Reflection::Array<MeshNode>, meshes);
			MYK_PROPERTY(IntegratorNode, integrator);
			MYK_END_PROPERTY;
		public:
			void addMaterial(MaterialNode* material) {
				materials->push_back(material);
			}
		};
	} 
}