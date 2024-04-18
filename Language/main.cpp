#include "scan.hpp"
#include "serialize_code.hpp"
#include "interpret.hpp"




int main() {
	AST tree = scan({ "int foo = 5","print(foo + 10)"});
	interpret_code(tree);
}
