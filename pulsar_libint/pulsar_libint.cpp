#include "pulsar_libint/pulsar_libint.hpp"

namespace pulsar_libint{

libint2::BasisSet make_basis(const pulsar::BasisSet& bs)
{
    using Contraction=libint2::Shell::Contraction;
    const auto psr_pure=pulsar::ShellType::SphericalGaussian;
    libint2::BasisSet shells;
    for(const auto& shell : bs)
    {
        const double x=shell.get_coord(0),
                     y=shell.get_coord(1),
                     z=shell.get_coord(2);
        const std::array<double,3> carts({x,y,z});
        //LibInt2 does not support general contractions
        for(size_t i=0;i<shell.n_general_contractions();++i)
        {
            std::vector<Contraction> conts;
            const size_t L=shell.general_am(i);
            const bool is_pure=shell.get_type()==psr_pure;
            conts.push_back(Contraction({L,is_pure,shell.get_coefs(i)}));
            shells.push_back(libint2::Shell(shell.get_alphas(),conts, carts));
        }
    }
    return shells;
}

}//End namespace
