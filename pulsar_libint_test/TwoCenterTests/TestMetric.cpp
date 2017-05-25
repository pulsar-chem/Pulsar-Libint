#include <pulsar/testing/CppTester.hpp>
#include <pulsar/modulebase/TwoCenterIntegral.hpp>
#include "../TestCommon.hpp"
using namespace pulsar;

//Computes the density fitting metric integrals for water in STO-3G
//Note: the integrals actually use STO-3G and not a fitting basis, but I fail
//to see how that really matters for a unit test...
std::vector<std::vector<double>> corr={
    { //( 0 | 0 )
    1.0464371073132783, },
    { //( 1 | 0 )
    3.4291997049832545, },
    { //( 1 | 1 )
    26.4352259268832768, },
    { //( 2 | 0 )
    0.0000000000000000, 0.0000000000000000, 0.0000000000000000, },
    { //( 2 | 1 )
    0.0000000000000000, -0.0000000000000002, 0.0000000000000000, },
    { //( 2 | 2 )
      5.7847979494771771, 0.0000000000000000, 0.0000000000000000,
      0.0000000000000000, 5.7847979494771771, 0.0000000000000000,
      0.0000000000000000, 0.0000000000000000, 5.7847979494771771, },
    { //( 3 | 0 )
    2.6052624154025357, },
    { //( 3 | 1 )
    25.3420823544301896, },
    { //( 3 | 2 )
    4.2141100758044443, 3.2924421345358774, 0.0000000000000000, },
    { //( 3 | 3 )
    39.9325704220624615, },
    { //( 4 | 0 )
    2.6052624154025357, },
    { //( 4 | 1 )
    25.3420823544301896, },
    { //( 4 | 2 )
    -4.2141100758044443, 3.2924421345358774, 0.0000000000000000, },
    { //( 4 | 3 )
    26.6712891938732142, },
    { //( 4 | 4 )
    39.9325704220624615, },

};

TEST_SIMPLE(TestMetric){
    CppTester tester("Testing the Metric class");
    const std::string name="Metric";
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
    tester.print_results();
    return tester.nfailed();
}
