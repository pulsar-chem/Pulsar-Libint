#include "pulsar_libint/LibInt1E.hpp"
#include "pulsar_libint/LibInt2E.hpp"

using pulsar::ModuleCreationFuncs;

extern "C" {

ModuleCreationFuncs insert_supermodule(void){
    ModuleCreationFuncs cf;
    cf.add_cpp_creator<pulsar_libint::ERI>("ERI");
    cf.add_cpp_creator<pulsar_libint::Kinetic>("Kinetic");
    cf.add_cpp_creator<pulsar_libint::Overlap>("Overlap");
    cf.add_cpp_creator<pulsar_libint::NuclearElectron>("NuclearElectron");
    return cf;
}

}
