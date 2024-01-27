#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <string>

using namespace llvm;
using namespace std;

namespace {
    struct FunctionCounter : public ModulePass {
        static char ID; // Pass identification, replacement for typeid
        FunctionCounter() : ModulePass(ID) {}

        bool runOnModule(Module &M) override {
            unsigned int functionCount = 0;
            unsigned int basicBlockCount = 0;
            std::map<int, int> mp;

            for (Function &F : M) {
                if (!F.isDeclaration()) {
                    for (BasicBlock &B : F) {
                        int count = 0;
                        for (Instruction &I: B) {
                            count++;
                        }
                        if (mp.find(count) == mp.end()) {
                            mp[count] = 1;
                        } else {
                            ++mp[count];
                        }
                        ++basicBlockCount;
                    }
                    ++functionCount;
                }
            }
            errs() << "The program has a total of " << functionCount << " functions and " << basicBlockCount << " basic blocks.\n";
            errs() << "Instructions: Blocks\n";
            for (auto it = mp.begin(); it != mp.end(); ++it) {
                errs() << it->first << ": " << it->second << "\n";
            }
            return false; // We don't modify the module
        }
    };
}

char FunctionCounter::ID = 0;
static RegisterPass<FunctionCounter> X("function-counter", "Count Functions Pass");

