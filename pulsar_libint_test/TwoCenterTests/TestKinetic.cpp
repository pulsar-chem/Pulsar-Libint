#include <pulsar/testing/CppTester.hpp>
#include <pulsar/modulebase/TwoCenterIntegral.hpp>
#include "../TestCommon.hpp"
using namespace pulsar;

//Computes the kinetic energy integrals for water in STO-3G
std::vector<std::vector<double>> corr={
    {//(  0 |  0 )
    29.0031999455395848,},
    {//(  1 |  0 )
    -0.1680109393164923,},
    {//(  1 |  1 )
    0.8081279549303477,},
    {//(  2 |  0 )
    0.0000000000000000,0.0000000000000001,0.0000000000000000,},
    {//(  2 |  1 )
    0.0000000000000000,-0.0000000000000000,0.0000000000000000,},
    {//(  2 |  2 )
    2.5287311981947642,0.0000000000000000,0.0000000000000000,
    0.0000000000000000,2.5287311981947642,0.0000000000000000,
    0.0000000000000000,0.0000000000000000,2.5287311981947642,},
    {//(  3 |  0 )
    -0.0084163851854474,},
    {//(  3 |  1 )
    0.0705173385189986,},
    {//(  3 |  2 )
    0.1470905524127554,0.1149203802569079,0.0000000000000000,},
    {//(  3 |  3 )
    0.7600318835666090,},
    {//(  4 |  0 )
    -0.0084163851854474,},
    {//(  4 |  1 )
    0.0705173385189986,},
    {//(  4 |  2 )
    -0.1470905524127554,0.1149203802569079,0.0000000000000000,},
    {//(  4 |  3 )
    -0.0039797367270373,},
    {//(  4 |  4 )
    0.7600318835666090,},

};

TEST_SIMPLE(TestKinetic){
    CppTester tester("Testing the Kinetic class");
    const std::string name="Kinetic";
    auto wf=make_wf();
    auto mm=std::make_shared<ModuleManager>();
    ModuleInfo minfo;
    minfo.path=PULSAR_LIBINT_LIBRARY;
    minfo.language="c_module";
    minfo.name=name;
    mm->load_module_from_minfo(minfo,name);
    auto Ints=mm->get_module<TwoCenterIntegral>(name,0);
    auto bs=wf.system->get_basis_set("PRIMARY");
    Ints->initialize(0,wf,bs,bs);

    size_t counter=0;
    for(size_t si=0;si<5;++si)
    {
        const size_t ni=bs.shell_info(si).n_functions();
        for(size_t sj=0;sj<=si;++sj)
        {
            const size_t nj=bs.shell_info(sj).n_functions();
            const double* buffer=Ints->calculate(si,sj);
            if(buffer==nullptr)continue;
            std::stringstream ss;
            ss<<"("<<si<<"|"<<sj<<")";
            ptr_wrapper wrapped_buffer={buffer,ni*nj};
            tester.test_double_vector(ss.str(),corr[counter],wrapped_buffer);
            ++counter;
        }
    }

    return tester.nfailed();
}
