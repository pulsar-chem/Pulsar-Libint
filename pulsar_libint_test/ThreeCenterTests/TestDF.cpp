#include <pulsar/testing/CppTester.hpp>
#include <pulsar/modulebase/ThreeCenterIntegral.hpp>
#include "DF_STO_3G.hpp"
#include "../TestCommon.hpp"

using namespace pulsar;

//Computes the three-center, two-electron integrals for water in sto-3g
//Note: as with the metric tensor using sto-3g instead of a proper fitting basis
//should be fine for testing purposes.

TEST_SIMPLE(TestDF){
    CppTester tester("Testing the three-center, two electron integrals class");
    auto wf=make_wf();
    auto mm=std::make_shared<ModuleManager>();
    ModuleInfo minfo;
    minfo.path=PULSAR_LIBINT_LIBRARY;
    minfo.language="c_module";
    minfo.name="DF3C2E";
    mm->load_module_from_minfo(minfo,"DFInts");
    auto eri=mm->get_module<ThreeCenterIntegral>("DFInts",0);
    auto bs=wf.system->get_basis_set("PRIMARY");
    eri->initialize(0,wf,bs,bs,bs);

    size_t counter=0;
    const size_t nshells=5;
    //TODO: sk<=sj
    for(size_t si=0;si<nshells;++si)
    {
        const size_t ni=bs.shell_info(si).n_functions();
        for(size_t sj=0;sj<nshells;++sj)
        {
            const size_t nj=bs.shell_info(sj).n_functions();
            for(size_t sk=0;sk<nshells;++sk)
            {
                    const size_t nk=bs.shell_info(sk).n_functions();
                    const double* buffer=eri->calculate(si,sj,sk);
                    if(buffer==nullptr)continue;
                    std::stringstream ss;
                    ss<<"("<<si<<" | "<<sj<<" "<<sk<<")";
                    ptr_wrapper wrapped_buffer={buffer,ni*nj*nk};
                    tester.test_double_vector(ss.str(),corr_sto3g[counter],wrapped_buffer);
                    ++counter;
            }
        }
    }
    tester.print_results();
    return tester.nfailed();
}
