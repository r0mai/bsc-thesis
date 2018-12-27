#include <dn/AstVisitor.hpp>

#include <fstream>
#include <utility>

namespace {

std::string indent(std::size_t count) {
	return std::string(count, ' ');
}

} // unnamed namespace

dn::AstVisitor::AstVisitor(std::string outputFile) :
		outputFile(std::move(outputFile)) {
}

bool dn::AstVisitor::VisitDecl(clang::Decl* decl) {
	auto* variableDeclaration = clang::dyn_cast<clang::VarDecl>(decl);
	if (!variableDeclaration) {
		return true;
	}
	auto name = variableDeclaration->getNameAsString();
	auto type = variableDeclaration->getType().getAsString();

	++variableNames[type][name];
	return true;
}

void dn::AstVisitor::printVariableNames() const {
	std::ofstream output{getNameStoreFilename()};
	output << "{\n";
	output << indent(4) << "TypeNames: {\n";
	for (const auto& typeNameCountPair: variableNames) {
		const auto& type = typeNameCountPair.first;
		output << indent(8) << '"' << type << '"' << ": {\n";
		const auto& nameCounts = typeNameCountPair.second;
		for (const auto& nameCount: nameCounts) {
			output << indent(12) << '"' << nameCount.first << '"' << ": "
					<< nameCount.second << '\n';
		}
		output << indent(8) << "}\n";
	}
	output << indent(4) << "}\n";
	output << "}\n";
}

std::string dn::AstVisitor::getNameStoreFilename() const {
	return outputFile + ".names.json";
}
