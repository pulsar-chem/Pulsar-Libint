#pragma once
#include <memory>
#include <array>
#include <pulsar_libint/pulsar_libint.hpp>
#include <pulsar/modulebase/ThreeCenterIntegral.hpp>
#include <libint2.hpp>


namespace pulsar_libint {

template<libint2::Operator Op>
class LibInt3C : public pulsar::ThreeCenterIntegral {
protected:
    std::array<libint2::BasisSet,3> bs_;
    libint2::Engine engine_;
public:
     LibInt3C(ID_t id):ThreeCenterIntegral(id)
     {
        libint2::initialize();
     }

    ~LibInt3C()
    {
        libint2::finalize();
    }

     void initialize_(unsigned int deriv,
                      const pulsar::Wavefunction &,
                      const pulsar::BasisSet & bs1,
                      const pulsar::BasisSet & bs2,
                      const pulsar::BasisSet & bs3)
     {

       bs_=std::array<libint2::BasisSet,3>({make_basis(bs1),
                                            make_basis(bs2),
                                            make_basis(bs3)});
       const size_t max_prims=std::max(
                    std::max(bs_[0].max_nprim(bs_[0]),bs_[1].max_nprim(bs_[1])),
                             bs_[2].max_nprim(bs_[2]));
       const size_t max_l=std::max(
                   std::max(bs_[0].max_l(bs_[0]),bs_[1].max_l(bs_[1])),
                             bs_[2].max_l(bs_[2]));

       engine_=libint2::Engine(Op,max_prims,max_l,deriv);
       engine_.set_braket(libint2::BraKet::xs_xx);
     }

     const double* calculate_(uint64_t shell1,
                              uint64_t shell2,
                              uint64_t shell3)
     {
         const auto& buf_vec=engine_.results();
         engine_.compute(bs_[0][shell1],bs_[1][shell2],bs_[2][shell3]);
         return buf_vec[0];
     }

};

using DF3C2E=LibInt3C<libint2::Operator::coulomb>;

}//End namespace
