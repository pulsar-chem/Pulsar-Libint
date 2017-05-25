#include <pulsar/testing/CppTester.hpp>
#include <pulsar/modulebase/FourCenterIntegral.hpp>
#include "H2O_STO3G_ERI.hpp"
#include "../TestCommon.hpp"

using namespace pulsar;

//Computes the ERI integrals for water in STO-3G
TEST_SIMPLE(TestERI){
    CppTester tester("Testing the ERI class");
    auto wf=make_wf();
    auto mm=std::make_shared<ModuleManager>();
    ModuleInfo minfo;
    minfo.path=PULSAR_LIBINT_LIBRARY;
    minfo.language="c_module";
    minfo.name="ERI";
    mm->load_module_from_minfo(minfo,"ERI");
    auto eri=mm->get_module<FourCenterIntegral>("ERI",0);
    auto bs=wf.system->get_basis_set("PRIMARY");
    eri->initialize(0,wf,bs,bs,bs,bs);

    size_t counter=0;
    for(size_t si=0;si<5;++si)
    {
        const size_t ni=bs.shell_info(si).n_functions();
        for(size_t sj=0;sj<=si;++sj)
        {
            const size_t nj=bs.shell_info(sj).n_functions();
            for(size_t sk=0;sk<=si;++sk)
            {
                const size_t nk=bs.shell_info(sk).n_functions();
                for(size_t sl=0;sl<=(si==sk?sj:sk);++sl)
                {
                    const size_t nl=bs.shell_info(sl).n_functions();
                    const double* buffer=eri->calculate(si,sj,sk,sl);
                    if(buffer==nullptr)continue;
                    std::stringstream ss;
                    ss<<"("<<si<<" "<<sj<<"|"<<sk<<" "<<sl<<")";
                    ptr_wrapper wrapped_buffer={buffer,ni*nj*nk*nl};
                    tester.test_double_vector(ss.str(),corr[counter],wrapped_buffer);
                    ++counter;
                }
            }
        }
    }

    return tester.nfailed();
}
