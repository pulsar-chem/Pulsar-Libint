#include <pulsar/testing/CppTester.hpp>
#include <pulsar/modulebase/OneElectronIntegral.hpp>
#include "../TestCommon.hpp"

using namespace pulsar;

//Computes the nuclear-electron energy integrals for water in STO-3G
std::vector<std::vector<double>> corr={
    {//(  0 |  0 )
    -61.5805952694322016,},
    {//(  1 |  0 )
    -7.4108218563311627,},
    {//(  1 |  1 )
    -10.0090711420700238,},
    {//(  2 |  0 )
    0.0000000000000000,-0.0144738837457361,0.0000000000000000,},
    {//(  2 |  1 )
    0.0000000000000000,-0.1768908347336429,0.0000000000000000,},
    {//(  2 |  2 )
    -9.9875499350885519,0.0000000000000000,0.0000000000000000,
     0.0000000000000000,-9.9440433416987553,0.0000000000000000,
     0.0000000000000000,0.0000000000000000,-9.8758759950909436,},
    {//(  3 |  0 )
    -1.2316855721424860,},
    {//(  3 |  1 )
    -2.9772268535781317,},
    {//(  3 |  2 )
    -1.8222369134761314,-1.4717933387129600,0.0000000000000000,},
    {//(  3 |  3 )
    -5.3002032522950184,},
    {//(  4 |  0 )
    -1.2316855721424860,},
    {//(  4 |  1 )
    -2.9772268535781312,},
    {//(  4 |  2 )
    1.8222369134761311,-1.4717933387129600,0.0000000000000000,},
    {//(  4 |  3 )
    -1.0671710804724346,},
    {//(  4 |  4 )
    -5.3002032522950167,},
};


TEST_SIMPLE(TestNuclearElectron){
    CppTester tester("Testing the NuclearElectron class");
    const std::string name="NuclearElectron";
    auto wf=make_wf();
    ModuleInfo minfo;
    minfo.path=PULSAR_LIBINT_LIBRARY;
    minfo.type="c_module";
    minfo.name=name;
    auto mm=std::make_shared<ModuleManager>();
    mm->load_module_from_minfo(minfo,name);
    auto Ints=mm->get_module<OneElectronIntegral>(name,0);
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
