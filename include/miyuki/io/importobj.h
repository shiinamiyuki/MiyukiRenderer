#include <miyuki.h>
#include <reflection.h>
#include <graph/materialnode.h>
namespace Miyuki {
	namespace IO {
		struct ObjLoadInfo {
			std::unordered_map<std::string, std::string> shapeMat;
			std::string outputContent;
			std::vector<Reflection::LocalObject<Graph::MaterialNode>> materials;
			Reflection::Runtime* runtime = nullptr;
			ObjLoadInfo(Reflection::Runtime* runtime) :runtime(runtime) {}
		};
		void LoadMTLFile(const std::string& filename, ObjLoadInfo& info);
		void LoadObjFile(const std::string& filename, ObjLoadInfo& info);
	}
}