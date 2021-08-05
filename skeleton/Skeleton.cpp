#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace llvm;
using namespace std;

namespace
{

  struct Hello : public FunctionPass
  {
    static char ID;
    Hello() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override
    {
      unsigned int basicBlockCount = 0;
      unsigned int instructionCount = 0;

      std::ofstream myfile{"output.txt", std::ofstream::out};
      std::error_code ec = std::make_error_code(std::io_errc::stream);
      raw_fd_ostream S(StringRef("output.txt"), ec);

      myfile << F.getName().str() << ": " << F.getInstructionCount() << "\n";

      for (BasicBlock &BB : F)
      {
        BB.print(S);
        basicBlockCount++;
        for (Instruction &I : BB)
        {
          //errs() << "Instruction I" << I << "\n";
          //myfile << "Instruction I" << I.getName().str() << "\n";
          I.print(S);
          instructionCount++;
        }
      }
      myfile << basicBlockCount << " " << instructionCount;
      //myfile.close();
      return false;
    }
  };
  struct Hello1 : public ModulePass
  {
    static char ID;
    Hello1() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M)
    {
      std::error_code ec = std::make_error_code(std::io_errc::stream);
      std::ofstream myfile1{"output.json", std::ofstream::out};

      raw_fd_ostream T(StringRef("output.json"), ec);
      T << "[\n";

      errs() << "In a Module called " << M.getName() << "!\n";
      for (auto &F : M)
      {
        T << "\t{\n\t\t\"" << F.getName() << "\":{\n\t\t\t\"number_of_callers\":" << F.getNumUses() << ",\n";
        T << "\t\t\t\"function_body\":\"" << F << "\",\n";
        vector<string> callsFunctions;
        vector<Argument *> argumentList;
        for (auto &B : F)
        {
          for (auto &I : B)
          {
            if (CallInst *callInst = dyn_cast<CallInst>(&I))
            {
              Function *calledFunction = callInst->getCalledFunction();
              StringRef cfName = calledFunction->getName();
              //errs() << cfName;
              callsFunctions.push_back(cfName.str());
            }
          }
        }
        T << "\t\t\t\"calls_functions\":[";
        for (int i = 0; i < callsFunctions.size(); i++)
        {
          if (i != callsFunctions.size() - 1)
          {
            T << "\"" << callsFunctions[i] << "\",";
          }
          else
          {
            T << "\"" << callsFunctions[i] << "\"";
          }
        }
        /*for (string i : callsFunctions)
        {
          T << "\"" << i << "\",";
        }*/
        T << "],\n";
        for (auto &arg : F.args())
        {
          //errs() << arg;
          argumentList.push_back(&arg);
        }
        T << "\t\t\t\"argument_list\":[";
        for (int i = 0; i < argumentList.size(); i++)
        {
          if (i != argumentList.size() - 1)
          {
            T << "\"" << *argumentList[i] << "\",";
          }
          else
          {
            T << "\"" << *argumentList[i] << "\"";
          }
        }
        /*for (Argument *i : argumentList)
        {
          T << "\"" << *i << "\",";
        }*/
        T << "]\n\t\t}\n\t},\n";
      }
      T << "] \n";
      T.close();
      errs() << "Ouptut saved to output.json!\n";
      return false;
    }
  };
}

char Hello::ID = 0;
char Hello1::ID = 1;
static RegisterPass<Hello> X("hello", "Hello World Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);

static RegisterPass<Hello1> Z("hello1", "Hello World Pass 1", false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM)
    {
      PM.add(new Hello());
      PM.add(new Hello1());
    });
