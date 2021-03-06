/**
 * @file VariableChecker.cpp
 * @author 叶宙果
 * @version v2
 */
#include "VariableChecker.h"

/* 
 * 构造函数
 */
VariableChecker::VariableChecker()
{
    ;
}

/* 
 * 打印目前函数的CFG
 */
void VariableChecker::PrintCFG(FunctionDecl *func)
{
    cout << "Inside " << " " << func->getNameInfo().getName().getAsString() << "\n";

    clang::CodeInjector *injector  = nullptr;

    clang::AnalysisDeclContextManager *ADCM = new clang::AnalysisDeclContextManager(
      TheCompInst.getASTContext(),false, false,false,false,false,false,false,false,false, true, true, true, true,injector);
    
    //ADCM->getContext(func)->dumpCFG(true);
    
    // must call adcm->getCFGBuildOptions().setAllAlwaysAdd() 
    // before getting any analysis from your AnalysisDeclContext. 
    // This will create elements for all sub-expressions in the CFGBlocks of the control-flow-graph.
    ADCM->getCFGBuildOptions().setAllAlwaysAdd();
    clang::AnalysisDeclContext *func_ADC = ADCM->getContext(func);
    
    CFG *cfg = func_ADC->getCFG();

    cfg->dump(TheCompInst.getLangOpts(),true);
}

/* 
 * 打印目前函数的活跃变量信息
 */
void VariableChecker::PrintLiveVariables(FunctionDecl *func)
{
    cout << "Inside " << " " << func->getNameInfo().getName().getAsString() << "\n";

    clang::CodeInjector *injector  = nullptr;

    clang::AnalysisDeclContextManager *ADCM = new clang::AnalysisDeclContextManager(
      TheCompInst.getASTContext(),false, false,false,false,false,false,false,false,false, true, true, true, true,injector);
    
    //ADCM->getContext(func)->dumpCFG(true);
    
    // must call adcm->getCFGBuildOptions().setAllAlwaysAdd() 
    // before getting any analysis from your AnalysisDeclContext. 
    // This will create elements for all sub-expressions in the CFGBlocks of the control-flow-graph.
    ADCM->getCFGBuildOptions().setAllAlwaysAdd();
    clang::AnalysisDeclContext *func_ADC = ADCM->getContext(func);
    
    CFG *cfg = func_ADC->getCFG();

    //cfg->dump(TheCompInst.getLangOpts(),true);
    

    clang::LiveVariables *func_LV = clang::LiveVariables::computeLiveness(*func_ADC, false);
    clang::LiveVariables::Observer *obs = new clang::LiveVariables::Observer();

    func_LV->runOnAllBlocks(*obs);
    func_LV->dumpBlockLiveness((func_ADC->getASTContext()).getSourceManager());
}