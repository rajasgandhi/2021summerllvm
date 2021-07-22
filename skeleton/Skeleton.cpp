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

      //errs() << F.getName() << ": " << F.getInstructionCount() << "\n";
      myfile << F.getName().str() << ": " << F.getInstructionCount() << "\n";

      for (BasicBlock &BB : F)
      {
        //errs() << "BB has name" << BB << "\n";
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
      std::ofstream myfile{"output1.txt", std::ofstream::out};
      std::error_code ec = std::make_error_code(std::io_errc::stream);
      raw_fd_ostream S(StringRef("output1.txt"), ec);

      std::ofstream myfile1{"output.json", std::ofstream::out};

      raw_fd_ostream T(StringRef("output.json"), ec);
      T << "{ \n";

      errs() << "In a Module called " << M.getName() << "!\n";
      for (auto &F : M)
      {
        T << "\t\"" << F.getName() << "\":{\n\t\t\"number_of_callers\":" << F.getNumUses() << ",\n\t\"body\":\"" << F << "\"},\n";
        vector<string> functionlist;
        vector<Argument*> argumentList;
        for (auto &B : F)
        {
          for (auto &I : B)
          {
            if (CallInst *callInst = dyn_cast<CallInst>(&I))
            {
              Function *calledFunction = callInst->getCalledFunction();
              StringRef cfName = calledFunction->getName();
              //errs() << cfName;
              functionlist.push_back(cfName.str());
            }
          }
        }
        T << "\t\t\"functionlist\":{[\n";
        for (string i : functionlist)
        {
          T << "\"" << i << "\",";
        }
        T << "]},";
        for (auto &arg : F.args())
        {
          errs() << arg;
          argumentList.push_back(&arg);
        }
        T << "\t\t\"argumentList\":{[\n";
        for (Argument* i : argumentList)
        {
          T << "\"" << *i << "\",";
        }
        T << "]},";
      }
      T << "} \n";
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
