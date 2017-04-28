#include <pulsar/testing/CppTester.hpp>
#include <pulsar/modulebase/TwoCenterIntegral.hpp>
#include "../TestCommon.hpp"

using namespace pulsar;

//Computes the overalap integrals for water in STO-3G
std::vector<std::vector<double>> corr={
    {//(  0 |  0 )
    1.0000000000000004,},
    {//(  1 |  0 )
    0.2367039365108476,},
    {//(  1 |  1 )
    1.0000000000000002,},
    {//(  2 |  0 )
    0.0000000000000000,0.0000000000000000,0.0000000000000000,},
    {//(  2 |  1 )
    0.0000000000000000,-0.0000000000000000,0.0000000000000000,},
    {//(  2 |  2 )
    1.0000000000000002,0.0000000000000000,0.0000000000000000,
    0.0000000000000000,1.0000000000000002,0.0000000000000000,
    0.0000000000000000,0.0000000000000000,1.0000000000000002,},
    {//(  3 |  0 )
    0.0384055905135490,},
    {//(  3 |  1 )
    0.3861387813310925,},
    {//(  3 |  2 )
    0.2684376412681760,0.2097276494226497,0.0000000000000000,},
    {//(  3 |  3 )
    1.0000000000000002,},
    {//(  4 |  0 )
    0.0384055905135490,},
    {//(  4 |  1 )
    0.3861387813310925,},
    {//(  4 |  2 )
    -0.2684376412681760,0.2097276494226497,0.0000000000000000,},
    {//(  4 |  3 )
    0.1817608668218927,},
    {//(  4 |  4 )
    1.0000000000000002,},
};

TEST_SIMPLE(TestOverlap){
    CppTester tester("Testing the Overlap class");
    const std::string name="Overlap";
    auto wf=make_wf();
    ModuleInfo minfo;
    minfo.path=PULSAR_LIBINT_LIBRARY;
    minfo.type="c_module";
    minfo.name=name;
    auto mm=std::make_shared<ModuleManager>();
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

