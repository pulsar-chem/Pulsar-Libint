#include "pulsar_libint/LibInt2C.hpp"
#include "pulsar_libint/LibInt3C.hpp"
#include "pulsar_libint/LibInt4C.hpp"

using pulsar::ModuleCreationFuncs;

extern "C" {

ModuleCreationFuncs insert_supermodule(void){
    ModuleCreationFuncs cf;
    cf.add_cpp_creator<pulsar_libint::DF3C2E>("DF3C2E");
    cf.add_cpp_creator<pulsar_libint::ERI>("ERI");
    cf.add_cpp_creator<pulsar_libint::Kinetic>("Kinetic");
    cf.add_cpp_creator<pulsar_libint::Overlap>("Overlap");
    cf.add_cpp_creator<pulsar_libint::Metric>("Metric");
    cf.add_cpp_creator<pulsar_libint::NuclearElectron>("NuclearElectron");
    return cf;
}

}
