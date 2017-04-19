#include <pulsar/testing/CppTester.hpp>
#include <pulsar/modulebase/OneElectronIntegral.hpp>

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

struct ptr_wrapper{
    const double* ptr_;
    size_t n_;
    const double* begin()const{return ptr_;}
    const double* end()const{return ptr_+n_;}
};

TEST_SIMPLE(TestKinetic){
    CppTester tester("Testing the Kinetic class");
    const std::string name="Kinetic";
    AtomSetUniverse MyU;
    const double angstrom_to_bohr = 1 / 0.52917721092;
    const double Oy=-0.07579*angstrom_to_bohr;
    const double Hx=0.86681*angstrom_to_bohr;
    const double Hy=0.60144*angstrom_to_bohr;
    auto cg = pulsar::ShellType::CartesianGaussian;
    const BasisShellInfo O1s(cg,0,3,1,
                             {130.709320000, 23.808861000, 6.443608300},
                             {0.15432897, 0.53532814, 0.44463454});
    const BasisShellInfo O2s(cg,0,3,1,
                             {5.033151300, 1.169596100, 0.380389000},
                             {-0.09996723, 0.39951283, 0.70011547});
    const BasisShellInfo O2p(cg,1,3,1,
                             {5.033151300, 1.169596100, 0.380389000},
                             {0.15591627, 0.60768372, 0.39195739});
    const BasisShellInfo H1s(cg,0,3,1,
                             {3.425250910, 0.623913730, 0.168855400},
                             {0.15432897, 0.53532814, 0.44463454});
    Atom O=create_atom({0.00000,Oy,0.00000},8);
    O.basis_sets["PRIMARY"].shells=std::vector<BasisShellInfo>({O1s,O2s,O2p});
    Atom H1=create_atom({Hx,Hy,0.00000},1);
    H1.basis_sets["PRIMARY"].shells.push_back(H1s);
    Atom H2=create_atom({-Hx,Hy,0.00000},1);
    H2.basis_sets["PRIMARY"].shells.push_back(H1s);
    MyU.insert(O);
    MyU.insert(H1);
    MyU.insert(H2);
    Wavefunction wf;
    wf.system=std::make_shared<System>(MyU,true);
    auto mm=std::make_shared<ModuleManager>();
    ModuleInfo minfo;
    minfo.path=PULSAR_LIBINT_LIBRARY;
    minfo.type="c_module";
    minfo.name=name;
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
            tester.test_double(ss.str(),corr[counter],wrapped_buffer);
            ++counter;
        }
    }

    return tester.nfailed();
}
