#include <dn/AstVisitor.hpp>

#include <fstream>
#include <iostream>
#include <utility>

namespace {

std::string indent(std::size_t count) {
	return std::string(count, ' ');
}

} // unnamed namespace

dn::AstVisitor::AstVisitor(std::string outputFile,
		const clang::SourceManager& sourceManager) :
		outputFile(std::move(outputFile)),
		sourceManager(sourceManager) {
}

bool dn::AstVisitor::VisitDecl(clang::Decl* decl) {
	auto* variableDeclaration = clang::dyn_cast<clang::VarDecl>(decl);
	if (!variableDeclaration) {
		return true;
	}
	variableDeclarations.emplace_back(*variableDeclaration);
	return true;
}

void dn::AstVisitor::printVariableNames() const {
	std::ofstream output{outputFile};
	output << "{\n";
	output << indent(4) << '"' << "Variables" << '"' << ": [\n";
	bool first = true;
	for (const auto& variableDeclaration: variableDeclarations) {
		if (!first) {
			output << ",\n";
		}
		first = false;
		output << indent(8) << "{\n";
		output << indent(12)
				<< "type: " << '"' << variableDeclaration.getType() << '"'
				<< ",\n";
		output << indent(12)
				<< "name: " << '"' << variableDeclaration.getName() << '"'
				<< ",\n";
		output << indent(12)
				<< "location: " << '"'
				<< variableDeclaration.getLocation(sourceManager) << '"'
				<< "\n";
		output << indent(8) << "}";
	}
	output << "\n" << indent(4) << "]\n";
	output << "}\n";
}
