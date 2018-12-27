#include <clang/Frontend/FrontendPluginRegistry.h>

#include <dn/AstAction.hpp>

clang::FrontendPluginRegistry::Add<dn::Action> _{
	"dump-names", "Dump names of types and symbols"
};
